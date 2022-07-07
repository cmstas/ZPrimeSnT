import sys,os,copy
import math
import ROOT

def print_header(fout):
    fout.write('#ifndef MUONISOSF_H\n')  
    fout.write('#define MUONISOSF_H\n')  
    fout.write('\n')
    fout.write('#include <map>\n')  
    fout.write('#include <vector>\n')  
    fout.write('#include <iostream>\n')  
    fout.write('#include <TString.h>\n')  
    fout.write('\n')
    fout.write('using namespace std;\n')
    fout.write('\n')
    fout.write('map<TString,map<TString,map<TString,float>>> isosf = { };\n')
    fout.write('map<TString,map<TString,map<TString,float>>> isosfunc = { };\n')
    fout.write('\n')
    tf = ROOT.TFile(indir+"/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root")
    th   = tf.Get("NUM_TightRelTkIso_DEN_HighPtIDandIPCut_abseta_pt").Clone("thist")
    fout.write('constexpr int nptbins_iso = '+str(th.GetNbinsY())+';\n')
    fout.write('constexpr int netabins_iso = '+str(th.GetNbinsX())+';\n')
    fout.write('\n')
    fout.write('float *thresholds_pt_iso = new float[nptbins_iso];\n')
    fout.write('TString *ptbins_iso = new TString[nptbins_iso];\n')
    fout.write('inline void set_ptbins_iso() {\n')
    for b in range(1, th.GetNbinsY()+1):
        fout.write('\tthresholds_pt_iso['+str(b-1)+'] = '+str(th.GetXaxis().GetBinLowEdge(b))+';\n')
        fout.write('\tptbins_iso['+str(b-1)+'] = "pt'+str(b-1)+'";\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('float *thresholds_eta_iso = new float[netabins_iso];\n')
    fout.write('TString *etabins_iso = new TString[netabins_iso];\n')
    fout.write('inline void set_etabins_iso() {\n')
    for b in range(1, th.GetNbinsX()+1):
        fout.write('\tthresholds_eta_iso['+str(b-1)+'] = '+str(th.GetXaxis().GetBinLowEdge(b))+';\n')
        fout.write('\tetabins_iso['+str(b-1)+'] = "eta'+str(b-1)+'";\n')
    tf.Close()
    fout.write('}\n')
    fout.write('\n')

def print_function_h(fout):
    fout.write('TString get_muonIsoSFPtBin(const float pt);\n')
    fout.write('\n')
    fout.write('TString get_muonIsoSFEtaBin(const float abseta);\n')
    fout.write('\n')
    fout.write('float get_muonIsoSF( const float pt, const float eta, const TString year, const TString variation="central" );\n')
    fout.write('\n')
    fout.write('inline void reset_muonIsoSF() {\n')
    fout.write('\n')
    fout.write('\tisosf.clear();\n')
    fout.write('\tisosfunc.clear();\n')
    fout.write('\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('inline void set_muonIsoSF() {\n')
    fout.write('\tset_ptbins_iso();\n')
    fout.write('\tset_etabins_iso();\n')
    fout.write('\n')

def print_footer(fout):
    fout.write('}\n')
    fout.write('\n')
    fout.write('#endif\n')
    
def get_muonIsoSF(fout, year = "2018"):
    
    if not os.path.exists(outdir):
        os.makedirs(outdir)

    tf = ROOT.TFile(indir+"/Efficiencies_muon_generalTracks_Z_Run"+year+"_UL_ISO.root")
    th   = tf.Get("NUM_TightRelTkIso_DEN_HighPtIDandIPCut_abseta_pt").Clone("thist")
    sfname = "isosf"
    uncname = "isosfunc"
    fout.write('\t'+sfname +'.insert({"'+year+'", { }});\n')
    fout.write('\t'+uncname+'.insert({"'+year+'", { }});\n')
    for bx in range(1, th.GetNbinsX()+1):
        fout.write('\t'+sfname +'["'+year+'"].insert({"eta'+str(bx-1)+'", { }});\n')
        fout.write('\t'+uncname+'["'+year+'"].insert({"eta'+str(bx-1)+'", { }});\n')
        for by in range(1, th.GetNbinsY()+1):
            tsf  = th.GetBinContent(bx, by)
            tunc = th.GetBinError  (bx, by)
            fout.write('\t'+sfname +'["'+year+'"]["eta'+str(bx-1)+'"].insert({"pt'+str(by-1)+'", '+str(tsf) +'});\n')
            fout.write('\t'+uncname+'["'+year+'"]["eta'+str(bx-1)+'"].insert({"pt'+str(by-1)+'", '+str(tunc)+'});\n')
    tf.Close()
    fout.write('\n')

def print_cc(fout,fname):
    fout.write('#include "%s.h"\n'%fname)
    fout.write('\n')
    fout.write('TString get_muonIsoSFPtBin(const float pt) {\n')
    fout.write('\tfor ( unsigned int b=nptbins_iso-1; b>=1; b-- ) {\n')
    fout.write('\t\tif ( pt > thresholds_pt_iso[b] ) {\n')
    fout.write('\t\t\treturn ptbins_iso[b];\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\treturn ptbins_iso[0];\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('TString get_muonIsoSFEtaBin(const float abseta) {\n')
    fout.write('\tfor ( unsigned int b=netabins_iso-1; b>=1; b-- ) {\n')
    fout.write('\t\tif ( abseta > thresholds_eta_iso[b] ) {\n')
    fout.write('\t\t\treturn etabins_iso[b];\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\treturn etabins_iso[0];\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('float get_muonIsoSF( const float pt, const float eta, const TString year, const TString variation ) {\n')
    fout.write('\tif ( year!="2016nonAPV" && year!="2016APV" && year!="2017" && year!="2018" ) {\n')
    fout.write('\t\tstd::cout << "WARNING: unknown year, returning unity muon RECO SF!" << std::endl;\n')
    fout.write('\t\treturn 1.0;\n')
    fout.write('\t}\n')
    fout.write('\tif ( pt < 10.0 || fabs(eta) > 2.4 ) return 1.0;\n')
    fout.write('\telse {\n')
    fout.write('\t\tTString etabin = get_muonIsoSFEtaBin(fabs(eta));\n')
    fout.write('\t\tTString ptbin = get_muonIsoSFPtBin(pt);\n')
    fout.write('\t\tif ( variation == "central" ) return isosf[year][etabin][ptbin];\n')
    fout.write('\t\telse if ( variation == "up" ) return isosf[year][etabin][ptbin]+isosfunc[year][etabin][ptbin];\n')
    fout.write('\t\telse if ( variation == "down" ) return isosf[year][etabin][ptbin]-isosfunc[year][etabin][ptbin];\n')
    fout.write('\t\telse {\n')
    fout.write('\t\t\tstd::cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << std::endl;\n')
    fout.write('\t\t\treturn 1.0;\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('}\n')

indir = "./data/"
outdir="./NanoCORE/Tools/"
fname = "muonIsoSF"

fcc = open(outdir+"/"+fname+".cc",'w')
print_cc(fcc, fname)

fheader = open(outdir+"/"+fname+".h",'w')
print_header(fheader)
print_function_h(fheader)

for year in ["2016nonAPV","2016APV","2017","2018"]:
    get_muonIsoSF(fheader, year)

print_footer(fheader)
