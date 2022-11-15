from collections import OrderedDict
import ROOT
import math
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
parser.add_argument("--shape", default=False, action="store_true", help="Shape normalization") # Not properly implemented (yet?)
parser.add_argument("--cumulative", default=False, action="store_true", help="Cumulative distributions") # Not properly implemented (yet?)
parser.add_argument("--projectY", default=[], nargs=2, type=float, help="Plot Y projection, giving the lower and upper boundaries for the projection")
parser.add_argument("--projectX", default=[], nargs=2, type=float, help="Plot X projection, giving the lower and upper boundaries for the projection")
parser.add_argument("--selections", default=[], nargs="+", help="List of selections to be plotted. Default: only final selection ('sel10')")
parser.add_argument("--years", default=[], nargs="+", help="List of years to be plotted. Default: all years")
parser.add_argument("--plot", default=[], nargs="+", help="List of histograms to be plotted. Default: all")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

if not os.path.exists(args.outDir):
  os.makedirs(args.outDir)
os.system('cp '+os.environ.get("PWD")+'/utils/index.php '+args.outDir)

plotData=args.data

projectY=True
if len(args.projectY)==0:
  projectY=False

projectX=True
if len(args.projectX)==0:
  projectX=False

if len(args.selections)==0:
  args.selections = ["sel10"]

if len(args.years)==0:
  args.years = ["all"]

# Do signal/MC ratio
doSignalMCRatio = False

# Use fixed ratio axis
useFixedRatio = False

# Do log scales:
doLogX = False
doLogY = False

# Samples
samples=[]
if plotData:
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
#sampleFillColor["BFF"]      = None
#sampleFillColor["BFFdbs1p0"]= None
#sampleFillColor["DY_v7"]    = ROOT.kGreen+1
#sampleFillColor["ttbar_v7"] = ROOT.kAzure+1

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
#sampleLineColor["BFF"]      = ROOT.kViolet
#sampleLineColor["BFFdbs1p0"]= ROOT.kRed
#sampleLineColor["DY_v7"]    = None
#sampleLineColor["ttbar_v7"] = None

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
#sampleLineWidth["BFF"]      = 2
#sampleLineWidth["BFFdbs1p0"]= 2
#sampleLineWidth["DY_v7"]    = 0
#sampleLineWidth["ttbar_v7"] = 0

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
#sampleMarkerStyle["BFF"]      = None
#sampleMarkerStyle["BFFdbs1p0"]= None
#sampleMarkerStyle["DY_v7"]    = None
#sampleMarkerStyle["ttbar_v7"] = None

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
#sampleMarkerSize["BFF"]      = None
#sampleMarkerSize["BFFdbs1p0"]= None
#sampleMarkerSize["DY_v7"]    = None
#sampleMarkerSize["ttbar_v7"] = None

sampleLegend=dict()
sampleLegend["data"]     = "Data"
sampleLegend["Y3"]       = "Y3"
sampleLegend["DY3"]      = "DY3"
sampleLegend["DYp3"]     = "DYp3"
sampleLegend["B3mL2"]    = "B3mL2"
sampleLegend["DYbb"]     = "DY(#mu#mu)+bb"
sampleLegend["ZToMuMu"]  = "DY(#mu#mu)"
sampleLegend["ttbar"]    = "t#bar{t}"
sampleLegend["tW+tZq"]   = "tW+tZq"
sampleLegend["TTX"]      = "t#bar{t}X"
sampleLegend["WW"]       = "WW"
sampleLegend["ZZ"]       = "ZZ"
sampleLegend["WZ"]       = "WZ"
#sampleLegend["BFF"]      = "BFF"
#sampleLegend["BFFdbs1p0"]= "BFFdbs1p0"
#sampleLegend["DY_v7"]    = "DY(#mu#mu)"
#sampleLegend["ttbar_v7"] = "t#bar{t}"

epsilon = 1e-6

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
#sels.append("m_{#mu#mu}>175 GeV")
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
nbbin["nBTag0"]="N_{b-tag}= 0 (p_{T}>20 GeV, M WP)"
nbbin["nBTag1p"]="N_{b-tag}#geq 1 (p_{T}>20 GeV, T+Ms WP)"
nbbin["nBTag1"]="N_{b-tag}= 1 (p_{T}>20 GeV, T WP)"
nbbin["nBTag2p"]="N_{b-tag}#geq 2 (p_{T}>20 GeV, T+Ms WP)"

