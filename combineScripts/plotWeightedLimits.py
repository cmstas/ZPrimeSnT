import os,sys
import ROOT
import numpy as np
import pickle
sys.path.append('python')
from compute_width import calculate_Zpmumu_weight
from compute_width import calculate_width
from compute_width import get_model_name

def setpalette(h2):
    ROOT.gPad.Update()
    #h2 = g2.GetHistogram()
    palette = h2.GetListOfFunctions().FindObject("palette")
    palette.SetX2NDC(0.925)

luminosity = 137.61
useFixedMassGrid = False
useGenParamsVSMass = True
doAdditionalPlots = True

models = ["Y3","DY3","DYp3","B3mL2"]

colors = dict()
colors["Y3"]    = ROOT.kBlack
colors["DY3"]   = ROOT.kBlue
colors["DYp3"]  = ROOT.kRed
colors["B3mL2"] = ROOT.kMagenta

markers = dict()
markers["Y3"]    = 20
markers["DY3"]   = 21
markers["DYp3"]  = 22
markers["B3mL2"] = 23

model=sys.argv[1]
which=sys.argv[3]
lfile=sys.argv[2]+"/limits_3D_%s_%s.root"%(which,model)
lname="limit3d_%s_%s"%(which,model)
wrname="width_resolution_ratio_3d_%s"%model
if model not in models:
    print("Unknown model.")
    exit()

outdir=sys.argv[2]
fl = ROOT.TFile.Open(lfile)
hl = fl.Get(lname).Clone()
hl.SetDirectory(ROOT.gROOT)
hwr = fl.Get(wrname).Clone()
hwr.SetDirectory(ROOT.gROOT)
fl.Close()

xsbb = dict()
xssb = dict() 
fxs = ROOT.TFile.Open("data/xsec_interpolation_ZPrimeToMuMuSB_bestfit_13TeV_Allanach.root")
for tm in models:
    xsbb[tm] = fxs.Get("spline_%s_xsec_bb"%tm).Clone()
    xssb[tm] = fxs.Get("spline_%s_xsec_sb"%tm).Clone() 
fxs.Close()

aebb_nb1_model = dict()
aesb_nb1_model = dict()
aebb_nb2_model = dict()
aesb_nb2_model = dict()
fae = ROOT.TFile.Open("data/acceff_interpolation_Run2.root")
aebb_nb1 = fae.Get("spline_avg_acceff_bb_Nb_eq_1_Run2").Clone()
aebb_nb2 = fae.Get("spline_avg_acceff_bb_Nb_geq_2_Run2").Clone()
aesb_nb1 = fae.Get("spline_avg_acceff_sb_Nb_eq_1_Run2").Clone()
aesb_nb2 = fae.Get("spline_avg_acceff_sb_Nb_geq_2_Run2").Clone()
gaebb_nb1 =  ROOT.TGraph()
gaebb_nb1.SetLineColor(ROOT.kBlack)
gaebb_nb1.SetLineWidth(3)
gaebb_nb1.SetMarkerColor(ROOT.kBlack)
gaebb_nb1.SetMarkerStyle(20)
gaebb_nb1.SetMarkerSize(0.75)
gaebb_nb2 =  ROOT.TGraph()
gaebb_nb2.SetLineColor(ROOT.kBlack)
gaebb_nb2.SetLineWidth(3)
gaebb_nb2.SetMarkerColor(ROOT.kBlack)
gaebb_nb2.SetMarkerStyle(20)
gaebb_nb2.SetMarkerSize(0.75)
gaesb_nb1 =  ROOT.TGraph()
gaesb_nb1.SetLineColor(ROOT.kBlack)
gaesb_nb1.SetLineWidth(3)
gaesb_nb1.SetMarkerColor(ROOT.kBlack)
gaesb_nb1.SetMarkerStyle(20)
gaesb_nb1.SetMarkerSize(0.75)
gaesb_nb2 =  ROOT.TGraph()
gaesb_nb2.SetLineColor(ROOT.kBlack)
gaesb_nb2.SetLineWidth(3)
gaesb_nb2.SetMarkerColor(ROOT.kBlack)
gaesb_nb2.SetMarkerStyle(20)
gaesb_nb2.SetMarkerSize(0.75)
for tm in models:
    aebb_nb1_model[tm] = fae.Get("gr_%s_acceff_bb_Nb_eq_1_Run2"%tm).Clone()
    aebb_nb2_model[tm] = fae.Get("gr_%s_acceff_bb_Nb_geq_2_Run2"%tm).Clone()
    aesb_nb1_model[tm] = fae.Get("gr_%s_acceff_sb_Nb_eq_1_Run2"%tm).Clone()
    aesb_nb2_model[tm] = fae.Get("gr_%s_acceff_sb_Nb_geq_2_Run2"%tm).Clone()
    aebb_nb1_model[tm].SetLineColor(colors[tm])
    aebb_nb1_model[tm].SetLineWidth(2)
    aebb_nb1_model[tm].SetLineStyle(2)
    aebb_nb1_model[tm].SetFillColorAlpha(colors[tm],0.5)
    aesb_nb1_model[tm].SetLineColor(colors[tm])
    aesb_nb1_model[tm].SetLineWidth(2)
    aesb_nb1_model[tm].SetLineStyle(2)
    aesb_nb1_model[tm].SetFillColorAlpha(colors[tm],0.5)
    aebb_nb2_model[tm].SetLineColor(colors[tm])
    aebb_nb2_model[tm].SetLineWidth(2)
    aebb_nb2_model[tm].SetLineStyle(2)
    aebb_nb2_model[tm].SetFillColorAlpha(colors[tm],0.5)
    aesb_nb2_model[tm].SetLineColor(colors[tm])
    aesb_nb2_model[tm].SetLineWidth(2)
    aesb_nb2_model[tm].SetLineStyle(2)
    aesb_nb2_model[tm].SetFillColorAlpha(colors[tm],0.5)
