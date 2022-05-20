### python3

import os,sys
import ROOT

sigmavl = []
sigmael = []

fin = ROOT.TFile("./cpp/fitResults/d_mllinclusive_nBTag1p_MuDetAll_Y3_M200_2018_fitResult_dcbvoigt.root")
tfr = fin.Get("fitResult")

ts = tfr.floatParsFinal().find("sigma")
sigmavl.append(ts.getValV())
sigmael.append(ts.getError())

print(sigmavl)
print(sigmael)
