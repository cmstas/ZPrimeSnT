#include "muonRecoSF.h"

TString get_muonRecoSFPBin_hpt(const float p) {
	for ( unsigned int b=npbins_hpt-1; b>=1; b-- ) {
		if ( p > thresholds_p_hpt[b] ) {
			return pbins_hpt[b];
		}
	}
	return pbins_hpt[0];
}

TString get_muonRecoSFEtaBin_hpt(const float abseta) {
	for ( unsigned int b=netabins_hpt-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta_hpt[b] ) {
			return etabins_hpt[b];
		}
	}
	return etabins_hpt[0];
}

TString get_muonRecoSFPtBin_mpt(const float pt) {
	for ( unsigned int b=nptbins_mpt-1; b>=1; b-- ) {
		if ( pt > thresholds_pt_mpt[b] ) {
			return ptbins_mpt[b];
		}
	}
	return ptbins_mpt[0];
}

TString get_muonRecoSFEtaBin_mpt(const float abseta) {
	for ( unsigned int b=netabins_mpt-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta_mpt[b] ) {
			return etabins_mpt[b];
		}
	}
	return etabins_mpt[0];
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
