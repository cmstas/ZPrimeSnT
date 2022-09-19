import os,sys

if len(sys.argv)<3:
    print("Please, specify model and limit directory.")
    exit(1)

model = sys.argv[1]
limdir = sys.argv[2]
fout = open("%s/limits_%s.txt"%(limdir,model),"w")

which="shape"
if len(sys.argv)>3:
    which = sys.argv[3]

masses = [250,400,550,700,850,1000,1250,1500,2000]
f2bs = [0.0]
if model == "nomodel":
    f2bs = [0.0,0.1,0.25,0.5,0.75,0.9,1.0]
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
        if model != "nomodel":
            fin=open("%s/lim_%s_%s_m%.0f.txt"%(limdir,which,model,m),"r")
        else:
            fin=open("%s/lim_%s_f2b%.0f_m%.0f.txt"%(limdir,model,100.0*f,m),"r")
        for l in fin.readlines():
            if "Observed" in l:
                obs = l.split()[len(l.split())-1]
            elif "Expected  2.5" in l:
                m2s = l.split()[len(l.split())-1]
            elif "Expected 16" in l:
                m1s = l.split()[len(l.split())-1]
            elif "Expected 50" in l:
                exp = l.split()[len(l.split())-1]
            elif "Expected 84" in l:
                p1s = l.split()[len(l.split())-1]
            elif "Expected 97.5" in l:
                p2s = l.split()[len(l.split())-1]
        fin.close()
        if model != "nomodel":
            fout.write("%s,%.0f,%s,%s,%s,%s,%s,%s\n"%(model,m,obs,exp,m2s,m1s,p1s,p2s))
        else:
            fout.write("%.0f,%.2f,%s,%s,%s,%s,%s,%s\n"%(m,f,obs,exp,m2s,m1s,p1s,p2s))

fout.close()
