import os,sys
import numpy as np
import ROOT

def setpalette(g2):
    ROOT.gPad.Update()
    h2 = g2.GetHistogram()
    palette = h2.GetListOfFunctions().FindObject("palette")
    palette.SetX2NDC(0.925)

limdir = sys.argv[1]

drawObserved = False
doLog = False

massl = []
f2bd  = dict()
obsd  = dict()
expd  = dict()
m2sd  = dict()
m1sd  = dict()
p1sd  = dict()
p2sd  = dict()

fin = open("%s/limits_nomodel.txt"%(limdir),"r")
for l in fin.readlines():
    if l.startswith("#"):
        continue
    ls = l.split(",")
    if float(ls[0]) not in massl:
        massl.append(float(ls[0]))
    if float(ls[0]) not in f2bd:
        f2bd[float(ls[0])] = []
        obsd[float(ls[0])] = dict()
        expd[float(ls[0])] = dict()
        m2sd[float(ls[0])] = dict()
        m1sd[float(ls[0])] = dict()  
        p1sd[float(ls[0])] = dict()
        p2sd[float(ls[0])] = dict()
    f2bd[float(ls[0])].append(float(ls[1]))
    obsd[float(ls[0])][float(ls[1])] = float(ls[2])
    expd[float(ls[0])][float(ls[1])] = float(ls[3])
    m2sd[float(ls[0])][float(ls[1])] = float(ls[4])
    m1sd[float(ls[0])][float(ls[1])] = float(ls[5])  
    p1sd[float(ls[0])][float(ls[1])] = float(ls[6])
    p2sd[float(ls[0])][float(ls[1])] = float(ls[7])        

fin.close()

massv = np.array(massl,"d")

ngp = 0
g2obs = ROOT.TGraph2D()
g2exp = ROOT.TGraph2D()
for m in massl:
    for fn,f in enumerate(f2bd[m]):
        g2obs.SetPoint(ngp,m,f,obsd[m][f])
        g2exp.SetPoint(ngp,m,f,expd[m][f])
        ngp = ngp+1

miny = 999.
maxy = -1.0
obsv  = []
expv  = []
g1obs = []
g1exp = []
for fn,f in enumerate(f2bd[massl[0]]):
    obsv.append(np.array([],"d"))
    expv.append(np.array([],"d"))
    for m in massl:
        obsv[fn] = np.append(obsv[fn],obsd[m][f])
        expv[fn] = np.append(expv[fn],expd[m][f])
    g1obs.append(ROOT.TGraph(len(massv),massv,obsv[fn]))
    g1obs[fn].SetLineColor(ROOT.kAzure+fn)
    g1obs[fn].SetLineWidth(2)
    g1exp.append(ROOT.TGraph(len(massv),massv,expv[fn]))
    g1exp[fn].SetLineColor(ROOT.kAzure+fn)
    g1exp[fn].SetLineWidth(2)
    if np.amin(obsv[fn])<miny:
        miny=np.amin(obsv[fn])*0.9
    if np.amin(expv[fn])<miny:
        miny=np.amin(expv[fn])*0.9
    if np.amax(obsv[fn])>maxy:
        maxy=np.amax(obsv[fn])*1.1
    if np.amax(expv[fn])>maxy:
        maxy=np.amax(expv[fn])*1.1

miny= 2.0
maxy=20.0

leg = ROOT.TLegend(0.65,0.45,0.85,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)
if drawObserved:
    leg.SetHeader("Observed limit")
else:
    leg.SetHeader("Expected limit")
for fn,f in enumerate(f2bd[massl[0]]):
    leg.AddEntry(g1exp[fn],"f_{#geq 2 b-tags}=%.2f"%f,"L")

haxis = ROOT.TH1D("haxis","",10,massv[0],massv[len(massv)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("95% CL upper limit on number of events")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(miny)
haxis.SetMaximum(maxy)
haxis.GetYaxis().SetRangeUser(miny,maxy)

ROOT.gStyle.SetOptStat(0)
can = ROOT.TCanvas("can","",600,600)
can.cd()
ROOT.gPad.SetTicky()
if doLog:
    ROOT.gPad.SetLogy()

haxis.Draw()

for fn,f in enumerate(f2bd[massl[0]]):
    if drawObserved:
        g1obs[fn].Draw("L")
    else:
        g1exp[fn].Draw("L")

leg.Draw("same")

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/limits_1D_nomodel.png"%(limdir))

can.Update()
can.Clear()

if doLog:
    ROOT.gPad.SetLogz()
if drawObserved:
    g2obs.Draw("colz")
    can.Update()
    g2obs.SetTitle("")
    g2obs.GetXaxis().SetTitle("Mass [GeV]")
    g2obs.GetYaxis().SetTitle("f_{#geq 2 b-tags}")
    g2obs.GetZaxis().SetTitle("95% CL observed upper limit on number of events")
    g2obs.GetXaxis().SetLabelSize(0.025)
    g2obs.GetYaxis().SetLabelSize(0.025)
    g2obs.GetZaxis().SetLabelSize(0.025)
    g2obs.SetMinimum(miny)
    g2obs.SetMaximum(maxy)
    g2obs.GetZaxis().SetRangeUser(miny,maxy)
    setpalette(g2obs)
else:
    g2exp.Draw("colz")
    can.Update()
    g2exp.SetTitle("")
    g2exp.GetXaxis().SetTitle("Mass [GeV]")
    g2exp.GetYaxis().SetTitle("f_{#geq 2 b-tags}")
    g2exp.GetZaxis().SetTitle("95% CL expected upper limit on number of events")
    g2exp.GetXaxis().SetLabelSize(0.025)
    g2exp.GetYaxis().SetLabelSize(0.025)
    g2exp.GetZaxis().SetLabelSize(0.025)
    g2exp.SetMinimum(miny)
    g2exp.SetMaximum(maxy)
    g2exp.GetZaxis().SetRangeUser(miny,maxy)
    setpalette(g2exp)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/limits_2D_nomodel.png"%(limdir))
