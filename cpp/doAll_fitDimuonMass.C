{
  gROOT->ProcessLine(".L fitDimuonMass.C+");  // Macro that performs the selection

  bool useData = false;

  TString inDir = "temp_data/";
  vector<TString> dNames = { };
  dNames.push_back("d_mllinclusive_nBTag1p_MuDetAll");
  dNames.push_back("d_mllinclusive_nBTag1_MuDetAll");
  dNames.push_back("d_mllinclusive_nBTag2p_MuDetAll");

  vector<TString> years = { };
  years.push_back("2018");
  //years.push_back("2017");
  //years.push_back("2016APV");
  //years.push_back("2016nonAPV");

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
    samples.push_back("ttbar");
  
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
    vector<TString> VV = { "WW", "WZ", "ZZ" };
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
  vector<TString> sigModel = { "Y3", "DY3", "DYp3", "B3mL2" };
  //vector<TString> sigModel = { "Y3" };
  vector<float> sigMass = { /*100.0,*/ 200.0, 400.0, 700.0, 1000.0, 1500.0, 2000.0 };
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

  for ( int iyear=0; iyear<years.size(); iyear++ )
  {
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
	fitmass(mmumu_sig[isample], sample, false, true, sigmodels[isample], sigmasses[isample], "dcbg", "fitResults");
	if ( samples.size() > 0 ) {
	  if ( useData )
	    fitmass(*mmumu_bkg, "Background", true, false, sigmodels[isample], sigmasses[isample], "", "fitResults");
	  else
	    fitmass(*mmumu_bkg, "Background", false, false, sigmodels[isample], sigmasses[isample], "", "fitResults");
	}
	cout<<endl;
      }
    }
  }
}