# Labels
latex = ROOT.TLatex()
latex.SetTextFont(42)
latex.SetTextAlign(31)
latex.SetTextSize(0.04)
latex.SetNDC(True)

latexZaxis = ROOT.TLatex()
latexZaxis.SetTextFont(42)
latexZaxis.SetTextAlign(31)
latexZaxis.SetTextSize(0.035)
latexZaxis.SetNDC(True)

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

    #error = ROOT.TMath.Sqrt(plot.GetBinError(0)*plot.GetBinError(0)+plot.GetBinError(1)*plot.GetBinError(1))
    #plot.SetBinContent(1, plot.GetBinContent(1) + plot.GetBinContent(0))
    #plot.SetBinError(1, error)
    #plot.SetBinContent(0, 0.0)
    #plot.SetBinError(0, 0.0)

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

    return plot

def customize_plot2d(sample, plot):
  plot.Rebin2D(5)
  return plot


def draw_onePlot(plotname, samplename, logZ, logY, logX, hist, canvas, yearenergy):
  histMax = hist.GetMaximum()
  exp = None
  if histMax > 0.0 and not logZ:
    exp = int(math.floor(math.log10(histMax)))
    if exp!=0:
      hist.Scale(pow(10,-exp))

  hist.SetTitle(samplename)
  hist.Draw("COLZ")
  canvas.Update()

  # Draw CMS headers
  expoffset=0.00
  yoffset=0.00
  zoffset=0.00
  if logY or 1.1*hist.GetYaxis().GetXmax()>100.0:
    yoffset=0.07
  if logX or 1.1*hist.GetXaxis().GetXmax()>100.0:
    zoffset=0.05
  latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
  latexCMS.DrawLatex(0.11+yoffset,0.91+expoffset,"CMS");
  latexCMSExtra.DrawLatex(0.20+yoffset,0.91+expoffset, cmsExtra);

  if logY and hist.GetYaxis().GetBinLowEdge(1) < epsilon:
      hist.GetYaxis().SetRangeUser(hist.GetYaxis().GetBinCenter(1)-0.25*hist.GetYaxis().GetBinWidth(1), hist.GetYaxis().GetBinUpEdge(hist.GetNbinsY()))
      h_axis_ratio.GetYaxis().SetRangeUser(hist.GetYaxis().GetBinCenter(1)-0.25*hist.GetYaxis().GetBinWidth(1), hist.GetYaxis().GetBinUpEdge(hist.GetNbinsY()))
  if logX and hist.GetXaxis().GetBinLowEdge(1) < epsilon:
      hist.GetXaxis().SetRangeUser(hist.GetXaxis().GetBinCenter(1)-0.25*hist.GetXaxis().GetBinWidth(1), hist.GetXaxis().GetBinUpEdge(hist.GetNbinsX()))
      h_axis_ratio.GetXaxis().SetRangeUser(hist.GetXaxis().GetBinCenter(1)-0.25*hist.GetXaxis().GetBinWidth(1), hist.GetXaxis().GetBinUpEdge(hist.GetNbinsX()))

  if logZ:
      canvas.SetLogz()
  if logY:
      canvas.SetLogy()
  if logX:
      canvas.SetLogx()

  hist.GetYaxis().SetTitleSize(0.03)
  hist.GetYaxis().SetTitleOffset(1.55)
  hist.GetYaxis().SetTitle(hist.GetYaxis().GetTitle())
  hist.GetYaxis().SetMaxDigits(2)

  hist.GetXaxis().SetTitleSize(0.03)
  hist.GetXaxis().SetTitleOffset(1.55)
  hist.GetXaxis().SetTitle(hist.GetXaxis().GetTitle())
  hist.GetXaxis().SetMaxDigits(2)

  if args.shape:
      hist.GetYaxis().SetTitle("A.U.")
      hist.GetXaxis().SetTitle("A.U.")
  else:
      hist.GetYaxis().SetTitle(hist.GetYaxis().GetTitle())
      hist.GetXaxis().SetTitle(hist.GetXaxis().GetTitle())

  hist.GetZaxis().SetLabelSize(0.03)

  hist.SetMinimum(0.0)
  if logZ:
    histMax = histMax*1e3
    hist.SetMinimum(1e-3)

  palette = hist.GetListOfFunctions().FindObject("palette")
  if palette:
    palette.SetX2NDC(palette.GetX2NDC()-0.02)
    palette.SetY1NDC(palette.GetY1NDC()+zoffset)
    if exp and not logZ:
      hist.SetMaximum(1.1*histMax*pow(10,-exp))
      latexZaxis.DrawLatex(0.98, 0.91, "#times10^{"+str(int(exp))+"}")
      hist.GetZaxis().SetRangeUser(0.0,1.1*histMax*pow(10,-exp))
    hist.GetZaxis().SetMaxDigits(2)

  canvas.Update()
  canvas.RedrawAxis()

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
  
  canvas.SaveAs(args.outDir + "/" + plotname + extension + "_" + samplename + ".png")


