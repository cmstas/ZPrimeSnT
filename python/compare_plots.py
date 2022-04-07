from curses import can_change_color
from hashlib import new
from numbers import Integral
from signal import signal
from tkinter.tix import Tree
import ROOT
import copy

def draw_plot(plotname1="fatjet_msoftdrop", plotname2="fatjet_msoftdrop", title="myTitle", log=True, DoRatio=True):
    #open file
    inputfile1 = ROOT.TFile("../outfiles/output.root")
    inputfile2 = ROOT.TFile("../outfiles/output.root")

    #get historam
    inputplot1 = inputfile1.Get(plotname1)
    inputplot2 = inputfile2.Get(plotname2)

    inputplot1.Rebin(4)
    inputplot2.Rebin(4)

    #draw overflow
    inputplot1.SetBinContent(1, inputplot1.GetBinContent(1) + inputplot1.GetBinContent(0))
    inputplot1.SetBinContent(inputplot1.GetNbinsX(), inputplot1.GetBinContent(inputplot1.GetNbinsX() + 1) + inputplot1.GetBinContent(inputplot1.GetNbinsX()))
    inputplot2.SetBinContent(1, inputplot2.GetBinContent(1) + inputplot2.GetBinContent(0))
    inputplot2.SetBinContent(inputplot2.GetNbinsX(), inputplot2.GetBinContent(inputplot2.GetNbinsX() + 1) + inputplot2.GetBinContent(inputplot2.GetNbinsX()))

    #plot legends, ranges
    inputplot1.SetLineColor(ROOT.kBlue)
    inputplot2.SetLineColor(ROOT.kRed)
    legend = ROOT.TLegend(0.7,0.83,0.95,0.97)
    legend.SetTextFont(60)
    legend.SetTextSize(0.02)
    legend.AddEntry(inputplot1,plotname1+" %.2f"%(inputplot1.Integral()))
    legend.AddEntry(inputplot2,plotname2+" %.2f"%(inputplot2.Integral()))

    if log==True:
        inputplot1.GetYaxis().SetRangeUser(10e-2,10e5)
        inputplot2.GetYaxis().SetRangeUser(10e-2,10e5)

    #define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    if DoRatio==True:
        ratioplot=copy.deepcopy(inputplot1)
        ratioplot.Divide(inputplot2)
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
    inputplot1.Draw("Hist")
    inputplot2.Draw("H same")

    legend.Draw()

    #print and save
    if log==True:
        canvas.SaveAs("../plots/" + plotname1 + "_log.png")
    if log==False:
        canvas.SaveAs("../plots/" + plotname2 + "_linear.png")

ROOT.gStyle.SetOptStat(0000)

listofplots1=["MuonTunePPtResolution8"]
listofplots2=["MuonPFPtResolution8"]

for plot1 in listofplots1:
    for plot2 in listofplots2:
        draw_plot(plot1, plot2, plot1, False, False)
        draw_plot(plot1, plot2, plot1, True, False)