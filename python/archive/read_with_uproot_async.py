import time
import os
import numpy as np
import uproot
import concurrent.futures
from utils.jagged_operations import jagged_operation

# In the other example, we read branches first and then we compute stuff
# from them afterwards -- serially. Here, we let some workers do
# the I/O while we're calculating.

f = uproot.open("../6204E92D-C712-E811-AF42-E0071B740D80.root")
t = f["Events"]

executor = concurrent.futures.ThreadPoolExecutor(8)

# Queue up a list of chunks (which are lambdas) to turn into data later
t0 = time.time()
chunks = []
for chunk in t.iterate(
        ["Jet_pt","Electron_pt","Electron_jetIdx","Electron_mvaTTH",
            ],
        entrysteps=int(2e5),
        executor=executor,
        blocking=False,
        ):
    print("Queueing up a chunk:", chunk)
    chunks.append(chunk)

# NOTE: at this point, we could sleep for dramatic effect
# time.sleep(3)
# The workers are working, and by the time we're done sleeping
# there would be no wait time when actually getting the chunks (`chunk()`)

tot_mvas = []
tot_ptratios = []
for chunk in chunks:
    print("Working on chunk:",chunk)
    data = chunk()
    jidxs = data["Electron_jetIdx"]
    epts = data["Electron_pt"]
    jpts = data["Jet_pt"]
    mvas = data["Electron_mvaTTH"]

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
    # push them into a list of arrays
    tot_mvas.append(mvas)
    tot_ptratios.append(ptratios)

# combine all the arrays from the chunks together again
mvas = np.concatenate(tot_mvas)
ptratios = np.concatenate(tot_ptratios)

t1 = time.time()
print("Took {:.2f} seconds @ {:.2f}MHz".format(
        t1-t0,1.e-6*len(t)/(t1-t0)))

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
