R__LOAD_LIBRARY(../NanoCORE/NANO_CORE.so)
#include "ScanChain_Zp.C+"

double getSumOfGenEventSumw(TChain *chaux);

void doAll_Zp(const char* outdir="temp_data", TString yearArg="all", int run_data=1, int run_MCbkg=1, int run_signal=1, int run_BFF=0, TString sampleArg="all", int prefireWeight=1, int topPtWeight=1, int PUWeight=1, int muonRecoSF=1, int muonIdSF=1, int muonIsoSF=1, int muonScaleUnc=0, int muonResUnc=0, int triggerSF=1, int bTagSF=1, int JECUnc=0, int JERUnc=0, int UnclEnUnc=0)
{
  // Event weights / scale factors:
  //  0: Do not apply
  //  1: Apply central value
  // +2: Apply positive variation
  // -2: Apply negative variation
  //prefireWeight: +/-2 = Syst variations, +/-3 = Stat variations --> Possibly merge in the future?
  //topPtWeight: bool variable, only have or not have
  //muonScaleUnc: No central value, set to +/-2 to get variations
  //muonResUnc: No central value, set to +/-2 to get variations
  //JECUnc: No central value, set to +/-2 to get variations
  //JERUnc: Use 1 to apply the nominal JER corrections, set to +/-2 to get variations
  //UnclEnUnc: No central value, set to +/-2 to get variations

  // 2016: https://twiki.cern.ch/twiki/bin/view/CMS/PdmVDatasetsUL2016
  // 2017: https://twiki.cern.ch/twiki/bin/view/CMS/PdmVDatasetsUL2017
  // 2018: https://twiki.cern.ch/twiki/bin/view/CMS/PdmVDatasetsUL2018
  vector<TString> years = { };
  if ( yearArg=="all" ) {
    years.push_back("2018");
    years.push_back("2017");
    years.push_back("2016APV");
    years.push_back("2016nonAPV");
  }
  else if ( yearArg=="2018" || yearArg=="2017" || yearArg=="2016APV" || yearArg=="2016nonAPV" ) {
    years.push_back(yearArg);
  }
  else {
    cout << "\nInvalid option for year, exiting...\n\n";
    return;
  }


  vector<TString> samples = { };
  map<TString,TString> sample_names = { };
  map<TString,map<TString,vector<TString>>> sample_prod = { };

  bool runOnSignalBeforeSkim = false; // To get yields before any selection, to be combined with writeOutYields_BeforeSel in ScanChain_Zp

  if(run_data){
    // SingleMuon data
    if ( sampleArg=="data" || sampleArg=="all" ) {
      samples.push_back("data");
      sample_names.insert({"data", "SingleMuon"});
      sample_prod.insert({"data", { { "2018",       {
                   "Run2018A-UL2018_MiniAODv2_NanoAODv9_GT36-v1",
                 "Run2018B-UL2018_MiniAODv2_NanoAODv9_GT36-v1",
                 "Run2018C-UL2018_MiniAODv2_NanoAODv9_GT36-v1",
                 "Run2018D-UL2018_MiniAODv2_NanoAODv9_GT36-v1"
                } },
                                    { "2017",       {
                 "Run2017B-UL2017_MiniAODv2_NanoAODv9-v1",
                 "Run2017C-UL2017_MiniAODv2_NanoAODv9-v1",
                 "Run2017D-UL2017_MiniAODv2_NanoAODv9-v1",
                 "Run2017E-UL2017_MiniAODv2_NanoAODv9-v1",
                 "Run2017F-UL2017_MiniAODv2_NanoAODv9-v1",
                 "Run2017G-UL2017_MiniAODv2_NanoAODv9-v1",
                 "Run2017H-UL2017_MiniAODv2_NanoAODv9-v1",
                } },
                                    { "2016APV",    {
                 "Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v2",
                 "Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2",
                 "Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v2",
                 "Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v2",
                 "Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v2",
                 "Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v2",
                } },
                                    { "2016nonAPV", {
                 "Run2016F-UL2016_MiniAODv2_NanoAODv9-v1",
                 "Run2016G-UL2016_MiniAODv2_NanoAODv9-v1",
                 "Run2016H-UL2016_MiniAODv2_NanoAODv9-v1",
                } } } });
    }
  }

  if(run_MCbkg){
    // ttbar
    if ( sampleArg=="ttbar" || sampleArg=="all" ) {
      vector<TString> fs = { "2L2Nu", "SemiLeptonic", "Hadronic" };
      for ( unsigned int ifs=0; ifs<fs.size(); ifs++)
      {
        samples.push_back("ttbar_"+fs[ifs]);
        sample_names.insert({"ttbar_"+fs[ifs],"TTTo"+fs[ifs]+"_TuneCP5_13TeV-powheg-pythia8"});
        sample_prod.insert({"ttbar_"+fs[ifs], { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                                { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                                { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                                { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
      }
    }

    // DY
    //if ( sampleArg=="DY" || sampleArg=="all" ) {
    //  samples.push_back("DY");
    //  sample_names.insert({"DY","DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
    //  sample_prod.insert({"DY", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" } },
    //                              { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" } }.
    //                              { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
    //                              { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    //}

    // DYbb
    if ( sampleArg=="DYbb" || sampleArg=="all" ) {
      samples.push_back("DYbb");
      sample_names.insert({"DYbb","DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8"});
      sample_prod.insert({"DYbb", { { "2018",       { "RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1" } },
                              { "2017",       { "RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1" } },
            { "2016APV",    { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } },
            { "2016nonAPV", { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } } } });
    }

    // ZToMuMu
    if ( sampleArg=="ZToMuMu" || sampleArg=="all" ) {
      vector<TString> lowM = { "50", "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000" };
      vector<TString> uppM = { "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000", "Inf" };
      for ( unsigned int imass=0; imass<lowM.size(); imass++ )
      {
        samples.push_back("ZToMuMu_"+lowM[imass]+"_"+uppM[imass]);
        sample_names.insert({"ZToMuMu_"+lowM[imass]+"_"+uppM[imass],"ZToMuMu_M-"+lowM[imass]+"To"+uppM[imass]+"_TuneCP5_13TeV-powheg-pythia8"});
        sample_prod.insert({"ZToMuMu_"+lowM[imass]+"_"+uppM[imass], { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                                                      { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                                                      { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                                                      { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
      }
    }

    // VV
    //if ( sampleArg=="VV" || sampleArg=="all" ) {
    //  vector<TString> VV = { "WW", "WZ", "ZZ" };
    //  for ( unsigned int iVV=0; iVV<VV.size(); iVV++ )
    //  {
    //    samples.push_back(VV[iVV]);
    //    sample_names.insert({VV[iVV],VV[iVV]+"_TuneCP5_13TeV-pythia8"});
    //    sample_prod.insert({VV[iVV], { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
    //                                   { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
    //                                   { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
    //                                   { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    //  }
    //}

    // WW
    if ( sampleArg=="WW" || sampleArg=="all" ) {
      TString WWname="WWTo1L1Nu2Q";
      samples.push_back(WWname);
      sample_names.insert({WWname,WWname+"_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({WWname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      WWname="WWTo4Q";
      samples.push_back(WWname);
      sample_names.insert({WWname,WWname+"_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({WWname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v3" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      WWname="WWTo2L2Nu";
      samples.push_back(WWname);
      sample_names.insert({WWname,WWname+"_TuneCP5_13TeV-powheg-pythia8"});
      sample_prod.insert({WWname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    }

    // WZ
    if ( sampleArg=="WZ" || sampleArg=="all" ) {
      TString WZname="WZTo1L1Nu2Q";
      samples.push_back(WZname);
      sample_names.insert({WZname,WZname+"_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({WZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      WZname="WZTo1L3Nu";
      samples.push_back(WZname);
      sample_names.insert({WZname,WZname+"_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({WZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      WZname="WZTo2Q2L";
      samples.push_back(WZname);
      sample_names.insert({WZname,WZname+"_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({WZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2" } } } });

      WZname="WZTo3LNu";
      samples.push_back(WZname);
      sample_names.insert({WZname,WZname+"_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({WZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    }

    // ZZ
    if ( sampleArg=="ZZ" || sampleArg=="all" ) {
      TString ZZname="ZZTo2L2Nu";
      samples.push_back(ZZname);
      sample_names.insert({ZZname,ZZname+"_TuneCP5_13TeV_powheg_pythia8"});
      sample_prod.insert({ZZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      ZZname="ZZTo2Nu2Q";
      samples.push_back(ZZname);
      sample_names.insert({ZZname,ZZname+"_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({ZZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      ZZname="ZZTo2Q2L";
      samples.push_back(ZZname);
      sample_names.insert({ZZname,ZZname+"_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({ZZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      ZZname="ZZTo4L";
      samples.push_back(ZZname);
      sample_names.insert({ZZname,ZZname+"_TuneCP5_13TeV_powheg_pythia8"});
      sample_prod.insert({ZZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      ZZname="ZZTo4Q";
      samples.push_back(ZZname);
      sample_names.insert({ZZname,ZZname+"_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({ZZname, { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    }

    // tW
    if ( sampleArg=="tW" || sampleArg=="all" ) {
      vector<TString> top = { "", "anti" };
      vector<TString> top_name = { "tW", "tbarW" };
      for ( unsigned int itop=0; itop<top.size(); itop++)
      {
        samples.push_back(top_name[itop]);
        sample_names.insert({top_name[itop],"ST_tW_"+top[itop]+"top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8"});
        sample_prod.insert({top_name[itop], { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                              { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                              { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                              { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
      }
    }

    // tZq
    if ( sampleArg=="tZq" || sampleArg=="all" ) {
      samples.push_back("tZq");
      sample_names.insert({"tZq","tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8"});
      sample_prod.insert({"tZq", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                   { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                   { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                   { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    }

    // TTX
    if ( sampleArg=="TTX" || sampleArg=="all" ) {
      samples.push_back("TTW");
      sample_names.insert({"TTW","TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8"});
      sample_prod.insert({"TTW", { { "2018", { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                   { "2017", { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                   { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2" } },
                                   { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      samples.push_back("TTZ");
      sample_names.insert({"TTZ","TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8"});
      sample_prod.insert({"TTZ", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                   { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                   { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                   { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

      vector<TString> bb = { "", "Non" };
      for ( unsigned int ibb=0; ibb<bb.size(); ibb++ )
      {
        samples.push_back("TTHTo"+bb[ibb]+"bb");
        sample_names.insert({"TTHTo"+bb[ibb]+"bb","ttHJetTo"+bb[ibb]+"bb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8"});
        sample_prod.insert({"TTHTo"+bb[ibb]+"bb", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                                    { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                                    { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                                    { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
      }
    }
  }

  // Signals
  if(run_signal){
    vector<TString> sigModel;
    if ( sampleArg=="all" ) {
      sigModel.push_back("Y3");
      sigModel.push_back("DY3");
      sigModel.push_back("DYp3");
      sigModel.push_back("B3mL2");
    }
    else {
      if ( sampleArg.Contains("B3mL2") ) sigModel.push_back("B3mL2");
      else if ( sampleArg.Contains("DYp3") ) sigModel.push_back("DYp3");
      else if ( sampleArg.Contains("DY3") ) sigModel.push_back("DY3");
      else if ( sampleArg.Contains("Y3") ) sigModel.push_back("Y3");
      else cout << "Invalid signal model!\n";
    }
    vector<TString> sigMass = { /*"100",*/ "200", "250", "400", "550", "700", "850", "1000", "1250", "1500", "2000" };
    if ( sampleArg.Contains("_low" ) ) sigMass = { "200", "250", "400", "550", "700" };
    if ( sampleArg.Contains("_high" ) ) sigMass = { "850", "1000", "1250", "1500", "2000" };
    for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ )
    {
      for ( unsigned int imass=0; imass<sigMass.size(); imass++ )
      {
        samples.push_back(sigModel[imodel]+"_M"+sigMass[imass]);
        sample_names.insert({sigModel[imodel]+"_M"+sigMass[imass],"ZPrimeToMuMuSB_M"+sigMass[imass]+"_bestfit_TuneCP5_13TeV_Allanach_"+sigModel[imodel]+"_5f_madgraph_pythia8_NoPSWgts"});
        sample_prod.insert({sigModel[imodel]+"_M"+sigMass[imass], { { "2018",       { "RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private" } },
                                                                  { "2017",       { "RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2_private" } },
                                                                  { "2016APV",    { "RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2_private" } },
                                                                  { "2016nonAPV", { "RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2_private" } } } });
      }
    }
  }

  // BFF
  if(run_BFF){
    // Do not apply any corrections
    prefireWeight=0;
    topPtWeight=0;
    PUWeight=0;
    muonRecoSF=0;
    muonIdSF=0;
    muonIsoSF=0;
    muonScaleUnc=0;
    muonResUnc=0;
    triggerSF=0;
    bTagSF=0;
    JECUnc=0;
    JERUnc=0;
    UnclEnUnc=0;

    // ttbarv7
    if ( sampleArg=="TTv7" || sampleArg=="all" ) {
      samples.push_back("TTv7");
      sample_names.insert({"TTv7","TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8"});
      sample_prod.insert({"TTv7", { { "2018",       { "" } },
                                    { "2017",       { "" } },
             { "2016APV",    { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } },
             { "2016nonAPV", { "" } } } });
    }

    // DYv7
    if ( sampleArg=="DYv7" || sampleArg=="all" ) {
      samples.push_back("DYv7");
      sample_names.insert({"DYv7","DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"});
      sample_prod.insert({"DYv7", { { "2018",       { "" } },
                                    { "2017",       { "" } },
             { "2016APV",    { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext2-v1" } },
             { "2016nonAPV", { "" } } } });
    }

    vector<TString> sigMass = { "250", "350", "500" };
    if ( sampleArg=="BFF" || sampleArg=="all" ) {
      for ( unsigned int imass=0; imass<sigMass.size(); imass++ )
      {
        samples.push_back("BFF_M"+sigMass[imass]);
        sample_names.insert({"BFF_M"+sigMass[imass],"BFFZprimeToMuMu_M_"+sigMass[imass]+"_TuneCUETP8M1_13TeV-madgraph-pythia8"});
        sample_prod.insert({"BFF_M"+sigMass[imass], { { "2018",       { "" } },
                                                      { "2017",       { "" } },
                                                      { "2016APV",    { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } },
                                                      { "2016nonAPV", { "" } } } });
      }
      samples.push_back("BFFdbs1p0_M350");
      sample_names.insert({"BFFdbs1p0_M350","BFFZprimeToMuMu_M_350_dbs1p0_TuneCUETP8M1_13TeV-madgraph-pythia8"});
      sample_prod.insert({"BFFdbs1p0_M350", { { "2018",       { "" } },
                                              { "2017",       { "" } },
                                              { "2016APV",    { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } },
                                              { "2016nonAPV", { "" } } } });
    }

    sigMass.clear();
    sigMass = { "250", "400", "700", "1000" };
    if ( sampleArg=="Y3" || sampleArg=="all" ) {
      for ( unsigned int imass=0; imass<sigMass.size(); imass++ )
      {
        samples.push_back("Y3_M"+sigMass[imass]);
        sample_names.insert({"Y3_M"+sigMass[imass],"ZPrimeToMuMuSB_M"+sigMass[imass]+"_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts"});
        sample_prod.insert({"Y3_M"+sigMass[imass], { { "2018",       { "" } },
                                                { "2017",       { "" } },
                  { "2016APV",    { "RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2_private" } },
                  { "2016nonAPV", { "" } } } });
      }
    }
  }

  TString skimPackage = "skim2mu_1muPt50_1Mll100_allBranches_allFiles";
  TString baseDir = "/ceph/cms/store/user/evourlio/skimOutput/"+skimPackage;
  if (runOnSignalBeforeSkim)
    baseDir = "/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404";
  for ( int iyear=0; iyear<years.size(); iyear++ )
  {
    TString year = years[iyear];
    cout<<endl;
    cout<<"Year: "<<year<<endl;
    cout<<"------------"<<endl;
    for ( int isample=0; isample<samples.size(); isample++ )
    {
      TString sample = samples[isample];

      TString dataformat = "NANOAOD";
      if ( !(sample.Contains("data")) )
	dataformat+="SIM";

      TChain *ch_temp = new TChain("Events");
      TChain *chaux_temp = new TChain("Runs");
      for ( unsigned int d=0; d<sample_prod[sample][year].size(); d++ ) {
	if (year.Contains("2016") && sample=="DYbb")
	  sample_names[sample] = "DYBBJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
        TString dir = baseDir+"/"+sample_names[sample]+"_"+sample_prod[sample][year][d]+"_"+dataformat+"_"+skimPackage+"/merged/merged.root";
        if ( sample.Contains("BFF") )
          dir = baseDir+"/"+sample_names[sample]+"/"+sample_prod[sample][year][d]+"/"+dataformat+"/merged/merged.root";
        if ( runOnSignalBeforeSkim )
          dir = baseDir+"/"+sample_names[sample]+"/"+sample_prod[sample][year][d]+"/"+dataformat+"/output*.root";
        ch_temp->Add(dir);
        chaux_temp->Add(dir);
      }
      cout<<"Sample: "<<sample<<endl;

      if ( sample.Contains("data") ) ScanChain(ch_temp,1.0,year,sample,prefireWeight,topPtWeight,PUWeight,muonRecoSF,muonIdSF,muonIsoSF,muonScaleUnc,muonResUnc,triggerSF,bTagSF,JECUnc,JERUnc,UnclEnUnc,run_BFF,outdir);
      else ScanChain(ch_temp,getSumOfGenEventSumw(chaux_temp),year,sample,prefireWeight,topPtWeight,PUWeight,muonRecoSF,muonIdSF,muonIsoSF,muonScaleUnc,muonResUnc,triggerSF,bTagSF,JECUnc,JERUnc,UnclEnUnc,run_BFF,outdir);
    }
    cout<<endl;
  }
}

double getSumOfGenEventSumw(TChain *chaux)
{
  double genEventSumw, sumOfGenEventSumw=0.0;
  chaux->SetBranchAddress("genEventSumw",&genEventSumw);
  for (unsigned int run = 0; run < chaux->GetEntriesFast(); run++)
    {
      chaux->GetEntry(run);
      sumOfGenEventSumw += genEventSumw;
    }

  return sumOfGenEventSumw;
}
