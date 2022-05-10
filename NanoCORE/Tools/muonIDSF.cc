#include "muonIDSF.h"

TString get_muonIDSFPtBin(const float pt) {
	vector<float> thresholds;
	vector<TString> ptbins;
	thresholds.push_back(15.0);
	ptbins.push_back("pt0");
	thresholds.push_back(20.0);
	ptbins.push_back("pt1");
	thresholds.push_back(25.0);
	ptbins.push_back("pt2");
	thresholds.push_back(30.0);
	ptbins.push_back("pt3");
	thresholds.push_back(40.0);
	ptbins.push_back("pt4");
	thresholds.push_back(50.0);
	ptbins.push_back("pt5");
	thresholds.push_back(60.0);
	ptbins.push_back("pt6");
	for ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {
		if ( pt > thresholds.at(b) ) {
			return ptbins.at(b);
		}
	}
	return ptbins.at(0);
}

TString get_muonIDSFEtaBin(const float abseta) {
	vector<float> thresholds;
	vector<TString> etabins;
	thresholds.push_back(0.0);
	etabins.push_back("eta0");
	thresholds.push_back(0.9);
	etabins.push_back("eta1");
	thresholds.push_back(1.2);
	etabins.push_back("eta2");
	thresholds.push_back(2.1);
	etabins.push_back("eta3");
	for ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {
		if ( abseta > thresholds.at(b) ) {
			return etabins.at(b);
		}
	}
	return etabins.at(0);
}

float get_muonIDSF( const float pt, const float eta, const TString year, const TString variation ) {
	if ( year!="2016nonAPV" && year!="2016APV" && year!="2017" && year!="2018" ) {
		std::cout << "WARNING: unknown year, returning unity muon RECO SF!" << std::endl;
		return 1.0;
	}
	if ( pt < 10.0 || fabs(eta) > 2.4 ) return 1.0;
	else {
		TString etabin = get_muonIDSFEtaBin(fabs(eta));
		TString ptbin = get_muonIDSFPtBin(pt);
		if ( variation == "central" ) return idsf[year][etabin][ptbin];
		else if ( variation == "up" ) return idsf[year][etabin][ptbin]+idsfunc[year][etabin][ptbin];
		else if ( variation == "down" ) return idsf[year][etabin][ptbin]-idsfunc[year][etabin][ptbin];
		else {
			std::cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << std::endl;
			return 1.0;
		}
	}
}
