from collections import OrderedDict
import ROOT
import numpy
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
parser.add_argument("--dataOnly", default=False, action="store_true", help="Plot only data, no MC bkg")
parser.add_argument("--partialUnblinding", default=False, action="store_true", help="Plot 10% of data")
parser.add_argument("--noSignal", default=False, action="store_true", help="Do not plot signals")
parser.add_argument("--signalMass", default=[], nargs="+", help="Signal mass points to plot. Default: All")
parser.add_argument("--signalScale", default=True, help="Scale signal up for display")
parser.add_argument("--shape", default=False, action="store_true", help="Shape normalization")
parser.add_argument("--cumulative", default=False, action="store_true", help="Cumulative distributions")
parser.add_argument("--extendedLegend", default=False, action="store_true", help="Write integrals in TLegend")
parser.add_argument("--noSelPrint", default=False, action="store_true", help="Do not print slection onn plots")
parser.add_argument("--selections", default=[], nargs="+", help="List of selections to be plotted. Default: only final selection ('sel10')")
parser.add_argument("--years", default=[], nargs="+", help="List of years to be plotted. Default: all years")
parser.add_argument("--plotMllSlices", default=False, action="store_true", help="Plot in slices of mll. Default: False")
parser.add_argument("--mllBinningForBFF", default=False, action="store_true", help="Plot in slices of mll for BFF analysis comparison. Default: False")
parser.add_argument("--plotMuonDetRegions", default=False, action="store_true", help="Plot muon divided by detector regions. Default: False")
parser.add_argument("--plotProdModes", default=False, action="store_true", help="Plot signal samples split in production modes (ss, sb, bb). Bkgs cannot be splt in a simlar way and are plotted inclusively. Default: False")
parser.add_argument("--pdf", default=False, action="store_true", help="Output format: .pdf. Default: .png")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

if not os.path.exists(args.outDir):
    os.makedirs(args.outDir)
os.system('cp '+os.environ.get("PWD")+'/utils/index.php '+args.outDir)

if args.dataOnly:
    args.data = True

if len(args.signalMass)==0: 
    args.signalMass = [200,400,700,1000,1500,2000]

if "antisel10" in args.selections:
    args.signalMass = [200,400,700]

massToExclude=[]
if len(args.signalMass)>3:
    for i,m in enumerate(args.signalMass):
        if i%2==0:
            continue
        else:
            massToExclude.append(str(m))

if len(args.selections)==0:
    args.selections = ["sel10"]

if len(args.years)==0:
    args.years = ["all"]

# Only for test on Run2018B (7.05/fb)
scaleToTestLumi = 1.0
testLumiRatio = -1.0
if args.data and args.partialUnblinding:
    testLumiRatio=0.1

# Do signal/MC ratio
doSignalMCRatio = False

# Selection
sels = []
sels.append("N_{#mu}#geq 2, p_{T}^{#mu_{1}}>50 GeV, m_{#mu#mu}>100 GeV")
sels.append("HLT selection")
sels.append("N_{good PV}#geq 1 & E_{T}^{miss} filters")
sels.append("N_{highPt ID #mu}#geq 2 (d_{xy, z} < 0.02, 0.1 cm)")
sels.append("p_{T}^{#mu_{1,2}}>53 GeV & |#eta^{#mu_{1,2}}|<2.4")
sels.append("Track iso.(/p_{T})^{#mu_{1,2}}< 5.0 GeV (0.05)")
sels.append("N_{HLT match}#geq 1 (#DeltaR<0.02)")
sels.append("N_{#mu#mu}#geq 1 (OS, not from Z)")
sels.append("m_{#mu#mu}>275 GeV")
sels.append("No extra lepton / iso. track")
sels.append("N_{b-tag}#geq 1 (p_{T}>20 GeV, T+Ms WP)")
sels.append("E_{T}^{miss}<250 GeV, if aligned")
sels.append("min m_{#mu b}>175 GeV")
sels.append("min m_{#mu b}<175 GeV")

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
nsel["sel10"]=12
nsel["antisel10"]=13

nbbin=dict()
nbbin["nBTag0"]="N_{b} = 0"+("" if args.noSelPrint else " (p_{T}>20 GeV, M WP)")
nbbin["nBTag1p"]="N_{b} #geq 1"+("" if args.noSelPrint else " (p_{T}>20 GeV, T+Ms WP)")
nbbin["nBTag1"]="N_{b} = 1"+("" if args.noSelPrint else " (p_{T}>20 GeV, T WP)")
nbbin["nBTag2p"]="N_{b} #geq 2"+("" if args.noSelPrint else " (p_{T}>20 GeV, T+Ms WP)")

mllbin=dict()
if args.mllBinningForBFF:
  mllbin["mll225to275"]="225 < m_{#mu#mu} < 275 GeV"
  mllbin["mll315to385"]="315 < m_{#mu#mu} < 385 GeV"
  mllbin["mll450to550"]="450 < m_{#mu#mu} < 550 GeV"
else:
  mllbin["mll175to300"]="175 < m_{#mu#mu} < 300 GeV"
  mllbin["mll300to500"]="300 < m_{#mu#mu} < 500 GeV"
  mllbin["mll500to900"]="500 < m_{#mu#mu} < 900 GeV"
  mllbin["mll750to1250"]="750 <m_{#mu#mu} < 1250 GeV"
  mllbin["mll1100to1900"]="1.1 < m_{#mu#mu} < 1.9 TeV"
  mllbin["mll1500to2500"]="1.5 < m_{#mu#mu} < 2.5 TeV"

MuDetbin=dict()
MuDetbin["BB"]="2 muons in Barrel"
MuDetbin["BE"]="1 muon in Barrel, 1 muon in Endcap)"
MuDetbin["EE"]="2 muons in Endcap"

prodMode=dict()
prodMode["all"]="All production modes"
prodMode["ss"]="bs production mode"
prodMode["bs"]="bs production mode"
prodMode["bb"]="bb production mode"

# Samples
samples=[]
if args.data:
    samples.append("data")
