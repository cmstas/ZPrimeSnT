from collections import OrderedDict
import ROOT
import copy
import argparse
import os
from datetime import date    


user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("--inDir", default="./cpp/temp_data/", help="Choose input directory. Default: './cpp/temp_data/'")
parser.add_argument("--outDir", default="/home/users/"+os.environ.get("USER")+"/public_html/Zprime/plots_"+today, help="Choose output directory. Default: '/home/users/"+user+"/public_html/Zprime/pots_"+today+"'")
parser.add_argument("--data", action="store_true", default=False, help="Plot data")
parser.add_argument("--signalMass", default=[], action="append", help="Signal masspoints to plot. Default: All")
parser.add_argument("--signalScale", default=True, help="Scale signal up for display")
parser.add_argument("--shape", action="store_true", default=False, help="Shape normalization")
parser.add_argument("--extendedLegend", action="store_true", default=False, help="Write integrals in TLegend")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

if not os.path.exists(args.outDir):
    os.makedirs(args.outDir)
os.system('cp '+args.inDir+'../../utils/index.php '+args.outDir)

if len(args.signalMass)==0: 
    args.signalMass = [200,400,700,1000,1500,2000]


# Selection
sels = []
sels.append("N_{#mu}#geq 2, p_{T}^{#mu_{1}}>50 GeV, m_{#mu#mu}>100 GeV")
sels.append("HLT selection")
sels.append("N_{good PV}#geq 1")
sels.append("N_{highPt ID #mu}#geq 2")
sels.append("p_{T}^{#mu_{1,2}}>53 GeV & |#eta^{#mu_{1,2}}|<2.4")
sels.append("Track iso./p_{T} (#mu_{1,2})<0.1")
sels.append("N_{HLT match}#geq 1 (#DeltaR<0.02)")
sels.append("N_{#mu#mu}#geq 1 (OS, not from Z)")
sels.append("No extra lepton / iso. track")
sels.append("N_{b-tag}#geq 1 (p_{T}>20 GeV, medium WP)")
sels.append("m_{#mu#mu}>150 GeV")
sels.append("min m_{#mu b}>175 GeV")

nsel=dict()
nsel["sel0"]=2
nsel["sel1"]=3
nsel["sel2"]=4
nsel["sel3"]=5
nsel["sel4"]=6
nsel["sel5"]=7
nsel["sel6"]=8
nsel["sel7"]=9
nsel["sel8"]=10
nsel["sel9"]=11

nbbin=dict()
nbbin["nBTag1p"]="N_{b-tag}#geq 1 (p_{T}>20 GeV, medium WP)"
nbbin["nBTag1"]="N_{b-tag}= 1 (p_{T}>20 GeV, medium WP)"
nbbin["nBTag2p"]="N_{b-tag}#geq 2 (p_{T}>20 GeV, medium WP)"

mllbin=dict()
mllbin["mll150to250"]="150 < m_{#mu#mu} < 250 GeV"
mllbin["mll200to600"]="200 < m_{#mu#mu} < 600 GeV"
mllbin["mll500to900"]="500 < m_{#mu#mu} < 900 GeV"
mllbin["mll700to1300"]="700 <m_{#mu#mu} < 1300 GeV"
mllbin["mll1100to1900"]="1.1 < m_{#mu#mu} < 1.9 TeV"
mllbin["mll1500to2500"]="1.5 < m_{#mu#mu} < 2.5 TeV"


# Samples
samples=[]
# data to be added
samples.append("Y3")
samples.append("ZToMuMu")
samples.append("ttbar")
samples.append("tW")
samples.append("tbarW")
samples.append("TTW")
samples.append("TTZ")
samples.append("TTHToNonbb")
samples.append("TTHTobb")
samples.append("WW")
samples.append("ZZ")
samples.append("WZ")

