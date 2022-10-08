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
parser.add_argument("--partialUnblinding", default=False, action="store_true", help="Plot 10% of data")
parser.add_argument("--signalMass", default=[], nargs="+", help="Signal mass points to plot. Default: All")
parser.add_argument("--signalScale", default=True, help="Scale signal up for display")
parser.add_argument("--shape", default=False, action="store_true", help="Shape normalization")
parser.add_argument("--cumulative", default=False, action="store_true", help="Cumulative distributions")
parser.add_argument("--extendedLegend", default=False, action="store_true", help="Write integrals in TLegend")
parser.add_argument("--selections", default=[], nargs="+", help="List of selections to be plotted. Default: only final selection ('sel10')")
parser.add_argument("--years", default=[], nargs="+", help="List of years to be plotted. Default: all years")
parser.add_argument("--plotMllSlices", default=False, action="store_true", help="Plot in slices of mll. Default: False")
parser.add_argument("--mllBinningForBFF", default=False, action="store_true", help="Plot in slices of mll for BFF analysis comparison. Default: False")
parser.add_argument("--plotMuonDetRegions", default=False, action="store_true", help="Plot muon divided by detector regions. Default: False")
parser.add_argument("--plotProdModes", default=False, action="store_true", help="Plot signal samples split in production modes (ss, sb, bb). Bkgs cannot be splt in a simlar way and are plotted inclusively. Default: False")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

if not os.path.exists(args.outDir):
    os.makedirs(args.outDir)
os.system('cp '+os.environ.get("PWD")+'/utils/index.php '+args.outDir)

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
sels.append("m_{#mu#mu}>175 GeV")
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
nbbin["nBTag0"]="N_{b-tag}= 0 (p_{T}>20 GeV, M WP)"
nbbin["nBTag1p"]="N_{b-tag}#geq 1 (p_{T}>20 GeV, T+Ms WP)"
nbbin["nBTag1"]="N_{b-tag}= 1 (p_{T}>20 GeV, T WP)"
nbbin["nBTag2p"]="N_{b-tag}#geq 2 (p_{T}>20 GeV, T+Ms WP)"

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
#samples.append("Y3")
#samples.append("DY3")
#samples.append("DYp3")
#samples.append("B3mL2")
# SM MC
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
samples.append("WW")
samples.append("ZZ")
samples.append("WZ")
# PreUL NanoAODv7 samples for BFF comparison
# Signal MC
#samples.append("BFF")
#samples.append("BFFdbs1p0")
#samples.append("DY_v7")
#samples.append("ttbar_v7")

epsilon = 1e-6


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

plotData=args.data
if plotData:
    cmsExtra="Preliminary"
else:
    cmsExtra="Simulation"


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
    tempGroups["tW+tZq"] = ["tW","tbarW","tZq"]
    tempGroups["TTX"]   = ["TTW","TTZ","TTHToNonbb","TTHTobb"]
    for sample in sampleDict.keys():
        if sample in tempGroups["ttbar"]:
            if "ttbar" not in groupedSamples.keys():
                groupedSamples["ttbar"]=[]
            groupedSamples["ttbar"].append(sample)
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
    tempGroups["tW+tZq"] = ["tW","tbarW","tZq"]
    tempGroups["TTX"]   = ["TTW","TTZ","TTHToNonbb","TTHTobb"]
    for sample in sampleDict.keys():
        if sample in tempGroups["ttbar"]:
            if "ttbar" not in groupedSamples.keys():
                groupedSamples["ttbar"]=[]
            groupedSamples["ttbar"].append(sample)
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


