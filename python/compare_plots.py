from collections import OrderedDict
import ROOT
import numpy
import copy
import os
from datetime import date
import plotUtils

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

#inDirRef = "./cpp/temp_data_looseCuts/"
inDirRef = "./cpp/temp_data_noHEMveto/"
inDirOther = "./cpp/temp_data/"
#outDir = "/home/users/"+user+"/public_html/Zprime/looseCuts/"
outDir = "/home/users/"+user+"/public_html/Zprime/HEMveto/"
if not os.path.exists(outDir):
    os.makedirs(outDir)
os.system('cp utils/index.php '+outDir)

doRatio = True
extendedLegend = False
shape = False
plotData = False

signalMass = []
massToExclude=[]

sampleFillColor=[]
sampleFillColor.append(None)
sampleFillColor.append(None)

sampleLineColor=[]
sampleLineColor.append(ROOT.kBlack)
sampleLineColor.append(ROOT.kRed)

sampleLineWidth=[]
sampleLineWidth.append(2)
sampleLineWidth.append(2)

sampleMarkerStyle=[]
sampleMarkerStyle.append(None)
sampleMarkerStyle.append(None)

sampleMarkerSize=[]
sampleMarkerSize.append(None)
sampleMarkerSize.append(None)

sampleLegend=[]
#sampleLegend.append("Without cuts")
#sampleLegend.append("With cuts")
sampleLegend.append("Without veto")
sampleLegend.append("With veto")

def get_files(samples,year,inDir):

    sampleDict=OrderedDict()

    if year!="all":
        years=[year]
    else:
        years=["2016nonAPV","2016APV","2017","2018"]
    for tyear in years:
        for i,sample in enumerate(samples):
            if sample=="ZToMuMu":
                for m1,m2 in zip(["50","120","200","400","800","1400","2300","3500","4500","6000"],["120","200","400","800","1400","2300","3500","4500","6000","Inf"]):
                    if sample not in sampleDict.keys():
                        sampleDict[sample]=[]
                    sampleDict[sample].append(ROOT.TFile(inDir+"output_ZToMuMu_"+m1+"_"+m2+"_"+tyear+".root"))
            else:
                if sample not in sampleDict.keys():
                    sampleDict[sample]=[]
                sampleDict[sample].append(ROOT.TFile(inDir+"output_"+sample+"_"+tyear+".root"))
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

minX = 0.0
maxX = 0.0

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

    ### Rebin fine-binned histograms
    if ("Y3" not in sample and "DY3" not in sample and "DYp3" not in sample and "B3mL2" not in sample) or "mmumu" not in plot.GetName():
        if plot.GetXaxis().GetBinUpEdge(plot.GetNbinsX())-plot.GetXaxis().GetBinLowEdge(1) > 500.0 and plot.GetXaxis().GetBinWidth(1)<10.0:
            if plot.GetNbinsX()%5==0:
                plot.Rebin(5)
            elif plot.GetNbinsX()%3==0:
                plot.Rebin(3)
            else:
                plot.Rebin(2)
    else:
        model = sample.split("_")[0]
        mass = sample.split("_")[1].lstrip("M")
        while plot.GetBinWidth(1)<0.05*float(mass):
            if plot.GetNbinsX()%2==0:
                plot.Rebin(2)
            elif plot.GetNbinsX()%3==0:
                plot.Rebin(3)
            else:
                plot.Rebin(5)

    for b in range(1, plot.GetNbinsX()+1):
        if plot.GetBinContent(b)>0 and plot.GetBinError(b)/plot.GetBinContent(b)>0.75:
            plot.SetBinContent(b,0.0)
            plot.SetBinError(b,0.0)

    return plot