def draw_proj(plotname, proj_BG, stack_BG, proj_MC, proj_data, logY, logX, canvas, yearenergy, titleExt):
  g_unc = ROOT.TGraphAsymmErrors()
  g_ratio_unc = ROOT.TGraphAsymmErrors()
  for b in range(1,proj_MC.GetNbinsX()+1):
    thisPoint = g_ratio_unc.GetN()
    yerror = proj_MC.GetBinError(b)
    g_unc.SetPoint(thisPoint, proj_MC.GetBinCenter(b), proj_MC.GetBinContent(b))
    g_unc.SetPointError(thisPoint, 0.5*proj_MC.GetBinWidth(b), 0.5*proj_MC.GetBinWidth(b), yerror, yerror)
    if proj_MC.GetBinContent(b)>0.0:
      yerror = yerror/proj_MC.GetBinContent(b)
    else:
      yerror = 0.0
    g_ratio_unc.SetPoint(thisPoint, proj_MC.GetBinCenter(b), 1.0)
    g_ratio_unc.SetPointError(thisPoint, 0.5*proj_MC.GetBinWidth(b), 0.5*proj_MC.GetBinWidth(b), yerror, yerror)
  g_unc.SetFillStyle(3244)
  g_unc.SetFillColor(ROOT.kGray+3)
  g_ratio_unc.SetFillStyle(1001)
  g_ratio_unc.SetFillColor(ROOT.kGray)

  pads = []
  h_axis_ratio = ROOT.TH1F()
  h_axis_ratio = ROOT.TH1F("h_axis_ratio","",  proj_MC.GetNbinsX(),  proj_MC.GetXaxis().GetBinLowEdge(1),  proj_MC.GetXaxis().GetBinUpEdge(proj_MC.GetNbinsX()))
  if plotData:
    g_data = ROOT.TGraphAsymmErrors()
    g_data_clone = ROOT.TGraphAsymmErrors()
    plotUtils.ConvertToPoissonGraph(proj_data, g_data, drawZeros=False, drawXerr=False)
    g_data.SetMarkerStyle(20)
    g_data.SetMarkerSize(1.2)
    g_data.SetLineWidth(1)
    # draw with zero marker size so error bars drawn all the way to x axis in the case of 0 content
    g_data_clone = g_data.Clone()
    g_data_clone.SetMarkerSize(0.0)

    g_ratio = ROOT.TGraphAsymmErrors()
    plotUtils.GetPoissonRatioGraph(proj_MC, proj_data, g_ratio, drawZeros=False, drawXerr=False, useMCErr=False)
    g_ratio.SetMarkerStyle(20)
    g_ratio.SetMarkerSize(1.2)
    g_ratio.SetLineWidth(1)

    minR=0.0
    maxR=2.0
    ty = numpy.array([])
    tmax=maxR
    ty = g_ratio.GetY()
    if len(ty)>0:
        tmax = numpy.amax(ty)
    if tmax>maxR:
        maxR=tmax*1.05
    if maxR>5.0:
      if useFixedRatio:
        maxR=5.0
      else:
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

    line = ROOT.TLine(h_axis_ratio.GetXaxis().GetBinLowEdge(1), 1.0, h_axis_ratio.GetXaxis().GetBinUpEdge(h_axis_ratio.GetNbinsX()), 1.0)

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
    h_axis_ratio.Draw("")
    g_ratio_unc.Draw("SAME,2")
    g_ratio.Draw("SAME,P0")

    line.SetLineStyle(2)
    line.SetLineColor(ROOT.kBlack)
    line.SetLineWidth(1)
    line.Draw("SAME")
    
    pads[1].Modified()
    pads[1].Update()
    pads[1].RedrawAxis()

  else:
      pads.append(ROOT.TPad("1","1",0,0,1,1))
      pads[0].Draw()

  pads[0].cd()
  if logY:
      pads[0].SetLogy()
  if logX:
      proj_MC.GetXaxis().SetMoreLogLabels()
      pads[0].SetLogx()

  proj_MC.GetYaxis().SetTitle("Events")
  proj_MC.GetYaxis().SetTitleSize(0.04)
  proj_MC.GetXaxis().SetTitleSize(0.04)
  proj_MC.GetXaxis().SetTitleOffset(1.10)
  proj_MC.GetXaxis().SetTitle(proj_MC.GetXaxis().GetTitle())
  proj_MC.GetYaxis().SetLabelSize(0.03)
  if not args.shape:
    proj_MC.GetYaxis().SetMaxDigits(2)

  histMin=0.0
  histMax=0.0
  typ = numpy.array([])
  typ = g_unc.GetY()
  if len(typ)>0:
    histMax = numpy.amax(typ)
  if plotData:
    typ = g_data.GetY()
    if len(typ)>0 and numpy.amax(typ)>histMax:
      histMax = numpy.amax(typ)
  if logY:
      histMax = histMax*1e3
      histMin = 1e-3
  proj_MC.GetYaxis().SetRangeUser(histMin,1.1*histMax)
  proj_MC.SetMaximum(histMin)  
  proj_MC.SetMaximum(1.1*histMax)
  proj_MC.SetLineColor(0)
  proj_MC.SetLineWidth(0)
  proj_MC.Draw("HIST,SAME")
  stack_BG.Draw("HIST,SAME")
  proj_MC.Draw("HIST,SAME")
  g_unc.Draw("SAME,2")
  if plotData:
    g_data.Draw("P,SAME")
    g_data_clone.Draw("P,SAME")

  # Draw CMS headers
  expoffset=0.00
  yoffset=0.00
  if logY or 1.1*proj_MC.GetMaximum()>100.0:
      yoffset=0.05
  latex.DrawLatex(0.95, 0.93+expoffset, yearenergy);
  latexCMS.DrawLatex(0.11+yoffset,0.93+expoffset,"CMS");
  latexCMSExtra.DrawLatex(0.19+yoffset,0.93+expoffset, cmsExtra);

  # Draw selection
  whichnb  = ""
  whichsel = ""
  if "sel8" in plotname or "sel9" in plotname or "sel10" in plotname:
    whichnb  = plotname.split("_")[len(plotname.split("_"))-2]
    whichsel = plotname.split("_")[len(plotname.split("_"))-4]
  elif "sel7" in plotname or "sel6" in plotname or "sel5" in plotname:
    whichsel = plotname.split("_")[len(plotname.split("_"))-3]
  else:
    whichsel = plotname.split("_")[len(plotname.split("_"))-2]
  ts = 0
  for s in range(1,nsel[whichsel]+1):
    if '1p' not in whichnb and s==10:
      continue
    if '0' in whichnb and s>=12:
      continue
    if 'antisel10' in whichsel and s==12:
      continue
    if 'anti' not in whichsel and 'sel10' in whichsel and s==13:
      continue    
    ts = ts+1
    latexSel.DrawLatex(0.57+3*legoffset, 0.91-ts*(0.03-legoffset), sels[s])
  if '1p' not in whichnb and nsel[whichsel]>=10:
    ts = ts+1
    latexSel.DrawLatex(0.57+3*legoffset, 0.91-ts*(0.03-legoffset), nbbin[whichnb])
  ts = ts+1
  ptext = ""
  if "_px" in titleExt:
    if float(args.projectX[1]) >= 13000.0:
      if float(args.projectX[0]) < 0.0:
        ptext=""
      else:
        if "scalar" in plotname:
          ptext = "S_{T}>%.0f GeV"%(float(args.projectX[0]))
        else:
          ptext = "|#vec{S_{T}}|>%.0f GeV"%(float(args.projectX[0])) 
    else:
      if "scalar" in plotname:
        ptext = "%.0f<S_{T}<%.0f GeV"%(float(args.projectX[0]),float(args.projectX[1]))
      else:
        ptext = "%s<|#vec{S_{T}}|<%.0f GeV"%(float(args.projectX[0]),float(args.projectX[1]))
  else:
    if float(args.projectY[1]) >= 13000.0:
      if float(args.projectY[0]) < 20.0:
        ptext = ""
      elif "bjet1" in plotname:
        ptext = "p_{T}(b-jet_{1})>%.0f GeV"%(float(args.projectY[0]))
      else:
        ptext = "p_{T}(jet_{1})>%.0f GeV"%(float(args.projectY[0])) 
    else:
      if float(args.projectY[1]) < 20.0:
        if "bjet1" in plotname:
          ptext = "N_{b-tag} (p_{T}>20 GeV, T+M WPs)=0"
        else:
          ptext = "N_{jet} (p_{T}>20 GeV)=0"
      elif "bjet1" in plotname:
        ptext = "%.0f<p_{T}(b-jet_{1})<%.0f GeV"%(float(args.projectY[0]),float(args.projectY[1]))
      else:
        ptext = "%.0f<p_{T}(jet_{1})<%.0f GeV"%(float(args.projectY[0]),float(args.projectY[1]))
  latexSel.DrawLatex(0.57+3*legoffset, 0.91-ts*(0.03-legoffset), ptext)

  # Plot legends, ranges
  if plotData:
      legend = ROOT.TLegend(0.8,0.7,0.91,0.91)
  else:
      legend = ROOT.TLegend(0.8,0.7,0.89,0.89)
  legend.SetLineColor(0)
  legend.SetLineWidth(0)
  legend.SetFillColor(0)
  legend.SetFillStyle(0)
  if plotData:
    legend.AddEntry(g_data,"Data","EPL")
  for sample in proj_BG.keys():
    legend.AddEntry(proj_BG[sample], sampleLegend[sample],"F")
  #legend.AddEntry(proj_MC,"Total SM","L")
  legend.Draw()
  pads[0].Update()
  pads[0].RedrawAxis()

  # Print and save
  extension = "_"+year
  if logX:
      extension = extension+"_logX"
  if logY:
      extension = extension+"_logY"
  if args.shape:
      extension = extension+"_areaNormalized"
  
  if proj_MC.Integral()>0.0 or proj_data.Integral()>0.0:
    canvas.SaveAs(args.outDir + "/" + plotname + extension + titleExt + ".png")

