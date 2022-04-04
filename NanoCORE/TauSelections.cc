#include "TauSelections.h"

using namespace tas;

bool SS::tauID(int idx, SS::IDLevel id_level, int year) 
{
    if (Tau_pt().at(idx) < 10.) { return false; }
    if (fabs(Tau_dz().at(idx)) >= 0.2) { return false; }
    if (fabs(Tau_eta().at(idx)) > 2.3) { return false; }
    switch (year) 
    {
    case (2016):
        return SS::tau2016ID(idx, id_level);
        break;
    case (2017):
        return SS::tau2017ID(idx, id_level);
        break;
    case (2018):
        return SS::tau2018ID(idx, id_level);
        break;
    default:
        throw std::runtime_error("TauSelections.cc: ERROR - invalid year");
        return false;
        break;
    }
}

bool SS::tau2016ID(int idx, SS::IDLevel id_level) 
{ 
    return SS::tau2017ID(idx, id_level); 
}

bool SS::tau2017ID(int idx, SS::IDLevel id_level) 
{
    switch(id_level) 
    {
    case (SS::IDveto):
        return true;
        break;
    case (SS::IDfakable):
        if(!passesDeepTau(idx, DeepTau::vvLoose, DeepTau::vsElectrons)) { return false; }
        if(!passesDeepTau(idx, DeepTau::vLoose, DeepTau::vsMuons)) { return false; }
        if(!passesDeepTau(idx, DeepTau::loose, DeepTau::vsJets)) { return false; }
        return true;
        break;
    case (SS::IDtight):
        if(!passesDeepTau(idx, DeepTau::vLoose, DeepTau::vsElectrons)) { return false; }
        if(!passesDeepTau(idx, DeepTau::loose, DeepTau::vsMuons)) { return false; }
        if(!passesDeepTau(idx, DeepTau::tight, DeepTau::vsJets)) { return false; }
        return true;
        break;
    default:
        throw std::runtime_error("TauSelections.cc: ERROR - invalid ID level");
        return false;
        break;
    }
}

bool SS::tau2018ID(int idx, SS::IDLevel id_level) 
{ 
    return SS::tau2017ID(idx, id_level); 
}

bool ttH::tauID(int idx, ttH::IDLevel id_level, int year) 
{
    if (Tau_pt().at(idx) <= 20.) { return false; }
    if (fabs(Tau_dz().at(idx)) >= 0.2) { return false; }
    if (fabs(Tau_eta().at(idx)) >= 2.3) { return false; }
    if (!Tau_idDecayModeNewDMs().at(idx)) { return false; }
    if (id_level > ttH::IDveto)
    {
        // Reject two-prong decay modes
        if (Tau_decayMode().at(idx) == 5) { return false; }
        if (Tau_decayMode().at(idx) == 6) { return false; }
    }
    switch(id_level) 
    {
    case (ttH::IDveto):
        if (!passesDeepTau(idx, DeepTau::vLoose, DeepTau::vsJets)) { return false; }       // > VVLoose
        return true;
        break;
    case (ttH::IDfakable):
        if (!passesDeepTau(idx, DeepTau::vLoose, DeepTau::vsJets)) { return false; }       // > VVLoose
        if (!passesDeepTau(idx, DeepTau::loose, DeepTau::vsMuons)) { return false; }       // > VLoose
        if (!passesDeepTau(idx, DeepTau::vvLoose, DeepTau::vsElectrons)) { return false; } // > VVVLoose
        return true;
        break;
    case (ttH::IDtight):
        if (!passesDeepTau(idx, DeepTau::medium, DeepTau::vsJets)) { return false; }       // > Loose (ttH AN-19-111 1l+1tau channel ID)
        if (!passesDeepTau(idx, DeepTau::loose, DeepTau::vsMuons)) { return false; }       // > VLoose
        if (!passesDeepTau(idx, DeepTau::vvLoose, DeepTau::vsElectrons)) { return false; } // > VVVLoose
        return true;
        break;
    default:
        throw std::runtime_error("TauSelections.cc: ERROR - invalid ID level");
        return false;
        break;
    }
}

bool passesDeepTau(int idx, DeepTau::IDLevel id_level, DeepTau::Variant variant) 
{
    int bit_flag;
    if (variant == DeepTau::vsMuons)
    {
        if (id_level < DeepTau::vLoose || id_level > DeepTau::tight)
        {
            throw std::runtime_error("TauSelections.cc: ERROR - invalid DeepTau vs. mu ID level");
            return false;
        }
        bit_flag = std::pow(2, int(id_level - 2));
    }
    else
    {
        bit_flag = std::pow(2, int(id_level));
    }
    switch (variant) 
    {
    case (DeepTau::vsElectrons):
        return bool(Tau_idDeepTau2017v2p1VSe().at(idx) & bit_flag);
        break;
    case (DeepTau::vsMuons):
        return bool(Tau_idDeepTau2017v2p1VSmu().at(idx) & bit_flag);
        break;
    case (DeepTau::vsJets):
        return bool(Tau_idDeepTau2017v2p1VSjet().at(idx) & bit_flag);
        break;
    default:
        throw std::runtime_error("TauSelections.cc: ERROR - invalid DeepTau variant");
        return false;
        break;
    }
}
