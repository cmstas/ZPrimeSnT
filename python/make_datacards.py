import os,sys
import ROOT
from datetime import date

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

wsname = "wfit"
thisDir = os.environ.get("PWD")
inDir  = "%s/cpp/fitResults/"%thisDir

fnfitParamsForShapeUnc = "%s/utils/signalFitParameters_muonResolutionUnc.root"%thisDir
ffitParamsForShapeUnc = ROOT.TFile.Open(fnfitParamsForShapeUnc,"READ")
minMforSpline =  200.0
maxMforSpline = 2000.0

useCategorizedSignal = False
useCategorizedBackground = True

useData = False;
ext = "data"
if not useData:
    ext = "BGMC"

doCounting = False
useOnlyExponential = False
useOnlyPowerLaw = False
useOnlyBernstein = False
fullMeanFloat = False
meanFloat = False
doMuonResolution = True
noModel = False
dirExt = ""
if len(sys.argv)>1:
    if sys.argv[1]=="expo":
        useOnlyExponential = True
        dirExt = "_expoOnly"
    elif sys.argv[1]=="plaw":
        useOnlyPowerLaw = True
        dirExt = "_plawOnly"
    elif sys.argv[1]=="bern":
        useOnlyBernstein = True
        dirExt = "_bernOnly"
    elif sys.argv[1]=="count":
        doCounting = True
        dirExt = "_count"
    elif sys.argv[1]=="fullmeanfloat":
        fullMeanFloat = True
        dirExt = "_fullMeanFloat"
    elif sys.argv[1]=="meanfloat":
        meanFloat = True
        dirExt = "_meanFloat"
    elif sys.argv[1]=="nomodel":
        noModel=True
        dirExt = "_nomodel"
    if len(sys.argv)>2 and sys.argv[2]=="nomodel":
        noModel=True
        dirExt = dirExt+"_nomodel"

outDir = ("%s/datacards_all%s_"%(thisDir,dirExt))+today
if not os.path.exists(outDir):
    os.makedirs(outDir)

useSinglePDF = False
if useOnlyExponential or useOnlyPowerLaw or useOnlyBernstein:
    useSinglePDF = True

dNames = []
dNames.append("d_mllinclusive_nBTag1p_MuDetAll")
dNames.append("d_mllinclusive_nBTag1_MuDetAll")
dNames.append("d_mllinclusive_nBTag2p_MuDetAll")
###dNames.append("d_mllinclusive_nBTag1p_BB")
###dNames.append("d_mllinclusive_nBTag1_BB")
###dNames.append("d_mllinclusive_nBTag2p_BB")
###dNames.append("d_mllinclusive_nBTag1p_BE")
###dNames.append("d_mllinclusive_nBTag1_BE")
###dNames.append("d_mllinclusive_nBTag2p_BE")
###dNames.append("d_mllinclusive_nBTag1p_EE")
###dNames.append("d_mllinclusive_nBTag1_EE")
###dNames.append("d_mllinclusive_nBTag2p_EE")

years = []
#years.append("2018")
#years.append("2017")
#years.append("2016APV")
#years.append("2016nonAPV")
###
years.append("allyears")

# Signals
sigModels = []
sigModels.append("Y3")
#sigModels.append("DY3")
#sigModels.append("DYp3")
#sigModels.append("B3mL2")

if noModel:
    sigModels = ["Y3"]

sigMasses = []
sigMasses.append("250")
sigMasses.append("400")
sigMasses.append("550")
sigMasses.append("700")
sigMasses.append("850")
sigMasses.append("1000")
sigMasses.append("1250")
sigMasses.append("1500")
sigMasses.append("2000")

f2l = [0.0]
nSigTot = 1.0
if noModel:
    f2l = [0.0, 0.1, 0.25, 0.5, 0.75, 0.9, 1.0]

