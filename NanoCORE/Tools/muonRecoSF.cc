#include "muonRecoSF.h"

TString get_muonRecoSFPBin_hpt(const float p) {
	vector<float> thresholds;
	vector<TString> pbins;
	thresholds.push_back(50.0);
	pbins.push_back("p0");
	thresholds.push_back(100.0);
	pbins.push_back("p1");
	thresholds.push_back(150.0);
	pbins.push_back("p2");
	thresholds.push_back(200.0);
	pbins.push_back("p3");
	thresholds.push_back(300.0);
	pbins.push_back("p4");
	thresholds.push_back(400.0);
	pbins.push_back("p5");
	thresholds.push_back(600.0);
	pbins.push_back("p6");
	thresholds.push_back(1500.0);
	pbins.push_back("p7");
	for ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {
		if ( p > thresholds.at(b) ) {
			return pbins.at(b);
		}
	}
	return pbins.at(0);
}

TString get_muonRecoSFEtaBin_hpt(const float abseta) {
	vector<float> thresholds;
	vector<TString> etabins;
	thresholds.push_back(0.0);
	etabins.push_back("eta0");
	thresholds.push_back(1.6);
	etabins.push_back("eta1");
	for ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {
		if ( abseta > thresholds.at(b) ) {
			return etabins.at(b);
		}
	}
	return etabins.at(0);
}

TString get_muonRecoSFPtBin_mpt(const float pt) {
	vector<float> thresholds;
	vector<TString> ptbins;
	thresholds.push_back(2.0);
	ptbins.push_back("pt0");
	thresholds.push_back(2.5);
	ptbins.push_back("pt1");
	thresholds.push_back(2.75);
	ptbins.push_back("pt2");
	thresholds.push_back(3.0);
	ptbins.push_back("pt3");
	thresholds.push_back(3.25);
	ptbins.push_back("pt4");
	thresholds.push_back(3.5);
	ptbins.push_back("pt5");
	thresholds.push_back(3.75);
	ptbins.push_back("pt6");
	thresholds.push_back(4.0);
	ptbins.push_back("pt7");
	thresholds.push_back(4.5);
	ptbins.push_back("pt8");
	thresholds.push_back(5.0);
	ptbins.push_back("pt9");
	thresholds.push_back(6.0);
	ptbins.push_back("pt10");
	thresholds.push_back(8.0);
	ptbins.push_back("pt11");
	thresholds.push_back(10.0);
	ptbins.push_back("pt12");
	thresholds.push_back(15.0);
	ptbins.push_back("pt13");
	thresholds.push_back(20.0);
	ptbins.push_back("pt14");
	thresholds.push_back(30.0);
	ptbins.push_back("pt15");
	for ( unsigned int b=thresholds.size()-1; b>=1; b-- ) {
		if ( pt > thresholds.at(b) ) {
			return ptbins.at(b);
		}
	}
	return ptbins.at(0);
}

TString get_muonRecoSFEtaBin_mpt(const float abseta) {
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

float get_muonRecoSF(const float p, const float pt, const float eta, const TString year, const TString variation ) {
	if ( year!="2016nonAPV" && year!="2016APV" && year!="2017" && year!="2018" ) {
		std::cout << "WARNING: unknown year, returning unity muon RECO SF!" << std::endl;
		return 1.0;
	}
	if ( pt < 10.0 || fabs(eta) > 2.4 ) return 1.0;
	if ( p > 50.0 && ( fabs(eta) < 1.6 || p > 100.0 ) ) {
		TString etabin = get_muonRecoSFEtaBin_hpt(fabs(eta));
		TString pbin = get_muonRecoSFPBin_hpt(p);
		if ( variation == "central" ) return recosfhpt[year][etabin][pbin];
		else if ( variation == "up" ) return recosfhpt[year][etabin][pbin]+recosfunchpt[year][etabin][pbin];
		else if ( variation == "down" ) return recosfhpt[year][etabin][pbin]-recosfunchpt[year][etabin][pbin];
		else {
			std::cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << std::endl;
			return 1.0;
		}
	}
	else {
		TString etabin = get_muonRecoSFEtaBin_mpt(fabs(eta));
		TString ptbin = get_muonRecoSFPtBin_mpt(pt);
		if ( variation == "central" ) return recosfmpt[year][etabin][ptbin];
		else if ( variation == "up" ) return recosfmpt[year][etabin][ptbin]+recosfuncmpt[year][etabin][ptbin];
		else if ( variation == "down" ) return recosfmpt[year][etabin][ptbin]-recosfuncmpt[year][etabin][ptbin];
		else {
			std::cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << std::endl;
			return 1.0;
		}
	}
}
