import sys,os,copy
import math
import ROOT 

def print_header(fout):
    fout.write('#ifndef PUWEIGHT_H\n')  
    fout.write('#define PUWEIGHT_H\n')  
    fout.write('\n')
    fout.write('#include <iostream>\n')  
    fout.write('#include <TString.h>\n')  
    fout.write('\n')
    fout.write('#define nPUbins 99\n')  
    fout.write('\n')
    fout.write('using namespace std;\n')
    fout.write('\n')
    fout.write('double *puweight_central_2016nonAPV = new double[nPUbins];\n')
    fout.write('double *puweight_central_2016APV = new double[nPUbins];\n')
    fout.write('double *puweight_central_2017 = new double[nPUbins];\n')
    fout.write('double *puweight_central_2018 = new double[nPUbins];\n')
    fout.write('double *puweight_central_2018B = new double[nPUbins];\n')
    fout.write('double *puweight_up_2016nonAPV = new double[nPUbins];\n')
    fout.write('double *puweight_up_2016APV = new double[nPUbins];\n')
    fout.write('double *puweight_up_2017 = new double[nPUbins];\n')
    fout.write('double *puweight_up_2018 = new double[nPUbins];\n')
    fout.write('double *puweight_up_2018B = new double[nPUbins];\n')
    fout.write('double *puweight_down_2016nonAPV = new double[nPUbins];\n')
    fout.write('double *puweight_down_2016APV = new double[nPUbins];\n')
    fout.write('double *puweight_down_2017 = new double[nPUbins];\n')
    fout.write('double *puweight_down_2018 = new double[nPUbins];\n')
    fout.write('double *puweight_down_2018B = new double[nPUbins];\n')
    fout.write('\n')

def print_function_h(fout):
    fout.write('double get_puWeight(const unsigned int nTrueInt, const TString year, const TString var);\n')
    fout.write('\n')
    fout.write('inline void set_puWeights() {\n')

def print_footer(fout):
    fout.write('}\n')
    fout.write('\n')
    fout.write('#endif\n')

def print_cc(fout,fname):
    fout.write('#include "%s.h"\n'%fname)  
    fout.write('\n')
    fout.write('double get_puWeight(const unsigned int nTrueInt, const TString year, const TString var="central")\n')
    fout.write('{\n')
    fout.write('\tunsigned int npu = nTrueInt;\n')
    fout.write('\tif ( npu < 0 ) npu = 0;\n')
    fout.write('\tif ( npu >= nPUbins ) npu = nPUbins-1;\n')
    fout.write('\tif ( var=="central" ) {\n')
    fout.write('\t\tif ( year=="2016nonAPV" ) return puweight_central_2016nonAPV[npu];\n')
    fout.write('\t\telse if ( year=="2016APV" ) return puweight_central_2016APV[npu];\n')
    fout.write('\t\telse if ( year=="2017" ) return puweight_central_2017[npu];\n')
    fout.write('\t\telse if ( year=="2018" ) return puweight_central_2018[npu];\n')
    fout.write('\t\telse if ( year=="2018B" ) return puweight_central_2018B[npu];\n')
    fout.write('\t\telse {\n')
    fout.write('\t\t\tstd::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;\n')
    fout.write('\t\t\treturn 1.0;\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\telse if ( var=="up" ) {\n')
    fout.write('\t\tif ( year=="2016nonAPV" ) return puweight_up_2016nonAPV[npu];\n')
    fout.write('\t\telse if ( year=="2016APV" ) return puweight_up_2016APV[npu];\n')
    fout.write('\t\telse if ( year=="2017" ) return puweight_up_2017[npu];\n')
    fout.write('\t\telse if ( year=="2018" ) return puweight_up_2018[npu];\n')
    fout.write('\t\telse if ( year=="2018B" ) return puweight_up_2018B[npu];\n')
    fout.write('\t\telse {\n')
    fout.write('\t\t\tstd::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;\n')
    fout.write('\t\t\treturn 1.0;\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\telse if ( var=="down" ) {\n')
    fout.write('\t\tif ( year=="2016nonAPV" ) return puweight_down_2016nonAPV[npu];\n')
    fout.write('\t\telse if ( year=="2016APV" ) return puweight_down_2016APV[npu];\n')
    fout.write('\t\telse if ( year=="2017" ) return puweight_down_2017[npu];\n')
    fout.write('\t\telse if ( year=="2018" ) return puweight_down_2018[npu];\n')
    fout.write('\t\telse if ( year=="2018B" ) return puweight_down_2018B[npu];\n')
    fout.write('\t\telse {\n')
    fout.write('\t\t\tstd::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;\n')
    fout.write('\t\t\treturn 1.0;\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\telse {\n')
    fout.write('\t\tstd::cout << "WARNING: unknown variation (central, up, down), returning unity piluep weight!" << std::endl;\n')
    fout.write('\t\treturn 1.0;\n')
    fout.write('\t}\n')
    fout.write('}\n')

def get_weights(fout, year = "2018", var = "central", mcsample="ttbar"):

    if not os.path.exists(outdir):
        os.makedirs(outdir)

    ymc = year
    if year == "2018B":
        ymc = "2018"
    fmc = ROOT.TFile(indir+"/PileupHistogram_"+mcsample+"_"+ymc+".root")
    hmc   = fmc.Get("pileup").Clone(mcsample);
    hmc.Scale(1.0/hmc.Integral(0,-1))
    hdata = ROOT.TH1D()
    ydata = year
    if year == "2016nonAPV":
        ydata = "2016-postVFP"
    elif year == "2016APV":
        ydata = "2016-preVFP"
    xsec = "69200ub"
    if var == "up":
        xsec = "72400ub"
    elif var == "down":
        xsec = "66000ub"
    fdata= ROOT.TFile(indir+"/PileupHistogram-goldenJSON-13tev"+"-"+ydata+"-"+xsec+"-99bins.root") 
    hdata = fdata.Get("pileup").Clone("data")
    hdata.Scale(1.0/hdata.Integral(0,-1))
    hdata.Divide(hmc)
    
    wname = "puweight_"+var+"_"+year

    for b in range(1, hdata.GetNbinsX()+1):
        tw = hdata.GetBinContent(b);
        fout.write("\t"+wname+"["+str(b-1)+"] = "+str(tw)+";\n")
    fout.write("\n")

indir = "./data/"
outdir="./NanoCORE/Tools/"
fname = "puWeight"

fcc = open(outdir+"/"+fname+".cc",'w')
print_cc(fcc, fname)

fheader = open(outdir+"/"+fname+".h",'w')
print_header(fheader)
print_function_h(fheader)

for year in ["2016nonAPV","2016APV","2017","2018","2018B"]:
    for var in ["central","up","down"]:
        get_weights(fheader, year, var, mcsample="ttbar")

print_footer(fheader)
