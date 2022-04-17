import sys,os,copy
import math
import ROOT 

def make_table(samples, indir = "./cpp/temp_data/", year = "2018", outdir="tables/"):
    
    if not os.path.exists(outdir):
        os.makedirs(outdir)

    nCuts = 0
    yields = []
    effs   = []
    labels = []
    for i in range(len(samples)):
        yields.append([])
        effs  .append([])
        subsamples = []
        if samples[i]=='DY':
            subsamples = ['ZToMuMu_50_120',
                          'ZToMuMu_120_200',
                          'ZToMuMu_200_400',
                          'ZToMuMu_400_800',
                          'ZToMuMu_800_1400',
                          'ZToMuMu_1400_2300',
                          'ZToMuMu_2300_3500',
                          'ZToMuMu_3500_4500',
                          'ZToMuMu_4500_6000',
                          'ZToMuMu_6000_Inf']
        elif samples[i]=='VV':
            subsamples = ['WW','WZ','ZZ']
        elif samples[i]=='tW':
            subsamples = ['tW','tbarW']
        elif samples[i]=='ttX':
            subsamples = ['TTW','TTZ','TTHToNonbb']
        else: 
            subsamples.append(samples[i])

        for ii in range(len(subsamples)):
            tfile = ROOT.TFile(indir+"/output_"+subsamples[ii]+"_"+year+".root") 
            thist = tfile.Get("cutflow").Clone(subsamples[ii])
            
            if i==0 and ii==0:
                nCuts = thist.GetNbinsX()
                for b in range(1, nCuts+1):
                    if thist.GetXaxis().GetBinLabel(b)=="":
                        nCuts = nCuts-1
                        continue
                    else:
                        labels.append(thist.GetXaxis().GetBinLabel(b))

            for b in range(1, nCuts+1):
                if ii==0:
                    yields[i].append(thist.GetBinContent(b))
                else:
                    yields[i][b-1] = yields[i][b-1]+thist.GetBinContent(b)

        for b in range(1, nCuts+1):
            if yields[i][0]>0.0:
                effs[i].append(yields[i][b-1]/yields[i][0])
            else:
                effs[i].append(0.0)

    fout = open(outdir+"/cutflow_"+year+".tex",'w')
    
    fout.write('\\documentclass{article}\n')
    fout.write('\\usepackage{adjustbox}\n')
    fout.write('\\begin{document}\n')
    fout.write('\\begin{table*}[h]\n')
    fout.write('\\footnotesize\n')
    fout.write('\\begin{adjustbox}{width=\\textwidth}\n')
    fout.write('\\begin{tabular}{|l')
    for i in range(len(samples)):
        # Add one cell for absolute yield and one cell for efficiency
        fout.write('|c|c')
    fout.write('|}\n')
    fout.write('Selection ')
    for i in range(len(samples)):
        fout.write('& \multicolumn{2}{|c|}{'+samples[i].replace("_"," ")+'}')
    fout.write('\\\\\n')
    for i in range(len(samples)):
        fout.write('& Yield & Eff. (\%)')
    fout.write('\\\\\n')
    fout.write('\\hline\n')

    for c in range(nCuts):
        tlabel = labels[c]
        tlabel = tlabel.replace("pT","$p_{\\mathrm{T}}$")
        tlabel = tlabel.replace("pT","$p_{\\mathrm{T}}$")
        tlabel = tlabel.replace(">","$>$")
        tlabel = tlabel.replace("<","$<$")
        tlabel = tlabel.replace("$$","$ $")
        fout.write(tlabel)
        for i in range(len(samples)):
            fout.write('& %.3E & %.2f'%(yields[i][c],100.0*effs[i][c]))
        fout.write('\\\\\n')
    
    fout.write('\\end{tabular}\n')
    fout.write('\\end{adjustbox}\n')
    fout.write('\\end{table*}\n')
    fout.write('\\end{document}\n')

    fout.close()

samples=['ttbar','tW','ttX','DY','VV']
samples=samples+['Y3_M200','Y3_M400','Y3_M700','Y3_M1000','Y3_M1500','Y3_M2000']
make_table(samples)
