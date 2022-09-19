import ROOT
import numpy
import copy
import os,sys
from datetime import date
import plotUtils

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

doRatio = True
doPull = False
doDiff = False
useFixedRatioRange = True
if doPull or doDiff:
    useFixedRatioRange = False

wsname = "wfit"
thisDir = os.environ.get("PWD")
inDirF  = "%s/cpp/fitResults_fullwindow/"%thisDir
inDir   = "%s/datacards_all_Sep-13-2022/"%thisDir

useCategorizedSignal = False
useCategorizedBackground = True

nSigma = 3
printFit = True

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
sigMasses.append("250")
sigMasses.append("400")
sigMasses.append("550")
sigMasses.append("700")
sigMasses.append("850")
sigMasses.append("1000")
sigMasses.append("1250")
sigMasses.append("1500")
sigMasses.append("2000")

def drawLabels(s="Y_{3}",m="250",maxY=1.0,year="all",lumi=59.83+41.48+19.5+16.8):
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

    latexModel = ROOT. TLatex()
    latexModel.SetTextFont(42)
    latexModel.SetTextSize(0.05)
    latexModel.SetNDC(True)

    yearenergy=""
    if year!="all" or lumi<100.0:
        if year!="all":
            yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
        else:
            yearenergy="%.1f fb^{-1} (2016-2018, 13 TeV)"%(lumi)
    else:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    cmsExtra="Simulation"

    model = "%s, M=%s GeV"%(s,m)

    # Draw CMS headers
    expoffset=0
    if maxY<0.1:
        expoffset=0.03
    if doRatio:
        latex.DrawLatex(0.95, 0.93+expoffset, yearenergy);
        latexCMS.DrawLatex(0.11,0.93+expoffset,"CMS");
        latexCMSExtra.DrawLatex(0.19,0.93+expoffset, cmsExtra);
    else:
        latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
        latexCMS.DrawLatex(0.11,0.91+expoffset,"CMS");
        latexCMSExtra.DrawLatex(0.20,0.91+expoffset, cmsExtra);
    latexModel.DrawLatex(0.15, 0.83, model)

def printFitParams(mean,sigma,nL,aL,nR,aR,fG,meanUnc,sigmaUnc):
    latexFit = ROOT. TLatex()
    latexFit.SetTextFont(42)
    latexFit.SetTextSize(0.04)
    latexFit.SetNDC(True)
    latexFit.DrawLatex(0.15, 0.75, "#LT m_{#mu#mu} #GT = %.2f#pm%.2f GeV"%(mean,meanUnc))
    latexFit.DrawLatex(0.15, 0.70, "#sigma_{mass} = %.2f#pm%.2f GeV"%(sigma,sigmaUnc))
    latexFit.DrawLatex(0.15, 0.65, "n_{L} = %.2f"%nL)
    latexFit.DrawLatex(0.15, 0.60, "#alpha_{L} = %.2f"%aL)
    latexFit.DrawLatex(0.15, 0.55, "n_{R} = %.2f"%nR)
    latexFit.DrawLatex(0.15, 0.50, "#alpha_{R} = %.2f"%aR)
    latexFit.DrawLatex(0.15, 0.45, "f_{Gauss} = %.2f"%fG)

def getLegend(ch,gd,hs,hsm,hss):
    legend = ROOT.TLegend(0.7,0.6,0.91,0.91)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.AddEntry(gd,"MC","EP")
    legend.AddEntry(hs,"Fit (nominal)","L")
    legend.AddEntry(hsm,"Fit, #pm#delta(#LT m_{#mu#mu} #GT)","L")
    legend.AddEntry(hss,"Fit, #pm#delta(#sigma_{mass})","L")
            
    if ch==0:
        legend.SetHeader("N_{b-tag}#geq1")
    elif ch==1:
        legend.SetHeader("N_{b-tag}=1")
    elif ch==2:
        legend.SetHeader("N_{b-tag}#geq2")

    return legend

