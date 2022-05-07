#include "puWeight.h"

double get_puWeight(const unsigned int nTrueInt, const TString year, const TString var="central")
{
	unsigned int npu = nTrueInt;
	if ( npu < 0 ) npu = 0;
	if ( npu >= nPUbins ) npu = nPUbins-1;
	if ( var=="central" ) {
		if ( year=="2016nonAPV" ) return puweight_central_2016nonAPV[npu];
		else if ( year=="2016APV" ) return puweight_central_2016APV[npu];
		else if ( year=="2017" ) return puweight_central_2017[npu];
		else if ( year=="2018" ) return puweight_central_2018[npu];
		else if ( year=="2018B" ) return puweight_central_2018B[npu];
		else {
			std::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;
			return 1.0;
		}
	}
	else if ( var=="up" ) {
		if ( year=="2016nonAPV" ) return puweight_up_2016nonAPV[npu];
		else if ( year=="2016APV" ) return puweight_up_2016APV[npu];
		else if ( year=="2017" ) return puweight_up_2017[npu];
		else if ( year=="2018" ) return puweight_up_2018[npu];
		else if ( year=="2018B" ) return puweight_up_2018B[npu];
		else {
			std::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;
			return 1.0;
		}
	}
	else if ( var=="down" ) {
		if ( year=="2016nonAPV" ) return puweight_down_2016nonAPV[npu];
		else if ( year=="2016APV" ) return puweight_down_2016APV[npu];
		else if ( year=="2017" ) return puweight_down_2017[npu];
		else if ( year=="2018" ) return puweight_down_2018[npu];
		else if ( year=="2018B" ) return puweight_down_2018B[npu];
		else {
			std::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;
			return 1.0;
		}
	}
	else {
		std::cout << "WARNING: unknown variation (central, up, down), returning unity piluep weight!" << std::endl;
		return 1.0;
	}
}
