{
  gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
  gROOT->ProcessLine(".L ScanChain_Zp.C+");  // Macro that performs the selection


  vector<TString> years = { };
  years.push_back("2018");
  //years.push_back("2017");
  //years.push_back("2016APV");
  //years.push_back("2016nonAPV");

  vector<TString> samples = { };
  map<TString,TString> sample_names = { };
  map<TString,map<TString,TString>> sample_prod = { };
  map<TString,int> sample_useUnderscore = { };


  // ttbar
  samples.push_back("ttbar");
  sample_names.insert({"ttbar","TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8"});
  sample_prod.insert({"ttbar", { { "2018",       "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" },
                                 { "2017",       "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" },
                                 { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
                                 { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
  sample_useUnderscore.insert({"ttbar",0});

  // DY
  //samples.push_back("DY");
  //sample_names.insert({"DY","DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
  //sample_prod.insert({"DY", { { "2018",       "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2" },
  //                            { "2017",       "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2" }.
  //                            { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
  //                            { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
  //sample_useUnderscore.insert({"DY",0});

  // ZToMuMu
  vector<TString> lowM = { "50", "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000" };
  vector<TString> uppM = { "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000", "Inf" };
  for ( unsigned int imass=0; imass<lowM.size(); imass++ )
  {
    samples.push_back("ZToMuMu201X_"+lowM[imass]+"_"+uppM[imass]);
    sample_names.insert({"ZToMuMu201X_"+lowM[imass]+"_"+uppM[imass],"ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_"+lowM[imass]+"_"+uppM[imass]});
    sample_prod.insert({"ZToMuMu201X_"+lowM[imass]+"_"+uppM[imass],
      { { "2018", ( (lowM[imass]=="50" || lowM[imass]=="200") ? "RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1" :
                                                                "RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2" )},
        { "2017", ( lowM[imass]=="1400"                       ? "RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2" :
                                                                "RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1" )} } });
    sample_useUnderscore.insert({"ZToMuMu201X_"+lowM[imass]+"_"+uppM[imass],1});
  }

  for ( unsigned int imass=0; imass<lowM.size(); imass++ )
  {
    samples.push_back("ZToMuMu2016_"+lowM[imass]+"_"+uppM[imass]);
    sample_names.insert({"ZToMuMu2016_"+lowM[imass]+"_"+uppM[imass],"ZToMuMu_M-"+lowM[imass]+"To"+uppM[imass]+"_TuneCP5_13TeV-powheg-pythia8"});
    sample_prod.insert({"ZToMuMu2016_"+lowM[imass]+"_"+uppM[imass], { { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
                                                                      { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
    sample_useUnderscore.insert({"ZToMuMu2016_"+lowM[imass]+"_"+uppM[imass],0});
  }

  // VV
  vector<TString> VV = { "WW", "WZ", "ZZ" };
  for ( unsigned int iVV=0; iVV<VV.size(); iVV++ )
  {
    samples.push_back(VV[iVV]);
    sample_names.insert({VV[iVV],VV[iVV]+"_TuneCP5_13TeV-pythia8"});
    sample_prod.insert({VV[iVV], { { "2018",       "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" },
                                   { "2017",       "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" },
                                   { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
                                   { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
    sample_useUnderscore.insert({VV[iVV],0});
  }

  // tW
  vector<TString> top = { "", "anti" };
  vector<TString> top_name = { "tW", "tbarW" };
  for ( unsigned int itop=0; itop<top.size(); itop++)
  {
    samples.push_back(top_name[itop]);
    sample_names.insert({top_name[itop],"ST_tW_"+top[itop]+"top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8"});
    sample_prod.insert({top_name[itop], { { "2018",       "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" },
                                          { "2017",       "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" },
                                          { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
                                          { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
    sample_useUnderscore.insert({top_name[itop],0});
  }

  // TTX
  samples.push_back("TTW");
  sample_names.insert({"TTW","TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8"});
  sample_prod.insert({"TTW", { { "2018", "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" },
                               { "2017", "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" },
                               { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2" },
                               { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
  sample_useUnderscore.insert({"TTW",0});

  samples.push_back("TTZ");
  sample_names.insert({"TTZ","TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8"});
  sample_prod.insert({"TTZ", { { "2018",       "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" },
                               { "2017",       "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" },
                               { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
                               { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
  sample_useUnderscore.insert({"TTZ",0});

  vector<TString> bb = { "", "Non" };
  for ( unsigned int ibb=0; ibb<bb.size(); ibb++ )
  {
    samples.push_back("TTHTo"+bb[ibb]+"bb");
    sample_names.insert({"TTHTo"+bb[ibb]+"bb","ttHJetTo"+bb[ibb]+"bb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8"});
    sample_prod.insert({"TTHTo"+bb[ibb]+"bb", { { "2018",       "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1" },
                                                { "2017",       "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1" },
                                                { "2016APV",    "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1" },
                                                { "2016nonAPV", "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1" } } });
    sample_useUnderscore.insert({"TTHTo"+bb[ibb]+"bb",0});
  }

  // Signals
  vector<TString> sigModel = { "Y3", "DY3", "DYp3", "B3mL2" };
  vector<TString> sigMass = { /*"100",*/ "200", "400", "700", "1000", "1500", "2000" };
  for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ )
  {
    for ( unsigned int imass=0; imass<sigMass.size(); imass++ )
    {
      samples.push_back(sigModel[imodel]+"_M"+sigMass[imass]);
      sample_names.insert({sigModel[imodel]+"_M"+sigMass[imass],"ZPrimeToMuMuSB_M"+sigMass[imass]+"_bestfit_TuneCP5_13TeV_Allanach_"+sigModel[imodel]+"_5f_madgraph_pythia8_NoPSWgts"});
      sample_prod.insert({sigModel[imodel]+"_M"+sigMass[imass], { { "2018",       "RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private" },
                                                                  { "2017",       "RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2_private" },
                                                                  { "2016APV",    "RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2_private" },
                                                                  { "2016nonAPV", "RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2_private" } } });
      sample_useUnderscore.insert({sigModel[imodel]+"_M"+sigMass[imass],0});
    }
  }


  TString baseDir = "/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100_allBranches";
  TString baseSignalDir = baseDir;
  TString skimPackage = "skim2mu_1muPt50_1Mll100_allBranches";
  for ( int iyear=0; iyear<years.size(); iyear++ )
  {
    TString year = years[iyear];
    cout<<endl;
    cout<<"Year: "<<year<<endl;
    cout<<"------------"<<endl;
    for ( int isample=0; isample<samples.size(); isample++ )
    {
      TString sample = samples[isample];

      int useUnderscore = sample_useUnderscore[sample];

      // Account for the mess that is the ZToMuMu samples
      if ( year.Contains("2016") && sample.Contains("ZToMuMu201X_") ) continue;
      if ( (year=="2017" || year=="2018") && sample.Contains("ZToMuMu2016_") ) continue;
      if ( year=="2017" && sample.Contains("ZToMuMu201X_") && ( sample.Contains("120_200") || sample.Contains("400_800") || sample.Contains("3500_4500") || sample.Contains("6000_Inf") ) ) useUnderscore=0;

      TString dir = baseDir+"/"+sample_names[sample]+"_"+sample_prod[sample][year]+"_NANOAODSIM_"+skimPackage+"/merged/merged.root";

      TChain *ch_temp = new TChain("Events");
      ch_temp->Add(dir);

      TChain *chaux_temp = new TChain("Runs");
      chaux_temp->Add(dir);

      if ( sample.Contains("ZToMuMu201X_") ) sample.ReplaceAll("ZToMuMu201X_","ZToMuMu_");
      if ( sample.Contains("ZToMuMu2016_") ) sample.ReplaceAll("ZToMuMu2016_","ZToMuMu_");
      cout<<"Sample: "<<sample<<endl;

      ScanChain(ch_temp,getSumOfGenEventSumw(chaux_temp,useUnderscore),year,sample);
    }
    cout<<endl;
  }
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

