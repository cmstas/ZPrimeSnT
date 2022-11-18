import os,sys
import numpy as np
import ROOT

model = sys.argv[1]
limdir = sys.argv[2]

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
sigpl = []
sigfl = []
fin = open("%s/significance_%s.txt"%(limdir,model),"r")
for l in fin.readlines():
    if l.startswith("#"):
        continue
    ls = l.split(",")
    if ls[0]!=model:
        continue
    massl.append(float(ls[1]))
    sigfl.append(float(ls[2]))
    if float(ls[2])>1e-2:
        sigpl.append(float(ls[2]))
    else:
        sigpl.append(0.0)
fin.close()

massv = np.array(massl,"d")
sigpv = np.array(sigpl,"d")
sigfv = np.array(sigfl,"d")

miny = -5.0
maxy = +3.0

gsigp = ROOT.TGraph(len(massv),massv,sigpv)
gsigp.SetLineColor(1)
gsigp.SetLineStyle(1)
gsigp.SetLineWidth(2)

gsigf = ROOT.TGraph(len(massv),massv,sigfv)
gsigf.SetLineColor(1)
gsigf.SetLineStyle(1)
gsigf.SetLineWidth(2)

leg = ROOT.TLegend(0.15,0.80,0.45,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)
modelLeg = model
if model=="Y3":
    modelLeg="Y_{3}"
elif model=="DY3":
    modelLeg="DY_{3}"
elif model=="DYp3":
    modelLeg="DY'_{3}"
elif model=="B3mL2":
    modelLeg="B_{3}-L_{2}"
leg.SetHeader("%s signal"%modelLeg)
#leg.AddEntry(gexp,"Significance","L")

haxis = ROOT.TH2D("haxis","",10,massv[0],massv[len(massv)-1],8,miny,maxy)
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("Observed significance [std. dev.]")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.035)
haxis.GetYaxis().SetRangeUser(miny,maxy)
haxis.GetXaxis().SetMoreLogLabels()

line = ROOT.TLine(massv[0],0.0,massv[len(massv)-1],0.0)
line.SetLineColor(ROOT.kBlack)
line.SetLineStyle(2)

ROOT.gStyle.SetOptStat(0)
can = ROOT.TCanvas("can","",600,600)
can.cd()
ROOT.gPad.SetLogx()
ROOT.gPad.SetTicky()

haxis.Draw()
gsigf.Draw("L")
line.Draw("same")
leg.Draw("same")

drawLabels()

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/significance_twosided_%s.png"%(limdir,model))
can.SaveAs("%s/significance_twosided_%s.pdf"%(limdir,model))

can.cd()
can.Clear()

haxis.GetYaxis().SetRangeUser(0,maxy)
haxis.Draw()
gsigp.Draw("L")
leg.Draw("same")

drawLabels()

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/significance_onesided_%s.png"%(limdir,model))
can.SaveAs("%s/significance_onesided_%s.pdf"%(limdir,model))
