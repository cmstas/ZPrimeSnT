#include "puWeight.h"

double get_puWeight(const unsigned int nTrueInt, const std::string year, const std::string var="central")
{
	setWeights();
	unsigned int npu = nTrueInt;
	if ( npu < 0 ) npu = 0;
	if ( npu >= puweight_central_2018.size() ) npu = puweight_central_2018.size()-1;
	if ( var.compare("central")==0 ) {
		if ( year.compare("2016nonAPV")==0 ) return puweight_central_2016nonAPV.at(npu);
		else if ( year.compare("2016APV")==0 ) return puweight_central_2016APV.at(npu);
		else if ( year.compare("2017")==0 ) return puweight_central_2017.at(npu);
		else if ( year.compare("2018")==0 ) return puweight_central_2018.at(npu);
		else if ( year.compare("2018B")==0 ) return puweight_central_2018B.at(npu);
		else {
			std::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;
			return 1.0;
		}
	}
	else if ( var.compare("up")==0 ) {
		if ( year.compare("2016nonAPV")==0 ) return puweight_up_2016nonAPV.at(npu);
		else if ( year.compare("2016APV")==0 ) return puweight_up_2016APV.at(npu);
		else if ( year.compare("2017")==0 ) return puweight_up_2017.at(npu);
		else if ( year.compare("2018")==0 ) return puweight_up_2018.at(npu);
		else if ( year.compare("2018B")==0 ) return puweight_up_2018B.at(npu);
		else {
			std::cout << "WARNING: unknown year, returning unity piluep weight!" << std::endl;
			return 1.0;
		}
	}
	else if ( var.compare("down")==0 ) {
		if ( year.compare("2016nonAPV")==0 ) return puweight_down_2016nonAPV.at(npu);
		else if ( year.compare("2016APV")==0 ) return puweight_down_2016APV.at(npu);
		else if ( year.compare("2017")==0 ) return puweight_down_2017.at(npu);
		else if ( year.compare("2018")==0 ) return puweight_down_2018.at(npu);
		else if ( year.compare("2018B")==0 ) return puweight_down_2018B.at(npu);
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
