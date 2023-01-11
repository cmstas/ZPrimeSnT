#!/bin/env python3

import argparse

import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

import math

from compute_width import get_model_name
from compute_width import get_model_reference_pars
from compute_width import calculate_Zpmumu_weight


def getDefaultModelName(model):
   if model is not None and model == "BFF":
      return "BFF_gmu_0p17_dbs_0p04_gb_0p02"
   else:
      return get_model_name(model)


class SignalXSContainer:
   """
   Construct as
   obj = SignalXSContainer([optional: ROOT file name for cross sections])
   and evaluate as
   obj.eval(model,state,mass)
   where
   - model = "Y3", "DY3", "DYp3", "B3mL2", "BFF"
   - state = "ss", "sb", "bb"
   - mass = Mass of Zprime
   Returns the cross section at nominal parameter values.
   """
   def __init__(self,fname=None):
      if fname is None:
         fname="${CMSSW_BASE}/src/ZPrimeSnT/data/xsec_interpolation_ZPrimeToMuMuSB_bestfit_13TeV_Allanach.root"
      self.infile = ROOT.TFile.Open(fname, "read")
      if self.infile is None:
         raise RuntimeError("SignalXSContainer file {} is None!".format(fname))
      elif self.infile.IsZombie():
         raise RuntimeError("SignalXSContainer could not open file {}!".format(fname))

      models = ["Y3","DY3","DYp3","B3mL2","BFF"]
      states = ["ss","sb","bb","double_sb"]
      self.splines = dict()
      for model in models:
         self.splines[model] = dict()
         for state in states:
            sname = "spline_{}_xsec_{}".format(getDefaultModelName(model),state)
            sp = self.infile.Get(sname)
            if sp and sp is not None:
               self.splines[model][state] = sp

   def eval(self, model, state, mass):
      sp = self.splines[model][state]
      xl = sp.GetXmin()
      xh = sp.GetXmax()
      if mass<xl or mass>xh:
         return 0
      else:
         return math.exp(sp.Eval(mass))


class SignalAccEffContainer:
   """
   Construct as
   obj = SignalAccEffContainer([optional: ROOT file name for acceptance*eficiency interpolation])
   and evaluate as
   obj.eval(model,state,cat,mass)
   where
   - model = "Y3", "DY3", "DYp3", "B3mL2", "BFF", or "GenericLFU"
   - state = "ss", "sb", "bb"
   - cat = "Nb_eq_1", "Nb_geq_2"
   - mass = Mass of Zprime
   Returns a triplet of nominal acc*eff, lower unc., higher unc.
   """
   def __init__(self,fname=None):
      if fname is None:
         fname="${CMSSW_BASE}/src/ZPrimeSnT/data/acceff_interpolation_Run2.root"
      self.infile = ROOT.TFile.Open(fname, "read")
      if self.infile is None:
         raise RuntimeError("SignalAccEffContainer file {} is None!".format(fname))
      elif self.infile.IsZombie():
         raise RuntimeError("SignalAccEffContainer could not open file {}!".format(fname))

      models = ["Y3","DY3","DYp3","B3mL2","BFF"]
      states = ["ss","sb","bb","double_sb"]
      cats = ["Nb_eq_1","Nb_geq_2"]
      self.splines = dict()
      self.uncs = dict()
      for model in models:
         self.splines[model] = dict()
         self.uncs[model] = dict()
         for state in states:
            self.splines[model][state] = dict()
            self.uncs[model][state] = dict()
            for cat in cats:
               # Acceptances are averaged, so there is no need to pass the model
               # Arguments include the model just so that we can support such functionality if we need to distinguish them in the future.
               sname = None
               if model != "BFF":
                  sname = "spline_avg_acceff_{}_{}_{}".format(state,cat,"Run2")
               else:
                  sname = "spline_{}_acceff_{}_{}_{}".format(getDefaultModelName(model),state,cat,"Run2")
               sp = self.infile.Get(sname)
               if sp and sp is not None:
                  self.splines[model][state][cat] = sp
                  self.uncs[model][state][cat] = [ self.infile.Get(sname.replace("acceff", "errsq_dn_acceff")), self.infile.Get(sname.replace("acceff", "errsq_up_acceff")) ]

   def eval(self, model, state, cat, mass):
      sp_nom = self.splines[model][state][cat]
      sp_dn = self.uncs[model][state][cat][0]
      sp_up = self.uncs[model][state][cat][1]
      xl = sp_nom.GetXmin()
      xh = sp_nom.GetXmax()
      if mass<xl or mass>xh:
         return 0.,0.,0.
      else:
         vnom = sp_nom.Eval(mass)
         errsqdn = sp_dn.Eval(mass)
         errsqup = sp_up.Eval(mass)
         return vnom,-math.sqrt(errsqdn),math.sqrt(errsqup)


class SignalYieldCalculator:
   """
   Construct as
   obj = SignalYieldCalculator([optional: luminosity factor (default=1),
   and ROOT file names for xsec, and acceptance*eficiency interpolation]).
   Evaluate the class using
   obj.eval(state, cat, mass, model, couplings, model_old, couplings_old)
   where
   - state = "ss", "sb", or "bb" in all models, or "double_sb" in the BFF model only
   - cat = "Nb_eq_1", "Nb_geq_2"
   - mass = Mass of Zprime
   - model = "Y3", "DY3", "DYp3", "B3mL2", "BFF", "GenericLFU"
   - couplings = Appropriate dictionary of couplings for model.
   - model_old = "Y3", "DY3", "DYp3", "B3mL2", "BFF" (but "BFF" is not actually run, so don't use it!)
   - couplings_old = Appropriate dictionary of couplings for model_old, or None for the defaults in sample generation (the user should most likely keep this parameter as None).
   Returns a triplet of nominal yield, lower acc*eff. unc., higher acc*eff. unc.
   """
   def __init__(self,lumi=1.,fname_xs=None,fname_acceff=None):
      self.xs = SignalXSContainer(fname_xs)
      self.acceff = SignalAccEffContainer(fname_acceff)
      self.lumi = float(lumi)

   def eval(self, state, cat, mass, model, couplings, model_old=None, couplings_old=None):
      prod=-1
      if state=="ss":
         prod=6
      elif state=="sb":
         prod=8
      elif state=="double_sb":
         prod=64
      elif state=="bb":
         prod=10
      else:
         return 0

      if model is None:
         raise ValueError("SignalYieldCalculator::eval: model cannot be None.")
      if model_old is None:
         model_old = model
      if model_old=="GenericLFU":
         raise ValueError("SignalYieldCalculator::eval: model_old cannot be {}.".format(model_old))

      xswgt = calculate_Zpmumu_weight(
         minv=mass,
         MZp=mass,
         couplings=couplings,
         model=getDefaultModelName(model),
         prod=prod,useIntMass=True,
         couplings_old=couplings_old,
         model_old=getDefaultModelName(model_old)
         )

      ynom = self.lumi * self.xs.eval(getDefaultModelName(model_old), state, mass)
      acc = self.acceff.eval(getDefaultModelName(model_old), state, cat, mass)
      res=[]
      for aa in acc:
         res.append(xswgt*ynom*aa)
      if res[0]<0.:
         res[0]=0.
         res[1]=0.
      if res[0]+res[1]<0.:
         res[1]=-res[0]
      return res[0],res[1],res[2]
