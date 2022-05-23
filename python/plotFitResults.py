### python3

import os,sys
import ROOT
import numpy

models = ["Y3", "DY3", "DYp3", "B3mL2"]
colors = dict()
colors["Y3"] = ROOT.kViolet
colors["DY3"] = ROOT.kMagenta
colors["DYp3"] = ROOT.kRed
colors["B3mL2"] = ROOT.kCyan
nbbins = ["nBTag1p", "nBTag1", "nBTag2p"]
markers = dict()
markers["nBTag1p"] = 20
markers["nBTag1"]  = 21
markers["nBTag2p"] = 22
graphs = dict()
sigmav = dict()
sigmae = dict()
for m in models:
    graphs[m] = dict()
    sigmav[m] = dict()
    sigmae[m] = dict()
    for b in nbbins:
        graphs[m][b] = ROOT.TGraphErrors()
        sigmav[m][b] = numpy.array([],dtype=numpy.double)
        sigmae[m][b] = numpy.array([],dtype=numpy.double)
masses = [200.0, 400.0, 700.0, 1000.0, 1500.0, 2000.0]
massarray = numpy.array(masses, dtype=numpy.double)
zeroarray = numpy.zeros(len(massarray), dtype=numpy.double)
sigmam = numpy.zeros(len(massarray), dtype=numpy.double)
for m in models:
    for b in nbbins:
        for mm in masses:
            fname = "./cpp/fitResults/d_mllinclusive_%s_MuDetAll_%s_M%.0f_2018_fitResult_dcbvoigt.root"%(b,m,mm)
            fin = ROOT.TFile(fname)
            tfr = fin.Get("fitResult")
            ts = tfr.floatParsFinal().find("sigma")
            sigmav[m][b] = numpy.append(sigmav[m][b], ts.getValV())
            sigmae[m][b] = numpy.append(sigmae[m][b], ts.getError())
        graphs[m][b] = ROOT.TGraphErrors(len(massarray), massarray, sigmav[m][b], zeroarray, sigmae[m][b])
        graphs[m][b].SetMarkerColor(colors[m])
        graphs[m][b].SetLineColor(colors[m])
        graphs[m][b].SetMarkerStyle(markers[b])

for m in models:
    sigmam = sigmam + sigmav[m]["nBTag1"]
sigmam = sigmam/len(models)
graphm = ROOT.TGraph(len(massarray), massarray, sigmam)

ffit = ROOT.TF1("ffit","[0]*x*x+[1]*x+[2]",100,2500)
graphm.Fit(ffit)
a = ffit.GetParameter(0)
b = ffit.GetParameter(1)
c = ffit.GetParameter(2)
ffit.SetLineColor(1)
ffit.SetLineWidth(2)
latex = ROOT.TLatex()
text = "#sigma = a Mass^{2} + b Mass + c"
texta = "a = %.1e"%a
textb = "b = %.1e"%b
textc = "c = %.1e"%c

legnbtag = dict()
legmodel = dict()
for m in models:
    legnbtag[m] = ROOT.TLegend(0.15, 0.65, 0.35, 0.85)
    legnbtag[m].SetLineColor(0)
    legnbtag[m].SetFillColor(0)
    legnbtag[m].SetHeader(m,"L")
    for b in nbbins:
        legnbtag[m].AddEntry(graphs[m][b], b, "P")
for b in nbbins:
    legmodel[b] = ROOT.TLegend(0.15, 0.65, 0.35, 0.85)
    legmodel[b].SetLineColor(0)
    legmodel[b].SetFillColor(0)
    legmodel[b].SetHeader(b,"L")
    for m in models:
        legmodel[b].AddEntry(graphs[m][b], m, "P")

haxis = ROOT.TH1F("haxis","",1,100,2500)
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#sigma [GeV]")
haxis.GetYaxis().SetRangeUser(0.0, 100.0)

ROOT.gStyle.SetOptStat(0)

can = ROOT.TCanvas("can","",600,600)
can.cd()

for m in models:
    haxis.Draw()
    for b in nbbins:
        graphs[m][b].Draw("PE,same")
    legnbtag[m].Draw("same")
    ffit.Draw("same")
    latex.DrawLatexNDC(0.35, 0.15, text)
    latex.DrawLatexNDC(0.60, 0.35, texta)
    latex.DrawLatexNDC(0.60, 0.30, textb)
    latex.DrawLatexNDC(0.60, 0.25, textc)
    can.SaveAs("./cpp/fitResults/sigma_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()

for b in nbbins:
    haxis.Draw()
    for m in models:
        graphs[m][b].Draw("PE,same")
    legmodel[b].Draw("same")
    ffit.Draw("same")
    latex.DrawLatexNDC(0.35, 0.15, text)
    latex.DrawLatexNDC(0.60, 0.35, texta)
    latex.DrawLatexNDC(0.60, 0.30, textb)
    latex.DrawLatexNDC(0.60, 0.25, textc)
    can.SaveAs("./cpp/fitResults/sigma_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()
