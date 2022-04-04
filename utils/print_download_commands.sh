#!/usr/bin/env bash

function print_commands {
    dsname=$1
    nicename=$(echo $dsname | cut -d '/' -f2-3 | sed 's|\/|__|g')
    files=$(./dis_client.py -t files -d "$dsname | grep name")
    for f in $files ; do
        tailname=$(echo $f | rev | cut -d '/' -f1 | rev)
        echo xrdcp root://cmsxrootd.fnal.gov/$f root://redirector.t2.ucsd.edu//store/group/snt/nanoaod/$nicename/$tailname
    done
}

# ./print_download_commands.sh > commands.txt
# ./parallel --nice 10 --jobs 10 --bar --joblog joblog.txt < commands.txt

# print_commands /TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM
# print_commands /DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM
# print_commands /SMS-T1tttt_TuneCP2_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv4-PUFall18Fast_Nano14Dec2018_102X_upgrade2018_realistic_v16-v2/NANOAODSIM
# print_commands /GluGluHToZZTo4L_M130_13TeV_powheg2_JHUGenV7011_pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM

# print_commands /RPVGluinoGluinoToJets-M-300/RunIIFall17NanoAODv5-PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/NANOAODSIM
# print_commands /RPVGluinoGluinoToJets-M-900/RunIIFall17NanoAODv5-PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/NANOAODSIM
# print_commands /RPVGluinoGluinoToJets-M-200/RunIIFall17NanoAODv5-PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/NANOAODSIM
# print_commands /RPVGluinoGluinoToJets-M-1800/RunIIFall17NanoAODv5-PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/NANOAODSIM

# print_commands /JetHT/Run2016B_ver1-Nano1June2019_ver1-v1/NANOAOD
# print_commands /JetHT/Run2016B_ver2-Nano1June2019_ver2-v2/NANOAOD
# print_commands /JetHT/Run2016C-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2016D-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2016E-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2016F-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2016G-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2016H-Nano1June2019-v1/NANOAOD

# print_commands /JetHT/Run2017B-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2017C-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2017D-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2017E-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2017F-Nano1June2019-v1/NANOAOD

# print_commands /JetHT/Run2018A-Nano1June2019-v2/NANOAOD
# print_commands /JetHT/Run2018B-Nano1June2019-v2/NANOAOD
# print_commands /JetHT/Run2018C-Nano1June2019-v1/NANOAOD
# print_commands /JetHT/Run2018C-Nano1June2019-v2/NANOAOD
# print_commands /JetHT/Run2018D-Nano1June2019_ver2-v1/NANOAOD

# print_commands /DoubleMuon/Run2016B_ver1-Nano1June2019_ver1-v1/NANOAOD
# print_commands /DoubleMuon/Run2016B_ver2-Nano1June2019_ver2-v2/NANOAOD
# print_commands /DoubleMuon/Run2016C-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2016D-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2016E-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2016F-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2016G-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2016H-Nano1June2019-v1/NANOAOD

# print_commands /DoubleMuon/Run2017B-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2017C-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2017D-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2017E-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2017F-Nano1June2019-v1/NANOAOD

# print_commands /DoubleMuon/Run2018A-Nano1June2019-v2/NANOAOD
# print_commands /DoubleMuon/Run2018B-Nano1June2019-v2/NANOAOD
# print_commands /DoubleMuon/Run2018C-Nano1June2019-v1/NANOAOD
# print_commands /DoubleMuon/Run2018C-Nano1June2019-v2/NANOAOD
# print_commands /DoubleMuon/Run2018D-Nano1June2019_ver2-v1/NANOAOD
