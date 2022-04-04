import dash
import dash_core_components as dcc
import dash_html_components as html
import dash_table
import plotly.graph_objs as go
import os

import numpy as np
import awkward as ak
import pandas as pd
from particle import Particle
import uproot4
import uproot3_methods

import matplotlib.pyplot as plt
from matplotlib import colors

import pydot
import base64

from functools import lru_cache

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
app = dash.Dash(__name__,
        external_stylesheets=external_stylesheets,
        url_base_pathname='/nanogentree/')
app.config.suppress_callback_exceptions = True

def build_layout():
    params = {}
    input_filename = dcc.Input(
        id="filename",
        debounce=True,
        value = "root://xcache-redirector.t2.ucsd.edu:2042//store/mc/RunIISummer20UL17NanoAODv2/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v3/100000/A150DECA-C4E5-6C4A-8100-2B5594C25952.root",
        style = {"min-width": "80%"},
        placeholder = "/store/..., /hadoop/..., or root://...",
        type="text",
    )
    input_entry = dcc.Input(
        id="entry",
        debounce=False,
        type="number",
        value = 0,
        min = 0,

    )

    checklist_modifiers = dcc.Checklist(
        id="modifiers",
        options=[
            {'label': ' show flags', 'value': 'show_flags'},
            {'label': ' show info', 'value': 'show_info'},
            {'label': ' skip similar', 'value': 'skip_similar'},
        ],
        # switch=True,
        value=["skip_similar"],
        # labelStyle={'display': 'inline-block', "padding": "0px 15px" },
    )

    layout = [
            html.H1(children='NanoGENeology'),
            html.I("File "), input_filename,
            html.Br(),
            html.I("Entry "), input_entry,
            checklist_modifiers,
            html.Hr(),
            html.Img(id="image", height="100%"),
            ]

    return layout

# app.layout = build_layout
app.layout = html.Div(children=build_layout())

# which ones to tie to callbacks
component_ids = [
                "filename",
                "entry",
                "modifiers",
                ]

@lru_cache(50)
def get_tree(fname, treename="Events"):
    t = uproot4.open(fname)[treename]
    return t

# https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
statusflags = [
    "isPrompt",
    "isDecayedLeptonHadron",
    "isTauDecayProduct",
    "isPromptTauDecayProduct",
    "isDirectTauDecayProduct",
    "isDirectPromptTauDecayProduct",
    "isDirectHadronDecayProduct",
    "isHardProcess",
    "fromHardProcess",
    "isHardProcessTauDecayProduct",
    "isDirectHardProcessTauDecayProduct",
    "fromHardProcessBeforeFSR",
    "isFirstCopy",
    "isLastCopy",
    "isLastCopyBeforeFSR",
]

@lru_cache(1000)
def get_df_for_entry(fname, entry):
    """
    Takes filename of nanoaod ntuple
    and entry number (first event in a root file is entry 0)
    """
    t = get_tree(fname)
    kw = dict(entry_start=entry, entry_stop=entry+1)
    mother_idxs = t["GenPart_genPartIdxMother"].array(**kw)[0]
    ids = t["GenPart_pdgId"].array(**kw)[0]
    statuses = t["GenPart_status"].array(**kw)[0]
    pts = t["GenPart_pt"].array(**kw)[0]
    etas = t["GenPart_eta"].array(**kw)[0]
    phis = t["GenPart_phi"].array(**kw)[0]
    masses = t["GenPart_mass"].array(**kw)[0]
    flags = t["GenPart_statusFlags"].array(**kw)[0]
    energies = uproot3_methods.TLorentzVectorArray.from_ptetaphim(pts,etas,phis,masses).energy

    df = pd.DataFrame()
    df["mother_idx"] = np.array(mother_idxs).astype(int)
    df["id"] = np.array(ids).astype(int)
    df["status"] = np.array(statuses).astype(int)
    df["pt"] = pts
    df["eta"] = etas
    df["phi"] = phis
    df["mass"] = masses
    flags = map(lambda bs: [f[1] for f in zip(np.binary_repr(bs)[::-1], statusflags) if f[0] == "1"], flags)
    df["flags"] = list(flags)
    df["energy"] = energies

    df.loc[df["mother_idx"] == -1, "mother_idx"] = 0

    x = pd.DataFrame(dict(idx=df.index.values, midx=df.mother_idx.values)).groupby("midx")["idx"].count()
    df.loc[x.index, "daughters"] = x.values
    df["daughters"] = df["daughters"].fillna(0).astype(int)
    df["mass"] = df["mass"].fillna(0.)
    df["siblings"] = [df["daughters"].values[midx]-1 for midx in df["mother_idx"].values]
    df["nskip"] = 0
    df["skip"] = False
    df["mother_idx_unique"] = df["mother_idx"].copy()


    # find runs of parentage where the particle is the same (radiation with slight changes in pT,eta,phi)
    # mark these to be potentially suppressed later
    for i, leaf in df[(df["siblings"] == 0) & (df["daughters"] != 1)].iterrows():
        mother_idx = leaf["mother_idx"]
        niter = 0
        lineage = []
        for j in range(20):
            lineage.append(mother_idx)
            if df.loc[mother_idx]["id"] != leaf["id"]:
                break
            if df.loc[mother_idx]["mother_idx"] == mother_idx:
                break
            mother_idx = df.loc[mother_idx]["mother_idx"]
        if len(lineage) < 4: continue
        for idx in lineage[:-2]:
            df.loc[idx, "skip"] = True
        df.loc[i, "mother_idx_unique"] = lineage[-2]
        df.loc[i, "nskip"] = len(lineage)-2

    return df

