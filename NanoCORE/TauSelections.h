#ifndef TAUSELECTIONS_H
#define TAUSELECTIONS_H
#include "Base.h"
#include "Nano.h"
#include <math.h>

namespace SS {
    bool tauID(int idx, SS::IDLevel id_level, int year);
    bool tau2016ID(int idx, SS::IDLevel id_level);
    bool tau2017ID(int idx, SS::IDLevel id_level);
    bool tau2018ID(int idx, SS::IDLevel id_level);
}

namespace ttH {
    bool tauID(int idx, ttH::IDLevel id_level, int year);
}

namespace DeepTau {
    enum IDLevel {
        vvvLoose,
        vvLoose,
        vLoose,
        loose,
        medium,
        tight,
        vTight,
        vvTight,
        vvvTight
    };

    enum Variant {
        vsElectrons,
        vsMuons,
        vsJets
    };
}

bool passesDeepTau(int idx, DeepTau::IDLevel id_level, DeepTau::Variant variant);

#endif
