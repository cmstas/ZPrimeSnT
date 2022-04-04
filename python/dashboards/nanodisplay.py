import dash
import dash_core_components as dcc
import dash_html_components as html
import dash_table
import plotly.graph_objs as go
from plotly.subplots import make_subplots
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
        url_base_pathname='/nanodisplay/')
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
            {'label': ' dummy 1', 'value': 'dummy_1'},
            {'label': ' dummy 2', 'value': 'dummy_2'},
        ],
        # switch=True,
        value=["dummy_2"],
        # labelStyle={'display': 'inline-block', "padding": "0px 15px" },
    )

    layout = [
            html.H1(children='NanoDisplay'),
            html.I("File "), input_filename,
            html.Br(),
            html.I("Entry "), input_entry,
            checklist_modifiers,
            html.Hr(),
            html.Div(id="graphs"),
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

def ptetaphi_to_xyz(pt, eta, phi, norm=True):
    x = pt*np.cos(phi)
    y = pt*np.sin(phi)
    z = pt/np.tan(2*np.arctan(np.exp(-eta)))
    if norm:
        norm = (x**2+y**2+z**2)**0.5
        norm *= 0.5
        x, y, z = x/norm, y/norm, z/norm
    return x, y, z

def cylinder(r, h, a=0, nt=100, nv=50):
    """
    parametrize the cylinder of radius r, height h, base point a
    """
    theta = np.linspace(-np.pi/2-3*np.pi/4, +np.pi/2-3*np.pi/4, nt)
    v = np.linspace(a, a + h, nv)
    theta, v = np.meshgrid(theta, v)
    x = r * np.cos(theta)
    y = r * np.sin(theta)
    z = v
    return x, y, z

@lru_cache(50)
def get_tree(fname, treename="Events"):
    t = uproot4.open(fname)[treename]
    return t

@lru_cache(1000)
def get_info_for_entry(fname, entry):
    """
    Takes filename of nanoaod ntuple
    and entry number (first event in a root file is entry 0)
    """
    t = get_tree(fname)
    kw = dict(entry_start=entry, entry_stop=entry+1)
    info = dict()
    info["jet_pt"] = list(t["Jet_pt"].array(**kw)[0])
    info["jet_eta"] = list(t["Jet_eta"].array(**kw)[0])
    info["jet_phi"] = list(t["Jet_phi"].array(**kw)[0])
    info["jet_mass"] = list(t["Jet_mass"].array(**kw)[0])

    info["electron_pt"] = list(t["Electron_pt"].array(**kw)[0])
    info["electron_eta"] = list(t["Electron_eta"].array(**kw)[0])
    info["electron_phi"] = list(t["Electron_phi"].array(**kw)[0])
    info["electron_charge"] = list(t["Electron_charge"].array(**kw)[0])

    info["muon_pt"] = list(t["Muon_pt"].array(**kw)[0])
    info["muon_eta"] = list(t["Muon_eta"].array(**kw)[0])
    info["muon_phi"] = list(t["Muon_phi"].array(**kw)[0])
    info["muon_charge"] = list(t["Muon_charge"].array(**kw)[0])

    info["met_pt"] = float(t["MET_pt"].array(**kw)[0])
    info["met_phi"] = float(t["MET_phi"].array(**kw)[0])

    return info

# @app.callback(dash.dependencies.Output('graphs', 'children'),
#               inputs=[dash.dependencies.Input(i, 'value') for i in component_ids])
# def get_graphs(filename, entry, modifiers):
#     info = get_info_for_entry(filename, entry)
#     print(info)
#     fig = make_subplots()
#     x = [1, 2, 3, 4, 5]
#     y = [10, 10, 20, 20, 10]
#     data = go.Bar(x=x, y=y,
#            marker=dict(
#                line = dict(
#                width=0.0
#                ),
#            ),
#            opacity=0.75,
#     )
#     fig.add_trace(data)
#     g_plot = dcc.Graph(figure=fig, id='g_plot')
#     return [g_plot]

@app.callback(dash.dependencies.Output('graphs', 'children'),
              inputs=[dash.dependencies.Input(i, 'value') for i in component_ids])
def get_graphs(filename, entry, modifiers):
    info = get_info_for_entry(filename, entry)

    fig = make_subplots()

    jet_pt = info["jet_pt"]
    jet_eta = info["jet_eta"]
    jet_phi = info["jet_phi"]
    jet_mass = info["jet_mass"]
    njet = len(jet_pt)
    vx, vy, vz = [], [], []
    vu, vv, vw = [], [], []
    hovertexts = []
    for i in range(njet):
        hovertexts.append(f"<b>Jet</b><br>p<sub>T</sub> = {jet_pt[i]:.1f}<br>η = {jet_eta[i]:.2f}<br>φ = {jet_phi[i]:.2f}<br>mass = {jet_mass[i]:.1f}")
        vx.append(0)
        vy.append(0)
        vz.append(0)
        x, y, z = ptetaphi_to_xyz(jet_pt[i], jet_eta[i], jet_phi[i], norm=True)
        vu.append(y)
        vv.append(z)
        vw.append(z)
    fig.add_trace(
        go.Cone(
            x=vx,
            y=vz,
            z=vy,  # note the flip
            u=vu,
            v=vw,
            w=vv,  # note the flip
            sizemode="absolute",
            anchor="tip",
            colorscale=[[0, "red"], [1, "red"]],
            name=f"Jets ({njet})",
            showlegend=True,
            showscale=False,
            opacity=0.3,
            hoverinfo="text",
            hovertext=hovertexts,
        ),
    )

    electron_pt = info["electron_pt"]
    electron_eta = info["electron_eta"]
    electron_phi = info["electron_phi"]
    electron_charge = info["electron_charge"]
    nelectron = len(electron_pt)
    vx, vy, vz = [], [], []
    vu, vv, vw = [], [], []
    hovertexts = []
    for i in range(nelectron):
        hovertexts.append(f"<b>Electron</b><br>p<sub>T</sub> = {electron_pt[i]:.1f}<br>η = {electron_eta[i]:.2f}<br>φ = {electron_phi[i]:.2f}<br>charge = {electron_charge[i]:+}")
        vx.append(0)
        vy.append(0)
        vz.append(0)
        x, y, z = ptetaphi_to_xyz(electron_pt[i], electron_eta[i], electron_phi[i], norm=True)
        vu.append(y)
        vv.append(z)
        vw.append(z)

    fig.add_trace(
        go.Cone(
            x=vx,
            y=vz,
            z=vy,  # note the flip
            u=vu,
            v=vw,
            w=vv,  # note the flip
            sizemode="absolute",
            anchor="tip",
            colorscale=[[0, "blue"], [1, "blue"]],
            name=f"Electrons ({nelectron})",
            showlegend=True,
            showscale=False,
            opacity=0.3,
            hoverinfo="text",
            hovertext=hovertexts,
        ),
    )


    muon_pt = info["muon_pt"]
    muon_eta = info["muon_eta"]
    muon_phi = info["muon_phi"]
    muon_charge = info["muon_charge"]
    nmuon = len(muon_pt)
    # return to 0 each time
    vx, vy, vz = [], [], []
    hovertexts = []
    for i in range(nmuon):
        hovertexts.append("")
        vx.append(0)
        vy.append(0)
        vz.append(0)
        hovertexts.append(f"<b>Muon</b><br>p<sub>T</sub> = {muon_pt[i]:.1f}<br>η = {muon_eta[i]:.2f}<br>φ = {muon_phi[i]:.2f}<br>charge = {muon_charge[i]:+}")
        x, y, z = ptetaphi_to_xyz(muon_pt[i], muon_eta[i], muon_phi[i], norm=True)
        vx.append(x)
        vy.append(y)
        vz.append(z)
    fig.add_trace(
        go.Scatter3d(
            x=vx,
            y=vz,
            z=vy,  # note the flip
            marker=dict(size=0.001),
            line=dict(color="red", width=4),
            name=f"Muons ({nmuon})",
            mode="lines+markers",
            hoverinfo="text",
            hovertext=hovertexts,
        )
    )

    met_pt = info["met_pt"]
    met_phi = info["met_phi"]
    x, y, z = ptetaphi_to_xyz(met_pt, 0., met_phi, norm=True)
    vx = [0, x]
    vy = [0, y]
    vz = [0, z]
    fig.add_trace(
        go.Scatter3d(
            x=vx,
            y=vz,
            z=vy,  # note the flip
            marker=dict(size=0.001),
            line=dict(color="black", width=4),
            name="MET",
            mode="lines+markers",
            hoverinfo="name+text",
            hovertemplate=f"p<sub>T</sub> = {met_pt:.1f} GeV<br>φ = {met_phi:.2f}"
        )
    )

    vx, vy, vz = cylinder(1, 4, a=-2, nt=20, nv=2)
    fig.add_trace(
        go.Surface(
            x=vx,
            y=vz,
            z=vy,  # note the flip
            colorscale=[[0, "gray"], [1, "gray"]],
            opacity=0.1,
            showscale=False,
            hoverinfo="none",
            name="Dumb cylinder",
            showlegend=True,
            visible="legendonly",
        )
    )

    sf = 0.5
    fig.update_layout(
        height=600,
        width=800,
        template="plotly",
        scene=dict(
            aspectratio=dict(x=sf * 1, y=sf * 2, z=sf * 1),
            xaxis=dict(
                tickvals= [-1,+1],
                title="x",
                range=[-1, 1],
                showspikes=False,
            ),
            yaxis=dict(
                tickvals= [-1,+1],
                title="z",
                range=[-2, 2],
                showspikes=False,
            ),
            zaxis=dict(
                tickvals= [-1,+1],
                title="y",
                range=[-1, 1],
                showspikes=False,
            ),
        ),
        margin=dict(r=0, b=0, l=0, t=0),
        legend=dict(yanchor="top", y=0.99, xanchor="left", x=0.01),
    )

    g_plot = dcc.Graph(figure=fig, id='g_plot')
    return [g_plot]

if __name__ == '__main__':
    app.run_server(host="0.0.0.0", port=11339, debug=False)