def draw_plot(sampleDictRef, sampleDictOther, plotname, logY=True, logX=False, plotData=False, doRatio=True, lumi=59.83, year="2018"):

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
    if extendedLegend:
        legoffset=0.03
    latexSel = ROOT. TLatex()
    latexSel.SetTextAlign(11)
    latexSel.SetTextFont(42)
    latexSel.SetTextSize(0.02-0.1*legoffset)
    latexSel.SetNDC(True)

    yearenergy=""
    if year!="all":
        yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
    else:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    if plotData:
        cmsExtra="Preliminary"
    else:
        cmsExtra="Simulation"

    # Get histograms
    plotDictRef   = get_plots(sampleDictRef, plotname)
    plotDictOther = get_plots(sampleDictOther, plotname)
    curPlotsRef=OrderedDict()
    curPlotsOther=OrderedDict()

    for i,sample in enumerate(plotDictRef.keys()):
        # Signal
        if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
            model = sample.split("_")[0]
            mass = sample.split("_")[1].lstrip("M")
        curPlotsRef[sample] = copy.deepcopy(customize_plot(sample,plotDictRef[sample],sampleFillColor[0],sampleLineColor[0],sampleLineWidth[0],sampleMarkerStyle[0],sampleMarkerSize[0]))
        curPlotsOther[sample] = copy.deepcopy(customize_plot(sample,plotDictOther[sample],sampleFillColor[1],sampleLineColor[1],sampleLineWidth[1],sampleMarkerStyle[1],sampleMarkerSize[1]))
        if shape and curPlotsRef[sample].Integral(0,-1)>0.0:
            curPlotsRef[sample].Scale(1.0/curPlotsRef[sample].Integral(0,-1))
        if shape and curPlotsOther[sample].Integral(0,-1)>0.0:
            curPlotsOther[sample].Scale(1.0/curPlotsOther[sample].Integral(0,-1))
 
    # Plot legends, ranges
    legend = ROOT.TLegend(0.7,0.7,0.89,0.89)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)

    minX = curPlotsRef[sample].GetXaxis().GetBinLowEdge(1)
    maxX = curPlotsRef[sample].GetXaxis().GetBinUpEdge(curPlotsRef[sample].GetNbinsX())

    if "Y3" in sample or "DY3" in sample or "DYp3" in sample or "B3mL2" in sample:
        model = sample.split("_")[0]
        mass = sample.split("_")[1].lstrip("M")
        legend.SetHeader(model+" (M="+mass+"GeV)")
        if "mmumu" in curPlotsRef[sample].GetName():
            if float(mass)*0.5>175.0:
                minX = float(mass)*0.5
                maxX = float(mass)*1.3
            else:
                minX = 175.0
                maxX = float(mass)*1.3
    else:
        legend.SetHeader(sample)

    if extendedLegend:
        legend.AddEntry(curPlotsRef[sample],sampleLegend[0]+" %1.2E"%(curPlotsRef[sample].Integral(0,-1)),"L")
        legend.AddEntry(curPlotsOther[sample],sampleLegend[1]+" %1.2E"%(curPlotsOther[sample].Integral(0,-1)),"L")
    else:
        legend.AddEntry(curPlotsRef[sample],sampleLegend[0],"L")
        legend.AddEntry(curPlotsOther[sample],sampleLegend[1],"L")

    # Define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    refplot = copy.deepcopy(curPlotsRef[sample])

    h_axis = ROOT.TH1D()
    h_axis_ratio = ROOT.TH1D()
    h_axis = ROOT.TH1D("h_axis","", int((refplot.GetXaxis().GetBinUpEdge(refplot.GetNbinsX())-refplot.GetXaxis().GetBinLowEdge(1))/0.01), refplot.GetXaxis().GetBinLowEdge(1), refplot.GetXaxis().GetBinUpEdge(refplot.GetNbinsX()))
    h_axis_ratio = ROOT.TH1D("h_axis_ratio","", int((refplot.GetXaxis().GetBinUpEdge(refplot.GetNbinsX())-refplot.GetXaxis().GetBinLowEdge(1))/0.01), refplot.GetXaxis().GetBinLowEdge(1), refplot.GetXaxis().GetBinUpEdge(refplot.GetNbinsX()))
    h_axis.GetXaxis().SetRangeUser(minX, maxX)
    h_axis_ratio.GetXaxis().SetRangeUser(minX, maxX)
    if logX and refplot.GetXaxis().GetBinLowEdge(1) < epsilon:
        h_axis.GetXaxis().SetRangeUser(max(minX,refplot.GetXaxis().GetBinCenter(1)-0.25*refplot.GetXaxis().GetBinWidth(1)), maxX)
        h_axis_ratio.GetXaxis().SetRangeUser(max(minX,refplot.GetXaxis().GetBinCenter(1)-0.25*refplot.GetXaxis().GetBinWidth(1)), maxX)

    if plotData:
        g_other = ROOT.TGraphAsymmErrors()
        g_unc = ROOT.TGraphAsymmErrors()
        plotUtils.ConvertToPoissonGraph(curPlotsOther[sample], g_other, drawZeros=False, drawXerr=True)
        g_other.SetMarkerStyle(20)
        g_other.SetMarkerSize(1.2)
        g_other.SetLineWidth(1)
        # draw with zero marker size so error bars drawn all the way to x axis in the case of 0 content
        g_other_clone = g_other.Clone()
        g_other_clone.SetMarkerSize(0.0)
    else:
        g_other = copy.deepcopy(curPlotsOther[sample])


    if plotData:
        g_ratio = ROOT.TGraphAsymmErrors()
        g_ratio_unc = ROOT.TGraphAsymmErrors()
        plotUtils.GetPoissonRatioGraph(refplot, curPlotsOther[sample], g_ratio, drawZeros=False, drawXerr=True, useMCErr=True)
    else:
        g_ratio = curPlotsOther[sample].Clone("ratio")
        g_ratio.Divide(refplot)
    if sampleMarkerStyle[1]:
        g_ratio.SetMarkerStyle(sampleMarkerStyle[1])
        g_ratio.SetMarkerSize(samepleMakerSize[1])
    g_ratio.SetLineWidth(sampleLineWidth[1])
    g_ratio.SetLineColor(sampleLineColor[1])

    if plotData:
        for b in range(1,refplot.GetNbinsX()+1):
            thisPoint = g_ratio_unc.GetN()
            yerror = refplot.GetBinError(b)
            g_unc.SetPoint(thisPoint, refplot.GetBinCenter(b), refplot.GetBinContent(b))
            g_unc.SetPointError(thisPoint, 0.5*refplot.GetBinWidth(b), 0.5*refplot.GetBinWidth(b), yerror, yerror)
            if refplot.GetBinContent(b)>0.0:
                yerror = yerror/refplot.GetBinContent(b)
            else:
                yerror = 0.0
            g_ratio_unc.SetPoint(thisPoint, refplot.GetBinCenter(b), 1.0)
            g_ratio_unc.SetPointError(thisPoint, 0.5*refplot.GetBinWidth(b), 0.5*refplot.GetBinWidth(b), yerror, yerror)
        g_unc.SetFillStyle(3244)
        g_unc.SetFillColor(ROOT.kGray+3)
        g_ratio_unc.SetFillStyle(1001)
        g_ratio_unc.SetFillColor(ROOT.kGray)

    pads = []
    if doRatio==True:
        #minR = 0.925
        #maxR = 1.075
        minR = 0.775
        maxR = 1.025
        h_axis_ratio.GetYaxis().SetRangeUser(minR,maxR)
        h_axis_ratio.SetMinimum(minR)
        h_axis_ratio.SetMaximum(maxR)
        h_axis_ratio.SetTitle(";;Ratio")
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

        line = ROOT.TLine(minX, 1.0, maxX, 1.0)

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
        g_ratio.Draw("LE,same")
        #
        line.SetLineStyle(2)
        line.SetLineColor(sampleLineColor[0])
        line.SetLineWidth(1)
        line.Draw("SAME")
        #
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

    h_axis.GetYaxis().SetTitleSize(0.04)
    h_axis.GetXaxis().SetTitleSize(0.04)
    h_axis.GetXaxis().SetTitleOffset(1.25)
    h_axis.GetXaxis().SetTitle(refplot.GetXaxis().GetTitle())
    if shape:
        h_axis.GetYaxis().SetTitle("A.U.")
    else:
        h_axis.GetYaxis().SetTitle(refplot.GetYaxis().GetTitle())
    h_axis.GetYaxis().SetLabelSize(0.03)
    h_axis.GetYaxis().SetMaxDigits(3)
    h_axis.Draw("")
    refplot.Draw("HISTE,SAME")
    histMax = 0.0
    for sample in curPlotsOther.keys():
        if histMax < curPlotsOther[sample].GetMaximum():
            histMax = curPlotsOther[sample].GetMaximum()
        curPlotsOther[sample].Draw("HISTE,SAME")
    if histMax < refplot.GetMaximum():
        histMax = refplot.GetMaximum()
    if logY:
        histMax = histMax*0.5e1
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

    # Print and save
    extension = ""
    if logX:
        extension = extension+"_logX"
    if logY:
        extension = extension+"_logY"
    if shape:
        extension = extension+"_areaNormalized"
    
    canvas.SaveAs(outDir + plotname + extension + "_"+sample+".png")

# Main
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)

# year="all"
year="2018"
lumi=0.0 #fb^-1
if year == "2018":
    lumi = 59.83
elif year == "2017":
    lumi = 41.48
elif year == "2016APV":
    lumi = 19.5
elif year == "2016nonAPV":
    lumi = 16.8
elif year == "all":
    lumi = 59.83 + 41.48 + 19.5 + 16.8

# Sample
samplesRef = []
samplesRef.append("Y3_M200")
#samplesRef.append("Y3_M700")
#samplesRef.append("Y3_M1500")
#
samplesOther = samplesRef

# Open files
sampleDictRef=get_files(samplesRef,year,inDirRef)
sampleDictOther=get_files(samplesOther,year,inDirOther)
# List of plots
listofplots=["mmumu_sel10_mllinclusive_nBTag1p_MuDetAll"]
toexclude = []

for plot in listofplots:
    if plot in toexclude:
        continue
    draw_plot(sampleDictRef, sampleDictOther,  plot, True, False, False, True, lumi, year)
    draw_plot(sampleDictRef, sampleDictOther,  plot, False, False, False, True, lumi, year)
