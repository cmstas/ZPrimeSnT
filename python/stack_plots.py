from collections import OrderedDict
import ROOT
import copy
import argparse
import os
from datetime import date    
import plotUtils

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("--inDir", default="./cpp/temp_data/", help="Choose input directory. Default: './cpp/temp_data/'")
parser.add_argument("--outDir", default="/home/users/"+os.environ.get("USER")+"/public_html/Zprime/plots_"+today, help="Choose output directory. Default: '/home/users/"+user+"/public_html/Zprime/pots_"+today+"'")
parser.add_argument("--data", default=False, action="store_true", help="Plot data")
parser.add_argument("--signalMass", default=[], nargs="+", help="Signal mass points to plot. Default: All")
parser.add_argument("--signalScale", default=True, help="Scale signal up for display")
parser.add_argument("--shape", default=False, action="store_true", help="Shape normalization")
parser.add_argument("--extendedLegend", default=False, action="store_true", help="Write integrals in TLegend")
parser.add_argument("--selections", default=[], nargs="+", help="List of selections to be plotted. Default: only final selection ('sel9')")
parser.add_argument("--plotMllSlices", default=False, action="store_true", help="Plot in slices of mll. Default: False")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

if not os.path.exists(args.outDir):
    os.makedirs(args.outDir)
os.system('cp '+args.inDir+'../../utils/index.php '+args.outDir)

if len(args.signalMass)==0: 
    args.signalMass = [200,400,700,1000,1500,2000]

massToExclude=[]
if len(args.signalMass)>3:
    for i,m in enumerate(args.signalMass):
        if i%2==0:
            continue
        else:
            massToExclude.append(str(m))

if len(args.selections)==0:
    args.selections = ["sel9"]

# Only for test on Run2018B (7.05/fb)
scaleToTestLumi = 1.0
testLumi = -1.0
if args.data:
    testLumi=7.050180294

# Selection
sels = []
sels.append("N_{#mu}#geq 2, p_{T}^{#mu_{1}}>50 GeV, m_{#mu#mu}>100 GeV")
sels.append("HLT selection")
sels.append("N_{good PV}#geq 1 & MET filters")
sels.append("N_{highPt ID #mu}#geq 2")
sels.append("p_{T}^{#mu_{1,2}}>53 GeV & |#eta^{#mu_{1,2}}|<2.4")
sels.append("Track iso./p_{T} (#mu_{1,2})<0.1")
sels.append("N_{HLT match}#geq 1 (#DeltaR<0.02)")
sels.append("N_{#mu#mu}#geq 1 (OS, not from Z)")
sels.append("m_{#mu#mu}>150 GeV")
sels.append("No extra lepton / iso. track")
sels.append("N_{b-tag}#geq 1 (p_{T}>20 GeV, medium WP)")
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
if args.data:
    samples.append("data")
samples.append("Y3")
#samples.append("DY3")
#samples.append("DYp3")
#samples.append("B3mL2")
samples.append("ZToMuMu")
samples.append("ttbar")
samples.append("tW")
samples.append("tbarW")
samples.append("tZq")
samples.append("TTW")
samples.append("TTZ")
samples.append("TTHToNonbb")
samples.append("TTHTobb")
samples.append("WW")
samples.append("ZZ")
samples.append("WZ")

sampleFillColor=dict()
sampleFillColor["data"]     = None
sampleFillColor["Y3"]       = None
sampleFillColor["DY3"]      = None
sampleFillColor["DYp3"]     = None
sampleFillColor["B3mL2"]    = None
sampleFillColor["ZToMuMu"]  = ROOT.kGreen+1
sampleFillColor["ttbar"]    = ROOT.kAzure+1
sampleFillColor["tW+tZq"]   = ROOT.kAzure+2
sampleFillColor["TTX"]      = ROOT.kAzure+4
sampleFillColor["WW"]       = ROOT.kOrange-3
sampleFillColor["ZZ"]       = ROOT.kOrange-2
sampleFillColor["WZ"]       = ROOT.kOrange-1

