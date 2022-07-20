import os,sys
import ROOT
from datetime import date

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

wsname = "wfit"
inDir  = "./cpp/fitResults"
outDir = "./datacards_"+today
if not os.path.exists(outDir):
    os.makedirs(outDir)

useData = False;
ext = "data"
if not useData:
    ext = "BGMC"

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

sigMasses = []
sigMasses.append("200")
sigMasses.append("400")
sigMasses.append("700")
sigMasses.append("1000")
sigMasses.append("1500")
sigMasses.append("2000")

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
                # Open input file with workspace
                f = ROOT.TFile(finame)
                # Retrieve workspace from file
                w = f.Get(wsname)
                # Retrieve signal normalization
                nSig = w.var("signalNorm").getValV()
                # Retrieve signal mean
                mean = w.var("mean").getValV()
                # Retrieve signal std. deviation
                sigma = w.var("sigma").getValV()
                # Retrieve MC stat. uncertainty from RooDataSet
                mcstatunc = 1.0/ROOT.TMath.Sqrt(w.data("signalRooDataSet").numEntries())
                # Close input file with workspace
                f.Close()

                # Define systematics that are independent of signal mass
                btagsyst = 0.01
                if binidx>=2:
                    btagsyst = 0.05

                muonsfsyst = 0.025
                muonselsyst = 0.05

                # Derive mass-dependent systematic uncertainties
                minm = 200.0
                maxm = 2000.0
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

                card = open("%s/card_ch%d_%s_M%s_%s.txt"%(outDir,binidx,s,m,y),"w")
                card.write("imax *\n")
                card.write("jmax *\n")
                card.write("kmax *\n")
                card.write("------------\n")
                card.write("shapes data_obs * %s %s:data_obs\n"%(finame,wsname))
                card.write("shapes signal * %s %s:signal\n"%(finame,wsname))
                card.write("shapes background * %s %s:roomultipdf_%d\n"%(finame,wsname,binidx))
                card.write("------------\n")  
                # Observation (taken directly from RooDataSet data_obs)
                card.write("bin ch%d\n"%(binidx))
                card.write("observation -1\n")
                card.write("------------\n")  
                # Rates (background is left freely floating)
                card.write("bin ch%d ch%d\n"%(binidx,binidx))
                card.write("process signal background\n")
                card.write("process 0 1\n")
                card.write("rate %.3f 1\n"%(nSig))
                card.write("------------\n")  
                # Systematics
                card.write("lumi lnN 1.016 -\n") # Integrated luminosity uncertainty on signal (fully correlated)
                card.write("sig_triggersf lnN %.3f -\n"%(1.0+triggersyst)) # Systematic uncertainty on signal from trigger (fully correlated)
                card.write("sig_muonsf lnN %.3f -\n"%(1.0+muonsfsyst)) # Systematic uncertainty on signal from muon RECO, ID, isolation (fully correlated)
                card.write("sig_muonsel lnN %.3f -\n"%(1.0+muonselsyst)) # Systematic uncertainty on signal from muon additional selection (fully correlated)
                card.write("sig_btagsf lnN %.3f -\n"%(1.0+btagsyst)) # Systematic uncertainty on signal from b-tagging (fully correlated)
                card.write("sig_jec_ch%d lnN %.3f -\n"%(binidx,1.0+jecsyst)) # Systematic uncertainty on signal from JES (uncorrelated)
                card.write("sig_mcstat_ch%d lnN %.3f -\n"%(binidx,1.0+mcstatunc)) # MC stat. uncertainty (uncorrelated)
                card.write("mean param %.3f %.3f\n"%(mean,sigma)) # Shape systematic on dimuon mass mean value
                card.write("pdf_index_%d discrete\n"%(binidx)) # For discrete profiling
                card.close()
                
                # text2workspace for individual cards:
                os.system("text2workspace.py %s/card_ch%d_%s_M%s_%s.txt -m %s"%(outDir,binidx,s,m,y,m))

            # Combine cards:
            if len(dNames)>1:
                os.system("combineCards.py %s/card_ch1_%s_M%s_%s.txt %s/card_ch2_%s_M%s_%s.txt > %s/card_combined_%s_M%s_%s.txt"%(outDir,s,m,y,outDir,s,m,y,outDir,s,m,y))
                os.system("text2workspace.py %s/card_combined_%s_M%s_%s.txt -m %s"%(outDir,s,m,y,m))
