#!/usr/bin/env python3
# coding: utf-8
#--------------------------------------------------------------
# Read a file of yields from Manos and a file of cross-sections
# from Ulascan.
# Aggregate all the information on a csv file.
# The csv file has exactly the same information at the yileds file
# with the following information added on:
# - xsections
# - acceptances
# - widths
# - a numerical "model flag" to complement the "model string"
# Can also output a root tree with the exact same information
# as the csv file, except that the "model string" is removed
# because uproot does not handle that gracefully.  (Ask Pivarski).
#
# In addition, outputs a pdf with plots of acceptance and xsection
#
# To see what parameters can be set
# ./Aggregate.py --help
#
# Claudio 28-Jul-2022
# Protect against missing uproot 1-Aug-2022
#---------------------------------------------------

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from compute_width import calculate_width
from matplotlib.backends.backend_pdf import PdfPages
import argparse

uprootLoaded = True
try:
    import uproot
except:
    uprootLoaded = False
    print(" ")
    print("Cannot import uproot")
    print("The root file will not be made")
    print(" ")

######################## Various initializations ##############

# Parameters and their default values
lumi = 137.6  # luminosity in invfb
yieldFile = "./yieldFileAllYears_AfterSel.txt"
xsecFile  = "./xsec_collected.csv"
makePlots = True
makeCSV   = True
makeROOT  = True
outCSV    = "./MCdefaults.csv"
outROOT   = "./MCdefaults.root"
outPLOT   = "./plots.pdf"

# Define the arguments
description = "Aggregate yields + xsec files.  Output root/csv with also efficiencies and widths"
parser =  argparse.ArgumentParser(description=description)
parser.add_argument('-l','--lumi',
                    help='Luminosity in invfb.          Default = '+str(lumi),
                    type=float, default=lumi)
parser.add_argument('-yf','--yieldFile',
                    help='yields file.                   Default = '+yieldFile,
                    type=str, default=yieldFile)
parser.add_argument('-xf','--xsecFile',
                    help='cross section file.            Default = '+xsecFile,
                    type=str, default=xsecFile)
parser.add_argument('-mpdf','--makePdf',
                    help='make pdf file with plots.      Default = '+str(makePlots),
                    choices=('True','False'), default=str(makePlots))
parser.add_argument('-mcsv','--makeCSV',
                    help='make aggregated csv file.      Default = '+str(makeCSV),
                    choices=('True','False'), default=str(makeCSV))
parser.add_argument('-mroo','--makeROOT',
                    help='make aggregated root file.     Default = '+str(makeROOT),
                    choices=('True','False'), default=str(makeROOT))
parser.add_argument('-cf','--csvFile',
                    help='Output aggregated csv file.    Default = '+str(outCSV),
                    type=str, default=outCSV)
parser.add_argument('-rf','--rootFile',
                    help='Output aggregated root file.   Default = '+str(outROOT),
                    type=str, default=outROOT)
parser.add_argument('-pf','--pdfFile',
                    help='Output pdf file with plots .   Default = '+str(outPLOT),
                    type=str, default=outPLOT)

# This is a dictionary containing the arguments
args = vars(parser.parse_args())

# Tell the users what they are running with
print("  ")
print("Executing Aggregate.py with following parameters:")
for key, value in args.items():
    print(key, ' = ', value)

# Extract the arguments.
# I could have used the args directly but this code migrated
# from jupyter where the args did not exist.  Sigh.
lumi      = args['lumi']
yieldFile = args['yieldFile']
xsecFile  = args['xsecFile']
makePlots = (args['makePdf'] == "True")
makeCSV   = (args['makeCSV']   == "True")
makeROOT  = (args['makeROOT']  == "True")
outCSV    = args['csvFile']
outROOT   = args['rootFile']
outPLOT   = args['pdfFile']

# Some debug output
debug=False
if (debug):
    print(' ')
    print('lumi      = ', lumi)
    print('yieldFile =', yieldFile)
    print('xsecFile  =', yieldFile)
    print('outCSV    = ', outCSV)
    print('outROOT   = ', outROOT)
    print('outPLOT   = ', outPLOT)
    print('makePlots = ', makePlots)
    print('makeCSV   = ', makeCSV)
    print('makeROOT  = ', makeROOT)

############# Initalizations are now done ################

# Read various files into pandas data frames
# The yields from Manos
yields = pd.read_csv(yieldFile)
# The cross sections in fb from Ulascan
xsec   = pd.read_csv(xsecFile)

# Manos did not run on the Mass=100 GeV samples,
# but Ulascan provided the cross-sections for M=100 also.
# So remove the 100 GeV xsec information
xsec  = xsec.loc[xsec['mass'] != 100]

# Rename the column "g/M" to "x" (better for ROOT later)
yields.columns = ['x' if xx=='g/M' else xx for xx in yields.columns]

