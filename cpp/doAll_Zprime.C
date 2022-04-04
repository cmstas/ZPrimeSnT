{

    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
    gROOT->ProcessLine(".L ScanChain_Zprime.C+");  // Macro that performs the selection
    TChain *ch = new TChain("Events");

    // Files to be looped over
    ch->Add("/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_NANOAODSIM_skim2mu_1muPt50_1Mll100/output_1.root");

    ScanChain(ch,"2018","ttbar");

    // Additions to be made here:
    // - Chains for different processes, different years
    // - Adding loops to add large number of files to TChain

}
