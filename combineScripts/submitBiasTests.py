import os,sys
import ROOT
import numpy as np
from datetime import date

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

### if date ("MMM-DD-YYYY") is not specified, use today's date
inDate = today
outDate = today
if len(sys.argv)>1:
    inDate=sys.argv[1]
    outDate=inDate
    if len(sys.argv)>2:
        outDate=sys.argv[2]
wsname = "wfit"
thisDir = os.environ.get("PWD")
inDir  = "%s/datacards_all_%s/"%(thisDir,inDate)

limDir = "%s/limits_asymptotic_%s/"%(thisDir,inDate)

biasCombination = True
biasPerChannel = True
biasPerPDF = True
biasSummary = True
checkIndividualPDFs = False
plotEnvelope = False

useCategorizedSignal = False
useCategorizedBackground = True

rs = [0,1,2]
#rs.append(3)

outDir = "%s/limits_all_%s_checks/"%(thisDir,outDate)
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
sigMasses.append("350")
sigMasses.append("500")
sigMasses.append("700")
sigMasses.append("1000")
sigMasses.append("1250")
sigMasses.append("1500")
sigMasses.append("2000")

mean = 0.0
sigma = 0.0
for y in years:
    for s in sigModels:
        meanfit  = dict()
        sigmafit = dict()
        namefit  = dict()
        for m in sigMasses:
            meanfit[m]  = dict()
            sigmafit[m] = dict()
            namefit[m]  = dict()
            #
            nBGAll = 0
            nBG1b = 0
            nBG2b = 0
            nS1b = 0
            nS2b = 0
            limFile = "%s/limits_%s.txt"%(limDir,s)
            expLim = 1.0
            if os.path.exists(limFile):
                flim = open(limFile,"r")
                for ll in flim.readlines():
                    if ll.split(",")[1]!=m:
                        continue
                    expLim=float(ll.split(",")[3])
                    break
                flim.close()
            for d in dNames:
                meanfit[m][d]  = dict()
                sigmafit[m][d] = dict()
                namefit[m][d]  = dict()
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
                # Retrieve signal normalization
                nSig = w.var("signalNorm%s"%catExtS).getValV()
                nSig = nSig*137.61
                if binidx==1:
                    nS1b = nSig
                if binidx==2:
                    nS2b = nSig
                # Retrieve background normalization
                nBG = w.var("roomultipdf%s_norm"%catExtB).getValV()
                if binidx>0:
                    nBGAll=nBGAll+nBG
                if binidx==1:
                    nBG1b = nBG
                if binidx==2:
                    nBG2b = nBG
                # Retrieve (number of) PDFs in envelope
                nPDF = w.cat("pdf_index%s"%catExtB).numTypes()
                pdfnames = []
                numpars = []
                pdfs = w.pdf("roomultipdf%s"%catExtB)
                for p in range(nPDF):
                    numpars.append(w.pdf(pdfs.getPdf(p).GetName()).getVariables().getSize()-1)
                    if "exponential" in pdfs.getPdf(p).GetName():
                        pdfnames.append("Exponential")
                    elif "powerlaw" in pdfs.getPdf(p).GetName():
                        pdfnames.append("Power-law")
                    else:
                        pdfnames.append("Bernstein<%d>"%(numpars[p]))
                pdfnames.append("Envelope")
                # Retrieve range
                maxm = w.var("mfit").getMax()
                minm = w.var("mfit").getMin()
                mrange = abs(maxm-minm)
                # Close input file with workspace
                f.Close()
                
                card = "%s/card_ch%d_%s_M%s_%s.root"%(inDir,binidx,s,m,y)
                options="--cminDefaultMinimizerStrategy 0 --X-rtd MINIMIZER_freezeDisassociatedParams --toysFrequentist --bypassFrequentist --robustFit 1"
                #options=options+" --X-rtd TMCSO_PseudoAsimov=5000"
                #options=options+"--X-rtd TMCSO_AdaptivePseudoAsimov=1"
                
                rLimOneBin = 1.0
                #os.system("combine -M AsymptoticLimits -d %s %s -m %s >& log_asym.txt"%(card,options,m))
                #flob = open("log_asym.txt","r")
                #for ll in flob.readlines():
                #    if "Expected 50" in ll:
                #        rLimOneBin = float(ll.split()[len(ll.split())-1])
                #flob.close()
                #os.system("rm log_asym.txt")

                ### Evaluate -2dLL for envelope
                extra = ""
                #extra = extra+" --X-rtd TMCSO_PseudoAsimov=10000"
                if plotEnvelope:
                    os.system("combine -M MultiDimFit -d %s -P r --algo grid --saveNLL --forceRecreateNLL -n _%s_envelope%s -m %s --rMin -1 --rMax 3 --setParameterRanges r=-0.3,3 --X-rtd REMOVE_CONSTANT_ZERO_POINT=1 --setParameters myIndex=-1 --expectSignal 0 -t -1 --points 90 --cminDefaultMinimizerStrategy 0 --toysFrequentist --bypassFrequentist --robustFit 1 --X-rtd MINIMIZER_freezeDisassociatedParams %s"%(card,s,catExtB,m,extra))
                fnmultidim = []
                for rn,r in enumerate(rs):
                    meanfit[m][d][r]  = []
                    sigmafit[m][d][r] = []
                    namefit[m][d][r]  = []
                    fnfitdiag = []
                    for p in range(nPDF):
                
                        ### Eveluate -2dLL per PDF
                        if rn==0 and plotEnvelope:
                            os.system("combine -M MultiDimFit -d %s -P r --algo grid --saveNLL --forceRecreateNLL --freezeParameters pdf_index%s --setParameters pdf_index%s=%d -n _%s_index%d%s -m %s --rMin -1 --rMax 3 --setParameterRanges r=-0.3,3 --X-rtd REMOVE_CONSTANT_ZERO_POINT=1 --expectSignal 0 -t -1 --points 90 --cminDefaultMinimizerStrategy 0 --toysFrequentist --bypassFrequentist --robustFit 1 --X-rtd MINIMIZER_freezeDisassociatedParams %s"%(card,catExtB,catExtB,p,s,p,catExtB,m,extra))
                            fnmultidim.append("_%s_index%d%s.MultiDimFit.mH%s"%(s,p,catExtB,m))

                        if not biasPerChannel or not biasPerPDF:
                            continue
                        ### If injected signal is >3x the existing background, do not perform test
                        if float(r)*expLim*nSig/nBG>3.0:
                            continue
                        ### If total yield is <=10.0 and yield/GeV<0.1, do not perform test
                        if float(r)*expLim*nSig+nBG<=10.0 and (float(r)*expLim*nSig+nBG)/mrange<0.1:
                            continue
                        ### Bias, per channel, per PDF
                        print("PDF index = ", p)
                        os.system("combine %s -M GenerateOnly --setParameters pdf_index%s=%d --toysFrequentist -t 100 --expectSignal %f --saveToys -m %s --freezeParameters pdf_index%s -n _%s_M%s_r%d_index%d%s"%(card,catExtB,p,float(r)*expLim,m,catExtB,s,m,r,p,catExtB))
                        os.system("combine %s -M FitDiagnostics --toysFile higgsCombine_%s_M%s_r%d_index%d%s.GenerateOnly.mH%s.123456.root -t 100 --rMin %f --rMax %f -n _%s_M%s_r%d_envelope_genindex%d%s -m %s %s"%(card,s,m,r,p,catExtB,m,max(-5,float(r)*expLim-5),max(5,float(r)*expLim+5),s,m,r,p,catExtB,m,options))
                        fnfitdiag.append("_%s_M%s_r%d_envelope_genindex%d%s"%(s,m,r,p,catExtB))
                        for pp in range(nPDF):
                            if not checkIndividualPDFs:
                                break
                            elif pp!=p:
                                os.system("combine %s -M FitDiagnostics --setParameters pdf_index%s=%d --toysFile higgsCombine_%s_M%s_r%d_index%d%s.GenerateOnly.mH%s.123456.root -t 100 --rMin %f --rMax %f --freezeParameters pdf_index%s -n _%s_M%s_r%d_index%d_genindex%d%s -m %s %s"%(card,catExtB,pp,s,m,r,p,catExtB,m,max(-5,float(r)*expLim-5),max(5,float(r)*expLim+5),catExtB,s,m,r,pp,p,catExtB,m,options))
                                fnfitdiag.append("_%s_M%s_r%d_index%d_genindex%d%s"%(s,m,r,pp,p,catExtB))

                    if not biasPerChannel:
                        break
                    ### If injected signal is >3x the existing background, do not perform test
                    if float(r)*expLim*nSig/nBG>3.0:
                        break
                    ### If total yield is <=10.0 and yield/GeV<0.1, do not perform test
                    if float(r)*expLim*nSig+nBG<=10.0 and (float(r)*expLim*nSig+nBG)/mrange<0.1:
                        break
                    ### Bias, per channel
                    print("combine %s -M GenerateOnly --toysFrequentist -t 100 --expectSignal %f --saveToys -m %s -n _%s_M%s_r%d%s"%(card,float(r)*expLim,m,s,m,r,catExtB))
                    os.system("combine %s -M GenerateOnly --toysFrequentist -t 100 --expectSignal %f --saveToys -m %s -n _%s_M%s_r%d%s"%(card,float(r)*expLim,m,s,m,r,catExtB))
                    print("combine %s -M FitDiagnostics --toysFile higgsCombine_%s_M%s_r%d%s.GenerateOnly.mH%s.123456.root -t 100 --rMin %f --rMax %f -n _%s_M%s_r%d_envelope%s -m %s  %s"%(card,s,m,r,catExtB,m,max(-5,float(r)*expLim-5),max(5,float(r)*expLim+5),s,m,r,catExtB,m,options))
                    os.system("combine %s -M FitDiagnostics --toysFile higgsCombine_%s_M%s_r%d%s.GenerateOnly.mH%s.123456.root -t 100 --rMin %f --rMax %f -n _%s_M%s_r%d_envelope%s -m %s  %s"%(card,s,m,r,catExtB,m,max(-5,float(r)*expLim-5),max(5,float(r)*expLim+5),s,m,r,catExtB,m,options))
                    fnfitdiag.append("_%s_M%s_r%d_envelope%s"%(s,m,r,catExtB))
                    for pp in range(nPDF):
                        if not checkIndividualPDFs:
                            break
                        elif pp!=p:
                            os.system("combine %s -M FitDiagnostics --setParameters pdf_index%s=%d --toysFile higgsCombine_%s_M%s_r%d_index%d%s.GenerateOnly.mH%s.123456.root -t 100 --rMin %f --rMax %f --freezeParameters pdf_index%s -n _%s_M%s_r%d_index%d_genindex%d%s -m %s  %s"%(card,catExtB,pp,s,m,r,p,catExtB,m,max(-5,float(r)*expLim-5),max(5,float(r)*expLim+5),catExtB,s,m,r,pp,p,catExtB,m,options))
                            fnfitdiag.append("_%s_M%s_r%d_index%d_genindex%d%s"%(s,m,r,pp,p,catExtB))

                    ### Plot bias from fit diagnostics, per channel
                    for fdn in fnfitdiag:
                        ROOT.gStyle.SetOptStat(0)
                        ROOT.gStyle.SetOptFit(111)
                        fd = ROOT.TFile.Open("fitDiagnostics%s.root"%fdn)
                        td = fd.Get("tree_fit_sb")
                        h = ROOT.TH1D("h","",61,-6.1,6.1)
                        h.GetXaxis().SetTitle("(r_{out} - r_{in})/#sigma_{r}")
                        h.GetYaxis().SetTitle("Number of toys")
                        #todraw = "(r-%f)/((rLoErr/rHiErr>3.0 || rHiErr/rLoErr>3.0) ? rErr : (r>%f ? rLoErr : rHiErr))>>h"%(float(r)*expLim,float(r)*expLim)
                        todraw = "(r-%f)/((rLoErr/rHiErr>2.0 || rHiErr/rLoErr>2.0) ? rErr : 0.5*(rLoErr+rHiErr))>>h"%(float(r)*expLim)
                        td.Draw(todraw,"fit_status==0 && abs(r-%f)<4.95"%(float(r)*expLim),"goff")
                        fg = ROOT.TF1("fg","gaus",-5.0,5.0)
                        fg.SetLineColor(2)
                        h.Fit(fg,"0L","",-5.0,5.0)
                        meanfit[m][d][r].append(fg.GetParameter(1))
                        sigmafit[m][d][r].append(fg.GetParameter(2))
                        can = ROOT.TCanvas("can","",600,600)
                        h.Draw()
                        can.Update()
                        can.Clear()
                        h.Draw()
                        fg.Draw("same")
                        text = ROOT.TLatex()
                        text.SetTextSize(0.03);
                        text.SetTextFont(42);
                        text.DrawLatexNDC(0.15,0.85,"%s, M=%s GeV"%(s,m))
                        bintext = ""
                        if binidx==1:
                            bintext="=1"
                        elif binidx==2:
                            bintext="#geq2"
                        text.DrawLatexNDC(0.15,0.8,"N_{b-tag}%s (%.0f events)"%(bintext,nBG))
                        text.DrawLatexNDC(0.15,0.75,"r_{in}=%d (%.1f)"%(r,r*nSig*expLim))
                        if len(fdn.split("_"))>6:
                            genPdfIdx = int(fdn.split("_")[5].replace("genindex",""))
                            text.DrawLatexNDC(0.15,0.7,"Gen. PDF: %s"%(pdfnames[genPdfIdx].lower()))
                            namefit[m][d][r].append(pdfnames[genPdfIdx].lower())
                        else:
                            text.DrawLatexNDC(0.15,0.7,"Gen. PDF: envelope")
                            namefit[m][d][r].append("envelope")
                        can.Update()
                        can.SaveAs("%s/bias%s.png"%(outDir,fdn))

                if plotEnvelope:
                    fnmultidim.append("_%s_envelope%s.MultiDimFit.mH%s"%(s,catExtB,m))

                    ### Plot -2dLL, per channel
                    gs = []
                    miny = +1e9
                    maxy = -1e9
                    legend = ROOT.TLegend(0.65,0.7,0.85,0.87)
                    legend.SetLineColor(0)
                    legend.SetFillColor(0)
                    pdfcolors = dict()
                    pdfcolors["Envelope"]=1
                    pdfcolors["Exponential"]=2
                    pdfcolors["Power-law"]=4
                    pdfcolors["Bernstein"]=6
                    for nf,fdn in enumerate(fnmultidim):
                        fd = ROOT.TFile.Open("higgsCombine%s.root"%fdn)
                        td = fd.Get("limit")
                        xl = []
                        yl = []
                        ### Penalty assigned to PDFs with >1 DOF:
                        #penalty=0.0
                        #if nf<len(fnmultidim)-1:
                        #    penalty=0.5*(numpars[nf]-1)
                        for e in range(td.GetEntries()):
                            td.GetEntry(e)
                            if (td.deltaNLL>1e-9 or td.deltaNLL<-1e-9) and td.deltaNLL>-1e9 and td.deltaNLL<1e9:
                                xl.append(td.r)
                                yl.append(2*(td.deltaNLL+td.nll+td.nll0))
                        xv = np.array(xl,"d")
                        yv = np.array(yl,"d")
                        gs.append(ROOT.TGraph(len(xl),xv,yv))
                        gs[nf].SetLineColor(pdfcolors[pdfnames[nf].split("<")[0]])
                        gs[nf].SetMarkerColor(pdfcolors[pdfnames[nf].split("<")[0]])
                        gs[nf].SetMarkerStyle(4)
                        gs[nf].SetMarkerSize(0.5)
                        if np.amin(yv)<miny:
                            miny = np.amin(yv)
                        if np.amax(yv)>maxy:
                            maxy = np.amax(yv)
                        if nf<len(fnmultidim)-1:
                            legend.AddEntry(gs[nf],pdfnames[nf],"L")
                        else:
                            legend.AddEntry(gs[nf],pdfnames[nf],"P")
                    h = ROOT.TH2D("h","",1,-0.3,3.0,1,miny,miny+1.25*(maxy-miny))
                    h.GetXaxis().SetTitle("r")
                    h.GetYaxis().SetTitle("-2Log(L)+c")
                    h.GetYaxis().SetLabelSize(0.02)
                    ROOT.gStyle.SetOptStat(0)
                    ROOT.gStyle.SetOptFit(0)
                    can = ROOT.TCanvas("can","",600,600)
                    h.Draw()
                    for nf,fdn in enumerate(fnmultidim):
                        if nf<len(fnmultidim)-1:
                            gs[nf].Draw("L")
                        else:
                            gs[nf].Draw("P")
                    legend.Draw("same")
                    text = ROOT.TLatex()
                    text.SetTextSize(0.03);
                    text.SetTextFont(42);
                    text.DrawLatexNDC(0.15,0.85,"M=%s GeV"%(m))
                    bintext = ""
                    if binidx==1:
                        bintext="=1"
                    elif binidx==2:
                        bintext="#geq2"
                    text.DrawLatexNDC(0.15,0.8,"N_{b-tag}%s"%(bintext))
                    can.Update()
                    can.SaveAs("%s/PDFEnvelope_expected_M%s%s.png"%(outDir,m,catExtB))

            if not biasCombination:
                continue
            ### Bias, combination
            card = "%s/card_combined_%s_M%s_%s.root"%(inDir,s,m,y)
            options="--cminDefaultMinimizerStrategy 0 --X-rtd MINIMIZER_freezeDisassociatedParams --toysFrequentist --bypassFrequentist --robustFit 1" 
            #options=options+" --X-rtd TMCSO_PseudoAsimov=5000"
            #options=options+"--X-rtd TMCSO_AdaptivePseudoAsimov=1"

            meanfit[m]["combined"] = dict()
            sigmafit[m]["combined"] = dict()
            namefit[m]["combined"] = dict()
            for rn,r in enumerate(rs):
                meanfit[m]["combined"][r] = []
                sigmafit[m]["combined"][r] = []
                namefit[m]["combined"][r] = []
                ### If injected signal is >3x the existing background, do not perform test
                if float(r)*expLim*(nS1b+nS2b)/nBGAll>3.0:
                    break
                ### If total yield is <=10.0 and yield/GeV<0.1, do not perform test
                if (float(r)*expLim*(nS1b+nS2b)+nBGAll)/mrange<0.1 and float(r)*expLim*(nS1b+nS2b)+nBGAll<=10.0:
                    break
                os.system("combine %s -M GenerateOnly --toysFrequentist -t 100 --expectSignal %f --saveToys -m %s -n _%s_M%s_r%d_envelope_combined"%(card,float(r)*expLim,m,s,m,r))
                os.system("combine %s -M FitDiagnostics --toysFile higgsCombine_%s_M%s_r%d_envelope_combined.GenerateOnly.mH%s.123456.root -t 100 --rMin %f --rMax %f -n _%s_M%s_r%d_envelope_combined -m %s %s"%(card,s,m,r,m,max(-5,float(r)*expLim-5),max(5,float(r)*expLim+5),s,m,r,m,options))
                fnfitdiag = ["_%s_M%s_r%d_envelope_combined"%(s,m,r)]

                ### Plot bias from fit diagnostics for combination
                for fdn in fnfitdiag:
                    ROOT.gStyle.SetOptStat(0)
                    ROOT.gStyle.SetOptFit(111)
                    fd = ROOT.TFile.Open("fitDiagnostics%s.root"%fdn)
                    td = fd.Get("tree_fit_sb")
                    h = ROOT.TH1D("h","",61,-6.1,6.1)
                    h.GetXaxis().SetTitle("(r_{out} - r_{in})/#sigma_{r}")
                    h.GetYaxis().SetTitle("Number of toys")
                    #todraw = "(r-%f)/((rLoErr/rHiErr>3.0 || rHiErr/rLoErr>3.0) ? rErr : (r>%f ? rLoErr : rHiErr))>>h"%(float(r)*expLim,float(r)*expLim)
                    todraw = "(r-%f)/((rLoErr/rHiErr>2.0 || rHiErr/rLoErr>2.0) ? rErr : 0.5*(rLoErr+rHiErr))>>h"%(float(r)*expLim)
                    td.Draw(todraw,"fit_status==0 && abs(r-%f)<4.95"%(float(r)*expLim),"goff")
                    fg = ROOT.TF1("fg","gaus",-5.0,5.0)
                    fg.SetLineColor(2)
                    h.Fit(fg,"0L","",-5.0,5.0)
                    meanfit[m]["combined"][r].append(fg.GetParameter(1))
                    sigmafit[m]["combined"][r].append(fg.GetParameter(2))
                    namefit[m]["combined"][r].append("envelope")
                    can = ROOT.TCanvas("can","",600,600)
                    h.Draw()
                    can.Update()
                    can.Clear()
                    h.Draw()
                    fg.Draw("same")
                    text = ROOT.TLatex()
                    text.SetTextSize(0.03);
                    text.SetTextFont(42);
                    text.DrawLatexNDC(0.15,0.85,"%s, M=%s GeV"%(s,m))
                    text.DrawLatexNDC(0.15,0.8,"N_{b-tag}=1+#geq2 (%.0f+%.0f events)"%(nBG1b,nBG2b))
                    text.DrawLatexNDC(0.15,0.75,"r_{in}=%d (%.1f+%.1f)"%(r,r*nS1b*expLim,r*nS2b*expLim))
                    text.DrawLatexNDC(0.15,0.7,"Gen. PDF: envelope")
                    can.Update()
                    can.SaveAs("%s/bias%s.png"%(outDir,fdn))


        ### Plot bias summary
        ROOT.gStyle.SetOptStat(0)
        ROOT.gStyle.SetOptFit(0)
        offset = dict()
        offset["envelope"]=0.0
        offset["bernstein"]=5.0
        offset["power-law"]=10.0
        offset["exponential"]=15.0
        plotMasses = ["350","500","700","1000","1500"]
        dNames.append("combined")
        colors = dict()
        colors["envelope"]=6
        colors["bernstein"]=4
        colors["power-law"]=3
        colors["exponential"]=2
        for r in rs:
            for d in dNames:
                g   = dict()
                npg = dict()
                doPlot = False
                leg = ROOT.TLegend(0.55,0.65,0.89,0.89)
                leg.SetLineColor(0)
                leg.SetLineStyle(0)
                leg.SetLineWidth(0)
                leg.SetFillColor(0)
                leg.SetFillStyle(0)
                for m in plotMasses:
                    if m not in sigMasses:
                        continue
                    if m not in meanfit:
                        continue
                    if d not in meanfit[m]:
                        continue
                    if r not in meanfit[m][d]:
                        continue
                    for t in range(len(meanfit[m][d][r])):
                        if namefit[m][d][r][t] not in g:
                            g[namefit[m][d][r][t]] = ROOT.TGraphErrors()
                            npg[namefit[m][d][r][t]] = 0
                            g[namefit[m][d][r][t]].SetLineColor(colors[namefit[m][d][r][t].split("<")[0]])
                            g[namefit[m][d][r][t]].SetMarkerColor(colors[namefit[m][d][r][t].split("<")[0]])
                            g[namefit[m][d][r][t]].SetMarkerStyle(3)
                            leg.AddEntry(g[namefit[m][d][r][t]],"Gen. PDF: %s"%namefit[m][d][r][t],"PL")
                            doPlot = True
                        g[namefit[m][d][r][t]].SetPoint(npg[namefit[m][d][r][t]],float(m)+offset[namefit[m][d][r][t].split("<")[0]],meanfit[m][d][r][t])
                        g[namefit[m][d][r][t]].SetPointError(npg[namefit[m][d][r][t]],0.0,sigmafit[m][d][r][t])
                        npg[namefit[m][d][r][t]] = npg[namefit[m][d][r][t]] + 1
                if not doPlot:
                    continue
                can = ROOT.TCanvas("can","",600,600)
                xmin=200.0
                xmax=1150.0
                haxis = ROOT.TH2D("haxis","",100,xmin,xmax,100,-2.5,2.5)
                haxis.GetXaxis().SetTitle("Dimuon mass [GeV]")
                haxis.GetYaxis().SetTitle("<(r_{out} - r_{in})/#sigma_{r}>")
                haxis.GetYaxis().SetLabelSize(0.025)
                haxis.Draw()
                l = ROOT.TLine(xmin,0.0,xmax,0.0)
                l.SetLineColor(1)
                l.SetLineStyle(2)
                l.Draw("same")
                lu = ROOT.TLine(xmin,1.0,xmax,1.0)
                lu.SetLineColor(1)
                lu.SetLineStyle(2)
                lu.Draw("same")
                ld = ROOT.TLine(xmin,-1.0,xmax,-1.0)
                ld.SetLineColor(1)
                ld.SetLineStyle(2)
                ld.Draw("same")
                lup5 = ROOT.TLine(xmin,0.5,xmax,0.5)
                lup5.SetLineColor(1)
                lup5.SetLineStyle(2)
                lup5.Draw("same")
                ldp5 = ROOT.TLine(xmin,-0.5,xmax,-0.5)
                ldp5.SetLineColor(1)
                ldp5.SetLineStyle(2)
                ldp5.Draw("same")
                for gg in g:
                    g[gg].Draw("PE,same")
                leg.Draw("same")

                text = ROOT.TLatex()
                text.SetTextSize(0.03);
                text.SetTextFont(42);
                binidx="ch0"
                if "nBTag1p" in d:
                    text.DrawLatexNDC(0.15,0.85,"N_{b-tag}#geq1")
                elif "nBTag1" in d:
                    text.DrawLatexNDC(0.15,0.85,"N_{b-tag}=1")
                    binidx="ch1"
                elif "nBTag2p" in d:
                    text.DrawLatexNDC(0.15,0.85,"N_{b-tag}#geq2")
                    binidx="ch2"
                else:
                    text.DrawLatexNDC(0.15,0.85,"N_{b-tag}=1 + N_{b-tag}#geq2")
                    binidx="combined"
                text.DrawLatexNDC(0.15,0.80,"r_{in}=%d"%(r))
                can.Update()
                can.SaveAs("%s/bias_vs_mass_%s_r%d_%s.png"%(outDir,s,r,binidx))
