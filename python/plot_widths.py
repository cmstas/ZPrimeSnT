#!/bin/env python3

import os,sys
import ROOT
import numpy

models = ["Y3", "DY3", "DYp3", "B3mL2"]
masses = [200.0, 400.0, 700.0, 1000.0, 1500.0, 2000.0]
massarray = numpy.array(masses, dtype=numpy.double)

colors = dict()
colors["Y3"] = ROOT.kViolet
colors["DY3"] = ROOT.kMagenta
colors["DYp3"] = ROOT.kRed
colors["B3mL2"] = ROOT.kCyan

widths = dict()
widths["Y3"] = dict()
widths["Y3"]["100"] = 0.000872
widths["Y3"]["200"] = 0.004015
widths["Y3"]["400"] = 0.049430
widths["Y3"]["700"] = 0.306252
widths["Y3"]["1000"] = 0.913002
widths["Y3"]["1500"] = 3.114878
widths["Y3"]["2000"] = 7.410280
widths["DY3"] = dict()
widths["DY3"]["100"] = 0.002599
widths["DY3"]["200"] = 0.017882
widths["DY3"]["400"] = 0.157854
widths["DY3"]["700"] = 0.888927
widths["DY3"]["1000"] = 2.613129
widths["DY3"]["1500"] = 8.855362
widths["DY3"]["2000"] = 21.019506
widths["DYp3"] = dict()
widths["DYp3"]["100"] = 0.000849
widths["DYp3"]["200"] = 0.005838
widths["DYp3"]["400"] = 0.051549
widths["DYp3"]["700"] = 0.290284
widths["DYp3"]["1000"] = 0.853301
widths["DYp3"]["1500"] = 2.891601
widths["DYp3"]["2000"] = 6.863586
widths["B3mL2"] = dict()
widths["B3mL2"]["100"] = 0.001072
widths["B3mL2"]["200"] = 0.008755
widths["B3mL2"]["400"] = 0.078932
widths["B3mL2"]["700"] = 0.441860
widths["B3mL2"]["1000"] = 1.291954
widths["B3mL2"]["1500"] = 4.363471
widths["B3mL2"]["2000"] = 10.344343

graphs = dict()
ffits = dict()
for m in models:
    widtharray = numpy.array([], dtype=numpy.double) 
    for mm in masses:
        widtharray = numpy.append(widtharray, widths[m]["%.0f"%mm])

    graphs[m] = ROOT.TGraph(len(massarray),massarray,widtharray)
    graphs[m].SetMarkerColor(colors[m])
    graphs[m].SetMarkerStyle(20)

    ffits[m] = ROOT.TF1("ffit%s"%m,"[0]*x*x+[1]*x+[2]",100,2500)
    ffits[m].SetLineColor(colors[m])
    ffits[m].SetLineWidth(2)
    graphs[m].Fit(ffits[m])

ROOT.gStyle.SetOptStat(0)

can = ROOT.TCanvas("can","",600,600)
can.cd()

legmodel = ROOT.TLegend(0.15, 0.65, 0.35, 0.85)
legmodel.SetLineColor(0)
legmodel.SetFillColor(0)
for m in models:
    legmodel.AddEntry(graphs[m], m, "P")

haxis = ROOT.TH1F("haxis","",1,100,2500)
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#Gamma [GeV]")
haxis.GetYaxis().SetRangeUser(0.0, 100.0)
haxis.Draw()
for m in models:
    graphs[m].Draw("PE,same")
    ffits[m].Draw("same")
legmodel.Draw("same")
can.SaveAs("./cpp/fitResults_dcbg/gamma_vs_mass.png")
can.Update()
can.Clear()
