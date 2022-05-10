import sys,os,copy
import math
import ROOT

def print_header(fout):
    fout.write('#ifndef MUONIDSF_H\n')  
    fout.write('#define MUONIDSF_H\n')  
    fout.write('\n')
    fout.write('#include <map>\n')  
    fout.write('#include <vector>\n')  
    fout.write('#include <iostream>\n')  
    fout.write('#include <TString.h>\n')  
    fout.write('\n')
    fout.write('using namespace std;\n')
    fout.write('\n')
    fout.write('map<TString,map<TString,map<TString,float>>> idsf = { };\n')
    fout.write('map<TString,map<TString,map<TString,float>>> idsfunc = { };\n')
    fout.write('\n')

def print_function_h(fout):
    fout.write('TString get_muonIDSFPtBin(const float pt);\n')
    fout.write('\n')
    fout.write('TString get_muonIDSFEtaBin(const float abseta);\n')
    fout.write('\n')
    fout.write('float get_muonIDSF( const float pt, const float eta, const TString year, const TString variation="central" );\n')
    fout.write('\n')
    fout.write('inline void reset_muonIDSF() {\n')
    fout.write('\n')
    fout.write('\tidsf.clear();\n')
    fout.write('\tidsfunc.clear();\n')
    fout.write('\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('inline void set_muonIDSF() {\n')

def print_footer(fout):
    fout.write('}\n')
    fout.write('\n')
    fout.write('#endif\n')
    
def get_muonIDSF(fout, year = "2018"):
    
    if not os.path.exists(outdir):
        os.makedirs(outdir)

    tf = ROOT.TFile(indir+"/Efficiencies_muon_generalTracks_Z_Run"+year+"_UL_ID.root")
    th   = tf.Get("NUM_HighPtID_DEN_TrackerMuons_abseta_pt").Clone("thist")
    sfname = "idsf"
    uncname = "idsfunc"
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
    fout.write('TString get_muonIDSFPtBin(const float pt) {\n')
    fout.write('\tvector<float> thresholds;\n')
    fout.write('\tvector<TString> ptbins;\n')
    tf = ROOT.TFile(indir+"/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root")
    th   = tf.Get("NUM_HighPtID_DEN_TrackerMuons_abseta_pt").Clone("thist")
    for b in range(1, th.GetNbinsY()+1):
        fout.write('\tthresholds.push_back('+str(th.GetYaxis().GetBinLowEdge(b))+');\n')
        fout.write('\tptbins.push_back("pt'+str(b-1)+'");\n')
    tf.Close()
    fout.write('\tfor ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {\n')
    fout.write('\t\tif ( pt > thresholds.at(b) ) {\n')
    fout.write('\t\t\treturn ptbins.at(b);\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\treturn ptbins.at(0);\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('TString get_muonIDSFEtaBin(const float abseta) {\n')
    fout.write('\tvector<float> thresholds;\n')
    fout.write('\tvector<TString> etabins;\n')
    tf = ROOT.TFile(indir+"/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root")
    th   = tf.Get("NUM_HighPtID_DEN_TrackerMuons_abseta_pt").Clone("thist")
    for b in range(1, th.GetNbinsX()+1):
        fout.write('\tthresholds.push_back('+str(th.GetXaxis().GetBinLowEdge(b))+');\n')
        fout.write('\tetabins.push_back("eta'+str(b-1)+'");\n')
    tf.Close()
    fout.write('\tfor ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {\n')
    fout.write('\t\tif ( abseta > thresholds.at(b) ) {\n')
    fout.write('\t\t\treturn etabins.at(b);\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('\treturn etabins.at(0);\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('float get_muonIDSF( const float pt, const float eta, const TString year, const TString variation ) {\n')
    fout.write('\tif ( year!="2016nonAPV" && year!="2016APV" && year!="2017" && year!="2018" ) {\n')
    fout.write('\t\tstd::cout << "WARNING: unknown year, returning unity muon RECO SF!" << std::endl;\n')
    fout.write('\t\treturn 1.0;\n')
    fout.write('\t}\n')
    fout.write('\tif ( pt < 10.0 || fabs(eta) > 2.4 ) return 1.0;\n')
    fout.write('\telse {\n')
    fout.write('\t\tTString etabin = get_muonIDSFEtaBin(fabs(eta));\n')
    fout.write('\t\tTString ptbin = get_muonIDSFPtBin(pt);\n')
    fout.write('\t\tif ( variation == "central" ) return idsf[year][etabin][ptbin];\n')
    fout.write('\t\telse if ( variation == "up" ) return idsf[year][etabin][ptbin]+idsfunc[year][etabin][ptbin];\n')
    fout.write('\t\telse if ( variation == "down" ) return idsf[year][etabin][ptbin]-idsfunc[year][etabin][ptbin];\n')
    fout.write('\t\telse {\n')
    fout.write('\t\t\tstd::cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << std::endl;\n')
    fout.write('\t\t\treturn 1.0;\n')
    fout.write('\t\t}\n')
    fout.write('\t}\n')
    fout.write('}\n')

indir = "./data/"
outdir="./NanoCORE/Tools/"
fname = "muonIDSF"

fcc = open(outdir+"/"+fname+".cc",'w')
print_cc(fcc, fname)

fheader = open(outdir+"/"+fname+".h",'w')
print_header(fheader)
print_function_h(fheader)

for year in ["2016nonAPV","2016APV","2017","2018"]:
    get_muonIDSF(fheader, year)

print_footer(fheader)