sampleLineColor=dict()
sampleLineColor["data"]     = ROOT.kBlack
sampleLineColor["Y3"]       = ROOT.kViolet
sampleLineColor["DY3"]      = ROOT.kMagenta
sampleLineColor["DYp3"]     = ROOT.kRed
sampleLineColor["B3mL2"]    = ROOT.kCyan
sampleLineColor["ZToMuMu"]  = None
sampleLineColor["ttbar"]    = None
sampleLineColor["tW+tZq"]   = None
sampleLineColor["TTX"]      = None
sampleLineColor["WW"]       = None
sampleLineColor["ZZ"]       = None
sampleLineColor["WZ"]       = None

sampleLineWidth=dict()
sampleLineWidth["data"]     = 1
sampleLineWidth["Y3"]       = 2
sampleLineWidth["DY3"]      = 2
sampleLineWidth["DYp3"]     = 2
sampleLineWidth["B3mL2"]    = 2
sampleLineWidth["ZToMuMu"]  = 0
sampleLineWidth["ttbar"]    = 0
sampleLineWidth["tW+tZq"]   = 0
sampleLineWidth["TTX"]      = 0
sampleLineWidth["WW"]       = 0
sampleLineWidth["ZZ"]       = 0
sampleLineWidth["WZ"]       = 0

sampleMarkerStyle=dict()
sampleMarkerStyle["data"]     = 20
sampleMarkerStyle["Y3"]       = None
sampleMarkerStyle["DY3"]      = None
sampleMarkerStyle["DYp3"]     = None
sampleMarkerStyle["B3mL2"]    = None
sampleMarkerStyle["ZToMuMu"]  = None
sampleMarkerStyle["ttbar"]    = None
sampleMarkerStyle["tW+tZq"]   = None
sampleMarkerStyle["TTX"]      = None
sampleMarkerStyle["WW"]       = None
sampleMarkerStyle["ZZ"]       = None
sampleMarkerStyle["WZ"]       = None

sampleMarkerSize=dict()
sampleMarkerSize["data"]     = 1.2
sampleMarkerSize["Y3"]       = None
sampleMarkerSize["DY3"]      = None
sampleMarkerSize["DYp3"]     = None
sampleMarkerSize["B3mL2"]    = None
sampleMarkerSize["ZToMuMu"]  = None
sampleMarkerSize["ttbar"]    = None
sampleMarkerSize["tW+tZq"]   = None
sampleMarkerSize["TTX"]      = None
sampleMarkerSize["WW"]       = None
sampleMarkerSize["ZZ"]       = None
sampleMarkerSize["WZ"]       = None

sampleLegend=dict()
sampleLegend["data"]     = "Data"
sampleLegend["Y3"]       = "Y3"
sampleLegend["DY3"]      = "DY3"
sampleLegend["DYp3"]     = "DYp3"
sampleLegend["B3mL2"]    = "B3mL2"
sampleLegend["ZToMuMu"]  = "DY(#mu#mu)"
sampleLegend["ttbar"]    = "t#bar{t}"
sampleLegend["tW+tZq"]   = "tW+tZq"
sampleLegend["TTX"]      = "t#bar{t}X"
sampleLegend["WW"]       = "WW"
sampleLegend["ZZ"]       = "ZZ"
sampleLegend["WZ"]       = "WZ"

epsilon = 1e-6

def get_files(samples,year):

    sampleDict=OrderedDict()

    if year!="all":
        years=[year]
    else:
        years=["2016nonAPV","2016APV","2017","2018"]
    for tyear in years:
        for i,sample in enumerate(samples):
            if sample=="Y3" or sample=="DY3" or sample=="DYp3" or sample=="B3mL2":
                for mass in args.signalMass:
                    if (sample+"_M"+str(mass)) not in sampleDict.keys():
                        sampleDict[sample+"_M"+str(mass)]=[]
                    sampleDict[sample+"_M"+str(mass)].append(ROOT.TFile(args.inDir+"output_"+sample+"_M"+str(mass)+"_"+tyear+".root"))
            elif sample=="ZToMuMu":
                for m1,m2 in zip(["50","120","200","400","800","1400","2300","3500","4500","6000"],["120","200","400","800","1400","2300","3500","4500","6000","Inf"]): 
                    if sample not in sampleDict.keys():
                        sampleDict[sample]=[]
                    sampleDict[sample].append(ROOT.TFile(args.inDir+"output_ZToMuMu_"+m1+"_"+m2+"_"+tyear+".root"))
            else:
                if sample not in sampleDict.keys():
                    sampleDict[sample]=[]
                sampleDict[sample].append(ROOT.TFile(args.inDir+"output_"+sample+"_"+tyear+".root"))
    return sampleDict