for y in years:
    for s in sigModels:
        for m in sigMasses:
            for d in dNames:
                fitPsNom = ROOT.TFile("utils/signalFitParameters_default.root")
                sigmaNom = (fitPsNom.Get("splines")).Eval(float(m))
                fitPsUnc = ROOT.TFile("utils/signalFitParameters_muonResolutionUnc.root")
                sigmaUnc = (fitPsUnc.Get("splines")).Eval(float(m))
                sigmaUnc = abs(sigmaUnc-sigmaNom)

                minm =  200.0
                maxm = 2000.0
                minsyst = 0.000
                maxsyst = 0.002
                meanUnc = max(0.0,(maxsyst-minsyst)/(maxm-minm)*float(m) + minsyst - minm/(maxm-minm)*(maxsyst-minsyst))*float(m)

                finameF = "%s/%s_%s_M%s_%s_workspace.root"%(inDirF,d,s,m,y)
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
                fF = ROOT.TFile(finameF)                
                # Retrieve workspace from file
                w = f.Get(wsname)
                wF = fF.Get(wsname)
                # Retrive x, min and max
                x = w.var("mfit")
                # Retrieve fit parameters
                mean  = w.var("mean").getValV()
                sigma = w.var("sigma").getValV()
                nL = w.var("nL").getValV()
                aL = w.var("alphaL").getValV()
                nR = w.var("nR").getValV()
                aR = w.var("alphaR").getValV()
                fG = w.var("mcfrac").getValV()
                #emean  = w.var("mean").getError()
                #esigma = w.var("sigma").getError()
                #enL = w.var("nL").getError()
                #eaL = w.var("alphaL").getError()
                #enR = w.var("nL").getError()
                #eaR = w.var("alphaR").getError()
                #efG = w.var("mcfrac").getError()
                # Set range and binning
                minx = max(175.0,0.5*float(m))
                maxx = 1.5*float(m)
                if nSigma>0:
                    minx = max(175.0,float(m)-nSigma*sigma)
                    maxx = float(m)+nSigma*sigma
                nBins = int((maxx-minx)/(0.01*float(m)))
                if nSigma>0:
                    nBins = int(5*nSigma)
                # Retrieve signal normalization
                nSig = w.var("signalNorm%s"%catExtS).getValV()                
                # Retrieve signal dataset and PDF, and fill histograms
                d = wF.data("signalRooDataSet%s"%catExtS)
                hd = x.createHistogram("hd",ROOT.RooFit.Binning(nBins,minx,maxx))
                d.fillHistogram(hd,ROOT.RooArgList(x))
                sp = w.pdf("signal%s"%catExtS)
                hs = sp.createHistogram("hs",x,ROOT.RooFit.Binning(100*nBins,minx,maxx))
                hs.SetLineColor(6)
                hs.Scale(nSig)
                for b in range(1,hs.GetNbinsX()+1):
                    hs.SetBinError(b,0)
                hsr = hs.Clone("hsr")
                hsr.Rebin(100)
                hs.Scale(100.0)

                w.var("mean").setVal(mean+meanUnc)
                hsmu = sp.createHistogram("hsmu",x,ROOT.RooFit.Binning(100*nBins,minx,maxx))
                hsmu.SetLineColor(ROOT.kViolet)
                hsmu.Scale(nSig)
                for b in range(1,hsmu.GetNbinsX()+1):
                    hsmu.SetBinError(b,0)
                hsmur = hsmu.Clone("hsmur")
                hsmur.Rebin(100)
                hsmu.Scale(100.0)

                w.var("mean").setVal(mean-meanUnc)
                hsmd = sp.createHistogram("hsmd",x,ROOT.RooFit.Binning(100*nBins,minx,maxx))
                hsmd.SetLineColor(ROOT.kViolet)
                hsmd.Scale(nSig)
                for b in range(1,hsmd.GetNbinsX()+1):
                    hsmd.SetBinError(b,0)
                hsmdr = hsmd.Clone("hsmdr")
                hsmdr.Rebin(100)
                hsmd.Scale(100.0)

                w.var("mean").setVal(mean)
                w.var("sigma").setVal(sigma+sigmaUnc)
                hssu = sp.createHistogram("hssu",x,ROOT.RooFit.Binning(100*nBins,minx,maxx))
                hssu.SetLineColor(ROOT.kBlue)
                hssu.Scale(nSig)
                for b in range(1,hssu.GetNbinsX()+1):
                    hssu.SetBinError(b,0)
                hssur = hssu.Clone("hssur")
                hssur.Rebin(100)
                hssu.Scale(100.0)

                w.var("sigma").setVal(sigma-sigmaUnc)
                hssd = sp.createHistogram("hssd",x,ROOT.RooFit.Binning(100*nBins,minx,maxx))
                hssd.SetLineColor(ROOT.kBlue)
                hssd.Scale(nSig)
                for b in range(1,hssd.GetNbinsX()+1):
                    hssd.SetBinError(b,0)
                hssdr = hssd.Clone("hssdr")
                hssdr.Rebin(100)
                hssd.Scale(100.0)

                w.var("sigma").setVal(sigma)

                chi2=0.0
                ndof=0
                weight = d.sumEntries()/d.numEntries()
                for b in range(1,hd.GetNbinsX()+1):
                    if not hd.GetXaxis().GetBinLowEdge(b)<float(m)-5*sigma and not hd.GetXaxis().GetBinLowEdge(b)>float(m)+5*sigma:
                        ndof = ndof+1
                        chi2 = chi2+(hd.GetBinContent(b)-hsr.GetBinContent(b))*(hd.GetBinContent(b)-hsr.GetBinContent(b))/(hsr.GetBinContent(b)) 
                ndof = ndof-7
                pvalue = ROOT.Math.chisquared_cdf_c(numpy.double(chi2),numpy.double(ndof))

                ROOT.gStyle.SetOptStat(0)
                can = ROOT.TCanvas("can","",600,600)
                can.cd()

                h_axis = ROOT.TH1D("h_axis","", hd.GetNbinsX(), hd.GetXaxis().GetBinLowEdge(1), hd.GetXaxis().GetBinUpEdge(hd.GetNbinsX()))
                h_axis.GetXaxis().SetTitle("m_{#mu#mu} [GeV]")
                h_axis.GetYaxis().SetTitle("Events")
                h_axis.GetYaxis().SetMaxDigits(3)
                hd.SetMarkerStyle(20)
                hd.SetMarkerSize(1.2)
                hd.SetLineWidth(1)

                h_axis_ratio = ROOT.TH1D("h_axis_ratio","", hd.GetNbinsX(), hd.GetXaxis().GetBinLowEdge(1), hd.GetXaxis().GetBinUpEdge(hd.GetNbinsX()))
                g_ratio = hd.Clone("g_ratio")
                g_ratio_mu = hs.Clone("g_ratio_mu")
                g_ratio_md = hs.Clone("g_ratio_md")
                g_ratio_su = hs.Clone("g_ratio_su")
                g_ratio_sd = hs.Clone("g_ratio_sd")
                if not doPull and not doDiff:
                    g_ratio.Divide(hsr)
                    g_ratio_mu.Divide(hsmu)
                    g_ratio_md.Divide(hsmd)
                    g_ratio_su.Divide(hssu)
                    g_ratio_sd.Divide(hssd)
                elif not doDiff:
                    for b in range(1,hd.GetNbinsX()+1):
                        g_ratio.SetBinContent(b,(hd.GetBinContent(b)-hsr.GetBinContent(b))/hd.GetBinError(b))
                else:
                    g_ratio.Add(hsr,-1.0)
                    g_ratio.Divide(hd)
                g_ratio.SetMarkerStyle(20)
                g_ratio.SetMarkerSize(1.2)
                g_ratio.SetLineColor(1)
                g_ratio.SetLineWidth(1)
                g_ratio_mu.SetLineColor(ROOT.kViolet)
                g_ratio_md.SetLineColor(ROOT.kViolet)
                g_ratio_su.SetLineColor(ROOT.kBlue)
                g_ratio_sd.SetLineColor(ROOT.kBlue)

                pads = []

                minR=0.25
                maxR=-0.25
                tmax=maxR
                for b in range(1,hd.GetNbinsX()+1):
                    tmax = g_ratio.GetBinContent(b)
                    if tmax>maxR:
                        maxR=tmax*1.05
                    if tmax<minR:
                        minR=tmax
                        if minR<0:
                            minR=minR*1.05
                        else:
                            minR=minR*0.95
                if maxR>5.0 and not (doPull or doDiff):
                    minR=0.1
                
                if useFixedRatioRange:
                    minR=0.25
                    maxR=1.75

                if doRatio:    
                    h_axis_ratio.GetYaxis().SetRangeUser(minR,maxR)
                    h_axis_ratio.SetMinimum(minR)
                    h_axis_ratio.SetMaximum(maxR)
                    if not (doPull or doDiff):
                        #h_axis_ratio.SetTitle(";;MC / fit")
                        h_axis_ratio.SetTitle(";;X / fit (nom.)")
                    elif not doDiff:
                        h_axis_ratio.SetTitle(";;(MC - fit) / #sigma_{MC}")
                    else:
                        h_axis_ratio.SetTitle(";;(MC - fit) / MC")
                    h_axis_ratio.GetYaxis().SetTitleSize(0.16)
                    h_axis_ratio.GetYaxis().SetTitleOffset(0.25)
                    h_axis_ratio.GetYaxis().SetLabelSize(0.12)
                    h_axis_ratio.GetYaxis().CenterTitle()
                    h_axis_ratio.GetYaxis().SetTickLength(0.02)
                    h_axis_ratio.GetXaxis().SetLabelSize(0)
                    h_axis_ratio.GetXaxis().SetTitle("")
                    h_axis_ratio.GetXaxis().SetTickSize(0.06)

                    line = ROOT.TLine(minx, 1.0, maxx, 1.0)
                    
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
                    if maxR>5.0 and not (doPull or doDiff):
                        pads[1].SetLogy()
                    pads[1].SetTickx()
                    h_axis_ratio.Draw("")
                    g_ratio.Draw("SAME,P0")
                    if not doPull and not doDiff:
                        g_ratio_mu.Draw("hist,same")
                        g_ratio_md.Draw("hist,same")
                        g_ratio_su.Draw("hist,same")
                        g_ratio_sd.Draw("hist,same")
                    
                    line.SetLineStyle(2)
                    line.SetLineColor(1)
                    line.SetLineWidth(1)
                    line.Draw("SAME")
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
                for b in range(1,hd.GetNbinsX()+1):
                    tmax = hd.GetBinContent(b)
                    if tmax>maxR:
                        maxR=tmax
                maxR = maxR*1.5
                h_axis.SetMinimum(minR)
                h_axis.SetMaximum(maxR)
                h_axis.GetYaxis().SetRangeUser(minR,maxR)
                h_axis.GetYaxis().SetTitleSize(0.04)
                h_axis.GetXaxis().SetTitleSize(0.04)
                h_axis.GetXaxis().SetTitleOffset(1.25)
                h_axis.GetYaxis().SetLabelSize(0.03)

                h_axis.Draw("")
                hd.Draw("P,same")
                hs.Draw("hist,same")
                hsmu.Draw("hist,same")
                hsmd.Draw("hist,same")
                hssu.Draw("hist,same")
                hssd.Draw("hist,same")

                if s=="Y3":
                    sl = "Y_{3}"
                elif s=="DY3":
                    sl = "DY_{3}"
                elif s=="DYp3":
                    sl = "DY'_{3}"
                elif s=="B3mL2":
                    sl = "B_{3}-L_{2}"
                else:
                    sl = s

                legend = getLegend(binidx,hd,hs,hsmu,hssu)
                drawLabels(sl,m,maxR)
                if printFit:
                    printFitParams(mean,sigma,nL,aL,nR,aR,fG,meanUnc,sigmaUnc)
                legend.Draw("same")
                pads[0].Update()
                pads[0].RedrawAxis()
                
                can.SaveAs("%s/fitSignal_%s_M%s%s.png"%(outDir,s,m,catExtB))

                # Close input file with workspace                
                f.Close()
                fF.Close()
