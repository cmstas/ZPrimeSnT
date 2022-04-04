#ifndef JETCORRECTOR_H
#define JETCORRECTOR_H
#include <vector>
#include <string>
#include "TString.h"
#include "jetcorr/FactorizedJetCorrector.h"

//Are you getting pissed off because of memory-related crashes?  
//Don't forget that your vector of files has to be const!!  -Alex

FactorizedJetCorrector *makeJetCorrector (const std::vector<std::string> &vector_of_file_names);

#endif