fae.Close()

#masses = [250,400,550,700,850,1000,1250,1500,2000]
#massesFixed = [350,400,500,600,700,850,1000,1250,1500,2000]
massesFixed = [350,600,900,1200,1500,2000]
masses = []
mF = massesFixed[0]
mL = massesFixed[len(masses)-1]
if not useFixedMassGrid:
    mF = 350.0
    mL = 2000.0
    masses = [mF]
    tm = mF
    while tm < mL:
        if tm<400.0:
            tm=tm+5.0
        elif tm<700.0:
            tm=tm+10.0
        elif tm<1000.0:
            tm=tm+15.0
        elif tm<1500.0:
            tm=tm+25.0
        else:
            tm=tm+50.0
        masses.append(tm)
else:
    masses = massesFixed


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
    if year!="all" or (lumi>0.0 and lumi<100.0):
        if year!="all":
            yearenergy="%.1f fb^{-1} (%s, 13 TeV)"%(lumi,year)
        else:
            yearenergy="%.1f fb^{-1} (2016-2018, 13 TeV)"%(lumi)
    elif lumi>0.0:
        yearenergy="%.0f fb^{-1} (13 TeV)"%(lumi)
    else:
        yearenergy="13 TeV"
    if plotData:
        cmsExtra="Preliminary"
    else:
        cmsExtra="Simulation"

    # Draw CMS headers
    expoffset=0
    latex.DrawLatex(0.90, 0.91+expoffset, yearenergy);
    latexCMS.DrawLatex(0.11,0.91+expoffset,"CMS");
    latexCMSExtra.DrawLatex(0.20,0.91+expoffset, cmsExtra);

### Get fit contours from Allanach et al.:
fitfile=""
if model=="Y3":
    fitfile="tfhm_2d.dat"
elif model=="DY3":
    fitfile="dtfhm_2d.dat"
elif model=="DYp3":
    fitfile="dtfhmp_2d.dat"
elif model=="B3mL2":
    fitfile="tfhm_2d.dat"

with open("data/Allanach/%s"%fitfile, 'rb') as filehandle:
    data_for_plot = pickle.load(filehandle)
# Identify best-fit point
gzp_for_plot   = [data['gzp']     for data in data_for_plot]
theta_for_plot = [data['theta']    for data in data_for_plot]
dchi2_for_plot = [2*data['global'] for data in data_for_plot]
max_D_old      = max(dchi2_for_plot)
pos            = dchi2_for_plot.index(max_D_old)
max_dchi2 = 0.0
gzp_gf    = 0.0
theta_gf  = 0.0
if model=="Y3":
    max_dchi2 = 2*21.31500863005739
    gzp_gf    = 0.42551091
    theta_gf  = -0.14501005
elif model=="DY3":
    max_dchi2 = max_D_old
    gzp_gf    = gzp_for_plot[pos]
    theta_gf  = theta_for_plot[pos]
elif model=="DYp3":
    max_dchi2 = 2*19.32362591271114
    gzp_gf    = 0.25340287
    theta_gf  = -0.18055267
x = np.array(gzp_for_plot)
y = np.array(theta_for_plot)
z = np.array(dchi2_for_plot)
cols = np.unique(x).shape[0]
X = x.reshape(-1, cols)
Y = y.reshape(-1, cols)
Z = z.reshape(-1, cols)
idx = np.where(~np.isnan(X+Y+Z))
X = X[idx]
Y = Y[idx]
Z = Z[idx]

