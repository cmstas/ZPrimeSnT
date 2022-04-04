#ifndef METSELECTIONS_H
#define METSELECTIONS_H

#include "Nano.h"

#include "Tools/JetCorrector.h"
#include "Tools/jetcorr/FactorizedJetCorrector.h"
#include "Tools/jetcorr/JetCorrectionUncertainty.h"
#include "Tools/jetcorr/JetCorrectionUncertainty.icc"
#include "Tools/jetcorr/SimpleJetCorrectionUncertainty.icc"
#include "Tools/jetcorr/Utilities.icc"

pair<float, float> getT1CHSMET(FactorizedJetCorrector *jet_corrector, JetCorrectionUncertainty *jecUnc = NULL,
                               bool uncUp = 0);
bool passesMETfilters(bool isData);

#endif