mean = 0.0
sigma = 0.0
for y in years:
    for s in sigModels:
        for m in sigMasses:
            for d in dNames:
                finame = "%s/%s_%s_M%s_%s_workspace.root"%(inDir,d,s,m,y)
                binidx=-1
                if "nBTag1p" in finame:
                    binidx=0
                elif "nBTag1" in finame:
                    binidx=1
                elif "nBTag2p" in finame:
                    binidx=2
                catExtS = ""
                catExtB = ""
                if useCategorizedSignal:
                    catExtS = "_ch%d"%binidx
                if useCategorizedBackground:
                    catExtB = "_ch%d"%binidx
                # Open input file with workspace
                f = ROOT.TFile(finame)
                # Retrieve workspace from file
                w = f.Get(wsname)
                # Retrieve signal normalization
                nSig = w.var("signalNorm%s"%catExtS).getValV()
                # Retrieve signal mean and std. deviation
                if binidx==0 or useCategorizedSignal:
                    mean = w.var("mean%s"%catExtS).getValV()
                    sigma = w.var("sigma%s"%catExtS).getValV()
                # Retrieve MC stat. uncertainty from RooDataSet
                mcstatunc = 1.0/ROOT.TMath.Sqrt(w.var("signalRawNorm%s"%catExtS).getValV())
                # Retrive BG normalization:
                nBG = w.data("data_obs%s"%catExtB).sumEntries()
                # Close input file with workspace
                f.Close()
                if not doCounting:
                    os.system("cp %s %s/"%(finame,outDir))
                    finame = "%s_%s_M%s_%s_workspace.root"%(d,s,m,y)

                # Define systematics that are independent of signal mass
                btagsyst = 0.01
                if binidx>=2:
                    btagsyst = 0.05

                muonselsyst = 0.05

                # Derive mass-dependent systematic uncertainties
                minm = 200.0
                maxm = 2000.0
                #
                minsyst = 0.015
                maxsyst = 0.03
                muonsfsyst = max(0.0,(maxsyst-minsyst)/(maxm-minm)*float(m) + minsyst - minm/(maxm-minm)*(maxsyst-minsyst))
                #
                minsyst = 0.01
                maxsyst = 0.05
                triggersyst = max(0.0,(maxsyst-minsyst)/(maxm-minm)*float(m) + minsyst - minm/(maxm-minm)*(maxsyst-minsyst))
                #
                if binidx<2:
                    minsyst = 0.015
                    maxsyst = 0.01
                else:
                    minsyst = 0.05
                    maxsyst = 0.02
                jecsyst = max(0.0,(maxsyst-minsyst)/(maxm-minm)*float(m) + minsyst - minm/(maxm-minm)*(maxsyst-minsyst))

                # Shape systematic on signal mean, linearly increasing with mass
                minsyst = 0.000
                maxsyst = 0.002
                meanvar = max(0.0,(maxsyst-minsyst)/(maxm-minm)*float(m) + minsyst - minm/(maxm-minm)*(maxsyst-minsyst))*float(m)

                sigmavar = 0.0
                if float(m) > minMforSpline-0.001 and float(m) < maxMforSpline+0.001:
                    fsigmavar = ffitParamsForShapeUnc.Get("splines")
                    sigmavar = abs(fsigmavar.Eval(float(m))-sigma)
                else:
                    fsigmavar =ffitParamsForShapeUnc.Get("fsigma")
                    sigmavar = abs(fsigmavar.Eval(float(m))-sigma)

                for f in f2l:
                    cname = ""
                    if noModel:
                        nSig = nSigTot
                        if binidx == 1:
                            nSig = nSigTot*(1-f)
                        elif binidx == 2:
                            nSig = nSigTot*f
                        if binidx > 0:
                            cname = "_f2b%d"%(f*100)

                    card = open("%s/card%s_ch%d_%s_M%s_%s.txt"%(outDir,cname,binidx,s,m,y),"w")
                    card.write("imax *\n")
                    card.write("jmax *\n")
                    card.write("kmax *\n")
                    card.write("------------\n")
                    if doCounting:
                        card.write("shapes * * FAKE\n")
                    else:
                        card.write("shapes data_obs * %s %s:data_obs%s\n"%(finame,wsname,catExtB))
                        card.write("shapes signal * %s %s:signal%s\n"%(finame,wsname,catExtS))
                        if not useSinglePDF:
                            card.write("shapes background * %s %s:roomultipdf%s\n"%(finame,wsname,catExtB))
                        elif useOnlyExponential:
                            card.write("shapes background * %s %s:background_exponential%s\n"%(finame,wsname,catExtB))
                        elif useOnlyPowerLaw:
                            card.write("shapes background * %s %s:background_powerlaw%s\n"%(finame,wsname,catExtB))
                        elif useOnlyBernstein:
                            card.write("shapes background * %s %s:background_bernstein%s\n"%(finame,wsname,catExtB))
                    card.write("------------\n")
                    # Observation (taken directly from RooDataSet data_obs)
                    card.write("bin ch%d\n"%(binidx))
                    if doCounting:
                        card.write("observation %.3f\n"%nBG)
                    else:
                        card.write("observation -1\n")
                    card.write("------------\n")  
                    # Rates (background is left freely floating)
                    card.write("bin ch%d ch%d\n"%(binidx,binidx))
                    card.write("process signal background\n")
                    card.write("process 0 1\n")
                    if doCounting:
                        card.write("rate %.3f %.3f\n"%(nSig,nBG))
                    else:
                        card.write("rate %.3f 1\n"%(nSig))
                    card.write("------------\n")  
                    # Systematics
                    card.write("lumi lnN 1.016 -\n") # Integrated luminosity uncertainty on signal (fully correlated)
                    card.write("sig_triggersf lnN %.3f -\n"%(1.0+triggersyst)) # Systematic uncertainty on signal from trigger (fully correlated)
                    card.write("sig_muonsf lnN %.3f -\n"%(1.0+muonsfsyst)) # Systematic uncertainty on signal from muon RECO, ID, isolation (fully correlated)
                    card.write("sig_muonsel lnN %.3f -\n"%(1.0+muonselsyst)) # Systematic uncertainty on signal from muon additional selection (fully correlated)
                    card.write("sig_btagsf lnN %.3f -\n"%(1.0+btagsyst)) # Systematic uncertainty on signal from b-tagging (fully correlated)
                    card.write("sig_jec_ch%d lnN %.3f -\n"%(binidx,1.0+jecsyst)) # Systematic uncertainty on signal from JES (uncorrelated)
                    if not noModel:
                        card.write("sig_mcstat_ch%d lnN %.3f -\n"%(binidx,1.0+mcstatunc)) # MC stat. uncertainty (uncorrelated)
                    if meanFloat:
                        card.write("mean param %.3f -%.3f/+%.3f\n"%(mean,0.5*sigma,0.5*sigma)) # Shape systematic on dimuon mass mean value
                    elif fullMeanFloat:
                        card.write("mean param %.3f %.3f\n"%(mean,sigma)) # Shape systematic on dimuon mass mean value
                    elif meanvar/float(m)>0.001:
                        card.write("mean param %.3f %.3f\n"%(mean,meanvar))
                    if doMuonResolution:
                        card.write("sigma param %.3f %.3f\n"%(sigma,sigmavar))                        
                    if doCounting:
                        card.write("bg_norm_ch%d gmN %d - 1.0\n"%(binidx,int(nBG)))
                    else:
                        if not useSinglePDF:
                            card.write("pdf_index_ch%d discrete\n"%(binidx)) # For discrete profiling
                    card.close()
                
                    # text2workspace for individual cards:
                    os.chdir(outDir)
                    os.system("text2workspace.py card%s_ch%d_%s_M%s_%s.txt -m %s"%(cname,binidx,s,m,y,m))
                    os.chdir(thisDir)

            # Combine cards:
            if len(dNames)>1:
                os.chdir(outDir)
                for f in f2l:
                    cname = ""
                    if noModel and binidx > 0:
                        cname = "_f2b%d"%(f*100)
                    os.system("combineCards.py -S card%s_ch1_%s_M%s_%s.txt card%s_ch2_%s_M%s_%s.txt > card%s_combined_%s_M%s_%s.txt"%(cname,s,m,y,cname,s,m,y,cname,s,m,y))
                    os.system("text2workspace.py card%s_combined_%s_M%s_%s.txt -m %s"%(cname,s,m,y,m))
                os.chdir(thisDir)

