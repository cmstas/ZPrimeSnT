#!/bin/env python3

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
#
graphs = dict()
sigmav = dict()
sigmae = dict()
#
graphfR = dict()
mcfracRv = dict()
mcfracRe = dict()
#
graphaR = dict()
alphaRv = dict()
alphaRe = dict()
#
graphnR = dict()
nRv = dict()
nRe = dict()
#
graphfL = dict()
mcfracLv = dict()
mcfracLe = dict()
#
graphaL = dict()
alphaLv = dict()
alphaLe = dict()
#
graphnL = dict()
nLv = dict()
nLe = dict()
#
for m in models:
    graphs[m] = dict()
    sigmav[m] = dict()
    sigmae[m] = dict()
    #
    graphfR[m] = dict()
    mcfracRv[m] = dict()
    mcfracRe[m] = dict()
    #
    graphaR[m] = dict()
    alphaRv[m] = dict()
    alphaRe[m] = dict()
    #
    graphnR[m] = dict()
    nRv[m] = dict()
    nRe[m] = dict()
    #
    graphfL[m] = dict()
    mcfracLv[m] = dict()
    mcfracLe[m] = dict()
    #
    graphaL[m] = dict()
    alphaLv[m] = dict()
    alphaLe[m] = dict()
    #
    graphnL[m] = dict()
    nLv[m] = dict()
    nLe[m] = dict()
    #
    for b in nbbins:
        graphs[m][b] = ROOT.TGraphErrors()
        sigmav[m][b] = numpy.array([],dtype=numpy.double)
        sigmae[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphfR[m][b] = ROOT.TGraphErrors()
        mcfracRv[m][b] = numpy.array([],dtype=numpy.double)
        mcfracRe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphaR[m][b] = ROOT.TGraphErrors()
        alphaRv[m][b] = numpy.array([],dtype=numpy.double)
        alphaRe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphnR[m][b] = ROOT.TGraphErrors()
        nRv[m][b] = numpy.array([],dtype=numpy.double)
        nRe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphfL[m][b] = ROOT.TGraphErrors()
        mcfracLv[m][b] = numpy.array([],dtype=numpy.double)
        mcfracLe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphaL[m][b] = ROOT.TGraphErrors()
        alphaLv[m][b] = numpy.array([],dtype=numpy.double)
        alphaLe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphnL[m][b] = ROOT.TGraphErrors()
        nLv[m][b] = numpy.array([],dtype=numpy.double)
        nLe[m][b] = numpy.array([],dtype=numpy.double)

masses = [200.0, 400.0, 700.0, 1000.0, 1500.0, 2000.0]
massarray = numpy.array(masses, dtype=numpy.double)
zeroarray = numpy.zeros(len(massarray), dtype=numpy.double)
sigmam = numpy.zeros(len(massarray), dtype=numpy.double)
sigmame = numpy.zeros(len(massarray), dtype=numpy.double)
nRm = numpy.zeros(len(massarray), dtype=numpy.double)
nRme = numpy.zeros(len(massarray), dtype=numpy.double)
nLm = numpy.zeros(len(massarray), dtype=numpy.double)
nLme = numpy.zeros(len(massarray), dtype=numpy.double)
alphaRm = numpy.zeros(len(massarray), dtype=numpy.double)
alphaRme = numpy.zeros(len(massarray), dtype=numpy.double)
alphaLm = numpy.zeros(len(massarray), dtype=numpy.double)
alphaLme = numpy.zeros(len(massarray), dtype=numpy.double)
mcfracRm = numpy.zeros(len(massarray), dtype=numpy.double)
mcfracRme = numpy.zeros(len(massarray), dtype=numpy.double)
mcfracLm = numpy.zeros(len(massarray), dtype=numpy.double)
mcfracLme = numpy.zeros(len(massarray), dtype=numpy.double)

for m in models:
    for b in nbbins:
        for mm in masses:
            fname = "./cpp/fitResults/d_mllinclusive_%s_MuDetAll_%s_M%.0f_2018_fitResult_dcbg.root"%(b,m,mm)
            fin = ROOT.TFile(fname)
            tfr = fin.Get("fitResult")
            ts = tfr.floatParsFinal().find("sigma")
            tfR = tfr.floatParsFinal().find("mc_frac_1")
            taR = tfr.floatParsFinal().find("alpha_1")
            tnR = tfr.floatParsFinal().find("n_1")
            tfL = tfr.floatParsFinal().find("mc_frac_2")
            taL = tfr.floatParsFinal().find("alpha_2")
            tnL = tfr.floatParsFinal().find("n_2")
            sigmav[m][b] = numpy.append(sigmav[m][b], ts.getValV())
            sigmae[m][b] = numpy.append(sigmae[m][b], ts.getError())
            mcfracRv[m][b] = numpy.append(mcfracRv[m][b], tfR.getValV())
            mcfracRe[m][b] = numpy.append(mcfracRe[m][b], tfR.getError())
            alphaRv[m][b] = numpy.append(alphaRv[m][b], taR.getValV())
            alphaRe[m][b] = numpy.append(alphaRe[m][b], taR.getError())
            nRv[m][b] = numpy.append(nRv[m][b], tnR.getValV())
            nRe[m][b] = numpy.append(nRe[m][b], tnR.getError())
            mcfracLv[m][b] = numpy.append(mcfracLv[m][b], tfL.getValV())
            mcfracLe[m][b] = numpy.append(mcfracLe[m][b], tfL.getError())
            alphaLv[m][b] = numpy.append(alphaLv[m][b], taL.getValV())
            alphaLe[m][b] = numpy.append(alphaLe[m][b], taL.getError())
            nLv[m][b] = numpy.append(nLv[m][b], tnL.getValV())
            nLe[m][b] = numpy.append(nLe[m][b], tnL.getError())
        graphs[m][b] = ROOT.TGraphErrors(len(massarray), massarray, sigmav[m][b], zeroarray, sigmae[m][b])
        graphs[m][b].SetMarkerColor(colors[m])
        graphs[m][b].SetLineColor(colors[m])
        graphs[m][b].SetMarkerStyle(markers[b])
        #
        graphfR[m][b] = ROOT.TGraphErrors(len(massarray), massarray, mcfracRv[m][b], zeroarray, mcfracRe[m][b])
        graphfR[m][b].SetMarkerColor(colors[m])
        graphfR[m][b].SetLineColor(colors[m])
        graphfR[m][b].SetMarkerStyle(markers[b])
        #
        graphaR[m][b] = ROOT.TGraphErrors(len(massarray), massarray, alphaRv[m][b], zeroarray, alphaRe[m][b])
        graphaR[m][b].SetMarkerColor(colors[m])
        graphaR[m][b].SetLineColor(colors[m])
        graphaR[m][b].SetMarkerStyle(markers[b])
        #
        graphnR[m][b] = ROOT.TGraphErrors(len(massarray), massarray, nRv[m][b], zeroarray, nRe[m][b])
        graphnR[m][b].SetMarkerColor(colors[m])
        graphnR[m][b].SetLineColor(colors[m])
        graphnR[m][b].SetMarkerStyle(markers[b])
        #
        graphfL[m][b] = ROOT.TGraphErrors(len(massarray), massarray, mcfracLv[m][b], zeroarray, mcfracLe[m][b])
        graphfL[m][b].SetMarkerColor(colors[m])
        graphfL[m][b].SetLineColor(colors[m])
        graphfL[m][b].SetMarkerStyle(markers[b])
        #
        graphaL[m][b] = ROOT.TGraphErrors(len(massarray), massarray, alphaLv[m][b], zeroarray, alphaLe[m][b])
        graphaL[m][b].SetMarkerColor(colors[m])
        graphaL[m][b].SetLineColor(colors[m])
        graphaL[m][b].SetMarkerStyle(markers[b])
        #
        graphnL[m][b] = ROOT.TGraphErrors(len(massarray), massarray, nLv[m][b], zeroarray, nLe[m][b])
        graphnL[m][b].SetMarkerColor(colors[m])
        graphnL[m][b].SetLineColor(colors[m])
        graphnL[m][b].SetMarkerStyle(markers[b])

for m in models:
    sigmam = sigmam + sigmav[m]["nBTag1"]
    sigmame = sigmame + (sigmae[m]["nBTag1"])*(sigmae[m]["nBTag1"])/((sigmav[m]["nBTag1"])*(sigmav[m]["nBTag1"]))
    sigmam = sigmam + sigmav[m]["nBTag2p"]
    sigmame = sigmame + (sigmae[m]["nBTag2p"])*(sigmae[m]["nBTag2p"])/((sigmav[m]["nBTag2p"])*(sigmav[m]["nBTag2p"]))
    nRm = nRm + nRv[m]["nBTag1"]
    nRme = nRme + (nRe[m]["nBTag1"])*(nRe[m]["nBTag1"])/((nRv[m]["nBTag1"])*(nRv[m]["nBTag1"]))
    nRm = nRm + nRv[m]["nBTag2p"]
    nRme = nRme + (nRe[m]["nBTag2p"])*(nRe[m]["nBTag2p"])/((nRv[m]["nBTag2p"])*(nRv[m]["nBTag2p"]))
    nLm = nLm + nLv[m]["nBTag1"]
    nLme = nLme + (nLe[m]["nBTag1"])*(nLe[m]["nBTag1"])/((nLv[m]["nBTag1"])*(nLv[m]["nBTag1"]))
    nLm = nLm + nLv[m]["nBTag2p"]
    nLme = nLme + (nLe[m]["nBTag2p"])*(nLe[m]["nBTag2p"])/((nLv[m]["nBTag2p"])*(nLv[m]["nBTag2p"]))
    alphaRm = alphaRm + alphaRv[m]["nBTag1"]
    alphaRme = alphaRme + (alphaRe[m]["nBTag1"])*(alphaRe[m]["nBTag1"])/((alphaRv[m]["nBTag1"])*(alphaRv[m]["nBTag1"]))
    alphaRm = alphaRm + alphaRv[m]["nBTag2p"]
    alphaRme = alphaRme + (alphaRe[m]["nBTag2p"])*(alphaRe[m]["nBTag2p"])/((alphaRv[m]["nBTag2p"])*(alphaRv[m]["nBTag2p"]))
    alphaLm = alphaLm + alphaLv[m]["nBTag1"]
    alphaLme = alphaLme + (alphaLe[m]["nBTag1"])*(alphaLe[m]["nBTag1"])/((alphaLv[m]["nBTag1"])*(alphaLv[m]["nBTag1"]))
    alphaLm = alphaLm + alphaLv[m]["nBTag2p"]
    alphaLme = alphaLme + (alphaLe[m]["nBTag2p"])*(alphaLe[m]["nBTag2p"])/((alphaLv[m]["nBTag2p"])*(alphaLv[m]["nBTag2p"]))
    mcfracRm = mcfracRm + mcfracRv[m]["nBTag1"]
    mcfracRme = mcfracRme + (mcfracRe[m]["nBTag1"])*(mcfracRe[m]["nBTag1"])/((mcfracRv[m]["nBTag1"])*(mcfracRv[m]["nBTag1"]))
    mcfracRm = mcfracRm + mcfracRv[m]["nBTag2p"]
    mcfracRme = mcfracRme + (mcfracRe[m]["nBTag2p"])*(mcfracRe[m]["nBTag2p"])/((mcfracRv[m]["nBTag2p"])*(mcfracRv[m]["nBTag2p"]))
    mcfracLm = mcfracLm + mcfracLv[m]["nBTag1"]
    mcfracLme = mcfracLme + (mcfracLe[m]["nBTag1"])*(mcfracLe[m]["nBTag1"])/((mcfracLv[m]["nBTag1"])*(mcfracLv[m]["nBTag1"]))
    mcfracLm = mcfracLm + mcfracLv[m]["nBTag2p"]
    mcfracLme = mcfracLme + (mcfracLe[m]["nBTag2p"])*(mcfracLe[m]["nBTag2p"])/((mcfracLv[m]["nBTag2p"])*(mcfracLv[m]["nBTag2p"]))

print(mcfracRm, mcfracRme)

sigmam = sigmam/(2*len(models))
sigmame = numpy.sqrt(sigmame)/sigmam
graphsm = ROOT.TGraph(len(massarray), massarray, sigmam)
#graphsm = ROOT.TGraphErrors(len(massarray), massarray, sigmam, zeroarray, sigmame)
nRm = nRm/(2*len(models))
nRme = numpy.sqrt(nRme)/nRm
graphnRm = ROOT.TGraphErrors(len(massarray), massarray, nRm, zeroarray, nRme)
nLm = nLm/(2*len(models))
nLme = numpy.sqrt(nLme)/nLm
graphnLm = ROOT.TGraphErrors(len(massarray), massarray, nLm, zeroarray, nLme)
alphaRm = alphaRm/(2*len(models))
alphaRme = numpy.sqrt(alphaRme)/alphaRm
graphaRm = ROOT.TGraphErrors(len(massarray), massarray, alphaRm, zeroarray, alphaRme)
alphaLm = alphaLm/(2*len(models))
alphaLme = numpy.sqrt(alphaLme)/alphaLm
graphaLm = ROOT.TGraphErrors(len(massarray), massarray, alphaLm, zeroarray, alphaLme)
mcfracRm = mcfracRm/(2*len(models))
mcfracRme = numpy.sqrt(mcfracRme)/mcfracRm
graphfRm = ROOT.TGraph(len(massarray), massarray, mcfracRm)
#graphfRm = ROOT.TGraphErrors(len(massarray), massarray, mcfracRm, zeroarray, mcfracRme)
mcfracLm = mcfracLm/(2*len(models))
mcfracLme = numpy.sqrt(mcfracLme)/mcfracLm
graphfLm = ROOT.TGraph(len(massarray), massarray, mcfracLm)
#graphfLm = ROOT.TGraphErrors(len(massarray), massarray, mcfracLm, zeroarray, mcfracLme)

ffit = ROOT.TF1("ffit","[0]*x*x+[1]*x+[2]",100,2500)
graphsm.Fit(ffit)
a = ffit.GetParameter(0)
b = ffit.GetParameter(1)
c = ffit.GetParameter(2)
ffit.SetLineColor(1)
ffit.SetLineWidth(2)
latex = ROOT.TLatex()
text = "#sigma = a Mass^{2} + b Mass + c"
texta = "a = %.2e"%a
textb = "b = %.2e"%b
textc = "c = %.2e"%c

fnR = ROOT.TF1("fnR","[0]*x+[1]",100,2500)
graphnRm.Fit(fnR)
fnR.SetLineColor(1)
fnR.SetLineWidth(2)
textnR = "n_{R} = a Mass + b"
anR = fnR.GetParameter(0)
bnR = fnR.GetParameter(1)
textanR = "a = %.2e"%anR
textbnR = "b = %.2e"%bnR

fnL = ROOT.TF1("fnL","[0]*x+[1]",100,2500)
graphnLm.Fit(fnL)
fnL.SetLineColor(1)
fnL.SetLineWidth(2)
textnL = "n_{L} = a Mass + b"
anL = fnL.GetParameter(0)
bnL = fnL.GetParameter(1)
textanL = "a = %.2e"%anL
textbnL = "b = %.2e"%bnL

faR = ROOT.TF1("faR","[0]*x+[1]",100,2500)
graphaRm.Fit(faR)
faR.SetLineColor(1)
faR.SetLineWidth(2)
textaR = "#alpha_{R} = a Mass + b"
aaR = faR.GetParameter(0)
baR = faR.GetParameter(1)
textaaR = "a = %.2e"%aaR
textbaR = "b = %.2e"%baR

faL = ROOT.TF1("faL","[0]*x+[1]",100,2500)
graphaLm.Fit(faL)
faL.SetLineColor(1)
faL.SetLineWidth(2)
textaL = "#alpha_{L} = a Mass + b"
aaL = faL.GetParameter(0)
baL = faL.GetParameter(1)
textaaL = "a = %.2e"%aaL
textbaL = "b = %.2e"%baL

ffR = ROOT.TF1("ffR","[0]*x+[1]",100,2500)
graphfRm.Fit(ffR)
ffR.SetLineColor(1)
ffR.SetLineWidth(2)
textfR = "f_{R} = a Mass + b"
afR = ffR.GetParameter(0)
bfR = ffR.GetParameter(1)
textafR = "a = %.2e"%afR
textbfR = "b = %.2e"%bfR

ffL = ROOT.TF1("ffL","[0]*x+[1]",100,2500)
graphfLm.Fit(ffL)
ffL.SetLineColor(1)
ffL.SetLineWidth(2)
textfL = "f_{L} = a Mass + b"
afL = ffL.GetParameter(0)
bfL = ffL.GetParameter(1)
textafL = "a = %.2e"%afL
textbfL = "b = %.2e"%bfL

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

ROOT.gStyle.SetOptStat(0)

can = ROOT.TCanvas("can","",600,600)
can.cd()

haxis = ROOT.TH1F("haxis","",1,100,2500)
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#sigma [GeV]")
haxis.GetYaxis().SetRangeUser(0.0, 100.0)
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

###

haxis.GetYaxis().SetTitle("f_{R}")
haxis.GetYaxis().SetRangeUser(0.0, 1.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphfR[m][b].Draw("PE,same")
    ffR.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textfR)
    latex.DrawLatexNDC(0.60, 0.80, textafR)
    latex.DrawLatexNDC(0.60, 0.75, textbfR)
    can.SaveAs("./cpp/fitResults/mcfracR_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphfR[m][b].Draw("PE,same")
    ffR.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textfR)
    latex.DrawLatexNDC(0.60, 0.80, textafR)
    latex.DrawLatexNDC(0.60, 0.75, textbfR)
    can.SaveAs("./cpp/fitResults/mcfracR_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("f_{L}")
haxis.GetYaxis().SetRangeUser(0.0, 1.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphfL[m][b].Draw("PE,same")
    ffL.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textfL)
    latex.DrawLatexNDC(0.60, 0.25, textafL)
    latex.DrawLatexNDC(0.60, 0.20, textbfL)
    can.SaveAs("./cpp/fitResults/mcfracL_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphfL[m][b].Draw("PE,same")
    ffL.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textfL)
    latex.DrawLatexNDC(0.60, 0.25, textafL)
    latex.DrawLatexNDC(0.60, 0.20, textbfL)
    can.SaveAs("./cpp/fitResults/mcfracL_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("#alpha_{R}")
haxis.GetYaxis().SetRangeUser(0.0, 2.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphaR[m][b].Draw("PE,same")
    faR.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textaR)
    latex.DrawLatexNDC(0.60, 0.25, textaaR)
    latex.DrawLatexNDC(0.60, 0.20, textbaR)
    can.SaveAs("./cpp/fitResults/alphaR_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphaR[m][b].Draw("PE,same")
    faR.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textaR)
    latex.DrawLatexNDC(0.60, 0.25, textaaR)
    latex.DrawLatexNDC(0.60, 0.20, textbaR)
    can.SaveAs("./cpp/fitResults/alphaR_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("#alpha_{L}")
haxis.GetYaxis().SetRangeUser(-2.0, 0.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphaL[m][b].Draw("PE,same")
    faL.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textaL)
    latex.DrawLatexNDC(0.60, 0.80, textaaL)
    latex.DrawLatexNDC(0.60, 0.75, textbaL)
    can.SaveAs("./cpp/fitResults/alphaL_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphaL[m][b].Draw("PE,same")
    faL.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textaL)
    latex.DrawLatexNDC(0.60, 0.80, textaaL)
    latex.DrawLatexNDC(0.60, 0.75, textbaL)
    can.SaveAs("./cpp/fitResults/alphaL_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("n_{R}")
haxis.GetYaxis().SetRangeUser(0.0, 15.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphnR[m][b].Draw("PE,same")
    fnR.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textnR)
    latex.DrawLatexNDC(0.60, 0.80, textanR)
    latex.DrawLatexNDC(0.60, 0.75, textbnR)
    can.SaveAs("./cpp/fitResults/nR_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphnR[m][b].Draw("PE,same")
    fnR.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textnR)
    latex.DrawLatexNDC(0.60, 0.80, textanR)
    latex.DrawLatexNDC(0.60, 0.75, textbnR)
    can.SaveAs("./cpp/fitResults/nR_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("n_{L}")
haxis.GetYaxis().SetRangeUser(0.0, 15.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphnL[m][b].Draw("PE,same")
    fnL.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textnL)
    latex.DrawLatexNDC(0.60, 0.25, textanL)
    latex.DrawLatexNDC(0.60, 0.20, textbnL)
    can.SaveAs("./cpp/fitResults/nL_vs_mass_nBTag_%s.png"%m)
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphnL[m][b].Draw("PE,same")
    fnL.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textnL)
    latex.DrawLatexNDC(0.60, 0.25, textanL)
    latex.DrawLatexNDC(0.60, 0.20, textbnL)
    can.SaveAs("./cpp/fitResults/nL_vs_mass_model_%s.png"%b)
    can.Update()
    can.Clear()
