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
   obj.calculate(mass, f2b_Nexcl_pairs, delsb, mult_gnu, nsteps)
   where
   - mass = Mass of Zprime
   - f2b_Nexcl_pairs = List of (f2b, N_excluded) pairs (list of lists)
   - delsb = delta_sb parameter value in the GenericLFU model
   - mult_gnu = Multiplier of gnu in the GenericLFU model
   - nsteps = Number of points
   Returns a list of nsteps (glep, gb, total width) pairs.
   """

   def __init__(self,lumi):
      self.yields = SignalYieldCalculator(lumi)

   def calculate(self, mass, f2b_Nexcl_pairs, delsb=0., mult_gnu=1., nsteps=100, max_width=-1.):
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
      Npred = -1.
      for i in range(0,len(f2b_Nexcl_pairs)-1):
         n1 = f2b_Nexcl_pairs[i][1]
         n2 = f2b_Nexcl_pairs[i+1][1]
         f1 = f2b_Nexcl_pairs[i][0]
         f2 = f2b_Nexcl_pairs[i+1][0]
         if f2b>=f1 and f2b<=f2:
            Npred = n1 + (n2-n1)/(f2-f1)*(f2b-f1)
            break

      nfracs=nsteps if max_width<0. else 6
      inc=1./float(nfracs)
      for ir in range(0, nfracs+1):
         flep = inc*float(ir)
         couplings["glep"]=math.sqrt(flep);
         couplings["gb"]=math.sqrt(1.-flep)
         couplings["gnu"]=couplings["glep"]*mult_gnu
         N1bb=self.yields.eval("bb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
         N1sb=self.yields.eval("sb","Nb_eq_1",mass,"GenericLFU",couplings,"B3mL2")[0]
         N2bb=self.yields.eval("bb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
         N2sb=self.yields.eval("sb","Nb_geq_2",mass,"GenericLFU",couplings,"B3mL2")[0]
         Ntot = N1bb+N1sb+N2bb+N2sb
         if Ntot==0.: continue
         scale = math.sqrt(Npred/Ntot)
         couplings["glep"]=couplings["glep"]*scale
         couplings["gb"]=couplings["gb"]*scale
         couplings["gnu"]=couplings["glep"]*mult_gnu
         gzp = calculate_width(mass, couplings, "GenericLFU", "Zp", False)
         res.append([couplings["glep"], couplings["gb"], gzp])

      mm = np.array(
        [
           [ res[0][0]**2, res[0][1]**2 ],
           [ res[1][0]**2, res[1][1]**2 ]
        ]
      )
      fr = np.array(
         [
            res[0][0]**2 * res[0][1]**2,
            res[1][0]**2 * res[1][1]**2
         ]
      )
      gammar = np.array(
         [
            res[0][2],
            res[1][2]
         ]
      )
      minv=np.linalg.inv(mm)
      gcoefs = [ 0., 0. ]
      gammacoefs = [ 0., 0. ]
      for ii in range(2):
         for jj in range(2):
            gcoefs[ii] = gcoefs[ii] + minv[ii][jj]*fr[jj]
            gammacoefs[ii] = gammacoefs[ii] + minv[ii][jj]*gammar[jj]

      #allOk=True
      #for rr in res:
         #qq=gcoefs[0]*rr[0]**2 - rr[0]**2*rr[1]**2 + gcoefs[1]*rr[1]**2
         #qg=gammacoefs[0]*rr[0]**2 - rr[2] + gammacoefs[1]*rr[1]**2
         #if abs(qq)>1e-5:
            #allOk=False
            #print("Quotient for gl={}, gb={}: {} / {}".format(rr[0], rr[1], qq))
         #if abs(qg)>1e-5:
            #allOk=False
            #print("Quotient g for gl={}, gb={}: {} / {}".format(rr[0], rr[1], qg))
      #print("All OK? {}".format(allOk))

      if max_width>0.:
         res = []
         aa = gammacoefs[0] / gammacoefs[1]
         bb = gcoefs[0] - (max_width+gammacoefs[0]*gcoefs[1])/gammacoefs[1]
         cc = max_width*gcoefs[1]/gammacoefs[1]

         glfirst = math.sqrt((-bb - math.sqrt(bb**2 - 4*aa*cc))/(2*aa))
         gbfirst = -gcoefs[0]*glfirst**2 / (gcoefs[1] - glfirst**2)
         glsecond = math.sqrt((-bb + math.sqrt(bb**2 - 4*aa*cc))/(2*aa))
         gbsecond = -gcoefs[0]*glsecond**2 / (gcoefs[1] - glsecond**2)

         ffirst = (gbfirst**2)/(glfirst**2 + gbfirst**2)
         fsecond = (gbsecond**2)/(glsecond**2 + gbsecond**2)

         inc=(fsecond - ffirst)/float(nsteps)
         for ir in range(0, nsteps+1):
            vf = ffirst + inc*float(ir)
            vgl = math.sqrt(((gcoefs[1]-gcoefs[0])*vf+gcoefs[0])/vf)
            vgb = math.sqrt(vgl**2/(1.-vf)*vf)
            vgg = gammacoefs[0]*vgl**2 + gammacoefs[1]*vgb**2
            res.append([vgl, vgb, vgg])

      res.sort()
      return res