sampleFillColor=dict()
# data to be added
sampleFillColor["Y3"]       = None
sampleFillColor["ZToMuMu"]  = ROOT.kGreen+1
sampleFillColor["ttbar"]    = ROOT.kAzure+1
sampleFillColor["ST_tW"]    = ROOT.kAzure+2
sampleFillColor["TTX"]      = ROOT.kAzure+4
sampleFillColor["WW"]       = ROOT.kOrange-3
sampleFillColor["ZZ"]       = ROOT.kOrange-2
sampleFillColor["WZ"]       = ROOT.kOrange-1

sampleLineColor=dict()
# data to be added
sampleLineColor["Y3"]       = ROOT.kViolet-9
sampleLineColor["ZToMuMu"]  = None
sampleLineColor["ttbar"]    = None
sampleLineColor["ST_tW"]    = None
sampleLineColor["TTX"]      = None
sampleLineColor["WW"]       = None
sampleLineColor["ZZ"]       = None
sampleLineColor["WZ"]       = None

sampleLineWidth=dict()
# data to be added
sampleLineWidth["Y3"]       = 2
sampleLineWidth["ZToMuMu"]  = 0
sampleLineWidth["ttbar"]    = 0
sampleLineWidth["ST_tW"]    = 0
sampleLineWidth["TTX"]      = 0
sampleLineWidth["WW"]       = 0
sampleLineWidth["ZZ"]       = 0
sampleLineWidth["WZ"]       = 0

sampleLegend=dict()
sampleLegend["Y3"]       = "Y3"
sampleLegend["data"]     = "data"
sampleLegend["ZToMuMu"]  = "DY(#mu#mu)"
sampleLegend["ttbar"]    = "t#bar{t}"
sampleLegend["ST_tW"]    = "tW"
sampleLegend["TTX"]      = "t#bar{t}X"
sampleLegend["WW"]       = "WW"
sampleLegend["ZZ"]       = "ZZ"
sampleLegend["WZ"]       = "WZ"


def get_files(samples):

    sampleDict=OrderedDict()

    for i,sample in enumerate(samples):
        if sample=="Y3" or sample=="DY3" or sample=="DYp3" or sample=="B3mL2":
            for mass in args.signalMass: 
                 sampleDict[sample+"_M"+str(mass)]=ROOT.TFile(args.inDir+"output_"+sample+"_M"+str(mass)+"_2018.root")
        elif sample=="ZToMuMu":
            for m1,m2 in zip(["50","120","200","400","800","1400","2300","3500","4500","6000"],["120","200","400","800","1400","2300","3500","4500","6000","Inf"]): 
                sampleDict[sample+"_"+m1+"_"+m2]=ROOT.TFile(args.inDir+"output_ZToMuMu_"+m1+"_"+m2+"_2018.root")
        else:
            sampleDict[sample]=ROOT.TFile(args.inDir+"output_"+sample+"_2018.root")

    return sampleDict


def get_plots(sampleDict, plotname):
    plotDict=OrderedDict()

    ZToMuMuPlot=None
    ST_tWPlot=None
    TTXPlot=None
    for i,sample in enumerate(sampleDict.keys()):
        inFile = sampleDict[sample]
        if "ZToMuMu" in sample:
            if not ZToMuMuPlot:
                ZToMuMuPlot = copy.deepcopy(inFile.Get(plotname))
            else:
                ZToMuMuPlot.Add(inFile.Get(plotname))
            plotDict["ZToMuMu"] = ZToMuMuPlot
        elif sample=="tW" or sample=="tbarW":
            if not ST_tWPlot:
                ST_tWPlot = copy.deepcopy(inFile.Get(plotname))
            else:
                ST_tWPlot.Add(inFile.Get(plotname))
            plotDict["ST_tW"] = ST_tWPlot
        elif sample=="TTW" or sample=="TTZ" or sample=="TTHToNonbb" or sample=="TTHTobb":
            if not TTXPlot:
                TTXPlot = copy.deepcopy(inFile.Get(plotname))
            else:
                TTXPlot.Add(inFile.Get(plotname))
            plotDict["TTX"] = TTXPlot
        else:
            plotDict[sample] = inFile.Get(plotname)

    return plotDict