#def customize_plot(sample, plot, fillColor, lineColor, lineWidth, markerStyle, markerSize):
def customize_plot(sample, plot):

    #error = ROOT.TMath.Sqrt(plot.GetBinError(0)*plot.GetBinError(0)+plot.GetBinError(1)*plot.GetBinError(1))
    #plot.SetBinContent(1, plot.GetBinContent(1) + plot.GetBinContent(0))
    #plot.SetBinError(1, error)
    #plot.SetBinContent(0, 0.0)
    #plot.SetBinError(0, 0.0)

    #error = ROOT.TMath.Sqrt(plot.GetBinError(plot.GetNbinsX()+1)*plot.GetBinError(plot.GetNbinsX()+1)+plot.GetBinError(plot.GetNbinsX())*plot.GetBinError(plot.GetNbinsX()))
    #plot.SetBinContent(plot.GetNbinsX(), plot.GetBinContent(plot.GetNbinsX()+1) + plot.GetBinContent(plot.GetNbinsX()))
    #plot.SetBinError(plot.GetNbinsX(), error)
    #plot.SetBinContent(plot.GetNbinsX()+1, 0.0)
    #plot.SetBinError(plot.GetNbinsX()+1, 0.0)

    #### Rebinning is unnecessary with histograms with varying bin size (unlike in the past). Thus, lines below are commented out
    ##### Rebin fine-binned histograms
    ##if plot.GetXaxis().GetBinUpEdge(plot.GetNbinsX())-plot.GetXaxis().GetBinLowEdge(1) > 500.0 and plot.GetXaxis().GetBinWidth(1)<10.0:
    ##    if plot.GetNbinsX()%5==0:
    ##        plot.Rebin(5)
    ##    elif plot.GetNbinsX()%3==0:
    ##        plot.Rebin(3)
    ##    else:
    ##        plot.Rebin(2)

    #maxx = 1000.0
    #if "antisel10" in plot.GetName() and ("mmumu" in plot.GetName() or "mu1_pt" in plot.GetName() or "mu2_pt" in plot.GetName()) or "bjet1_pt" in plot.GetName() or "bjet2_pt" in plot.GetName() or "nbtag" in plot.GetName():
    #    if "mu1_pt" in plot.GetName():
    #        maxx = 700.0
    #    if "mu2_pt" in plot.GetName():
    #        maxx = 500.0
    #    if "bjet1_pt" in plot.GetName():
    #        maxx = 500.0
    #    if "bjet2_pt" in plot.GetName():
    #        maxx = 300.0
    #    if "nbtag" in plot.GetName():
    #        maxx = 3.0
    #    tb = plot.GetXaxis().FindBin(maxx)
    #    sumc  = 0.0
    #    sume2 = 0.0
    #    for b in range(tb, plot.GetNbinsX()+1):
    #        sumc = sumc + plot.GetBinContent(b)
    #        sume2 = sume2 + (plot.GetBinError(b))*(plot.GetBinError(b))
    #        if b>tb:
    #            plot.SetBinContent(b,0.0)
    #            plot.SetBinError(b,0.0)
    #    plot.SetBinContent(tb,sumc)
    #    plot.SetBinError(tb,ROOT.TMath.Sqrt(sume2))

    #### Remove spikes
    #if sample!="data" and not "met_pt" in plot.GetName():
    #    for b in range(1, plot.GetNbinsX()+1):
    #        if plot.GetBinContent(b)>0 and plot.GetBinError(b)/plot.GetBinContent(b)>0.75:
    #            plot.SetBinContent(b,0.0)
    #            plot.SetBinError(b,0.0)

    return plot


def draw_onePlot(plotname, samplename, logZ, logY, logX, h_axis, hist, histMax, legend, canvas, yearenergy):
    h_axis.Draw("")
    hist.SetTitle(samplename)
    hist.Draw("COLZ")

    if histMax == 0:
        histMax = hist.GetMaximum()
    if logY:
        histMax = histMax*1e3
        h_axis.SetMinimum(1e-3)
    h_axis.SetMaximum(1.1*histMax)

    legend.Draw()
    canvas.Update()
    canvas.RedrawAxis()


    # Draw CMS headers
    expoffset=0.03
    if logY or 1.1*histMax<1000.0:
        expoffset=0
    latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
    latexCMS.DrawLatex(0.11,0.91+expoffset,"CMS");
    latexCMSExtra.DrawLatex(0.20,0.91+expoffset, cmsExtra);


    # Print and save
    extension = "_"+year
    if logX:
        extension = extension+"_logX"
    if logY:
        extension = extension+"_logY"
    if logZ:
        extension = extension+"_logZ"
    if args.shape:
        extension = extension+"_areaNormalized"
    
    canvas.SaveAs(args.outDir + plotname + "/" + plotname + extension + "_" + samplename + ".png")

    return histMax


