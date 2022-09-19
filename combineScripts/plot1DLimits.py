import os,sys
import numpy as np
import ROOT

drawObserved = False

model = sys.argv[1]
limdir = sys.argv[2]

massl = []
obsl  = []
expl  = []
m2sl  = []
m1sl  = []
p1sl  = []
p2sl  = []

fin = open("%s/limits_%s.txt"%(limdir,model),"r")
for l in fin.readlines():
    if l.startswith("#"):
        continue
    ls = l.split(",")
    if ls[0]!=model:
        continue
    massl.append(float(ls[1]))
    obsl .append(float(ls[2]))
    expl .append(float(ls[3]))
    m2sl .append(float(ls[4]))
    m1sl .append(float(ls[5]))
    p1sl .append(float(ls[6]))
    p2sl .append(float(ls[7]))
fin.close()

massv = np.array(massl,"d")
obsv  = np.array(obsl ,"d")
expv  = np.array(expl ,"d")
m1sv  = np.array(m1sl ,"d")
p1sv  = np.array(p1sl ,"d")

miny = 999.
maxy = -1.0
if min(obsl)<miny:
    miny=min(obsl)*0.9
if min(m1sl)<miny:
    miny=min(m1sl)*0.9

if max(obsl)>maxy:
    maxy=max(obsl)*1.1
if max(p1sl)>maxy:
    maxy=max(p1sl)*1.1

miny=0.1
maxy=50.

gobs = ROOT.TGraph(len(massv),massv,obsv)
gobs.SetLineColor(1)
gobs.SetLineStyle(1)
gobs.SetLineWidth(2)

gexp = ROOT.TGraph(len(massv),massv,expv)
gexp.SetLineColor(2)
gexp.SetLineStyle(1)
gexp.SetLineWidth(2)

gm1s = ROOT.TGraph(len(massv),massv,m1sv)
gm1s.SetLineColor(2)
gm1s.SetLineStyle(2)
gm1s.SetLineWidth(1)

gp1s = ROOT.TGraph(len(massv),massv,p1sv)
gp1s.SetLineColor(2)
gp1s.SetLineStyle(2)
gp1s.SetLineWidth(1)

leg = ROOT.TLegend(0.15,0.65,0.35,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)
leg.SetHeader("%s model"%model)
if drawObserved:
    leg.AddEntry(gobs,"Observed","L")
leg.AddEntry(gexp,"Expected","L")

haxis = ROOT.TH1D("haxis","",10,massv[0],massv[len(massv)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("95% CL upper limit on #sigma/#sigma_{theory}")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(miny)
haxis.SetMaximum(maxy)
haxis.GetYaxis().SetRangeUser(miny,maxy)

line = ROOT.TLine(massv[0],1.0,massv[len(massv)-1],1.0)
line.SetLineColor(ROOT.kGray)
line.SetLineStyle(2)

ROOT.gStyle.SetOptStat(0)
can = ROOT.TCanvas("can","",600,600)
can.cd()
ROOT.gPad.SetTicky()
ROOT.gPad.SetLogy()

haxis.Draw()

gm1s.Draw("L")
gexp.Draw("L")
gp1s.Draw("L")
if drawObserved:
    gobs.Draw("L")

line.Draw("same")

leg.Draw("same")

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/limits_%s.png"%(limdir,model))
