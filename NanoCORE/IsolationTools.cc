#include "IsolationTools.h"

using namespace tas;

bool passesLeptonIso(unsigned int idx, int id, double mini_iso_cut, double pt_ratio_cut, double pt_rel_cut) {
    double mini_iso;
    double pt_ratio;
    double pt_rel;
    if (abs(id) == 11) {
        mini_iso = Electron_miniPFRelIso_all().at(idx);
        pt_ratio = 1 / (Electron_jetRelIso().at(idx) + 1);
        pt_rel = Electron_jetPtRelv2().at(idx);
    } else if (abs(id) == 13) {
        mini_iso = Muon_miniPFRelIso_all().at(idx);
        pt_ratio = 1 / (Muon_jetRelIso().at(idx) + 1);
        pt_rel = Muon_jetPtRelv2().at(idx);
    } else {
        return false;
    }
    bool pass_mini_iso_cut = mini_iso < mini_iso_cut;
    bool pass_pt_ratio_cut = pt_ratio > pt_ratio_cut;
    bool pass_pt_rel_cut = pt_rel > pt_rel_cut;
    return (pass_mini_iso_cut && (pass_pt_ratio_cut || pass_pt_rel_cut));
}

float coneCorrPt(int id, int idx, float multiiso_minireliso, float multiiso_ptratio, float multiiso_ptrel) {
    // Isolation variables
    float miniiso = abs(id) == 11 ? Electron_miniPFRelIso_all().at(idx) : Muon_miniPFRelIso_all().at(idx);
    float ptratio = abs(id) == 11 ? 1 / (Electron_jetRelIso().at(idx) + 1) : 1 / (Muon_jetRelIso().at(idx) + 1);
    float ptrel = abs(id) == 11 ? Electron_jetPtRelv2().at(idx) : Muon_jetPtRelv2().at(idx);
    // Lepton & jet pt
    float lep_pt = abs(id) == 11 ? Electron_pt().at(idx) : Muon_pt().at(idx);
    float jet_pt = lep_pt / ptratio;
    if (ptrel > multiiso_ptrel) {
        return lep_pt * (1 + std::max(float(0), miniiso - multiiso_minireliso));
    } else {
        return std::max(lep_pt, jet_pt * multiiso_ptratio);
    }
}