column1 = 0
column2 = 0
if model=="Y3":
    column1=8
    column2=20
elif model=="DY3":
    column1=9
    colimn2=column1
elif model=="DYp3":
    column1=6
    colimn2=column1
x1 = np.unique(x)[column1:]
x2 = np.unique(x)[column2:]
F = 0.0
if model=="Y3":
    F = 0.5 * np.arcsin(-0.09 / ((x1)**2+0.35*x1))
elif model=="DY3":
    F = 0.5*np.arcsin(0.0045 * 9 / (x1**2))
elif model=="DYp3":
    F = 0.5*np.arcsin(-0.0045 * 9 / ((x1)**2+0.2*x1))
elif model=="B3mL2":
    gzp_gf   = 0.05*3
    theta_gf = 0.10
    x1 = np.linspace(0.05,0.61,55)
    F = 0.5*np.arcsin(0.0005 / (x1*x1))
    x1 = x1*3

gfit  = ROOT.TGraph2D(len(X),X/3,Y,Z)
gfit.SetName("gfit")
gbest = ROOT.TGraph()
gbest.SetPoint(0,gzp_gf/3.0,theta_gf)
gbest.SetLineColor(colors[model])
gbest.SetMarkerColor(colors[model])
gbest.SetMarkerStyle(20)
gbest.SetMarkerSize(1.0)
gfunc = ROOT.TGraph(len(F),x1/3,F)
gfunc.SetLineColor(colors[model])
gfunc.SetLineStyle(4)
gcontlist = []
gcontlist.append(gfit.GetContourList(max_dchi2-2.41))
gcontlist.append(gfit.GetContourList(max_dchi2-5.99))

### Define scan over g_X and theta_23:
minx = 0.01
maxx = 0.30
nbx  = 30
mint = -0.5
maxt = 0
nbt  = 51
if model == 'DY3':
    mint = 0.0
    maxt = 0.5
if model == 'B3mL2':
    minx = 0.01
    maxx = 0.50
    nbx  = 50
    mint = 0.0
    maxt = 0.2
    nbt  = 21
xscan   = np.linspace(minx, maxx, nbx)
t23scan = np.linspace(mint, maxt, nbt)
### For B3-L2 redefine max for plotting:
if model=="B3mL2":
    maxx=0.15

### Get exclusion limits in theta_23 vs g_X plane for subset of mass points
g2d = []
limlist = []
mlist = []
for mn,m in enumerate(massesFixed):
    tb = hl.GetXaxis().FindBin(m)
    hl.GetXaxis().SetRange(tb,tb)
    g2d.append(ROOT.TGraph2D(hl.Project3D("zy")))
    g2d[mn].SetName("g2d_M%.0f"%m)
    g2d[mn].SetNpx(401)
    g2d[mn].SetNpy(401)
    if np.amin(g2d[mn].GetZ())<1.0 and np.amax(g2d[mn].GetZ())>1.0:
        limlist.append(g2d[mn].GetContourList(1.0))
        mlist.append(m)
    hl.GetXaxis().SetRange(0,-1)

### Legend for 2D limits: theta_23 vs g_X
legxoffset = 0.0
if model=="DYp3" or model=="B3mL2":
    legxoffset=0.575
leg = ROOT.TLegend(0.125+legxoffset,0.5,0.3+legxoffset,0.875)
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
leg.SetHeader("#scale[1.5]{%s (95%% CL)}"%modelLeg)

### Define min and max gx from Allanch fit (to be used):
mingx = 1.0
maxgx = 0.0
### For B3-L2, use values from Table 2 of https://arxiv.org/pdf/2110.13518.pdf
if model=="B3mL2":
    mingx = np.double(0.05)
    maxgx = np.double(0.62)

haxis = ROOT.TH1D("haxis","",1,minx,maxx)
haxis.SetLineColor(1)
haxis.SetMinimum(mint)
haxis.SetMaximum(maxt)
haxis.GetYaxis().SetRangeUser(mint,maxt)
haxis.GetXaxis().SetTitle("g_{X} [1 TeV/M_{X}]")
haxis.GetYaxis().SetTitle("#theta_{23}")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.0225)

ROOT.gStyle.SetOptStat(0)
can = ROOT.TCanvas("can","",600,600)
can.cd()
ROOT.gPad.SetTickx()
ROOT.gPad.SetTicky()
haxis.Draw()

for ln in reversed(range(len(gcontlist))):
    for gn in range(len(gcontlist[ln])):
        g = gcontlist[ln].At(gn)
        g.SetLineColor(colors[model])
        g.SetFillColorAlpha(colors[model],0.2+0.2*(ln-1))
        if model != "B3mL2":
            if np.amin(g.GetX())<mingx:
                mingx = np.amin(g.GetX())
            if np.amax(g.GetX())>maxgx:
                maxgx = np.amax(g.GetX())
            g.Draw("LF,same")
