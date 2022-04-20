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
  TChain *ch6 = new TChain("Events");
  TChain *ch6aux = new TChain("Runs");
  TChain *ch7 = new TChain("Events");
  TChain *ch7aux = new TChain("Runs");
  TChain *ch8 = new TChain("Events");
  TChain *ch8aux = new TChain("Runs");
  TChain *ch9 = new TChain("Events");
  TChain *ch9aux = new TChain("Runs");
  TChain *ch10 = new TChain("Events");
  TChain *ch10aux = new TChain("Runs");
  TChain *ch11 = new TChain("Events");
  TChain *ch11aux = new TChain("Runs");
  TChain *ch_Y3_M100 = new TChain("Events");
  TChain *chaux_Y3_M100 = new TChain("Runs");
  TChain *ch_Y3_M200 = new TChain("Events");
  TChain *chaux_Y3_M200 = new TChain("Runs");
  TChain *ch_Y3_M400 = new TChain("Events");
  TChain *chaux_Y3_M400 = new TChain("Runs");
  TChain *ch_Y3_M700 = new TChain("Events");
  TChain *chaux_Y3_M700 = new TChain("Runs");
  TChain *ch_Y3_M1000 = new TChain("Events");
  TChain *chaux_Y3_M1000 = new TChain("Runs");
  TChain *ch_Y3_M1500 = new TChain("Events");
  TChain *chaux_Y3_M1500 = new TChain("Runs");
  TChain *ch_Y3_M2000 = new TChain("Events");
  TChain *chaux_Y3_M2000 = new TChain("Runs");
  TChain *ch_ZToMuMu_50_120 = new TChain("Events");
  TChain *chaux_ZToMuMu_50_120 = new TChain("Runs");
  TChain *ch_ZToMuMu_120_200 = new TChain("Events");
  TChain *chaux_ZToMuMu_120_200 = new TChain("Runs");
  TChain *ch_ZToMuMu_200_400 = new TChain("Events");
  TChain *chaux_ZToMuMu_200_400 = new TChain("Runs");
  TChain *ch_ZToMuMu_400_800 = new TChain("Events");
  TChain *chaux_ZToMuMu_400_800 = new TChain("Runs");
  TChain *ch_ZToMuMu_800_1400 = new TChain("Events");
  TChain *chaux_ZToMuMu_800_1400 = new TChain("Runs");
  TChain *ch_ZToMuMu_1400_2300 = new TChain("Events");
  TChain *chaux_ZToMuMu_1400_2300 = new TChain("Runs");
  TChain *ch_ZToMuMu_2300_3500 = new TChain("Events");
  TChain *chaux_ZToMuMu_2300_3500 = new TChain("Runs");
  TChain *ch_ZToMuMu_3500_4500 = new TChain("Events");
  TChain *chaux_ZToMuMu_3500_4500 = new TChain("Runs");
  TChain *ch_ZToMuMu_4500_6000 = new TChain("Events");
  TChain *chaux_ZToMuMu_4500_6000 = new TChain("Runs");
  TChain *ch_ZToMuMu_6000_Inf = new TChain("Events");
  TChain *chaux_ZToMuMu_6000_Inf = new TChain("Runs");

  TString baseDir = "/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100_allBranches";
  TString baseSignalDir = baseDir;
  // Files to be looped over
  ch->Add(baseDir+"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux->Add(baseDir+"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch,getSumOfGenEventSumw(chaux),"2018","ttbar");

  //ch1->Add(baseDir+"/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  //ch1aux->Add(baseDir+"/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  //ScanChain(ch1,getSumOfGenEventSumw(ch1aux),"2018","DY");

  ch_ZToMuMu_50_120->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_50_120_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_50_120->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_50_120_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_50_120,getSumOfGenEventSumw(chaux_ZToMuMu_50_120,true),"2018","ZToMuMu_50_120");

  ch_ZToMuMu_120_200->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_120_200_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_120_200->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_120_200_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_120_200,getSumOfGenEventSumw(chaux_ZToMuMu_120_200,true),"2018","ZToMuMu_120_200");

  ch_ZToMuMu_200_400->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_200_400_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_200_400->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_200_400_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_200_400,getSumOfGenEventSumw(chaux_ZToMuMu_200_400,true),"2018","ZToMuMu_200_400");

  ch_ZToMuMu_400_800->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_400_800_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_400_800->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_400_800_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_400_800,getSumOfGenEventSumw(chaux_ZToMuMu_400_800,true),"2018","ZToMuMu_400_800");

  ch_ZToMuMu_800_1400->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_800_1400_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_800_1400->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_800_1400_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_800_1400,getSumOfGenEventSumw(chaux_ZToMuMu_800_1400,true),"2018","ZToMuMu_800_1400");

  ch_ZToMuMu_1400_2300->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_1400_2300_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_1400_2300->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_1400_2300_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_1400_2300,getSumOfGenEventSumw(chaux_ZToMuMu_1400_2300,true),"2018","ZToMuMu_1400_2300");

  ch_ZToMuMu_2300_3500->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_2300_3500_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_2300_3500->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_2300_3500_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_2300_3500,getSumOfGenEventSumw(chaux_ZToMuMu_2300_3500,true),"2018","ZToMuMu_2300_3500");

  ch_ZToMuMu_3500_4500->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_3500_4500_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_3500_4500->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_3500_4500_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_3500_4500,getSumOfGenEventSumw(chaux_ZToMuMu_3500_4500,true),"2018","ZToMuMu_3500_4500");

  ch_ZToMuMu_4500_6000->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_4500_6000_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_4500_6000->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_4500_6000_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_4500_6000,getSumOfGenEventSumw(chaux_ZToMuMu_4500_6000,true),"2018","ZToMuMu_4500_6000");

  ch_ZToMuMu_6000_Inf->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_6000_Inf_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_ZToMuMu_6000_Inf->Add(baseDir+"/ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_6000_Inf_RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_ZToMuMu_6000_Inf,getSumOfGenEventSumw(chaux_ZToMuMu_6000_Inf,true),"2018","ZToMuMu_6000_Inf");
     
  ch2->Add(baseDir+"/WW_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch2aux->Add(baseDir+"/WW_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch2,getSumOfGenEventSumw(ch2aux),"2018","WW");
 
  ch3->Add(baseDir+"/WZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch3aux->Add(baseDir+"/WZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch3,getSumOfGenEventSumw(ch3aux),"2018","WZ");
   
  ch4->Add(baseDir+"/ZZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch4aux->Add(baseDir+"/ZZ_TuneCP5_13TeV-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch4,getSumOfGenEventSumw(ch4aux),"2018","ZZ");

  ch6->Add(baseDir+"/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch6aux->Add(baseDir+"/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch6,getSumOfGenEventSumw(ch6aux),"2018","tW");

  ch7->Add(baseDir+"/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch7aux->Add(baseDir+"/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch7,getSumOfGenEventSumw(ch7aux),"2018","tbarW");
    
  ch8->Add(baseDir+"/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch8aux->Add(baseDir+"/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch8,getSumOfGenEventSumw(ch8aux),"2018","TTW");

  ch9->Add(baseDir+"/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch9aux->Add(baseDir+"/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch9,getSumOfGenEventSumw(ch9aux),"2018","TTZ");
    
  ch10->Add(baseDir+"/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch10aux->Add(baseDir+"/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch10,getSumOfGenEventSumw(ch10aux),"2018","TTHToNonbb");
    
  ch11->Add(baseDir+"/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch11aux->Add(baseDir+"/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch11,getSumOfGenEventSumw(ch11aux),"2018","TTHTobb");
 
  // Signal Y3, 2018
  ch_Y3_M100->Add(baseSignalDir+"/ZPrimeToMuMuSB_M100_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_Y3_M100->Add(baseSignalDir+"/ZPrimeToMuMuSB_M100_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_Y3_M100,getSumOfGenEventSumw(chaux_Y3_M100),"2018","Y3_M100");

  ch5->Add(baseSignalDir+"/ZPrimeToMuMuSB_M200_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ch5aux->Add(baseSignalDir+"/ZPrimeToMuMuSB_M200_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch5,getSumOfGenEventSumw(ch5aux),"2018","Y3_M200");

  ch_Y3_M400->Add(baseSignalDir+"/ZPrimeToMuMuSB_M400_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_Y3_M400->Add(baseSignalDir+"/ZPrimeToMuMuSB_M400_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_Y3_M400,getSumOfGenEventSumw(chaux_Y3_M400),"2018","Y3_M400");

  ch_Y3_M700->Add(baseSignalDir+"/ZPrimeToMuMuSB_M700_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_Y3_M700->Add(baseSignalDir+"/ZPrimeToMuMuSB_M700_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_Y3_M700,getSumOfGenEventSumw(chaux_Y3_M700),"2018","Y3_M700");

  ch_Y3_M1000->Add(baseSignalDir+"/ZPrimeToMuMuSB_M1000_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_Y3_M1000->Add(baseSignalDir+"/ZPrimeToMuMuSB_M1000_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_Y3_M1000,getSumOfGenEventSumw(chaux_Y3_M1000),"2018","Y3_M1000");

  ch_Y3_M1500->Add(baseSignalDir+"/ZPrimeToMuMuSB_M1500_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_Y3_M1500->Add(baseSignalDir+"/ZPrimeToMuMuSB_M1500_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_Y3_M1500,getSumOfGenEventSumw(chaux_Y3_M1500),"2018","Y3_M1500");

  ch_Y3_M2000->Add(baseSignalDir+"/ZPrimeToMuMuSB_M2000_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  chaux_Y3_M2000->Add(baseSignalDir+"/ZPrimeToMuMuSB_M2000_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private_NANOAODSIM_skim2mu_1muPt50_1Mll100_allBranches/merged/merged.root");
  ScanChain(ch_Y3_M2000,getSumOfGenEventSumw(chaux_Y3_M2000),"2018","Y3_M2000");

}

double getSumOfGenEventSumw(TChain *chaux, bool useUnderscore=false)
{
  double genEventSumw, sumOfGenEventSumw=0.0;
  if (useUnderscore) chaux->SetBranchAddress("genEventSumw_",&genEventSumw);
  else chaux->SetBranchAddress("genEventSumw",&genEventSumw);
  for (unsigned int run = 0; run < chaux->GetEntriesFast(); run++)
    {
      chaux->GetEntry(run);
      sumOfGenEventSumw += genEventSumw;
    }

  return sumOfGenEventSumw;
}

