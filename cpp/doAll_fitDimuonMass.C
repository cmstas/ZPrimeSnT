{
  gROOT->ProcessLine(".L fit_dimuon.C+");  // Macro that performs the selection

  bool useData = false;
  bool writeWS = true;
  bool mergeYears = true;

  TString inDir = "temp_data/";
  vector<TString> dNames = { };
  dNames.push_back("d_mllinclusive_nBTag1p_MuDetAll");
  dNames.push_back("d_mllinclusive_nBTag1_MuDetAll");
  dNames.push_back("d_mllinclusive_nBTag2p_MuDetAll");
  //dNames.push_back("d_mllinclusive_nBTag1p_BB");
  //dNames.push_back("d_mllinclusive_nBTag1_BB");
  //dNames.push_back("d_mllinclusive_nBTag2p_BB");
  //dNames.push_back("d_mllinclusive_nBTag1p_BE");
  //dNames.push_back("d_mllinclusive_nBTag1_BE");
  //dNames.push_back("d_mllinclusive_nBTag2p_BE");
  //dNames.push_back("d_mllinclusive_nBTag1p_EE");
  //dNames.push_back("d_mllinclusive_nBTag1_EE");
  //dNames.push_back("d_mllinclusive_nBTag2p_EE");

  vector<TString> years = { };
  years.push_back("2018");
  years.push_back("2017");
  years.push_back("2016APV");
  years.push_back("2016nonAPV");

  vector<TString> samples = { };
  vector<TString> sigmodels = { };
  vector<TString> sigsamples = { };
  vector<float> sigmasses = { };

  if ( useData ) {
    // SingleMuon data
    samples.push_back("data");
  }
  else {
    // ttbar
    vector<TString> fs = { "2L2Nu", "SemiLeptonic", "Hadronic" };
    for ( unsigned int ifs=0; ifs<fs.size(); ifs++)
      {
        samples.push_back("ttbar_"+fs[ifs]);
      }

    // DY
    //samples.push_back("DY");

    // ZToMuMu
    vector<TString> lowM = { "50", "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000" };
    vector<TString> uppM = { "120", "200", "400", "800", "1400", "2300", "3500", "4500", "6000", "Inf" };
    for ( unsigned int imass=0; imass<lowM.size(); imass++ )
      {
  	samples.push_back("ZToMuMu_"+lowM[imass]+"_"+uppM[imass]);
      }

    // VV
    //vector<TString> VV = { "WW", "WZ", "ZZ" };
    vector<TString> VV = { "WWTo1L1Nu2Q", "WWTo4Q", "WWTo2L2Nu",
                           "WZTo1L1Nu2Q", "WZTo1L3Nu", "WZTo2Q2L","WZTo3LNu",
                           "ZZTo2L2Nu", "ZZTo2Nu2Q", "ZZTo2Q2L", "ZZTo4L", "ZZTo4Q" };
    for ( unsigned int iVV=0; iVV<VV.size(); iVV++ )
      {
  	samples.push_back(VV[iVV]);
      }

    // tW
    vector<TString> top = { "", "anti" };
    vector<TString> top_name = { "tW", "tbarW" };
    for ( unsigned int itop=0; itop<top.size(); itop++)
      {
  	samples.push_back(top_name[itop]);
      }

    // tZq
    samples.push_back("tZq");

    // TTX
    samples.push_back("TTW");
    samples.push_back("TTZ");
    vector<TString> bb = { "", "Non" };
    for ( unsigned int ibb=0; ibb<bb.size(); ibb++ )
      {
  	samples.push_back("TTHTo"+bb[ibb]+"bb");
      }
  }

  // Signals
  vector<TString> sigModel = { "Y3"/*, "DY3", "DYp3", "B3mL2"*/ };
  vector<float> sigMass = { /*200.0,*/ 250.0, 400.0, 550.0, 700.0, 850.0, 1000.0, 1250.0, 1500.0, 2000.0 };
  vector<TString> sigMassString = { };
  for ( unsigned int m=0; m<sigMass.size(); m++ )
    sigMassString.push_back(Form("%.0f",sigMass[m]));
  for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ )
    {
      for ( unsigned int imass=0; imass<sigMassString.size(); imass++ )
	{
	  sigmodels.push_back(sigModel[imodel]);
	  sigsamples.push_back(sigModel[imodel]+"_M"+sigMassString[imass]);
	  sigmasses.push_back(sigMass[imass]);
	}
    }

  if ( !mergeYears ) {
    for ( int iyear=0; iyear<years.size(); iyear++ ) {
      TString year = years[iyear];
      cout<<endl;
      cout<<"Year: "<<year<<endl;
      cout<<"------------"<<endl;
      for ( unsigned int d=0; d<dNames.size(); d++ ) {
	RooDataSet *mmumu_bkg;
	for ( int isample=0; isample<samples.size(); isample++ ) {
	  TString sample = samples[isample];
	  cout<<"Sample: "<<sample<<endl;
	  TString inFile = Form("%s/output_%s_%s.root",inDir.Data(),sample.Data(),year.Data());
	  TFile fin(inFile);
	  if ( isample==0 ) {
	    mmumu_bkg = (RooDataSet*) fin.Get(dNames[d])->Clone();
	  }
	  else {
	    RooDataSet *tds_other = (RooDataSet*) fin.Get(dNames[d])->Clone();
	    mmumu_bkg->append( *tds_other );
	  }
	  fin.Close();
	}
	if ( useData )
	  mmumu_bkg->SetName(dNames[d]+"_data_"+year);
	else
	  mmumu_bkg->SetName(dNames[d]+"_BGMC_"+year);
	vector<RooDataSet> mmumu_sig = { };
	for ( int isample=0; isample<sigsamples.size(); isample++ ) {
	  TString sample = sigsamples[isample];
	  cout<<"Sample: "<<sample<<endl;
	  TString inFile = Form("%s/output_%s_%s.root",inDir.Data(),sample.Data(),year.Data());
	  TFile fin(inFile);
	  RooDataSet *tds = (RooDataSet*) fin.Get(dNames[d])->Clone();
	  tds->SetName(dNames[d]+"_"+sample+"_"+year);
	  mmumu_sig.push_back( *tds );
	  fin.Close();

	  // Create workspace, import data and model
	  TString outDir = "fitResults";
	  RooWorkspace wfit("wfit","workspace");

	  fitmass(mmumu_sig[isample], sample, false, true, sigmodels[isample], sigmasses[isample], wfit, "dcbfastg", outDir);
	  if ( samples.size() > 0 ) {
	    if ( useData )
	      fitmass(*mmumu_bkg, "Background", true, false, sigmodels[isample], sigmasses[isample], wfit, "", outDir);
	    else
	      fitmass(*mmumu_bkg, "Background", false, false, sigmodels[isample], sigmasses[isample], wfit, "", outDir);
	  }

	  // Print workspace contents
	  wfit.Print();

	  if ( writeWS ) {
	    // Save the workspace into a ROOT file
	    TString fwsname = Form("%s/%s_workspace.root",outDir.Data(),mmumu_sig[isample].GetName());
	    TFile *fws = new TFile(fwsname, "RECREATE");
	    fws->cd();
	    cout << "Writing workspace..." << endl;
	    wfit.Write();
	    fws->Close();
	  }
	  cout<<endl;
	}
      }
    }
  }
  else {
    for ( unsigned int d=0; d<dNames.size(); d++ ) {  
      RooDataSet *mmumu_bkg;
      cout<<endl;
      cout<<"Dataset: "<<d<<endl;
      cout<<"------------"<<endl;
      for ( int isample=0; isample<samples.size(); isample++ ) {
	TString sample = samples[isample];
	cout<<"Sample: "<<sample<<endl;
	for ( int iyear=0; iyear<years.size(); iyear++ ) {
	  TString year = years[iyear];
	  cout<<endl;
	  cout<<"Year: "<<year<<endl;
	  TString inFile = Form("%s/output_%s_%s.root",inDir.Data(),sample.Data(),year.Data());
	  TFile fin(inFile);
	  if ( isample==0 && iyear==0 ) {
	    mmumu_bkg = (RooDataSet*) fin.Get(dNames[d])->Clone();
	  }
	  else {
	    RooDataSet *tds_other = (RooDataSet*) fin.Get(dNames[d])->Clone();
	    mmumu_bkg->append( *tds_other );
	  }
	  fin.Close();
	}
      }
      if ( useData )
	mmumu_bkg->SetName(dNames[d]+"_data_allyears");
      else
	mmumu_bkg->SetName(dNames[d]+"_BGMC_allyears");
      vector<RooDataSet*> mmumu_sig = { };
      for ( int isample=0; isample<sigsamples.size(); isample++ ) {
	TString sample = sigsamples[isample];
	cout<<"Sample: "<<sample<<endl;
	for ( int iyear=0; iyear<years.size(); iyear++ ) {
	  TString year = years[iyear];
	  cout<<endl;
	  cout<<"Year: "<<year<<endl;
	  TString inFile = Form("%s/output_%s_%s.root",inDir.Data(),sample.Data(),year.Data());
	  TFile fin(inFile);
	  RooDataSet *tds;
	  if ( iyear==0 ) {
	    tds = (RooDataSet*) fin.Get(dNames[d])->Clone();
	    mmumu_sig.push_back(tds);
	  }
	  else {
	    RooDataSet *tds_other = (RooDataSet*) fin.Get(dNames[d])->Clone();
	    mmumu_sig[isample]->append( *tds_other );
	  }
	  fin.Close();
	}
	mmumu_sig[isample]->SetName(dNames[d]+"_"+sample+"_allyears");

	// Create workspace, import data and model
	TString outDir = "fitResults";
	RooWorkspace wfit("wfit","workspace");

	fitmass(*mmumu_sig[isample], sample, false, true, sigmodels[isample], sigmasses[isample], wfit, "dcbfastg", outDir);
	if ( samples.size() > 0 ) {
	  if ( useData )
	    fitmass(*mmumu_bkg, "Background", true, false, sigmodels[isample], sigmasses[isample], wfit, "", outDir);
	  else
	    fitmass(*mmumu_bkg, "Background", false, false, sigmodels[isample], sigmasses[isample], wfit, "", outDir);
	}

	// Print workspace contents
	wfit.Print();

	if ( writeWS ) {
	  // Save the workspace into a ROOT file
	  TString fwsname = Form("%s/%s_workspace.root",outDir.Data(),mmumu_sig[isample]->GetName());
	  TFile *fws = new TFile(fwsname, "RECREATE");
	  fws->cd();
	  cout << "Writing workspace..." << endl;
	  wfit.Write();
	  fws->Close();
	}
	cout<<endl;
      }
    }
  }
}
