{
  gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
  gROOT->ProcessLine(".L ScanChain_Zp.C+");  // Macro that performs the selection


  vector<TString> years = { };
  years.push_back("2018");
  //years.push_back("2017");
  //years.push_back("2016");

  vector<TString> samples = { };
  map<TString,TString> sample_names = { };
  map<TString,TString> sample_prod = { };
  map<TString,int> sample_useUnderscore = { };


  // ttbar
  samples.push_back("ttbar");
  sample_names.insert({"ttbar","TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8"});
  sample_prod.insert({"ttbar","RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1"});
  sample_useUnderscore.insert({"ttbar",0});

  // DY
  //samples.push_back("DY");
  //sample_names.insert({"DY","DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8"});
  //sample_prod.insert({"DY","RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2"});
  //sample_useUnderscore.insert({"DY",0});

  // ZToMuMu
  vector<TString> lowM = { "50", "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000" };
  vector<TString> uppM = { "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000", "Inf" };
  for ( unsigned int imass=0; imass<lowM.size(); imass++ )
  {
    samples.push_back("ZToMuMu_"+lowM[imass]+"_"+uppM[imass]);
    sample_names.insert({"ZToMuMu_"+lowM[imass]+"_"+uppM[imass],"ZToMuMu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_M_"+lowM[imass]+"_"+uppM[imass]});
    sample_prod.insert({"ZToMuMu_"+lowM[imass]+"_"+uppM[imass],( (lowM[imass]=="50" || lowM[imass]=="200") ? "RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1" : "RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2" )});
    sample_useUnderscore.insert({"ZToMuMu_"+lowM[imass]+"_"+uppM[imass],1});
  }

  // VV
  vector<TString> VV = { "WW", "WZ", "ZZ" };
  for ( unsigned int iVV=0; iVV<VV.size(); iVV++ )
  {
    samples.push_back(VV[iVV]);
    sample_names.insert({VV[iVV],VV[iVV]+"_TuneCP5_13TeV-pythia8"});
    sample_prod.insert({VV[iVV],"RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1"});
    sample_useUnderscore.insert({VV[iVV],0});
  }

  // tW
  vector<TString> top = { "", "anti" };
  vector<TString> top_name = { "tW", "tbarW" };
  for ( unsigned int itop=0; itop<top.size(); itop++)
  {
    samples.push_back(top_name[itop]);
    sample_names.insert({top_name[itop],"ST_tW_"+top[itop]+"top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8"});
    sample_prod.insert({top_name[itop],"RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1"});
    sample_useUnderscore.insert({top_name[itop],0});
  }

  // TTX
  samples.push_back("TTW");
  sample_names.insert({"TTW","TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8"});
  sample_prod.insert({"TTW","RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1"});
  sample_useUnderscore.insert({"TTW",0});

  samples.push_back("TTZ");
  sample_names.insert({"TTZ","TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8"});
  sample_prod.insert({"TTZ","RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1"});
  sample_useUnderscore.insert({"TTZ",0});

  vector<TString> bb = { "", "Non" };
  for ( unsigned int ibb=0; ibb<bb.size(); ibb++ )
  {
    samples.push_back("TTHTo"+bb[ibb]+"bb");
    sample_names.insert({"TTHTo"+bb[ibb]+"bb","ttHJetTo"+bb[ibb]+"bb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8"});
    sample_prod.insert({"TTHTo"+bb[ibb]+"bb","RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1"});
    sample_useUnderscore.insert({"TTHTo"+bb[ibb]+"bb",0});
  }

  // Signals
  vector<TString> sigMass = { /*"100",*/ "200", "400", "700", "1000", "1500", "2000" };
  for ( unsigned int imass=0; imass<sigMass.size(); imass++ )
  {
    samples.push_back("Y3_M"+sigMass[imass]);
    sample_names.insert({"Y3_M"+sigMass[imass],"ZPrimeToMuMuSB_M"+sigMass[imass]+"_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts"});
    sample_prod.insert({"Y3_M"+sigMass[imass],"RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private"});
    sample_useUnderscore.insert({"Y3_M"+sigMass[imass],0});
  }


  TString baseDir = "/ceph/cms/store/user/evourlio/skimOutput/skim2mu_1muPt50_1Mll100_allBranches";
  TString baseSignalDir = baseDir;
  TString skimPackage = "skim2mu_1muPt50_1Mll100_allBranches";
  for ( int iyear=0; iyear<years.size(); iyear++ )
  {
    TString year = years[iyear];
    for ( int isample=0; isample<samples.size(); isample++ )
    {
      TString sample = samples[isample];
      cout<<sample<<endl;
      TString dir = baseDir+"/"+sample_names[sample]+"_"+sample_prod[sample]+"_NANOAODSIM_"+skimPackage+"/merged/merged.root";

      TChain *ch_temp = new TChain("Events");
      ch_temp->Add(dir);

      TChain *chaux_temp = new TChain("Runs");
      chaux_temp->Add(dir);

      ScanChain(ch_temp,getSumOfGenEventSumw(chaux_temp,sample_useUnderscore[sample]),year,sample);
    }
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

