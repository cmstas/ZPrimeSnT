from curses import can_change_color
from hashlib import new
from numbers import Integral
from tkinter.tix import Tree
import ROOT
import copy

def draw_plot(plotname="fatjet_msoftdrop", title="myTitle", log=True, compare_data=False, DoRatio=True):
    #open file
#    signalfile = ROOT.TFile("/ceph/cms/store/user/kdownham/Zprime/background/output_DY_2018.root")
    DYfile = ROOT.TFile("/ceph/cms/store/user/kdownham/Zprime/background/output_DY_2018.root")
    WWfile = ROOT.TFile("/ceph/cms/store/user/kdownham/Zprime/background/output_WW_2018.root")
    WZfile = ROOT.TFile("/ceph/cms/store/user/kdownham/Zprime/background/output_WZ_2018.root")
    ZZfile = ROOT.TFile("/ceph/cms/store/user/kdownham/Zprime/background/output_ZZ_2018.root")
    ttbarfile = ROOT.TFile("/ceph/cms/store/user/kdownham/Zprime/background/output_ttbar_2018.root")
    if compare_data:
        datafile = ROOT.TFile("../outfiles/data_2018_2_selected.root")

    #get historam
#    signalplot = signalfile.Get(plotname)
    if compare_data:
        dataplot = datafile.Get(plotname)
        dataplot.Rebin(4)
    DYplot = DYfile.Get(plotname)
    WWplot = WWfile.Get(plotname)
    WZplot = WZfile.Get(plotname)
    ZZplot = ZZfile.Get(plotname)
    ttbarplot = ttbarfile.Get(plotname)

#    signalplot.Rebin(4)
#    DYplot.Rebin(4)
#    WWplot.Rebin(4)
#    WZplot.Rebin(4)
#    ZZplot.Rebin(4)
#    ttbarplot.Rebin(4)

    #draw overflow
#    signalplot.SetBinContent(1, signalplot.GetBinContent(1) + signalplot.GetBinContent(0))
#    signalplot.SetBinContent(signalplot.GetNbinsX(), signalplot.GetBinContent(signalplot.GetNbinsX() + 1) + signalplot.GetBinContent(signalplot.GetNbinsX()))
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

    #buid stack
    stack = ROOT.THStack("stack","")
    ZZplot.SetFillColor(ROOT.kOrange+3)
    stack.Add(ZZplot)
    ttbarplot.SetFillColor(ROOT.kOrange+4)
    stack.Add(ttbarplot)
    WWplot.SetFillColor(ROOT.kOrange+1)
    stack.Add(WWplot)
    WZplot.SetFillColor(ROOT.kOrange+2)
    stack.Add(WZplot)
    DYplot.SetFillColor(ROOT.kOrange)
    stack.Add(DYplot)
    stack.SetTitle(title)

    #plot legends, ranges
    legend = ROOT.TLegend(0.7,0.83,0.95,0.97)
    legend.SetTextFont(60)
    legend.SetTextSize(0.02)
#    legend.AddEntry(signalplot,"signal %.2f"%(signalplot.Integral()))
    if compare_data:
        legend.AddEntry(dataplot,"data %.2f"%(dataplot.Integral()))
    legend.AddEntry(DYplot, "DY %.2f"%(DYplot.Integral()))
    legend.AddEntry(WWplot, "WW %.2f"%(WWplot.Integral()))
    legend.AddEntry(WZplot, "WZ %.2f"%(WZplot.Integral()))
    legend.AddEntry(ZZplot,"ZZ %.2f"%(ZZplot.Integral()))
    legend.AddEntry(ttbarplot,"ttbar %.2f"%(ttbarplot.Integral()))

    if log==True:
        DYplot.GetYaxis().SetRangeUser(10e-2,10e8)
        WWplot.GetYaxis().SetRangeUser(10e-2,10e8)
        WZplot.GetYaxis().SetRangeUser(10e-2,10e8)
        ZZplot.GetYaxis().SetRangeUser(10e-2,10e8)
        ttbarplot.GetYaxis().SetRangeUser(10e-2,10e8)
#        signalplot.GetYaxis().SetRangeUser(10e-2,10e8)
        if compare_data:
            dataplot.GetYaxis().SetRangeUser(10e-2,10e8)

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
    if log==True:
#        signalplot.Draw("Hist")
        stack.Draw("Hist")
#        signalplot.Draw("H same")
        if compare_data:
            dataplot.Draw("E0 same")

    if log==False:
        stack.Draw("Hist")
#        signalplot.Draw("H same")
        if compare_data:
            dataplot.Draw("E0 same")
    legend.Draw()

    #print and save
    if log==True:
        if compare_data==False:
            canvas.SaveAs("../plots/" + plotname + "_s+b_log.png")
        if compare_data==True:
            canvas.SaveAs("../plots/" + plotname + "_mc+data_log.png")
    if log==False:
        if compare_data==False:
            canvas.SaveAs("../plots/" + plotname + "_s+b_linear.png")
        if compare_data==True:
            canvas.SaveAs("../plots/" + plotname + "_mc+data_linear.png")

ROOT.gStyle.SetOptStat(0000)

listofplots1=["mu1_pt", "mu1_pt_pre", "mu1_pt_post", "mu2_pt", "mu2_pt_pre", "mu2_pt_post",
                "nGood_PV_pre", "nGood_PV_post","nCand_Muons_pre","nCand_Muons_post","nCand_trigObj_pre","nCand_trigObj_post",
                "mu1_trkRelIso_pre", "mu1_trkRelIso_post", "mu2_trkRelIso_pre", "mu2_trkRelIso_post",
                "mu1_highPtId_pre", "mu1_highPtId_post", "mu2_highPtId_pre", "mu2_highPtId_post", ]

for plot in listofplots1:
    title=plot
    draw_plot(plot, title, False, False, False)
    draw_plot(plot, title, True, False, False)
