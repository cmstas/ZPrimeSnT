#include "bTagEff.h"

TString get_bTagEffPtBin(const float pt) {
	for ( unsigned int b=nptbins-2; b>=1; b-- ) { // Exclude the last pT bin due to statistics -> Use the next to last bin
		if ( pt > thresholds_pt[b] ) {
			return ptbins[b];
		}
	}
	return ptbins[0];
}

TString get_bTagEffEtaBin(const float abseta) {
	for ( unsigned int b=netabins-1; b>=1; b-- ) {
		if ( abseta > thresholds_eta[b] ) {
			return etabins[b];
		}
	}
	return etabins[0];
}

float get_bTagEff( const float pt, const float eta, const TString year, const TString WP, const int flavor, const TString variation ) {
	if ( year!="2016nonAPV" && year!="2016APV" && year!="2017" && year!="2018" ) {
		std::cout << "WARNING: unknown year, returning unity b-tagging efficiency!" << std::endl;
		return 1.0;
	}
	if ( pt < 20.0 || fabs(eta) > 2.8 ) return 1.0;
	TString etabin = get_bTagEffEtaBin(fabs(eta));
	TString ptbin = get_bTagEffPtBin(pt);
	if ( WP == "loose" ) {
		if ( flavor == 4 ) {
			if ( variation == "central" ) return bTagEff_loose_c[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_loose_c[year][etabin][ptbin]+bTagEffunc_loose_c[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_loose_c[year][etabin][ptbin]-bTagEffunc_loose_c[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else if ( flavor == 5 ) {
			if ( variation == "central" ) return bTagEff_loose_b[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_loose_b[year][etabin][ptbin]+bTagEffunc_loose_b[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_loose_b[year][etabin][ptbin]-bTagEffunc_loose_b[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else if ( flavor == 0 ){
			if ( variation == "central" ) return bTagEff_loose_udsg[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_loose_udsg[year][etabin][ptbin]+bTagEffunc_loose_udsg[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_loose_udsg[year][etabin][ptbin]-bTagEffunc_loose_udsg[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else {
			std::cout << "WARNING: unknown flavor, up, down), returning unity efficiency!" << std::endl;
			return 1.0;
		}
	}
	else if ( WP == "med" ) {
		if ( flavor == 4 ) {
			if ( variation == "central" ) return bTagEff_med_c[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_med_c[year][etabin][ptbin]+bTagEffunc_med_c[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_med_c[year][etabin][ptbin]-bTagEffunc_med_c[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else if ( flavor == 5 ) {
			if ( variation == "central" ) return bTagEff_med_b[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_med_b[year][etabin][ptbin]+bTagEffunc_med_b[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_med_b[year][etabin][ptbin]-bTagEffunc_med_b[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else if ( flavor == 0 ){
			if ( variation == "central" ) return bTagEff_med_udsg[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_med_udsg[year][etabin][ptbin]+bTagEffunc_med_udsg[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_med_udsg[year][etabin][ptbin]-bTagEffunc_med_udsg[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else {
			std::cout << "WARNING: unknown flavor, up, down), returning unity efficiency!" << std::endl;
			return 1.0;
		}
	}
	else if ( WP == "tight" ) {
		if ( flavor == 4 ) {
			if ( variation == "central" ) return bTagEff_tight_c[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_tight_c[year][etabin][ptbin]+bTagEffunc_tight_c[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_tight_c[year][etabin][ptbin]-bTagEffunc_tight_c[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else if ( flavor == 5 ) {
			if ( variation == "central" ) return bTagEff_tight_b[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_tight_b[year][etabin][ptbin]+bTagEffunc_tight_b[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_tight_b[year][etabin][ptbin]-bTagEffunc_tight_b[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else if ( flavor == 0 ){
			if ( variation == "central" ) return bTagEff_tight_udsg[year][etabin][ptbin];
			else if ( variation == "up" ) return bTagEff_tight_udsg[year][etabin][ptbin]+bTagEffunc_tight_udsg[year][etabin][ptbin];
			else if ( variation == "down" ) return bTagEff_tight_udsg[year][etabin][ptbin]-bTagEffunc_tight_udsg[year][etabin][ptbin];
			else {
				std::cout << "WARNING: unknown variation (central, up, down), returning unity efficiency!" << std::endl;
				return 1.0;
			}
		}
		else {
			std::cout << "WARNING: unknown flavor, up, down), returning unity efficiency!" << std::endl;
			return 1.0;
		}
	}
	else {
		std::cout << "WARNING: unknown WP, up, down), returning unity efficiency!" << std::endl;
		return 1.0;
	}
}