def draw_plot(sampleDict, plotname, logZ=True, logY=True, logX=False, doRatio=True, lumi=59.83, year="2018"):

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

    if not os.path.exists(args.outDir+plotname):
      os.makedirs(args.outDir+plotname)
    os.system('cp '+os.environ.get("PWD")+'/utils/index.php '+args.outDir+plotname)

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
                curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample]))
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
                curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample]))
                if args.shape and curPlots[sample].Integral(0,-1)>0.0:
                    if "cutflow" not in plotname:
                        curPlots[sample].Scale(1.0/curPlots[sample].Integral(0,-1))
                if args.cumulative:
                    curPlots[sample] = plotUtils.GetCumulative(curPlots[sample],lowToHighBinsCumulative)
        # Bkg
        else:
            curPlots[sample] = copy.deepcopy(customize_plot(sample,plotDict[sample]))
            if testLumiRatio>0.0:
                curPlots[sample].Scale(scaleToTestLumi)
            if not totalSM:
                totalSM = curPlots[sample].Clone("totalSM")
            else:
                totalSM.Add(curPlots[sample])

    totalScale   = totalSM.Integral(0,-1,0,-1)
    if args.shape and totalScale>0.0:
        totalSM.Scale(1.0/totalScale)


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
    

    # Define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    plot2D = copy.deepcopy(totalSM)

    h_axis = ROOT.TH2F()
    h_axis = ROOT.TH2F("h_axis","", plot2D.GetNbinsX(), plot2D.GetXaxis().GetBinLowEdge(1), plot2D.GetXaxis().GetBinUpEdge(plot2D.GetNbinsX()), plot2D.GetNbinsY(), plot2D.GetYaxis().GetBinLowEdge(1), plot2D.GetYaxis().GetBinUpEdge(plot2D.GetNbinsY()))
    if logY and plot2D.GetYaxis().GetBinLowEdge(1) < epsilon:
        h_axis.GetYaxis().SetRangeUser(plot2D.GetYaxis().GetBinCenter(1)-0.25*plot2D.GetYaxis().GetBinWidth(1), plot2D.GetYaxis().GetBinUpEdge(plot2D.GetNbinsY()))
        h_axis_ratio.GetYaxis().SetRangeUser(plot2D.GetYaxis().GetBinCenter(1)-0.25*plot2D.GetYaxis().GetBinWidth(1), plot2D.GetYaxis().GetBinUpEdge(plot2D.GetNbinsY()))
    if logX and plot2D.GetXaxis().GetBinLowEdge(1) < epsilon:
        h_axis.GetXaxis().SetRangeUser(plot2D.GetXaxis().GetBinCenter(1)-0.25*plot2D.GetXaxis().GetBinWidth(1), plot2D.GetXaxis().GetBinUpEdge(plot2D.GetNbinsX()))
        h_axis_ratio.GetXaxis().SetRangeUser(plot2D.GetXaxis().GetBinCenter(1)-0.25*plot2D.GetXaxis().GetBinWidth(1), plot2D.GetXaxis().GetBinUpEdge(plot2D.GetNbinsX()))

    if logY:
        h_axis.GetYaxis().SetMoreLogLabels()
        canvas.SetLogy()
    if logX:
        h_axis.GetXaxis().SetMoreLogLabels()
        canvas.SetLogx()

    h_axis.GetYaxis().SetTitleSize(0.04)
    h_axis.GetYaxis().SetTitleOffset(1.25)
    h_axis.GetYaxis().SetTitle(totalSM.GetYaxis().GetTitle())
    h_axis.GetXaxis().SetTitleSize(0.04)
    h_axis.GetXaxis().SetTitleOffset(1.25)
    h_axis.GetXaxis().SetTitle(totalSM.GetXaxis().GetTitle())
    if args.shape:
        h_axis.GetYaxis().SetTitle("A.U.")
        h_axis.GetXaxis().SetTitle("A.U.")
    else:
        h_axis.GetYaxis().SetTitle(totalSM.GetYaxis().GetTitle())
        h_axis.GetXaxis().SetTitle(totalSM.GetXaxis().GetTitle())
    h_axis.GetZaxis().SetLabelSize(0.03)
    if not args.shape:
        h_axis.GetZaxis().SetMaxDigits(3)

    histMax = 0.0
    histMax = draw_onePlot(plotname, "totalSM", logZ, logY, logX, h_axis, totalSM, histMax, legend, canvas, yearenergy)
    for sample in curPlots.keys():
        draw_onePlot(plotname, sample, logZ, logY, logX, h_axis, curPlots[sample], histMax, legend, canvas, yearenergy)
    dataOverTotalSM = copy.deepcopy(curPlots["data"])
    dataOverTotalSM.Divide(totalSM)
    draw_onePlot(plotname, "dataOverTotalSM", logZ, logY, logX, h_axis, dataOverTotalSM, histMax, legend, canvas, yearenergy)



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
        if "TH2" in listkeys.At(i).GetClassName():
            listofplots.append(listkeys.At(i).GetName())
    toexclude = []
    for plot in listofplots:
        if plot in toexclude:
            continue
        draw_plot(sampleDict, plot, False, False, False, False, lumi, year)
        #draw_plot(sampleDict, plot, True , False, False, lumi, year)
        #if ("pt" in plot) or ("mmumu" in plot) or ("mlb" in plot) or ("mbb" in plot) or ("RelIso" in plot) or ("dxy" in plot) or ("dz" in plot):
        #    draw_plot(sampleDict, plot, False, True, False, lumi, year)
        #    draw_plot(sampleDict, plot, True , True, False, lumi, year)
