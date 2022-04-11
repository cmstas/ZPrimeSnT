{

    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
    gROOT->ProcessLine(".L ScanChain_Zp.C+");  // Macro that performs the selection
    TChain *ch = new TChain("Events");
    TChain *chaux = new TChain("Runs");
    TChain *ch1 = new TChain("Events");
    TChain *ch1aux = new TChain("Runs");
    TChain *ch2 = new TChain("Events");
    TChain *ch2aux = new TChain("Runs");
    TChain *ch3 = new TChain("Events");
    TChain *ch3aux = new TChain("Runs");
    TChain *ch4 = new TChain("Events");
    TChain *ch4aux = new TChain("Runs");
    TChain *ch5 = new TChain("Events");
    TChain *ch5aux = new TChain("Runs");

    // Files to be looped over
    ch->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    chaux->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ScanChain(ch,chaux,"2018","ttbar");

    ch1->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ch1aux->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ScanChain(ch1,ch1aux,"2018","DY");
     
    ch2->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/WW_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ch2aux->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/WW_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ScanChain(ch2,ch2aux,"2018","WW");
 
    ch3->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/WZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ch3aux->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/WZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ScanChain(ch3,ch3aux,"2018","WZ");
   
    ch4->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/ZZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ch4aux->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/ZZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/merged/merged.root");
    ScanChain(ch4,ch4aux,"2018","ZZ");

    // Signal Y3, M200, 2018
    ch5->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100_PrivSignal/ZPrimeToMuMuSB_M200_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_PrivSignal/merged/merged.root");
    ch5aux->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100_PrivSignal/ZPrimeToMuMuSB_M200_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_PrivSignal/merged/merged.root");
    ScanChain(ch5,ch5aux,"2018","signal");
}
