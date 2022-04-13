#!/usr/bin/env python
"""
Cutflow table information 
"""

__author__ = "Yanxi Gu <yag002@ucsd.edu>"
__auther_m__ = "Luxin Zhang~ mua~ <zlx2016@mail.ustc.edu.cn>"
__copyright__ = "Copyright (c) Yanxi Gu"
__created__ = "[2022-01-26 Fri 01:39]" 

import sys,os,copy
import math
import ROOT 
#from tools import check_outfile_path

#ZZ_Selection = int(sys.argv[1])

def make_table(samplename1, samplename2, samplename3, samplename4, samplename5, samplename6, outname, table_name):
    
    for i in range(6):
        exec ("signal_samplename%s = '../cpp/temp_data/output_' +  samplename%s + '_2018.root'"%(i+1,i+1))
        exec ("signal_sample%s =  ROOT.TFile(signal_samplename%s)"%(i+1,i+1))
        exec ("temp%s = signal_sample%s.Get('cutflow')"%(i+1,i+1))

    for isignal in range(6):
        for i in range(20):
            exec ("signal%s_%s = temp%s.GetBinContent(%s)"%(isignal+1,i+1,isignal+1,i+1))

    fout_script = open(outname,'w')

    print('GYXILU\n')
    print('mua~\n')
    fout_script.write('GYXILU\n')
    fout_script.write('mua$\\tilde$\n')
    fout_script.write('\\begin{table}[]\n')
    fout_script.write('\\begin{tabular}{c|c|c|c|c|c|c}\n')

    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('Cut',samplename1,samplename2,samplename3,samplename4,samplename5,samplename6))

    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('Total 2018',round(signal1_1,2),round(signal2_1,2),round(signal3_1,2),round(signal4_1,2),round(signal5_1,2),round(signal6_1,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('HLT',round(signal1_2,2),round(signal2_2,2),round(signal3_2,2),round(signal4_2,2),round(signal5_2,2),round(signal6_2,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('PV_npvsGood',round(signal1_3,2),round(signal2_3,2),round(signal3_3,2),round(signal4_3,2),round(signal5_3,2),round(signal6_3,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('muon_pt',round(signal1_4,2),round(signal2_4,2),round(signal3_4,2),round(signal4_4,2),round(signal5_4,2),round(signal6_4,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('muon_Iso',round(signal1_5,2),round(signal2_5,2),round(signal3_5,2),round(signal4_5,2),round(signal5_5,2),round(signal6_5,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('muon_trk_glob',round(signal1_6,2),round(signal2_6,2),round(signal3_6,2),round(signal4_6,2),round(signal5_6,2),round(signal6_6,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('muon_id',round(signal1_7,2),round(signal2_7,2),round(signal3_7,2),round(signal4_7,2),round(signal5_7,2),round(signal6_7,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('Mu_matchedToTrig',round(signal1_8,2),round(signal2_8,2),round(signal3_8,2),round(signal4_8,2),round(signal5_8,2),round(signal6_8,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('muon pair',round(signal1_9,2),round(signal2_9,2),round(signal3_9,2),round(signal4_9,2),round(signal5_9,2),round(signal6_9,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('1 or more b tag medium',round(signal1_10,2),round(signal2_10,2),round(signal3_10,2),round(signal4_10,2),round(signal5_10,2),round(signal6_10,2)))
    print("%-30s%-15s%-15s%-15s%-15s%-15s%-15s"%('m_ll > 150 GeV',round(signal1_11,2),round(signal2_11,2),round(signal3_11,2),round(signal4_11,2),round(signal5_11,2),round(signal6_11,2)))
 

    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('Cut',samplename1,samplename2,samplename3,samplename4,samplename5,samplename6,r'\\'))
    fout_script.write('\hline\n')
    fout_script.write('\hline\n')
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('Total 2018',round(signal1_1,2),round(signal2_1,2),round(signal3_1,2),round(signal4_1,2),round(signal5_1,2),round(signal6_1,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('HLT',round(signal1_2,2),round(signal2_2,2),round(signal3_2,2),round(signal4_2,2),round(signal5_2,2),round(signal6_2,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('PV_npvsGood',round(signal1_3,2),round(signal2_3,2),round(signal3_3,2),round(signal4_3,2),round(signal5_3,2),round(signal6_3,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('muon_pt',round(signal1_4,2),round(signal2_4,2),round(signal3_4,2),round(signal4_4,2),round(signal5_4,2),round(signal6_4,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('muon_Iso',round(signal1_5,2),round(signal2_5,2),round(signal3_5,2),round(signal4_5,2),round(signal5_5,2),round(signal6_5,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('muon_trk_glob',round(signal1_6,2),round(signal2_6,2),round(signal3_6,2),round(signal4_6,2),round(signal5_6,2),round(signal6_6,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('muon_id',round(signal1_7,2),round(signal2_7,2),round(signal3_7,2),round(signal4_7,2),round(signal5_7,2),round(signal6_7,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('Mu_matchedToTrig',round(signal1_8,2),round(signal2_8,2),round(signal3_8,2),round(signal4_8,2),round(signal5_8,2),round(signal6_8,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('muon pair',round(signal1_9,2),round(signal2_9,2),round(signal3_9,2),round(signal4_9,2),round(signal5_9,2),round(signal6_9,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('1 or more b tag medium',round(signal1_10,2),round(signal2_10,2),round(signal3_10,2),round(signal4_10,2),round(signal5_10,2),round(signal6_10,2),r'\\'))
    fout_script.write('%-30s&%-15s&%-15s&%-15s&%-15s&%-15s&%-15s%-5s\n'%('m_ll > 150 GeV',round(signal1_11,2),round(signal2_11,2),round(signal3_11,2),round(signal4_11,2),round(signal5_11,2),round(signal6_11,2),r'\\'))

    fout_script.write('\\end{tabular}\n')
    fout_script.write('\\caption{'+table_name+'}\n')
    fout_script.write('\\label{'+table_name+'}\n')
    fout_script.write('~\\\\\n')
    fout_script.write('\\end{table}\n')

    fout_script.close()


Soutname_in = '../tables/cutflow.txt'
Stable_name_in = "cutflow"
make_table("signal", "DY", "WW", "WZ", "ZZ", "ttbar", Soutname_in, Stable_name_in)




