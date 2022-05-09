import os,sys
import numpy as np
import ROOT

if len(sys.argv)<=1:
    print "Please, specify year: 2018, 2017, 2016APV, 2016nonAPV"
    exit()

year = sys.argv[1]
if year!="2018" and year!="2017" and year!="2016APV" and year!="2016nonAPV":
    print "Please, specify year: 2018, 2017, 2016APV, 2016nonAPV"
    exit()

fout = ROOT.TFile("data/muon_highpt_recosf_"+year+".root", "RECREATE")
fout.cd()

etabins = [0.0, 1.6, 2.4]
etabinsstr = ["0.0", "1.6", "2.4"]
netabins = len(etabins)-1
pbins = [50.0, 100.0, 150.0, 200.0, 300.0, 400.0, 600.0, 1500.0, 3500.0]
pbinsstr = ["50.0", "100.0", "150.0", "200.0", "300.0", "400.0", "600.0", "1500.0", "3500.0"]
npbins = len(pbins)-1
etabins_array = np.array(etabins, "d")
pbins_array = np.array(pbins, "d")
hHighPtMuonRecoSF = ROOT.TH2F("hHighPtMuonRecoSF","", netabins, etabins_array, npbins, pbins_array)

sfhpdict = dict()
sfunchpdict = dict()
for ne in range(0, len(etabins)):
    sfhpdict[str(etabins[ne])] = dict()
    sfunchpdict[str(etabins[ne])] = dict()
    for np in range(0, len(pbins)):
        sfhpdict[str(etabins[ne])][str(pbins[np])] = 0.0
        sfunchpdict[str(etabins[ne])][str(pbins[np])] = 0.0

# https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonUL2018#RECO_efficiency_AN1
if year=="2018":  
    sfhpdict["0.0"]["50.0"] = 0.9943
    sfunchpdict["0.0"]["50.0"] = 0.0007
    sfhpdict["0.0"]["100.0"] = 0.9948
    sfunchpdict["0.0"]["100.0"] = 0.0007
    sfhpdict["0.0"]["150.0"] = 0.9950
    sfunchpdict["0.0"]["150.0"] = 0.0009
    sfhpdict["0.0"]["200.0"] = 0.994
    sfunchpdict["0.0"]["200.0"] = 0.001
    sfhpdict["0.0"]["300.0"] = 0.9914
    sfunchpdict["0.0"]["300.0"] = 0.0009
    sfhpdict["0.0"]["400.0"] = 0.993
    sfunchpdict["0.0"]["400.0"] = 0.002
    sfhpdict["0.0"]["600.0"] = 0.991
    sfunchpdict["0.0"]["600.0"] = 0.004
    sfhpdict["0.0"]["1500.0"] = 1.0
    sfunchpdict["0.0"]["1500.0"] = 0.1
    #
    sfhpdict["1.6"]["100.0"] = 0.993
    sfunchpdict["1.6"]["100.0"] = 0.001
    sfhpdict["1.6"]["150.0"] = 0.990
    sfunchpdict["1.6"]["150.0"] = 0.001
    sfhpdict["1.6"]["200.0"] = 0.988
    sfunchpdict["1.6"]["200.0"] = 0.001
    sfhpdict["1.6"]["300.0"] = 0.981
    sfunchpdict["1.6"]["300.0"] = 0.002
    sfhpdict["1.6"]["400.0"] = 0.983
    sfunchpdict["1.6"]["400.0"] = 0.003
    sfhpdict["1.6"]["600.0"] = 0.978
    sfunchpdict["1.6"]["600.0"] = 0.006
    sfhpdict["1.6"]["1500.0"] = 0.98
    sfunchpdict["1.6"]["1500.0"] = 0.03

