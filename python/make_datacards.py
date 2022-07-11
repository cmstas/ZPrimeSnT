import os,sys
import ROOT
from datetime import date

user = os.environ.get("USER")
today= date.today().strftime("%b-%d-%Y")

wsname = "wfit"
inDir  = "./cpp/fitResults"
outDir = "/home/users/"+user+"/Zprime/ZPrimeSnT/datacards_"+today
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
#dNames.append("d_mllinclusive_nBTag1p_BB")
#dNames.append("d_mllinclusive_nBTag1_BB")
#dNames.append("d_mllinclusive_nBTag2p_BB")
#dNames.append("d_mllinclusive_nBTag1p_BE")
#dNames.append("d_mllinclusive_nBTag1_BE")
#dNames.append("d_mllinclusive_nBTag2p_BE")
#dNames.append("d_mllinclusive_nBTag1p_EE")
#dNames.append("d_mllinclusive_nBTag1_EE")
#dNames.append("d_mllinclusive_nBTag2p_EE")

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
                # Open input file with workspace
                f = ROOT.TFile(finame)
                # Retrieve workspace from file
                w = f.Get(wsname)
                # Retrieve signal normalization
                nSig = w.var("sigNormalization_%s_%s_M%s_%s"%(d,s,m,y)).getValV()
                # Retrieve signal mean
                mean = w.var("mean_%s_%s_M%s_%s"%(d,s,m,y)).getValV()
                # Retrieve signal std. deviation
                sigma = w.var("sigma_%s_%s_M%s_%s"%(d,s,m,y)).getValV()
                # Retrieve MC stat. uncertainty from RooDataSet
                mcstatunc = 1.0/ROOT.TMath.Sqrt(w.data("%s_%s_M%s_%s"%(d,s,m,y)).numEntries())
                # Close input file with workspace
                f.Close()

                card = open("%s/card_%s_%s_M%s_%s.txt"%(outDir,d,s,m,y),"w")
                card.write("imax *\n")
                card.write("jmax *\n")
                card.write("kmax *\n")
                card.write("------------\n")
                card.write("shapes data_obs * %s %s:%s_%s_%s\n"%(finame,wsname,d,ext,y))
                card.write("shapes signal * %s %s:signal_%s_%s_M%s_%s\n"%(finame,wsname,d,s,m,y))
                card.write("shapes background * %s %s:roomultipdf_%s_%s_%s\n"%(finame,wsname,d,ext,y))
                card.write("------------\n")  
                card.write("bin %s\n"%(d))
                card.write("observation -1\n")
                card.write("------------\n")  
                card.write("bin %s %s\n"%(d,d))
                card.write("process signal background\n")
                card.write("process 0 1\n")
                # Freely floating background normalization
                card.write("rate %f 1\n"%(nSig))
                card.write("------------\n")  
                # Systematics
                card.write("lumi lnN 1.016 -\n") #2.5% uncertainty on signal (fully correlated)
                card.write("sig_normsyst lnN 1.05 -\n") #10% example systematic uncertainty on signal (fully correlated)
                card.write("sig_mcstat lnN %f -\n"%(1.0+mcstatunc)) #MC stat. uncertainty
                card.write("\n")
                card.write("pdf_index_%s_%s_%s discrete\n"%(d,ext,y))
                card.close()
