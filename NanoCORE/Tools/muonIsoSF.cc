#include "muonIsoSF.h"

TString get_muonIsoSFPtBin(const float pt) {
	for ( unsigned int b=nptbins_iso-1; b>=1; b-- ) {
		if ( pt > thresholds_pt_iso[b] ) {
			return ptbins_iso[b];
		}
	}
	return ptbins_iso[0];
}

TString get_muonIsoSFEtaBin(const float abseta) {
	for ( unsigned int b=netabins_iso-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta_iso[b] ) {
			return etabins_iso[b];
		}
	}
	return etabins_iso[0];
}

float get_muonIsoSF( const float pt, const float eta, const TString year, const TString variation ) {
	if ( year!="2016nonAPV" && year!="2016APV" && year!="2017" && year!="2018" ) {
		std::cout << "WARNING: unknown year, returning unity muon RECO SF!" << std::endl;
		return 1.0;
	}
	if ( pt < 10.0 || fabs(eta) > 2.4 ) return 1.0;
	else {
		TString etabin = get_muonIsoSFEtaBin(fabs(eta));
		TString ptbin = get_muonIsoSFPtBin(pt);
		if ( variation == "central" ) return isosf[year][etabin][ptbin];
		else if ( variation == "up" ) return isosf[year][etabin][ptbin]+isosfunc[year][etabin][ptbin];
		else if ( variation == "down" ) return isosf[year][etabin][ptbin]-isosfunc[year][etabin][ptbin];
		else {
			std::cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << std::endl;
			return 1.0;
		}
	}
}