gbest.Draw("P,same")
gfunc.Draw("L,same")

ROOT.gStyle.SetPalette(ROOT.kCMYK)
#ROOT.gStyle.SetPalette(ROOT.kColorPrintableOnGrey)
colsGrad = ROOT.TColor.GetPalette()
for ln in range(len(limlist)):
    for gn in range(len(limlist[ln])):
        g = limlist[ln].At(gn)
        g.SetLineColor(colsGrad.At(ln*50))
        g.SetLineWidth(2)
        leg.AddEntry(g,"M_{X}=%.0f GeV"%mlist[ln],"L")
        if which=="expected":
            g.SetLineStyle(2)
        g.Draw("L,same")
leg.Draw("same")
drawLabels()
can.Update()
ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/limit_2d_t23_vs_gx_%s.png"%(outdir,model))
can.SaveAs("%s/limit_2d_t23_vs_gx_%s.pdf"%(outdir,model))

###

### Limits in g_X vs mass plane:

### Get exclusion contours from Allanach et al.:
exfile=[]
if model=="Y3":
    exfile.append("y3_fig06.csv")
elif model=="DY3":
    exfile.append("dy3_fig07.csv")
elif model=="DYp3":
    exfile.append("dy3p_fig08.csv")
elif model=="B3mL2":
    exfile.append("zprime_fig09.csv")
    exfile.append("zprime_fig10.csv")

exg2d=[]
exg2d95l=[]
for en in range(len(exfile)):
    fex = open("data/Allanach/%s"%exfile[en],"r")
    ex = []
    ey = []
    ez = []
    for ln,line in enumerate(fex.readlines()):
        if ln==0 or line.startswith("#"):
            continue
        ex.append(float(line.split(",")[2]))
        ey.append(float(line.split(",")[1]))
        tz = float(line.split(",")[len(line.split(","))-1])
        ez.append(tz)
    eys = [x for _,x in sorted(zip(ex,ey))]
    ezs = [x for _,x in sorted(zip(ex,ez))]
    exs = sorted(ex)
    ex = np.array(exs,"d")
    ey = np.array(eys,"d")
    ez = np.array(ezs,"d")
    exg2d.append(ROOT.TGraph2D(len(ex),ex,ey,ez))
    exg2d[en].SetName("exg2d%d"%en)
    exg2d[en].SetNpx(401)
    exg2d[en].SetNpy(401)
    gc = exg2d[en].GetContourList(0.95)
    gc.SetName("exg2d%d_contour"%en)
    exg2d95l.append(gc)

### Get exclusion limits in g_X plane vs mass plane for best-fit theta_23
tb = hl.GetZaxis().FindBin(theta_gf)
hl.GetZaxis().SetRange(tb,tb)
g2dvsm = ROOT.TGraph2D(hl.Project3D("yx"))
g2dvsm.SetName("g2dvsm")
g2dvsm.SetNpx(401)
g2dvsm.SetNpy(401)
limlistvsm = g2dvsm.GetContourList(1.0)
hl.GetZaxis().SetRange(0,-1)

tb = hwr.GetZaxis().FindBin(theta_gf)
hwr.GetZaxis().SetRange(tb,tb)
gwr = ROOT.TGraph2D(hwr.Project3D("yx"))
gwr.SetName("gwr")
gwr.SetNpx(401)
gwr.SetNpy(401)
if np.amax(gwr.GetZ())>0.5:
    wrlist = gwr.GetContourList(0.5)
hwr.GetZaxis().SetRange(0,-1)

can.Clear()
ROOT.gStyle.SetPalette(ROOT.kBird)
ROOT.gPad.SetLogz()

hwrl = gwr.GetHistogram()
hwrl.SetTitle("")
hwrl.SetMinimum(0.01)
hwrl.SetMaximum(5.0)
hwrl.GetZaxis().SetRangeUser(0.01,5.0)
hwrl.SetContour(5,np.array([0.01,0.1,0.5,1.0,2.0]))
hwrl.GetXaxis().SetTitle("M_{X} [GeV]")
hwrl.GetYaxis().SetTitle("g_{X} [1 TeV/M_{X}]")
hwrl.GetZaxis().SetTitle("#Gamma / #sigma_{mass}")
hwrl.GetZaxis().SetTitleOffset(0.75)
hwrl.GetXaxis().SetLabelSize(0.025)
hwrl.GetYaxis().SetLabelSize(0.0225)
hwrl.GetZaxis().SetLabelSize(0.02)
hwrl.Draw("colz,cjust")#,cjust")
if np.amax(gwr.GetZ())>0.5:
    gwrl = wrlist.At(0)
    gwrl.SetLineColor(1)
    gwrl.SetLineWidth(2)
    gwrl.Draw("L,same")
