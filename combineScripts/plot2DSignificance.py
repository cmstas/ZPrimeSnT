import os,sys
import numpy as np
import ROOT

limdir = sys.argv[1]
doLog = False

def setpalette(g2):
    ROOT.gPad.Update()
    h2 = g2.GetHistogram()
    palette = h2.GetListOfFunctions().FindObject("palette")
    palette.SetX2NDC(0.925)

def drawLabels(year="all",lumi=59.83+41.48+19.5+16.8,plotData=True):
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
    latexSel = ROOT. TLatex()
    latexSel.SetTextAlign(11)
    latexSel.SetTextFont(42)
    latexSel.SetTextSize(0.02-0.1*legoffset)
    latexSel.SetNDC(True)

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

    # Draw CMS headers
    expoffset=0
    latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
    latexCMS.DrawLatex(0.11,0.91+expoffset,"CMS");
    latexCMSExtra.DrawLatex(0.20,0.91+expoffset, cmsExtra);

massl = []
f2bd  = dict()
sigpd = dict()
sigfd  = dict()

fin = open("%s/significance_nomodel.txt"%(limdir),"r")
for l in fin.readlines():
    if l.startswith("#"):
        continue
    ls = l.split(",")
    if float(ls[0]) not in massl:
        massl.append(float(ls[0]))
    if float(ls[0]) not in f2bd:
        f2bd[float(ls[0])] = []
        sigpd[float(ls[0])] = dict()
        sigfd[float(ls[0])] = dict()
    f2bd[float(ls[0])].append(float(ls[1]))
    sigfd[float(ls[0])][float(ls[1])] = float(ls[2])
    if float(ls[2]) > 1e-2:
        sigpd[float(ls[0])][float(ls[1])] = float(ls[2])
    else:
        sigpd[float(ls[0])][float(ls[1])] = float(0.0)

fin.close()

massv = np.array(massl,"d")

ngp = 0
g2sigp = ROOT.TGraph2D()
g2sigf = ROOT.TGraph2D()
g2sigp.SetName("onesidedsig2d")
g2sigf.SetName("twosidedsig2d")
g2sigp.SetNpx(len(massl)*5+1)
g2sigp.SetNpy(len(f2bd[massl[0]])*5+1)
g2sigf.SetNpx(len(massl)*5+1)
g2sigf.SetNpy(len(f2bd[massl[0]])*5+1)

for m in massl:
    for fn,f in enumerate(f2bd[m]):
        g2sigp.SetPoint(ngp,m,f,sigpd[m][f])
        g2sigf.SetPoint(ngp,m,f,sigfd[m][f])
        ngp = ngp+1

miny = -5.0
maxy = +5.0
sigpv  = []
sigfv  = []
g1sigp = []
g1sigf = []
ROOT.gStyle.SetPalette(ROOT.kCMYK)
colsGrad = ROOT.TColor.GetPalette()
for fn,f in enumerate(f2bd[massl[0]]):
    sigpv.append(np.array([],"d"))
    sigfv.append(np.array([],"d"))
    for m in massl:
        sigpv[fn] = np.append(sigpv[fn],sigpd[m][f])
        sigfv[fn] = np.append(sigfv[fn],sigfd[m][f])
    g1sigp.append(ROOT.TGraph(len(massv),massv,sigpv[fn]))
    g1sigp[fn].SetLineColor(colsGrad.At(fn*25))
    g1sigp[fn].SetLineWidth(2)
    g1sigf.append(ROOT.TGraph(len(massv),massv,sigfv[fn]))
    g1sigf[fn].SetLineColor(colsGrad.At(fn*25))
    g1sigf[fn].SetLineWidth(2)

leg = ROOT.TLegend(0.15,0.65,0.55,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)
leg.SetNColumns(2)
#leg.SetHeader("Significance")
for fn,f in enumerate(f2bd[massl[0]]):
    if f!=0.0 and f!=0.25 and f!=0.5 and f!=0.75 and f!=1.0:
        continue
    #leg.AddEntry(g1obs[fn],"f_{2b}=%.2f"%f,"L")
    leg.AddEntry(g1sigp[fn],"f_{2b}=%.2f"%f,"L")

haxis = ROOT.TH2D("haxis","",10,massv[0],massv[len(massv)-1],10,miny,maxy)
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("Observed significance [std. dev.]")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetRangeUser(miny,maxy)
haxis.GetXaxis().SetMoreLogLabels()