def draw_plot(sampleDict, plotname, logZ=True, logY=True, logX=False, lumi=59.83, year="2018"):
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

  os.system('cp '+os.environ.get("PWD")+'/utils/index.php '+args.outDir)

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
              curPlots[sample] = copy.deepcopy(customize_plot2d(sample,plotDict[sample]))
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
              curPlots[sample] = copy.deepcopy(customize_plot2d(sample,plotDict[sample]))
              if args.shape and curPlots[sample].Integral(0,-1)>0.0:
                  if "cutflow" not in plotname:
                      curPlots[sample].Scale(1.0/curPlots[sample].Integral(0,-1))
              if args.cumulative:
                  curPlots[sample] = plotUtils.GetCumulative(curPlots[sample],lowToHighBinsCumulative)
      # Bkg
      else:
          curPlots[sample] = copy.deepcopy(customize_plot2d(sample,plotDict[sample]))
          if not totalSM:
              totalSM = curPlots[sample].Clone("totalSM")
          else:
              totalSM.Add(curPlots[sample])

  totalScale   = totalSM.Integral(0,-1,0,-1)
  if args.shape and totalScale>0.0:
      totalSM.Scale(1.0/totalScale)

  # Define canvas
  canvas = ROOT.TCanvas("canvas","canvas",800,800)

  plot2D = copy.deepcopy(totalSM)


  # Y projection
  projY_BG=dict()
  stackY_BG = ROOT.THStack("stackY_BG","")
  if projectY:
    canvasY = ROOT.TCanvas("canvasY","canvasY",800,800)
    if logY:
      canvasY.SetLogy()
    if logX:
      canvasY.SetLogx()

    lowX = args.projectY[0]
    highX = args.projectY[1]
    titleExtY = "_py_"+str(int(lowX))+"_"+str(int(highX))
    
    for i,sample in enumerate(reversed(plotDict.keys())):
      if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample or "data" in sample:
        continue
      projY_BG[sample] = curPlots[sample].ProjectionY(titleExtY+"_"+sample, curPlots[sample].GetXaxis().FindBin(lowX), curPlots[sample].GetXaxis().FindBin(highX))
      projY_BG[sample].Rebin(3)
      projY_BG[sample] = copy.deepcopy(customize_plot(sample,projY_BG[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample],sampleMarkerStyle[sample],sampleMarkerStyle[sample]))
      stackY_BG.Add(projY_BG[sample])
    projY_MC = totalSM.ProjectionY(titleExtY+"_MC", totalSM.GetXaxis().FindBin(lowX), totalSM.GetXaxis().FindBin(highX))
    projY_MC.Rebin(3)
    projY_MC = copy.deepcopy(customize_plot("totalSM",projY_MC,0,0,0,0,0))
    projY_data = ROOT.TH2F()
    if plotData:
      projY_data = curPlots["data"].ProjectionY(titleExtY+"_data", curPlots["data"].GetXaxis().FindBin(lowX), curPlots["data"].GetXaxis().FindBin(highX))
      projY_data.Rebin(3)
      projY_data = copy.deepcopy(customize_plot("data",projY_data,sampleFillColor["data"],sampleLineColor["data"],sampleLineWidth["data"],sampleMarkerStyle["data"],sampleMarkerStyle["data"]))
      
    draw_proj(plotname, projY_BG, stackY_BG, projY_MC, projY_data, doLogY, doLogX, canvasY, yearenergy, titleExtY)

  # X projection
  projX_BG=dict()
  stackX_BG = ROOT.THStack("stackX_BG","")
  if projectX:
    canvasX = ROOT.TCanvas("canvasX","canvasX",800,800)
    if logY:
      canvasX.SetLogy()
    if logX:
      canvasX.SetLogx()

    lowY = args.projectX[0]
    highY = args.projectX[1]
    titleExtX = "_px_"+str(int(lowY))+"_"+str(int(highY))

    for i,sample in enumerate(reversed(plotDict.keys())):
      if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample or "BFF" in sample or "data" in sample:
        continue
      projX_BG[sample] = curPlots[sample].ProjectionX(titleExtX+"_"+sample, curPlots[sample].GetYaxis().FindBin(lowY), curPlots[sample].GetYaxis().FindBin(highY))
      #projX_BG[sample].Rebin(3)
      projX_BG[sample] = copy.deepcopy(customize_plot(sample,projX_BG[sample],sampleFillColor[sample],sampleLineColor[sample],sampleLineWidth[sample],sampleMarkerStyle[sample],sampleMarkerStyle[sample]))
      stackX_BG.Add(projX_BG[sample])
    projX_MC = totalSM.ProjectionX(titleExtX+"_MC", totalSM.GetYaxis().FindBin(lowY), totalSM.GetYaxis().FindBin(highY))
    #projX_MC.Rebin(3)
    projX_MC = copy.deepcopy(customize_plot("totalSM",projX_MC,0,0,0,0,0))
    projX_data = ROOT.TH2F()
    if plotData:
      projX_data = curPlots["data"].ProjectionX(titleExtX+"_data", curPlots["data"].GetYaxis().FindBin(lowY), curPlots["data"].GetYaxis().FindBin(highY))
      #projX_data.Rebin(3)
      projX_data = copy.deepcopy(customize_plot("data",projX_data,sampleFillColor["data"],sampleLineColor["data"],sampleLineWidth["data"],sampleMarkerStyle["data"],sampleMarkerStyle["data"]))

    draw_proj(plotname, projX_BG, stackX_BG, projX_MC, projX_data, doLogY, doLogX, canvasX, yearenergy, titleExtX)

  if not projectY and not projectX:
    if plotData:
      dataOverTotalSM = copy.deepcopy(curPlots["data"])
      dataOverTotalSM.Divide(totalSM)
      draw_onePlot(plotname, "dataOverTotalSM", logZ, logY, logX, dataOverTotalSM, canvas, yearenergy)
    draw_onePlot(plotname, "totalSM", logZ, logY, logX, totalSM, canvas, yearenergy)
    for sample in curPlots.keys():
        draw_onePlot(plotname, sample, logZ, logY, logX, curPlots[sample], canvas, yearenergy)


# Main
ROOT.gStyle.SetPalette(1)
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
  if len(args.plot)==0:
    listfile = sampleDict[sampleDict.keys()[0]][0]
    listkeys = listfile.GetListOfKeys()
    size = listkeys.GetSize()
    for i in range(0,size):
      if "TH2" in listkeys.At(i).GetClassName():
        listofplots.append(listkeys.At(i).GetName())
  else:
    listofplots = listofplots + args.plot
  toexclude = []
  for plot in listofplots:
    if plot in toexclude:
      continue
    draw_plot(sampleDict, plot, False, False, False, lumi, year)
    draw_plot(sampleDict, plot, True, False, False, lumi, year)
