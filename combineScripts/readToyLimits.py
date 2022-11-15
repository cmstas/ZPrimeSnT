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

fout = open("%s/limits_toys_%s.txt"%(outdir,model),"w")

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
    fout.write("# mass,f2b,obs,exp,exp-2s,exp-1s,exp+1s,exp+1s\n")
else:
    fout.write("# model,mass,obs,exp,exp-2s,exp-1s,exp+1s,exp+1s\n")

for m in masses:
    for f in f2bs:
        obs = -1.0
        exp = -1.0
        m2s = -1.0
        m1s = -1.0
        p1s = -1.0
        p2s = -1.0
        fname = []
        if model != "nomodel":
            #fname.append("%s/lim_toysObs_%s_m%.0f.txt"%(limdir,model,m))
            #fname.append("%s/lim_toysEm2_%s_m%.0f.txt"%(limdir,model,m))
            #fname.append("%s/lim_toysEm1_%s_m%.0f.txt"%(limdir,model,m))
            #fname.append("%s/lim_toysExp_%s_m%.0f.txt"%(limdir,model,m))
            #fname.append("%s/lim_toysEp1_%s_m%.0f.txt"%(limdir,model,m))
            #fname.append("%s/lim_toysEp2_%s_m%.0f.txt"%(limdir,model,m))
            fname.append("%s/lim_toysObs_%s_m%.0f.txt"%(limdir,model,m))
            fname.append("%s/lim_toysEm1_%s_m%.0f.txt"%(limdir,model,m))
            fname.append("%s/lim_toysEm1_%s_m%.0f.txt"%(limdir,model,m))
            fname.append("%s/lim_toysExp_%s_m%.0f.txt"%(limdir,model,m))
            fname.append("%s/lim_toysEp1_%s_m%.0f.txt"%(limdir,model,m))
            fname.append("%s/lim_toysEp1_%s_m%.0f.txt"%(limdir,model,m))
        else:
            #fname.append("%s/lim_toysObs_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            #fname.append("%s/lim_toysEm2_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            #fname.append("%s/lim_toysEm1_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            #fname.append("%s/lim_toysExp_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            #fname.append("%s/lim_toysEp1_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            #fname.append("%s/lim_toysEp2_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            fname.append("%s/lim_toysObs_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            fname.append("%s/lim_toysExp_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            fname.append("%s/lim_toysExp_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            fname.append("%s/lim_toysExp_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            fname.append("%s/lim_toysExp_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
            fname.append("%s/lim_toysExp_f2b%.0f_m%.0f.txt"%(limdir,100.0*f,m))
        allExist = True
        for fn in fname:
            if not os.path.exists(fn):
                allExist = False
                break
        if not allExist:
            continue
        limits = []
        for fn in fname:
            fin = open(fn,"r")
            for l in fin.readlines():
                if not l.startswith("Limit"):
                    continue
                else:
                    limits.append(l.split()[3])
                    break
            fin.close()
        if len(limits)<6:
            continue
        obs = limits[0]
        m2s = limits[1]
        m1s = limits[2]
        exp = limits[3]
        p1s = limits[4]
        p2s = limits[5]
        fin.close()
        if model != "nomodel":
            fout.write("%s,%.0f,%s,%s,%s,%s,%s,%s\n"%(model,m,obs,exp,m2s,m1s,p1s,p2s))
        else:
            fout.write("%.0f,%.2f,%s,%s,%s,%s,%s,%s\n"%(m,f,obs,exp,m2s,m1s,p1s,p2s))

fout.close()
