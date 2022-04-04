import os

import time
import numba
import numpy as np
import uproot

from tqdm import tqdm

jit = numba.autojit

f = uproot.open("../508B6DBB-9742-E811-BA65-A4BF0112BCB0.root")
t = f["Events"]

class Collection():
    def __init__(self, info={}):
        self.prefix = None
        self.N = 0
        self.vars = []
        for i,(k,v) in enumerate(info.items()):
            k = k.decode("utf-8")
            vname = k.split("_",1)[1]
            self.vars.append(vname)
            setattr(self, k.split("_",1)[1], v)
            if i == 0:
                self.prefix = k.split("_",1)[0]
                self.N = len(v)

    def __repr__(self):
        attributes = "\n".join(" - {}".format(v) for v in self.vars)
        return "<{} collection with {} entries and attributes: \n{}\n>".format(self.prefix, self.N, attributes)

Jets = Collection(t.arrays(["Jet_pt","Jet_eta","Jet_phi","Jet_mass","Jet_cleanmask","Jet_btagDeepB"]))
Electrons = Collection(t.arrays(["Electron_pt","Electron_eta","Electron_phi","Electron_mass","Electron_jetIdx","Electron_cutBased","Electron_miniPFRelIso_all"]))
Muons = Collection(t.arrays(["Muon_pt","Muon_eta","Muon_phi","Muon_mass","Muon_jetIdx","Muon_mediumId","Muon_miniPFRelIso_all"]))
MET = Collection(t.arrays(["MET_pt"]))
print(Jets)

@jit(numba.float64(numba.float64,numba.float64))
def dPhi(phi1,phi2):
    dphi = np.abs(phi2-phi1)
    if dphi >= np.pi: dphi -= 2.0*np.pi
    if dphi < -np.pi: dphi += 2.0*np.pi
    return dphi

@jit(numba.float64(numba.float64,numba.float64,numba.float64,numba.float64))
def deltaR(eta1,phi1,eta2,phi2):
    dphi = dPhi(phi1,phi2)
    deta = eta2-eta1
    return (deta*deta+dphi*dphi)**0.5

@jit
def get_match_index(eta1s,phi1s,eta2s,phi2s):
    matches = []
    for eta1,phi1 in zip(eta1s,phi1s):
        match = -1
        for idx,(eta2,phi2) in enumerate(zip(eta2s,phi2s)):
            if deltaR(eta1,phi1,eta2,phi2) < 0.4:
                match = idx
                break
        matches.append(match)
    return np.array(matches)

def classify_electrons(ievt,Electrons):
    etas = Electrons.eta[ievt]
    cbmedium = Electrons.cutBased[ievt] >= 3
    miniiso = Electrons.miniPFRelIso_all[ievt]
    passes = cbmedium
    passes[np.abs(etas > 2.5)] = 0
    passes[miniiso > 0.2] = 0
    return passes

def classify_muons(ievt,Muons):
    etas = Muons.eta[ievt]
    mediumid = Muons.mediumId[ievt]
    miniiso = Muons.miniPFRelIso_all[ievt]
    passes = mediumid
    passes[np.abs(etas > 2.4)] = 0
    passes[miniiso > 0.2] = 0
    return passes


#
list_nb = []
for i in tqdm(xrange(len(t))):
    # print(i)
    met = MET.pt[i]
    if met < 50.: continue

    jet_pts = Jets.pt[i]
    jet_cleanmasks = Jets.cleanmask[i]
    if np.sum(jet_pts[jet_cleanmasks==1]>40) < 2: continue

    electron_pts = Electrons.pt[i]
    muon_pts = Muons.pt[i]
    if sum(electron_pts>15.)+sum(muon_pts>10)<2: continue

    good_electrons = classify_electrons(i,Electrons)
    good_muons = classify_muons(i,Muons)

    ntightlep = sum(good_electrons)+sum(good_muons)
    ht = np.sum(jet_pts[jet_cleanmasks & (jet_pts>40)])
    njets = np.sum((jet_pts>40) & jet_cleanmasks)
    # all jets are btagged since btagDeepB is broken in nanoAOD
    nbtags = sum((Jets.btagDeepB[i]>-9000) & (jet_pts>25) & jet_cleanmasks)
    list_nb.append(nbtags)

list_nb = np.array(list_nb)

import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.hist(list_nb, bins=range(10),histtype="stepfilled",alpha=0.5, normed=True, label="good")
ax.legend()
fig.savefig("nbtags.png")
os.system("which ic && ic nbtags.png")
