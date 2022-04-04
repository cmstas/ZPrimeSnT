// Copy some stuff from SSSelections
#ifndef HGG_SELECTIONS_H
#define HGG_SELECTIONS_H

#include "Nano.h"
#include "Base.h"
#include "Config.h"
#include "ElectronSelections.h"
#include "MuonSelections.h"

using namespace tas;

//Inspired by Nick's SSSelections Lepton
class Photon
{
    public:
        Photon(unsigned int idx);
        Photon();
        Photon(const Photon& photon);
        void set_idlevel(int);
        const float& id() const;
        const unsigned int& idx() const;
        const float& idlevel() const;
        const LorentzVector& p4() const;
        const float& pt() const;
        const float& eta() const;
        const float& phi() const;
        const float& eveto_cut() const;

    private:
        float id_;
        float pt_ = 0.;
        float eta_ = 0.;
        float phi_ = 0.;
        LorentzVector p4_;
        unsigned int idx_;
        float idlevel_ = 0.0;
        float eveto_cut_ = 0.1; 
};

class DiPhoton
{
    public:
        DiPhoton(unsigned int, unsigned int);
        DiPhoton();
        DiPhoton(Photon, Photon);
        DiPhoton(const DiPhoton&);
        const Photon& leadingPhoton() const;
        const Photon& subLeadingPhoton() const;
        const LorentzVector& p4() const;
        const float& pt() const;
        const float& eta() const;
        const float& phi() const;
        const float& mass() const;


    private:
        void computeP4();
        Photon leadingPhoton_;
        Photon subLeadingPhoton_;
        LorentzVector p4_;
        float pt_;
        float eta_;
        float phi_;
        float mass_;

};

struct Tau
{
    Tau(unsigned int idx = 0) :  idx_(idx)
    {
        pt_ = nt.Tau_pt()[idx]; 
        eta_ = nt.Tau_eta()[idx];
        phi_ = nt.Tau_phi()[idx];
        p4_ = nt.Tau_p4()[idx];
        id_vs_e_ = nt.Tau_idDeepTau2017v2p1VSe()[idx];
        id_vs_mu_ = nt.Tau_idDeepTau2017v2p1VSmu()[idx];
        id_vs_jet_ = nt.Tau_idDeepTau2017v2p1VSjet()[idx];
    }
    void set_idlevel(int idLevel_vs_e, int idLevel_vs_mu, int idLevel_vs_jet)
    {
        idLevel_vs_e_ = idLevel_vs_e;
        idLevel_vs_mu_ = idLevel_vs_mu;
        idLevel_vs_jet = idLevel_vs_jet;
    }

    int id_vs_e() 
    { 
        return id_vs_e_; 
    }
    int id_vs_mu()
    {
        return id_vs_mu_;
    }
    int id_vs_jet()
    {
        return id_vs_jet_;
    }
    unsigned int idx() 
    { 
        return idx_; 
    }
    LorentzVector p4() 
    { 
        return p4_; 
    }
    float pt() 
    { 
        return pt_; 
    }
    float eta() 
    { 
        return eta_; 
    }
    float phi() 
    { 
        return phi_; 
    }
    private:
    int id_vs_e_;
    int id_vs_mu_;
    int id_vs_jet_;
    float pt_ = 0.;
    float eta_ = 0.;
    float phi_ = 0.;
    LorentzVector p4_;
    unsigned int idx_;
    int idLevel_vs_e_ = 0.0;
    int idLevel_vs_mu_ = 0.0;
    int idLevel_vs_jet_ = 0.0;
};


typedef std::vector<Photon> Photons;

Photons getPhotons();
DiPhoton makeDiPhotonResonance(Photons& photons);
#endif
