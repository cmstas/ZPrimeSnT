#!/bin/env python3
import os,sys
import ROOT
import numpy

indir = sys.argv[1]

models = ["Y3", "DY3", "DYp3", "B3mL2"]
legmod = dict()
legmod["Y3"] = "Y_{3}"
legmod["DY3"] = "DY_{3}"
legmod["DYp3"] = "DY'_{3}"
legmod["B3mL2"] = "B_{3}-L_{2}"
colors = dict()
colors["Y3"] = ROOT.kViolet
colors["DY3"] = ROOT.kMagenta
colors["DYp3"] = ROOT.kRed
colors["B3mL2"] = ROOT.kCyan
#nbbins = ["nBTag1p", "nBTag1", "nBTag2p"]
nbbins = ["ch0", "ch1", "ch2"]
markers = dict()
#markers["nBTag1p"] = 20
#markers["nBTag1"]  = 21
#markers["nBTag2p"] = 22
markers["ch0"] = 20
markers["ch1"]  = 21
markers["ch2"] = 22
legch = dict()
legch["ch0"] = "N_{b-tag}#geq1"
legch["ch1"] = "N_{b-tag}=1"
legch["ch2"] = "N_{b-tag}#geq2"
#
graphm = dict()
meanv = dict()
meane = dict()
#
graphs = dict()
sigmav = dict()
sigmae = dict()
#
graphf = dict()
mcfracv = dict()
mcfrace = dict()
#
graphaR = dict()
alphaRv = dict()
alphaRe = dict()
#
graphnR = dict()
nRv = dict()
nRe = dict()
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
    graphm[m] = dict()
    meanv[m] = dict()
    meane[m] = dict()
    #
    graphs[m] = dict()
    sigmav[m] = dict()
    sigmae[m] = dict()
    #
    graphf[m] = dict()
    mcfracv[m] = dict()
    mcfrace[m] = dict()
    #
    graphaR[m] = dict()
    alphaRv[m] = dict()
    alphaRe[m] = dict()
    #
    graphnR[m] = dict()
    nRv[m] = dict()
    nRe[m] = dict()
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
        graphm[m][b] = ROOT.TGraphErrors()
        meanv[m][b] = numpy.array([],dtype=numpy.double)
        meane[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphs[m][b] = ROOT.TGraphErrors()
        sigmav[m][b] = numpy.array([],dtype=numpy.double)
        sigmae[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphf[m][b] = ROOT.TGraphErrors()
        mcfracv[m][b] = numpy.array([],dtype=numpy.double)
        mcfrace[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphaR[m][b] = ROOT.TGraphErrors()
        alphaRv[m][b] = numpy.array([],dtype=numpy.double)
        alphaRe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphnR[m][b] = ROOT.TGraphErrors()
        nRv[m][b] = numpy.array([],dtype=numpy.double)
        nRe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphaL[m][b] = ROOT.TGraphErrors()
        alphaLv[m][b] = numpy.array([],dtype=numpy.double)
        alphaLe[m][b] = numpy.array([],dtype=numpy.double)
        #
        graphnL[m][b] = ROOT.TGraphErrors()
        nLv[m][b] = numpy.array([],dtype=numpy.double)
        nLe[m][b] = numpy.array([],dtype=numpy.double)

masses = [200.0, 250.0, 400.0, 550.0, 700.0, 850.0, 1000.0, 1250.0, 1500.0, 2000.0]
massarray = numpy.array(masses, dtype=numpy.double)
zeroarray = numpy.zeros(len(massarray), dtype=numpy.double)
meanm = numpy.zeros(len(massarray), dtype=numpy.double)
meanme = numpy.zeros(len(massarray), dtype=numpy.double)
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
mcfracm = numpy.zeros(len(massarray), dtype=numpy.double)
mcfracme = numpy.zeros(len(massarray), dtype=numpy.double)

for m in models:
    for b in nbbins:
        for mm in masses:
            fname = "%s/signalRooDataSet_fitResult_dcbfastg_%s_M%.0f_%s.root"%(indir,m,mm,b)
            fin = ROOT.TFile(fname)
            tfr = fin.Get("fitResult")
            tm = tfr.floatParsFinal().find("mean")
            ts = tfr.floatParsFinal().find("sigma")
            tf = tfr.floatParsFinal().find("mcfrac")
            taR = tfr.floatParsFinal().find("alphaR")
            tnR = tfr.floatParsFinal().find("nR")
            taL = tfr.floatParsFinal().find("alphaL")
            tnL = tfr.floatParsFinal().find("nL")
            meanv[m][b] = numpy.append(meanv[m][b], tm.getValV())
            meane[m][b] = numpy.append(meane[m][b], max(0.001*tm.getValV(),tm.getError()))
            sigmav[m][b] = numpy.append(sigmav[m][b], ts.getValV())
            sigmae[m][b] = numpy.append(sigmae[m][b], max(0.001*ts.getValV(),ts.getError()))
            mcfracv[m][b] = numpy.append(mcfracv[m][b], tf.getValV())
            mcfrace[m][b] = numpy.append(mcfrace[m][b], max(0.05*tf.getValV(),tf.getError()))
            alphaRv[m][b] = numpy.append(alphaRv[m][b], taR.getValV())
            alphaRe[m][b] = numpy.append(alphaRe[m][b], max(0.05*taR.getValV(),taR.getError()))
            nRv[m][b] = numpy.append(nRv[m][b], tnR.getValV())
            nRe[m][b] = numpy.append(nRe[m][b], max(0.05* tnR.getValV(),tnR.getError()))
            alphaLv[m][b] = numpy.append(alphaLv[m][b], taL.getValV())
            alphaLe[m][b] = numpy.append(alphaLe[m][b], max(0.05*taL.getValV(),taL.getError()))
            nLv[m][b] = numpy.append(nLv[m][b], tnL.getValV())
            nLe[m][b] = numpy.append(nLe[m][b], max(0.05*tnL.getValV(),tnL.getError()))
        graphm[m][b] = ROOT.TGraphErrors(len(massarray), massarray, meanv[m][b], zeroarray, meane[m][b])
        graphm[m][b].SetMarkerColor(colors[m])
        graphm[m][b].SetLineColor(colors[m])
        graphm[m][b].SetMarkerStyle(markers[b])
        #
        graphs[m][b] = ROOT.TGraphErrors(len(massarray), massarray, sigmav[m][b], zeroarray, sigmae[m][b])
        graphs[m][b].SetMarkerColor(colors[m])
        graphs[m][b].SetLineColor(colors[m])
        graphs[m][b].SetMarkerStyle(markers[b])
        #
        graphf[m][b] = ROOT.TGraphErrors(len(massarray), massarray, mcfracv[m][b], zeroarray, mcfrace[m][b])
        graphf[m][b].SetMarkerColor(colors[m])
        graphf[m][b].SetLineColor(colors[m])
        graphf[m][b].SetMarkerStyle(markers[b])
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
    meanm = meanm + meanv[m]["ch1"]/((meane[m]["ch1"])*(meane[m]["ch1"]))
    meanme = meanme + 1.0/((meane[m]["ch1"])*(meane[m]["ch1"]))
    meanm = meanm + meanv[m]["ch2"]/((meane[m]["ch2"])*(meane[m]["ch2"]))
    meanme = meanme + 1.0/((meane[m]["ch2"])*(meane[m]["ch2"]))
    sigmam = sigmam + sigmav[m]["ch1"]/((sigmae[m]["ch1"])*(sigmae[m]["ch1"]))
    sigmame = sigmame + 1.0/((sigmae[m]["ch1"])*(sigmae[m]["ch1"]))
    sigmam = sigmam + sigmav[m]["ch2"]/((sigmae[m]["ch2"])*(sigmae[m]["ch2"]))
    sigmame = sigmame + 1.0/((sigmae[m]["ch2"])*(sigmae[m]["ch2"]))
    nRm = nRm + nRv[m]["ch1"]/((nRe[m]["ch1"])*(nRe[m]["ch1"]))
    nRme = nRme + 1.0/((nRe[m]["ch1"])*(nRe[m]["ch1"]))
    nRm = nRm + nRv[m]["ch2"]/((nRe[m]["ch2"])*(nRe[m]["ch2"]))
    nRme = nRme + 1.0/((nRe[m]["ch2"])*(nRe[m]["ch2"]))
    nLm = nLm + nLv[m]["ch1"]/((nLe[m]["ch1"])*(nLe[m]["ch1"]))
    nLme = nLme + 1.0/((nLe[m]["ch1"])*(nLe[m]["ch1"]))
    nLm = nLm + nLv[m]["ch2"]/((nLe[m]["ch2"])*(nLe[m]["ch2"]))
    nLme = nLme + 1.0/((nLe[m]["ch2"])*(nLe[m]["ch2"]))
    alphaRm = alphaRm + alphaRv[m]["ch1"]/((alphaRe[m]["ch1"])*(alphaRe[m]["ch1"]))
    alphaRme = alphaRme + 1.0/((alphaRe[m]["ch1"])*(alphaRe[m]["ch1"]))
    alphaRm = alphaRm + alphaRv[m]["ch2"]/((alphaRe[m]["ch2"])*(alphaRe[m]["ch2"]))
    alphaRme = alphaRme + 1.0/((alphaRe[m]["ch2"])*(alphaRe[m]["ch2"]))
    alphaLm = alphaLm + alphaLv[m]["ch1"]/((alphaLe[m]["ch1"])*(alphaLe[m]["ch1"]))
    alphaLme = alphaLme + 1.0/((alphaLe[m]["ch1"])*(alphaLe[m]["ch1"]))
    alphaLm = alphaLm + alphaLv[m]["ch2"]/((alphaLe[m]["ch2"])*(alphaLe[m]["ch2"]))
    alphaLme = alphaLme + 1.0/((alphaLe[m]["ch2"])*(alphaLe[m]["ch2"]))
    mcfracm = mcfracm + mcfracv[m]["ch1"]/((mcfrace[m]["ch1"])*(mcfrace[m]["ch1"]))
    mcfracme = mcfracme + 1.0/((mcfrace[m]["ch1"])*(mcfrace[m]["ch1"]))
    mcfracm = mcfracm + mcfracv[m]["ch2"]/((mcfrace[m]["ch2"])*(mcfrace[m]["ch2"]))
    mcfracme = mcfracme + 1.0/((mcfrace[m]["ch2"])*(mcfrace[m]["ch2"]))

meanm = meanm/meanme
meanme = numpy.sqrt(1.0/meanme)
graphmm = ROOT.TGraph(len(massarray), massarray, meanm)
sigmam = sigmam/sigmame
sigmame = numpy.sqrt(1.0/sigmame)
graphsm = ROOT.TGraph(len(massarray), massarray, sigmam)
nRm = nRm/nRme
nRme = numpy.sqrt(1.0/nRme)
graphnRm = ROOT.TGraphErrors(len(massarray), massarray, nRm)
nLm = nLm/nLme
nLme = numpy.sqrt(1.0/nLme)
graphnLm = ROOT.TGraphErrors(len(massarray), massarray, nLm)
alphaRm = alphaRm/alphaRme
alphaRme = numpy.sqrt(1.0/alphaRme)
graphaRm = ROOT.TGraph(len(massarray), massarray, alphaRm)
alphaLm = alphaLm/alphaLme
alphaLme = numpy.sqrt(1.0/alphaLme)
graphaLm = ROOT.TGraph(len(massarray), massarray, alphaLm)
mcfracm = mcfracm/mcfracme
mcfracme = numpy.sqrt(1.0/mcfracme)
graphfm = ROOT.TGraph(len(massarray), massarray, mcfracm)

fmean = ROOT.TF1("fmean","[0]*x",100,2500)
graphmm.Fit(fmean,"L","",175.0,2500.0)
splinem = ROOT.TSpline3("splinem",graphmm)
splinem.SetName("splinem")
a = fmean.GetParameter(0)
#b = fmean.GetParameter(1)
fmean.SetLineColor(1)
fmean.SetLineWidth(2)
fmean.SetLineStyle(2)
latex = ROOT.TLatex()
textmean = "<m_{#mu#mu}> #approx a Mass"
textamean = "a = %.2e"%a
#textbmean = "b = %.2e"%b

fsigma = ROOT.TF1("fsigma","[0]*x*x+[1]*x",100,2500)
graphsm.Fit(fsigma,"L","",175.0,2500.0)
splines = ROOT.TSpline3("splines",graphsm)
splines.SetName("splines")
a = fsigma.GetParameter(0)
b = fsigma.GetParameter(1)
fsigma.SetLineColor(1)
fsigma.SetLineWidth(2)
fsigma.SetLineStyle(2)
latex = ROOT.TLatex()
textsigma = "#sigma #approx a Mass^{2} + b Mass"
textasigma = "a = %.2e"%a
textbsigma = "b = %.2e"%b

fnR = ROOT.TF1("fnL","[0]*x*x+[1]*x+[2]",100,2500)
graphnRm.Fit(fnR,"L","",175.0,2500.0)
splinenR = ROOT.TSpline3("splinenR",graphnRm)
splinenR.SetName("splinenR")
fnR.SetLineColor(1)
fnR.SetLineWidth(2)
fnR.SetLineStyle(2)
textnR = "n_{R} #approx a Mass^{2} + b Mass + c"
anR = fnR.GetParameter(0)
bnR = fnR.GetParameter(1)
cnR = fnR.GetParameter(2)
textanR = "a = %.2e"%anR
textbnR = "b = %.2e"%bnR
textcnR = "c = %.2e"%cnR

fnL = ROOT.TF1("fnL","[0]*x*x+[1]*x+[2]",100,2500)
graphnLm.Fit(fnL,"L","",175.0,2500.0)
splinenL = ROOT.TSpline3("splinenL",graphnLm)
splinenL.SetName("splinenL")
fnL.SetLineColor(1)
fnL.SetLineWidth(2)
fnL.SetLineStyle(2)
textnL = "n_{L} #approx a Mass^{2} + b Mass + c"
anL = fnL.GetParameter(0)
bnL = fnL.GetParameter(1)
cnL = fnL.GetParameter(2)
textanL = "a = %.2e"%anL
textbnL = "b = %.2e"%bnL
textcnL = "c = %.2e"%cnL

faR = ROOT.TF1("faR","[0]*x+[1]",100,2500)
graphaRm.Fit(faR,"L","",175.0,2500.0)
splineaR = ROOT.TSpline3("splineaR",graphaRm)
splineaR.SetName("splineaR")
faR.SetLineColor(1)
faR.SetLineWidth(2)
faR.SetLineStyle(2)
textaR = "#alpha_{R} #approx a Mass + b"
aaR = faR.GetParameter(0)
baR = faR.GetParameter(1)
textaaR = "a = %.2e"%aaR
textbaR = "b = %.2e"%baR

faL = ROOT.TF1("faL","[0]*x+[1]",100,2500)
graphaLm.Fit(faL,"L","",175.0,2500.0)
splineaL = ROOT.TSpline3("splineaL",graphaLm)
splineaL.SetName("splineaL")
faL.SetLineColor(1)
faL.SetLineWidth(2)
faL.SetLineStyle(2)
textaL = "#alpha_{L} #approx a Mass + b"
aaL = faL.GetParameter(0)
baL = faL.GetParameter(1)
textaaL = "a = %.2e"%aaL
textbaL = "b = %.2e"%baL

ff = ROOT.TF1("ff","[0]*x*x+[1]*x+[2]",100,2500)
graphfm.Fit(ff,"L","",175.0,2500.0)
splinef = ROOT.TSpline3("splinef",graphfm)
splinef.SetName("splinef")
ff.SetLineColor(1)
ff.SetLineWidth(2)
ff.SetLineStyle(2)
textf = "f #approx a Mass^{2} + b Mass + c"
af = ff.GetParameter(0)
bf = ff.GetParameter(1)
cf = ff.GetParameter(2)
textaf = "a = %.2e"%af
textbf = "b = %.2e"%bf
textcf = "c = %.2e"%cf

legnbtag = dict()
legmodel = dict()
for m in models:
    legnbtag[m] = ROOT.TLegend(0.15, 0.65, 0.35, 0.85)
    legnbtag[m].SetLineColor(0)
    legnbtag[m].SetFillColor(0)
    legnbtag[m].SetHeader(legmod[m],"L")
    for b in nbbins:
        if "ch0" in b: continue
        legnbtag[m].AddEntry(graphs[m][b], legch[b], "P")
for b in nbbins:
    legmodel[b] = ROOT.TLegend(0.15, 0.65, 0.35, 0.89)
    legmodel[b].SetLineColor(0)
    legmodel[b].SetFillColor(0)
    legmodel[b].SetHeader(legch[b],"L")
    for m in models:
        legmodel[b].AddEntry(graphs[m][b], legmod[m], "P")

ROOT.gStyle.SetOptStat(0)

can = ROOT.TCanvas("can","",600,600)
can.cd()

haxis = ROOT.TH1F("haxis","",1,100,2500)
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("<m_{#mu#mu}> [GeV]")
haxis.GetYaxis().SetRangeUser(100, 2500.0)
haxis.GetYaxis().SetLabelSize(0.025)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphm[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphm[m][b].Draw("PE,same")
    legnbtag[m].Draw("same")
    fmean.Draw("same")
    splinem.Draw("same")
    latex.DrawLatexNDC(0.50, 0.15, textmean)
    latex.DrawLatexNDC(0.60, 0.25, textamean)
    #latex.DrawLatexNDC(0.60, 0.25, textbmean)
    can.SaveAs("%s/mean_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphm[m][b].Draw("PE,same")
    legmodel[b].Draw("same")
    fmean.Draw("same")
    splinem.Draw("same")
    latex.DrawLatexNDC(0.50, 0.15, textmean)
    latex.DrawLatexNDC(0.60, 0.25, textamean)
    #latex.DrawLatexNDC(0.60, 0.25, textbmean)
    can.SaveAs("%s/mean_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("#sigma [GeV]")
haxis.GetYaxis().SetRangeUser(0.0, 100.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphs[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphs[m][b].Draw("PE,same")
    legnbtag[m].Draw("same")
    fsigma.Draw("same")
    splines.Draw("same")
    latex.DrawLatexNDC(0.40, 0.15, textsigma)
    latex.DrawLatexNDC(0.60, 0.30, textasigma)
    latex.DrawLatexNDC(0.60, 0.25, textbsigma)
    can.SaveAs("%s/sigma_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphs[m][b].Draw("PE,same")
    legmodel[b].Draw("same")
    fsigma.Draw("same")
    splines.Draw("same")
    latex.DrawLatexNDC(0.40, 0.15, textsigma)
    latex.DrawLatexNDC(0.60, 0.30, textasigma)
    latex.DrawLatexNDC(0.60, 0.25, textbsigma)
    can.SaveAs("%s/sigma_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("fraction(Gauss)")
haxis.GetYaxis().SetRangeUser(0.0, 1.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphf[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphf[m][b].Draw("PE,same")
    ff.Draw("same")
    splinef.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.35, 0.85, textf)
    latex.DrawLatexNDC(0.60, 0.80, textaf)
    latex.DrawLatexNDC(0.60, 0.75, textbf)
    latex.DrawLatexNDC(0.60, 0.70, textcf)
    can.SaveAs("%s/mcfrac_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphf[m][b].Draw("PE,same")
    ff.Draw("same")
    splinef.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.35, 0.85, textf)
    latex.DrawLatexNDC(0.60, 0.80, textaf)
    latex.DrawLatexNDC(0.60, 0.75, textbf)
    latex.DrawLatexNDC(0.60, 0.70, textcf)
    can.SaveAs("%s/mcfrac_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("#alpha_{R}")
haxis.GetYaxis().SetRangeUser(0.0, 2.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphaR[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphaR[m][b].Draw("PE,same")
    faR.Draw("same")
    splineaR.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textaR)
    latex.DrawLatexNDC(0.60, 0.25, textaaR)
    latex.DrawLatexNDC(0.60, 0.20, textbaR)
    can.SaveAs("%s/alphaR_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphaR[m][b].Draw("PE,same")
    faR.Draw("same")
    splineaR.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.15, textaR)
    latex.DrawLatexNDC(0.60, 0.25, textaaR)
    latex.DrawLatexNDC(0.60, 0.20, textbaR)
    can.SaveAs("%s/alphaR_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("#alpha_{L}")
haxis.GetYaxis().SetRangeUser(0.0, 2.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphaL[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphaL[m][b].Draw("PE,same")
    faL.Draw("same")
    splineaL.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textaL)
    latex.DrawLatexNDC(0.60, 0.80, textaaL)
    latex.DrawLatexNDC(0.60, 0.75, textbaL)
    can.SaveAs("%s/alphaL_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphaL[m][b].Draw("PE,same")
    faL.Draw("same")
    splineaL.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.55, 0.85, textaL)
    latex.DrawLatexNDC(0.60, 0.80, textaaL)
    latex.DrawLatexNDC(0.60, 0.75, textbaL)
    can.SaveAs("%s/alphaL_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("n_{R}")
haxis.GetYaxis().SetRangeUser(0.0, 15.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphnR[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphnR[m][b].Draw("PE,same")
    fnR.Draw("same")
    splinenR.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.35, 0.85, textnR)
    latex.DrawLatexNDC(0.60, 0.80, textanR)
    latex.DrawLatexNDC(0.60, 0.75, textbnR)
    latex.DrawLatexNDC(0.60, 0.70, textcnR)
    can.SaveAs("%s/nR_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphnR[m][b].Draw("PE,same")
    fnR.Draw("same")
    splinenR.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.35, 0.85, textnR)
    latex.DrawLatexNDC(0.60, 0.80, textanR)
    latex.DrawLatexNDC(0.60, 0.75, textbnR)
    latex.DrawLatexNDC(0.60, 0.70, textcnR)
    can.SaveAs("%s/nR_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

###

haxis.GetYaxis().SetTitle("n_{L}")
haxis.GetYaxis().SetRangeUser(0.0, 15.0)
for m in models:
    haxis.Draw()
    for b in nbbins:
        graphnL[m][b].RemovePoint(0)
        if "ch0" in b: continue
        graphnL[m][b].Draw("PE,same")
    fnL.Draw("same")
    splinenL.Draw("same")
    legnbtag[m].Draw("same")
    latex.DrawLatexNDC(0.35, 0.85, textnL)
    latex.DrawLatexNDC(0.60, 0.80, textanL)
    latex.DrawLatexNDC(0.60, 0.75, textbnL)
    latex.DrawLatexNDC(0.60, 0.70, textcnL)
    can.SaveAs("%s/nL_vs_mass_nBTag_%s.png"%(indir,m))
    can.Update()
    can.Clear()
for b in nbbins:
    haxis.Draw()
    for m in models:
        graphnL[m][b].Draw("PE,same")
    fnL.Draw("same")
    splinenL.Draw("same")
    legmodel[b].Draw("same")
    latex.DrawLatexNDC(0.35, 0.85, textnL)
    latex.DrawLatexNDC(0.60, 0.80, textanL)
    latex.DrawLatexNDC(0.60, 0.75, textbnL)
    latex.DrawLatexNDC(0.60, 0.70, textcnL)
    can.SaveAs("%s/nL_vs_mass_model_%s.png"%(indir,b))
    can.Update()
    can.Clear()

fout = ROOT.TFile("%s/fitParameters.root"%indir,"RECREATE")
fout.cd()
fmean.Write()
splinem.Write()
fsigma.Write()
splines.Write()
fnR.Write()
splinenR.Write()
fnL.Write()
splinenL.Write()
faR.Write()
splineaR.Write()
faL.Write()
splineaL.Write()
ff.Write()
splinef.Write()
fout.Write()
fout.Close()
