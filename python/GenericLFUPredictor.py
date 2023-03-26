#!/bin/env python3

import argparse

import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

import math
import numpy as np

from compute_width import calculate_width
from SignalYieldCalculator import SignalYieldCalculator


class GenericLFUPredictor:
   """
   Construct as
   obj = GenericLFUPredictor(lumi),
   Evaluate the class using
   obj.calculate(mass, f2b_Nexcl_pairs, delsb, mult_gnu, nsteps, couplings_plot))
   where
   - mass = Mass of Zprime
   - f2b_Nexcl_pairs = List of (f2b, N_excluded) pairs (list of lists)
   - mreso = Resolution at 'mass'
   - max_width_mult = Multiplier on 'mreso' to define the validity range
   - delsb = delta_sb parameter value in the GenericLFU model
   - mult_gnu = Multiplier of gnu in the GenericLFU model
   - nsteps = Number of points
   - couplings_plot = Set of couplings to be used in the signal example included in the paper plots
   Returns a [list of nsteps (glep, gb, total width) pairs, corrected yields for signal with couplings_plot].
   """

   def __init__(self,lumi,fname_xs=None,fname_acceff=None):
      self.yields = SignalYieldCalculator(lumi,fname_xs,fname_acceff)
      self.widthcorr_coeff = 0.61179

   def calculate(self, mass, f2b_Nexcl_pairs, mreso, max_width_mult=0.5, delsb=0., mult_gnu=1., nsteps=100, couplings_plot={ "glep" : 0.5, "gb" : 0.5, "gnu" : 0.5 }):
      res = []

      couplings=dict()
      couplings["glep"]=couplings["gb"]=1.
      couplings["delsb"]=delsb
      couplings["gnu"]=couplings["glep"]*mult_gnu
      # Since delsb determines f2b, we compute that only once.
      f2b_Nexcl_pairs.sort()
      N1bb=self.yields.eval("bb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
      N1sb=self.yields.eval("sb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
      N2bb=self.yields.eval("bb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
      N2sb=self.yields.eval("sb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
      Ntot = N1bb+N1sb+N2bb+N2sb
      f2b = (N2bb+N2sb)/Ntot
      res = []
      Npred = -1. # This is the excluded value.
      for i in range(0,len(f2b_Nexcl_pairs)-1):
         n1 = f2b_Nexcl_pairs[i][1]
         n2 = f2b_Nexcl_pairs[i+1][1]
         f1 = f2b_Nexcl_pairs[i][0]
         f2 = f2b_Nexcl_pairs[i+1][0]
         if f2b>=f1 and f2b<=f2:
            Npred = n1 + (n2-n1)/(f2-f1)*(f2b-f1)
            break

      # Obtain GL, GB, N0
      couplings["glep"]=1.
      couplings["gb"]=0.
      couplings["gnu"]=couplings["glep"]*mult_gnu
      GL = calculate_width(mass, couplings, "GenericLFU", "Zp", False)
      couplings["glep"]=0.
      couplings["gb"]=1.
      couplings["gnu"]=couplings["glep"]*mult_gnu
      GB = calculate_width(mass, couplings, "GenericLFU", "Zp", False)
      couplings["glep"]=1.
      couplings["gb"]=1.
      couplings["gnu"]=couplings["glep"]*mult_gnu
      N1bb=self.yields.eval("bb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
      N1sb=self.yields.eval("sb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
      N2bb=self.yields.eval("bb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
      N2sb=self.yields.eval("sb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
      N0 = (N1bb+N1sb+N2bb+N2sb)*(GL+GB)/(GL*GB)

      # Calculate bounds feasibility
      GZpminB = mreso / (2.*self.widthcorr_coeff)
      GZpminDelta = GZpminB**2 - 4.*Npred/N0*mreso/self.widthcorr_coeff
      if GZpminDelta<=0.:
         return res # No exclusions
      GZpmin = GZpminB - math.sqrt(GZpminDelta)
      GZpsup = GZpminB + math.sqrt(GZpminDelta)
      GZpmax = GZpsup
      if max_width_mult>0.:
         GZpmax = min(GZpmax, mreso*max_width_mult)

      GZp_ff_pairs = []
      GZp_ff_pairs_backward = []
      for ip in range(0, nsteps+1):
         GZp = GZpmax - (GZpmax - GZpmin)/float(nsteps)*float(ip)
         if GZp == GZpmin or GZp == GZpsup:
            GZp_ff_pairs.append([GZp, 0.5])
         else:
            ffC = Npred / (N0 * GZp * (1. - self.widthcorr_coeff/mreso*GZp))
            ffA = 1.
            ffB = -1.
            ffDelta = ffB**2 - 4.*ffA*ffC
            if ffDelta<=0.:
               continue
            ffmin = (-ffB - math.sqrt(ffDelta))/(2.*ffA)
            ffmax = (-ffB + math.sqrt(ffDelta))/(2.*ffA)
            GZp_ff_pairs.append([GZp, ffmin])
            GZp_ff_pairs_backward.append([GZp, ffmax])
      for ip in range(0, len(GZp_ff_pairs_backward)):
         GZp_ff_pairs.append(GZp_ff_pairs_backward[len(GZp_ff_pairs_backward)-1-ip])

      # Translate GZp, ff pairs to gl, gb.
      for GZp_ff_pair in GZp_ff_pairs:
         GZp = GZp_ff_pair[0]
         ff = GZp_ff_pair[1]
         vgl = math.sqrt((1.-ff)*GZp/GL)
         vgb = math.sqrt(ff*GZp/GB)
         # Inverting the two equations above to solve for GZp(vgl,vgb) gives:
         # GZp = vgl*GL + vgb*GB
         res.append([vgl, vgb, GZp])

      return res, N0*(1. - self.widthcorr_coeff/mreso*(couplings_plot["glep"]*GL + couplings_plot["gb"]*GB))
