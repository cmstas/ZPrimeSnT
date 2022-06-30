#!/usr/bin/env sh

# url is like https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer19UL18_JRV2_MC/Summer19UL18_JRV2_MC_PtResolution_AK4PFchs.txt

baseurl="https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/"

eras="
Summer20UL16APV_JRV3_MC
Summer20UL16_JRV3_MC
Summer19UL17_JRV2_MC
Summer19UL18_JRV2_MC
"

jettypes="
AK4PFchs
"

corrstrs="
PtResolution
SF
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
