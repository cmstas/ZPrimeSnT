{
  gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
  gROOT->ProcessLine(".L ScanChain_Zp.C+");  // Macro that performs the selection

  // Event weights / scale factors:
  //  0: Do not apply
  //  1: Apply central value
  // +2: Apply positive variation
  // -2: Apply negative variation
  int prefireWeight=1; // +/-2 = Syst variations, +/-3 = Stat variations --> Possibly merge in the future?
  int topPtWeight=1; // bool variable, only have or not have
  int PUWeight=1;
  int muonRecoSF=1;
  int muonIdSF=1;
  int muonIsoSF=1;
  int triggerSF=1;
  int bTagSF=1;
  int JECUnc=0; // No central value, set to +/-2 to get variations
  int JERUnc=0; // Use 1 to apply the nominal JER corrections, set to +/-2 to get variations
  const char* outdir = "temp_data"; // Name of output directory

  // 2016: https://twiki.cern.ch/twiki/bin/view/CMS/PdmVDatasetsUL2016
  // 2017: https://twiki.cern.ch/twiki/bin/view/CMS/PdmVDatasetsUL2017
  // 2018: https://twiki.cern.ch/twiki/bin/view/CMS/PdmVDatasetsUL2018
  vector<TString> years = { };
  years.push_back("2018");
  years.push_back("2017");
  years.push_back("2016APV");
  years.push_back("2016nonAPV");

  vector<TString> samples = { };
  map<TString,TString> sample_names = { };
  map<TString,map<TString,vector<TString>>> sample_prod = { };

  bool run_data = 1;
  bool run_MCbkg = 1;
  bool run_signal = 1;

  if(run_data){
    // SingleMuon data
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

  if(run_MCbkg){
    // ttbar
    samples.push_back("ttbar");
    sample_names.insert({"ttbar","TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8"});
    sample_prod.insert({"ttbar", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                   { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                   { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                   { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

    // DY
    //samples.push_back("DY");
    //sample_names.insert({"DY","DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
    //sample_prod.insert({"DY", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" } },
    //                            { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" } }.
    //                            { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
    //                            { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

    // DYbb
    samples.push_back("DYbb");
    sample_names.insert({"DYbb","DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8"});
    sample_prod.insert({"DYbb", { { "2018",       { "RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1" } },
	                          { "2017",       { "RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1" } },
				  { "2016APV",    { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } },
				  { "2016nonAPV", { "RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1" } } } });

    // ZToMuMu
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

    // VV
    vector<TString> VV = { "WW", "WZ", "ZZ" };
    for ( unsigned int iVV=0; iVV<VV.size(); iVV++ )
    {
      samples.push_back(VV[iVV]);
      sample_names.insert({VV[iVV],VV[iVV]+"_TuneCP5_13TeV-pythia8"});
      sample_prod.insert({VV[iVV], { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                     { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                     { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                     { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });
    }

    // tW
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

    // tZq
    samples.push_back("tZq");
    sample_names.insert({"tZq","tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8"});
    sample_prod.insert({"tZq", { { "2018",       { "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                 { "2017",       { "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" } },
                                 { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                 { "2016nonAPV", { "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } } });

    // TTX
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

  // Signals
  if(run_signal){
    vector<TString> sigModel = { "Y3", "DY3", "DYp3", "B3mL2" };
    vector<TString> sigMass = { /*"100",*/ "200", "400", "700", "1000", "1500", "2000" };
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

  TString skimPackage = "skim2mu_1muPt50_1Mll100_allBranches_allFiles";
  TString baseDir = "/ceph/cms/store/user/evourlio/skimOutput/"+skimPackage;
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
        ch_temp->Add(dir);
        chaux_temp->Add(dir);
      }
      cout<<"Sample: "<<sample<<endl;

      if ( sample.Contains("data") ) ScanChain(ch_temp,1.0,year,sample,prefireWeight,topPtWeight,PUWeight,muonRecoSF,muonIdSF,muonIsoSF,triggerSF,bTagSF,JECUnc,JERUnc,outdir);
      else ScanChain(ch_temp,getSumOfGenEventSumw(chaux_temp),year,sample,prefireWeight,topPtWeight,PUWeight,muonRecoSF,muonIdSF,muonIsoSF,triggerSF,bTagSF,JECUnc,JERUnc,outdir);
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
