from curses import can_change_color
from hashlib import new
from numbers import Integral
from tkinter.tix import Tree
import ROOT
import copy
import argparse
import os
from datetime import date    

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("--inDir", default="./cpp/temp_data/", help="Choose input directory. Default: './cpp/temp_data/'.")
parser.add_argument("--outDir", default="/home/users/"+os.environ.get("USER")+"/public_html/Zprime/plots_"+today, help="Choose output directory. Default: '/home/users/"+user+"/public_html/Zprime/pots_"+today+"'.")
parser.add_argument("--data", action="store_true", default=False, help="Include data")
parser.add_argument("--signalMass", default=[], action="append", help="Signal masspoints to plot. Default: All.")
parser.add_argument("--signalScale", default=10.0, help="Number to scale the signal by.")
parser.add_argument("--shape", default=False, help="Shape normalization.")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

if not os.path.exists(args.outDir):
    os.makedirs(args.outDir)
os.system('cp '+args.inDir+'../../utils/index.php '+args.outDir)

if len(args.signalMass)==0: 
    args.signalMass = [200,400,700,1000,1500,2000]
signalXSecScale = { "200": 1.0, "400": 5.0, "700": 25.0, "1000": 100.0, "1500": 500.0, "2000": 2000.0}

def get_plot(plotFile, plotname, fillColor=None, lineColor=None, lineWidth=0):
    plot = plotFile.Get(plotname)

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

