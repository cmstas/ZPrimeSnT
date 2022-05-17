{
    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
    gROOT->ProcessLine(".L ScanChain_btagEff.C+");
    TChain *ch_2016APV = new TChain("Events");
    TChain *ch_2016nonAPV = new TChain("Events");
    TChain *ch_2017 = new TChain("Events");
    TChain *ch_2018 = new TChain("Events");

    ch_2016APV->Add("/ceph/cms/store/user/mmasciov/ZPrimeSnT/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL16NanoAODAPVv9_106X_mcRun2_asymptotic_preVFP_v11-v1_onefile_unskimmed.root");
    ScanChain(ch_2016APV, -1, -1, "DeepFlav_106X_2016APV_ttbar_2lep");

    ch_2016nonAPV->Add("/ceph/cms/store/user/mmasciov/ZPrimeSnT/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL16NanoAODv9_106X_mcRun2_asymptotic_v17-v1_onefile_unskimmed.root");
    ScanChain(ch_2016nonAPV, -1, -1, "DeepFlav_106X_2016nonAPV_ttbar_2lep");

    ch_2017->Add("/ceph/cms/store/user/mmasciov/ZPrimeSnT/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL17NanoAODv9_106X_mc2017_realistic_v9-v1_onefile_unskimmed.root");
    ScanChain(ch_2017, -1, -1, "DeepFlav_106X_2017_ttbar_2lep");

    ch_2018->Add("/ceph/cms/store/user/mmasciov/ZPrimeSnT/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9_106X_upgrade2018_realistic_v16_L1v1-v1_onefile_unskimmed.root");
    ScanChain(ch_2018, -1, -1, "DeepFlav_106X_2018_ttbar_2lep");

}
