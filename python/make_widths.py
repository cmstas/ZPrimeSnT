import os,sys
import compute_width

def print_header(fout):
    fout.write('#ifndef WIDTHS_H\n')  
    fout.write('#define WIDTHS_H\n')  
    fout.write('\n')
    fout.write('#include <map>\n')  
    fout.write('#include <vector>\n')  
    fout.write('#include <iostream>\n')  
    fout.write('#include <TString.h>\n')  
    fout.write('\n')
    fout.write('using namespace std;\n')
    fout.write('\n')
    fout.write('map<TString,map<TString,float>> widths = { };\n')
    fout.write('\n')
    fout.write('inline void reset_widths() {\n')
    fout.write('\twidths.clear();\n')
    fout.write('}\n')
    fout.write('inline void set_widths() {\n')

def print_footer(fout):
    fout.write('}\n')
    fout.write('\n')
    fout.write('#endif\n')

models = ["Y3", "DY3", "DYp3", "B3mL2"]
masses = [100.0, 200.0, 400.0, 700.0, 1000.0, 1500.0, 2000.0]
#gx["Y3"] = 0.14
#gx["DY3"] = 0.14
#gx["DYp3"] = 0.08
#gx["B3mL2"] = 0.05
#t23["Y3"] = -0.15
#t23["DY3"] = -0.18
#t23["DYp3"] = 0.13
#t23["B3mL2"] = 0.1

outdir="./NanoCORE/Tools/"
fname = "widths"
fheader = open(outdir+"/"+fname+".h",'w')
print_header(fheader)
gx = dict()
t23 = dict()
widths = dict()
for m in models:
    tm = m
    if m=="B3mL2":
        tm="B3-L2"
    fheader.write('\twidths.insert({"%s", {}});\n'%m)
    gx[m],t23[m] = compute_width.get_model_reference_pars(tm)
    widths[m] = dict()
    for mm in masses:
        widths[m]["%.0f"%mm] = compute_width.calculate_width(mm, gx[m], t23[m], tm, 'Zp', False)
        fheader.write('\twidths["%s"].insert({"%.0f", %f});\n'%(m,mm,widths[m]["%.0f"%mm]))
print_footer(fheader)