can.Update()
setpalette(hwrl)
can.Update()
ROOT.gPad.RedrawAxis()
ztitle = ROOT.TLatex(0.975,0.9,hwrl.GetZaxis().GetTitle());
ztitle.SetNDC()
ztitle.SetTextFont(42)
ztitle.SetTextSize(0.04)
ztitle.SetTextAlign(31)
ztitle.SetTextAngle(90)
ztitle.Draw()
modelt = ROOT.TPaveText(0.125,0.125,0.375,0.175,"blNDC")
ttext = modelt.AddText("%s (#theta_{23}=%.2f)"%(modelLeg,theta_gf))
ttext.SetTextFont(42)
ttext.SetTextSize(0.04)
modelt.SetFillColor(0)
modelt.SetBorderSize(0)
modelt.Draw()
drawLabels()
can.Update()
can.SaveAs("%s/width_resolution_ratio_%s.png"%(outdir,model))
can.SaveAs("%s/width_resolution_ratio_%s.pdf"%(outdir,model))

### Legend for 2D limits: theta_23 vs g_X
legxoffset = 0.0
legyoffset = 0.0
if model=="DYp3" or model=="B3mL2":
    legxoffset=-0.45
    legyoffset=0.475
leg = ROOT.TLegend(0.6+legxoffset,0.125+legyoffset,0.875+legxoffset,0.4+legyoffset)
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
#leg.SetHeader("#scale[1.25]{#splitline{%s (#theta_{23}=%.2f)}{95%% CL exclusion}}"%(modelLeg,theta_gf))
leg.SetHeader("#scale[1.25]{%s (#theta_{23}=%.2f)}, 95%% CL"%(modelLeg,theta_gf))

del haxis
minm = np.amin(masses)
maxm = np.amax(masses)
### For display purposes, set g_X minimum to 0.0325
minx=0.0325
if model=="B3mL2":
    minm=1000.0
haxis = ROOT.TH1D("haxis","",1,minm,maxm)
haxis.SetLineColor(1)
haxis.SetMinimum(minx)
haxis.SetMaximum(maxx)
haxis.GetYaxis().SetRangeUser(minx,maxx)
haxis.GetXaxis().SetTitle("M_{X} [GeV]")
haxis.GetYaxis().SetTitle("g_{X} [1 TeV/M_{X}]")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.0225)

### Get fit-allowed region
tx=np.array([minm,maxm])
grmin = ROOT.TGraph(2,tx,np.array([mingx,mingx]))
grmax = ROOT.TGraph(2,tx,np.array([maxgx,maxgx]))
grbest = ROOT.TGraph(2,tx,np.array([gzp_gf/3.0,gzp_gf/3.0]))
grband = ROOT.TGraph(2*2);
for i in range(2):
    grband.SetPoint(i,tx[i],maxgx)
    grband.SetPoint(2+i,tx[2-i-1],mingx)
grband.SetFillColorAlpha(ROOT.kBlue, 0.2)
grband.SetLineWidth(0)
grbest.SetLineColor(ROOT.kBlue)
grbest.SetLineStyle(4)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx()
ROOT.gPad.SetTicky()
haxis.Draw()
grband.Draw("F,same")
grbest.Draw("L,same")

for ln in range(len(exg2d95l)):
    for gn in range(len(exg2d95l[ln])):
        g = exg2d95l[ln].At(gn)
        #if ln==0:
        #    g.SetLineWidth(9902)
        #else:
        #    g.SetLineWidth(8802)
        g.SetLineWidth(2)
        g.SetLineColor(ROOT.kMagenta)
        g.SetFillColor(ROOT.kMagenta)
        g.SetFillStyle(3004)
        g.Draw("L,same")
        if ln==0 and gn==0:
            leg.AddEntry(g,"arXiv:2110.13518","L")

for gn in range(len(limlistvsm)):
    g = limlistvsm.At(gn)
    g.SetLineWidth(2)
    if which=="expected":
        g.SetLineColor(2)
        g.SetLineStyle(2)
        leg.AddEntry(g,"Median expected","L")
    for i in reversed(range(g.GetN())):
        if np.amax(gwr.GetZ())>0.5:
            if g.GetPointY(i)>gwrl.Eval(g.GetPointX(i)):
                g.RemovePoint(i)
            else:
                break
    g.Draw("L,same")

