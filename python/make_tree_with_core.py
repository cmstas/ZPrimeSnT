#!/usr/bin/env python
from tqdm import tqdm
import ROOT as r
import os
import array

class BranchWrapper(object):
    def __init__(self, name, branch, is_vector):
        self.name = name
        self.branch = branch
        self.is_vector = is_vector

    def set(self, x):
        if not self.is_vector:
            self.branch[0] = x
        else:
            raise RuntimeError("Cannot set() a vector branch ({})".format(self.name))

    def append(self, x):
        if self.is_vector:
            self.branch.push_back(x)
        else:
            raise RuntimeError("Cannot append() to a scalar branch ({})".format(self.name))

    def extend(self, xx):
        if self.is_vector:
            for x in xx:
                self.branch.push_back(x)
        else:
            raise RuntimeError("Cannot extend() a scalar branch ({})".format(self.name))

class Looper(object):
    def __init__(self, chain, output_name="temp.root"):
        self.chain = chain
        self.output_name = output_name
        self.output_file = r.TFile(self.output_name, "recreate")
        self.output_tree = r.TTree("Events", "")
        self.output_branches = dict()

        self.init_core()

    def init_core(self):
        r.gSystem.Load('../NanoCORE/NANO_CORE.so')
        for include in ["Nano.cc", "MetSelections.cc"]:
            r.gInterpreter.ProcessLine('#include "../NanoCORE/%s"' % include)

        # CORE functions will be ROOT object members after we gSystem.Load CORE
        from ROOT import nt, passesMETfilters, gconf
        gconf.year = 2018
        self.nt = nt
        self.nt.Init(self.chain)

    def make_branch(self, name, typestring):
        # Python: https://docs.python.org/2/library/array.html
        # ROOT: https://root.cern.ch/doc/v612/classTTree.html
        extra = []
        if typestring == "vector<int>": obj = r.vector("int")()
        if typestring == "vector<float>": obj = r.vector("float")()
        if typestring == "vector<bool>": obj = r.vector("bool")()
        if typestring == "float":
            obj = array.array("f",[999]) # float
            extra.append("{}/F".format(name)) # Float_t
        if typestring == "bool":
            obj = array.array("b",[0]) # signed char
            extra.append("{}/O".format(name)) # Bool_t
        if typestring == "int":
            obj = array.array("i",[999]) # signed int
            extra.append("{}/I".format(name)) # Int_t
        if typestring == "long":
            obj = array.array("L",[999]) # unsigned long
            extra.append("{}/L".format(name)) # Long64_t
        self.output_branches[name] = obj
        self.output_tree.Branch(name,obj,*extra)

    def get_branch(self, name, typestring):
        if name not in self.output_branches:
            self.make_branch(name, typestring)

        return BranchWrapper(name, self.output_branches[name], ("vec" in typestring))

    def b(self, *args, **kwargs):
        # alias to `get_branch`
        return self.get_branch(*args, **kwargs)


    def clear_branches(self):
        for v in self.output_branches.values():
            if hasattr(v,"clear"):
                v.clear()
            elif v.typecode in ["f", "i", "L"]:
                v[0] = -999
            elif v.typecode in ["b"]:
                v[0] = 0

    def loop(self, nevents=-1, progress=True):
        N = self.chain.GetEntries()
        if not progress:
            iterable = range(self.chain.GetEntries())
        else:
            iterable = tqdm(range(self.chain.GetEntries()),total=self.chain.GetEntries())
        for ievent in iterable:
            if nevents > 0 and ievent > nevents: break
            self.nt.GetEntry(ievent)
            self.clear_branches()
            self.process()
            self.output_tree.Fill()
        self.cleanup()

    def cleanup(self):
        self.output_tree.Write()
        self.output_file.Close()
        print("Wrote {}".format(self.output_name))

    def process(self):
        """
        Subclass and implement with something like
        ```
        ht = 0.
        for imu,pt in enumerate(self.nt.Muon_pt()):
            if pt < 15: continue
            self.b("pts", "vector<float>").append(pt)
            ht += pt
        self.b("ht", "float").set(ht)
        ```
        """
        raise NotImplemented()

if __name__ == "__main__":


    class MyLooper(Looper):
        def process(self):
            ht = 0.
            for imu,pt in enumerate(self.nt.Muon_pt()):
                if pt < 15: continue
                self.b("pts", "vector<float>").append(pt)
                ht += pt
            self.b("ht", "float").set(ht)

    ch = r.TChain("Events")
    ch.Add("root://redirector.t2.ucsd.edu///store/user/namin/nanoaod/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/8E0C8306-DC0D-0548-BA7C-D0698140DF28.root");
    looper = MyLooper(ch)
    looper.loop(nevents=1000)

