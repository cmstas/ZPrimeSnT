import re
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--s", default=[], action="append", help="Choose the signal model(s): 'Y3','DY3','DYp3','B3mL2'.")
parser.add_argument("--m", default=[], action="append", help="Choose the mass(es): '100','200','400','700','1000','1500','2000'.")
parser.add_argument("--y", default=[], action="append", help="Choose the year(s): '2016', '2016APV', '2017', '2018'.")

args = parser.parse_args()
if args.s==[]: args.s=["Y3","DY3","DYp3","B3mL2"]
if args.m==[]: args.m=["100","200","400","700","1000","1500","2000"]
if args.y==[]: args.y=["2016","2016APV","2017","2018"]

basepath = "/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404"

for s in args.s:
  for m in args.m:
    samplepath = "ZPrimeToMuMuSB_M"+m+"_bestfit_TuneCP5_13TeV_Allanach_"+s+"_5f_madgraph_pythia8_NoPSWgts"
    for y in args.y:
      yearpath = "RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private" if y=="2018" else "RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2_private" if y=="2017" else "RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2_private" if y=="2016APV" else "RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2_private" if y=="2016" else ""
      if yearpath=="":
        print "Invalid year"
        exit()
      filepath = basepath+"/"+samplepath+"/"+yearpath+"/XSEC/"

      xsec_tot = 0.0
      events_tot = 0.0

      for txtfile in os.listdir(filepath):
        txtfile_fullpath = filepath+txtfile

        with open(txtfile_fullpath, 'r') as file:
          line = file.readline()
          while line:
            if re.match(r'^Total.*', line):
              xsec_line = line
              break
            line = file.readline()

          xsec_splitline = xsec_line.split()
          [xsec,events] = [ float(xsec_splitline[1]), float(xsec_splitline[4]) ]
          xsec_tot = xsec_tot + xsec * events
          events_tot = events_tot + events

      xsec_final = xsec_tot / events_tot
      print "Signal model: "+str(s)+",\tMass: "+str(m)+"\tYear: "+str(y)+"\t Final weighted average xsec = "+str(xsec_final)