if np.amax(gwr.GetZ())>0.5:
    gwrl.SetLineColor(1)
    gwrl.SetLineStyle(3)
    gwrl.SetLineWidth(2)    
    ex = np.array(gwrl.GetX())
    ey = np.array(gwrl.GetY())
    gwrl.Draw("L,same")
    leg.AddEntry(gwrl, "#Gamma = 0.5 #sigma_{mass}","L")

leg.AddEntry(grband, "Allowed range (fit)", "F")
leg.AddEntry(grbest, "Best-fit value", "L")
leg.Draw("same")

drawLabels()

can.Update()
ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/limit_2d_gx_vs_mass_%s.png"%(outdir,model))
can.SaveAs("%s/limit_2d_gx_vs_mass_%s.pdf"%(outdir,model))

###

if useGenParamsVSMass:
    xscan=[gzp_gf/3.0]
    t23scan=[theta_gf/3.0]
else:
    exit()
hvsm = ROOT.TH1D()
gvsm = ROOT.TGraph()
for x in xscan:
    xb = hl.GetYaxis().FindBin(x)
    hl.GetYaxis().SetRange(xb,xb)
    for t23 in t23scan:
        tb = hl.GetZaxis().FindBin(t23)
        hl.GetZaxis().SetRange(tb,tb)
        hvsm = hl.Project3D("x")
        for mn,m in enumerate(masses):
            gvsm.SetPoint(mn,m,hvsm.GetBinContent(hvsm.GetXaxis().FindBin(m)))

        miny=+100.0
        maxy=-100.0
        yv  = gvsm.GetY()
        if np.amin(yv)<miny:
            miny = 0.5*np.amin(yv)
        if np.amin(yv)>maxy:
            maxy = 2.0*np.amax(yv)
        if maxy<10.0:
            maxy=10.0
        leg = ROOT.TLegend(0.15,0.65,0.35,0.85)
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
        #if drawObserved:
        #    leg.AddEntry(gobs,"Observed","L")
        if which=="expected":
            gvsm.SetLineColor(2)
            gvsm.SetLineStyle(2)
        leg.AddEntry(gvsm,"Median expected","L")

        del haxis
        haxis = ROOT.TH1D("haxis","",10,masses[0],masses[len(masses)-1])
        haxis.GetXaxis().SetTitle("Mass [GeV]")
        haxis.GetYaxis().SetTitle("95% CL upper limit on #sigma/#sigma_{theory}")
        haxis.GetXaxis().SetLabelSize(0.025)
        haxis.GetYaxis().SetLabelSize(0.025)
        haxis.SetMinimum(miny)
        haxis.SetMaximum(maxy)
        haxis.GetYaxis().SetRangeUser(miny,maxy)

        line = ROOT.TLine(masses[0],1.0,masses[len(masses)-1],1.0)
        line.SetLineColor(ROOT.kGray)
        line.SetLineStyle(2)

        ROOT.gStyle.SetOptStat(0)
        can.cd()
        can.Clear()
        ROOT.gPad.SetTickx(0)
        ROOT.gPad.SetTicky(1)
        ROOT.gPad.SetLogy()
        haxis.Draw()
        gvsm.Draw("L")
        #if drawObserved:
        #    gobs.Draw("L")
        line.Draw("same")
        leg.Draw("same")
        modeltext = ROOT.TLatex()
        modeltext.SetTextFont(42)
        modeltext.SetTextSize(0.04)
        modeltext.DrawLatexNDC(0.15,0.85,"%s (g_{X} [1 TeV/M_{X}]=%.2f, #theta_{23}=%.2f)"%(modelLeg,x,t23))

        drawLabels()
        
        ROOT.gPad.RedrawAxis()
        can.Update()
        can.SaveAs("%s/limit_1D_vsmass_%s.png"%(outdir,model))
        can.SaveAs("%s/limit_1D_vsmass_%s.pdf"%(outdir,model))
        ###
        hl.GetZaxis().SetRange(0,-1)
    hl.GetYaxis().SetRange(0,-1)

if not doAdditionalPlots:
    exit()

useSpline = True
minMforSpline = 200.0
maxMforSpline = 2000.0
ffit = ROOT.TFile.Open("utils/signalFitParameters_default.root")
sigmas = ffit.Get("splines").Clone()
sigmaf = ffit.Get("fsigma").Clone()
ffit.Close()

leg = ROOT.TLegend(0.15,0.55,0.45,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)

massesForWidth = [200,350,500,700,1000,1500,2000]
gsigma = ROOT.TGraph()
gsigma.SetLineColor(ROOT.kBlack)
gsigma.SetLineStyle(2)
gsigma.SetMarkerColor(ROOT.kBlack)
leg.AddEntry(gsigma,"#sigma_{mass} (average)","L")
gwidth = dict()
xbf = dict()
tbf = dict() 
xbf["Y3"]=0.14
tbf["Y3"]=-0.15
xbf["DY3"]=0.14
tbf["DY3"]=0.13
xbf["DYp3"]=0.08
tbf["DYp3"]=-0.18
xbf["B3mL2"]=0.05
tbf["B3mL2"]=0.10

