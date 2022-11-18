import os,sys

useSignalMC = False

if len(sys.argv)<3:
    print("Please, specify model and limit directory.")
    exit(1)

model = sys.argv[1]
limdir = sys.argv[2]
if len(sys.argv)>3:
    outdir = sys.argv[3]
    if not os.path.exists(outdir):
        os.makedirs(outdir)
else:
    outdir = limdir

fout = open("%s/significance_%s.txt"%(outdir,model),"w")

masses = [250,400,550,700,850,1000,1250,1500,2000]
if not useSignalMC:
    mF = 350.0
    mL = 2000.0
    masses = [mF]
    tm = mF
    while tm < mL:
        if tm<400.0:
            tm=tm+5.0
        elif tm<700.0:
            tm=tm+10.0
        elif tm<1000.0:
            tm=tm+15.0
        elif tm<1500.0:
            tm=tm+25.0
        else:
            tm=tm+50.0
        masses.append(tm)

f2bs = [0.0]
if model == "nomodel":
    f2bs = [0.0,0.01,0.05,0.1,0.25,0.5,0.75,0.9,0.95,0.99,1.0]
    fout.write("# mass,f2b,significance (obs.)\n")
else:
    fout.write("# model,mass,significance (obs.)\n")

for m in masses:
    for f in f2bs:
        sig = 0.0
        if model != "nomodel":
            fname = "%s/lim_sigObs_%s_m%.0f.txt"%(limdir,model,m)
        else:
            fname = "%s/lim_sigObs_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m)
        if not os.path.exists(fname):
            continue
        else:
            fin=open(fname,"r")
        for l in fin.readlines():
            if not l.startswith("Significance"):
                continue
            sig = l.split()[len(l.split())-1]
        fin.close()
        if model != "nomodel":
            fout.write("%s,%.0f,%s\n"%(model,m,sig))
        else:
            fout.write("%.0f,%.2f,%s\n"%(m,f,sig))

fout.close()
