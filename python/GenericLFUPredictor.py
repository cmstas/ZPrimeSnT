#!/bin/env python3

import argparse

import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

import math

from compute_width import calculate_width
from SignalYieldCalculator import SignalYieldCalculator


class GenericLFUPredictor:
   """
   Construct as
   obj = GenericLFUPredictor(),
   Evaluate the class using
   obj.calculate(mass, f2b_Nexcl_pairs, delsb)
   where
   - mass = Mass of Zprime
   - f2b_Nexcl_pairs = List of (f2b, N_excluded) pairs (list of lists)
   - delsb = delta_sb parameter value in the GenericLFU model
   - nsteps = Number of points
   Returns a list of nsteps (glep, gb, total width) pairs.
   """

   def __init__(self):
      self.yields = SignalYieldCalculator()

   def calculate(self, mass, f2b_Nexcl_pairs, delsb=0., nsteps=100):
      couplings=dict()
      couplings["glep"]=couplings["gnu"]=couplings["gb"]=1.
      couplings["delsb"]=delsb
      # Since delsb determines f2b, we compute that only once.
      f2b_Nexcl_pairs.sort()
      N1bb=self.yields.eval("bb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
      N1sb=self.yields.eval("sb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
      N2bb=self.yields.eval("bb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
      N2sb=self.yields.eval("sb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
      Ntot = N1bb+N1sb+N2bb+N2sb
      f2b = (N2bb+N2sb)/Ntot
      res = []
      Npred = -1.
      for i in range(0,len(f2b_Nexcl_pairs)-1):
         n1 = f2b_Nexcl_pairs[i][1]
         n2 = f2b_Nexcl_pairs[i+1][1]
         f1 = f2b_Nexcl_pairs[i][0]
         f2 = f2b_Nexcl_pairs[i+1][0]
         if f2b>=f1 and f2b<=f2:
            Npred = n1 + (n2-n1)/(f2-f1)*(f2b-f1)
            break

      nfracs=nsteps
      inc=1./float(nfracs)
      for ir in range(0, nfracs+1):
         flep = inc*float(ir)
         couplings["glep"]=couplings["gnu"]=math.sqrt(flep);
         couplings["gb"]=math.sqrt(1.-flep)
         N1bb=self.yields.eval("bb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
         N1sb=self.yields.eval("sb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
         N2bb=self.yields.eval("bb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
         N2sb=self.yields.eval("sb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
         Ntot = N1bb+N1sb+N2bb+N2sb
         if Ntot==0.: continue
         scale = math.sqrt(Npred/Ntot)
         couplings["glep"]=couplings["glep"]*scale
         couplings["gb"]=couplings["gb"]*scale
         gzp = calculate_width(mass, couplings, "GenericLFU", "Zp", False)
         res.append([couplings["glep"], couplings["gb"], gzp])

      res.sort()
      return res