for tmodel in models:
    gwidth[tmodel] = ROOT.TGraph()
    gwidth[tmodel].SetLineColor(colors[tmodel])
    gwidth[tmodel].SetMarkerColor(colors[tmodel])
    if tmodel=="Y3":
        modelLeg="#Gamma^{Y_{3}} (best-fit)"
    elif tmodel=="DY3":
        modelLeg="#Gamma^{DY_{3}} (best-fit)"
    elif tmodel=="DYp3":
        modelLeg="#Gamma^{DY'_{3}} (best-fit)"
    elif tmodel=="B3mL2":
        modelLeg="#Gamma^{B_{3}-L_{2}} (best-fit)"
    leg.AddEntry(gwidth[tmodel],modelLeg,"L")


for mn,m in enumerate(massesForWidth):
    for tmodel in models:
        width = calculate_width(m, xbf[tmodel], tbf[tmodel], get_model_name(tmodel), 'Zp', False)
        gwidth[tmodel].SetPoint(mn,m,width)
    sigma = 0.0
    if useSpline and m>=minMforSpline and m<=maxMforSpline:
        sigma = sigmas.Eval(m)
    else:
        sigma = sigmaf.Eval(m)
    gsigma.SetPoint(mn,m,sigma)

del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("Width [GeV]")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0.0)
haxis.SetMaximum(100.0)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(0)
haxis.Draw()

gsigma.Draw("C,same")
for tmodel in models:
    gwidth[tmodel].Draw("C,same")

leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/width_and_resolution_vsmass.png"%(outdir))
can.SaveAs("%s/width_and_resolution_vsmass.pdf"%(outdir))

### Cross sections

leg = ROOT.TLegend(0.55,0.55,0.85,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)

#massesForWidth = [200,250,300,350,400,500,600,700,850,1000,1250,1500,2000]
massesForWidth = [200,250,400,700,1000,1500,2000]
gxsecbb = dict()
gxsecsb = dict()
for tm in models:
    gxsecbb[tm] = ROOT.TGraph()
    gxsecbb[tm].SetLineColor(colors[tm])
    gxsecbb[tm].SetMarkerStyle(markers[tm])
    gxsecbb[tm].SetMarkerColor(colors[tm])
    gxsecsb[tm] = ROOT.TGraph()
    gxsecsb[tm].SetLineColor(colors[tm])
    gxsecsb[tm].SetMarkerStyle(markers[tm])
    gxsecsb[tm].SetMarkerColor(colors[tm])
    if tm=="Y3":
        modelLeg="Y_{3} (best-fit)"
    elif tm=="DY3":
        modelLeg="DY_{3} (best-fit)"
    elif tm=="DYp3":
        modelLeg="DY'_{3} (best-fit)"
    elif tm=="B3mL2":
        modelLeg="B_{3}-L_{2} (best-fit)"
    leg.AddEntry(gxsecbb[tm],modelLeg,"PL")

    for mn,m in enumerate(massesForWidth):
        txsbb = ROOT.TMath.Exp(xsbb[tm].Eval(m))
        txssb = ROOT.TMath.Exp(xssb[tm].Eval(m))
        gxsecbb[tm].SetPoint(mn,m,txsbb)
        gxsecsb[tm].SetPoint(mn,m,txssb)

del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#sigma_{bb} [fb]")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0.5e-2)
haxis.SetMaximum(1e3)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(1)
haxis.Draw()

for tm in models:
    gxsecbb[tm].Draw("CP,same")

leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/xsection_bb_vsmass.png"%(outdir))
can.SaveAs("%s/xsection_bb_vsmass.pdf"%(outdir))

del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#sigma_{sb} [fb]")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0.25e-4)
haxis.SetMaximum(2.5)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(1)
haxis.Draw()

for tm in models:
    gxsecsb[tm].Draw("CP,same")

leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/xsection_sb_vsmass.png"%(outdir))
can.SaveAs("%s/xsection_sb_vsmass.pdf"%(outdir))

### Acceptance x Efficiency

leg = ROOT.TLegend(0.15,0.55,0.35,0.85)
leg.SetLineColor(0)
leg.SetFillColor(0)

