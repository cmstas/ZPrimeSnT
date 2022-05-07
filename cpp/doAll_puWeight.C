{
  gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");  // NanoCORE library
  gROOT->ProcessLine(".L ScanChain_puWeight.C+");  // Macro that performs the selection


  vector<TString> years = { };
  years.push_back("2018");
  years.push_back("2017");
  years.push_back("2016APV");
  years.push_back("2016nonAPV");

  vector<TString> samples = { };
  map<TString,TString> sample_names = { };
  map<TString,map<TString,vector<TString>>> sample_prod = { };

  // ttbar
  samples.push_back("ttbar");
  sample_names.insert({"ttbar","TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8"});
  sample_prod.insert({"ttbar", { { "2018",       { "RunIISummer20UL18NanoAODv9_106X_upgrade2018_realistic_v16_L1v1-v1" } },
                                 { "2017",       { "RunIISummer20UL17NanoAODv9_106X_mc2017_realistic_v9-v1" } },
                                 { "2016APV",    { "RunIISummer20UL16NanoAODAPVv9_106X_mcRun2_asymptotic_preVFP_v11-v1" } },
                                 { "2016nonAPV", { "RunIISummer20UL16NanoAODv9_106X_mcRun2_asymptotic_v17-v1" } } } });

  // Signals
  vector<TString> sigModel = { "Y3" };
  vector<TString> sigMass = { "1000" };
  for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ )
  {
    for ( unsigned int imass=0; imass<sigMass.size(); imass++ )
    {
      samples.push_back(sigModel[imodel]+"_M"+sigMass[imass]);
      sample_names.insert({sigModel[imodel]+"_M"+sigMass[imass],"ZPrimeToMuMuSB_M"+sigMass[imass]+"_bestfit_TuneCP5_13TeV_Allanach_"+sigModel[imodel]+"_5f_madgraph_pythia8_NoPSWgts"});
      sample_prod.insert({sigModel[imodel]+"_M"+sigMass[imass], { { "2018",       { "RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2" } },
                                                                  { "2017",       { "RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2" } },
                                                                  { "2016APV",    { "RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2" } },
                                                                  { "2016nonAPV", { "RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2" } } } });
    }
  }

  TString baseDir = "/ceph/cms/store/user/mmasciov/ZPrimeSnT";
  for ( int iyear=0; iyear<years.size(); iyear++ )
  {
    TString year = years[iyear];
    cout<<endl;
    cout<<"Year: "<<year<<endl;
    cout<<"------------"<<endl;
    for ( int isample=0; isample<samples.size(); isample++ )
    {
      TString sample = samples[isample];

      TString dataformat = "NANOAODSIM";
      TString extension = dataformat;
      if ( sample == "ttbar" )
	extension = "onefile_unskimmed";

      TChain *ch_temp = new TChain("Events");
      TChain *chaux_temp = new TChain("Runs");
      for ( unsigned int d=0; d<sample_prod[sample][year].size(); d++ ) {
        TString dir = baseDir+"/"+sample_names[sample]+"_"+sample_prod[sample][year][d]+"_"+extension+".root";
        ch_temp->Add(dir);
        chaux_temp->Add(dir);
      }
      cout<<"Sample: "<<sample<<endl;
      ScanChain(ch_temp,getSumOfGenEventSumw(chaux_temp),year,sample);
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
