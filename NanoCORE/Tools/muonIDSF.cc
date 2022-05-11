#include "muonIDSF.h"

TString get_muonIDSFPtBin(const float pt) {
	for ( unsigned int b=nptbins_id-1; b>=1; b-- ) {
		if ( pt > thresholds_pt_id[b] ) {
			return ptbins_id[b];
		}
	}
	return ptbins_id[0];
}

TString get_muonIDSFEtaBin(const float abseta) {
	for ( unsigned int b=netabins_id-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta_id[b] ) {
			return etabins_id[b];
		}
	}
	return etabins_id[0];
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
