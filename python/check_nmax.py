#!/bin/env python

import ROOT as r
import os

import sys

def usage():
    print("Usage:")
    print("")
    print("   python {} NANOFILE".format(sys.argv[0]))
    print("")
    sys.exit()

try:
    input_file = str(sys.argv[1])
except:
    usage()

ch = r.TChain("Events")
ch.Add(input_file);

branch_nmaxs = {
"nSV" : 39 ,
"nSoftActivityJet" : 21 ,
"nLHEScaleWeight" : 3 ,
"nCorrT1METJet" : 102 ,
"nMuon" : 30 ,
"nGenJet" : 60 ,
"nPSWeight" : 15 ,
"nLHEPart" : 24 ,
"nTau" : 18 ,
"nIsoTrack" : 21 ,
"nLHEPdfWeight" : 3 ,
"nFsrPhoton" : 9 ,
"nOtherPV" : 12 ,
"nTrigObj" : 108 ,
"nSubJet" : 33 ,
"nSubGenJetAK8" : 42 ,
"nGenVisTau" : 9 ,
"nGenJetAK8" : 24 ,
"nElectron" : 21 ,
"nFatJet" : 18 ,
"nJet" : 81 ,
"nGenIsolatedPhoton" : 12 ,
"nGenDressedLepton" : 12 ,
"nGenPart" : 402 ,
"nPhoton" : 24 ,
"nLHEReweightingWeight" : 3 ,
"nLHEWeight" : 60 ,
}

for br in branch_nmaxs:
    print("{} <= {}".format(br, branch_nmaxs[br]))
    ch.Scan("{}".format(br), "{}>{}".format(br, branch_nmaxs[br]))