def get_plots(sampleDict, plotname):
    plotDict=OrderedDict()
    groupedSamples = OrderedDict()
    tempGroups = OrderedDict()
    tempGroups["tW+tZq"] = ["tW","tbarW","tZq"]
    tempGroups["TTX"]   = ["TTW","TTZ","TTHToNonbb","TTHTobb"]
    for sample in sampleDict.keys():
        if sample in tempGroups["tW+tZq"]:
            if "tW+tZq" not in groupedSamples.keys():
                groupedSamples["tW+tZq"]=[]
            groupedSamples["tW+tZq"].append(sample)
        elif sample in tempGroups["TTX"]:
            if "TTX" not in groupedSamples.keys():
                groupedSamples["TTX"]=[]
            groupedSamples["TTX"].append(sample)
        else:
            groupedSamples[sample] = [sample]

    for gsample in groupedSamples.keys():
        tplot=None
        for sample in groupedSamples[gsample]:
            for tsample in sampleDict.keys():
                if sample not in tsample:
                    continue
                for inFile in sampleDict[tsample]:
                    if not tplot:
                        tplot = copy.deepcopy(inFile.Get(plotname))
                    else:
                        tplot.Add(inFile.Get(plotname))
        plotDict[gsample] = tplot

    return plotDict


def customize_plot(plot, fillColor, lineColor, lineWidth, markerStyle, markerSize):
    error = ROOT.TMath.Sqrt(plot.GetBinError(0)*plot.GetBinError(0)+plot.GetBinError(1)*plot.GetBinError(1))
    plot.SetBinContent(1, plot.GetBinContent(1) + plot.GetBinContent(0))
    plot.SetBinError(1, error)
    plot.SetBinContent(0, 0.0)
    plot.SetBinError(0, 0.0)

    error = ROOT.TMath.Sqrt(plot.GetBinError(plot.GetNbinsX()+1)*plot.GetBinError(plot.GetNbinsX()+1)+plot.GetBinError(plot.GetNbinsX())*plot.GetBinError(plot.GetNbinsX()))
    plot.SetBinContent(plot.GetNbinsX(), plot.GetBinContent(plot.GetNbinsX()+1) + plot.GetBinContent(plot.GetNbinsX()))
    plot.SetBinError(plot.GetNbinsX(), error)
    plot.SetBinContent(plot.GetNbinsX()+1, 0.0)
    plot.SetBinError(plot.GetNbinsX()+1, 0.0)

    if fillColor: 
        plot.SetFillColor(fillColor)
        plot.SetLineColor(fillColor)
        plot.SetMarkerColor(fillColor)
    if lineColor: 
        plot.SetLineColor(lineColor)
        plot.SetMarkerColor(lineColor)
    if lineWidth:
        plot.SetLineWidth(lineWidth)
    if markerStyle:
        plot.SetMarkerStyle(markerStyle)
    if markerSize:
        plot.SetMarkerSize(markerSize)
    #plot.Sumw2()

    ### Rebin fine-binned histograms
    if plot.GetXaxis().GetBinUpEdge(plot.GetNbinsX())-plot.GetXaxis().GetBinLowEdge(1) > 500.0 and plot.GetXaxis().GetBinWidth(1)<10.0:
        if plot.GetNbinsX()%5==0:
            plot.Rebin(5)
        elif plot.GetNbinsX()%3==0:
            plot.Rebin(3)
        else:
            plot.Rebin(2)

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
    latexCMS.SetTextSize(0.04)
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
    latexSel.SetTextSize(0.02-0.1*legoffset)
    latexSel.SetNDC(True)

    if testLumi>0.0:
        scaleToTestLumi = testLumi/lumi
        lumi = testLumi

    yearenergy=""
    if year!="all":
        yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
    else:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    if plotData:
        cmsExtra="Preliminary"
    else:
        cmsExtra="Simulation"

    if "cutflow" not in plotname:
        thissel=""
        if "sel8" in plotname or "sel9" in plotname:
            thissel = plotname.split("_")[len(plotname.split("_"))-3]
        else:
            thissel = plotname.split("_")[len(plotname.split("_"))-2]
        if thissel not in args.selections:
            return(0)
        thismll=""
        if "sel8" in plotname or "sel9" in plotname:
            thismll = plotname.split("_")[len(plotname.split("_"))-2]
        else:
            thismll = plotname.split("_")[len(plotname.split("_"))-1]
        if not args.plotMllSlices and 'inclusive' not in thismll:
            return(0)
    else:
        if not args.plotMllSlices and ("cutflow" in plotname and "mll" in plotname and "inclusive" not in plotname):
            return(0)

    # Get histograms
    plotDict = get_plots(sampleDict, plotname)
    curPlots=OrderedDict()

    totalSM = None
    for i,sample in enumerate(plotDict.keys()):
        # Signal
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
            model = sample.split("_")[0]
            mass = sample.split("_")[1].lstrip("M")
            if "mmumu" not in plotname and mass in massToExclude:
                continue
            if "mmumu" not in plotname:
                curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[model],sampleLineColor[model]+i%len(args.signalMass),sampleLineWidth[model],sampleMarkerStyle[model],sampleMarkerSize[model]))
            else:
                curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[model],sampleLineColor[model],sampleLineWidth[model],sampleMarkerStyle[model],sampleMarkerSize[model]))
            if testLumi>0.0:
                curPlots[sample].Scale(scaleToTestLumi)
            if args.shape and curPlots[sample].Integral(0,-1)>0.0:
                if "cutflow" not in plotname:
                    curPlots[sample].Scale(1.0/curPlots[sample].Integral(0,-1))
                else:
                    curPlots[sample].Scale(1.0/curPlots[sample].GetBinContent(1))
        # Data
        elif sample=="data": 
            if plotData:
                curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample],sampleMarkerStyle[sample],sampleMarkerSize[sample]))
        # Bkg
        else:
            curPlots[sample] = copy.deepcopy(customize_plot(plotDict[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample],sampleMarkerStyle[sample],sampleMarkerSize[sample]))
            if testLumi>0.0:
                curPlots[sample].Scale(scaleToTestLumi)
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
                model = sample.split("_")[0]
                if model not in signalXSecScale.keys():
                    signalXSecScale[model] = { }
                mass = sample.split("_")[1].lstrip("M")
                sigIntegral = curPlots[sample].Integral(0,-1)
                steps = [5.0, 10.0, 50.0, 100.0, 500.0, 1000.0, 5000.0, 10000.0, 50000.0]
                signalXSecScale[model][str(mass)]=1.0
                if sigIntegral>0.0 and totalScale>0.0:
                    ratioSMToSig = totalScale / sigIntegral
                    ratioSigToSM = sigIntegral / totalScale
                    for s in steps:
                        if ratioSigToSM<s and ratioSMToSig>s:
                            signalXSecScale[model][str(mass)]=s
                            if ratioSigToSM*s > 1:
                                signalXSecScale[model][str(mass)]=signalXSecScale[model][str(mass)]/5.0
                    if ratioSMToSig>steps[len(steps)-1]:
                        signalXSecScale[model][str(mass)]=5e3
                        if ratioSigToSM*(5e3) > 1:
                            signalXSecScale[model][str(mass)]=signalXSecScale[model][str(mass)]/5.0
                curPlots[sample].Scale(signalXSecScale[model][str(mass)])

    # Plot legends, ranges
    if args.data:
        legend = ROOT.TLegend(0.7,0.6,0.91,0.91)
    else:
        legend = ROOT.TLegend(0.7,0.6,0.89,0.89)
    if args.extendedLegend:
        if args.data:
            legend = ROOT.TLegend(0.6,0.6,0.91,0.91)
        else:
            legend = ROOT.TLegend(0.7,0.6,0.89,0.89)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    
    if args.extendedLegend:
        for sample in curPlots.keys():
            # Signal
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
                model = sample.split("_")[0]
                mass = sample.split("_")[1].lstrip("M")
                if (not logY) and args.signalScale and not args.shape and signalXSecScale[model][str(mass)]>1.0+epsilon:
                    if "cutflow" not in plotname and "mmumu" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E (x%1.1E)"%(curPlots[sample].Integral(0,-1),float(signalXSecScale[model][str(mass)])),"L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E (x%1.1E)"%(curPlots[sample].GetBinContent(1),float(signalXSecScale[model][str(mass)])),"L")
                else:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E"%(curPlots[sample].Integral(0,-1)),"L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) %1.2E"%(curPlots[sample].GetBinContent(1)),"L")
            # Data
            elif sample=="data": 
                if plotData:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[sample]+" %1.2E"%(curPlots[sample].Integral(0,-1)),"EPL")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[sample]+" %1.2E"%(curPlots[sample].GetBinContent(1)),"EPL")
            # Bkg 
            else:
                if "cutflow" not in plotname:
                    legend.AddEntry(curPlots[sample], sampleLegend[sample]+" %1.2E"%(curPlots[sample].Integral(0,-1)),"F")
                else:
                    legend.AddEntry(curPlots[sample], sampleLegend[sample]+" %1.2E"%(curPlots[sample].GetBinContent(1)),"F")
    else:
        entryExists = OrderedDict()
        for sample in curPlots.keys():
            # Signal
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
                model = sample.split("_")[0]
                mass = sample.split("_")[1].lstrip("M")
                if (not logY) and args.signalScale and not args.shape and signalXSecScale[model][str(mass)]>1.0+epsilon:
                    if "cutflow" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) x%d"%(int(signalXSecScale[model][str(mass)])),"L")
                    else:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV) x%d"%(int(signalXSecScale[model][str(mass)])),"L")
                else:
                    if "cutflow" not in plotname and "mmumu" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV)","L")
                    elif "mmumu" in plotname and model not in entryExists.keys():
                        legend.AddEntry(curPlots[sample],sampleLegend[model],"L")
                        entryExists[model]=True
                    elif "mmumu" not in plotname:
                        legend.AddEntry(curPlots[sample],sampleLegend[model]+" ("+str(mass)+" GeV)","L")
            # Data
            elif sample=="data": 
                if plotData:
                    legend.AddEntry(curPlots[sample],sampleLegend[sample],"EPL")
            # Bkg
            else:
                legend.AddEntry(curPlots[sample], sampleLegend[sample],"F")
    

    # Define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    MCplot = copy.deepcopy(totalSM)
    g_unc = ROOT.TGraphAsymmErrors()
    g_data = ROOT.TGraphAsymmErrors()
    g_ratio = ROOT.TGraphAsymmErrors()
    g_ratio_unc = ROOT.TGraphAsymmErrors()

    h_axis = ROOT.TH1D()
    h_axis_ratio = ROOT.TH1D()
    h_axis = ROOT.TH1D("h_axis","", MCplot.GetNbinsX(), MCplot.GetXaxis().GetBinLowEdge(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
    if "cutflow" in plotname:
        for b in range(1, curPlots[curPlots.keys()[0]].GetNbinsX()+1):
            tlabel = curPlots[curPlots.keys()[0]].GetXaxis().GetBinLabel(b)
            h_axis.GetXaxis().SetBinLabel(b, tlabel)
    h_axis_ratio = ROOT.TH1D("h_axis_ratio","", MCplot.GetNbinsX(), MCplot.GetXaxis().GetBinLowEdge(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
    if logX and MCplot.GetXaxis().GetBinLowEdge(1) < epsilon:
        h_axis.GetXaxis().SetRangeUser(MCplot.GetXaxis().GetBinCenter(1)-0.25*MCplot.GetXaxis().GetBinWidth(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
        h_axis_ratio.GetXaxis().SetRangeUser(MCplot.GetXaxis().GetBinCenter(1)-0.25*MCplot.GetXaxis().GetBinWidth(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
    if "cutflow" in plotname:
        h_axis_ratio.GetXaxis().SetNdivisions(MCplot.GetNbinsX())
        h_axis_ratio.GetYaxis().SetNdivisions(505)

    if plotData:
        doRatio=True

        #plotUtils.ConvertToPoissonGraph(curPlots["data"], g_data, drawZeros=True, drawXerr=False)
        plotUtils.ConvertToPoissonGraph(curPlots["data"], g_data, drawZeros=False, drawXerr=False)
        g_data.SetMarkerStyle(20)
        g_data.SetMarkerSize(1.2)
        g_data.SetLineWidth(1)
        # draw with zero marker size so error bars drawn all the way to x axis in the case of 0 content
        g_data_clone = g_data.Clone()
        g_data_clone.SetMarkerSize(0.0)

        #plotUtils.GetPoissonRatioGraph(MCplot, curPlots["data"], g_ratio, drawZeros=True, drawXerr=False, useMCErr=False)
        plotUtils.GetPoissonRatioGraph(MCplot, curPlots["data"], g_ratio, drawZeros=False, drawXerr=False, useMCErr=False)
        g_ratio.SetMarkerStyle(20)
        g_ratio.SetMarkerSize(1.2)
        g_ratio.SetLineWidth(1)

    for b in range(1,MCplot.GetNbinsX()+1):
        thisPoint = g_ratio_unc.GetN()
        yerror = MCplot.GetBinError(b)
        g_unc.SetPoint(thisPoint, MCplot.GetBinCenter(b), MCplot.GetBinContent(b))
        g_unc.SetPointError(thisPoint, 0.5*MCplot.GetBinWidth(b), 0.5*MCplot.GetBinWidth(b), yerror, yerror)
        if MCplot.GetBinContent(b)>0.0:
            yerror = yerror/MCplot.GetBinContent(b)
        else:
            yerror = 0.0
        g_ratio_unc.SetPoint(thisPoint, MCplot.GetBinCenter(b), 1.0)
        g_ratio_unc.SetPointError(thisPoint, 0.5*MCplot.GetBinWidth(b), 0.5*MCplot.GetBinWidth(b), yerror, yerror)
    g_unc.SetFillStyle(3244)
    g_unc.SetFillColor(ROOT.kGray+3)
    g_ratio_unc.SetFillStyle(1001)
    g_ratio_unc.SetFillColor(ROOT.kGray)

    pads = []
    if doRatio==True:
        h_axis_ratio.GetYaxis().SetRangeUser(0.0,2.0)
        h_axis_ratio.SetMinimum(0.0)
        h_axis_ratio.SetMaximum(2.0)
        h_axis_ratio.SetTitle(";;Data / MC")
        h_axis_ratio.GetYaxis().SetTitleSize(0.16)
        h_axis_ratio.GetYaxis().SetTitleOffset(0.25)
        if logY:
            h_axis_ratio.GetYaxis().SetTitleOffset(0.3)
        h_axis_ratio.GetYaxis().SetLabelSize(0.12)
        h_axis_ratio.GetYaxis().CenterTitle()
        h_axis_ratio.GetYaxis().SetTickLength(0.02)
        h_axis_ratio.GetXaxis().SetLabelSize(0)
        h_axis_ratio.GetXaxis().SetTitle("")
        h_axis_ratio.GetXaxis().SetTickSize(0.06)

        line = ROOT.TLine(h_axis.GetXaxis().GetBinLowEdge(1), 1.0, h_axis.GetXaxis().GetBinUpEdge(h_axis.GetNbinsX()), 1.0)

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
        pads[1].SetTickx()
        if logX:
            h_axis_ratio.GetXaxis().SetMoreLogLabels()
            pads[1].SetLogx()
        h_axis_ratio.Draw("")
        g_ratio_unc.Draw("SAME,2")
        g_ratio.Draw("SAME,P0")
        #
        line.SetLineStyle(2)
        line.SetLineColor(sampleLineColor["data"])
        line.SetLineWidth(1)
        line.Draw("SAME")
        #
        pads[1].RedrawAxis()

    else:
        pads.append(ROOT.TPad("1","1",0,0,1,1))
        pads[0].Draw()

    pads[0].cd()
    if logY:
        pads[0].SetLogy()
    if logX:
        h_axis.GetXaxis().SetMoreLogLabels()
        pads[0].SetLogx()


    #plot data, stack, signal, data  
    h_axis.GetYaxis().SetTitleSize(0.04)
    h_axis.GetXaxis().SetTitleSize(0.04)
    h_axis.GetXaxis().SetTitleOffset(1.25)
    if "cutflow" in plotname:
        h_axis.GetXaxis().SetLabelSize(0.023)
    else:
        h_axis.GetXaxis().SetTitle(totalSM.GetXaxis().GetTitle())
    if args.shape:
        h_axis.GetYaxis().SetTitle("A.U.")
    else:
        h_axis.GetYaxis().SetTitle(totalSM.GetYaxis().GetTitle())
    h_axis.GetYaxis().SetLabelSize(0.03)
    h_axis.GetYaxis().SetMaxDigits(3)
    h_axis.Draw("")
    stack.Draw("HIST,SAME")
    g_unc.Draw("SAME,2")
    histMax = 0.0
    for sample in curPlots.keys():
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
            if histMax < curPlots[sample].GetMaximum(): 
                histMax = curPlots[sample].GetMaximum()
            curPlots[sample].Draw("HIST,SAME")
    if plotData:
        if histMax < curPlots["data"].GetMaximum():
            histMax = curPlots["data"].GetMaximum()
        g_data.Draw("P,SAME")
        g_data_clone.Draw("P,SAME")

    if histMax < stack.GetMaximum(): 
        histMax = stack.GetMaximum()
    if logY:
        histMax = histMax*1e3
        h_axis.SetMinimum(1e-3)
    h_axis.SetMaximum(1.1*histMax)

    legend.Draw()
    pads[0].Update()
    pads[0].RedrawAxis()


    # Draw CMS headers
    expoffset=0.03
    if logY or 1.1*histMax<1000.0:
        expoffset=0
    if doRatio:
        latex.DrawLatex(0.95, 0.93+expoffset, yearenergy);
        latexCMS.DrawLatex(0.11,0.93+expoffset,"CMS");
        latexCMSExtra.DrawLatex(0.19,0.93+expoffset, cmsExtra);
    else:
        latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
        latexCMS.DrawLatex(0.11,0.91+expoffset,"CMS");
        latexCMSExtra.DrawLatex(0.20,0.91+expoffset, cmsExtra);


    # Draw selection
    if "cutflow" not in plotname:
        whichnb  = ""
        whichmll = ""
        whichsel = ""
        if "sel8" in plotname or "sel9" in plotname:
            whichnb  = plotname.split("_")[len(plotname.split("_"))-1]
            whichmll = plotname.split("_")[len(plotname.split("_"))-2]
            whichsel = plotname.split("_")[len(plotname.split("_"))-3]
        else:
            whichmll = plotname.split("_")[len(plotname.split("_"))-1]
            whichsel = plotname.split("_")[len(plotname.split("_"))-2]
        ts = 0
        for s in range(0,nsel[whichsel]+1):
            if 'inclusive' not in whichmll and s==8:
                continue
            if '1p' not in whichnb and s==10:
                continue
            ts = ts+1
            if args.data:
                latexSel.DrawLatex(0.45+3*legoffset, 0.91-ts*(0.03-legoffset), sels[s])
            else:
                latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), sels[s])
        if 'inclusive' not in whichmll and nsel[whichsel]>=8:
            ts = ts+1
            if args.data:
                latexSel.DrawLatex(0.45+3*legoffset, 0.91-ts*(0.03-legoffset), mllbin[whichmll])
            else:
                latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), mllbin[whichmll])
        if '1p' not in whichnb and nsel[whichsel]>=10:
            ts = ts+1
            if args.data:
                latexSel.DrawLatex(0.45+3*legoffset, 0.91-ts*(0.03-legoffset), nbbin[whichnb])
            else:
                latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), nbbin[whichnb])


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

year="2018"
lumi=59.83
# Open files
sampleDict=get_files(samples,year)
# List of plots
listofplots = []
listfile = sampleDict[sampleDict.keys()[0]][0]
listkeys = listfile.GetListOfKeys()
size = listkeys.GetSize()
for i in range(0,size):
    listofplots.append(listkeys.At(i).GetName())
toexclude = []

for plot in listofplots:
    if plot in toexclude:
        continue
    draw_plot(sampleDict, plot, False, False, args.data, False, lumi, year)
    draw_plot(sampleDict, plot, True , False, args.data, False, lumi, year)
    if("pt" in plot or "mmumu" in plot or "mlb" in plot):
      draw_plot(sampleDict, plot, False, True, args.data, False, lumi, year)
      draw_plot(sampleDict, plot, True , True, args.data, False, lumi, year)