ROOT.gStyle.SetOptStat(0)
can = ROOT.TCanvas("can","",600,600)
can.cd()
#ROOT.gPad.SetLogx()
ROOT.gPad.SetTicky()

haxis.Draw()

for fn,f in enumerate(f2bd[massl[0]]):
    if f!=0.0 and f!=0.25 and f!=0.5 and f!=0.75 and f!=1.0:
        continue
    g1sigf[fn].Draw("L")

line = ROOT.TLine(massv[0],0.0,massv[len(massv)-1],0.0)
line.SetLineColor(ROOT.kBlack)
line.SetLineStyle(2)
line.Draw("same")

leg.Draw("same")

drawLabels()

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/significance_twosided_1D_nomodel.png"%(limdir))
can.SaveAs("%s/significance_twosided_1D_nomodel.pdf"%(limdir))

can.Update()
can.Clear()

can.cd()
#ROOT.gPad.SetLogx()
ROOT.gPad.SetTicky()

haxis.GetYaxis().SetRangeUser(0.0,3.0)
haxis.Draw()

for fn,f in enumerate(f2bd[massl[0]]):
    if f!=0.0 and f!=0.25 and f!=0.5 and f!=0.75 and f!=1.0:
        continue
    g1sigp[fn].Draw("L")

leg.Draw("same")

drawLabels()

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/significance_onesided_1D_nomodel.png"%(limdir))
can.SaveAs("%s/significance_onesided_1D_nomodel.pdf"%(limdir))

can.Update()
can.Clear()

ROOT.gStyle.SetPalette(ROOT.kBird)
ROOT.gPad.SetLogx()
ROOT.gPad.SetLogy(0)
minz= -3.25
maxz= 3.25
if doLog:
    ROOT.gPad.SetLogz()
g2sigf.Draw("colz")
can.Update()
g2sigf.SetTitle("")
g2sigf.GetXaxis().SetTitle("Mass [GeV]")
g2sigf.GetYaxis().SetTitle("f_{2b}")
g2sigf.GetZaxis().SetTitle("Observed significance")
g2sigf.GetXaxis().SetLabelSize(0.025)
g2sigf.GetYaxis().SetLabelSize(0.025)
g2sigf.GetZaxis().SetLabelSize(0.025)
g2sigf.GetXaxis().SetMoreLogLabels()
g2sigf.GetZaxis().SetMoreLogLabels()
g2sigf.SetMinimum(minz)
g2sigf.SetMaximum(maxz)
g2sigf.GetZaxis().SetRangeUser(minz,maxz)
setpalette(g2sigf)

drawLabels()

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/significance_twosided_2D_nomodel.png"%(limdir))
can.SaveAs("%s/significance_twosided_2D_nomodel.pdf"%(limdir))

can.Update()
can.Clear()

ROOT.gStyle.SetPalette(ROOT.kBird)
ROOT.gPad.SetLogx()
ROOT.gPad.SetLogy(0)
minz= 0.0
maxz= 2.1
if doLog:
    ROOT.gPad.SetLogz()
g2sigp.Draw("colz")
can.Update()
g2sigp.SetTitle("")
g2sigp.GetXaxis().SetTitle("Mass [GeV]")
g2sigp.GetYaxis().SetTitle("f_{2b}")
g2sigp.GetZaxis().SetTitle("Observed significance")
g2sigp.GetXaxis().SetLabelSize(0.025)
g2sigp.GetYaxis().SetLabelSize(0.025)
g2sigp.GetZaxis().SetLabelSize(0.025)
g2sigp.GetXaxis().SetMoreLogLabels()
g2sigp.GetZaxis().SetMoreLogLabels()
g2sigp.SetMinimum(minz)
g2sigp.SetMaximum(maxz)
g2sigp.GetZaxis().SetRangeUser(minz,maxz)
setpalette(g2sigp)

drawLabels()

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/significance_onesided_2D_nomodel.png"%(limdir))
can.SaveAs("%s/significance_onesided_2D_nomodel.pdf"%(limdir))

fout = ROOT.TFile("%s/significance_2D_nomodel.root"%(limdir), "RECREATE")
fout.cd()
g2sigp.Write()
g2sigf.Write()
fout.Close()