# Signal MC
if not args.noSignal:
  samples.append("Y3")
  #samples.append("DY3")
  #samples.append("DYp3")
  samples.append("B3mL2")
# SM MC
if not args.dataOnly:
    #samples.append("DYbb")
    samples.append("ZToMuMu")
    samples.append("ttbar_2L2Nu")
    samples.append("ttbar_SemiLeptonic")
    samples.append("ttbar_Hadronic")
    samples.append("tW")
    samples.append("tbarW")
    samples.append("tZq")
    samples.append("TTW")
    samples.append("TTZ")
    samples.append("TTHToNonbb")
    samples.append("TTHTobb")
    #samples.append("WW")
    samples.append("WWTo1L1Nu2Q")
    samples.append("WWTo4Q")
    samples.append("WWTo2L2Nu")
    #samples.append("ZZ")
    samples.append("ZZTo2L2Nu")
    samples.append("ZZTo2Nu2Q")
    samples.append("ZZTo2Q2L")
    samples.append("ZZTo4L")
    samples.append("ZZTo4Q")
    #samples.append("WZ")
    samples.append("WZTo1L1Nu2Q")
    samples.append("WZTo1L3Nu")
    samples.append("WZTo2Q2L")
    samples.append("WZTo3LNu")
# PreUL NanoAODv7 samples for BFF comparison
# Signal MC
#samples.append("BFF")
#samples.append("BFFdbs1p0")
#samples.append("DY_v7")
#samples.append("ttbar_v7")

sampleFillColor=dict()
sampleFillColor["data"]     = None
sampleFillColor["Y3"]       = None
sampleFillColor["DY3"]      = None
sampleFillColor["DYp3"]     = None
sampleFillColor["B3mL2"]    = None
sampleFillColor["DYbb"]     = ROOT.kRed
sampleFillColor["ZToMuMu"]  = ROOT.kGreen+1
sampleFillColor["ttbar"]    = ROOT.kAzure+1
sampleFillColor["tW+tZq"]   = ROOT.kAzure+2
sampleFillColor["TTX"]      = ROOT.kAzure+4
sampleFillColor["WW"]       = ROOT.kOrange-3
sampleFillColor["ZZ"]       = ROOT.kOrange-2
sampleFillColor["WZ"]       = ROOT.kOrange-1
sampleFillColor["BFF"]      = None
sampleFillColor["BFFdbs1p0"]= None
sampleFillColor["DY_v7"]    = ROOT.kGreen+1
sampleFillColor["ttbar_v7"] = ROOT.kAzure+1

sampleLineColor=dict()
sampleLineColor["data"]     = ROOT.kBlack
sampleLineColor["Y3"]       = ROOT.kViolet
sampleLineColor["DY3"]      = ROOT.kMagenta
sampleLineColor["DYp3"]     = ROOT.kRed
sampleLineColor["B3mL2"]    = ROOT.kCyan
sampleLineColor["DYbb"]     = None
sampleLineColor["ZToMuMu"]  = None
sampleLineColor["ttbar"]    = None
sampleLineColor["tW+tZq"]   = None
sampleLineColor["TTX"]      = None
sampleLineColor["WW"]       = None
sampleLineColor["ZZ"]       = None
sampleLineColor["WZ"]       = None
sampleLineColor["BFF"]      = ROOT.kViolet
sampleLineColor["BFFdbs1p0"]= ROOT.kRed
sampleLineColor["DY_v7"]    = None
sampleLineColor["ttbar_v7"] = None

sampleLineWidth=dict()
sampleLineWidth["data"]     = 1
sampleLineWidth["Y3"]       = 2
sampleLineWidth["DY3"]      = 2
sampleLineWidth["DYp3"]     = 2
sampleLineWidth["B3mL2"]    = 2
sampleLineWidth["DYbb"]     = 0
sampleLineWidth["ZToMuMu"]  = 0
sampleLineWidth["ttbar"]    = 0
sampleLineWidth["tW+tZq"]   = 0
sampleLineWidth["TTX"]      = 0
sampleLineWidth["WW"]       = 0
sampleLineWidth["ZZ"]       = 0
sampleLineWidth["WZ"]       = 0
sampleLineWidth["BFF"]      = 2
sampleLineWidth["BFFdbs1p0"]= 2
sampleLineWidth["DY_v7"]    = 0
sampleLineWidth["ttbar_v7"] = 0

sampleMarkerStyle=dict()
sampleMarkerStyle["data"]     = 20
sampleMarkerStyle["Y3"]       = None
sampleMarkerStyle["DY3"]      = None
sampleMarkerStyle["DYp3"]     = None
sampleMarkerStyle["B3mL2"]    = None
sampleMarkerStyle["DYbb"]     = None
sampleMarkerStyle["ZToMuMu"]  = None
sampleMarkerStyle["ttbar"]    = None
sampleMarkerStyle["tW+tZq"]   = None
sampleMarkerStyle["TTX"]      = None
sampleMarkerStyle["WW"]       = None
sampleMarkerStyle["ZZ"]       = None
sampleMarkerStyle["WZ"]       = None
sampleMarkerStyle["BFF"]      = None
sampleMarkerStyle["BFFdbs1p0"]= None
sampleMarkerStyle["DY_v7"]    = None
sampleMarkerStyle["ttbar_v7"] = None

sampleMarkerSize=dict()
sampleMarkerSize["data"]     = 1.2
sampleMarkerSize["Y3"]       = None
sampleMarkerSize["DY3"]      = None
sampleMarkerSize["DYp3"]     = None
sampleMarkerSize["B3mL2"]    = None
sampleMarkerSize["DYbb"]     = None
sampleMarkerSize["ZToMuMu"]  = None
sampleMarkerSize["ttbar"]    = None
sampleMarkerSize["tW+tZq"]   = None
sampleMarkerSize["TTX"]      = None
sampleMarkerSize["WW"]       = None
sampleMarkerSize["ZZ"]       = None
sampleMarkerSize["WZ"]       = None
sampleMarkerSize["BFF"]      = None
sampleMarkerSize["BFFdbs1p0"]= None
sampleMarkerSize["DY_v7"]    = None
sampleMarkerSize["ttbar_v7"] = None

