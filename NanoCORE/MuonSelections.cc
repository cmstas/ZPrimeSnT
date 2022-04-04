#include "MuonSelections.h"
#include "IsolationTools.h"
#include "Config.h"

using namespace tas;

bool SS::muonID(unsigned int idx, SS::IDLevel id_level, int year) {
    // Common (across years and ID levels) checks
    if (Muon_pt().at(idx) < 5.) { return false; }
    if (fabs(Muon_eta().at(idx)) > 2.4) { return false; }
    if (fabs(Muon_dxy().at(idx)) > 0.05) { return false; }
    if (fabs(Muon_dz().at(idx)) > 0.1) { return false; }
    if (!Muon_looseId().at(idx)) { return false; } // loose POG ID
    if (Muon_miniPFRelIso_all().at(idx) > 0.4) { return false; }
    if (id_level > SS::IDveto) {
        // Common (across years) fakable(loose) and tight checks
        if (Muon_pt().at(idx) < 10.) { return false; }
        if (fabs(Muon_sip3d().at(idx)) >= 4) { return false; }
        if (!Muon_mediumId().at(idx)) { return false; } // medium POG ID
        if (Muon_ptErr().at(idx) / Muon_pt().at(idx) >= 0.2) { return false; }
    }
    switch (year) {
    case (2016):
        return muon2016ID(idx, id_level);
        break;
    case (2017):
        return muon2017ID(idx, id_level);
        break;
    case (2018):
        return muon2018ID(idx, id_level);
        break;
    default:
        throw std::runtime_error("MuonSelections.cc: ERROR - invalid year");
        return false;
        break;
    }
}

bool SS::muon2016ID(unsigned int idx, SS::IDLevel id_level) {
    // ID-specific checks
    switch (id_level) {
    case (SS::IDveto):
        break;
    case (SS::IDfakable):
        break;
    case (SS::IDtight):
        if (!passesLeptonIso(idx, 13, 0.16, 0.76, 7.2)) { return false; }
        break;
    default:
        throw std::runtime_error("MuonSelections.cc: ERROR - invalid ID level");
        return false;
        break;
    }
    return true;
}

bool SS::muon2017ID(unsigned int idx, SS::IDLevel id_level) {
    // ID-specific checks
    switch (id_level) {
    case (SS::IDveto):
        break;
    case (SS::IDfakable):
        break;
    case (SS::IDtight):
        if (!passesLeptonIso(idx, 13, 0.11, 0.74, 6.8)) { return false; }
        break;
    default:
        throw std::runtime_error("MuonSelections.cc: ERROR - invalid ID level");
        return false;
        break;
    }
    return true;
}

bool SS::muon2018ID(unsigned int idx, SS::IDLevel id_level) {
    // ID-specific checks
    switch (id_level) {
    case (SS::IDveto):
        break;
    case (SS::IDfakable):
        // Same as 2017 ID
        break;
    case (SS::IDtight):
        // Same as 2017 ID
        if (!passesLeptonIso(idx, 13, 0.11, 0.74, 6.8)) { return false; }
        break;
    default:
        throw std::runtime_error("MuonSelections.cc: ERROR - invalid ID level");
        return false;
        break;
    }
    return true;
}

bool ttH::muonID(unsigned int idx, ttH::IDLevel id_level, int year) {
    // Common (across ID levels) checks
    if (Muon_pt().at(idx) <= 5.) { return false; }
    if (fabs(Muon_eta().at(idx)) >= 2.4) { return false; }
    if (fabs(Muon_dxy().at(idx)) >= 0.05) { return false; }
    if (fabs(Muon_dz().at(idx)) >= 0.1) { return false; }
    if (fabs(Muon_sip3d().at(idx)) >= 8) { return false; }
    if (Muon_miniPFRelIso_all().at(idx) >= 0.4) { return false; }
    if (!Muon_looseId().at(idx)) { return false; } // loose POG ID
    // Common fakable(loose) and tight checks
    if (id_level > ttH::IDveto) {
        if (Muon_pt().at(idx) <= 10.) { return false; }
        int jet_idx = Muon_jetIdx().at(idx); // jet_idx = -1 if no matched jet
        if (jet_idx >= 0)
        {
            if (Jet_btagDeepFlavB().at(jet_idx) >= gconf.WP_DeepFlav_medium) { return false; };
        }
        if (Muon_ptErr().at(idx) / Muon_pt().at(idx) >= 0.2) { return false; }
    }
    switch (id_level) {
    case (ttH::IDveto):
        break;
    case (ttH::IDfakable):
        if (Muon_mvaTTH().at(idx) <= 0.85) { 
            if (Muon_jetRelIso().at(idx) >= 0.5) { return false; }
        }
        break;
    case (ttH::IDtight):
        if (!Muon_mediumId().at(idx)) { return false; } // medium POG ID
        if (Muon_mvaTTH().at(idx) <= 0.85) { return false; }
        break;
    default:
        throw std::runtime_error("MuonSelections.cc: ERROR - invalid ID level");
        return false;
        break;
    }
    return true;
}
