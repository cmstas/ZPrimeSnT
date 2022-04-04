#!/usr/bin/env sh

# url is like https://raw.githubusercontent.com/cms-jet/JECDatabase/master/textFiles/Autumn18_V19_MC/Autumn18_V19_MC_L1FastJet_AK4PFchs.txt

baseurl="https://raw.githubusercontent.com/cms-jet/JECDatabase/master/textFiles/"

eras="
Summer19UL16APV_RunBCDEF_V7_DATA
Summer19UL16_RunFGH_V7_DATA
Summer19UL16APV_V7_MC
Summer19UL16_V7_MC
Summer19UL17_RunB_V5_DATA
Summer19UL17_RunC_V5_DATA
Summer19UL17_RunD_V5_DATA
Summer19UL17_RunE_V5_DATA
Summer19UL17_RunF_V5_DATA
Summer19UL17_V5_MC
Summer19UL18_RunA_V5_DATA
Summer19UL18_RunB_V5_DATA
Summer19UL18_RunC_V5_DATA
Summer19UL18_RunD_V5_DATA
Summer19UL18_V5_MC
"

jettypes="
AK4PFchs
"

corrstrs="
L1FastJet
L1RC
L2L3Residual
L2Relative
L2Residual
L3Absolute
Uncertainty
"

for era in $eras; do
    mkdir -p $era

    cd $era
    for jettype in $jettypes; do
        for corrstr in $corrstrs; do
            echo Executing: curl -s -L "$baseurl/$era/${era}_${corrstr}_${jettype}.txt"
            curl -s -O -L "$baseurl/$era/${era}_${corrstr}_${jettype}.txt"
        done
    done
    cd -
done