def customize_plot(plot, fillColor, lineColor, lineWidth):
    plot.SetBinContent(1, plot.GetBinContent(1) + plot.GetBinContent(0))
    plot.SetBinContent(plot.GetNbinsX(), plot.GetBinContent(plot.GetNbinsX() + 1) + plot.GetBinContent(plot.GetNbinsX()))

    if fillColor: 
        plot.SetFillColor(fillColor)
        plot.SetLineColor(fillColor)
        plot.SetMarkerColor(fillColor)
    if lineColor: 
        plot.SetLineColor(lineColor)
        plot.SetMarkerColor(lineColor)
    plot.SetLineWidth(lineWidth)
    #plot.Sumw2()

    return plot


def draw_plot(sampleDict, plotname, logY=True, logX=False, plotData=False, doRatio=True, lumi=59.83, year="2018"):

    # Labels
    latex = ROOT.TLatex()
    latex.SetTextFont(42)
    latex.SetTextAlign(31)
    latex.SetTextSize(0.04)
    latex.SetNDC(True)

    latexCMS = ROOT.TLatex()
    latexCMS.SetTextFont(61)
    latexCMS.SetTextSize(0.05)
    latexCMS.SetNDC(True)

    latexCMSExtra = ROOT.TLatex()
    latexCMSExtra.SetTextFont(52)
    latexCMSExtra.SetTextSize(0.04)
    latexCMSExtra.SetNDC(True)

    legoffset = 0.0
    if args.extendedLegend:
        legoffset=0.03
    latexSel = ROOT. TLatex()
    latexSel.SetTextAlign(11)
    latexSel.SetTextFont(42)
    latexSel.SetTextSize(0.02-legoffset)
    latexSel.SetNDC(True)

    yearenergy=""
    if year!="all":
        yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
    else:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    cmsExtra="Simulation"


    # Get histograms
    plotDict = get_plots(sampleDict, plotname)
    curPlots=OrderedDict()

    totalSM = None
    for i,sample in enumerate(plotDict.keys()):
        # Signal
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
            model = sample.split("_")[0]
            mass = sample.split("_")[1].lstrip("M")
            curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[model],sampleLineColor[model]+i%len(args.signalMass),sampleLineWidth[model]))
            if args.shape and curPlots[sample].Integral(0,-1)>0.0:
                if "cutflow" not in plotname:
                    curPlots[sample].Scale(1.0/curPlots[sample].Integral(0,-1))
                else:
                    curPlots[sample].Scale(1.0/curPlots[sample].GetBinContent(1))
        # Data
        elif sample=="data": 
            if plotData:
                curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample]))
        # Bkg
        else:
            curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample]))
            if not totalSM:
                totalSM = curPlots[sample].Clone("totalSM")
            else:
                totalSM.Add(curPlots[sample])

    totalScale   = totalSM.Integral(0,-1)
    if "cutflow" in plotname:
        totalScale = totalSM.GetBinContent(1)


    # Build stack
    stack = ROOT.THStack("stack","")
    for i,sample in enumerate(reversed(plotDict.keys())):
        # Bkg
        if not ("Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or sample=="data"):
            if args.shape and totalScale>0.0:
                curPlots[sample].Scale(1.0/totalScale)
            stack.Add(curPlots[sample])


    # Signal Scaling
    signalXSecScale = { }
    if (not logY) and args.signalScale and not args.shape:
        for sample in curPlots.keys():
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
                mass = sample.split("_")[1].lstrip("M")
                sigIntegral = curPlots[sample].Integral(0,-1)
                steps = [50.0, 100.0, 500.0, 1000.0, 5000.0, 10000.0, 50000.0]
                signalXSecScale[str(mass)]=1.0
                if sigIntegral>0.0 and totalScale>0.0:
                    ratioSMToSig = totalScale / sigIntegral
                    ratioSigToSM = sigIntegral / totalScale
                    for s in steps:
                        if ratioSMToSig<s:
                            signalXSecScale[str(mass)]=s/50.0
                            if ratioSigToSM*(s/50.0) > 1:
                                signalXSecScale[str(mass)]=signalXSecScale[str(mass)]/10.0
                    if ratioSMToSig>steps[len(steps)-1]:
                        signalXSecScale[str(mass)]=5e3
                        if ratioSigToSM*(5e3) > 1:
                            signalXSecScale[str(mass)]=signalXSecScale[str(mass)]/10.0
                curPlots[sample].Scale(signalXSecScale[str(mass)])


    # Plot legends, ranges
    legend = ROOT.TLegend(0.65,0.65,0.89,0.89)
    if args.extendedLegend:
        legend = ROOT.TLegend(0.55,0.55,0.89,0.89)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    #legend.SetTextSize(0.02)

    if args.extendedLegend:
        for sample in curPlots.keys():
            # Signal
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
                model = sample.split("_")[0]
                mass = sample.split("_")[1].lstrip("M")
                if (not logY) and args.signalScale and not args.shape and signalXSecScale[str(mass)]>1.5:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E (x%1.1E)"%(curPlots[sample].Integral(0,-1),float(signalXSecScale[str(mass)])),"L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E (x%1.1E)"%(curPlots[sample].GetBinContent(1),float(signalXSecScale[str(mass)])),"L")
                else:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E"%(curPlots[sample].Integral(0,-1)),"L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E"%(curPlots[sample].GetBinContent(1)),"L")
            # Data
            elif sample=="data": 
                if plotData:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[sample]+" %1.2E"%(curPlots[sample].Integral(0,-1)),"PL")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[sample]+" %1.2E"%(curPlots[sample].GetBinContent(1)),"PL")
            # Bkg 
            else:
                if "cutflow" not in plotname:
                    legend.AddEntry(curPlots[sample], sampleLegend[sample]+" %1.2E"%(curPlots[sample].Integral(0,-1)),"F")
                else:
                    legend.AddEntry(curPlots[sample], sampleLegend[sample]+" %1.2E"%(curPlots[sample].GetBinContent(1)),"F")
    else:
        for sample in curPlots.keys():
            # Signal
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
                model = sample.split("_")[0]
                mass = sample.split("_")[1].lstrip("M")
                if (not logY) and args.signalScale and not args.shape and signalXSecScale[str(mass)]>1.5:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) x%1.1E"%(float(signalXSecScale[str(mass)])),"L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) x%1.1E"%(float(signalXSecScale[str(mass)])),"L")
                else:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV)","L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV)","L")
            # Data
            elif sample=="data": 
                if plotData:
                    legend.AddEntry(curPlots[sample],sampleLegend[sample],"PL")
            # Bkg
            else:
                legend.AddEntry(curPlots[sample], sampleLegend[sample],"F")
    

    # Define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    if doRatio==True:
        MCplot = copy.deepcopy(totalSM)
        ratioplot=copy.deepcopy(curPlots["data"])
        ratioplot.Divide(MCplot)
        ratioplot.SetTitle(";Data / MC")
        pad1 = ROOT.TPad("pad1","pad1",0,0.3,1,1)
        pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.3)
        pad1.Draw()
        pad2.Draw()
        pad2.cd()
        if logX:
            if ratioplot.GetXaxis().GetBinLowEdge(1)<=0.0:
                ratioplot.GetXaxis().SetRangeUser(1.0, ratioplot.GetXaxis().GetBinUpEdge(ratioplot.GetNbinsX()))
            pad2.SetLogx()
        ratioplot.Draw("E0")
    else:
        pad1 = ROOT.TPad("pad1","pad1",0,0,1,1)
        pad1.Draw()

    pad1.cd()
    if logY:
        pad1.SetLogy()
    if logX:
        pad1.SetLogx()


    #plot data, stack, signal, data  
    stack.Draw("HIST")
    if logX:
        if stack.GetXaxis().GetBinLowEdge(1)<=0.0:
            stack.GetXaxis().SetRangeUser(1.0, stack.GetXaxis().GetBinUpEdge(stack.GetXaxis().GetNbins()))
    if "cutflow" in plotname:
        stack.GetXaxis().SetLabelSize(0.023)
    else:
        stack.GetXaxis().SetTitle(totalSM.GetXaxis().GetTitle())
    stack.GetYaxis().SetTitle(totalSM.GetYaxis().GetTitle())
    if args.shape:
        stack.GetYaxis().SetTitle("A.U.")
    stack.GetYaxis().SetLabelSize(0.03)
    stack.GetYaxis().SetMaxDigits(3)
    histMax = 0.0
    for sample in curPlots.keys():
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
            if histMax < curPlots[sample].GetMaximum(): 
                histMax = curPlots[sample].GetMaximum()
            curPlots[sample].Draw("HIST same")
    if plotData: 
        curPlots["data"].Draw("E0 same")

    if histMax < stack.GetMaximum(): 
        histMax = stack.GetMaximum()
    if logY:
        histMax = histMax*1e3
        stack.SetMinimum(1e-3)
    stack.SetMaximum(1.1*histMax)

    canvas.Update()
    legend.Draw()
    ROOT.gPad.RedrawAxis()


    # Draw CMS headers
    expoffset=0.03
    if logY or 1.1*histMax<1000.0:
        expoffset=0
    latex.DrawLatex(0.9, 0.92+expoffset, yearenergy);
    latexCMS.DrawLatex(0.11,0.92+expoffset,"CMS");
    latexCMSExtra.DrawLatex(0.22,0.92+expoffset, cmsExtra);


    # Draw selection
    if "cutflow" not in plotname:
        whichnb  = plotname.split("_")[len(plotname.split("_"))-1]
        whichmll = plotname.split("_")[len(plotname.split("_"))-2]
        whichsel = plotname.split("_")[len(plotname.split("_"))-3]
        ts = 0
        for s in range(0,nsel[whichsel]+1):
            if '1p' not in whichnb and s==7:
                continue
            if 'inclusive' not in whichmll and s==8:
                continue
            ts = ts+1
            latexSel.DrawLatex(0.3+3*legoffset, 0.89-ts*(0.028-legoffset), sels[s])
        if '1p' not in whichnb and nsel[whichsel]>=9:
            ts = ts+1
            latexSel.DrawLatex(0.3+3*legoffset, 0.89-ts*(0.028-legoffset), nbbin[whichnb])
        if 'inclusive' not in whichmll and nsel[whichsel]>=7:
            ts = ts+1
            latexSel.DrawLatex(0.3+3*legoffset, 0.89-ts*(0.028-legoffset), mllbin[whichmll])


    # Print and save
    extension = ""
    if plotData:
        extension = extension+"_mc+data"
    else:
        extension = extension+"_s+b"
    if logX:
        extension = extension+"_logX"
    if logY:
        extension = extension+"_logY"
    if args.shape:
        extension = extension+"_areaNormalized"
    
    canvas.SaveAs(args.outDir + plotname + extension + ".png")



# Main
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)

# Open files
sampleDict=get_files(samples)

# List of plots
listofplots = []
listfile = sampleDict[sampleDict.keys()[0]]
listkeys = listfile.GetListOfKeys()
size = listkeys.GetSize()
for i in range(0,size):
    listofplots.append(listkeys.At(i).GetName())
toexclude = []

for plot in listofplots:
    if plot in toexclude:
        continue
    draw_plot(sampleDict, plot, False, False, args.data, False, 59.83, "2018")
    draw_plot(sampleDict, plot, True , False, args.data, False, 59.83, "2018")
    if("pt" in plot or "mll_pf" in plot):
      draw_plot(sampleDict, plot, False, True, args.data, False, 59.83, "2018")
      draw_plot(sampleDict, plot, True , True, args.data, False, 59.83, "2018")