def make_svgsrc_from_df(df, show_flags=False, show_info=False, skip_similar=False):
    if skip_similar:
        df = df[~df["skip"]].copy()
        df["mother_idx"] = df["mother_idx_unique"]
    cmap = plt.cm.get_cmap('Blues')
    # https://graphviz.org/doc/info/shapes.html
#     rankdir = "TB" if (show_info or show_flags) else "LR"
    ranksep = 0.2 if (show_info or show_flags) else 0.0
    rankdir = "TB"
    dot = pydot.Dot(rankdir=rankdir, ranksep=ranksep)
    dot.set('concentrate', False)
    dot.set_node_defaults(shape='record', fontsize=10)
    for idx,row in df.iterrows():
        # print(row)
        idx = int(idx)
        midx = int(row["mother_idx"])
        nodename = f"node{idx}"
        parentnodename = f"node{midx}"

        pdgid = int(row['id'])
        part_name = Particle.from_pdgid(pdgid).name
        flagsrc = ""
        if show_flags:
            flagsrc += "<font point-size='8'>"
            for flag in row["flags"]:
                flagsrc += f"<br/>{flag}"
            flagsrc += "</font>"
        info = ""
        if show_info:
            info += f"""<br/><br/>status  = {row['status']:.0f} <br/>
p<sub>T</sub>  = {row['pt']:.1f} <br/>
&eta; = {row['eta']:.2f} <br/>
&phi; = {row['phi']:.2f} <br/>
mass = {row['mass']:.2f}"""

        nodelabel = f"""<
        <font face="sans-serif"> <b> <font point-size="14">{pdgid}</font> </b><font point-size="12">({part_name})</font>{info}{flagsrc}</font>
        >"""
        energy = np.nan_to_num(row["energy"])
        if energy == 0.: energy = 6500.
        fe = np.clip(energy/1000.,0,0.5)
        color = colors.to_hex(cmap(fe))
        node = pydot.Node(nodename, label=nodelabel, fillcolor=color, style="filled")
        edgelabel = f"{int(row['nskip'])} skipped" if (skip_similar and (row["nskip"] != 0)) else ""
        edge = pydot.Edge(parentnodename, nodename, label=edgelabel)
        dot.add_node(node)
        dot.add_edge(edge)

    # print(dot)
    svg = dot.create_svg()
    # print(svg)
    data = base64.b64encode(svg).decode()
    src = f"data:image/svg+xml;base64,{data}"
    return src

@app.callback(dash.dependencies.Output('image', 'src'),
              inputs=[dash.dependencies.Input(i, 'value') for i in component_ids])
def get_image(filename, entry, modifiers):
    # print(modifiers)

    opts = dict()
    for m in modifiers:
        opts[m] = True
    # print(opts)

    df = get_df_for_entry(filename, entry)
    # print(df)
    src = make_svgsrc_from_df(df, **opts)
    # print(src)

    return src



if __name__ == '__main__':
    app.run_server(host="0.0.0.0", port=11337, debug=False)

