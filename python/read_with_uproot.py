#!/usr/bin/env python3

import os
import sys
import numpy as np
import uproot
import uproot_methods
import time

t0 = time.time()
f = uproot.open("root://redirector.t2.ucsd.edu///store/user/namin/nanoaod/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/8E0C8306-DC0D-0548-BA7C-D0698140DF28.root")
t = f["Events"]
t1 = time.time()
print(f"Took {t1-t0:.2f}s to open the file and get the tree with {len(t)} entries")

t0 = time.time()
branches = t.arrays(["/(Electron|Jet)_(pt|eta|phi|mass|jetIdx|mvaTTH)/"],namedecode="ascii", entrystart=0, entrystop=200000)
t1 = time.time()
nevents = len(branches['Electron_pt'])
print(f"Took {t1-t0:.2f}s @ {0.001*nevents/(t1-t0):.1f}kHz to read {len(branches.keys())} branches from {nevents} events")

t0 = time.time()
jets = uproot_methods.TLorentzVectorArray.from_ptetaphim(
        branches["Jet_pt"],
        branches["Jet_eta"],
        branches["Jet_phi"],
        branches["Jet_mass"],
        )
t1 = time.time()
print(f"Took {t1-t0:.2f}s @ {0.001*len(jets)/(t1-t0):.1f}kHz to make jet p4s")

t0 = time.time()
electrons = uproot_methods.TLorentzVectorArray.from_ptetaphim(
        branches["Electron_pt"],
        branches["Electron_eta"],
        branches["Electron_phi"],
        branches["Electron_mass"],
        )
electrons["jetIdx"] = branches["Electron_jetIdx"]
electrons["mvaTTH"] = branches["Electron_mvaTTH"]
t1 = time.time()
print(f"Took {t1-t0:.2f}s @ {0.001*len(electrons)/(t1-t0):.1f}kHz to make electron p4s")

# Drop low pT electrons
electrons = electrons[electrons.pt>25.]

# Make sure all electrons have a jetidx to match
electrons = electrons[electrons["jetIdx"]>=0]

ptratios = electrons.pt/jets[electrons["jetIdx"]].pt
mvas = electrons["mvaTTH"]

# Now plot stuff
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.hist(ptratios[mvas > 0.5].flatten(), bins=np.linspace(-0.05,1.1,100),histtype="stepfilled",alpha=0.6, density=False, label="ttH MVA > 0.5")
ax.hist(ptratios[mvas < 0.5].flatten(), bins=np.linspace(-0.05,1.1,100),histtype="stepfilled",alpha=0.6, density=False, label="ttH MVA < 0.5")
ax.set_xlabel(r"$p_\mathrm{T}^\mathrm{ratio}$")
ax.set_ylabel(r"Entries")
ax.set_title(r"$p_\mathrm{T}^\mathrm{ratio}$ for electrons with $p_\mathrm{T}>25~\mathrm{GeV}$")
ax.legend()
fig.set_tight_layout(True)
fig.savefig("ptratios.png")
os.system("test $(which ic) && ic ptratios.png")
