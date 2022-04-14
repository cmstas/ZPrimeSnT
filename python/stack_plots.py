from curses import can_change_color
from hashlib import new
from numbers import Integral
from tkinter.tix import Tree
import ROOT
import copy
import argparse

parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("--inDir", default="/home/users/kdownham/ZPrimeAnalysis/ZPrimeAnalysis/cpp/temp_data/", help="Choose input directory. Default: '/home/users/kdownham/ZPrimeAnalysis/ZPrimeAnalysis/cpp/temp_data/'.")
parser.add_argument("--outDir", default="/home/users/kdownham/public_html/ZPrime", help="Choose output directory. Default: '../plots'.")
parser.add_argument("--data", action="store_true", default=False, help="Include data")
args = parser.parse_args()

args.inDir = args.inDir.rstrip("/")+"/"
args.outDir = args.outDir.rstrip("/")+"/"

def draw_plot(plotname="fatjet_msoftdrop", title="myTitle", log=True, compare_data=False, DoRatio=True):
    #open file
    signalfile = ROOT.TFile(args.inDir+"output_signal_2018.root")
    DYfile =     ROOT.TFile(args.inDir+"output_DY_2018.root")
    WWfile =     ROOT.TFile(args.inDir+"output_WW_2018.root")
    WZfile =     ROOT.TFile(args.inDir+"output_WZ_2018.root")
    ZZfile =     ROOT.TFile(args.inDir+"output_ZZ_2018.root")
    ttbarfile =  ROOT.TFile(args.inDir+"output_ttbar_2018.root")
    tWfile =     ROOT.TFile(args.inDir+"output_tW_2018.root")
    tbarWfile =  ROOT.TFile(args.inDir+"output_tbarW_2018.root")
    TTWfile =    ROOT.TFile(args.inDir+"output_TTW_2018.root")
    TTZfile =    ROOT.TFile(args.inDir+"output_TTZ_2018.root")
    TTHNobbfile= ROOT.TFile(args.inDir+"output_TTHToNonbb_2018.root")
   #TTHbbfile =  ROOT.TFile(args.inDir+"output_TTHTobb_2018.root")
    if compare_data: datafile = ROOT.TFile(args.inDir+"data_2018_2_selected.root")

    #get historam
    signalplot = signalfile.Get(plotname)
    if compare_data:
        dataplot = datafile.Get(plotname)
        dataplot.Rebin(4)
    DYplot = DYfile.Get(plotname)
    WWplot = WWfile.Get(plotname)
    WZplot = WZfile.Get(plotname)
    ZZplot = ZZfile.Get(plotname)
    ttbarplot = ttbarfile.Get(plotname)
    tWplot = tWfile.Get(plotname)
    tbarWplot = tbarWfile.Get(plotname)
    TTWplot = TTWfile.Get(plotname)
    TTZplot = TTZfile.Get(plotname)
    TTHNobbplot = TTHNobbfile.Get(plotname)
   #TTHbbplot = TTHbbfile.Get(plotname)