# Next rename Ulascan csv columns like the old ones
xsec.columns = ['M'        if xx=='mass'       else xx for xx in xsec.columns]
xsec.columns = ['sigma'    if xx=='xsec_total' else xx for xx in xsec.columns]
xsec.columns = ['sigma_ss' if xx=='xsec_ss'    else xx for xx in xsec.columns]
xsec.columns = ['sigma_sb' if xx=='xsec_sb'    else xx for xx in xsec.columns]
xsec.columns = ['sigma_bb' if xx=='xsec_bb'    else xx for xx in xsec.columns]

# sort all pandas so that they are "lined" up
yields.sort_values(by=['model','M'], inplace=True)
xsec.sort_values(by=['model','M'], inplace=True)
yields.reset_index(inplace=True)
xsec.reset_index(inplace=True)

# make sure that they are lined up
if not yields['model'].equals(xsec['model']):
    print("yields and xsec models not lined up")
    exit()
if not yields['M'].equals(xsec['M']):
    print("yields and xsec masses not lined up")
    exit()

# if the fracXX columns do no exist, add them
if not 'fracss' in xsec.columns:
    xsec['fracss'] = xsec['sigma_ss']/xsec['sigma']
if not 'fracsb' in xsec.columns:
    xsec['fracsb'] = xsec['sigma_sb']/xsec['sigma']
if not 'fracbb' in xsec.columns:
    xsec['fracbb'] = xsec['sigma_bb']/xsec['sigma']


# add xsec-related columns to yields dataframe
c_to_add = ['sigma', 'sigma_ss', 'sigma_sb', 'sigma_bb', 'fracss', 'fracsb', 'fracbb']
for c in c_to_add:
    col = xsec[c]
    yields = yields.join(col)

# add gX column to yields data frame (remember GeV vs TeV)
yields['gX'] = yields['x'] * yields['M'] / 1000.

# Calculate the widths and add them to the yields dataframe
M     = (yields['M'].to_numpy()).copy()
gX    = (yields['gX'].to_numpy()).copy()
x     = (yields['x'].to_numpy()).copy()
t23   = (yields['t23'].to_numpy()).copy()
model = (yields['model'].to_list()).copy()

# calculate width, stick it in the yields pandas
width   = []
mmwidth = []
for thisM, thisX, thist23, thismodel in zip(M, x, t23, model):
    out   = calculate_width(thisM, thisX, thist23, thismodel,'Zp', False)
    mmout = calculate_width(thisM, thisX, thist23, thismodel,'mu-mu+', False)
    if abs(out.imag) > 1e-4:
        print("width = ", out)
    if abs(mmout.imag) > 1e-4:
        print("mm width = ", mmout)
    width.append(out.real)
    mmwidth.append(mmout.real)
yields['width']   = width
yields['mmwidth'] = mmwidth


# add a column "imodel" to be a numerical match to "model"
imodel = []
for mdl in model:
    if mdl == "B3mL2":
        imodel.append(1)
    elif mdl == "DY3":
        imodel.append(2)
    elif mdl == "DYp3":
        imodel.append(3)
    elif mdl == "Y3":
        imodel.append(4)
    else:
        print("Found an unknown model.  Quitting now.")
        exit()
yields['imodel'] = imodel

# do some reordering of columns
column_imodel = yields.pop("imodel")
column_gX     = yields.pop('gX')
column_sigma  = yields.pop('sigma')
column_sigma_ss  = yields.pop('sigma_ss')
column_sigma_sb  = yields.pop('sigma_sb')
column_sigma_bb  = yields.pop('sigma_bb')
column_fracss = yields.pop('fracss')
column_fracsb = yields.pop('fracsb')
column_fracbb = yields.pop('fracbb')
column_width  = yields.pop('width')
column_mmwidth = yields.pop('mmwidth')
yields.insert(1, 'imodel', column_imodel)
yields.insert(5, 'gX', column_gX)
yields.insert(6, 'sigma', column_sigma)
yields.insert(7, 'sigma_ss', column_sigma_ss)
yields.insert(8, 'sigma_sb', column_sigma_sb)
yields.insert(9, 'sigma_bb', column_sigma_bb)
yields.insert(10, 'fracss', column_fracss)
yields.insert(11, 'fracsb', column_fracsb)
yields.insert(12, 'fracbb', column_fracbb)
yields.insert(13, 'width', column_width)
yields.insert(14, 'mmwidth', column_mmwidth)

# The change of name of the dataframe is "historical"
df = yields

# Add acceptances to data frame
acc1bb  = (1./lumi) * df['N1bb_w'] / df['sigma_bb']
acc2bb  = (1./lumi) * df['N2bb_w'] / df['sigma_bb']
acc1bs  = (1./lumi) * df['N1bs_w'] / df['sigma_sb']
acc2bs  = (1./lumi) * df['N2bs_w'] / df['sigma_sb']
acc1ss  = (1./lumi) * df['N1ss_w'] / df['sigma_ss']
acc2ss  = (1./lumi) * df['N2ss_w'] / df['sigma_ss']
acc1ss.replace(np.NaN, 0, inplace=True)
acc1ss.replace(np.inf, 0, inplace=True)
acc2ss.replace(np.NaN, 0, inplace=True)
acc2ss.replace(np.inf, 0, inplace=True)
df = df.assign(acc1bb = acc1bb)
df = df.assign(acc2bb = acc2bb)
df = df.assign(acc1bs = acc1bs)
df = df.assign(acc2bs = acc2bs)
df = df.assign(acc1ss = acc1ss)
df = df.assign(acc2ss = acc2ss)

