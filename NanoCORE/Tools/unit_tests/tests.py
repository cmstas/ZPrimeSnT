#!/usr/bin/env python

import unittest
import os
import ROOT as r

def vround(a,digits=4):
    if (type(a) in [tuple, list]):
        return [round(x, digits) for x in a]
    elif (type(a) in [float]):
        return round(a, digits)
    else:
        return a

class CORETest(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        thispath = os.path.abspath(__file__)
        corebase = os.path.join(thispath.rsplit("NanoCORE/",1)[0], "NanoCORE")

        filename = thispath.rsplit("/",1)[0] + "/files/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18NanoAODv5_1000events.root"
        jecera = "Autumn18_V19_MC";

        file_and_jecera = "file={}\n\tjecera={}".format(filename, jecera)
        print(">>> Starting unit tests with\n\t"+file_and_jecera)

        print(">>> Making TChain")
        ch = r.TChain("Events")
        ch.Add(filename);
        print(">>> Loading shared library")
        r.gSystem.Load('{corebase}/NANO_CORE.so'.format(corebase=corebase))
        print(">>> Loading includes")
        includes = [
            "Nano.cc",
            "SSSelections.cc",
            "ElectronSelections.cc",
            "MuonSelections.cc",
            "MetSelections.cc",
            "Config.cc"
        ]
        for include in includes:
            cpp_include = '#include "{corebase}/{include}"'.format(
                corebase=corebase, 
                include=include
            )
            r.gInterpreter.ProcessLine(cpp_include)

        print(">>> Making jet corrector")
        p = dict(corebase=corebase, jecera=jecera)
        vs = r.std.vector("string")()
        jetcorr_path = "{corebase}/Tools/jetcorr/data/{jecera}/{jecera}_"
        vs.push_back((jetcorr_path+"L1FastJet_AK4PFchs.txt").format(**p))
        vs.push_back((jetcorr_path+"L2Relative_AK4PFchs.txt").format(**p))
        vs.push_back((jetcorr_path+"L3Absolute_AK4PFchs.txt").format(**p))
        from ROOT import makeJetCorrector
        jetcorr = makeJetCorrector(vs)

        print(">>> Initializing nanotree")
        from ROOT import nt
        nt.Init(ch)
        print(">>> Getting first event")
        nt.GetEntry(0)
        print(">>> Done initializing")

        # attach objects to be used later to class instances
        cls.ch = ch
        cls.nt = nt
        cls.jetcorr = jetcorr

    def test_jec_correction(self):
        self.jetcorr.setJetPtEtaARho(50., 1.1, 0.5, 25.)
        corr = float(self.jetcorr.getCorrection())
        self.assertEqual(vround(corr), vround(1.01693546772))

    def test_jec_subcorrections(self):
        self.jetcorr.setJetPtEtaARho(50., 1.1, 0.5, 25.)
        subcorrs = list(map(float, self.jetcorr.getSubCorrections()))
        self.assertEqual(
            vround(subcorrs), 
            vround([
                0.9395483732223511, 
                1.0169354677200317, 
                1.0169354677200317
            ])
        )

    def test_infer_year(self):
        self.assertEqual(self.nt.year(), 2018)

    def test_infer_mc(self):
        self.assertEqual(self.nt.isData(), False)

    def test_t1met(self):
        from ROOT import getT1CHSMET
        t1pair = getT1CHSMET(self.jetcorr)
        self.assertEqual(vround(self.nt.RawMET_pt()), vround(33.71875))
        self.assertEqual(vround(self.nt.RawMET_phi()), vround(2.087890625))
        self.assertEqual(vround(self.nt.MET_pt()), vround(30.6464557648))
        self.assertEqual(vround(self.nt.MET_phi()), vround(2.0341796875))
        self.assertEqual(vround(t1pair.first), vround(30.6478996277))
        self.assertEqual(vround(t1pair.second), vround(2.03437948227))

    def test_met_filters(self):
        from ROOT import gconf, passesMETfilters
        gconf.year = self.nt.year()
        self.assertEqual(passesMETfilters(self.nt.isData()), True)

    def test_electrons(self):
        from ROOT import gconf, SS
        gconf.year = self.nt.year()
        pts = list(self.nt.Electron_pt())
        nElectron = len(pts)
        self.assertEqual(nElectron, 1)
        self.assertEqual(vround(pts), vround([43.71261215209961]))
        self.assertEqual(SS.electronID(0, SS.IDtight, gconf.year), False)

    def test_muons(self):
        from ROOT import gconf, SS
        gconf.year = self.nt.year()
        self.nt.GetEntry(10)
        pts = list(self.nt.Muon_pt())
        nMuon = len(pts)
        self.assertEqual(nMuon, 1)
        self.assertEqual(vround(pts), vround([32.8664474487]))
        self.assertEqual(SS.muonID(0, SS.IDtight, gconf.year), True)
        self.nt.GetEntry(0)

if __name__ == "__main__":
    unittest.main(verbosity=2)
