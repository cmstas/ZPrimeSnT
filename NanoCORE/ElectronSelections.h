#ifndef ELECTRONSELECTIONS_H
#define ELECTRONSELECTIONS_H
#include "Base.h"
#include "Nano.h"

namespace SS {
    enum ElectronMVAIDLevel {
        vetoNoIso2018,
        fakableNoIsoLooseMVA2018,
        medium2018,
        vetoNoIso2017,
        fakableNoIsoLooseMVA2017,
        medium2017,
        vetoNoIso2016,
        fakableNoIso2016,
        fakableNoIsoLooseMVA2016,
        mediumNoIso2016
    };

    bool electronID(int idx, SS::IDLevel id_level, int year);
    bool electron2016ID(int idx, SS::IDLevel id_level);
    bool electron2017ID(int idx, SS::IDLevel id_level);
    bool electron2018ID(int idx, SS::IDLevel id_level);
    bool passesElectronMVA(int idx, SS::ElectronMVAIDLevel id_level, int year);
    bool isTriggerSafeNoIso(int idx);
}

namespace ttH {
    bool electronID(int idx, ttH::IDLevel id_level, int year);
    bool isTriggerSafeNoIso(int idx);
}

#endif