sampleLegend=dict()
sampleLegend["data"]     = "Data"
sampleLegend["Y3"]       = "Y_{3}"+(" signal MC" if args.noSelPrint else "")
sampleLegend["DY3"]      = "DY_{3}"+(" signal MC" if args.noSelPrint else "")
sampleLegend["DYp3"]     = "DY'_{3}"+(" signal MC" if args.noSelPrint else "")
sampleLegend["B3mL2"]    = "B_{3}-L_{2}"+(" signal MC" if args.noSelPrint else "")
sampleLegend["DYbb"]     = "DY(#mu#mu)+bb"
sampleLegend["ZToMuMu"]  = "DY(#mu#mu)"
sampleLegend["ttbar"]    = "t#bar{t}"
sampleLegend["tW+tZq"]   = "tW+tZq"
sampleLegend["TTX"]      = "t#bar{t}X"
sampleLegend["WW"]       = "WW"
sampleLegend["ZZ"]       = "ZZ"
sampleLegend["WZ"]       = "WZ"
sampleLegend["BFF"]      = "BFF"
sampleLegend["BFFdbs1p0"]= "BFFdbs1p0"
sampleLegend["DY_v7"]    = "DY(#mu#mu)"
sampleLegend["ttbar_v7"] = "t#bar{t}"

epsilon = 1e-6

def get_files(samples,year):

    sampleDict=OrderedDict()

    if year!="all" and year!="2016":
        years=[year]
    elif year=="2016":
        years=["2016nonAPV","2016APV"]
    else:
        years=["2016nonAPV","2016APV","2017","2018"]
    for tyear in years:
        for i,sample in enumerate(samples):
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF"in sample:
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


def get_nan_plots(sampleDict, plotname):
    plotDict=OrderedDict()
    groupedSamples = OrderedDict()
    tempGroups = OrderedDict()
    tempGroups["ttbar"]   = ["ttbar_2L2Nu","ttbar_SemiLeptonic","ttbar_Hadronic"]
    tempGroups["WW"] = ["WWTo1L1Nu2Q", "WWTo4Q", "WWTo2L2Nu"]
    tempGroups["WZ"] = ["WZTo1L1Nu2Q", "WZTo1L3Nu", "WZTo2Q2L","WZTo3LNu"]
    tempGroups["ZZ"] = ["ZZTo2L2Nu", "ZZTo2Nu2Q", "ZZTo2Q2L", "ZZTo4L", "ZZTo4Q"]
    tempGroups["tW+tZq"] = ["tW","tbarW","tZq"]
    tempGroups["TTX"]   = ["TTW","TTZ","TTHToNonbb","TTHTobb"]
    for sample in sampleDict.keys():
        if sample in tempGroups["ttbar"]:
            if "ttbar" not in groupedSamples.keys():
                groupedSamples["ttbar"]=[]
            groupedSamples["ttbar"].append(sample)
        elif sample in tempGroups["WW"]:
            if "WW" not in groupedSamples.keys():
                groupedSamples["WW"]=[]
            groupedSamples["WW"].append(sample)
        elif sample in tempGroups["WZ"]:
            if "WZ" not in groupedSamples.keys():
                groupedSamples["WZ"]=[]
            groupedSamples["WZ"].append(sample)
        elif sample in tempGroups["ZZ"]:
            if "ZZ" not in groupedSamples.keys():
                groupedSamples["ZZ"]=[]
            groupedSamples["ZZ"].append(sample)
        elif sample in tempGroups["tW+tZq"]:
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
                        for b in range(0, tplot.GetNbinsX()+2):
                            if numpy.isnan(tplot.GetBinContent(b)) or tplot.GetBinContent(b)<0.0 or not numpy.isfinite(tplot.GetBinContent(b)):
                                tplot.SetBinContent(b,0.0)
                                tplot.SetBinError(b,0.0)
                    else:
                        temphist = inFile.Get(plotname).Clone()
                        for b in range(0, temphist.GetNbinsX()+2):
                            if numpy.isnan(temphist.GetBinContent(b)) or temphist.GetBinContent(b)<0.0 or not numpy.isfinite(temphist.GetBinContent(b)):
                                temphist.SetBinContent(b,0.0)
                                temphist.SetBinError(b,0.0)
                        tplot.Add(temphist)
        plotDict[gsample] = tplot

    return plotDict


def get_plots(sampleDict, plotname):
    plotDict=OrderedDict()
    groupedSamples = OrderedDict()
    tempGroups = OrderedDict()
    tempGroups["ttbar"] = ["ttbar_2L2Nu","ttbar_SemiLeptonic","ttbar_Hadronic"]
    tempGroups["WW"] = ["WWTo1L1Nu2Q", "WWTo4Q", "WWTo2L2Nu"]
    tempGroups["WZ"] = ["WZTo1L1Nu2Q", "WZTo1L3Nu", "WZTo2Q2L","WZTo3LNu"]
    tempGroups["ZZ"] = ["ZZTo2L2Nu", "ZZTo2Nu2Q", "ZZTo2Q2L", "ZZTo4L", "ZZTo4Q"]
    tempGroups["tW+tZq"] = ["tW","tbarW","tZq"]
    tempGroups["TTX"]   = ["TTW","TTZ","TTHToNonbb","TTHTobb"]
    for sample in sampleDict.keys():
        if sample in tempGroups["ttbar"]:
            if "ttbar" not in groupedSamples.keys():
                groupedSamples["ttbar"]=[]
            groupedSamples["ttbar"].append(sample)
        elif sample in tempGroups["WW"]:
            if "WW" not in groupedSamples.keys():
                groupedSamples["WW"]=[]
            groupedSamples["WW"].append(sample)
        elif sample in tempGroups["WZ"]:
            if "WZ" not in groupedSamples.keys():
                groupedSamples["WZ"]=[]
            groupedSamples["WZ"].append(sample)
        elif sample in tempGroups["ZZ"]:
            if "ZZ" not in groupedSamples.keys():
                groupedSamples["ZZ"]=[]
            groupedSamples["ZZ"].append(sample)
        elif sample in tempGroups["tW+tZq"]:
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

        for b in range(0, tplot.GetNbinsX()+2):
            if tplot.GetBinContent(b)<0.0 or numpy.isnan(tplot.GetBinContent(b)) or not numpy.isfinite(tplot.GetBinContent(b)):
                tplot.SetBinContent(b,0.0)
                tplot.SetBinError(b,0.0)

        plotDict[gsample] = tplot

    return plotDict


