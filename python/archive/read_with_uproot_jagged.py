import time
import os

import numpy as np
import uproot

# f = uproot.open("../508B6DBB-9742-E811-BA65-A4BF0112BCB0.root")
f = uproot.open("../6204E92D-C712-E811-AF42-E0071B740D80.root")
t = f["Events"]


# # for small files, multithreading doesn't help due to overhead
# import concurrent.futures
# executor = concurrent.futures.ThreadPoolExecutor(4)

# Read the branches -- happens at ~0.35MHz
t0 = time.time()
info = t.arrays(
        ["Jet_pt","Electron_pt","Electron_jetIdx","Electron_mvaTTH"],
        # executor=executor,
        )

jidxs = info["Electron_jetIdx"]
epts = info["Electron_pt"]
jpts = info["Jet_pt"]
mvas = info["Electron_mvaTTH"]
nevts = len(jidxs)
t1 = time.time()
print("Read 4 branches from {} events in {:.2f} seconds @ {:.2f}MHz".format(
        nevts,t1-t0,1.e-6*len(jidxs)/(t1-t0)))

# Each electron has an index into the jet branches, so follow it
# and get the matching jet pts for each electron (they are negative
# if no match is found)
from utils.jagged_operations import jagged_operation
t0 = time.time()
matched_jpts = jagged_operation(
        typ="index2into1",
        jagged_arr=jpts,
        jagged_idxs=jidxs,
        masks=jidxs.content>=0)
# compute pt ratio -- happens at ~10MHz
good = matched_jpts>0
ptratios = epts.content/matched_jpts
mvas = mvas.content[good]
ptratios = ptratios[good]
t1 = time.time()
print("Calculated ptratios for {} events with {} electrons, {} jets in {:.2f} seconds @ {:.2f}MHz".format(
        nevts,len(epts.content),len(jpts.content),t1-t0,1.e-6*len(jpts)/(t1-t0)))

# plot pt ratios for low and high ttH leptonMVA electrons
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.hist(ptratios[mvas > 0.0], bins=np.linspace(-0.1,1.1,100),histtype="stepfilled",alpha=0.5, normed=True, label="good")
ax.hist(ptratios[mvas < 0.0], bins=np.linspace(-0.1,1.1,100),histtype="stepfilled",alpha=0.5, normed=True, label="bad")
ax.legend()
fig.savefig("ptratios.png")
os.system("which ic && ic ptratios.png")
