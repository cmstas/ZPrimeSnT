#ifndef SSSELECTIONS_H
#define SSSELECTIONS_H
#include "Nano.h"
#include "Base.h"

SS::IDLevel whichLeptonLevel(int id, int idx);
bool isLeptonLevel(SS::IDLevel idlevel, int id, int idx);

struct Lepton {
    Lepton(int id = 0, unsigned int idx = 0) : id_(id), idx_(idx) {
        if (id != 0) {
            pt_ = (abs(id_) == 11 ? nt.Electron_pt()[idx_] : nt.Muon_pt()[idx_]);
            eta_ = (abs(id_) == 11 ? nt.Electron_eta()[idx_] : nt.Muon_eta()[idx_]);
            phi_ = (abs(id_) == 11 ? nt.Electron_phi()[idx_] : nt.Muon_phi()[idx_]);
            p4_ = (abs(id_) == 11 ? nt.Electron_p4()[idx_] : nt.Muon_p4()[idx_]);
            idlevel_ = whichLeptonLevel(id_, idx_);
        }
    }
    void set_idlevel(int idlevel) { idlevel_ = idlevel; }
    int id() { return id_; }
    int absid() { return abs(id_); }
    int is_el() { return abs(id_) == 11; }
    int is_mu() { return abs(id_) == 13; }
    int charge() { return -1 * id_ / abs(id_); }
    unsigned int idx() { return idx_; }
    int idlevel() { return idlevel_; }
    LorentzVector p4() { return p4_; }
    float pt() { return pt_; }
    float eta() { return eta_; }
    float phi() { return phi_; }

  private:
    int id_;
    float pt_ = 0.;
    float eta_ = 0.;
    float phi_ = 0.;
    LorentzVector p4_;
    unsigned int idx_;
    int idlevel_ = SS::IDdefault;
};
typedef std::pair<Lepton, Lepton> Hyp;
typedef std::vector<Lepton> Leptons;

std::ostream &operator<<(std::ostream &os, Lepton &lep) {
    std::string lepstr = (abs(lep.id()) == 11) ? "Electron" : "Muon";
    return os << "<" << lepstr << " id=" << std::showpos << setw(3) << lep.id() << std::noshowpos << ", idx=" << setw(2)
              << lep.idx() << ", level=" << lep.idlevel() << ", (pT,eta)="
              << "(" << lep.pt() << "," << lep.eta() << ")>";
}
template <typename T1, typename T2> std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

Leptons getLeptons();
std::tuple<int, int, float> getJetInfo(vector<Lepton> &leps, int variation = 0);
std::pair<int, int> makesResonance(Leptons &leps, Lepton lep1, Lepton lep2, float mass, float window);
std::pair<int, Hyp> getBestHyp(vector<Lepton> &leptons, bool verbose);
void dumpLeptonProperties(Lepton lep);

#endif
