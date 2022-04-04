#include "HggSelections.h"
#include "Config.h"
#include "ElectronSelections.h"
#include "MuonSelections.h"
#include <algorithm>

using namespace tas;

Photon::Photon(unsigned int idx) : idx_(idx)
{
        pt_ = nt.Photon_pt()[idx_];
        eta_ = nt.Photon_eta()[idx_];
        phi_ = nt.Photon_phi()[idx_];
        p4_ = nt.Photon_p4()[idx_];
        id_ = nt.Photon_mvaID()[idx_];
        eveto_cut_ = nt.Photon_electronVeto()[idx_];
}
Photon::Photon()
{
        //do nothing!
    idx_ = -1;
    pt_ = 0.;
    eta_ = 0.;
    phi_ = 0.;
    idlevel_ = 0.0;
    eveto_cut_ = 0.1; 
    id_ = 0.0;
}
Photon::Photon(const Photon& photon)
{
    pt_ = photon.pt_;
    eta_ = photon.eta_;
    phi_ = photon.phi_;
    p4_ = photon.p4_;
    id_ = photon.id_;
    eveto_cut_ = photon.eveto_cut_;
    idlevel_ = photon.idlevel_;
    idx_ = photon.idx_;
}

void Photon::set_idlevel(int idlevel) 
{ 
    idlevel_ = idlevel; 
}
const float& Photon::id() const
{ 
    return id_; 
}
const unsigned int& Photon::idx() const
{ 
    return idx_; 
}
const float& Photon:: idlevel() const
{ 
    return idlevel_; 
}
const LorentzVector& Photon::p4() const
{ 
    return p4_; 
}
const float& Photon::pt() const 
{ 
    return pt_; 
}
const float& Photon::eta() const
{ 
    return eta_; 
}
const float& Photon::phi() const
{ 
    return phi_; 
}
const float& Photon::eveto_cut() const
{
    return eveto_cut_;
}

DiPhoton::DiPhoton(unsigned int idx1, unsigned int idx2)
{
    leadingPhoton_ = Photon(idx1);
    subLeadingPhoton_ = Photon(idx2);

    if(leadingPhoton_.pt() < subLeadingPhoton_.pt())
    {
        auto temp = leadingPhoton_;
        leadingPhoton_ = subLeadingPhoton_;
        subLeadingPhoton_ = temp;
    }
    computeP4();
}
DiPhoton::DiPhoton()
{

}
DiPhoton::DiPhoton(Photon pho1, Photon pho2)
{
    if(pho1.pt() < pho2.pt())
    {
        leadingPhoton_ = pho2;
        subLeadingPhoton_ = pho1;
    }
    else
    {
        leadingPhoton_ = pho1;
        subLeadingPhoton_ = pho2;
    }
    computeP4();
}
DiPhoton::DiPhoton(const DiPhoton& dp)
{
    leadingPhoton_ = dp.leadingPhoton_;
    subLeadingPhoton_ = dp.subLeadingPhoton_;
    p4_ = dp.p4_;
    pt_ = dp.pt_;
    eta_ = dp.eta_;
    phi_ = dp.phi_;
    mass_ = dp.mass_;
}

const Photon& DiPhoton::leadingPhoton() const
{
    return leadingPhoton_;
}
const Photon& DiPhoton::subLeadingPhoton() const
{
    return subLeadingPhoton_;
}
const LorentzVector& DiPhoton::p4() const
{
    return p4_;
}
const float& DiPhoton::pt() const
{
    return pt_;
}
const float& DiPhoton::eta() const
{
    return eta_;
}
const float& DiPhoton::phi() const
{
    return phi_;
}
const float& DiPhoton::mass() const
{
    return mass_;
}


void DiPhoton::computeP4()
{
    p4_ = leadingPhoton_.p4() + subLeadingPhoton_.p4();
    pt_ = p4_.pt();
    eta_ = p4_.eta();
    phi_ = p4_.phi();
    mass_ = p4_.mass();
}


Photons getPhotons()
{
    Photons photons;
    for(unsigned int iPh = 0; iPh < Photon_pt().size(); iPh++)
    {
        if(Photon_pt()[iPh] < 10) 
        { 
            continue; 
        }
        photons.push_back(Photon(iPh));
    }
    return photons;
}

//copy from diphoton skims
bool useLowR9(Photon& photon, float rho, float isEB)
{
    if(isEB)
    {
        if(Photon_sieie()[photon.idx()] >= 0.015)
        {
            return false;
        }
        if(Photon_trkSumPtHollowConeDR03()[photon.idx()] >= 6.0)
        {
            return false;
        }
        if(Photon_photonIso()[photon.idx()] - 0.16544 * rho >= 4.0)
        {
            return false;
        }
    }
    else
    {
        if(Photon_sieie()[photon.idx()] >= 0.035)
        {
            return false;
        }
        if(Photon_trkSumPtHollowConeDR03()[photon.idx()] >= 6.0)
        {
            return false;
        }
        if(Photon_photonIso()[photon.idx()] - 0.13212 * rho >= 4.0)
        {
            return false;
        }  
    }
    return true;
}

bool EB_highR9(Photon& photon)
{
    return std::abs(photon.eta()) < 1.5 and Photon_r9()[photon.idx()] > 0.85;
}

bool EE_highR9(Photon&  photon)
{
    return std::abs(photon.eta()) > 1.5 and Photon_r9()[photon.idx()] > 0.9;
}

bool EB_lowR9(Photon& photon)
{
    float rho = fixedGridRhoFastjetAll();
    return std::abs(photon.eta()) < 1.5 and Photon_r9()[photon.idx()] < 0.85 and Photon_r9()[photon.idx()] > 0.5 and useLowR9(photon, rho, true);
}

bool EE_lowR9(Photon& photon)
{
    float rho = fixedGridRhoFastjetAll();
    return std::abs(photon.eta()) < 1.5 and Photon_r9()[photon.idx()] < 0.85 and Photon_r9()[photon.idx()] > 0.5 and useLowR9(photon, rho, false);

}

DiPhoton makeDiPhotonResonance(Photons& photons)
{
    //copy selections from skim!
    Photons goodPhotons;
    DiPhoton diPhoton;

    for(auto &ph:photons)
    {
        if(ph.eveto_cut() >= 0.5 and (EE_highR9(ph) or EB_highR9(ph) or EB_lowR9(ph) or EE_lowR9(ph)))
        {
            if(Photon_hoe()[ph.idx()] < 0.08 and std::abs(ph.eta()) < 2.5 and (std::abs(ph.eta()) < 1.442 or abs(ph.eta()) > 1.566) and (Photon_r9()[ph.idx()] > 0.8 \
                        or Photon_chargedHadronIso()[ph.idx()] < 20 or Photon_chargedHadronIso()[ph.idx()]/ph.pt() < 0.3))
            {
                goodPhotons.push_back(ph);
            }
        }
    }
    std::sort(goodPhotons.begin(), goodPhotons.end(), [](const Photon& ph1, const Photon& ph2){return ph1.pt() > ph2.pt();});
    if(goodPhotons.size() >= 2 and goodPhotons[0].pt() > 35 and goodPhotons[1].pt() > 25)
    {
        diPhoton = DiPhoton(goodPhotons[0], goodPhotons[1]);
    }
    else
    {
        diPhoton = DiPhoton(Photon(), Photon());
    }
    return diPhoton;
}