#    signalplot.Rebin(4)
#    DYplot.Rebin(4)
#    WWplot.Rebin(4)
#    WZplot.Rebin(4)
#    ZZplot.Rebin(4)
#    ttbarplot.Rebin(4)

    #draw overflow
    signalplot.SetBinContent(1, signalplot.GetBinContent(1) + signalplot.GetBinContent(0))
    signalplot.SetBinContent(signalplot.GetNbinsX(), signalplot.GetBinContent(signalplot.GetNbinsX() + 1) + signalplot.GetBinContent(signalplot.GetNbinsX()))
    if compare_data:
        dataplot.SetBinContent(1, dataplot.GetBinContent(1) + dataplot.GetBinContent(0))
        dataplot.SetBinContent(dataplot.GetNbinsX(), dataplot.GetBinContent(dataplot.GetNbinsX() + 1) + dataplot.GetBinContent(dataplot.GetNbinsX()))
    DYplot.SetBinContent(1, DYplot.GetBinContent(1) + DYplot.GetBinContent(0))
    DYplot.SetBinContent(DYplot.GetNbinsX(), DYplot.GetBinContent(DYplot.GetNbinsX() + 1) + DYplot.GetBinContent(DYplot.GetNbinsX()))
    WWplot.SetBinContent(1, WWplot.GetBinContent(1) + WWplot.GetBinContent(0))
    WWplot.SetBinContent(WWplot.GetNbinsX(), WWplot.GetBinContent(WWplot.GetNbinsX() + 1) + WWplot.GetBinContent(WWplot.GetNbinsX()))
    WZplot.SetBinContent(1, WZplot.GetBinContent(1) + WZplot.GetBinContent(0))
    WZplot.SetBinContent(WZplot.GetNbinsX(), WZplot.GetBinContent(WZplot.GetNbinsX() + 1) + WZplot.GetBinContent(WZplot.GetNbinsX()))
    ZZplot.SetBinContent(1, ZZplot.GetBinContent(1) + ZZplot.GetBinContent(0))
    ZZplot.SetBinContent(ZZplot.GetNbinsX(), ZZplot.GetBinContent(ZZplot.GetNbinsX() + 1) + ZZplot.GetBinContent(ZZplot.GetNbinsX()))
    ttbarplot.SetBinContent(1, ttbarplot.GetBinContent(1) + ttbarplot.GetBinContent(0))
    ttbarplot.SetBinContent(ttbarplot.GetNbinsX(), ttbarplot.GetBinContent(ttbarplot.GetNbinsX() + 1) + ttbarplot.GetBinContent(ttbarplot.GetNbinsX()))
    tWplot.SetBinContent(1, tWplot.GetBinContent(1) + tWplot.GetBinContent(0))
    tWplot.SetBinContent(tWplot.GetNbinsX(), tWplot.GetBinContent(tWplot.GetNbinsX() + 1) + tWplot.GetBinContent(tWplot.GetNbinsX())) 
    tbarWplot.SetBinContent(1, tbarWplot.GetBinContent(1) + tbarWplot.GetBinContent(0))
    tbarWplot.SetBinContent(tbarWplot.GetNbinsX(), tbarWplot.GetBinContent(tbarWplot.GetNbinsX() + 1) + tbarWplot.GetBinContent(tbarWplot.GetNbinsX()))
    TTWplot.SetBinContent(1, TTWplot.GetBinContent(1) + TTWplot.GetBinContent(0))
    TTWplot.SetBinContent(TTWplot.GetNbinsX(), TTWplot.GetBinContent(TTWplot.GetNbinsX() + 1) + TTWplot.GetBinContent(TTWplot.GetNbinsX()))
    TTZplot.SetBinContent(1, TTZplot.GetBinContent(1) + TTZplot.GetBinContent(0))
    TTZplot.SetBinContent(TTZplot.GetNbinsX(), TTZplot.GetBinContent(TTZplot.GetNbinsX() + 1) + TTZplot.GetBinContent(TTZplot.GetNbinsX()))
    TTHNobbplot.SetBinContent(1, TTHNobbplot.GetBinContent(1) + TTHNobbplot.GetBinContent(0))
    TTHNobbplot.SetBinContent(TTHNobbplot.GetNbinsX(), TTHNobbplot.GetBinContent(TTHNobbplot.GetNbinsX() + 1) + TTHNobbplot.GetBinContent(TTHNobbplot.GetNbinsX()))
    #TTHbbplot.SetBinContent(1, TTHbbplot.GetBinContent(1) + TTHbbplot.GetBinContent(0))
    #TTHbbplot.SetBinContent(TTHbbplot.GetNbinsX(), TTHbbplot.GetBinContent(TTHbbplot.GetNbinsX() + 1) + TTHbbplot.GetBinContent(TTHbbplot.GetNbinsX()))
 

    #build stack
    stack = ROOT.THStack("stack","")
    ZZplot.SetFillColor(ROOT.kOrange+3)
    ZZplot.SetLineWidth(0)
    stack.Add(ZZplot)
    ttbarplot.SetFillColor(ROOT.kOrange+4)
    ttbarplot.SetLineWidth(0)
    stack.Add(ttbarplot)
    WWplot.SetFillColor(ROOT.kOrange+1)
    WWplot.SetLineWidth(0)
    stack.Add(WWplot)
    WZplot.SetFillColor(ROOT.kOrange+2)
    WZplot.SetLineWidth(0)
    stack.Add(WZplot)
    DYplot.SetFillColor(ROOT.kOrange)
    DYplot.SetLineWidth(0)
    stack.Add(DYplot)
    tWplot.SetFillColor(ROOT.kOrange+5)
    tWplot.SetLineWidth(0)
    stack.Add(tWplot)
    tbarWplot.SetFillColor(ROOT.kOrange+6)
    tbarWplot.SetLineWidth(0)
    stack.Add(tbarWplot)
    TTWplot.SetFillColor(ROOT.kOrange+7)
    TTWplot.SetLineWidth(0)
    stack.Add(TTWplot)
    TTZplot.SetFillColor(ROOT.kOrange+8)
    TTZplot.SetLineWidth(0)
    stack.Add(TTZplot)
    TTHNobbplot.SetFillColor(ROOT.kOrange+9)
    TTHNobbplot.SetLineWidth(0)
    stack.Add(TTHNobbplot)
    #TTHbbplot.SetFillColor(ROOT.kOrange+10)
    #TTHbbplot.SetLineWidth(0)
    #stack.Add(TTHbbplot)
    stack.SetTitle(title)

    #plot legends, ranges
    legend = ROOT.TLegend(0.7,0.83,0.95,0.97)
    legend.SetTextFont(60)
    legend.SetTextSize(0.02)
    legend.AddEntry(signalplot,"signal %.2f"%(signalplot.Integral()))
    if compare_data: legend.AddEntry(dataplot,"data %.2f"%(dataplot.Integral()))
    legend.AddEntry(DYplot, "DY %.2f"%(DYplot.Integral()))
    legend.AddEntry(WWplot, "WW %.2f"%(WWplot.Integral()))
    legend.AddEntry(WZplot, "WZ %.2f"%(WZplot.Integral()))
    legend.AddEntry(ZZplot,"ZZ %.2f"%(ZZplot.Integral()))
    legend.AddEntry(ttbarplot,"ttbar %.2f"%(ttbarplot.Integral()))
    legend.AddEntry(tWplot,"tW %.2f"%(tWplot.Integral()))
    legend.AddEntry(tbarWplot,"tbarW %.2f"%(tbarWplot.Integral()))
    legend.AddEntry(TTWplot,"ttW %.2f"%(TTWplot.Integral()))
    legend.AddEntry(TTZplot,"ttZ %.2f"%(TTZplot.Integral()))
    legend.AddEntry(TTHNobbplot,"ttHNobb %.2f"%(TTHNobbplot.Integral()))
    legend.AddEntry(TTHbbplot,"ttHbb %.2f"%(TTHbbplot.Integral())) 

    #define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    if DoRatio==True:
        MCplot = copy.deepcopy(DYplot)
        MCplot.Add(WWplot)
        MCplot.Add(WZplot)
        MCplot.Add(ZZplot)
        MCplot.Add(ttbarplot)
        ratioplot=copy.deepcopy(dataplot)
        ratioplot.Divide(MCplot)
        ratioplot.SetTitle(";"+title+";data / MC")
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
    signalplot.SetLineColor(ROOT.kRed)
    signalplot.SetLineWidth(3)
    if log==True:
#        signalplot.Draw("Hist")
        stack.Draw("HIST")
        signalplot.Draw("HIST same")
        if compare_data: dataplot.Draw("E0 same")

        stack.SetMinimum(10e-2)
        stack.SetMaximum(10e8)
        #stack.Draw("Hist")

    if log==False:
        stack.Draw("HIST")
        signalplot.Draw("HIST same")
        if compare_data: dataplot.Draw("E0 same")
    legend.Draw()

    #print and save
    if log==True:
        if compare_data==False:
            canvas.SaveAs(args.outDir + plotname + "_s+b_log.png")
        if compare_data==True:
            canvas.SaveAs(args.outDir + plotname + "_mc+data_log.png")
    if log==False:
        if compare_data==False:
            canvas.SaveAs(args.outDir + plotname + "_s+b_linear.png")
        if compare_data==True:
            canvas.SaveAs(args.outDir + plotname + "_mc+data_linear.png")

ROOT.gStyle.SetOptStat(0000)
ROOT.gROOT.SetBatch(1)

#listofplots1=["mu1_pt", "mu1_pt_pre", "mu1_pt_post", "mu2_pt", "mu2_pt_pre", "mu2_pt_post",
#                "nGood_PV_pre", "nGood_PV_post","nCand_Muons_pre","nCand_Muons_post","nCand_trigObj_pre","nCand_trigObj_post",
#                "mu1_trkRelIso_pre", "mu1_trkRelIso_post", "mu2_trkRelIso_pre", "mu2_trkRelIso_post",
#                "mu1_highPtId_pre", "mu1_highPtId_post", "mu2_highPtId_pre", "mu2_highPtId_post", ]
listofplots1 = ["nCand_Muons", "mll_pf", "nbtagDeepFlavB", "btagDeepFlavB", "mll_pf_pre", "bjet1_pt", "bjet2_pt", "max_mlb", "min_mlb", "mu1_pt", "mu2_pt", "mu1_trkRelIso_pre", "mu1_trkRelIso_post", "mu2_trkRelIso_pre", "mu2_trkRelIso_post" , "mll_pf_btag", "mu1_trkRelIso", "mu2_trkRelIso"]

for plot in listofplots1:
    title=plot
    draw_plot(plot, title, False, args.data, False)
    draw_plot(plot, title, True, args.data, False)