massesForWidth = [200,250,400,550,700,850,1000,1250,1500,2000]
#massesForWidth = [200,250,300,350,400,500,600,700,850,1000,1250,1500,2000]
for tm in models:
    if tm=="Y3":
        modelLeg="Y_{3}"
    elif tm=="DY3":
        modelLeg="DY_{3}"
    elif tm=="DYp3":
        modelLeg="DY'_{3}"
    elif tm=="B3mL2":
        modelLeg="B_{3}-L_{2}"
    leg.AddEntry(aebb_nb1_model[tm],modelLeg,"F")
leg.AddEntry(gaebb_nb1,"Average","PL")
for mn,m in enumerate(massesForWidth):
    taebb_nb1 = aebb_nb1.Eval(m)
    gaebb_nb1.SetPoint(mn,m,taebb_nb1)
    taesb_nb1 = aesb_nb1.Eval(m)
    gaesb_nb1.SetPoint(mn,m,taesb_nb1)
    taebb_nb2 = aebb_nb2.Eval(m)
    gaebb_nb2.SetPoint(mn,m,taebb_nb2)
    taesb_nb2 = aesb_nb2.Eval(m)
    gaesb_nb2.SetPoint(mn,m,taesb_nb2)

del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#Alpha #times #epsilon")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0)
haxis.SetMaximum(np.amax(np.array(gaebb_nb1.GetY()))*1.75)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(0)
haxis.Draw()
tgbb_nb1_model = dict()
tgsb_nb1_model = dict()
tgbb_nb2_model = dict()
tgsb_nb2_model = dict()
for tm in models:
    aebb_nb1_model[tm].Draw("3,same")
    tgbb_nb1_model[tm] = ROOT.TGraph(aebb_nb1_model[tm])
    tgbb_nb1_model[tm].Draw("L,same")
gaebb_nb1.Draw("L,P,same")
leg.SetHeader("Z'bb, N_{b}=1")
leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/acceff_bb_nb1_vsmass.png"%(outdir))
can.SaveAs("%s/acceff_bb_nb1_vsmass.pdf"%(outdir))

del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#Alpha #times #epsilon")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0)
haxis.SetMaximum(np.amax(np.array(gaebb_nb2.GetY()))*1.75)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(0)
haxis.Draw()

for tm in models:
    aebb_nb2_model[tm].Draw("3,same")
    tgbb_nb2_model[tm] = ROOT.TGraph(aebb_nb2_model[tm])
    tgbb_nb2_model[tm].Draw("L,same")
gaebb_nb2.Draw("L,P,same")
leg.SetHeader("Z'bb, N_{b}#geq2")
leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/acceff_bb_nb2p_vsmass.png"%(outdir))
can.SaveAs("%s/acceff_bb_nb2p_vsmass.pdf"%(outdir))


del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#Alpha #times #epsilon")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0)
haxis.SetMaximum(np.amax(np.array(gaesb_nb1.GetY()))*1.75)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(0)
haxis.Draw()

for tm in models:
    aesb_nb1_model[tm].Draw("3,same")
    tgsb_nb1_model[tm] = ROOT.TGraph(aesb_nb1_model[tm])
    tgsb_nb1_model[tm].Draw("L,same")
gaesb_nb1.Draw("L,P,same")
leg.SetHeader("Z'sb, N_{b}=1")
leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/acceff_sb_nb1_vsmass.png"%(outdir))
can.SaveAs("%s/acceff_sb_nb1_vsmass.pdf"%(outdir))

del haxis
haxis = ROOT.TH1D("haxis","",10,massesForWidth[0],massesForWidth[len(massesForWidth)-1])
haxis.GetXaxis().SetTitle("Mass [GeV]")
haxis.GetYaxis().SetTitle("#Alpha #times #epsilon")
haxis.GetXaxis().SetLabelSize(0.025)
haxis.GetYaxis().SetLabelSize(0.025)
haxis.SetMinimum(0)
haxis.SetMaximum(np.amax(np.array(gaesb_nb2.GetY()))*1.75)

ROOT.gStyle.SetOptStat(0)
can.cd()
can.Clear()
ROOT.gPad.SetTickx(0)
ROOT.gPad.SetTicky(1)
ROOT.gPad.SetLogy(0)
haxis.Draw()

for tm in models:
    aesb_nb2_model[tm].Draw("3,same")
    tgsb_nb2_model[tm] = ROOT.TGraph(aesb_nb2_model[tm])
    tgsb_nb2_model[tm].Draw("L,same")
gaesb_nb2.Draw("L,P,same")
leg.SetHeader("Z'sb, N_{b}#geq2")
leg.Draw("same")

drawLabels("all",-1.0,False)

ROOT.gPad.RedrawAxis()
can.Update()
can.SaveAs("%s/acceff_sb_nb2p_vsmass.png"%(outdir))
can.SaveAs("%s/acceff_sb_nb2p_vsmass.pdf"%(outdir))

