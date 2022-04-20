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

def draw_plot(plotname="fatjet_msoftdrop", title="myTitle", log=True, plotData=False, doRatio=True, lumi=59.83, year="2018"):

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

    #open file
    signalfiles = []
    ZToMuMufiles = []
    for mass in args.signalMass: 
        signalfiles.append(ROOT.TFile(args.inDir+"output_Y3_M"+str(mass)+"_2018.root"))
    for m1,m2 in zip(["50","120","200","400","800","1400","2300","3500","4500","6000"],["120","200","400","800","1400","2300","3500","4500","6000","Inf"]): 
        ZToMuMufiles.append(ROOT.TFile(args.inDir+"output_ZToMuMu_"+m1+"_"+m2+"_2018.root"))
    ttbarfile =  ROOT.TFile(args.inDir+"output_ttbar_2018.root")
    tWfile =     ROOT.TFile(args.inDir+"output_tW_2018.root")
    tbarWfile =  ROOT.TFile(args.inDir+"output_tbarW_2018.root")
    TTWfile =    ROOT.TFile(args.inDir+"output_TTW_2018.root")
    TTZfile =    ROOT.TFile(args.inDir+"output_TTZ_2018.root")
    TTHNobbfile= ROOT.TFile(args.inDir+"output_TTHToNonbb_2018.root")
    TTHbbfile=   ROOT.TFile(args.inDir+"output_TTHTobb_2018.root")
    WWfile =     ROOT.TFile(args.inDir+"output_WW_2018.root")
    ZZfile =     ROOT.TFile(args.inDir+"output_ZZ_2018.root")
    WZfile =     ROOT.TFile(args.inDir+"output_WZ_2018.root")
    if plotData: 
        datafile = ROOT.TFile(args.inDir+"data_2018_2_selected.root")

    #get historam
    signalplots = []
    ZToMuMuplots = []
    for i in range(len(args.signalMass)): 
        signalplots.append(get_plot(signalfiles[i],plotname,lineColor=ROOT.kViolet-9+i,lineWidth=2))
        if args.shape and signalplots[i].Integral(0,-1)>0.0:
            if "cutflow" not in plotname:
                signalplots[i].Scale(1.0/signalplots[i].Integral(0,-1))
            else:
                signalplots[i].Scale(1.0/signalplots[i].GetBinContent(1))
    if plotData: 
        dataplot = get_plot(datafile,plotname,lineColor=ROOT.kBlack,lineWidth=2)
    for i in range(len(ZToMuMufiles)): 
        ZToMuMuplots.append(get_plot(ZToMuMufiles[i],plotname,fillColor=ROOT.kGreen+1))
    ttbarplot = get_plot(ttbarfile,plotname,fillColor=ROOT.kAzure+1)
    tWplot = get_plot(tWfile,plotname,fillColor=ROOT.kAzure+2)
    tbarWplot = get_plot(tbarWfile,plotname,fillColor=ROOT.kAzure+2)
    TTWplot = get_plot(TTWfile,plotname,fillColor=ROOT.kAzure+4)
    TTZplot = get_plot(TTZfile,plotname,fillColor=ROOT.kAzure+4)
    TTHNobbplot = get_plot(TTHNobbfile,plotname,fillColor=ROOT.kAzure+4)
    TTHbbplot = get_plot(TTHNobbfile,plotname,fillColor=ROOT.kAzure+4)
    WWplot = get_plot(WWfile,plotname,fillColor=ROOT.kOrange-3)
    ZZplot = get_plot(ZZfile,plotname,fillColor=ROOT.kOrange-2)
    WZplot = get_plot(WZfile,plotname,fillColor=ROOT.kOrange-1)

    #add histos
    ZToMuMuplot = ZToMuMuplots[0].Clone("ZToMuMu")
    for i in range(1,len(ZToMuMuplots)): 
        ZToMuMuplot.Add(ZToMuMuplots[i])
    ST_tWplot = tWplot.Clone("ST_tW")
    ST_tWplot.Add(tbarWplot)
    TTXplot = TTWplot.Clone("TTX")
    TTXplot.Add(TTZplot)
    TTXplot.Add(TTHNobbplot)
    TTXplot.Add(TTHbbplot)

    totalSM = ZToMuMuplot.Clone("totalSM")
    totalSM.Add(ttbarplot)
    totalSM.Add(ST_tWplot)
    totalSM.Add(TTXplot)
    totalSM.Add(WWplot)
    totalSM.Add(ZZplot)
    totalSM.Add(WZplot)
    totalScale   = totalSM.Integral(0,-1)
    if "cutflow" in plotname:
        totalScale = totalSM.GetBinContent(1)

    if args.shape and totalScale>0.0:
        ZToMuMuplot.Scale(1.0/totalScale)
        ttbarplot.Scale(1.0/totalScale)
        ST_tWplot.Scale(1.0/totalScale)
        TTXplot.Scale(1.0/totalScale)
        WWplot.Scale(1.0/totalScale)
        ZZplot.Scale(1.0/totalScale)
        WZplot.Scale(1.0/totalScale)

    signalXSecScale = { }
    if log==False and args.signalScale and not args.shape:
        for i,mass in enumerate(args.signalMass):
            sigIntegral = signalplots[i].Integral(0,-1)
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
            signalplots[i].Scale(signalXSecScale[str(mass)])

    #build stack
    stack = ROOT.THStack("stack","")
    stack.Add(WZplot)
    stack.Add(ZZplot)
    stack.Add(WWplot)
    stack.Add(TTXplot)
    stack.Add(ST_tWplot)
    stack.Add(ttbarplot)
    stack.Add(ZToMuMuplot)
    stack.SetTitle(title)

    #plot legends, ranges
    legend = ROOT.TLegend(0.65,0.65,0.89,0.89)
    if args.extendedLegend:
        legend = ROOT.TLegend(0.55,0.55,0.89,0.89)
    legend.SetLineColor(0)
    legend.SetLineWidth(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    #legend.SetTextSize(0.02)

    if args.extendedLegend:
        for i,mass in enumerate(args.signalMass): 
            if log==False and args.signalScale and not args.shape and signalXSecScale[str(mass)]>1.5:
                if "cutflow" not in plotname:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) %1.2E (x%1.1E)"%(signalplots[i].Integral(0,-1),float(signalXSecScale[str(mass)])),"L")
                else:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) %1.2E (x%1.1E)"%(signalplots[i].GetBinContent(1),float(signalXSecScale[str(mass)])),"L")
            else:
                if "cutflow" not in plotname:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) %1.2E"%(signalplots[i].Integral(0,-1)),"L")
                else:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) %1.2E"%(signalplots[i].GetBinContent(1)),"L")
            
        if "cutflow" not in plotname:
            if plotData: 
                legend.AddEntry(dataplot,"data %1.2E"%(dataplot.Integral(0,-1)),"PL")
            legend.AddEntry(ZToMuMuplot, "DY(#mu#mu) %1.2E"%(ZToMuMuplot.Integral(0,-1)),"F")
            legend.AddEntry(ttbarplot,"t#bar{t} %1.2E"%(ttbarplot.Integral(0,-1)),"F")
            legend.AddEntry(ST_tWplot,"tW %1.2E"%(ST_tWplot.Integral(0,-1)),"F")
            legend.AddEntry(TTXplot,"t#bar{t}X %1.2E"%(TTXplot.Integral(0,-1)),"F")
            legend.AddEntry(WWplot,"WW %1.2E"%(WWplot.Integral(0,-1)),"F")
            legend.AddEntry(ZZplot,"ZZ %1.2E"%(ZZplot.Integral(0,-1)),"F")
            legend.AddEntry(WZplot,"WZ %1.2E"%(WZplot.Integral(0,-1)),"F")
        else:
            if plotData: 
                legend.AddEntry(dataplot,"data %1.2E"%(dataplot.GetBinContent(1)),"PL")
            legend.AddEntry(ZToMuMuplot, "DY(#mu#mu) %1.2E"%(ZToMuMuplot.GetBinContent(1)),"F")
            legend.AddEntry(ttbarplot,"t#bar{t} %1.2E"%(ttbarplot.GetBinContent(1)),"F")
            legend.AddEntry(TTXplot,"t#bar{t}X %1.2E"%(TTXplot.GetBinContent(1)),"F")
            legend.AddEntry(ST_tWplot,"tW %1.2E"%(ST_tWplot.GetBinContent(1)),"F")
            legend.AddEntry(WWplot,"WW %1.2E"%(WWplot.GetBinContent(1)),"F")
            legend.AddEntry(ZZplot,"ZZ %1.2E"%(ZZplot.GetBinContent(1)),"F")
            legend.AddEntry(WZplot,"WZ %1.2E"%(WZplot.GetBinContent(1)),"F")
    
    else:
        for i,mass in enumerate(args.signalMass): 
            if log==False and args.signalScale and not args.shape and signalXSecScale[str(mass)]>1.5:
                if "cutflow" not in plotname:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) x%1.1E"%(float(signalXSecScale[str(mass)])),"L")
                else:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV) x%1.1E"%(float(signalXSecScale[str(mass)])),"L")
            else:
                if "cutflow" not in plotname:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV)","L")
                else:
                    legend.AddEntry(signalplots[i],"Y3 ("+str(mass)+" GeV)","L")
            
        if "cutflow" not in plotname:
            if plotData: 
                legend.AddEntry(dataplot,"data","PL")
            legend.AddEntry(ZToMuMuplot, "DY(#mu#mu)","F")
            legend.AddEntry(ttbarplot,"t#bar{t}","F")
            legend.AddEntry(ST_tWplot,"tW","F")
            legend.AddEntry(TTXplot,"t#bar{t}X","F")
            legend.AddEntry(WWplot,"WW","F")
            legend.AddEntry(ZZplot,"ZZ","F")
            legend.AddEntry(WZplot,"WZ","F")
        else:
            if plotData: 
                legend.AddEntry(dataplot,"data","PL")
            legend.AddEntry(ZToMuMuplot, "DY(#mu#mu)","F")
            legend.AddEntry(ttbarplot,"t#bar{t}","F")
            legend.AddEntry(TTXplot,"t#bar{t}X","F")
            legend.AddEntry(ST_tWplot,"tW","F")
            legend.AddEntry(WWplot,"WW","F")
            legend.AddEntry(ZZplot,"ZZ","F")
            legend.AddEntry(WZplot,"WZ","F")
    
    #define canvas
    canvas = ROOT.TCanvas("canvas","canvas",800,800)

    if doRatio==True:
        MCplot = copy.deepcopy(ZToMuMuplot)
        MCplot.Add(ttbarplot)
        MCplot.Add(ST_tWplot)
        MCplot.Add(WWplot)
        MCplot.Add(TTXplot)
        MCplot.Add(ZZplot)
        MCplot.Add(WZplot)
        ratioplot=copy.deepcopy(dataplot)
        ratioplot.Divide(MCplot)
        ratioplot.SetTitle(";"+title+";Data / MC")
        pad1 = ROOT.TPad("pad1","pad1",0,0.3,1,1)
        pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.3)
        pad1.Draw()
        pad2.Draw()
        pad2.cd()
        ratioplot.Draw("E0")

    if doRatio==False:
        pad1 = ROOT.TPad("pad1","pad1",0,0,1,1)
        pad1.Draw()

    pad1.cd()
    if log==True:
        pad1.SetLogy()

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
        if histMax < signalplots[i].GetMaximum(): 
            histMax = signalplots[i].GetMaximum()
        signalplots[i].Draw("HIST same")
    if plotData: 
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

    expoffset=0.03
    if log==True or 1.1*histMax<1000.0:
        expoffset=0
    latex.DrawLatex(0.9, 0.92+expoffset, yearenergy);
    latexCMS.DrawLatex(0.11,0.92+expoffset,"CMS");
    latexCMSExtra.DrawLatex(0.22,0.92+expoffset, cmsExtra);

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

    #print and save
    extension = ""
    if plotData:
        extension = extension+"_mc+data"
    else:
        extension = extension+"_s+b"
    if log:
        extension = extension+"_logY"
    if args.shape:
        extension = extension+"_areaNormalized"
    
    canvas.SaveAs(args.outDir + plotname + extension + ".png")

    if("pt" in plotname):
        canvas.Clear()
        canvas.cd()
        
        if doRatio==True:
            if ratioplot.GetXaxis().GetBinLowEdge(1)<=0.0:
                ratioplot.GetXaxis().SetRangeUser(1.0, ratioplot.GetXaxis().GetBinUpEdge(ratioplot.GetNbinsX()))
            ratioplot.SetTitle(";"+title+";Data / MC")
            pad1 = ROOT.TPad("pad1","pad1",0,0.3,1,1)
            pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.3)
            pad1.Draw()
            pad2.Draw()
            pad2.cd()
            pad2.SetLogx()
            ratioplot.Draw("E0")

        if doRatio==False:
            pad1 = ROOT.TPad("pad1","pad1",0,0,1,1)
            pad1.Draw()
            
        pad1.cd()
        if log==True:
            pad1.SetLogy()
        pad1.SetLogx()
        
        #plot data,stack, signal, data  
        stack.Draw("HIST")
        if stack.GetXaxis().GetBinLowEdge(1)<=0.0:
            stack.GetXaxis().SetRangeUser(1.0, stack.GetXaxis().GetBinUpEdge(stack.GetXaxis().GetNbins()))
        stack.GetXaxis().SetTitle(totalSM.GetXaxis().GetTitle())
        stack.GetYaxis().SetTitle(totalSM.GetYaxis().GetTitle())
        if args.shape:
            stack.GetYaxis().SetTitle("A.U.")
        stack.GetYaxis().SetLabelSize(0.03)
        stack.GetYaxis().SetMaxDigits(3)
        histMax = 0.0
        for i,mass in enumerate(args.signalMass):
            if histMax < signalplots[i].GetMaximum(): 
                histMax = signalplots[i].GetMaximum()
            signalplots[i].Draw("HIST same")
        if plotData: 
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

        #print and save
        extension = ""
        if plotData:
            extension = extension+"_mc+data"
        else:
            extension = extension+"_s+b"
        extension = extension+"_logX"
        if log:
            extension = extension+"_logY"
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