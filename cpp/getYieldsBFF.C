{
  bool useXSec = true;
  bool useBFF2016XSec = true;
  bool writeToyCard = true;

  TString inDir = "temp_data_BFF/";
  vector<TString> dNames = { };
  dNames.push_back("d_mllinclusive_nBTag1p_MuDetAll");
  dNames.push_back("d_mllinclusive_nBTag1_MuDetAll");
  dNames.push_back("d_mllinclusive_nBTag2p_MuDetAll");
  dNames.push_back("d_mll225to275_nBTag1p_MuDetAll");
  dNames.push_back("d_mll225to275_nBTag1_MuDetAll");
  dNames.push_back("d_mll225to275_nBTag2p_MuDetAll");
  dNames.push_back("d_mll315to385_nBTag1p_MuDetAll");
  dNames.push_back("d_mll315to385_nBTag1_MuDetAll");
  dNames.push_back("d_mll315to385_nBTag2p_MuDetAll");
  dNames.push_back("d_mll360to440_nBTag1p_MuDetAll");
  dNames.push_back("d_mll360to440_nBTag1_MuDetAll");
  dNames.push_back("d_mll360to440_nBTag2p_MuDetAll");
  dNames.push_back("d_mll450to550_nBTag1p_MuDetAll");
  dNames.push_back("d_mll450to550_nBTag1_MuDetAll");
  dNames.push_back("d_mll450to550_nBTag2p_MuDetAll");
  dNames.push_back("d_mll630to770_nBTag1p_MuDetAll");
  dNames.push_back("d_mll630to770_nBTag1_MuDetAll");
  dNames.push_back("d_mll630to770_nBTag2p_MuDetAll");
  dNames.push_back("d_mll900to1100_nBTag1p_MuDetAll");
  dNames.push_back("d_mll900to1100_nBTag1_MuDetAll");
  dNames.push_back("d_mll900to1100_nBTag2p_MuDetAll");

  vector<TString> years = { };
  years.push_back("2016APV");

  vector<TString> samples = { };
  vector<TString> sigmodels = { };
  vector<TString> sigsamples = { };
  vector<float> sigmasses = { };
  map<TString,float> sigxsections = { };
  if ( useBFF2016XSec ) {
    sigxsections.insert({"BFF_M250",0.1225});
    sigxsections.insert({"BFF_M350",0.03104});
    sigxsections.insert({"BFF_M500",0.00642});
    sigxsections.insert({"BFFdbs1p0_M350",0.1658});
  }
  else {
    sigxsections.insert({"BFF_M250",0.1296});
    sigxsections.insert({"BFF_M350",0.0332});
    sigxsections.insert({"BFF_M500",0.0069});
    sigxsections.insert({"BFFdbs1p0_M350",0.1780});
  }
  sigxsections.insert({"Y3_M250",0.010116452});
  sigxsections.insert({"Y3_M400",0.0029093405});
  sigxsections.insert({"Y3_M700",0.0006143530});
  sigxsections.insert({"Y3_M1000",0.0001919544});

  // DY
  samples.push_back("DYv7");

  // ttbar
  samples.push_back("TTv7");

  // Signals
  vector<TString> sigModel = { "Y3" };
  vector<float> sigMass = { 250.0, 400.0 , 700.0, 1000.0 };
  vector<TString> sigMassString = { };
  for ( unsigned int m=0; m<sigMass.size(); m++ )
    sigMassString.push_back(Form("%.0f",sigMass[m]));
  for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ ) {
    for ( unsigned int imass=0; imass<sigMassString.size(); imass++ ) {
      sigmodels.push_back(sigModel[imodel]);
      sigsamples.push_back(sigModel[imodel]+"_M"+sigMassString[imass]);
      sigmasses.push_back(sigMass[imass]);
    }
  }

  sigModel = { "BFF" };
  sigMass = { 250.0 , 350.0, 500.0 };
  sigMassString = { };
  for ( unsigned int m=0; m<sigMass.size(); m++ )
    sigMassString.push_back(Form("%.0f",sigMass[m]));
  for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ ) {
    for ( unsigned int imass=0; imass<sigMassString.size(); imass++ ) {
      sigmodels.push_back(sigModel[imodel]);
      sigsamples.push_back(sigModel[imodel]+"_M"+sigMassString[imass]);
      sigmasses.push_back(sigMass[imass]);
    }
  }

  sigModel = { "BFFdbs1p0" };
  sigMass = { 350.0 };
  sigMassString = { };
  for ( unsigned int m=0; m<sigMass.size(); m++ )
    sigMassString.push_back(Form("%.0f",sigMass[m]));
  for ( unsigned int imodel=0; imodel<sigModel.size(); imodel++ ) {
    for ( unsigned int imass=0; imass<sigMassString.size(); imass++ ) {
      sigmodels.push_back(sigModel[imodel]);
      sigsamples.push_back(sigModel[imodel]+"_M"+sigMassString[imass]);
      sigmasses.push_back(sigMass[imass]);
    }
  }

  for ( int iyear=0; iyear<years.size(); iyear++ ) {
    TString year = years[iyear];
    for ( unsigned int d=0; d<dNames.size(); d++ ) {
      float B = 0.0;
      float TT = 0.0;
      float DY = 0.0;
      float Be = 0.0;
      float TTe = 0.0;
      float DYe = 0.0;
      RooDataSet *mmumu_bkg;
      for ( int isample=0; isample<samples.size(); isample++ ) {
	TString sample = samples[isample];
	TString inFile = Form("%s/output_%s_%s.root",inDir.Data(),sample.Data(),year.Data());
	TFile fin(inFile);
	if ( isample==0 ) {
	  mmumu_bkg = (RooDataSet*) fin.Get(dNames[d])->Clone();
	  DY = mmumu_bkg->sumEntries();	
	  if (mmumu_bkg->numEntries()>0)
	    DYe = (mmumu_bkg->sumEntries())/TMath::Sqrt(mmumu_bkg->numEntries());
	  else
	    DYe = 0.0;
	}
	else {
	  RooDataSet *tds_other = (RooDataSet*) fin.Get(dNames[d])->Clone();
	  TT = tds_other->sumEntries();	
	  if (tds_other->numEntries()>0)
	    TTe = (tds_other->sumEntries())/TMath::Sqrt(tds_other->numEntries());
	  else
	    TTe = 0.0;
	  mmumu_bkg->append( *tds_other );
	}
	fin.Close();
	B = mmumu_bkg->sumEntries();	
	Be = TMath::Sqrt(DYe*DYe+TTe*TTe);
      }
      float S = 0.0;
      float Se = 0.0;
      for ( int isample=0; isample<sigsamples.size(); isample++ ) {
	TString sample = sigsamples[isample];
	TString inFile = Form("%s/output_%s_%s.root",inDir.Data(),sample.Data(),year.Data());
	TFile fin(inFile);
	RooDataSet *tds = (RooDataSet*) fin.Get(dNames[d])->Clone();
	fin.Close();
	S = tds->sumEntries();
	if (tds->numEntries()>0)
	  Se = (tds->sumEntries())/TMath::Sqrt(tds->numEntries());
	else
	  Se = 0.0;
	if (useXSec) {
	  S *=sigxsections[sample.Data()]/0.1;
	  Se*=sigxsections[sample.Data()]/0.1;	  
	}
	TString mlow = Form("%.0f",sigmasses[isample]-0.1*sigmasses[isample]);
	if (!(dNames[d].Contains(mlow.Data()))) continue; 
	cout<<endl;
	cout<<"Year: "<<year<<endl;
	cout << dNames[d] << endl;
	cout<<"Sample: "<<sample<<endl;
	cout<<"------------"<<endl;
	cout << "S: " << S << " " << Se << endl;
	cout << "DY: " << DY << " " << DYe << endl;
	cout << "TT: " << TT << " " << TTe << endl;
	cout << "B: " << B << " " << Be << endl;
	float sob = (B>0) ? S/TMath::Sqrt(B) : -1.0;
	float sosb = (S+B>0) ? S/TMath::Sqrt(S+B) : -1.0;
	cout << "S/sqrt(B): " << sob << endl;
	cout << "S/sqrt(S+B): " << sosb << endl;
	cout<<endl;

	if ( writeToyCard ) {
	  ofstream fout;
	  TString bname = "";
	  if ( dNames[d].Contains("nBTag1p") ) bname="chsum";
	  else if ( dNames[d].Contains("nBTag1") ) bname="ch1";
	  else if ( dNames[d].Contains("nBTag2p") ) bname="ch2";
	  TString fname = Form("card_%s_%s.txt",sample.Data(),bname.Data());
	  fout.open(fname.Data());
	  fout << "imax *" << endl;
	  fout << "jmax *" << endl;
	  fout << "kmax *" << endl;
	  fout << "------" << endl;
	  //fout << "shapes * * FAKE" << endl;
	  //fout << "------" << endl;
	  fout << "bin\t\t" << bname << endl;
	  fout << Form("observation\t%.2f",B) << endl;
	  fout << "------" << endl;
	  fout << "bin\t" << bname << "\t" << bname << endl;
	  fout << "process\tsignal\tbackground" << endl;
	  fout << "process\t0\t1" << endl;
	  fout << Form("rate\t%.2f\t%.2f",S,B) << endl;
	  fout.close();
	}
      }
    }
  }
}
