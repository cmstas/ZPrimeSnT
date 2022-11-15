import os,sys
import ROOT
import numpy as np
sys.path.append('python')
from compute_width import calculate_Zpmumu_weight
from compute_width import calculate_width
from compute_width import get_model_name

luminosity = 137.61
useFixedMassGrid = False

model=sys.argv[1]
lfile=sys.argv[2]+"/limits_2D_nomodel.root"
which=sys.argv[3]
lname="%s2d"%which

outdir=sys.argv[2]

fl = ROOT.TFile.Open(lfile)
gl = ROOT.TGraph2D(fl.Get(lname)).Clone()
gl.SetDirectory(ROOT.gROOT)
fl.Close()

fxs = ROOT.TFile.Open("data/xsec_interpolation_ZPrimeToMuMuSB_bestfit_13TeV_Allanach.root")
xsbb = fxs.Get("spline_%s_xsec_bb"%model).Clone()
xssb = fxs.Get("spline_%s_xsec_sb"%model).Clone() 
fxs.Close()

fae = ROOT.TFile.Open("data/acceff_interpolation_Run2.root")
aebb_nb1 = fae.Get("spline_avg_acceff_bb_Nb_eq_1_Run2").Clone()
aebb_nb2 = fae.Get("spline_avg_acceff_bb_Nb_geq_2_Run2").Clone()
aesb_nb1 = fae.Get("spline_avg_acceff_sb_Nb_eq_1_Run2").Clone()
aesb_nb2 = fae.Get("spline_avg_acceff_sb_Nb_geq_2_Run2").Clone()
fae.Close()

useSpline = True
minMforSpline = 200.0
maxMforSpline = 2000.0
ffit = ROOT.TFile.Open("utils/signalFitParameters_default.root")
sigmas = ffit.Get("splines").Clone()
sigmaf = ffit.Get("fsigma").Clone()
ffit.Close()

masses = [250,400,550,700,850,1000,1250,1500,2000]
mF = masses[0]
mL = masses[len(masses)-1]
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

nbm = int((mL-mF)/5.0)
bwm = (mL-mF)/nbm
bwx = (maxx-minx)/nbx
bwt = (maxt-mint)/nbt
h3d = ROOT.TH3D("limit3d_%s_%s"%(which,model),"",nbm+1,mF-0.5*bwm,mL+0.5*bwm,nbx+1,minx-0.5*bwx,maxx+0.5*bwx,nbt+1,mint-0.5*bwt,maxt+0.5*bwt)
h3d.GetXaxis().SetTitle("M_{X} [GeV]")
h3d.GetYaxis().SetTitle("g_{X} [1 TeV/M_{X}]")
h3d.GetZaxis().SetTitle("#theta_{23}")
h3d_w = ROOT.TH3D("width_resolution_ratio_3d_%s"%(model),"",nbm+1,mF-0.5*bwm,mL+0.5*bwm,nbx+1,minx-0.5*bwx,maxx+0.5*bwx,nbt+1,mint-0.5*bwt,maxt+0.5*bwt)
h3d_w.GetXaxis().SetTitle("M_{X} [GeV]")
h3d_w.GetYaxis().SetTitle("g_{X} [1 TeV/M_{X}]")
h3d_w.GetZaxis().SetTitle("#theta_{23}")

#for mass in masses:
for mb in range(nbm+1):
    mass = h3d.GetXaxis().GetBinCenter(mb+1)
    for x in xscan:
        for t23 in t23scan:
            width = calculate_width(mass, x, t23, get_model_name(model), 'Zp', False)
            sigma = 0.0
            if useSpline and mass>=minMforSpline and mass<=maxMforSpline:
                sigma = sigmas.Eval(mass)
            else:
                sigma = sigmaf.Eval(mass)
            h3d_w.Fill(mass,x,t23, width/sigma)
            if width > 0.5*sigma:
                continue
            bsW = calculate_Zpmumu_weight(mass, mass, x, t23, get_model_name(model), 8,  True)
            bbW = calculate_Zpmumu_weight(mass, mass, x, t23, get_model_name(model), 10, True)
            N1bb = (ROOT.TMath.Exp(xsbb.Eval(mass)))*(aebb_nb1.Eval(mass))*luminosity
            N1sb = (ROOT.TMath.Exp(xssb.Eval(mass)))*(aesb_nb1.Eval(mass))*luminosity
            N2bb = (ROOT.TMath.Exp(xsbb.Eval(mass)))*(aebb_nb2.Eval(mass))*luminosity
            N2sb = (ROOT.TMath.Exp(xssb.Eval(mass)))*(aesb_nb2.Eval(mass))*luminosity
            N1ss = 0.0 # ss contribution is negligible -> set to 0
            N2ss = 0.0 # ss contribution is negligible -> set to 0
            N1 = bbW*N1bb + bsW*N1sb + N1ss
            N2 = bbW*N2bb + bsW*N2sb + N2ss
            N  = N1+N2
            f2 = N2/N
            Nl = gl.Interpolate(mass,f2)
            mu = Nl/N
            h3d.Fill(mass,x,t23, mu)

fout = ROOT.TFile("%s/limits_3D_%s_%s.root"%(outdir,which,model), "RECREATE")
fout.cd()
h3d.Write()
h3d_w.Write()
fout.Close()
