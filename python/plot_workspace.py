import ROOT
import numpy
import copy
import os,sys
from datetime import date
import plotUtils

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

doRatio = True
doPull = True
useData = True
useSignalMC = True
doPartialUnblinding = False

wsname = "wfit"
thisDir = os.environ.get("PWD")
inDir  = "%s/datacards_all_nomodel_Oct-10-2022/"%thisDir

useCategorizedSignal = False
useCategorizedBackground = True

outDir = ("%s/fitPlots_"%(thisDir))+today
if not os.path.exists(outDir):
    os.makedirs(outDir)

dNames = []
#dNames.append("d_mllinclusive_nBTag1p_MuDetAll")
dNames.append("d_mllinclusive_nBTag1_MuDetAll")
dNames.append("d_mllinclusive_nBTag2p_MuDetAll")

years = []
#years.append("2018")
#years.append("2017")
#years.append("2016APV")
#years.append("2016nonAPV")
###
years.append("allyears")

# Signals
sigModels = []
sigModels.append("Y3")
#sigModels.append("DY3")
#sigModels.append("DYp3")
#sigModels.append("B3mL2")

sigMasses = []
if useSignalMC:
    #sigMasses.append("250")
    sigMasses.append("350")
    sigMasses.append("500")
    sigMasses.append("700")
    #sigMasses.append("850")
    sigMasses.append("1000")
    #sigMasses.append("1250")
    sigMasses.append("1500")
    sigMasses.append("2000")
else:
    mF = 350.0
    mL = 2000.0
    sigMasses.append("%.0f"%mF)
    tm = mF
    while tm < mL:
      if tm<400.0: tm=tm+5.0
      elif tm<700.0: tm=tm+10.0
      elif tm<1000.0: tm=tm+15.0
      elif tm<1500.0: tm=tm+25.0
      else: tm=tm+50.0
      sigMasses.append("%.0f"%tm)


def drawLabels(year="all",lumi=59.83+41.48+19.5+16.8,plotData=False):
    # Labels
    latex = ROOT.TLatex()
    latex.SetTextFont(42)
    latex.SetTextAlign(31)
    latex.SetTextSize(0.04)
    latex.SetNDC(True)

    latexCMS = ROOT.TLatex()
    latexCMS.SetTextFont(61)
    latexCMS.SetTextSize(0.04)
    latexCMS.SetNDC(True)

    latexCMSExtra = ROOT.TLatex()
    latexCMSExtra.SetTextFont(52)
    latexCMSExtra.SetTextSize(0.04)
    latexCMSExtra.SetNDC(True)

    legoffset = 0.0
    latexSel = ROOT. TLatex()
    latexSel.SetTextAlign(11)
    latexSel.SetTextFont(42)
    latexSel.SetTextSize(0.02-0.1*legoffset)
    latexSel.SetNDC(True)

    yearenergy=""
    if year!="all" or lumi<100.0:
        if year!="all":
            yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
        else:
            yearenergy="%.1f fb^{-1} (2016-2018, 13 TeV)"%(lumi)
    else:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    if plotData:
        cmsExtra="Preliminary"
    else:
        cmsExtra="Simulation"

    # Draw CMS headers
    expoffset=0
    if doRatio:
        latex.DrawLatex(0.95, 0.93+expoffset, yearenergy);
        latexCMS.DrawLatex(0.11,0.93+expoffset,"CMS");
        latexCMSExtra.DrawLatex(0.19,0.93+expoffset, cmsExtra);
    else:
        latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
        latexCMS.DrawLatex(0.11,0.91+expoffset,"CMS");
        latexCMSExtra.DrawLatex(0.20,0.91+expoffset, cmsExtra);