# https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonUL2017#RECO_efficiency_AN1
elif year=="2017":  
    sfhpdict["0.0"]["50.0"] = 0.9938
    sfunchpdict["0.0"]["50.0"] = 0.0006
    sfhpdict["0.0"]["100.0"] = 0.9950
    sfunchpdict["0.0"]["100.0"] = 0.0007
    sfhpdict["0.0"]["150.0"] = 0.996
    sfunchpdict["0.0"]["150.0"] = 0.001
    sfhpdict["0.0"]["200.0"] = 0.996
    sfunchpdict["0.0"]["200.0"] = 0.001
    sfhpdict["0.0"]["300.0"] = 0.994
    sfunchpdict["0.0"]["300.0"] = 0.001
    sfhpdict["0.0"]["400.0"] = 1.003
    sfunchpdict["0.0"]["400.0"] = 0.006
    sfhpdict["0.0"]["600.0"] = 0.987
    sfunchpdict["0.0"]["600.0"] = 0.003
    sfhpdict["0.0"]["1500.0"] = 0.9
    sfunchpdict["0.0"]["1500.0"] = 0.1
    #
    sfhpdict["1.6"]["100.0"] = 0.993
    sfunchpdict["1.6"]["100.0"] = 0.001
    sfhpdict["1.6"]["150.0"] = 0.989
    sfunchpdict["1.6"]["150.0"] = 0.001
    sfhpdict["1.6"]["200.0"] = 0.986
    sfunchpdict["1.6"]["200.0"] = 0.001
    sfhpdict["1.6"]["300.0"] = 0.989
    sfunchpdict["1.6"]["300.0"] = 0.002
    sfhpdict["1.6"]["400.0"] = 0.983
    sfunchpdict["1.6"]["400.0"] = 0.003
    sfhpdict["1.6"]["600.0"] = 0.986
    sfunchpdict["1.6"]["600.0"] = 0.006
    sfhpdict["1.6"]["1500.0"] = 1.01
    sfunchpdict["1.6"]["1500.0"] = 0.01

# https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonUL2016#RECO_efficiency_AN1
elif "2016" in year:  
    sfhpdict["0.0"]["50.0"] = 0.9914
    sfunchpdict["0.0"]["50.0"] = 0.0008
    sfhpdict["0.0"]["100.0"] = 0.9936
    sfunchpdict["0.0"]["100.0"] = 0.0009
    sfhpdict["0.0"]["150.0"] = 0.993
    sfunchpdict["0.0"]["150.0"] = 0.001
    sfhpdict["0.0"]["200.0"] = 0.993
    sfunchpdict["0.0"]["200.0"] = 0.002
    sfhpdict["0.0"]["300.0"] = 0.990
    sfunchpdict["0.0"]["300.0"] = 0.004
    sfhpdict["0.0"]["400.0"] = 0.990
    sfunchpdict["0.0"]["400.0"] = 0.003
    sfhpdict["0.0"]["600.0"] = 0.989
    sfunchpdict["0.0"]["600.0"] = 0.004
    sfhpdict["0.0"]["1500.0"] = 0.8
    sfunchpdict["0.0"]["1500.0"] = 0.3
    #
    sfhpdict["1.6"]["100.0"] = 0.993
    sfunchpdict["1.6"]["100.0"] = 0.001
    sfhpdict["1.6"]["150.0"] = 0.991
    sfunchpdict["1.6"]["150.0"] = 0.001
    sfhpdict["1.6"]["200.0"] = 0.985
    sfunchpdict["1.6"]["200.0"] = 0.001
    sfhpdict["1.6"]["300.0"] = 0.981
    sfunchpdict["1.6"]["300.0"] = 0.002
    sfhpdict["1.6"]["400.0"] = 0.979
    sfunchpdict["1.6"]["400.0"] = 0.004
    sfhpdict["1.6"]["600.0"] = 0.978
    sfunchpdict["1.6"]["600.0"] = 0.005
    sfhpdict["1.6"]["1500.0"] = 0.9
    sfunchpdict["1.6"]["1500.0"] = 0.2

for be in range(1,hHighPtMuonRecoSF.GetNbinsX()+1):
    for bp in range(1,hHighPtMuonRecoSF.GetNbinsY()+1):
        hHighPtMuonRecoSF.SetBinContent(be, bp, sfhpdict[etabinsstr[be-1]][pbinsstr[bp-1]])
        hHighPtMuonRecoSF.SetBinError(be, bp, sfunchpdict[etabinsstr[be-1]][pbinsstr[bp-1]])

fout.Write()
fout.Close()
