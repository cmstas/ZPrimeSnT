#include "muonRecoSF.h"

TString get_muonRecoSFPBin_hpt(const float p) {
	for ( unsigned int b=thresholds_p_hpt.size()-1; b>=1; b-- ) {
		if ( p > thresholds_p_hpt.at(b) ) {
			return pbins_hpt.at(b);
		}
	}
	return pbins_hpt.at(0);
}

TString get_muonRecoSFEtaBin_hpt(const float abseta) {
	for ( unsigned int b=thresholds_eta_hpt.size()-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta_hpt.at(b) ) {
			return etabins_hpt.at(b);
		}
	}
	return etabins_hpt.at(0);
}

TString get_muonRecoSFPtBin_mpt(const float pt) {
	for ( unsigned int b=thresholds_pt_mpt.size()-1; b>=1; b-- ) {
		if ( pt > thresholds_pt_mpt.at(b) ) {
			return ptbins_mpt.at(b);
		}
	}
	return ptbins_mpt.at(0);
}

TString get_muonRecoSFEtaBin_mpt(const float abseta) {
	for ( unsigned int b=thresholds_eta_mpt.size()-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta_mpt.at(b) ) {
			return etabins_mpt.at(b);
		}
	}
	return etabins_mpt.at(0);
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