def getLegend(ch,gd,p,hp,hs,smodel,smass,sigsf=-1.0,plotSignal=True,plotData=True):
    legend = ROOT.TLegend(0.7,0.6,0.91,0.91)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    if plotData:
        legend.AddEntry(gd,"Data","EP")
    else:
        legend.AddEntry(gd,"Data (toy)","EP")
    for pn,pp in enumerate(p):
        legend.AddEntry(hp[pn],pp,"L")
    if plotSignal:
        if smodel=="Y3":
            smodel="Y_{3}"
        elif smodel=="DY3":
            smodel="DY_{3}"
        elif smodel=="DYp3":
            smodel="DY'_{3}"
        elif smodel=="B3mL2":
            smodel="B_{3}-L_{2}"
        if sigsf>0:
            legend.AddEntry(hs,"%s, M=%.0f GeV (x%d)"%(smodel,smass,sigsf), "L")
        else:
            legend.AddEntry(hs,"%s, M=%.0f GeV"%(smodel,smass), "L")
            
    if ch==0:
        legend.SetHeader("N_{b}#geq1")
    elif ch==1:
        legend.SetHeader("N_{b}=1")
    elif ch==2:
        legend.SetHeader("N_{b}#geq2")

    return legend

mean = 0.0
sigma = 0.0
for y in years:
    for s in sigModels:
        for m in sigMasses:
            for d in dNames:
                finame = "%s/%s_%s_M%s_%s_workspace.root"%(inDir,d,s,m,y)
                binidx=-1
                if "nBTag1p" in finame:
                    binidx=0
                elif "nBTag1" in finame:
                    binidx=1
                elif "nBTag2p" in finame:
                    binidx=2
                catExtS = ""
                catExtB = ""
                if useCategorizedSignal:
                    catExtS = "_ch%d"%binidx
                if useCategorizedBackground:
                    catExtB = "_ch%d"%binidx
                # Open input file with workspace
                f = ROOT.TFile(finame)
                # Retrieve workspace from file
                w = f.Get(wsname)
                # Retrive x, min and max
                x = w.var("mfit")
                minx = x.getMin()
                maxx = x.getMax()
                #nBins = int((maxx-minx)/(0.01*float(m)))
                nBins = 5*10;
                # Retrieve signal normalization
                lumi=59.83+41.48+19.5+16.8                
                if doPartialUnblinding:
                    lumi = 0.1*lumi
                nSig = w.var("signalNorm%s"%catExtS).getValV()
                nSig = nSig*lumi
                print(m, binidx, nSig)
                # Retrieve signal mean and std. deviation
                if binidx==0 or useCategorizedSignal:
                    mean = w.var("mean%s"%catExtS).getValV()
                    sigma = w.var("sigma%s"%catExtS).getValV()
                # Retrive BG normalization:
                nBG = w.data("data_obs%s"%catExtB).sumEntries()

                d = w.data("data_obs%s"%catExtB)
                hd = x.createHistogram("hd",ROOT.RooFit.Binning(nBins,minx,maxx))                
                d.fillHistogram(hd,ROOT.RooArgList(x))
                
                bpdf = w.pdf("roomultipdf%s"%catExtB)
                nPDF = w.cat("pdf_index%s"%catExtB).numTypes()
                p  = []
                pn = []
                hp = []
                hpr = []
                numpars = []
                for pp in range(nPDF):
                    p.append(bpdf.getPdf(pp))
                    numpars.append(w.pdf(bpdf.getPdf(pp).GetName()).getVariables().getSize()-1)
                    if "exponential" in p[pp].GetName():
                        pn.append("Exponential")
                        color=2
                    elif "powerlaw" in p[pp].GetName():
                        pn.append("Power-law")
                        color=3
                    else:
                        pn.append("Bernstein<%d>"%(numpars[pp]))
                        color=4
                    hp.append(p[pp].createHistogram("hp%d"%pp,x,ROOT.RooFit.Binning(100*nBins,minx,maxx)))
                    hp[pp].SetLineColor(color)
                    hp[pp].Scale(nBG)
                    hpr.append(hp[pp].Clone("hpr%d"%pp))
                    hpr[pp].Rebin(100)
                    hp[pp].Scale(100.0)

                sp = w.pdf("signal%s"%catExtS)
                hs = sp.createHistogram("hs",x,ROOT.RooFit.Binning(100*nBins,minx,maxx))
                hs.SetLineColor(6)
                hs.Scale(nSig*100.0)

                ROOT.gStyle.SetOptStat(0)
                can = ROOT.TCanvas("can","",600,600)
                can.cd()

                h_axis = ROOT.TH1D("h_axis","", hd.GetNbinsX(), hd.GetXaxis().GetBinLowEdge(1), hd.GetXaxis().GetBinUpEdge(hd.GetNbinsX()))
                h_axis.GetXaxis().SetTitle("m_{#mu#mu} [GeV]")
                h_axis.GetYaxis().SetTitle("Events")
                g_data = ROOT.TGraphAsymmErrors()
                plotUtils.ConvertToPoissonGraph(hd, g_data, drawZeros=True, drawXerr=False)
                g_data.SetMarkerStyle(20)
                g_data.SetMarkerSize(1.2)
                g_data.SetLineWidth(1)
                # draw with zero marker size so error bars drawn all the way to x axis in the case of 0 content
                g_data_clone = g_data.Clone()
                g_data_clone.SetMarkerSize(0.0)

                h_axis_ratio = ROOT.TH2D("h_axis_ratio","", hd.GetNbinsX(), hd.GetXaxis().GetBinLowEdge(1), hd.GetXaxis().GetBinUpEdge(hd.GetNbinsX()), 2000, -100.0, 100.0)
                g_ratio = [] 
                for pp in range(nPDF):
                    g_ratio.append(ROOT.TGraphAsymmErrors())
                    if not doPull:
                        plotUtils.GetPoissonRatioGraph(hpr[pp], hd, g_ratio[pp], drawZeros=False, drawXerr=False, useMCErr=False)
                    else:
                        plotUtils.GetPullGraph(hpr[pp], hd, g_ratio[pp], drawZeros=True, drawXerr=False, useMCErr=False)                        
                    g_ratio[pp].SetMarkerStyle(4)
                    g_ratio[pp].SetMarkerSize(1.2)
                    g_ratio[pp].SetMarkerColor(hpr[pp].GetLineColor())
                    g_ratio[pp].SetLineWidth(1)
                    g_ratio[pp].SetLineColor(hpr[pp].GetLineColor())

                pads = []
                if doRatio==True:
                    if not doPull:
                        minR=0.25
                        maxR=1.75
                        ty = numpy.array([])
                        tmax=maxR
                        for pp in range(nPDF):
                            ty = g_ratio[pp].GetY()
                            if len(ty)>0:
                                tmax = numpy.amax(ty)
                            if tmax>maxR:
                                maxR=tmax*1.05
                        if maxR>5.0:
                            minR=0.1
                    else:
                        minR=-2.0
                        maxR=+2.0
                        ty = numpy.array([])
                        tmax=maxR
                        for pp in range(nPDF):
                            ty = g_ratio[pp].GetY()
                            if len(ty)>0:
                                tmax = numpy.amax(ty)
                                tmin = numpy.amin(ty)
                            if tmax>maxR:
                                maxR=tmax*1.10
                            if tmin<minR:
                                minR=tmin
                                if minR<0.0:
                                    minR = minR*1.10
                                else:
                                    minR = minR*0.90
                        if maxR>5.0 and not doPull:
                            minR=0.1
                    h_axis_ratio.GetYaxis().SetRangeUser(minR,maxR)
                    #h_axis_ratio.SetMinimum(minR)
                    #h_axis_ratio.SetMaximum(maxR)
                    if not doPull:
                        h_axis_ratio.SetTitle(";;Data / fit")
                    else:
                        h_axis_ratio.SetTitle(";;(Data-fit)/#sigma_{data}")
                    h_axis_ratio.GetYaxis().SetTitleSize(0.16)
                    h_axis_ratio.GetYaxis().SetTitleOffset(0.25)
                    h_axis_ratio.GetYaxis().SetLabelSize(0.12)
                    h_axis_ratio.GetYaxis().CenterTitle()
                    h_axis_ratio.GetYaxis().SetTickLength(0.02)
                    h_axis_ratio.GetXaxis().SetLabelSize(0)
                    h_axis_ratio.GetXaxis().SetTitle("")
                    h_axis_ratio.GetXaxis().SetTickSize(0.06)

                    line = ROOT.TLine(minx, 1.0, maxx, 1.0)
                    if doPull:
                        line = ROOT.TLine(minx, 0.0, maxx, 0.0)
                        linep1 = ROOT.TLine(minx, 1.0, maxx, 1.0)
                        linep2 = ROOT.TLine(minx, 2.0, maxx, 2.0)
                        linem1 = ROOT.TLine(minx, -1.0, maxx, -1.0)
                        linem2 = ROOT.TLine(minx, -2.0, maxx, -2.0)

                    pads.append(ROOT.TPad("1","1",0.0,0.18,1.0,1.0))
                    pads.append(ROOT.TPad("2","2",0.0,0.0,1.0,0.19))
                    pads[0].SetTopMargin(0.08)
                    pads[0].SetBottomMargin(0.13)
                    pads[0].SetRightMargin(0.05)
                    pads[0].SetLeftMargin(0.10)
                    pads[1].SetRightMargin(0.05)
                    pads[1].SetLeftMargin(0.10)
                    pads[0].Draw()
                    pads[1].Draw()
                    pads[1].cd()
                    if maxR>5.0 and not doPull:
                        pads[1].SetLogy()
                    pads[1].SetTickx()
                    h_axis_ratio.Draw("")
                    for pp in range(nPDF):
                        g_ratio[pp].Draw("SAME,P0")

                    line.SetLineStyle(2)
                    line.SetLineColor(1)
                    line.SetLineWidth(1)
                    line.Draw("SAME")
                    if doPull:
                        linep1.SetLineStyle(2)
                        linep1.SetLineColor(1)
                        linep1.SetLineWidth(1)
                        linep2.SetLineStyle(2)
                        linep2.SetLineColor(1)
                        linep2.SetLineWidth(1)
                        linem1.SetLineStyle(2)
                        linem1.SetLineColor(1)
                        linem1.SetLineWidth(1)
                        linem2.SetLineStyle(2)
                        linem2.SetLineColor(1)
                        linem2.SetLineWidth(1)
                        if minR<-2.0:
                            linem1.Draw("SAME")
                            linem2.Draw("SAME")
                        elif minR<-1.0:
                            linem1.Draw("SAME")
                        if maxR>2.0:
                            linep1.Draw("SAME")
                            linep2.Draw("SAME")
                        elif maxR>1.0:
                            linep1.Draw("SAME")
                    pads[1].Modified();
                    pads[1].Update();
                else:
                    pads.append(ROOT.TPad("1","1",0,0,1,1))
                    pads[0].Draw()

                pads[0].cd()

                minR=0.0
                maxR=0.0
                ty = numpy.array([])
                tmax=maxR
                ty = g_data.GetY() 
                if len(ty)>0:
                    tmax = numpy.amax(ty)
                    if tmax>maxR:
                        maxR=tmax
                if maxR>1.0:
                    maxR = maxR*1.5
                else:
                    maxR = maxR*2.0
                h_axis.SetMinimum(minR)
                h_axis.SetMaximum(maxR)
                h_axis.GetYaxis().SetRangeUser(minR,maxR)
                h_axis.GetYaxis().SetTitleSize(0.04)
                h_axis.GetXaxis().SetTitleSize(0.04)
                h_axis.GetXaxis().SetTitleOffset(1.25)
                h_axis.GetYaxis().SetLabelSize(0.03)

                h_axis.Draw("")
                g_data.Draw("P,same")
                g_data_clone.Draw("P,same")
                for pp in range(nPDF):
                    hp[pp].Draw("hist,same")
                hs.Draw("hist,same")

                legend = getLegend(binidx,g_data,pn,hp,hs,s,float(m))
                year="all"
                drawLabels(year,lumi,useData)
                legend.Draw("same")
                pads[0].Update()
                pads[0].RedrawAxis()
                
                can.SaveAs("%s/fitBG_M%s%s.png"%(outDir,m,catExtB))
                can.SaveAs("%s/fitBG_M%s%s.pdf"%(outDir,m,catExtB))

                # Close input file with workspace                
                f.Close()
