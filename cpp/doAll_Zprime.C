{

    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
    gROOT->ProcessLine(".L ScanChain_Zp.C+");  // Macro that performs the selection
    TChain *ch = new TChain("Events");
    TChain *ch1 = new TChain("Events");
    TChain *ch2 = new TChain("Events");
    TChain *ch3 = new TChain("Events");
    TChain *ch4 = new TChain("Events");

    // Files to be looped over
    for (int j = 1; j <= 155; j++){
    ch->Add(Form("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/output_%i.root",j));
    }

    ScanChain(ch,"2018","ttbar");


    for (int k = 1; k <= 204; k++){
    ch1->Add(Form("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100/output_%i.root",k));
    }

    ScanChain(ch1,"2018","DY");

       
    for (int l = 1; l <= 31; l++){
    ch2->Add(Form("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/WW_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/output_%i.root",l));
    }   
    
    ScanChain(ch2,"2018","WW");

 
    for (int m = 1; m <= 16; m++){
    ch3->Add(Form("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/WZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/output_%i.root",m));
    }
    
    ScanChain(ch3,"2018","WZ");

   
    for (int n = 1; n <= 6; n++){
    ch4->Add(Form("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/ZZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/output_%i.root",n));
    }
   
    ScanChain(ch4,"2018","ZZ");
    
}