def draw_plot(plotname="fatjet_msoftdrop", title="myTitle", log=True, compare_data=False, DoRatio=True, lumi=59.83, year="2018"):

    #labels
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

    latexSel = ROOT. TLatex()
    latexSel.SetTextAlign(21)
    latexSel.SetTextFont(42)
    latexSel.SetTextSize(0.035)
    latexSel.SetNDC(True)

    yearenergy=""
    if year!="all":
        yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
    else:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    cmsExtra="Simulation"

    #open file
    signalfiles = []
    ZToMuMufiles = []
    for mass in args.signalMass: 
        signalfiles.append(ROOT.TFile(args.inDir+"output_Y3_M"+str(mass)+"_2018.root"))
    for m1,m2 in zip(["50","120","200","400","800","1400","2300","3500","4500","6000"],["120","200","400","800","1400","2300","3500","4500","6000","Inf"]): 
        ZToMuMufiles.append(ROOT.TFile(args.inDir+"output_ZToMuMu_"+m1+"_"+m2+"_2018.root"))
    WWfile =     ROOT.TFile(args.inDir+"output_WW_2018.root")
    WZfile =     ROOT.TFile(args.inDir+"output_WZ_2018.root")
    ZZfile =     ROOT.TFile(args.inDir+"output_ZZ_2018.root")
    ttbarfile =  ROOT.TFile(args.inDir+"output_ttbar_2018.root")
    tWfile =     ROOT.TFile(args.inDir+"output_tW_2018.root")
    tbarWfile =  ROOT.TFile(args.inDir+"output_tbarW_2018.root")
    TTWfile =    ROOT.TFile(args.inDir+"output_TTW_2018.root")
    TTZfile =    ROOT.TFile(args.inDir+"output_TTZ_2018.root")
    TTHNobbfile= ROOT.TFile(args.inDir+"output_TTHToNonbb_2018.root")
    if compare_data: 
        datafile = ROOT.TFile(args.inDir+"data_2018_2_selected.root")

    #get historam
    signalplots = []
    ZToMuMuplots = []
    for i in range(len(args.signalMass)): 
        signalplots.append(get_plot(signalfiles[i],plotname,lineColor=ROOT.kPink+i,lineWidth=2))
        if args.shape and signalplots[i].Integral(0,-1)>0.0:
            if "cutflow" not in plotname:
                signalplots[i].Scale(1.0/signalplots[i].Integral(0,-1))
            else:
                signalplots[i].Scale(1.0/signalplots[i].GetBinContent(1))
    for i in range(len(ZToMuMufiles)): 
        ZToMuMuplots.append(get_plot(ZToMuMufiles[i],plotname,fillColor=ROOT.kOrange))
    if compare_data: 
        dataplot = get_plot(datafile,plotname,lineColor=ROOT.kBlack,lineWidth=2)
    WWplot = get_plot(WWfile,plotname,fillColor=ROOT.kOrange+1)
    WZplot = get_plot(WZfile,plotname,fillColor=ROOT.kOrange+2)
    ZZplot = get_plot(ZZfile,plotname,fillColor=ROOT.kOrange+3)
    ttbarplot = get_plot(ttbarfile,plotname,fillColor=ROOT.kOrange+4)
    tWplot = get_plot(tWfile,plotname,fillColor=ROOT.kOrange+5)
    tbarWplot = get_plot(tbarWfile,plotname,fillColor=ROOT.kOrange+5)
    TTWplot = get_plot(TTWfile,plotname,fillColor=ROOT.kOrange+6)
    TTZplot = get_plot(TTZfile,plotname,fillColor=ROOT.kOrange+6)
    TTHNobbplot = get_plot(TTHNobbfile,plotname,fillColor=ROOT.kOrange+6)
   
    #add histos
    ZToMuMuplot = ZToMuMuplots[0].Clone("ZToMuMu")
    for i in range(1,len(ZToMuMuplots)): 
        ZToMuMuplot.Add(ZToMuMuplots[i])
    ST_tWplot = tWplot.Clone("ST_tW")
    ST_tWplot.Add(tbarWplot)
    TTXplot = TTWplot.Clone("TTX")
    TTXplot.Add(TTZplot)
    TTXplot.Add(TTHNobbplot)

    totalSM = ZToMuMuplot.Clone("totalSM")
    totalSM.Add(ST_tWplot)
    totalSM.Add(TTXplot)
    totalSM.Add(ttbarplot)
    totalSM.Add(ZZplot)
    totalSM.Add(WWplot)
    totalSM.Add(WZplot)
    totalScale   = totalSM.Integral(0,-1)
    if "cutflow" in plotname:
        totalScale = totalSM.GetBinContent(1)

    if args.shape and totalScale>0.0:
        ZToMuMuplot.Scale(1.0/totalScale)
        ST_tWplot.Scale(1.0/totalScale)
        TTXplot.Scale(1.0/totalScale)
        ttbarplot.Scale(1.0/totalScale)
        ZZplot.Scale(1.0/totalScale)
        WWplot.Scale(1.0/totalScale)
        WZplot.Scale(1.0/totalScale)

    #build stack
    stack = ROOT.THStack("stack","")
    stack.Add(ZZplot)
    stack.Add(WZplot)
    stack.Add(WWplot)
    stack.Add(TTXplot)
    stack.Add(ST_tWplot)
    stack.Add(ttbarplot)
    stack.Add(ZToMuMuplot)
    stack.SetTitle(title)

    #plot legends, ranges
    legend = ROOT.TLegend(0.55,0.55,0.89,0.89)
    legend.SetLineColor(0)
    legend.SetFillColor(0)
    #legend.SetTextSize(0.02)

    for i,mass in enumerate(args.signalMass): 
        if log==False and args.signalScale and not args.shape:
            legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) %1.2E x%1.1E"%(signalplots[i].Integral(0,-1),(float(args.signalScale))*(float(signalXSecScale[str(mass)]))),"L")
        else:
            legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) %1.2E"%(signalplots[i].Integral(0,-1)),"L")
            
    if compare_data: 
        legend.AddEntry(dataplot,"data %1.2E"%(dataplot.Integral(0,-1)),"PL")
    legend.AddEntry(ZToMuMuplot, "DY(#mu#mu) %1.2E"%(ZToMuMuplot.Integral(0,-1)),"F")
    legend.AddEntry(ttbarplot,"t#bar{t} %1.2E"%(ttbarplot.Integral(0,-1)),"F")
    legend.AddEntry(tWplot,"tW %1.2E"%(ST_tWplot.Integral(0,-1)),"F")
    legend.AddEntry(TTXplot,"t#bar{t}X %1.2E"%(TTXplot.Integral(0,-1)),"F")
    legend.AddEntry(WWplot, "WW %1.2E"%(WWplot.Integral(0,-1)),"F")
    legend.AddEntry(WZplot, "WZ %1.2E"%(WZplot.Integral(0,-1)),"F")
    legend.AddEntry(ZZplot,"ZZ %1.2E"%(ZZplot.Integral(0,-1)),"F")

    #define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    if DoRatio==True:
        MCplot = copy.deepcopy(ZToMuMuplot)
        MCplot.Add(WWplot)
        MCplot.Add(WZplot)
        MCplot.Add(ZZplot)
        MCplot.Add(ttbarplot)
        MCplot.Add(tWplot)
        MCplot.Add(TTXplot)
        ratioplot=copy.deepcopy(dataplot)
        ratioplot.Divide(MCplot)
        ratioplot.SetTitle(";"+title+";Data / MC")
        pad1 = ROOT.TPad("pad1","pad1",0,0.3,1,1)
        pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.3)
        pad1.Draw()
        pad2.Draw()
        pad2.cd()
        ratioplot.Draw("E0")

    if DoRatio==False:
        pad1 = ROOT.TPad("pad1","pad1",0,0,1,1)
        pad1.Draw()

    pad1.cd()
    if log==True:
        pad1.SetLogy()
        #ROOT.gPad.SetLogy(1)

    #plot data,stack, signal, data  
    stack.Draw("HIST")
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
    for i,mass in enumerate(args.signalMass):
        if log==False and args.signalScale and not args.shape: 
            signalplots[i].Scale((float(args.signalScale))*(float(signalXSecScale[str(mass)])))
        if histMax < signalplots[i].GetMaximum(): 
            histMax = signalplots[i].GetMaximum()
        signalplots[i].Draw("HIST same")
    if compare_data: 
        dataplot.Draw("E0 same")

    if histMax < stack.GetMaximum(): 
        histMax = stack.GetMaximum()
    if log==True:
        histMax = histMax*1e3
        stack.SetMinimum(1e-3)
        
    stack.SetMaximum(1.1*histMax)

    canvas.Update()

    legend.Draw()

    ROOT.gPad.RedrawAxis()

    latex.DrawLatex(0.9, 0.92+0.03, yearenergy);
    latexCMS.DrawLatex(0.11,0.92+0.03,"CMS");
    latexCMSExtra.DrawLatex(0.22,0.92+0.03, cmsExtra);

    #print and save
    extension = ""
    if compare_data:
        extension = extension+"_mc+data"
    else:
        extension = extension+"_s+b"
    if log:
        extension = extension+"_log"
    else:
        extension = extension+"_linear"
    if args.shape:
        extension = extension+"_areaNormalized"
    
    canvas.SaveAs(args.outDir + plotname + extension + ".png")

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)

listofplots = []
listfile = ROOT.TFile(args.inDir+"output_ttbar_2018.root")
listkeys = listfile.GetListOfKeys()
size = listkeys.GetSize()
for i in range(0,size):
    listofplots.append(listkeys.At(i).GetName())
toexclude = []

for plot in listofplots:
    if plot in toexclude:
        continue
    title=""
    draw_plot(plot, title, False, args.data, False, 59.83, "2018")
    draw_plot(plot, title, True , args.data, False, 59.83, "2018")
