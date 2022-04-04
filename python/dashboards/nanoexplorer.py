#!/usr/bin/env python3

import dash
# import dash_bootstrap_components as dbc
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output
import dash_table
from urllib.parse import urlparse, parse_qsl, urlencode
import pandas as pd
import plotly.graph_objs as go
from plotly.subplots import make_subplots
import os
import ast
import numpy as np
from yahist import Hist1D
# import uproot
import scipy.special
import awkward as ak

import json
import requests
import subprocess
import uproot4
import uproot3

import functools
# import ROOT as r
from yahist import Hist1D

@functools.lru_cache(128)
def datasets_from_pattern(pattern):
    data = []
    cmd = f"dasgoclient -query 'dataset={pattern}' -json"
    js = json.loads(subprocess.getoutput(cmd))
    for j in js:
        j = j["dataset"][0]
        if j.get("status") != "VALID": continue
        data.append(dict(
            creation_date = j["creation_date"],
            name = j["name"],
        ))
    df = pd.DataFrame(data)
    df["creation_date"] = pd.to_datetime(df["creation_date"], unit="s")
    df = df.sort_values("creation_date", ascending=False).drop_duplicates(["name"]).reset_index(drop=True)
    df = df[["creation_date","name"]]
    return df

@functools.lru_cache(128)
def info_from_dataset(dataset):
    data = []
    cmd = f"dasgoclient -query 'file dataset={dataset}' -json"
    js = json.loads(subprocess.getoutput(cmd))
    for j in js:
        f = j["file"][0]
        data.append(dict(
            name=f["name"],
            nevents=f["nevents"],
            filesizeGB=round(f["size"]/1024**3,2),
        ))
    df = pd.DataFrame(data)
    df = df.sort_values("nevents", ascending=True).reset_index(drop=True)
    return df

@functools.lru_cache(128)
def branches_from_file(fname):
    f = uproot3.open("root://xcache-redirector.t2.ucsd.edu:2042/"+fname)
    t = f["Events"]
    data = []
    for name in t.keys():
        b = t[name]
        data.append(dict(
            name=name.decode(),
            desc=b._fTitle.decode(),
        ))
    df_branches = pd.DataFrame(data)
    return df_branches

@functools.lru_cache(128)
def hist_from_branch(fname, branch):
    from yahist import Hist1D
    f = uproot4.open("root://xcache-redirector.t2.ucsd.edu:2042/"+fname)
    t = f["Events"]
    arr = t[branch].array(entry_stop=500)
    try:
        arr = np.array(ak.flatten(arr))
    except:
        pass
    h = Hist1D(arr)
    return h


def get_table(df, **kwargs):
    return dash_table.DataTable(
            columns=[{"name": i, "id": i} for i in df.columns],
            data=df.to_dict('records'),
            sort_action="native",
            selected_rows = [],
            sort_mode="multi",
            page_action="native",
            page_current= 0,
            style_as_list_view=True,
            style_cell_conditional=[
                {
                    'if': {'column_id': c},
                    'textAlign': 'left'
                    } for c in df.columns
                ],
            style_cell={'padding': '5px',
                'font-family':'sans-serif',
                'font-size':'75%',
                },
            style_header={
                'backgroundColor': 'white',
                'fontWeight': 'bold'
                },
            **kwargs,
            )

# external_stylesheets = [dbc.themes.BOOTSTRAP]
external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
app = dash.Dash(__name__,
        external_stylesheets=external_stylesheets,
        url_base_pathname='/nanoexplorer/')
app.config.suppress_callback_exceptions = True

app.layout = html.Div([
    html.B("Dataset pattern: "), dcc.Input(
        id="input-pattern",
        type="text",
        debounce=True,
        style = {"min-width": "40%"},
        value="/TTTT*/*NanoAODv7*/NANOAODSIM",
    ),
    html.Hr(), html.B("Matching datasets:"), html.Div(id='table-datasets-container'),
    html.Hr(), html.B("Files:"), html.Div(id='table-files-container'),
    html.Hr(), html.B("Branches:"), html.Div(id='table-branches-container'),
    html.Div(id="graphs"),
    ])

@app.callback(
    Output('table-datasets-container', "children"),
    [Input('input-pattern', "value")])
def update_datasets(pattern):
    df = datasets_from_pattern(pattern)
    return [get_table(df, id='table-datasets', row_selectable="single", page_size=5)]

@app.callback(
    Output('table-files-container', "children"),
    [Input('table-datasets', "derived_virtual_data"),
     Input('table-datasets', "derived_virtual_selected_rows")])
def update_files(rows, derived_virtual_selected_rows):
    if derived_virtual_selected_rows is None:
        derived_virtual_selected_rows = []
    selected = derived_virtual_selected_rows
    if selected:
        dataset = rows[selected[0]]["name"]
        df = info_from_dataset(dataset)
        return [get_table(df, id='table-files', row_selectable="single", page_size=4)]
    return [dcc.Markdown("Please select a dataset above (on the left)", dangerously_allow_html=True)]

@app.callback(
    Output('table-branches-container', "children"),
    # [Input('input-pattern', "value")])
    [Input('table-files', "derived_virtual_data"),
     Input('table-files', "derived_virtual_selected_rows")])
def update_branches(rows, derived_virtual_selected_rows):
    if derived_virtual_selected_rows is None:
        derived_virtual_selected_rows = []
    selected = derived_virtual_selected_rows

    if selected:
        fname = rows[selected[0]]["name"]
        df = branches_from_file(fname)
        df["fname"] = fname
        return [get_table(df, id="table-branches", row_selectable="single", hidden_columns=["fname"], filter_action="native", page_size=8)]

    return [dcc.Markdown("Please select a file above", dangerously_allow_html=True)]

@app.callback(
        Output('graphs', 'children'),
        [Input('table-branches', "derived_virtual_data"),
         Input('table-branches', "derived_virtual_selected_rows")])
def get_graphs(rows, derived_virtual_selected_rows):

    if derived_virtual_selected_rows is None:
        derived_virtual_selected_rows = []
    selected = derived_virtual_selected_rows

    if not selected:
        return [dcc.Markdown("Please select a branch above and be super super patient (a minute or so)", dangerously_allow_html=True)]

    row = rows[selected[0]]
    fname = row["fname"]
    name = row["name"]
    title = f"{name}"

    h = hist_from_branch(fname, name)

    layout = dict(
            height=300,
            width=400,
            template="plotly_white",
            barmode='overlay',
            title=title,
            yaxis=dict(
                showgrid=True,
                title="Events",
                type="linear",
                ),
            xaxis=dict(
                showgrid=True,
                title="",
                type="linear",
                ),
            bargap=0.0,
            )
    data = go.Bar(x=h.bin_centers, y=h.counts,
           marker=dict(
               line = dict(
               width=0.0
               ),
           ),
           opacity=0.75,
    )
    fig = dict( data = [data], layout=layout,)
    g_plot = dcc.Graph(figure=fig, id='g_plot')
    return [g_plot]

if __name__ == '__main__':
    app.run_server(host="0.0.0.0", port=11338, debug=False)