# Add acceptance uncertainties to data frame
acc1bb_e = acc1bb * (df['N1bb_r']**(-1/2))
acc2bb_e = acc2bb * (df['N2bb_r']**(-1/2))
acc1bs_e = acc1bs * (df['N1bs_r']**(-1/2))
acc2bs_e = acc2bs * (df['N2bs_r']**(-1/2))
acc1ss_e = acc1ss * (df['N1ss_r']**(-1/2))
acc2ss_e = acc2ss * (df['N2ss_r']**(-1/2))
acc1ss_e.replace(np.NaN, 0, inplace=True)
acc1ss_e.replace(np.inf, 0, inplace=True)
acc2ss_e.replace(np.NaN, 0, inplace=True)
acc2ss_e.replace(np.inf, 0, inplace=True)
df = df.assign(acc1bb_e = acc1bb_e)
df = df.assign(acc2bb_e = acc2bb_e)
df = df.assign(acc1bs_e = acc1bs_e)
df = df.assign(acc2bs_e = acc2bs_e)
df = df.assign(acc1ss_e = acc1ss_e)
df = df.assign(acc2ss_e = acc2ss_e)

# Add columns with reweighting factors which in this case are 1.0
df['ssWeight'] = 1.0
df['sbWeight'] = 1.0
df['bbWeight'] = 1.0
# The float types below is for making the root file when weights=1 (may not need)
df = df.astype({'ssWeight':'float','sbWeight':'float', 'bbWeight' : 'float'})

# Separate dataframes by model for plotting purposes
df0    = df.loc[(df['model']=='B3mL2')]
df1    = df.loc[(df['model']=='DY3')]
df2    = df.loc[(df['model']=='DYp3')]
df3    = df.loc[(df['model']=='Y3')]
mod    = ['B3mL2', 'DY3', 'DYp3', 'Y3']
frames = [df0, df1, df2, df3]

# Plot the acceptances
if makePlots:
    figure1 = plt.figure(figsize=(12,8))

    acc = ['acc1bb', 'acc1bs', 'acc1ss', 'acc2bb', 'acc2bs', 'acc2ss']
    SR  = ['= 1b from bb', '= 1b from sb', '= 1b from ss', '> 1b from bb', '> 1b from sb',  '> 1b from ss',]
    mrk = ['o', 's', 'd', 'p']
    i = 0
    for a,s in zip(acc,SR):
        i = i + 1
        e = a + "_e"
        ax = plt.subplot(2,3,i)
        for m,f,mark in zip(mod,frames,mrk):
            ax.errorbar(f['M'], 100*f[a], yerr=100*f[e], label=m, marker=mark)
        ax.legend(fontsize='x-large')
        ax.grid()
        ax.set_ylim(bottom=0)
        ax.set_xlabel("Mass (GeV)", fontsize='x-large')
        ax.set_ylabel("Acceptance in percent", fontsize='x-large')
        ax.set_title(s)
    plt.tight_layout()
    # plt.savefig(outPLOT, format="pdf", bbox_inches="tight")
    # pdf.savefig()

# Also plot the cross sections
if makePlots:
    figure2 = plt.figure(figsize=(12,4))
    xsec  = ['bb x-section (fb)', 'bs x-sec (fb)', 'ss x-sec (fb)']
    mrk = ['o', 's', 'd', 'p']
    i = 0
    for x in xsec:
        i  = i + 1
        ax = plt.subplot(1,3,i)
        for m,f,mark in zip(mod,frames,mrk):
            if i == 1:
                ax.plot(f['M'], f['sigma_bb'], label=m, marker=mark)
            elif i==2:
                ax.plot(f['M'], f['sigma_sb'], label=m, marker=mark)
            else:
                ax.plot(f['M'], f['sigma_ss'], label=m, marker=mark)
        ax.legend(fontsize='x-large')
        ax.grid()
        # ax.set_ylim(bottom=0)
        ax.set_xlabel("Mass (GeV)", fontsize='x-large')
        ax.set_ylabel(x, fontsize='x-large')
        ax.set_yscale('log')
    plt.tight_layout()
    # plt.savefig(outPLOT, format="pdf", bbox_inches="tight")
    # pdf.savefig()
    # plt.close()

# Save the figures to the file
if makePlots:
    pdf = PdfPages(outPLOT)
    pdf.savefig(figure1)
    pdf.savefig(figure2)
    pdf.close()

# make csv
if makeCSV:
    df.drop('index', axis='columns', inplace=True)
    df.to_csv(outCSV, index=False)

# make root
# remove the model column in string format before shipping it to root
if makeROOT and uprootLoaded:
    new_df = df.drop("model", axis=1)
    with uproot.recreate(outROOT) as rootfile:
        rootfile["tree"] = new_df
