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
        exec ("signal_samplename%s = '../cpp/output_' +  samplename%s + '_2018.root'"%(i+1,i+1))
        exec ("signal_sample%s =  ROOT.TFile(signal_samplename%s)"%(i+1,i+1))
        exec ("temp%s = signal_sample%s.Get('cutflow')"%(i+1,i+1))

    for isignal in range(6):
        for i in range(20):
            exec ("signal%s_%s = temp%s.GetBinContent(%s)"%(isignal+1,i+1,isignal+1,i+1))

    fout_script = open(outname,'w')

    print('GYXILU\n')
    print('mua~\n')
    fout_script.write('GYXILU\n')
    fout_script.write('mua$\sim$\n')
    fout_script.write('\\begin{table}[]\n')
    fout_script.write('\\begin{tabular}{c|c|c|c|c|c|c|c|c|c|c|c|c}\n')

    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('Cut',samplename1,'eff',samplename2,'eff',samplename3,'eff',samplename4,'eff',samplename5,'eff',samplename6,'eff'))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('Total 2018','%.2E'%signal1_1,1,'%.2E'%signal2_1,1,'%.2E'%signal3_1,1,'%.2E'%signal4_1,1,'%.2E'%signal5_1,1,'%.2E'%signal6_1,1))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('HLT','%.2E'%signal1_2,'%.2F'%(signal1_2/signal1_1),'%.2E'%signal2_2,'%.2F'%(signal2_2/signal2_1),'%.2E'%signal3_2,'%.2F'%(signal3_2/signal3_1),'%.2E'%signal4_2,'%.2F'%(signal4_2/signal4_1),'%.2E'%signal5_2,'%.2F'%(signal5_2/signal5_1),'%.2E'%signal6_2,'%.2F'%(signal6_2/signal6_1)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('PV_npvsGood','%.2E'%signal1_3,'%.2F'%(signal1_3/signal1_2),'%.2E'%signal2_3,'%.2F'%(signal2_3/signal2_2),'%.2E'%signal3_3,'%.2F'%(signal3_3/signal3_2),'%.2E'%signal4_3,'%.2F'%(signal4_3/signal4_2),'%.2E'%signal5_3,'%.2F'%(signal5_3/signal5_2),'%.2E'%signal6_3,'%.2F'%(signal6_3/signal6_2)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('muon_pt','%.2E'%signal1_4,'%.2F'%(signal1_4/signal1_3),'%.2E'%signal2_4,'%.2F'%(signal2_4/signal2_3),'%.2E'%signal3_4,'%.2F'%(signal3_4/signal3_3),'%.2E'%signal4_4,'%.2F'%(signal4_4/signal4_3),'%.2E'%signal5_4,'%.2F'%(signal5_4/signal5_3),'%.2E'%signal6_4,'%.2F'%(signal6_4/signal6_3)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('muon_Iso','%.2E'%signal1_5,'%.2F'%(signal1_5/signal1_4),'%.2E'%signal2_5,'%.2F'%(signal2_5/signal2_4),'%.2E'%signal3_5,'%.2F'%(signal3_5/signal3_4),'%.2E'%signal4_5,'%.2F'%(signal4_5/signal4_4),'%.2E'%signal5_5,'%.2F'%(signal5_5/signal5_4),'%.2E'%signal6_5,'%.2F'%(signal6_5/signal6_4)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('muon_trk_glob','%.2E'%signal1_6,'%.2F'%(signal1_6/signal1_5),'%.2E'%signal2_6,'%.2F'%(signal2_6/signal2_5),'%.2E'%signal3_6,'%.2F'%(signal3_6/signal3_5),'%.2E'%signal4_6,'%.2F'%(signal4_6/signal4_5),'%.2E'%signal5_6,'%.2F'%(signal5_6/signal5_5),'%.2E'%signal6_6,'%.2F'%(signal6_6/signal6_5)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('muon_id','%.2E'%signal1_7,'%.2F'%(signal1_7/signal1_6),'%.2E'%signal2_7,'%.2F'%(signal2_7/signal2_6),'%.2E'%signal3_7,'%.2F'%(signal3_7/signal3_6),'%.2E'%signal4_7,'%.2F'%(signal4_7/signal4_6),'%.2E'%signal5_7,'%.2F'%(signal5_7/signal5_6),'%.2E'%signal6_7,'%.2F'%(signal6_7/signal6_6)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('Mu_matchedToTrig','%.2E'%signal1_8,'%.2F'%(signal1_8/signal1_7),'%.2E'%signal2_8,'%.2F'%(signal2_8/signal2_7),'%.2E'%signal3_8,'%.2F'%(signal3_8/signal3_7),'%.2E'%signal4_8,'%.2F'%(signal4_8/signal4_7),'%.2E'%signal5_8,'%.2F'%(signal5_8/signal5_7),'%.2E'%signal6_8,'%.2F'%(signal6_8/signal6_7)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('muon pair','%.2E'%signal1_9,'%.2F'%(signal1_9/signal1_8),'%.2E'%signal2_9,'%.2F'%(signal2_9/signal2_8),'%.2E'%signal3_9,'%.2F'%(signal3_9/signal3_8),'%.2E'%signal4_9,'%.2F'%(signal4_9/signal4_8),'%.2E'%signal5_9,'%.2F'%(signal5_9/signal5_8),'%.2E'%signal6_9,'%.2F'%(signal6_9/signal6_8)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('1 or more b tag medium','%.2E'%signal1_10,'%.2F'%(signal1_10/signal1_9),'%.2E'%signal2_10,'%.2F'%(signal2_10/signal2_9),'%.2E'%signal3_10,'%.2F'%(signal3_10/signal3_9),'%.2E'%signal4_10,'%.2F'%(signal4_10/signal4_9),'%.2E'%signal5_10,'%.2F'%(signal5_10/signal5_9),'%.2E'%signal6_10,'%.2F'%(signal6_10/signal6_9)))
    print("%-25s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s"%('m_ll > 150 GeV','%.2E'%signal1_11,'%.2F'%(signal1_11/signal1_10),'%.2E'%signal2_11,'%.2F'%(signal2_11/signal2_10),'%.2E'%signal3_11,'%.2F'%(signal3_11/signal3_10),'%.2E'%signal4_11,'%.2F'%(signal4_11/signal4_10),'%.2E'%signal5_11,'%.2F'%(signal5_11/signal5_10),'%.2E'%signal6_11,'%.2F'%(signal6_11/signal6_10)))

    fout_script.write('%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n'%('Cut',samplename1,'eff',samplename2,'eff',samplename3,'eff',samplename4,'eff',samplename5,'eff',samplename6,'eff',r'\\'))
    fout_script.write('\hline\n')
    fout_script.write('\hline\n')

    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('Cut',samplename1,'eff',samplename2,'eff',samplename3,'eff',samplename4,'eff',samplename5,'eff',samplename6,'eff',r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('Total 2018','%.2E'%signal1_1,1,'%.2E'%signal2_1,1,'%.2E'%signal3_1,1,'%.2E'%signal4_1,1,'%.2E'%signal5_1,1,'%.2E'%signal6_1,1,r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('HLT','%.2E'%signal1_2,'%.2F'%(signal1_2/signal1_1),'%.2E'%signal2_2,'%.2F'%(signal2_2/signal2_1),'%.2E'%signal3_2,'%.2F'%(signal3_2/signal3_1),'%.2E'%signal4_2,'%.2F'%(signal4_2/signal4_1),'%.2E'%signal5_2,'%.2F'%(signal5_2/signal5_1),'%.2E'%signal6_2,'%.2F'%(signal6_2/signal6_1),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('PV npvsGood','%.2E'%signal1_3,'%.2F'%(signal1_3/signal1_2),'%.2E'%signal2_3,'%.2F'%(signal2_3/signal2_2),'%.2E'%signal3_3,'%.2F'%(signal3_3/signal3_2),'%.2E'%signal4_3,'%.2F'%(signal4_3/signal4_2),'%.2E'%signal5_3,'%.2F'%(signal5_3/signal5_2),'%.2E'%signal6_3,'%.2F'%(signal6_3/signal6_2),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('muon pt','%.2E'%signal1_4,'%.2F'%(signal1_4/signal1_3),'%.2E'%signal2_4,'%.2F'%(signal2_4/signal2_3),'%.2E'%signal3_4,'%.2F'%(signal3_4/signal3_3),'%.2E'%signal4_4,'%.2F'%(signal4_4/signal4_3),'%.2E'%signal5_4,'%.2F'%(signal5_4/signal5_3),'%.2E'%signal6_4,'%.2F'%(signal6_4/signal6_3),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('muon Iso','%.2E'%signal1_5,'%.2F'%(signal1_5/signal1_4),'%.2E'%signal2_5,'%.2F'%(signal2_5/signal2_4),'%.2E'%signal3_5,'%.2F'%(signal3_5/signal3_4),'%.2E'%signal4_5,'%.2F'%(signal4_5/signal4_4),'%.2E'%signal5_5,'%.2F'%(signal5_5/signal5_4),'%.2E'%signal6_5,'%.2F'%(signal6_5/signal6_4),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('muon trk glob','%.2E'%signal1_6,'%.2F'%(signal1_6/signal1_5),'%.2E'%signal2_6,'%.2F'%(signal2_6/signal2_5),'%.2E'%signal3_6,'%.2F'%(signal3_6/signal3_5),'%.2E'%signal4_6,'%.2F'%(signal4_6/signal4_5),'%.2E'%signal5_6,'%.2F'%(signal5_6/signal5_5),'%.2E'%signal6_6,'%.2F'%(signal6_6/signal6_5),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('muon id','%.2E'%signal1_7,'%.2F'%(signal1_7/signal1_6),'%.2E'%signal2_7,'%.2F'%(signal2_7/signal2_6),'%.2E'%signal3_7,'%.2F'%(signal3_7/signal3_6),'%.2E'%signal4_7,'%.2F'%(signal4_7/signal4_6),'%.2E'%signal5_7,'%.2F'%(signal5_7/signal5_6),'%.2E'%signal6_7,'%.2F'%(signal6_7/signal6_6),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('Mu matchedToTrig','%.2E'%signal1_8,'%.2F'%(signal1_8/signal1_7),'%.2E'%signal2_8,'%.2F'%(signal2_8/signal2_7),'%.2E'%signal3_8,'%.2F'%(signal3_8/signal3_7),'%.2E'%signal4_8,'%.2F'%(signal4_8/signal4_7),'%.2E'%signal5_8,'%.2F'%(signal5_8/signal5_7),'%.2E'%signal6_8,'%.2F'%(signal6_8/signal6_7),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('muon pair','%.2E'%signal1_9,'%.2F'%(signal1_9/signal1_8),'%.2E'%signal2_9,'%.2F'%(signal2_9/signal2_8),'%.2E'%signal3_9,'%.2F'%(signal3_9/signal3_8),'%.2E'%signal4_9,'%.2F'%(signal4_9/signal4_8),'%.2E'%signal5_9,'%.2F'%(signal5_9/signal5_8),'%.2E'%signal6_9,'%.2F'%(signal6_9/signal6_8),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('1 or more b tag medium','%.2E'%signal1_10,'%.2F'%(signal1_10/signal1_9),'%.2E'%signal2_10,'%.2F'%(signal2_10/signal2_9),'%.2E'%signal3_10,'%.2F'%(signal3_10/signal3_9),'%.2E'%signal4_10,'%.2F'%(signal4_10/signal4_9),'%.2E'%signal5_10,'%.2F'%(signal5_10/signal5_9),'%.2E'%signal6_10,'%.2F'%(signal6_10/signal6_9),r'\\'))
    fout_script.write("%-25s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s&%-10s%-5s\n"%('m$\_$ll $>$ 150 GeV','%.2E'%signal1_11,'%.2F'%(signal1_11/signal1_10),'%.2E'%signal2_11,'%.2F'%(signal2_11/signal2_10),'%.2E'%signal3_11,'%.2F'%(signal3_11/signal3_10),'%.2E'%signal4_11,'%.2F'%(signal4_11/signal4_10),'%.2E'%signal5_11,'%.2F'%(signal5_11/signal5_10),'%.2E'%signal6_11,'%.2F'%(signal6_11/signal6_10),r'\\'))

    fout_script.write('\\end{tabular}\n')
    fout_script.write('\\caption{'+table_name+'}\n')
    fout_script.write('\\label{'+table_name+'}\n')
    fout_script.write('~\\\\\n')
    fout_script.write('\\end{table}\n')

    fout_script.close()


Soutname_in = '../tables/cutflow.txt'
Stable_name_in = "cutflow"
make_table("signal", "DY", "WW", "WZ", "ZZ", "ttbar", Soutname_in, Stable_name_in)