def customize_plot(sample, plot, fillColor, lineColor, lineWidth, markerStyle, markerSize):

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

    ### Rebinning is unnecessary with histograms with varying bin size (unlike in the past). Thus, lines below are commented out
    #### Rebin fine-binned histograms
    #if plot.GetXaxis().GetBinUpEdge(plot.GetNbinsX())-plot.GetXaxis().GetBinLowEdge(1) > 500.0 and plot.GetXaxis().GetBinWidth(1)<10.0:
    #    if plot.GetNbinsX()%5==0:
    #        plot.Rebin(5)
    #    elif plot.GetNbinsX()%3==0:
    #        plot.Rebin(3)
    #    else:
    #        plot.Rebin(2)

    # Fine tuning plots after comments
    maxx = None
    if "_sel10" in plot.GetName():
        if "trkAbsIso" in plot.GetName():
            plot.Rebin(10)
        if "mmumu" in plot.GetName():
            plot.Rebin(4)
        if "bjet1_pt" in plot.GetName():
            maxx = 500.0
        if "bjet2_pt" in plot.GetName():
            maxx = 300.0
        if "bjet2_eta" in plot.GetName():
            plot.Rebin(2)
        if "nBTag2p" in plot.GetName():
            if "mu1_pt" in plot.GetName():
                plot.Rebin(2)
            if "mu2_pt" in plot.GetName():
                plot.Rebin(2)
            if "mu1_eta" in plot.GetName():
                plot.Rebin(2)
            if "mu2_eta" in plot.GetName():
                plot.Rebin(2)
            if "bjet1_eta" in plot.GetName():
                plot.Rebin(2)
            if "puppimet_pt" in plot.GetName():
                plot.Rebin(2)
            if "puppimet_phi" in plot.GetName():
                plot.Rebin(2)
        if maxx != None:
            tb = plot.GetXaxis().FindBin(maxx)
            sumc  = 0.0
            sume2 = 0.0
            for b in range(tb, plot.GetNbinsX()+1):
                sumc = sumc + plot.GetBinContent(b)
                sume2 = sume2 + (plot.GetBinError(b))*(plot.GetBinError(b))
                if b>tb:
                    plot.SetBinContent(b,0.0)
                    plot.SetBinError(b,0.0)
            plot.SetBinContent(tb,sumc)
            plot.SetBinError(tb,ROOT.TMath.Sqrt(sume2))

    maxx = 1000.0
    if "antisel10" in plot.GetName() and ("mmumu" in plot.GetName() or "mu1_pt" in plot.GetName() or "mu2_pt" in plot.GetName() or "bjet1_pt" in plot.GetName() or "bjet2_pt" in plot.GetName() or "nbtag" in plot.GetName()):
        if "mu1_pt" in plot.GetName():
            maxx = 700.0
        if "mu2_pt" in plot.GetName():
            maxx = 500.0
        if "bjet1_pt" in plot.GetName():
            maxx = 500.0
        if "bjet2_pt" in plot.GetName():
            maxx = 300.0
        if "nbtag" in plot.GetName():
            maxx = 3.0
        tb = plot.GetXaxis().FindBin(maxx)
        sumc  = 0.0
        sume2 = 0.0
        for b in range(tb, plot.GetNbinsX()+1):
            sumc = sumc + plot.GetBinContent(b)
            sume2 = sume2 + (plot.GetBinError(b))*(plot.GetBinError(b))
            if b>tb:
                plot.SetBinContent(b,0.0)
                plot.SetBinError(b,0.0)
        plot.SetBinContent(tb,sumc)
        plot.SetBinError(tb,ROOT.TMath.Sqrt(sume2))

    ### Remove spikes
    if sample!="data" and not "met_pt" in plot.GetName():
        for b in range(1, plot.GetNbinsX()+1):
            if plot.GetBinContent(b)>0 and plot.GetBinError(b)/plot.GetBinContent(b)>0.75:
                plot.SetBinContent(b,0.0)
                plot.SetBinError(b,0.0)

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
    latexSel.SetTextSize(0.03 if args.noSelPrint else 0.02-0.1*legoffset)
    latexSel.SetNDC(True)

    if testLumiRatio>0.0:
        scaleToTestLumi = testLumiRatio
        lumi = testLumiRatio*lumi

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

    if "cutflow" not in plotname:
        thissel=""
        if "sel8" in plotname or "sel9" in plotname or "sel10" in plotname:
            thissel = plotname.split("_")[len(plotname.split("_"))-4]
            if not "sel" in thissel:
                thissel = plotname.split("_")[len(plotname.split("_"))-5]
        elif "sel7" in plotname or "sel6" in plotname or "sel5" in plotname:
            thissel = plotname.split("_")[len(plotname.split("_"))-3]
            if not "sel" in thissel:
                thissel = plotname.split("_")[len(plotname.split("_"))-4]
        else:
            thissel = plotname.split("_")[len(plotname.split("_"))-2]
            if not "sel" in thissel:
                thissel = plotname.split("_")[len(plotname.split("_"))-3]
        if thissel not in args.selections:
            return(0)

        thismll=""
        if "sel8" in plotname or "sel9" in plotname or "sel10" in plotname:
            thismll = plotname.split("_")[len(plotname.split("_"))-3]
            if not "mll" in thismll:
                thismll = plotname.split("_")[len(plotname.split("_"))-4]
        elif "sel7" in plotname or "sel6" in plotname or "sel5" in plotname:
            thismll = plotname.split("_")[len(plotname.split("_"))-2]
            if not "mll" in thismll:
                thismll = plotname.split("_")[len(plotname.split("_"))-3]
        else:
            thismll = plotname.split("_")[len(plotname.split("_"))-1]
            if not "mll" in thismll:
                thismll = plotname.split("_")[len(plotname.split("_"))-2]
        if not args.plotMllSlices and 'inclusive' not in thismll:
            return(0)

        thisMuDet=""
        if "sel8" in plotname or "sel9" in plotname or "sel10" in plotname:
            thisMuDet = plotname.split("_")[len(plotname.split("_"))-1]
            if not ("MuDetAll" in thisMuDet or "BB" in thisMuDet or "BE" in thisMuDet or "EE" in thisMuDet):
                thisMuDet = plotname.split("_")[len(plotname.split("_"))-2]
        elif "sel7" in plotname or "sel6" in plotname or "sel5" in plotname:
            thisMuDet = plotname.split("_")[len(plotname.split("_"))-1]
            if not ("MuDetAll" in thisMuDet or "BB" in thisMuDet or "BE" in thisMuDet or "EE" in thisMuDet):
                thisMuDet = plotname.split("_")[len(plotname.split("_"))-2]
        else:
            thisMuDet = "All"
        if not args.plotMuonDetRegions and 'All' not in thisMuDet:
            return(0)

        if not args.plotProdModes and "ProdModes" in plotname.split("_")[len(plotname.split("_"))-1]:
            return(0)
    else:
        if not args.plotMllSlices and ("cutflow" in plotname and "mll" in plotname and "inclusive" not in plotname):
            return(0)
        if not args.plotMuonDetRegions and ("cutflow" in plotname and "MuDet" in plotname and "All" not in plotname):
            return(0)
        if not args.plotProdModes and "ProdModes" in plotname.split("_")[len(plotname.split("_"))-1]:
            return(0)

    # Get histograms
    plotDict = get_plots(sampleDict, plotname)
    curPlots=OrderedDict()

    totalSM = None
    lowToHighBinsCumulative = True
    for i,sample in enumerate(plotDict.keys()):
        # Signal
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample:
            model = sample.split("_")[0]
            mass = sample.split("_")[1].lstrip("M")
            if "mmumu" not in plotname and mass in massToExclude:
                continue
            if "mmumu" not in plotname:
                curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample],sampleFillColor[model],sampleLineColor[model]+i%len(args.signalMass),sampleLineWidth[model],sampleMarkerStyle[model],sampleMarkerSize[model]))
            else:
                curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample],sampleFillColor[model],sampleLineColor[model],sampleLineWidth[model],sampleMarkerStyle[model],sampleMarkerSize[model]))
            if testLumiRatio>0.0:
                curPlots[sample].Scale(scaleToTestLumi)
            if args.shape and curPlots[sample].Integral(0,-1)>0.0:
                if "cutflow" not in plotname:
                    curPlots[sample].Scale(1.0/curPlots[sample].Integral(0,-1))
                    if args.cumulative:
                        curPlots[sample] = plotUtils.GetCumulative(curPlots[sample],lowToHighBinsCumulative)
                else:
                    curPlots[sample].Scale(1.0/curPlots[sample].GetBinContent(1))
        # Data
        elif sample=="data": 
            if plotData:
                curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample],sampleMarkerStyle[sample],sampleMarkerSize[sample]))
                if args.shape and curPlots[sample].Integral(0,-1)>0.0:
                    if "cutflow" not in plotname:
                        curPlots[sample].Scale(1.0/curPlots[sample].Integral(0,-1))
                if args.cumulative:
                    curPlots[sample] = plotUtils.GetCumulative(curPlots[sample],lowToHighBinsCumulative)
        # Bkg
        else:
            curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample],sampleMarkerStyle[sample],sampleMarkerSize[sample]))
            if testLumiRatio>0.0:
                curPlots[sample].Scale(scaleToTestLumi)
            if not totalSM:
                totalSM = curPlots[sample].Clone("totalSM")
            else:
                totalSM.Add(curPlots[sample])

    if args.dataOnly:
        totalSM = curPlots["data"].Clone("totalSM")
    totalScale   = totalSM.Integral(0,-1)
    if args.cumulative:
        totalSM = plotUtils.GetCumulative(totalSM,lowToHighBinsCumulative)
    if "cutflow" in plotname:
        totalScale = totalSM.GetBinContent(1)
    if args.shape and totalScale>0.0:
        totalSM.Scale(1.0/totalScale)


    # Build stack
    stack = ROOT.THStack("stack","")
    if not args.dataOnly:
        for i,sample in enumerate(reversed(plotDict.keys())):
            # Bkg
            if not ("Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample or sample=="data"):
                if args.shape and totalScale>0.0:
                    curPlots[sample].Scale(1.0/totalScale)
                if args.cumulative:
                    curPlots[sample] = plotUtils.GetCumulative(curPlots[sample],lowToHighBinsCumulative)
                stack.Add(curPlots[sample])


    # Signal Scaling
    signalXSecScale = { }
    if (not logY) and args.signalScale and not args.shape:
        for sample in curPlots.keys():
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample:
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
    legendXOffsetNoSelPrint = 0.18 if args.noSelPrint else 0.0
    legendYOffsetNoSelPrint = 0.1 if (args.dataOnly and args.noSignal) else 0.0
    if args.data:
        legend = ROOT.TLegend(0.7-legendXOffsetNoSelPrint,0.6+legendYOffsetNoSelPrint,0.91,0.91)
        if args.dataOnly:
            legend = ROOT.TLegend(0.7-legendXOffsetNoSelPrint,0.7+legendYOffsetNoSelPrint,0.89,0.89)
    else:
        legend = ROOT.TLegend(0.7-legendXOffsetNoSelPrint,0.6+legendYOffsetNoSelPrint,0.89,0.89)
    if args.extendedLegend:
        if args.data:
            legend = ROOT.TLegend(0.6-legendXOffsetNoSelPrint,0.6+legendYOffsetNoSelPrint,0.91,0.91)
            if args.dataOnly:
                legend = ROOT.TLegend(0.6-legendXOffsetNoSelPrint,0.7+legendYOffsetNoSelPrint,0.89,0.89)
        else:
            legend = ROOT.TLegend(0.7-legendXOffsetNoSelPrint,0.6+legendYOffsetNoSelPrint,0.89,0.89)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    
    if args.extendedLegend:
        for sample in curPlots.keys():
            # Signal
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample:
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
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample:
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
    g_data_clone = ROOT.TGraphAsymmErrors()
    g_ratio = ROOT.TGraphAsymmErrors()
    g_ratio_unc = ROOT.TGraphAsymmErrors()
    g_ratio_signal = ROOT.TMultiGraph()

    h_axis = ROOT.TH1F()
    h_axis_ratio = ROOT.TH1F()
    h_axis = ROOT.TH1F("h_axis","", MCplot.GetNbinsX(), MCplot.GetXaxis().GetBinLowEdge(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
    if "cutflow" in plotname:
        for b in range(1, curPlots[curPlots.keys()[0]].GetNbinsX()+1):
            tlabel = curPlots[curPlots.keys()[0]].GetXaxis().GetBinLabel(b)
            h_axis.GetXaxis().SetBinLabel(b, tlabel)
    h_axis_ratio = ROOT.TH1F("h_axis_ratio","", MCplot.GetNbinsX(), MCplot.GetXaxis().GetBinLowEdge(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
    if logX and MCplot.GetXaxis().GetBinLowEdge(1) < epsilon:
        h_axis.GetXaxis().SetRangeUser(MCplot.GetXaxis().GetBinCenter(1)-0.25*MCplot.GetXaxis().GetBinWidth(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
        h_axis_ratio.GetXaxis().SetRangeUser(MCplot.GetXaxis().GetBinCenter(1)-0.25*MCplot.GetXaxis().GetBinWidth(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
    if "cutflow" in plotname:
        h_axis_ratio.GetXaxis().SetNdivisions(MCplot.GetNbinsX())
        h_axis_ratio.GetYaxis().SetNdivisions(505)

    # Fine tuning plots after comments
    maxx = None
    if "_sel10" in plotname:
        if "bjet1_pt" in plotname:
            maxx=500.0
        if "bjet2_pt" in plotname:
            maxx=300.0
        if maxx != None:
            h_axis.GetXaxis().SetRangeUser(h_axis.GetXaxis().GetBinLowEdge(1),maxx)
            h_axis_ratio.GetXaxis().SetRangeUser(h_axis_ratio.GetXaxis().GetBinLowEdge(1),maxx)

    if "antisel10" in plotname and ("mmumu" in plotname or "mu1_pt" in plotname or "mu2_pt" in plotname or "bjet1_pt" in plotname or "bjet2_pt" in plotname or "nbtag" in plotname):
        maxx = 1000.0
        if "mu1_pt" in plotname:
            maxx=700.0
        if "mu2_pt" in plotname:
            maxx=500.0
        if "bjet1_pt" in plotname:
            maxx=500.0
        if "bjet2_pt" in plotname:
            maxx=300.0
        if "nbtag" in plotname:
            maxx=3.0
        h_axis.GetXaxis().SetRangeUser(h_axis.GetXaxis().GetBinLowEdge(1),maxx)
        h_axis_ratio.GetXaxis().SetRangeUser(h_axis_ratio.GetXaxis().GetBinLowEdge(1),maxx)

    doRatio=False
    if plotData:
        if not args.dataOnly:
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

    if not plotData and args.shape and doSignalMCRatio:
        doRatio=True

        for i,sample in enumerate(plotDict.keys()):
            # Signal
            if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample:
                model = sample.split("_")[0] 
                mass = sample.split("_")[1].lstrip("M")
                if "mmumu" not in plotname and mass in massToExclude:
                    continue
                if "mmumu" not in plotname:
                    g_signal_temp = ROOT.TGraphAsymmErrors()
                    plotUtils.ConvertToPoissonGraph(curPlots[sample], g_signal_temp, drawZeros=False, drawXerr=False, drawYerr=False)
                    g_signal_temp.SetMarkerStyle(20)
                    g_signal_temp.SetMarkerSize(1.2)
                    g_signal_temp.SetLineWidth(1)

                    # draw with zero marker size so error bars drawn all the way to x axis in the case of 0 content
                    g_signal_temp_clone = g_signal_temp.Clone()
                    g_signal_temp_clone.SetMarkerSize(0.0)

                    g_ratio_signal_temp = ROOT.TGraphAsymmErrors()
                    plotUtils.GetPoissonRatioGraph(MCplot, curPlots[sample], g_ratio_signal_temp, drawZeros=False, drawXerr=False, drawYerr=False, useMCErr=False)
                    g_ratio_signal_temp.SetMarkerStyle(20)
                    g_ratio_signal_temp.SetMarkerSize(1.2)
                    g_ratio_signal_temp.SetMarkerColor(sampleLineColor[model]+i%len(args.signalMass))
                    g_ratio_signal_temp.SetLineWidth(1)
                    g_ratio_signal.Add(copy.deepcopy(g_ratio_signal_temp))
                else:
                    g_signal_temp = ROOT.TGraphAsymmErrors()
                    plotUtils.ConvertToPoissonGraph(curPlots[sample], g_signal_temp, drawZeros=False, drawXerr=False, drawYerr=False)
                    g_signal_temp.SetMarkerStyle(20)
                    g_signal_temp.SetMarkerSize(1.2)
                    g_signal_temp.SetLineWidth(1)

                    # draw with zero marker size so error bars drawn all the way to x axis in the case of 0 content
                    g_signal_temp_clone = g_signal_temp.Clone()
                    g_signal_temp_clone.SetMarkerSize(0.0)

                    g_ratio_signal_temp = ROOT.TGraphAsymmErrors()
                    plotUtils.GetPoissonRatioGraph(MCplot, curPlots[sample], g_ratio_signal_temp, drawZeros=False, drawXerr=False, drawYerr=False, useMCErr=False)
                    g_ratio_signal_temp.SetMarkerStyle(20)
                    g_ratio_signal_temp.SetMarkerSize(1.2)
                    g_ratio_signal_temp.SetMarkerColor(sampleLineColor[model])
                    g_ratio_signal_temp.SetLineWidth(1)
                    g_ratio_signal.Add(copy.deepcopy(g_ratio_signal_temp))

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
        minR=0.0
        maxR=2.0
        ty = numpy.array([])
        tmax=maxR
        if args.data:
            ty = g_ratio.GetY()
        else:
            ty = g_ratio_signal.GetY()
        if len(ty)>0:
            tmax = numpy.amax(ty)
        if tmax>maxR:
            maxR=tmax*1.05
        if maxR>5.0:
            minR=0.1
        h_axis_ratio.GetYaxis().SetRangeUser(minR,maxR)
        h_axis_ratio.SetMinimum(minR)
        h_axis_ratio.SetMaximum(maxR)
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

        maxxl = h_axis.GetXaxis().GetBinUpEdge(h_axis.GetNbinsX())
        maxx = maxxl
        if "antisel10" in plotname:
            if "mmumu" in plotname:
                maxx = h_axis.GetXaxis().GetBinUpEdge(h_axis.GetXaxis().FindBin(1000.0))
            if "mu1_pt" in plotname or "mu2_pt" in plotname:
                maxx = h_axis.GetXaxis().GetBinUpEdge(h_axis.GetXaxis().FindBin(500.0))
        maxxl = maxx

        #line = ROOT.TLine(h_axis.GetXaxis().GetBinLowEdge(1), 1.0, h_axis.GetXaxis().GetBinUpEdge(h_axis.GetNbinsX()), 1.0)
        line = ROOT.TLine(h_axis.GetXaxis().GetBinLowEdge(1), 1.0, maxxl, 1.0)

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
        if maxR>5.0:
            pads[1].SetLogy()
        pads[1].SetTickx()
        if logX:
            h_axis_ratio.GetXaxis().SetMoreLogLabels()
            pads[1].SetLogx()
        if plotData:
            h_axis_ratio.Draw("")
            g_ratio_unc.Draw("SAME,2")
            g_ratio.Draw("SAME,P0")
        else:
            g_ratio_signal.Draw("SAME,P0")
            g_ratio_signal.GetXaxis().SetLimits(h_axis.GetXaxis().GetBinLowEdge(1),h_axis.GetXaxis().GetBinUpEdge(h_axis.GetNbinsX()));
            g_ratio_signal.GetHistogram().GetXaxis().SetRangeUser(h_axis.GetXaxis().GetBinLowEdge(1),h_axis.GetXaxis().GetBinUpEdge(h_axis.GetNbinsX()));
            g_ratio_signal.GetHistogram().GetYaxis().SetRangeUser(0.,2.0);

            g_ratio_signal.GetHistogram().SetTitle(";;Signal / MC")
            g_ratio_signal.GetHistogram().GetYaxis().SetTitleSize(0.16)
            g_ratio_signal.GetHistogram().GetYaxis().SetTitleOffset(0.25)
            g_ratio_signal.GetHistogram().GetYaxis().SetLabelSize(0.12)
            g_ratio_signal.GetHistogram().GetYaxis().CenterTitle()
            g_ratio_signal.GetHistogram().GetYaxis().SetTickLength(0.02)

            g_ratio_signal.GetHistogram().GetXaxis().SetLabelSize(0)
            g_ratio_signal.GetHistogram().GetXaxis().SetTitle("")
            g_ratio_signal.GetHistogram().GetXaxis().SetTickSize(0.06)
            if logX:
                if MCplot.GetXaxis().GetBinLowEdge(1) < epsilon:
                    g_ratio_signal.GetHistogram().GetXaxis().SetRangeUser(MCplot.GetXaxis().GetBinCenter(1)-0.25*MCplot.GetXaxis().GetBinWidth(1), MCplot.GetXaxis().GetBinUpEdge(MCplot.GetNbinsX()))
                g_ratio_signal.GetHistogram().GetXaxis().SetMoreLogLabels()
                pads[1].SetLogx()

        #
        line.SetLineStyle(2)
        line.SetLineColor(sampleLineColor["data"])
        line.SetLineWidth(1)
        line.Draw("SAME")
        #
        #pads[1].RedrawAxis()
        pads[1].Modified();
        pads[1].Update();

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
    if args.dataOnly:
        h_axis.GetYaxis().SetTitleOffset(1.35)
    h_axis.GetXaxis().SetTitleSize(0.04)
    h_axis.GetXaxis().SetTitleOffset(1.25)
    if "cutflow" in plotname:
        h_axis.GetXaxis().SetLabelSize(0.023)
    else:
        h_axis.GetXaxis().SetTitle(MCplot.GetXaxis().GetTitle())
    if args.shape:
        h_axis.GetYaxis().SetTitle("A.U.")
    else:
        h_axis.GetYaxis().SetTitle(MCplot.GetYaxis().GetTitle())
    h_axis.GetYaxis().SetLabelSize(0.03)
    if not args.shape:
        h_axis.GetYaxis().SetMaxDigits(3)
    h_axis.Draw("")
    if not args.dataOnly:
        stack.Draw("HIST,SAME")
        g_unc.Draw("SAME,2")
    histMax = 0.0
    if plotData:
        if histMax < curPlots["data"].GetMaximum():
            histMax = curPlots["data"].GetMaximum()
        g_data.Draw("P,SAME")
        g_data_clone.Draw("P,SAME")
    for sample in curPlots.keys():
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample:
            if histMax < curPlots[sample].GetMaximum(): 
                histMax = curPlots[sample].GetMaximum()
            curPlots[sample].Draw("HIST,SAME")

    if histMax < MCplot.GetMaximum(): 
        histMax = MCplot.GetMaximum()
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
        whichMuDet = ""
        whichsel = ""
        if "sel8" in plotname or "sel9" in plotname or "sel10" in plotname:
            if "ProdModes" in plotname.split("_")[len(plotname.split("_"))-1]:
                whichMuDet = plotname.split("_")[len(plotname.split("_"))-2]
                whichnb  = plotname.split("_")[len(plotname.split("_"))-3]
                whichmll = plotname.split("_")[len(plotname.split("_"))-4]
                whichsel = plotname.split("_")[len(plotname.split("_"))-5]
            else:
                whichMuDet = plotname.split("_")[len(plotname.split("_"))-1]
                whichnb  = plotname.split("_")[len(plotname.split("_"))-2]
                whichmll = plotname.split("_")[len(plotname.split("_"))-3]
                whichsel = plotname.split("_")[len(plotname.split("_"))-4]
        elif "sel7" in plotname or "sel6" in plotname or "sel5" in plotname:
            if "ProdModes" in plotname.split("_")[len(plotname.split("_"))-1]:
                whichMuDet = plotname.split("_")[len(plotname.split("_"))-2]
                whichmll = plotname.split("_")[len(plotname.split("_"))-3]
                whichsel = plotname.split("_")[len(plotname.split("_"))-4]
            else:
                whichMuDet = plotname.split("_")[len(plotname.split("_"))-1]
                whichmll = plotname.split("_")[len(plotname.split("_"))-2]
                whichsel = plotname.split("_")[len(plotname.split("_"))-3]
        else:
            if "ProdModes" in plotname.split("_")[len(plotname.split("_"))-1]:
                whichmll = plotname.split("_")[len(plotname.split("_"))-2]
                whichsel = plotname.split("_")[len(plotname.split("_"))-3]
            else:
                whichmll = plotname.split("_")[len(plotname.split("_"))-1]
                whichsel = plotname.split("_")[len(plotname.split("_"))-2]
        ts = 0
        if args.noSelPrint:
            if nsel[whichsel]>=8:
                ts = ts+1
                if args.data:
                    latexSel.DrawLatex((0.20 if args.dataOnly else 0.19)+3*legoffset, (0.87 if args.dataOnly else 0.88)-ts*(0.03-legoffset), nbbin[whichnb])
                else:
                    latexSel.DrawLatex(0.21+3*legoffset, 0.86-ts*(0.03-legoffset), nbbin[whichnb])
        else:
            for s in range(0,nsel[whichsel]+1):
                if 'inclusive' not in whichmll and s==8:
                    continue
                if '1p' not in whichnb and s==10:
                    continue
                if 'antisel10' in whichsel and s==12:
                    continue;
                if 'anti' not in whichsel and 'sel10' in whichsel and s==13:
                    continue;    
                ts = ts+1
                if args.data:
                    latexSel.DrawLatex((0.42 if args.dataOnly else 0.45)+3*legoffset, (0.9 if args.dataOnly else 0.91)-ts*(0.03-legoffset), sels[s])
                else:
                    latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), sels[s])
            if 'inclusive' not in whichmll and nsel[whichsel]>=8:
                ts = ts+1
                if args.data:
                    latexSel.DrawLatex((0.42 if args.dataOnly else 0.45)+3*legoffset, (0.9 if args.dataOnly else 0.91)-ts*(0.03-legoffset), mllbin[whichmll])
                else:
                    latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), mllbin[whichmll])
            if 'All' not in whichMuDet and nsel[whichsel]>=8:
                ts = ts+1
                if args.data:
                    latexSel.DrawLatex((0.42 if args.dataOnly else 0.45)+3*legoffset, (0.9 if args.dataOnly else 0.91)-ts*(0.03-legoffset), MuDetbin[whichMuDet])
                else:
                    latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), MuDetbin[whichMuDet])
            if '1p' not in whichnb and nsel[whichsel]>=10:
                ts = ts+1
                if args.data:
                    latexSel.DrawLatex((0.42 if args.dataOnly else 0.45)+3*legoffset, (0.9 if args.dataOnly else 0.91)-ts*(0.03-legoffset), nbbin[whichnb])
                else:
                    latexSel.DrawLatex(0.40+3*legoffset, 0.89-ts*(0.03-legoffset), nbbin[whichnb])


    # Print and save
    extension = "_"+year
    if plotData:
        if args.dataOnly:
            extension = extension+"_data"
        else:
            extension = extension+"_mcdata"
    else:
        extension = extension+"_sb"
    if logX:
        extension = extension+"_logX"
    if logY:
        extension = extension+"_logY"
    if args.shape:
        extension = extension+"_areaNormalized"
    if args.cumulative:
        extension = extension+"_cumulative"
    
    canvas.SaveAs(args.outDir + plotname + extension + ".pdf" if args.pdf else ".png")



# Main
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)

for year in args.years:
    lumi=0.0 #fb^-1
    if year == "2018":
        lumi = 59.83
    elif year == "2017":
        lumi = 41.48
    elif year == "2016APV":
        lumi = 19.5
    elif year == "2016nonAPV":
        lumi = 16.8
    elif year == "2016":
        lumi = 19.5+16.8
    elif year == "all":
        lumi = 59.83 + 41.48 + 19.5 + 16.8
    # Open files
    sampleDict=get_files(samples,year)
    # List of plots
    listofplots = []
    listfile = sampleDict[sampleDict.keys()[0]][0]
    listkeys = listfile.GetListOfKeys()
    size = listkeys.GetSize()
    for i in range(0,size):
        if "TH1" in listkeys.At(i).GetClassName():
            listofplots.append(listkeys.At(i).GetName())
    toexclude = []
    for plot in listofplots:
        if plot in toexclude:
            continue
        draw_plot(sampleDict, plot, False, False, args.data, False, lumi, year)
        draw_plot(sampleDict, plot, True , False, args.data, False, lumi, year)
        if ("pt" in plot) or ("mmumu" in plot) or ("mlb" in plot) or ("mbb" in plot) or ("RelIso" in plot) or ("dxy" in plot) or ("dz" in plot):
            draw_plot(sampleDict, plot, False, True, args.data, False, lumi, year)
            draw_plot(sampleDict, plot, True , True, args.data, False, lumi, year)
