// -*- C++ -*-
// Generated with args: /hadoop/cms/store/user/sicheng/NanoAOD/mc2018_v7/ZGTo2NuG_PtG-130_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/28A39133-C103-D743-80ED-8274F3B44754.root,/hadoop/cms/store/user/sicheng/NanoAOD/mc2016_v7/ZGTo2NuG_PtG-130_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/62466AA2-182A-3746-BAFA-8D875E05BA90.root
#ifndef Nano_H
#define Nano_H
#include "Math/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include "vector"
#include "unistd.h"
#include "chrono"
#include "ctime"
#include "numeric"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > LorentzVector;
#define makeP4(Collection, idx) LorentzVector(Collection##_pt[idx],Collection##_eta[idx],Collection##_phi[idx],Collection##_mass[idx]);
#define RANGE(a, b) unsigned a=0; a<b; a++

#define NSV_MAX 39 // for SV_* collection
#define NSOFTACTIVITYJET_MAX 21 // for SoftActivityJet_* collection
#define NLHESCALEWEIGHT_MAX 10 // for LHEScaleWeight_* collection
#define NCORRT1METJET_MAX 102 // for CorrT1METJet_* collection
#define NMUON_MAX 90 // for Muon_* collection
#define NGENJET_MAX 60 // for GenJet_* collection
#define NPSWEIGHT_MAX 15 // for PSWeight_* collection
#define NLHEPART_MAX 24 // for LHEPart_* collection
#define NTAU_MAX 90 // for Tau_* collection
#define NISOTRACK_MAX 21 // for IsoTrack_* collection
#define NLHEPDFWEIGHT_MAX 10 // for LHEPdfWeight_* collection
#define NFSRPHOTON_MAX 9 // for FsrPhoton_* collection
#define NOTHERPV_MAX 12 // for OtherPV_* collection
#define NTRIGOBJ_MAX 108 // for TrigObj_* collection
#define NSUBJET_MAX 33 // for SubJet_* collection
#define NSUBGENJETAK8_MAX 42 // for SubGenJetAK8_* collection
#define NGENVISTAU_MAX 9 // for GenVisTau_* collection
#define NGENJETAK8_MAX 24 // for GenJetAK8_* collection
#define NELECTRON_MAX 90 // for Electron_* collection
#define NFATJET_MAX 18 // for FatJet_* collection
#define NJET_MAX 250 // for Jet_* collection
#define NGENISOLATEDPHOTON_MAX 12 // for GenIsolatedPhoton_* collection
#define NGENDRESSEDLEPTON_MAX 12 // for GenDressedLepton_* collection
#define NGENPART_MAX 402 // for GenPart_* collection
#define NPHOTON_MAX 24 // for Photon_* collection
#define NLHEREWEIGHTINGWEIGHT_MAX 3 // for LHEReweightingWeight_* collection
#define NLHEWEIGHT_MAX 60 // for LHEWeight_mg_reweighting collection

using namespace std;

class Nano {
private:
protected:
    unsigned int index;
    float LHEWeight_mg_reweighting_[NLHEWEIGHT_MAX];
    vector<float> v_LHEWeight_mg_reweighting_;
    TBranch *b_LHEWeight_mg_reweighting_;
    bool loaded_LHEWeight_mg_reweighting_;
    float CaloMET_phi_;
    TBranch *b_CaloMET_phi_;
    bool loaded_CaloMET_phi_;
    float CaloMET_pt_;
    TBranch *b_CaloMET_pt_;
    bool loaded_CaloMET_pt_;
    float CaloMET_sumEt_;
    TBranch *b_CaloMET_sumEt_;
    bool loaded_CaloMET_sumEt_;
    float ChsMET_phi_;
    TBranch *b_ChsMET_phi_;
    bool loaded_ChsMET_phi_;
    float ChsMET_pt_;
    TBranch *b_ChsMET_pt_;
    bool loaded_ChsMET_pt_;
    float ChsMET_sumEt_;
    TBranch *b_ChsMET_sumEt_;
    bool loaded_ChsMET_sumEt_;
    float CorrT1METJet_area_[NCORRT1METJET_MAX];
    vector<float> v_CorrT1METJet_area_;
    TBranch *b_CorrT1METJet_area_;
    bool loaded_CorrT1METJet_area_;
    float CorrT1METJet_eta_[NCORRT1METJET_MAX];
    vector<float> v_CorrT1METJet_eta_;
    TBranch *b_CorrT1METJet_eta_;
    bool loaded_CorrT1METJet_eta_;
    float CorrT1METJet_muonSubtrFactor_[NCORRT1METJET_MAX];
    vector<float> v_CorrT1METJet_muonSubtrFactor_;
    TBranch *b_CorrT1METJet_muonSubtrFactor_;
    bool loaded_CorrT1METJet_muonSubtrFactor_;
    float CorrT1METJet_phi_[NCORRT1METJET_MAX];
    vector<float> v_CorrT1METJet_phi_;
    TBranch *b_CorrT1METJet_phi_;
    bool loaded_CorrT1METJet_phi_;
    float CorrT1METJet_rawPt_[NCORRT1METJET_MAX];
    vector<float> v_CorrT1METJet_rawPt_;
    TBranch *b_CorrT1METJet_rawPt_;
    bool loaded_CorrT1METJet_rawPt_;
    int Electron_charge_[NELECTRON_MAX];
    vector<int> v_Electron_charge_;
    TBranch *b_Electron_charge_;
    bool loaded_Electron_charge_;
    UChar_t Electron_cleanmask_[NELECTRON_MAX];
    vector<UChar_t> v_Electron_cleanmask_;
    TBranch *b_Electron_cleanmask_;
    bool loaded_Electron_cleanmask_;
    bool Electron_convVeto_[NELECTRON_MAX];
    vector<bool> v_Electron_convVeto_;
    TBranch *b_Electron_convVeto_;
    bool loaded_Electron_convVeto_;
    int Electron_cutBased_[NELECTRON_MAX];
    vector<int> v_Electron_cutBased_;
    TBranch *b_Electron_cutBased_;
    bool loaded_Electron_cutBased_;
    int Electron_cutBased_Fall17_V1_[NELECTRON_MAX];
    vector<int> v_Electron_cutBased_Fall17_V1_;
    TBranch *b_Electron_cutBased_Fall17_V1_;
    bool loaded_Electron_cutBased_Fall17_V1_;
    bool Electron_cutBased_HEEP_[NELECTRON_MAX];
    vector<bool> v_Electron_cutBased_HEEP_;
    TBranch *b_Electron_cutBased_HEEP_;
    bool loaded_Electron_cutBased_HEEP_;
    int Electron_cutBased_HLTPreSel_[NELECTRON_MAX];
    vector<int> v_Electron_cutBased_HLTPreSel_;
    TBranch *b_Electron_cutBased_HLTPreSel_;
    bool loaded_Electron_cutBased_HLTPreSel_;
    int Electron_cutBased_Spring15_[NELECTRON_MAX];
    vector<int> v_Electron_cutBased_Spring15_;
    TBranch *b_Electron_cutBased_Spring15_;
    bool loaded_Electron_cutBased_Spring15_;
    int Electron_cutBased_Sum16_[NELECTRON_MAX];
    vector<int> v_Electron_cutBased_Sum16_;
    TBranch *b_Electron_cutBased_Sum16_;
    bool loaded_Electron_cutBased_Sum16_;
    float Electron_deltaEtaSC_[NELECTRON_MAX];
    vector<float> v_Electron_deltaEtaSC_;
    TBranch *b_Electron_deltaEtaSC_;
    bool loaded_Electron_deltaEtaSC_;
    float Electron_dr03EcalRecHitSumEt_[NELECTRON_MAX];
    vector<float> v_Electron_dr03EcalRecHitSumEt_;
    TBranch *b_Electron_dr03EcalRecHitSumEt_;
    bool loaded_Electron_dr03EcalRecHitSumEt_;
    float Electron_dr03HcalDepth1TowerSumEt_[NELECTRON_MAX];
    vector<float> v_Electron_dr03HcalDepth1TowerSumEt_;
    TBranch *b_Electron_dr03HcalDepth1TowerSumEt_;
    bool loaded_Electron_dr03HcalDepth1TowerSumEt_;
    float Electron_dr03TkSumPt_[NELECTRON_MAX];
    vector<float> v_Electron_dr03TkSumPt_;
    TBranch *b_Electron_dr03TkSumPt_;
    bool loaded_Electron_dr03TkSumPt_;
    float Electron_dr03TkSumPtHEEP_[NELECTRON_MAX];
    vector<float> v_Electron_dr03TkSumPtHEEP_;
    TBranch *b_Electron_dr03TkSumPtHEEP_;
    bool loaded_Electron_dr03TkSumPtHEEP_;
    float Electron_dxy_[NELECTRON_MAX];
    vector<float> v_Electron_dxy_;
    TBranch *b_Electron_dxy_;
    bool loaded_Electron_dxy_;
    float Electron_dxyErr_[NELECTRON_MAX];
    vector<float> v_Electron_dxyErr_;
    TBranch *b_Electron_dxyErr_;
    bool loaded_Electron_dxyErr_;
    float Electron_dz_[NELECTRON_MAX];
    vector<float> v_Electron_dz_;
    TBranch *b_Electron_dz_;
    bool loaded_Electron_dz_;
    float Electron_dzErr_[NELECTRON_MAX];
    vector<float> v_Electron_dzErr_;
    TBranch *b_Electron_dzErr_;
    bool loaded_Electron_dzErr_;
    float Electron_eCorr_[NELECTRON_MAX];
    vector<float> v_Electron_eCorr_;
    TBranch *b_Electron_eCorr_;
    bool loaded_Electron_eCorr_;
    float Electron_eInvMinusPInv_[NELECTRON_MAX];
    vector<float> v_Electron_eInvMinusPInv_;
    TBranch *b_Electron_eInvMinusPInv_;
    bool loaded_Electron_eInvMinusPInv_;
    float Electron_energyErr_[NELECTRON_MAX];
    vector<float> v_Electron_energyErr_;
    TBranch *b_Electron_energyErr_;
    bool loaded_Electron_energyErr_;
    float Electron_eta_[NELECTRON_MAX];
    vector<float> v_Electron_eta_;
    TBranch *b_Electron_eta_;
    bool loaded_Electron_eta_;
    UChar_t Electron_genPartFlav_[NELECTRON_MAX];
    vector<UChar_t> v_Electron_genPartFlav_;
    TBranch *b_Electron_genPartFlav_;
    bool loaded_Electron_genPartFlav_;
    int Electron_genPartIdx_[NELECTRON_MAX];
    vector<int> v_Electron_genPartIdx_;
    TBranch *b_Electron_genPartIdx_;
    bool loaded_Electron_genPartIdx_;
    float Electron_hoe_[NELECTRON_MAX];
    vector<float> v_Electron_hoe_;
    TBranch *b_Electron_hoe_;
    bool loaded_Electron_hoe_;
    float Electron_ip3d_[NELECTRON_MAX];
    vector<float> v_Electron_ip3d_;
    TBranch *b_Electron_ip3d_;
    bool loaded_Electron_ip3d_;
    bool Electron_isPFcand_[NELECTRON_MAX];
    vector<bool> v_Electron_isPFcand_;
    TBranch *b_Electron_isPFcand_;
    bool loaded_Electron_isPFcand_;
    int Electron_jetIdx_[NELECTRON_MAX];
    vector<int> v_Electron_jetIdx_;
    TBranch *b_Electron_jetIdx_;
    bool loaded_Electron_jetIdx_;
    float Electron_jetPtRelv2_[NELECTRON_MAX];
    vector<float> v_Electron_jetPtRelv2_;
    TBranch *b_Electron_jetPtRelv2_;
    bool loaded_Electron_jetPtRelv2_;
    float Electron_jetRelIso_[NELECTRON_MAX];
    vector<float> v_Electron_jetRelIso_;
    TBranch *b_Electron_jetRelIso_;
    bool loaded_Electron_jetRelIso_;
    UChar_t Electron_lostHits_[NELECTRON_MAX];
    vector<UChar_t> v_Electron_lostHits_;
    TBranch *b_Electron_lostHits_;
    bool loaded_Electron_lostHits_;
    float Electron_mass_[NELECTRON_MAX];
    vector<float> v_Electron_mass_;
    TBranch *b_Electron_mass_;
    bool loaded_Electron_mass_;
    float Electron_miniPFRelIso_all_[NELECTRON_MAX];
    vector<float> v_Electron_miniPFRelIso_all_;
    TBranch *b_Electron_miniPFRelIso_all_;
    bool loaded_Electron_miniPFRelIso_all_;
    float Electron_miniPFRelIso_chg_[NELECTRON_MAX];
    vector<float> v_Electron_miniPFRelIso_chg_;
    TBranch *b_Electron_miniPFRelIso_chg_;
    bool loaded_Electron_miniPFRelIso_chg_;
    float Electron_mvaFall17V1Iso_[NELECTRON_MAX];
    vector<float> v_Electron_mvaFall17V1Iso_;
    TBranch *b_Electron_mvaFall17V1Iso_;
    bool loaded_Electron_mvaFall17V1Iso_;
    bool Electron_mvaFall17V1Iso_WP80_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V1Iso_WP80_;
    TBranch *b_Electron_mvaFall17V1Iso_WP80_;
    bool loaded_Electron_mvaFall17V1Iso_WP80_;
    bool Electron_mvaFall17V1Iso_WP90_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V1Iso_WP90_;
    TBranch *b_Electron_mvaFall17V1Iso_WP90_;
    bool loaded_Electron_mvaFall17V1Iso_WP90_;
    bool Electron_mvaFall17V1Iso_WPL_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V1Iso_WPL_;
    TBranch *b_Electron_mvaFall17V1Iso_WPL_;
    bool loaded_Electron_mvaFall17V1Iso_WPL_;
    float Electron_mvaFall17V1noIso_[NELECTRON_MAX];
    vector<float> v_Electron_mvaFall17V1noIso_;
    TBranch *b_Electron_mvaFall17V1noIso_;
    bool loaded_Electron_mvaFall17V1noIso_;
    bool Electron_mvaFall17V1noIso_WP80_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V1noIso_WP80_;
    TBranch *b_Electron_mvaFall17V1noIso_WP80_;
    bool loaded_Electron_mvaFall17V1noIso_WP80_;
    bool Electron_mvaFall17V1noIso_WP90_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V1noIso_WP90_;
    TBranch *b_Electron_mvaFall17V1noIso_WP90_;
    bool loaded_Electron_mvaFall17V1noIso_WP90_;
    bool Electron_mvaFall17V1noIso_WPL_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V1noIso_WPL_;
    TBranch *b_Electron_mvaFall17V1noIso_WPL_;
    bool loaded_Electron_mvaFall17V1noIso_WPL_;
    float Electron_mvaFall17V2Iso_[NELECTRON_MAX];
    vector<float> v_Electron_mvaFall17V2Iso_;
    TBranch *b_Electron_mvaFall17V2Iso_;
    bool loaded_Electron_mvaFall17V2Iso_;
    bool Electron_mvaFall17V2Iso_WP80_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V2Iso_WP80_;
    TBranch *b_Electron_mvaFall17V2Iso_WP80_;
    bool loaded_Electron_mvaFall17V2Iso_WP80_;
    bool Electron_mvaFall17V2Iso_WP90_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V2Iso_WP90_;
    TBranch *b_Electron_mvaFall17V2Iso_WP90_;
    bool loaded_Electron_mvaFall17V2Iso_WP90_;
    bool Electron_mvaFall17V2Iso_WPL_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V2Iso_WPL_;
    TBranch *b_Electron_mvaFall17V2Iso_WPL_;
    bool loaded_Electron_mvaFall17V2Iso_WPL_;
    float Electron_mvaFall17V2noIso_[NELECTRON_MAX];
    vector<float> v_Electron_mvaFall17V2noIso_;
    TBranch *b_Electron_mvaFall17V2noIso_;
    bool loaded_Electron_mvaFall17V2noIso_;
    bool Electron_mvaFall17V2noIso_WP80_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V2noIso_WP80_;
    TBranch *b_Electron_mvaFall17V2noIso_WP80_;
    bool loaded_Electron_mvaFall17V2noIso_WP80_;
    bool Electron_mvaFall17V2noIso_WP90_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V2noIso_WP90_;
    TBranch *b_Electron_mvaFall17V2noIso_WP90_;
    bool loaded_Electron_mvaFall17V2noIso_WP90_;
    bool Electron_mvaFall17V2noIso_WPL_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaFall17V2noIso_WPL_;
    TBranch *b_Electron_mvaFall17V2noIso_WPL_;
    bool loaded_Electron_mvaFall17V2noIso_WPL_;
    float Electron_mvaSpring16GP_[NELECTRON_MAX];
    vector<float> v_Electron_mvaSpring16GP_;
    TBranch *b_Electron_mvaSpring16GP_;
    bool loaded_Electron_mvaSpring16GP_;
    bool Electron_mvaSpring16GP_WP80_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaSpring16GP_WP80_;
    TBranch *b_Electron_mvaSpring16GP_WP80_;
    bool loaded_Electron_mvaSpring16GP_WP80_;
    bool Electron_mvaSpring16GP_WP90_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaSpring16GP_WP90_;
    TBranch *b_Electron_mvaSpring16GP_WP90_;
    bool loaded_Electron_mvaSpring16GP_WP90_;
    float Electron_mvaSpring16HZZ_[NELECTRON_MAX];
    vector<float> v_Electron_mvaSpring16HZZ_;
    TBranch *b_Electron_mvaSpring16HZZ_;
    bool loaded_Electron_mvaSpring16HZZ_;
    bool Electron_mvaSpring16HZZ_WPL_[NELECTRON_MAX];
    vector<bool> v_Electron_mvaSpring16HZZ_WPL_;
    TBranch *b_Electron_mvaSpring16HZZ_WPL_;
    bool loaded_Electron_mvaSpring16HZZ_WPL_;
    float Electron_mvaTTH_[NELECTRON_MAX];
    vector<float> v_Electron_mvaTTH_;
    TBranch *b_Electron_mvaTTH_;
    bool loaded_Electron_mvaTTH_;
    vector<LorentzVector> v_Electron_p4_;
    TBranch *b_Electron_p4_;
    bool loaded_Electron_p4_;
    int Electron_pdgId_[NELECTRON_MAX];
    vector<int> v_Electron_pdgId_;
    TBranch *b_Electron_pdgId_;
    bool loaded_Electron_pdgId_;
    float Electron_pfRelIso03_all_[NELECTRON_MAX];
    vector<float> v_Electron_pfRelIso03_all_;
    TBranch *b_Electron_pfRelIso03_all_;
    bool loaded_Electron_pfRelIso03_all_;
    float Electron_pfRelIso03_chg_[NELECTRON_MAX];
    vector<float> v_Electron_pfRelIso03_chg_;
    TBranch *b_Electron_pfRelIso03_chg_;
    bool loaded_Electron_pfRelIso03_chg_;
    float Electron_phi_[NELECTRON_MAX];
    vector<float> v_Electron_phi_;
    TBranch *b_Electron_phi_;
    bool loaded_Electron_phi_;
    int Electron_photonIdx_[NELECTRON_MAX];
    vector<int> v_Electron_photonIdx_;
    TBranch *b_Electron_photonIdx_;
    bool loaded_Electron_photonIdx_;
    float Electron_pt_[NELECTRON_MAX];
    vector<float> v_Electron_pt_;
    TBranch *b_Electron_pt_;
    bool loaded_Electron_pt_;
    float Electron_r9_[NELECTRON_MAX];
    vector<float> v_Electron_r9_;
    TBranch *b_Electron_r9_;
    bool loaded_Electron_r9_;
    float Electron_scEtOverPt_[NELECTRON_MAX];
    vector<float> v_Electron_scEtOverPt_;
    TBranch *b_Electron_scEtOverPt_;
    bool loaded_Electron_scEtOverPt_;
    UChar_t Electron_seedGain_[NELECTRON_MAX];
    vector<UChar_t> v_Electron_seedGain_;
    TBranch *b_Electron_seedGain_;
    bool loaded_Electron_seedGain_;
    float Electron_sieie_[NELECTRON_MAX];
    vector<float> v_Electron_sieie_;
    TBranch *b_Electron_sieie_;
    bool loaded_Electron_sieie_;
    float Electron_sip3d_[NELECTRON_MAX];
    vector<float> v_Electron_sip3d_;
    TBranch *b_Electron_sip3d_;
    bool loaded_Electron_sip3d_;
    int Electron_tightCharge_[NELECTRON_MAX];
    vector<int> v_Electron_tightCharge_;
    TBranch *b_Electron_tightCharge_;
    bool loaded_Electron_tightCharge_;
    int Electron_vidNestedWPBitmap_[NELECTRON_MAX];
    vector<int> v_Electron_vidNestedWPBitmap_;
    TBranch *b_Electron_vidNestedWPBitmap_;
    bool loaded_Electron_vidNestedWPBitmap_;
    int Electron_vidNestedWPBitmapHEEP_[NELECTRON_MAX];
    vector<int> v_Electron_vidNestedWPBitmapHEEP_;
    TBranch *b_Electron_vidNestedWPBitmapHEEP_;
    bool loaded_Electron_vidNestedWPBitmapHEEP_;
    int Electron_vidNestedWPBitmapSpring15_[NELECTRON_MAX];
    vector<int> v_Electron_vidNestedWPBitmapSpring15_;
    TBranch *b_Electron_vidNestedWPBitmapSpring15_;
    bool loaded_Electron_vidNestedWPBitmapSpring15_;
    int Electron_vidNestedWPBitmapSum16_[NELECTRON_MAX];
    vector<int> v_Electron_vidNestedWPBitmapSum16_;
    TBranch *b_Electron_vidNestedWPBitmapSum16_;
    bool loaded_Electron_vidNestedWPBitmapSum16_;
    float FatJet_area_[NFATJET_MAX];
    vector<float> v_FatJet_area_;
    TBranch *b_FatJet_area_;
    bool loaded_FatJet_area_;
    float FatJet_btagCMVA_[NFATJET_MAX];
    vector<float> v_FatJet_btagCMVA_;
    TBranch *b_FatJet_btagCMVA_;
    bool loaded_FatJet_btagCMVA_;
    float FatJet_btagCSVV2_[NFATJET_MAX];
    vector<float> v_FatJet_btagCSVV2_;
    TBranch *b_FatJet_btagCSVV2_;
    bool loaded_FatJet_btagCSVV2_;
    float FatJet_btagDDBvL_[NFATJET_MAX];
    vector<float> v_FatJet_btagDDBvL_;
    TBranch *b_FatJet_btagDDBvL_;
    bool loaded_FatJet_btagDDBvL_;
    float FatJet_btagDDBvL_noMD_[NFATJET_MAX];
    vector<float> v_FatJet_btagDDBvL_noMD_;
    TBranch *b_FatJet_btagDDBvL_noMD_;
    bool loaded_FatJet_btagDDBvL_noMD_;
    float FatJet_btagDDCvB_[NFATJET_MAX];
    vector<float> v_FatJet_btagDDCvB_;
    TBranch *b_FatJet_btagDDCvB_;
    bool loaded_FatJet_btagDDCvB_;
    float FatJet_btagDDCvB_noMD_[NFATJET_MAX];
    vector<float> v_FatJet_btagDDCvB_noMD_;
    TBranch *b_FatJet_btagDDCvB_noMD_;
    bool loaded_FatJet_btagDDCvB_noMD_;
    float FatJet_btagDDCvL_[NFATJET_MAX];
    vector<float> v_FatJet_btagDDCvL_;
    TBranch *b_FatJet_btagDDCvL_;
    bool loaded_FatJet_btagDDCvL_;
    float FatJet_btagDDCvL_noMD_[NFATJET_MAX];
    vector<float> v_FatJet_btagDDCvL_noMD_;
    TBranch *b_FatJet_btagDDCvL_noMD_;
    bool loaded_FatJet_btagDDCvL_noMD_;
    float FatJet_btagDeepB_[NFATJET_MAX];
    vector<float> v_FatJet_btagDeepB_;
    TBranch *b_FatJet_btagDeepB_;
    bool loaded_FatJet_btagDeepB_;
    float FatJet_btagHbb_[NFATJET_MAX];
    vector<float> v_FatJet_btagHbb_;
    TBranch *b_FatJet_btagHbb_;
    bool loaded_FatJet_btagHbb_;
    float FatJet_deepTagMD_H4qvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_H4qvsQCD_;
    TBranch *b_FatJet_deepTagMD_H4qvsQCD_;
    bool loaded_FatJet_deepTagMD_H4qvsQCD_;
    float FatJet_deepTagMD_HbbvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_HbbvsQCD_;
    TBranch *b_FatJet_deepTagMD_HbbvsQCD_;
    bool loaded_FatJet_deepTagMD_HbbvsQCD_;
    float FatJet_deepTagMD_TvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_TvsQCD_;
    TBranch *b_FatJet_deepTagMD_TvsQCD_;
    bool loaded_FatJet_deepTagMD_TvsQCD_;
    float FatJet_deepTagMD_WvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_WvsQCD_;
    TBranch *b_FatJet_deepTagMD_WvsQCD_;
    bool loaded_FatJet_deepTagMD_WvsQCD_;
    float FatJet_deepTagMD_ZHbbvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_ZHbbvsQCD_;
    TBranch *b_FatJet_deepTagMD_ZHbbvsQCD_;
    bool loaded_FatJet_deepTagMD_ZHbbvsQCD_;
    float FatJet_deepTagMD_ZHccvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_ZHccvsQCD_;
    TBranch *b_FatJet_deepTagMD_ZHccvsQCD_;
    bool loaded_FatJet_deepTagMD_ZHccvsQCD_;
    float FatJet_deepTagMD_ZbbvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_ZbbvsQCD_;
    TBranch *b_FatJet_deepTagMD_ZbbvsQCD_;
    bool loaded_FatJet_deepTagMD_ZbbvsQCD_;
    float FatJet_deepTagMD_ZvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_ZvsQCD_;
    TBranch *b_FatJet_deepTagMD_ZvsQCD_;
    bool loaded_FatJet_deepTagMD_ZvsQCD_;
    float FatJet_deepTagMD_bbvsLight_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_bbvsLight_;
    TBranch *b_FatJet_deepTagMD_bbvsLight_;
    bool loaded_FatJet_deepTagMD_bbvsLight_;
    float FatJet_deepTagMD_ccvsLight_[NFATJET_MAX];
    vector<float> v_FatJet_deepTagMD_ccvsLight_;
    TBranch *b_FatJet_deepTagMD_ccvsLight_;
    bool loaded_FatJet_deepTagMD_ccvsLight_;
    float FatJet_deepTag_H_[NFATJET_MAX];
    vector<float> v_FatJet_deepTag_H_;
    TBranch *b_FatJet_deepTag_H_;
    bool loaded_FatJet_deepTag_H_;
    float FatJet_deepTag_QCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTag_QCD_;
    TBranch *b_FatJet_deepTag_QCD_;
    bool loaded_FatJet_deepTag_QCD_;
    float FatJet_deepTag_QCDothers_[NFATJET_MAX];
    vector<float> v_FatJet_deepTag_QCDothers_;
    TBranch *b_FatJet_deepTag_QCDothers_;
    bool loaded_FatJet_deepTag_QCDothers_;
    float FatJet_deepTag_TvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTag_TvsQCD_;
    TBranch *b_FatJet_deepTag_TvsQCD_;
    bool loaded_FatJet_deepTag_TvsQCD_;
    float FatJet_deepTag_WvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTag_WvsQCD_;
    TBranch *b_FatJet_deepTag_WvsQCD_;
    bool loaded_FatJet_deepTag_WvsQCD_;
    float FatJet_deepTag_ZvsQCD_[NFATJET_MAX];
    vector<float> v_FatJet_deepTag_ZvsQCD_;
    TBranch *b_FatJet_deepTag_ZvsQCD_;
    bool loaded_FatJet_deepTag_ZvsQCD_;
    int FatJet_electronIdx3SJ_[NFATJET_MAX];
    vector<int> v_FatJet_electronIdx3SJ_;
    TBranch *b_FatJet_electronIdx3SJ_;
    bool loaded_FatJet_electronIdx3SJ_;
    float FatJet_eta_[NFATJET_MAX];
    vector<float> v_FatJet_eta_;
    TBranch *b_FatJet_eta_;
    bool loaded_FatJet_eta_;
    int FatJet_genJetAK8Idx_[NFATJET_MAX];
    vector<int> v_FatJet_genJetAK8Idx_;
    TBranch *b_FatJet_genJetAK8Idx_;
    bool loaded_FatJet_genJetAK8Idx_;
    int FatJet_hadronFlavour_[NFATJET_MAX];
    vector<int> v_FatJet_hadronFlavour_;
    TBranch *b_FatJet_hadronFlavour_;
    bool loaded_FatJet_hadronFlavour_;
    int FatJet_jetId_[NFATJET_MAX];
    vector<int> v_FatJet_jetId_;
    TBranch *b_FatJet_jetId_;
    bool loaded_FatJet_jetId_;
    float FatJet_lsf3_[NFATJET_MAX];
    vector<float> v_FatJet_lsf3_;
    TBranch *b_FatJet_lsf3_;
    bool loaded_FatJet_lsf3_;
    float FatJet_mass_[NFATJET_MAX];
    vector<float> v_FatJet_mass_;
    TBranch *b_FatJet_mass_;
    bool loaded_FatJet_mass_;
    float FatJet_msoftdrop_[NFATJET_MAX];
    vector<float> v_FatJet_msoftdrop_;
    TBranch *b_FatJet_msoftdrop_;
    bool loaded_FatJet_msoftdrop_;
    int FatJet_muonIdx3SJ_[NFATJET_MAX];
    vector<int> v_FatJet_muonIdx3SJ_;
    TBranch *b_FatJet_muonIdx3SJ_;
    bool loaded_FatJet_muonIdx3SJ_;
    float FatJet_n2b1_[NFATJET_MAX];
    vector<float> v_FatJet_n2b1_;
    TBranch *b_FatJet_n2b1_;
    bool loaded_FatJet_n2b1_;
    float FatJet_n3b1_[NFATJET_MAX];
    vector<float> v_FatJet_n3b1_;
    TBranch *b_FatJet_n3b1_;
    bool loaded_FatJet_n3b1_;
    UChar_t FatJet_nBHadrons_[NFATJET_MAX];
    vector<UChar_t> v_FatJet_nBHadrons_;
    TBranch *b_FatJet_nBHadrons_;
    bool loaded_FatJet_nBHadrons_;
    UChar_t FatJet_nCHadrons_[NFATJET_MAX];
    vector<UChar_t> v_FatJet_nCHadrons_;
    TBranch *b_FatJet_nCHadrons_;
    bool loaded_FatJet_nCHadrons_;
    vector<LorentzVector> v_FatJet_p4_;
    TBranch *b_FatJet_p4_;
    bool loaded_FatJet_p4_;
    float FatJet_phi_[NFATJET_MAX];
    vector<float> v_FatJet_phi_;
    TBranch *b_FatJet_phi_;
    bool loaded_FatJet_phi_;
    float FatJet_pt_[NFATJET_MAX];
    vector<float> v_FatJet_pt_;
    TBranch *b_FatJet_pt_;
    bool loaded_FatJet_pt_;
    float FatJet_rawFactor_[NFATJET_MAX];
    vector<float> v_FatJet_rawFactor_;
    TBranch *b_FatJet_rawFactor_;
    bool loaded_FatJet_rawFactor_;
    int FatJet_subJetIdx1_[NFATJET_MAX];
    vector<int> v_FatJet_subJetIdx1_;
    TBranch *b_FatJet_subJetIdx1_;
    bool loaded_FatJet_subJetIdx1_;
    int FatJet_subJetIdx2_[NFATJET_MAX];
    vector<int> v_FatJet_subJetIdx2_;
    TBranch *b_FatJet_subJetIdx2_;
    bool loaded_FatJet_subJetIdx2_;
    float FatJet_tau1_[NFATJET_MAX];
    vector<float> v_FatJet_tau1_;
    TBranch *b_FatJet_tau1_;
    bool loaded_FatJet_tau1_;
    float FatJet_tau2_[NFATJET_MAX];
    vector<float> v_FatJet_tau2_;
    TBranch *b_FatJet_tau2_;
    bool loaded_FatJet_tau2_;
    float FatJet_tau3_[NFATJET_MAX];
    vector<float> v_FatJet_tau3_;
    TBranch *b_FatJet_tau3_;
    bool loaded_FatJet_tau3_;
    float FatJet_tau4_[NFATJET_MAX];
    vector<float> v_FatJet_tau4_;
    TBranch *b_FatJet_tau4_;
    bool loaded_FatJet_tau4_;
    bool Flag_BadChargedCandidateFilter_;
    TBranch *b_Flag_BadChargedCandidateFilter_;
    bool loaded_Flag_BadChargedCandidateFilter_;
    bool Flag_BadChargedCandidateSummer16Filter_;
    TBranch *b_Flag_BadChargedCandidateSummer16Filter_;
    bool loaded_Flag_BadChargedCandidateSummer16Filter_;
    bool Flag_BadPFMuonFilter_;
    TBranch *b_Flag_BadPFMuonFilter_;
    bool loaded_Flag_BadPFMuonFilter_;
    bool Flag_BadPFMuonSummer16Filter_;
    TBranch *b_Flag_BadPFMuonSummer16Filter_;
    bool loaded_Flag_BadPFMuonSummer16Filter_;
    bool Flag_CSCTightHalo2015Filter_;
    TBranch *b_Flag_CSCTightHalo2015Filter_;
    bool loaded_Flag_CSCTightHalo2015Filter_;
    bool Flag_CSCTightHaloFilter_;
    TBranch *b_Flag_CSCTightHaloFilter_;
    bool loaded_Flag_CSCTightHaloFilter_;
    bool Flag_CSCTightHaloTrkMuUnvetoFilter_;
    TBranch *b_Flag_CSCTightHaloTrkMuUnvetoFilter_;
    bool loaded_Flag_CSCTightHaloTrkMuUnvetoFilter_;
    bool Flag_EcalDeadCellBoundaryEnergyFilter_;
    TBranch *b_Flag_EcalDeadCellBoundaryEnergyFilter_;
    bool loaded_Flag_EcalDeadCellBoundaryEnergyFilter_;
    bool Flag_EcalDeadCellTriggerPrimitiveFilter_;
    TBranch *b_Flag_EcalDeadCellTriggerPrimitiveFilter_;
    bool loaded_Flag_EcalDeadCellTriggerPrimitiveFilter_;
    bool Flag_HBHENoiseFilter_;
    TBranch *b_Flag_HBHENoiseFilter_;
    bool loaded_Flag_HBHENoiseFilter_;
    bool Flag_HBHENoiseIsoFilter_;
    TBranch *b_Flag_HBHENoiseIsoFilter_;
    bool loaded_Flag_HBHENoiseIsoFilter_;
    bool Flag_HcalStripHaloFilter_;
    TBranch *b_Flag_HcalStripHaloFilter_;
    bool loaded_Flag_HcalStripHaloFilter_;
    bool Flag_METFilters_;
    TBranch *b_Flag_METFilters_;
    bool loaded_Flag_METFilters_;
    bool Flag_chargedHadronTrackResolutionFilter_;
    TBranch *b_Flag_chargedHadronTrackResolutionFilter_;
    bool loaded_Flag_chargedHadronTrackResolutionFilter_;
    bool Flag_ecalBadCalibFilter_;
    TBranch *b_Flag_ecalBadCalibFilter_;
    bool loaded_Flag_ecalBadCalibFilter_;
    bool Flag_ecalBadCalibFilterV2_;
    TBranch *b_Flag_ecalBadCalibFilterV2_;
    bool loaded_Flag_ecalBadCalibFilterV2_;
    bool Flag_ecalLaserCorrFilter_;
    TBranch *b_Flag_ecalLaserCorrFilter_;
    bool loaded_Flag_ecalLaserCorrFilter_;
    bool Flag_eeBadScFilter_;
    TBranch *b_Flag_eeBadScFilter_;
    bool loaded_Flag_eeBadScFilter_;
    bool Flag_globalSuperTightHalo2016Filter_;
    TBranch *b_Flag_globalSuperTightHalo2016Filter_;
    bool loaded_Flag_globalSuperTightHalo2016Filter_;
    bool Flag_globalTightHalo2016Filter_;
    TBranch *b_Flag_globalTightHalo2016Filter_;
    bool loaded_Flag_globalTightHalo2016Filter_;
    bool Flag_goodVertices_;
    TBranch *b_Flag_goodVertices_;
    bool loaded_Flag_goodVertices_;
    bool Flag_hcalLaserEventFilter_;
    TBranch *b_Flag_hcalLaserEventFilter_;
    bool loaded_Flag_hcalLaserEventFilter_;
    bool Flag_muonBadTrackFilter_;
    TBranch *b_Flag_muonBadTrackFilter_;
    bool loaded_Flag_muonBadTrackFilter_;
    bool Flag_trkPOGFilters_;
    TBranch *b_Flag_trkPOGFilters_;
    bool loaded_Flag_trkPOGFilters_;
    bool Flag_trkPOG_logErrorTooManyClusters_;
    TBranch *b_Flag_trkPOG_logErrorTooManyClusters_;
    bool loaded_Flag_trkPOG_logErrorTooManyClusters_;
    bool Flag_trkPOG_manystripclus53X_;
    TBranch *b_Flag_trkPOG_manystripclus53X_;
    bool loaded_Flag_trkPOG_manystripclus53X_;
    bool Flag_trkPOG_toomanystripclus53X_;
    TBranch *b_Flag_trkPOG_toomanystripclus53X_;
    bool loaded_Flag_trkPOG_toomanystripclus53X_;
    float FsrPhoton_dROverEt2_[NFSRPHOTON_MAX];
    vector<float> v_FsrPhoton_dROverEt2_;
    TBranch *b_FsrPhoton_dROverEt2_;
    bool loaded_FsrPhoton_dROverEt2_;
    float FsrPhoton_eta_[NFSRPHOTON_MAX];
    vector<float> v_FsrPhoton_eta_;
    TBranch *b_FsrPhoton_eta_;
    bool loaded_FsrPhoton_eta_;
    int FsrPhoton_muonIdx_[NFSRPHOTON_MAX];
    vector<int> v_FsrPhoton_muonIdx_;
    TBranch *b_FsrPhoton_muonIdx_;
    bool loaded_FsrPhoton_muonIdx_;
    float FsrPhoton_phi_[NFSRPHOTON_MAX];
    vector<float> v_FsrPhoton_phi_;
    TBranch *b_FsrPhoton_phi_;
    bool loaded_FsrPhoton_phi_;
    float FsrPhoton_pt_[NFSRPHOTON_MAX];
    vector<float> v_FsrPhoton_pt_;
    TBranch *b_FsrPhoton_pt_;
    bool loaded_FsrPhoton_pt_;
    float FsrPhoton_relIso03_[NFSRPHOTON_MAX];
    vector<float> v_FsrPhoton_relIso03_;
    TBranch *b_FsrPhoton_relIso03_;
    bool loaded_FsrPhoton_relIso03_;
    float GenDressedLepton_eta_[NGENDRESSEDLEPTON_MAX];
    vector<float> v_GenDressedLepton_eta_;
    TBranch *b_GenDressedLepton_eta_;
    bool loaded_GenDressedLepton_eta_;
    bool GenDressedLepton_hasTauAnc_[NGENDRESSEDLEPTON_MAX];
    vector<bool> v_GenDressedLepton_hasTauAnc_;
    TBranch *b_GenDressedLepton_hasTauAnc_;
    bool loaded_GenDressedLepton_hasTauAnc_;
    float GenDressedLepton_mass_[NGENDRESSEDLEPTON_MAX];
    vector<float> v_GenDressedLepton_mass_;
    TBranch *b_GenDressedLepton_mass_;
    bool loaded_GenDressedLepton_mass_;
    vector<LorentzVector> v_GenDressedLepton_p4_;
    TBranch *b_GenDressedLepton_p4_;
    bool loaded_GenDressedLepton_p4_;
    int GenDressedLepton_pdgId_[NGENDRESSEDLEPTON_MAX];
    vector<int> v_GenDressedLepton_pdgId_;
    TBranch *b_GenDressedLepton_pdgId_;
    bool loaded_GenDressedLepton_pdgId_;
    float GenDressedLepton_phi_[NGENDRESSEDLEPTON_MAX];
    vector<float> v_GenDressedLepton_phi_;
    TBranch *b_GenDressedLepton_phi_;
    bool loaded_GenDressedLepton_phi_;
    float GenDressedLepton_pt_[NGENDRESSEDLEPTON_MAX];
    vector<float> v_GenDressedLepton_pt_;
    TBranch *b_GenDressedLepton_pt_;
    bool loaded_GenDressedLepton_pt_;
    float GenIsolatedPhoton_eta_[NGENISOLATEDPHOTON_MAX];
    vector<float> v_GenIsolatedPhoton_eta_;
    TBranch *b_GenIsolatedPhoton_eta_;
    bool loaded_GenIsolatedPhoton_eta_;
    float GenIsolatedPhoton_mass_[NGENISOLATEDPHOTON_MAX];
    vector<float> v_GenIsolatedPhoton_mass_;
    TBranch *b_GenIsolatedPhoton_mass_;
    bool loaded_GenIsolatedPhoton_mass_;
    vector<LorentzVector> v_GenIsolatedPhoton_p4_;
    TBranch *b_GenIsolatedPhoton_p4_;
    bool loaded_GenIsolatedPhoton_p4_;
    float GenIsolatedPhoton_phi_[NGENISOLATEDPHOTON_MAX];
    vector<float> v_GenIsolatedPhoton_phi_;
    TBranch *b_GenIsolatedPhoton_phi_;
    bool loaded_GenIsolatedPhoton_phi_;
    float GenIsolatedPhoton_pt_[NGENISOLATEDPHOTON_MAX];
    vector<float> v_GenIsolatedPhoton_pt_;
    TBranch *b_GenIsolatedPhoton_pt_;
    bool loaded_GenIsolatedPhoton_pt_;
    float GenJetAK8_eta_[NGENJETAK8_MAX];
    vector<float> v_GenJetAK8_eta_;
    TBranch *b_GenJetAK8_eta_;
    bool loaded_GenJetAK8_eta_;
    UChar_t GenJetAK8_hadronFlavour_[NGENJETAK8_MAX];
    vector<UChar_t> v_GenJetAK8_hadronFlavour_;
    TBranch *b_GenJetAK8_hadronFlavour_;
    bool loaded_GenJetAK8_hadronFlavour_;
    float GenJetAK8_mass_[NGENJETAK8_MAX];
    vector<float> v_GenJetAK8_mass_;
    TBranch *b_GenJetAK8_mass_;
    bool loaded_GenJetAK8_mass_;
    vector<LorentzVector> v_GenJetAK8_p4_;
    TBranch *b_GenJetAK8_p4_;
    bool loaded_GenJetAK8_p4_;
    int GenJetAK8_partonFlavour_[NGENJETAK8_MAX];
    vector<int> v_GenJetAK8_partonFlavour_;
    TBranch *b_GenJetAK8_partonFlavour_;
    bool loaded_GenJetAK8_partonFlavour_;
    float GenJetAK8_phi_[NGENJETAK8_MAX];
    vector<float> v_GenJetAK8_phi_;
    TBranch *b_GenJetAK8_phi_;
    bool loaded_GenJetAK8_phi_;
    float GenJetAK8_pt_[NGENJETAK8_MAX];
    vector<float> v_GenJetAK8_pt_;
    TBranch *b_GenJetAK8_pt_;
    bool loaded_GenJetAK8_pt_;
    float GenJet_eta_[NGENJET_MAX];
    vector<float> v_GenJet_eta_;
    TBranch *b_GenJet_eta_;
    bool loaded_GenJet_eta_;
    UChar_t GenJet_hadronFlavour_[NGENJET_MAX];
    vector<UChar_t> v_GenJet_hadronFlavour_;
    TBranch *b_GenJet_hadronFlavour_;
    bool loaded_GenJet_hadronFlavour_;
    float GenJet_mass_[NGENJET_MAX];
    vector<float> v_GenJet_mass_;
    TBranch *b_GenJet_mass_;
    bool loaded_GenJet_mass_;
    vector<LorentzVector> v_GenJet_p4_;
    TBranch *b_GenJet_p4_;
    bool loaded_GenJet_p4_;
    int GenJet_partonFlavour_[NGENJET_MAX];
    vector<int> v_GenJet_partonFlavour_;
    TBranch *b_GenJet_partonFlavour_;
    bool loaded_GenJet_partonFlavour_;
    float GenJet_phi_[NGENJET_MAX];
    vector<float> v_GenJet_phi_;
    TBranch *b_GenJet_phi_;
    bool loaded_GenJet_phi_;
    float GenJet_pt_[NGENJET_MAX];
    vector<float> v_GenJet_pt_;
    TBranch *b_GenJet_pt_;
    bool loaded_GenJet_pt_;
    float GenMET_phi_;
    TBranch *b_GenMET_phi_;
    bool loaded_GenMET_phi_;
    float GenMET_pt_;
    TBranch *b_GenMET_pt_;
    bool loaded_GenMET_pt_;
    float GenPart_eta_[NGENPART_MAX];
    vector<float> v_GenPart_eta_;
    TBranch *b_GenPart_eta_;
    bool loaded_GenPart_eta_;
    int GenPart_genPartIdxMother_[NGENPART_MAX];
    vector<int> v_GenPart_genPartIdxMother_;
    TBranch *b_GenPart_genPartIdxMother_;
    bool loaded_GenPart_genPartIdxMother_;
    float GenPart_mass_[NGENPART_MAX];
    vector<float> v_GenPart_mass_;
    TBranch *b_GenPart_mass_;
    bool loaded_GenPart_mass_;
    vector<LorentzVector> v_GenPart_p4_;
    TBranch *b_GenPart_p4_;
    bool loaded_GenPart_p4_;
    int GenPart_pdgId_[NGENPART_MAX];
    vector<int> v_GenPart_pdgId_;
    TBranch *b_GenPart_pdgId_;
    bool loaded_GenPart_pdgId_;
    float GenPart_phi_[NGENPART_MAX];
    vector<float> v_GenPart_phi_;
    TBranch *b_GenPart_phi_;
    bool loaded_GenPart_phi_;
    float GenPart_pt_[NGENPART_MAX];
    vector<float> v_GenPart_pt_;
    TBranch *b_GenPart_pt_;
    bool loaded_GenPart_pt_;
    int GenPart_status_[NGENPART_MAX];
    vector<int> v_GenPart_status_;
    TBranch *b_GenPart_status_;
    bool loaded_GenPart_status_;
    int GenPart_statusFlags_[NGENPART_MAX];
    vector<int> v_GenPart_statusFlags_;
    TBranch *b_GenPart_statusFlags_;
    bool loaded_GenPart_statusFlags_;
    int GenVisTau_charge_[NGENVISTAU_MAX];
    vector<int> v_GenVisTau_charge_;
    TBranch *b_GenVisTau_charge_;
    bool loaded_GenVisTau_charge_;
    float GenVisTau_eta_[NGENVISTAU_MAX];
    vector<float> v_GenVisTau_eta_;
    TBranch *b_GenVisTau_eta_;
    bool loaded_GenVisTau_eta_;
    int GenVisTau_genPartIdxMother_[NGENVISTAU_MAX];
    vector<int> v_GenVisTau_genPartIdxMother_;
    TBranch *b_GenVisTau_genPartIdxMother_;
    bool loaded_GenVisTau_genPartIdxMother_;
    float GenVisTau_mass_[NGENVISTAU_MAX];
    vector<float> v_GenVisTau_mass_;
    TBranch *b_GenVisTau_mass_;
    bool loaded_GenVisTau_mass_;
    vector<LorentzVector> v_GenVisTau_p4_;
    TBranch *b_GenVisTau_p4_;
    bool loaded_GenVisTau_p4_;
    float GenVisTau_phi_[NGENVISTAU_MAX];
    vector<float> v_GenVisTau_phi_;
    TBranch *b_GenVisTau_phi_;
    bool loaded_GenVisTau_phi_;
    float GenVisTau_pt_[NGENVISTAU_MAX];
    vector<float> v_GenVisTau_pt_;
    TBranch *b_GenVisTau_pt_;
    bool loaded_GenVisTau_pt_;
    int GenVisTau_status_[NGENVISTAU_MAX];
    vector<int> v_GenVisTau_status_;
    TBranch *b_GenVisTau_status_;
    bool loaded_GenVisTau_status_;
    float Generator_binvar_;
    TBranch *b_Generator_binvar_;
    bool loaded_Generator_binvar_;
    int Generator_id1_;
    TBranch *b_Generator_id1_;
    bool loaded_Generator_id1_;
    int Generator_id2_;
    TBranch *b_Generator_id2_;
    bool loaded_Generator_id2_;
    float Generator_scalePDF_;
    TBranch *b_Generator_scalePDF_;
    bool loaded_Generator_scalePDF_;
    float Generator_weight_;
    TBranch *b_Generator_weight_;
    bool loaded_Generator_weight_;
    float Generator_x1_;
    TBranch *b_Generator_x1_;
    bool loaded_Generator_x1_;
    float Generator_x2_;
    TBranch *b_Generator_x2_;
    bool loaded_Generator_x2_;
    float Generator_xpdf1_;
    TBranch *b_Generator_xpdf1_;
    bool loaded_Generator_xpdf1_;
    float Generator_xpdf2_;
    TBranch *b_Generator_xpdf2_;
    bool loaded_Generator_xpdf2_;
    bool HLT_AK4CaloJet100_;
    TBranch *b_HLT_AK4CaloJet100_;
    bool loaded_HLT_AK4CaloJet100_;
    bool HLT_AK4CaloJet120_;
    TBranch *b_HLT_AK4CaloJet120_;
    bool loaded_HLT_AK4CaloJet120_;
    bool HLT_AK4CaloJet30_;
    TBranch *b_HLT_AK4CaloJet30_;
    bool loaded_HLT_AK4CaloJet30_;
    bool HLT_AK4CaloJet40_;
    TBranch *b_HLT_AK4CaloJet40_;
    bool loaded_HLT_AK4CaloJet40_;
    bool HLT_AK4CaloJet50_;
    TBranch *b_HLT_AK4CaloJet50_;
    bool loaded_HLT_AK4CaloJet50_;
    bool HLT_AK4CaloJet80_;
    TBranch *b_HLT_AK4CaloJet80_;
    bool loaded_HLT_AK4CaloJet80_;
    bool HLT_AK4PFJet100_;
    TBranch *b_HLT_AK4PFJet100_;
    bool loaded_HLT_AK4PFJet100_;
    bool HLT_AK4PFJet120_;
    TBranch *b_HLT_AK4PFJet120_;
    bool loaded_HLT_AK4PFJet120_;
    bool HLT_AK4PFJet30_;
    TBranch *b_HLT_AK4PFJet30_;
    bool loaded_HLT_AK4PFJet30_;
    bool HLT_AK4PFJet50_;
    TBranch *b_HLT_AK4PFJet50_;
    bool loaded_HLT_AK4PFJet50_;
    bool HLT_AK4PFJet80_;
    TBranch *b_HLT_AK4PFJet80_;
    bool loaded_HLT_AK4PFJet80_;
    bool HLT_AK8DiPFJet250_200_TrimMass30_;
    TBranch *b_HLT_AK8DiPFJet250_200_TrimMass30_;
    bool loaded_HLT_AK8DiPFJet250_200_TrimMass30_;
    bool HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_;
    TBranch *b_HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_;
    bool loaded_HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_;
    bool HLT_AK8DiPFJet280_200_TrimMass30_;
    TBranch *b_HLT_AK8DiPFJet280_200_TrimMass30_;
    bool loaded_HLT_AK8DiPFJet280_200_TrimMass30_;
    bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_;
    TBranch *b_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_;
    bool loaded_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_;
    bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_;
    TBranch *b_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_;
    bool loaded_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_;
    bool HLT_AK8DiPFJet300_200_TrimMass30_;
    TBranch *b_HLT_AK8DiPFJet300_200_TrimMass30_;
    bool loaded_HLT_AK8DiPFJet300_200_TrimMass30_;
    bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_;
    TBranch *b_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_;
    bool loaded_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_;
    bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_;
    TBranch *b_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_;
    bool loaded_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_;
    bool HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_;
    TBranch *b_HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_;
    bool loaded_HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_;
    bool HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_;
    TBranch *b_HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_;
    bool loaded_HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_;
    bool HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_;
    TBranch *b_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_;
    bool loaded_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_;
    bool HLT_AK8PFHT750_TrimMass50_;
    TBranch *b_HLT_AK8PFHT750_TrimMass50_;
    bool loaded_HLT_AK8PFHT750_TrimMass50_;
    bool HLT_AK8PFHT800_TrimMass50_;
    TBranch *b_HLT_AK8PFHT800_TrimMass50_;
    bool loaded_HLT_AK8PFHT800_TrimMass50_;
    bool HLT_AK8PFHT850_TrimMass50_;
    TBranch *b_HLT_AK8PFHT850_TrimMass50_;
    bool loaded_HLT_AK8PFHT850_TrimMass50_;
    bool HLT_AK8PFHT900_TrimMass50_;
    TBranch *b_HLT_AK8PFHT900_TrimMass50_;
    bool loaded_HLT_AK8PFHT900_TrimMass50_;
    bool HLT_AK8PFJet140_;
    TBranch *b_HLT_AK8PFJet140_;
    bool loaded_HLT_AK8PFJet140_;
    bool HLT_AK8PFJet15_;
    TBranch *b_HLT_AK8PFJet15_;
    bool loaded_HLT_AK8PFJet15_;
    bool HLT_AK8PFJet200_;
    TBranch *b_HLT_AK8PFJet200_;
    bool loaded_HLT_AK8PFJet200_;
    bool HLT_AK8PFJet25_;
    TBranch *b_HLT_AK8PFJet25_;
    bool loaded_HLT_AK8PFJet25_;
    bool HLT_AK8PFJet260_;
    TBranch *b_HLT_AK8PFJet260_;
    bool loaded_HLT_AK8PFJet260_;
    bool HLT_AK8PFJet320_;
    TBranch *b_HLT_AK8PFJet320_;
    bool loaded_HLT_AK8PFJet320_;
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_;
    TBranch *b_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_;
    bool loaded_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_;
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_;
    TBranch *b_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_;
    bool loaded_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_;
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_;
    TBranch *b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_;
    bool loaded_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_;
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_;
    TBranch *b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_;
    bool loaded_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_;
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_;
    TBranch *b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_;
    bool loaded_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_;
    bool HLT_AK8PFJet360_TrimMass30_;
    TBranch *b_HLT_AK8PFJet360_TrimMass30_;
    bool loaded_HLT_AK8PFJet360_TrimMass30_;
    bool HLT_AK8PFJet380_TrimMass30_;
    TBranch *b_HLT_AK8PFJet380_TrimMass30_;
    bool loaded_HLT_AK8PFJet380_TrimMass30_;
    bool HLT_AK8PFJet40_;
    TBranch *b_HLT_AK8PFJet40_;
    bool loaded_HLT_AK8PFJet40_;
    bool HLT_AK8PFJet400_;
    TBranch *b_HLT_AK8PFJet400_;
    bool loaded_HLT_AK8PFJet400_;
    bool HLT_AK8PFJet400_TrimMass30_;
    TBranch *b_HLT_AK8PFJet400_TrimMass30_;
    bool loaded_HLT_AK8PFJet400_TrimMass30_;
    bool HLT_AK8PFJet420_TrimMass30_;
    TBranch *b_HLT_AK8PFJet420_TrimMass30_;
    bool loaded_HLT_AK8PFJet420_TrimMass30_;
    bool HLT_AK8PFJet450_;
    TBranch *b_HLT_AK8PFJet450_;
    bool loaded_HLT_AK8PFJet450_;
    bool HLT_AK8PFJet500_;
    TBranch *b_HLT_AK8PFJet500_;
    bool loaded_HLT_AK8PFJet500_;
    bool HLT_AK8PFJet550_;
    TBranch *b_HLT_AK8PFJet550_;
    bool loaded_HLT_AK8PFJet550_;
    bool HLT_AK8PFJet60_;
    TBranch *b_HLT_AK8PFJet60_;
    bool loaded_HLT_AK8PFJet60_;
    bool HLT_AK8PFJet80_;
    TBranch *b_HLT_AK8PFJet80_;
    bool loaded_HLT_AK8PFJet80_;
    bool HLT_AK8PFJetFwd140_;
    TBranch *b_HLT_AK8PFJetFwd140_;
    bool loaded_HLT_AK8PFJetFwd140_;
    bool HLT_AK8PFJetFwd15_;
    TBranch *b_HLT_AK8PFJetFwd15_;
    bool loaded_HLT_AK8PFJetFwd15_;
    bool HLT_AK8PFJetFwd200_;
    TBranch *b_HLT_AK8PFJetFwd200_;
    bool loaded_HLT_AK8PFJetFwd200_;
    bool HLT_AK8PFJetFwd25_;
    TBranch *b_HLT_AK8PFJetFwd25_;
    bool loaded_HLT_AK8PFJetFwd25_;
    bool HLT_AK8PFJetFwd260_;
    TBranch *b_HLT_AK8PFJetFwd260_;
    bool loaded_HLT_AK8PFJetFwd260_;
    bool HLT_AK8PFJetFwd320_;
    TBranch *b_HLT_AK8PFJetFwd320_;
    bool loaded_HLT_AK8PFJetFwd320_;
    bool HLT_AK8PFJetFwd40_;
    TBranch *b_HLT_AK8PFJetFwd40_;
    bool loaded_HLT_AK8PFJetFwd40_;
    bool HLT_AK8PFJetFwd400_;
    TBranch *b_HLT_AK8PFJetFwd400_;
    bool loaded_HLT_AK8PFJetFwd400_;
    bool HLT_AK8PFJetFwd450_;
    TBranch *b_HLT_AK8PFJetFwd450_;
    bool loaded_HLT_AK8PFJetFwd450_;
    bool HLT_AK8PFJetFwd500_;
    TBranch *b_HLT_AK8PFJetFwd500_;
    bool loaded_HLT_AK8PFJetFwd500_;
    bool HLT_AK8PFJetFwd60_;
    TBranch *b_HLT_AK8PFJetFwd60_;
    bool loaded_HLT_AK8PFJetFwd60_;
    bool HLT_AK8PFJetFwd80_;
    TBranch *b_HLT_AK8PFJetFwd80_;
    bool loaded_HLT_AK8PFJetFwd80_;
    bool HLT_BTagMu_AK4DiJet110_Mu5_;
    TBranch *b_HLT_BTagMu_AK4DiJet110_Mu5_;
    bool loaded_HLT_BTagMu_AK4DiJet110_Mu5_;
    bool HLT_BTagMu_AK4DiJet110_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK4DiJet110_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK4DiJet110_Mu5_noalgo_;
    bool HLT_BTagMu_AK4DiJet170_Mu5_;
    TBranch *b_HLT_BTagMu_AK4DiJet170_Mu5_;
    bool loaded_HLT_BTagMu_AK4DiJet170_Mu5_;
    bool HLT_BTagMu_AK4DiJet170_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK4DiJet170_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK4DiJet170_Mu5_noalgo_;
    bool HLT_BTagMu_AK4DiJet20_Mu5_;
    TBranch *b_HLT_BTagMu_AK4DiJet20_Mu5_;
    bool loaded_HLT_BTagMu_AK4DiJet20_Mu5_;
    bool HLT_BTagMu_AK4DiJet20_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK4DiJet20_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK4DiJet20_Mu5_noalgo_;
    bool HLT_BTagMu_AK4DiJet40_Mu5_;
    TBranch *b_HLT_BTagMu_AK4DiJet40_Mu5_;
    bool loaded_HLT_BTagMu_AK4DiJet40_Mu5_;
    bool HLT_BTagMu_AK4DiJet40_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK4DiJet40_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK4DiJet40_Mu5_noalgo_;
    bool HLT_BTagMu_AK4DiJet70_Mu5_;
    TBranch *b_HLT_BTagMu_AK4DiJet70_Mu5_;
    bool loaded_HLT_BTagMu_AK4DiJet70_Mu5_;
    bool HLT_BTagMu_AK4DiJet70_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK4DiJet70_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK4DiJet70_Mu5_noalgo_;
    bool HLT_BTagMu_AK4Jet300_Mu5_;
    TBranch *b_HLT_BTagMu_AK4Jet300_Mu5_;
    bool loaded_HLT_BTagMu_AK4Jet300_Mu5_;
    bool HLT_BTagMu_AK4Jet300_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK4Jet300_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK4Jet300_Mu5_noalgo_;
    bool HLT_BTagMu_AK8DiJet170_Mu5_;
    TBranch *b_HLT_BTagMu_AK8DiJet170_Mu5_;
    bool loaded_HLT_BTagMu_AK8DiJet170_Mu5_;
    bool HLT_BTagMu_AK8DiJet170_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK8DiJet170_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK8DiJet170_Mu5_noalgo_;
    bool HLT_BTagMu_AK8Jet170_DoubleMu5_;
    TBranch *b_HLT_BTagMu_AK8Jet170_DoubleMu5_;
    bool loaded_HLT_BTagMu_AK8Jet170_DoubleMu5_;
    bool HLT_BTagMu_AK8Jet170_DoubleMu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK8Jet170_DoubleMu5_noalgo_;
    bool loaded_HLT_BTagMu_AK8Jet170_DoubleMu5_noalgo_;
    bool HLT_BTagMu_AK8Jet300_Mu5_;
    TBranch *b_HLT_BTagMu_AK8Jet300_Mu5_;
    bool loaded_HLT_BTagMu_AK8Jet300_Mu5_;
    bool HLT_BTagMu_AK8Jet300_Mu5_noalgo_;
    TBranch *b_HLT_BTagMu_AK8Jet300_Mu5_noalgo_;
    bool loaded_HLT_BTagMu_AK8Jet300_Mu5_noalgo_;
    bool HLT_BTagMu_DiJet110_Mu5_;
    TBranch *b_HLT_BTagMu_DiJet110_Mu5_;
    bool loaded_HLT_BTagMu_DiJet110_Mu5_;
    bool HLT_BTagMu_DiJet170_Mu5_;
    TBranch *b_HLT_BTagMu_DiJet170_Mu5_;
    bool loaded_HLT_BTagMu_DiJet170_Mu5_;
    bool HLT_BTagMu_DiJet20_Mu5_;
    TBranch *b_HLT_BTagMu_DiJet20_Mu5_;
    bool loaded_HLT_BTagMu_DiJet20_Mu5_;
    bool HLT_BTagMu_DiJet40_Mu5_;
    TBranch *b_HLT_BTagMu_DiJet40_Mu5_;
    bool loaded_HLT_BTagMu_DiJet40_Mu5_;
    bool HLT_BTagMu_DiJet70_Mu5_;
    TBranch *b_HLT_BTagMu_DiJet70_Mu5_;
    bool loaded_HLT_BTagMu_DiJet70_Mu5_;
    bool HLT_BTagMu_Jet300_Mu5_;
    TBranch *b_HLT_BTagMu_Jet300_Mu5_;
    bool loaded_HLT_BTagMu_Jet300_Mu5_;
    bool HLT_CDC_L2cosmic_5_er1p0_;
    TBranch *b_HLT_CDC_L2cosmic_5_er1p0_;
    bool loaded_HLT_CDC_L2cosmic_5_er1p0_;
    bool HLT_CDC_L2cosmic_5p5_er1p0_;
    TBranch *b_HLT_CDC_L2cosmic_5p5_er1p0_;
    bool loaded_HLT_CDC_L2cosmic_5p5_er1p0_;
    bool HLT_CaloJet260_;
    TBranch *b_HLT_CaloJet260_;
    bool loaded_HLT_CaloJet260_;
    bool HLT_CaloJet500_NoJetID_;
    TBranch *b_HLT_CaloJet500_NoJetID_;
    bool loaded_HLT_CaloJet500_NoJetID_;
    bool HLT_CaloJet550_NoJetID_;
    TBranch *b_HLT_CaloJet550_NoJetID_;
    bool loaded_HLT_CaloJet550_NoJetID_;
    bool HLT_CaloMET100_HBHECleaned_;
    TBranch *b_HLT_CaloMET100_HBHECleaned_;
    bool loaded_HLT_CaloMET100_HBHECleaned_;
    bool HLT_CaloMET100_NotCleaned_;
    TBranch *b_HLT_CaloMET100_NotCleaned_;
    bool loaded_HLT_CaloMET100_NotCleaned_;
    bool HLT_CaloMET110_NotCleaned_;
    TBranch *b_HLT_CaloMET110_NotCleaned_;
    bool loaded_HLT_CaloMET110_NotCleaned_;
    bool HLT_CaloMET250_HBHECleaned_;
    TBranch *b_HLT_CaloMET250_HBHECleaned_;
    bool loaded_HLT_CaloMET250_HBHECleaned_;
    bool HLT_CaloMET250_NotCleaned_;
    TBranch *b_HLT_CaloMET250_NotCleaned_;
    bool loaded_HLT_CaloMET250_NotCleaned_;
    bool HLT_CaloMET300_HBHECleaned_;
    TBranch *b_HLT_CaloMET300_HBHECleaned_;
    bool loaded_HLT_CaloMET300_HBHECleaned_;
    bool HLT_CaloMET350_HBHECleaned_;
    TBranch *b_HLT_CaloMET350_HBHECleaned_;
    bool loaded_HLT_CaloMET350_HBHECleaned_;
    bool HLT_CaloMET70_HBHECleaned_;
    TBranch *b_HLT_CaloMET70_HBHECleaned_;
    bool loaded_HLT_CaloMET70_HBHECleaned_;
    bool HLT_CaloMET80_HBHECleaned_;
    TBranch *b_HLT_CaloMET80_HBHECleaned_;
    bool loaded_HLT_CaloMET80_HBHECleaned_;
    bool HLT_CaloMET80_NotCleaned_;
    TBranch *b_HLT_CaloMET80_NotCleaned_;
    bool loaded_HLT_CaloMET80_NotCleaned_;
    bool HLT_CaloMET90_HBHECleaned_;
    TBranch *b_HLT_CaloMET90_HBHECleaned_;
    bool loaded_HLT_CaloMET90_HBHECleaned_;
    bool HLT_CaloMET90_NotCleaned_;
    TBranch *b_HLT_CaloMET90_NotCleaned_;
    bool loaded_HLT_CaloMET90_NotCleaned_;
    bool HLT_CaloMHT90_;
    TBranch *b_HLT_CaloMHT90_;
    bool loaded_HLT_CaloMHT90_;
    bool HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_;
    TBranch *b_HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_;
    bool loaded_HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_;
    bool HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067_;
    TBranch *b_HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067_;
    bool loaded_HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067_;
    bool HLT_DiCentralPFJet170_;
    TBranch *b_HLT_DiCentralPFJet170_;
    bool loaded_HLT_DiCentralPFJet170_;
    bool HLT_DiCentralPFJet170_CFMax0p1_;
    TBranch *b_HLT_DiCentralPFJet170_CFMax0p1_;
    bool loaded_HLT_DiCentralPFJet170_CFMax0p1_;
    bool HLT_DiCentralPFJet220_CFMax0p3_;
    TBranch *b_HLT_DiCentralPFJet220_CFMax0p3_;
    bool loaded_HLT_DiCentralPFJet220_CFMax0p3_;
    bool HLT_DiCentralPFJet330_CFMax0p5_;
    TBranch *b_HLT_DiCentralPFJet330_CFMax0p5_;
    bool loaded_HLT_DiCentralPFJet330_CFMax0p5_;
    bool HLT_DiCentralPFJet430_;
    TBranch *b_HLT_DiCentralPFJet430_;
    bool loaded_HLT_DiCentralPFJet430_;
    bool HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_;
    TBranch *b_HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_;
    bool loaded_HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_;
    bool HLT_DiJet110_35_Mjj650_PFMET110_;
    TBranch *b_HLT_DiJet110_35_Mjj650_PFMET110_;
    bool loaded_HLT_DiJet110_35_Mjj650_PFMET110_;
    bool HLT_DiJet110_35_Mjj650_PFMET120_;
    TBranch *b_HLT_DiJet110_35_Mjj650_PFMET120_;
    bool loaded_HLT_DiJet110_35_Mjj650_PFMET120_;
    bool HLT_DiJet110_35_Mjj650_PFMET130_;
    TBranch *b_HLT_DiJet110_35_Mjj650_PFMET130_;
    bool loaded_HLT_DiJet110_35_Mjj650_PFMET130_;
    bool HLT_DiMu4_Ele9_CaloIdL_TrackIdL_DZ_Mass3p8_;
    TBranch *b_HLT_DiMu4_Ele9_CaloIdL_TrackIdL_DZ_Mass3p8_;
    bool loaded_HLT_DiMu4_Ele9_CaloIdL_TrackIdL_DZ_Mass3p8_;
    bool HLT_DiMu9_Ele9_CaloIdL_TrackIdL_;
    TBranch *b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_;
    bool loaded_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_;
    bool HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_;
    TBranch *b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_;
    bool loaded_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_;
    bool HLT_DiPFJet15_FBEta3_NoCaloMatched_;
    TBranch *b_HLT_DiPFJet15_FBEta3_NoCaloMatched_;
    bool loaded_HLT_DiPFJet15_FBEta3_NoCaloMatched_;
    bool HLT_DiPFJet15_NoCaloMatched_;
    TBranch *b_HLT_DiPFJet15_NoCaloMatched_;
    bool loaded_HLT_DiPFJet15_NoCaloMatched_;
    bool HLT_DiPFJet25_FBEta3_NoCaloMatched_;
    TBranch *b_HLT_DiPFJet25_FBEta3_NoCaloMatched_;
    bool loaded_HLT_DiPFJet25_FBEta3_NoCaloMatched_;
    bool HLT_DiPFJet25_NoCaloMatched_;
    TBranch *b_HLT_DiPFJet25_NoCaloMatched_;
    bool loaded_HLT_DiPFJet25_NoCaloMatched_;
    bool HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_;
    TBranch *b_HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_;
    bool loaded_HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_;
    bool HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_;
    TBranch *b_HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_;
    bool loaded_HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_;
    bool HLT_DiPFJetAve100_HFJEC_;
    TBranch *b_HLT_DiPFJetAve100_HFJEC_;
    bool loaded_HLT_DiPFJetAve100_HFJEC_;
    bool HLT_DiPFJetAve140_;
    TBranch *b_HLT_DiPFJetAve140_;
    bool loaded_HLT_DiPFJetAve140_;
    bool HLT_DiPFJetAve15_HFJEC_;
    TBranch *b_HLT_DiPFJetAve15_HFJEC_;
    bool loaded_HLT_DiPFJetAve15_HFJEC_;
    bool HLT_DiPFJetAve160_HFJEC_;
    TBranch *b_HLT_DiPFJetAve160_HFJEC_;
    bool loaded_HLT_DiPFJetAve160_HFJEC_;
    bool HLT_DiPFJetAve200_;
    TBranch *b_HLT_DiPFJetAve200_;
    bool loaded_HLT_DiPFJetAve200_;
    bool HLT_DiPFJetAve220_HFJEC_;
    TBranch *b_HLT_DiPFJetAve220_HFJEC_;
    bool loaded_HLT_DiPFJetAve220_HFJEC_;
    bool HLT_DiPFJetAve25_HFJEC_;
    TBranch *b_HLT_DiPFJetAve25_HFJEC_;
    bool loaded_HLT_DiPFJetAve25_HFJEC_;
    bool HLT_DiPFJetAve260_;
    TBranch *b_HLT_DiPFJetAve260_;
    bool loaded_HLT_DiPFJetAve260_;
    bool HLT_DiPFJetAve300_HFJEC_;
    TBranch *b_HLT_DiPFJetAve300_HFJEC_;
    bool loaded_HLT_DiPFJetAve300_HFJEC_;
    bool HLT_DiPFJetAve320_;
    TBranch *b_HLT_DiPFJetAve320_;
    bool loaded_HLT_DiPFJetAve320_;
    bool HLT_DiPFJetAve35_HFJEC_;
    TBranch *b_HLT_DiPFJetAve35_HFJEC_;
    bool loaded_HLT_DiPFJetAve35_HFJEC_;
    bool HLT_DiPFJetAve40_;
    TBranch *b_HLT_DiPFJetAve40_;
    bool loaded_HLT_DiPFJetAve40_;
    bool HLT_DiPFJetAve400_;
    TBranch *b_HLT_DiPFJetAve400_;
    bool loaded_HLT_DiPFJetAve400_;
    bool HLT_DiPFJetAve500_;
    TBranch *b_HLT_DiPFJetAve500_;
    bool loaded_HLT_DiPFJetAve500_;
    bool HLT_DiPFJetAve60_;
    TBranch *b_HLT_DiPFJetAve60_;
    bool loaded_HLT_DiPFJetAve60_;
    bool HLT_DiPFJetAve60_HFJEC_;
    TBranch *b_HLT_DiPFJetAve60_HFJEC_;
    bool loaded_HLT_DiPFJetAve60_HFJEC_;
    bool HLT_DiPFJetAve80_;
    TBranch *b_HLT_DiPFJetAve80_;
    bool loaded_HLT_DiPFJetAve80_;
    bool HLT_DiPFJetAve80_HFJEC_;
    TBranch *b_HLT_DiPFJetAve80_HFJEC_;
    bool loaded_HLT_DiPFJetAve80_HFJEC_;
    bool HLT_DiSC30_18_EIso_AND_HE_Mass70_;
    TBranch *b_HLT_DiSC30_18_EIso_AND_HE_Mass70_;
    bool loaded_HLT_DiSC30_18_EIso_AND_HE_Mass70_;
    bool HLT_Dimuon0_Jpsi_;
    TBranch *b_HLT_Dimuon0_Jpsi_;
    bool loaded_HLT_Dimuon0_Jpsi_;
    bool HLT_Dimuon0_Jpsi3p5_Muon2_;
    TBranch *b_HLT_Dimuon0_Jpsi3p5_Muon2_;
    bool loaded_HLT_Dimuon0_Jpsi3p5_Muon2_;
    bool HLT_Dimuon0_Jpsi_L1_4R_0er1p5R_;
    TBranch *b_HLT_Dimuon0_Jpsi_L1_4R_0er1p5R_;
    bool loaded_HLT_Dimuon0_Jpsi_L1_4R_0er1p5R_;
    bool HLT_Dimuon0_Jpsi_L1_NoOS_;
    TBranch *b_HLT_Dimuon0_Jpsi_L1_NoOS_;
    bool loaded_HLT_Dimuon0_Jpsi_L1_NoOS_;
    bool HLT_Dimuon0_Jpsi_Muon_;
    TBranch *b_HLT_Dimuon0_Jpsi_Muon_;
    bool loaded_HLT_Dimuon0_Jpsi_Muon_;
    bool HLT_Dimuon0_Jpsi_NoVertexing_;
    TBranch *b_HLT_Dimuon0_Jpsi_NoVertexing_;
    bool loaded_HLT_Dimuon0_Jpsi_NoVertexing_;
    bool HLT_Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R_;
    TBranch *b_HLT_Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R_;
    bool loaded_HLT_Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R_;
    bool HLT_Dimuon0_Jpsi_NoVertexing_NoOS_;
    TBranch *b_HLT_Dimuon0_Jpsi_NoVertexing_NoOS_;
    bool loaded_HLT_Dimuon0_Jpsi_NoVertexing_NoOS_;
    bool HLT_Dimuon0_LowMass_;
    TBranch *b_HLT_Dimuon0_LowMass_;
    bool loaded_HLT_Dimuon0_LowMass_;
    bool HLT_Dimuon0_LowMass_L1_0er1p5_;
    TBranch *b_HLT_Dimuon0_LowMass_L1_0er1p5_;
    bool loaded_HLT_Dimuon0_LowMass_L1_0er1p5_;
    bool HLT_Dimuon0_LowMass_L1_0er1p5R_;
    TBranch *b_HLT_Dimuon0_LowMass_L1_0er1p5R_;
    bool loaded_HLT_Dimuon0_LowMass_L1_0er1p5R_;
    bool HLT_Dimuon0_LowMass_L1_4_;
    TBranch *b_HLT_Dimuon0_LowMass_L1_4_;
    bool loaded_HLT_Dimuon0_LowMass_L1_4_;
    bool HLT_Dimuon0_LowMass_L1_4R_;
    TBranch *b_HLT_Dimuon0_LowMass_L1_4R_;
    bool loaded_HLT_Dimuon0_LowMass_L1_4R_;
    bool HLT_Dimuon0_LowMass_L1_TM530_;
    TBranch *b_HLT_Dimuon0_LowMass_L1_TM530_;
    bool loaded_HLT_Dimuon0_LowMass_L1_TM530_;
    bool HLT_Dimuon0_Phi_Barrel_;
    TBranch *b_HLT_Dimuon0_Phi_Barrel_;
    bool loaded_HLT_Dimuon0_Phi_Barrel_;
    bool HLT_Dimuon0_Upsilon_L1_4p5_;
    TBranch *b_HLT_Dimuon0_Upsilon_L1_4p5_;
    bool loaded_HLT_Dimuon0_Upsilon_L1_4p5_;
    bool HLT_Dimuon0_Upsilon_L1_4p5NoOS_;
    TBranch *b_HLT_Dimuon0_Upsilon_L1_4p5NoOS_;
    bool loaded_HLT_Dimuon0_Upsilon_L1_4p5NoOS_;
    bool HLT_Dimuon0_Upsilon_L1_4p5er2p0_;
    TBranch *b_HLT_Dimuon0_Upsilon_L1_4p5er2p0_;
    bool loaded_HLT_Dimuon0_Upsilon_L1_4p5er2p0_;
    bool HLT_Dimuon0_Upsilon_L1_4p5er2p0M_;
    TBranch *b_HLT_Dimuon0_Upsilon_L1_4p5er2p0M_;
    bool loaded_HLT_Dimuon0_Upsilon_L1_4p5er2p0M_;
    bool HLT_Dimuon0_Upsilon_L1_5_;
    TBranch *b_HLT_Dimuon0_Upsilon_L1_5_;
    bool loaded_HLT_Dimuon0_Upsilon_L1_5_;
    bool HLT_Dimuon0_Upsilon_L1_5M_;
    TBranch *b_HLT_Dimuon0_Upsilon_L1_5M_;
    bool loaded_HLT_Dimuon0_Upsilon_L1_5M_;
    bool HLT_Dimuon0_Upsilon_Muon_;
    TBranch *b_HLT_Dimuon0_Upsilon_Muon_;
    bool loaded_HLT_Dimuon0_Upsilon_Muon_;
    bool HLT_Dimuon0_Upsilon_Muon_L1_TM0_;
    TBranch *b_HLT_Dimuon0_Upsilon_Muon_L1_TM0_;
    bool loaded_HLT_Dimuon0_Upsilon_Muon_L1_TM0_;
    bool HLT_Dimuon0_Upsilon_Muon_NoL1Mass_;
    TBranch *b_HLT_Dimuon0_Upsilon_Muon_NoL1Mass_;
    bool loaded_HLT_Dimuon0_Upsilon_Muon_NoL1Mass_;
    bool HLT_Dimuon0_Upsilon_NoVertexing_;
    TBranch *b_HLT_Dimuon0_Upsilon_NoVertexing_;
    bool loaded_HLT_Dimuon0_Upsilon_NoVertexing_;
    bool HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing_;
    TBranch *b_HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing_;
    bool loaded_HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing_;
    bool HLT_Dimuon0er16_Jpsi_NoVertexing_;
    TBranch *b_HLT_Dimuon0er16_Jpsi_NoVertexing_;
    bool loaded_HLT_Dimuon0er16_Jpsi_NoVertexing_;
    bool HLT_Dimuon10_Jpsi_Barrel_;
    TBranch *b_HLT_Dimuon10_Jpsi_Barrel_;
    bool loaded_HLT_Dimuon10_Jpsi_Barrel_;
    bool HLT_Dimuon10_PsiPrime_Barrel_Seagulls_;
    TBranch *b_HLT_Dimuon10_PsiPrime_Barrel_Seagulls_;
    bool loaded_HLT_Dimuon10_PsiPrime_Barrel_Seagulls_;
    bool HLT_Dimuon12_Upsilon_y1p4_;
    TBranch *b_HLT_Dimuon12_Upsilon_y1p4_;
    bool loaded_HLT_Dimuon12_Upsilon_y1p4_;
    bool HLT_Dimuon13_PsiPrime_;
    TBranch *b_HLT_Dimuon13_PsiPrime_;
    bool loaded_HLT_Dimuon13_PsiPrime_;
    bool HLT_Dimuon13_Upsilon_;
    TBranch *b_HLT_Dimuon13_Upsilon_;
    bool loaded_HLT_Dimuon13_Upsilon_;
    bool HLT_Dimuon14_Phi_Barrel_Seagulls_;
    TBranch *b_HLT_Dimuon14_Phi_Barrel_Seagulls_;
    bool loaded_HLT_Dimuon14_Phi_Barrel_Seagulls_;
    bool HLT_Dimuon16_Jpsi_;
    TBranch *b_HLT_Dimuon16_Jpsi_;
    bool loaded_HLT_Dimuon16_Jpsi_;
    bool HLT_Dimuon18_PsiPrime_;
    TBranch *b_HLT_Dimuon18_PsiPrime_;
    bool loaded_HLT_Dimuon18_PsiPrime_;
    bool HLT_Dimuon18_PsiPrime_noCorrL1_;
    TBranch *b_HLT_Dimuon18_PsiPrime_noCorrL1_;
    bool loaded_HLT_Dimuon18_PsiPrime_noCorrL1_;
    bool HLT_Dimuon20_Jpsi_;
    TBranch *b_HLT_Dimuon20_Jpsi_;
    bool loaded_HLT_Dimuon20_Jpsi_;
    bool HLT_Dimuon20_Jpsi_Barrel_Seagulls_;
    TBranch *b_HLT_Dimuon20_Jpsi_Barrel_Seagulls_;
    bool loaded_HLT_Dimuon20_Jpsi_Barrel_Seagulls_;
    bool HLT_Dimuon24_Phi_noCorrL1_;
    TBranch *b_HLT_Dimuon24_Phi_noCorrL1_;
    bool loaded_HLT_Dimuon24_Phi_noCorrL1_;
    bool HLT_Dimuon24_Upsilon_noCorrL1_;
    TBranch *b_HLT_Dimuon24_Upsilon_noCorrL1_;
    bool loaded_HLT_Dimuon24_Upsilon_noCorrL1_;
    bool HLT_Dimuon25_Jpsi_;
    TBranch *b_HLT_Dimuon25_Jpsi_;
    bool loaded_HLT_Dimuon25_Jpsi_;
    bool HLT_Dimuon25_Jpsi_noCorrL1_;
    TBranch *b_HLT_Dimuon25_Jpsi_noCorrL1_;
    bool loaded_HLT_Dimuon25_Jpsi_noCorrL1_;
    bool HLT_Dimuon6_Jpsi_NoVertexing_;
    TBranch *b_HLT_Dimuon6_Jpsi_NoVertexing_;
    bool loaded_HLT_Dimuon6_Jpsi_NoVertexing_;
    bool HLT_Dimuon8_PsiPrime_Barrel_;
    TBranch *b_HLT_Dimuon8_PsiPrime_Barrel_;
    bool loaded_HLT_Dimuon8_PsiPrime_Barrel_;
    bool HLT_Dimuon8_Upsilon_Barrel_;
    TBranch *b_HLT_Dimuon8_Upsilon_Barrel_;
    bool loaded_HLT_Dimuon8_Upsilon_Barrel_;
    bool HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_;
    TBranch *b_HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_;
    bool loaded_HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_;
    bool HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_;
    TBranch *b_HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_;
    bool loaded_HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_;
    bool HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_;
    TBranch *b_HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_;
    bool loaded_HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_;
    bool HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_;
    TBranch *b_HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_;
    bool loaded_HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_;
    bool HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_;
    TBranch *b_HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_;
    bool loaded_HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_;
    bool HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_Mass55_;
    TBranch *b_HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_Mass55_;
    bool loaded_HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_Mass55_;
    bool HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70_;
    TBranch *b_HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70_;
    bool loaded_HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70_;
    bool HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_;
    TBranch *b_HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_;
    bool loaded_HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_;
    bool HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55_;
    TBranch *b_HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55_;
    bool loaded_HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55_;
    bool HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_;
    TBranch *b_HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_;
    bool loaded_HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_;
    bool HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_;
    TBranch *b_HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_;
    bool loaded_HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_;
    bool HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_;
    bool HLT_DoubleEle24_eta2p1_WPTight_Gsf_;
    TBranch *b_HLT_DoubleEle24_eta2p1_WPTight_Gsf_;
    bool loaded_HLT_DoubleEle24_eta2p1_WPTight_Gsf_;
    bool HLT_DoubleEle25_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_DoubleEle25_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_DoubleEle25_CaloIdL_GsfTrkIdVL_;
    bool HLT_DoubleEle25_CaloIdL_MW_;
    TBranch *b_HLT_DoubleEle25_CaloIdL_MW_;
    bool loaded_HLT_DoubleEle25_CaloIdL_MW_;
    bool HLT_DoubleEle27_CaloIdL_MW_;
    TBranch *b_HLT_DoubleEle27_CaloIdL_MW_;
    bool loaded_HLT_DoubleEle27_CaloIdL_MW_;
    bool HLT_DoubleEle33_CaloIdL_;
    TBranch *b_HLT_DoubleEle33_CaloIdL_;
    bool loaded_HLT_DoubleEle33_CaloIdL_;
    bool HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_;
    bool HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_;
    TBranch *b_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_;
    bool loaded_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_;
    bool HLT_DoubleEle33_CaloIdL_MW_;
    TBranch *b_HLT_DoubleEle33_CaloIdL_MW_;
    bool loaded_HLT_DoubleEle33_CaloIdL_MW_;
    bool HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_;
    bool HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350_;
    TBranch *b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350_;
    bool loaded_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350_;
    bool HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250_;
    TBranch *b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250_;
    bool loaded_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250_;
    bool HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_;
    TBranch *b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_;
    bool loaded_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_;
    bool HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350_;
    TBranch *b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350_;
    bool loaded_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350_;
    bool HLT_DoubleIsoMu17_eta2p1_;
    TBranch *b_HLT_DoubleIsoMu17_eta2p1_;
    bool loaded_HLT_DoubleIsoMu17_eta2p1_;
    bool HLT_DoubleIsoMu17_eta2p1_noDzCut_;
    TBranch *b_HLT_DoubleIsoMu17_eta2p1_noDzCut_;
    bool loaded_HLT_DoubleIsoMu17_eta2p1_noDzCut_;
    bool HLT_DoubleIsoMu20_eta2p1_;
    TBranch *b_HLT_DoubleIsoMu20_eta2p1_;
    bool loaded_HLT_DoubleIsoMu20_eta2p1_;
    bool HLT_DoubleJet90_Double30_DoubleBTagCSV_p087_;
    TBranch *b_HLT_DoubleJet90_Double30_DoubleBTagCSV_p087_;
    bool loaded_HLT_DoubleJet90_Double30_DoubleBTagCSV_p087_;
    bool HLT_DoubleJet90_Double30_TripleBTagCSV_p087_;
    TBranch *b_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_;
    bool loaded_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_;
    bool HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6_;
    TBranch *b_HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6_;
    bool loaded_HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6_;
    bool HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160_;
    TBranch *b_HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160_;
    bool loaded_HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160_;
    bool HLT_DoubleJetsC100_SingleBTagCSV_p014_;
    TBranch *b_HLT_DoubleJetsC100_SingleBTagCSV_p014_;
    bool loaded_HLT_DoubleJetsC100_SingleBTagCSV_p014_;
    bool HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350_;
    TBranch *b_HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350_;
    bool loaded_HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350_;
    bool HLT_DoubleJetsC100_SingleBTagCSV_p026_;
    TBranch *b_HLT_DoubleJetsC100_SingleBTagCSV_p026_;
    bool loaded_HLT_DoubleJetsC100_SingleBTagCSV_p026_;
    bool HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350_;
    TBranch *b_HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350_;
    bool loaded_HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350_;
    bool HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6_;
    TBranch *b_HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6_;
    bool loaded_HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6_;
    bool HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172_;
    TBranch *b_HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172_;
    bool loaded_HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172_;
    bool HLT_DoubleL2Mu23NoVtx_2Cha_;
    TBranch *b_HLT_DoubleL2Mu23NoVtx_2Cha_;
    bool loaded_HLT_DoubleL2Mu23NoVtx_2Cha_;
    bool HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_;
    TBranch *b_HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_;
    bool loaded_HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_;
    bool HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_NoL2Matched_;
    TBranch *b_HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_NoL2Matched_;
    bool loaded_HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_NoL2Matched_;
    bool HLT_DoubleL2Mu23NoVtx_2Cha_NoL2Matched_;
    TBranch *b_HLT_DoubleL2Mu23NoVtx_2Cha_NoL2Matched_;
    bool loaded_HLT_DoubleL2Mu23NoVtx_2Cha_NoL2Matched_;
    bool HLT_DoubleL2Mu25NoVtx_2Cha_;
    TBranch *b_HLT_DoubleL2Mu25NoVtx_2Cha_;
    bool loaded_HLT_DoubleL2Mu25NoVtx_2Cha_;
    bool HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_;
    TBranch *b_HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_;
    bool loaded_HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_;
    bool HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_Eta2p4_;
    TBranch *b_HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_Eta2p4_;
    bool loaded_HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_Eta2p4_;
    bool HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_NoL2Matched_;
    TBranch *b_HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_NoL2Matched_;
    bool loaded_HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_NoL2Matched_;
    bool HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4_;
    TBranch *b_HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4_;
    bool loaded_HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4_;
    bool HLT_DoubleL2Mu25NoVtx_2Cha_NoL2Matched_;
    TBranch *b_HLT_DoubleL2Mu25NoVtx_2Cha_NoL2Matched_;
    bool loaded_HLT_DoubleL2Mu25NoVtx_2Cha_NoL2Matched_;
    bool HLT_DoubleL2Mu30NoVtx_2Cha_CosmicSeed_Eta2p4_;
    TBranch *b_HLT_DoubleL2Mu30NoVtx_2Cha_CosmicSeed_Eta2p4_;
    bool loaded_HLT_DoubleL2Mu30NoVtx_2Cha_CosmicSeed_Eta2p4_;
    bool HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4_;
    TBranch *b_HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4_;
    bool loaded_HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4_;
    bool HLT_DoubleL2Mu50_;
    TBranch *b_HLT_DoubleL2Mu50_;
    bool loaded_HLT_DoubleL2Mu50_;
    bool HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_;
    bool HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;
    bool HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_;
    bool HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_;
    bool HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
    bool HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_;
    TBranch *b_HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_;
    bool loaded_HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_;
    bool HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg_;
    bool HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_;
    bool HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_;
    TBranch *b_HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_;
    bool loaded_HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_;
    bool HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_;
    bool HLT_DoubleMu0_;
    TBranch *b_HLT_DoubleMu0_;
    bool loaded_HLT_DoubleMu0_;
    bool HLT_DoubleMu18NoFiltersNoVtx_;
    TBranch *b_HLT_DoubleMu18NoFiltersNoVtx_;
    bool loaded_HLT_DoubleMu18NoFiltersNoVtx_;
    bool HLT_DoubleMu20_7_Mass0to30_L1_DM4_;
    TBranch *b_HLT_DoubleMu20_7_Mass0to30_L1_DM4_;
    bool loaded_HLT_DoubleMu20_7_Mass0to30_L1_DM4_;
    bool HLT_DoubleMu20_7_Mass0to30_L1_DM4EG_;
    TBranch *b_HLT_DoubleMu20_7_Mass0to30_L1_DM4EG_;
    bool loaded_HLT_DoubleMu20_7_Mass0to30_L1_DM4EG_;
    bool HLT_DoubleMu20_7_Mass0to30_Photon23_;
    TBranch *b_HLT_DoubleMu20_7_Mass0to30_Photon23_;
    bool loaded_HLT_DoubleMu20_7_Mass0to30_Photon23_;
    bool HLT_DoubleMu23NoFiltersNoVtxDisplaced_;
    TBranch *b_HLT_DoubleMu23NoFiltersNoVtxDisplaced_;
    bool loaded_HLT_DoubleMu23NoFiltersNoVtxDisplaced_;
    bool HLT_DoubleMu28NoFiltersNoVtxDisplaced_;
    TBranch *b_HLT_DoubleMu28NoFiltersNoVtxDisplaced_;
    bool loaded_HLT_DoubleMu28NoFiltersNoVtxDisplaced_;
    bool HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi_;
    TBranch *b_HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi_;
    bool loaded_HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi_;
    bool HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05_;
    TBranch *b_HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05_;
    bool loaded_HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05_;
    bool HLT_DoubleMu33NoFiltersNoVtx_;
    TBranch *b_HLT_DoubleMu33NoFiltersNoVtx_;
    bool loaded_HLT_DoubleMu33NoFiltersNoVtx_;
    bool HLT_DoubleMu33NoFiltersNoVtxDisplaced_;
    TBranch *b_HLT_DoubleMu33NoFiltersNoVtxDisplaced_;
    bool loaded_HLT_DoubleMu33NoFiltersNoVtxDisplaced_;
    bool HLT_DoubleMu38NoFiltersNoVtx_;
    TBranch *b_HLT_DoubleMu38NoFiltersNoVtx_;
    bool loaded_HLT_DoubleMu38NoFiltersNoVtx_;
    bool HLT_DoubleMu3_DCA_PFMET50_PFMHT60_;
    TBranch *b_HLT_DoubleMu3_DCA_PFMET50_PFMHT60_;
    bool loaded_HLT_DoubleMu3_DCA_PFMET50_PFMHT60_;
    bool HLT_DoubleMu3_DZ_PFMET50_PFMHT60_;
    TBranch *b_HLT_DoubleMu3_DZ_PFMET50_PFMHT60_;
    bool loaded_HLT_DoubleMu3_DZ_PFMET50_PFMHT60_;
    bool HLT_DoubleMu3_DZ_PFMET70_PFMHT70_;
    TBranch *b_HLT_DoubleMu3_DZ_PFMET70_PFMHT70_;
    bool loaded_HLT_DoubleMu3_DZ_PFMET70_PFMHT70_;
    bool HLT_DoubleMu3_DZ_PFMET90_PFMHT90_;
    TBranch *b_HLT_DoubleMu3_DZ_PFMET90_PFMHT90_;
    bool loaded_HLT_DoubleMu3_DZ_PFMET90_PFMHT90_;
    bool HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_;
    TBranch *b_HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_;
    bool loaded_HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_;
    bool HLT_DoubleMu3_PFMET50_;
    TBranch *b_HLT_DoubleMu3_PFMET50_;
    bool loaded_HLT_DoubleMu3_PFMET50_;
    bool HLT_DoubleMu3_TkMu_DsTau3Mu_;
    TBranch *b_HLT_DoubleMu3_TkMu_DsTau3Mu_;
    bool loaded_HLT_DoubleMu3_TkMu_DsTau3Mu_;
    bool HLT_DoubleMu3_Trk_Tau3mu_;
    TBranch *b_HLT_DoubleMu3_Trk_Tau3mu_;
    bool loaded_HLT_DoubleMu3_Trk_Tau3mu_;
    bool HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass_;
    TBranch *b_HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass_;
    bool loaded_HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass_;
    bool HLT_DoubleMu40NoFiltersNoVtxDisplaced_;
    TBranch *b_HLT_DoubleMu40NoFiltersNoVtxDisplaced_;
    bool loaded_HLT_DoubleMu40NoFiltersNoVtxDisplaced_;
    bool HLT_DoubleMu43NoFiltersNoVtx_;
    TBranch *b_HLT_DoubleMu43NoFiltersNoVtx_;
    bool loaded_HLT_DoubleMu43NoFiltersNoVtx_;
    bool HLT_DoubleMu48NoFiltersNoVtx_;
    TBranch *b_HLT_DoubleMu48NoFiltersNoVtx_;
    bool loaded_HLT_DoubleMu48NoFiltersNoVtx_;
    bool HLT_DoubleMu4_3_Bs_;
    TBranch *b_HLT_DoubleMu4_3_Bs_;
    bool loaded_HLT_DoubleMu4_3_Bs_;
    bool HLT_DoubleMu4_3_Jpsi_;
    TBranch *b_HLT_DoubleMu4_3_Jpsi_;
    bool loaded_HLT_DoubleMu4_3_Jpsi_;
    bool HLT_DoubleMu4_3_Jpsi_Displaced_;
    TBranch *b_HLT_DoubleMu4_3_Jpsi_Displaced_;
    bool loaded_HLT_DoubleMu4_3_Jpsi_Displaced_;
    bool HLT_DoubleMu4_JpsiTrkTrk_Displaced_;
    TBranch *b_HLT_DoubleMu4_JpsiTrkTrk_Displaced_;
    bool loaded_HLT_DoubleMu4_JpsiTrkTrk_Displaced_;
    bool HLT_DoubleMu4_JpsiTrk_Displaced_;
    TBranch *b_HLT_DoubleMu4_JpsiTrk_Displaced_;
    bool loaded_HLT_DoubleMu4_JpsiTrk_Displaced_;
    bool HLT_DoubleMu4_Jpsi_Displaced_;
    TBranch *b_HLT_DoubleMu4_Jpsi_Displaced_;
    bool loaded_HLT_DoubleMu4_Jpsi_Displaced_;
    bool HLT_DoubleMu4_Jpsi_NoVertexing_;
    TBranch *b_HLT_DoubleMu4_Jpsi_NoVertexing_;
    bool loaded_HLT_DoubleMu4_Jpsi_NoVertexing_;
    bool HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_;
    TBranch *b_HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_;
    bool loaded_HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_;
    bool HLT_DoubleMu4_Mass3p8_DZ_PFHT350_;
    TBranch *b_HLT_DoubleMu4_Mass3p8_DZ_PFHT350_;
    bool loaded_HLT_DoubleMu4_Mass3p8_DZ_PFHT350_;
    bool HLT_DoubleMu4_PsiPrimeTrk_Displaced_;
    TBranch *b_HLT_DoubleMu4_PsiPrimeTrk_Displaced_;
    bool loaded_HLT_DoubleMu4_PsiPrimeTrk_Displaced_;
    bool HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_;
    TBranch *b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_;
    bool loaded_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_;
    bool HLT_DoubleMu8_Mass8_PFHT250_;
    TBranch *b_HLT_DoubleMu8_Mass8_PFHT250_;
    bool loaded_HLT_DoubleMu8_Mass8_PFHT250_;
    bool HLT_DoubleMu8_Mass8_PFHT300_;
    TBranch *b_HLT_DoubleMu8_Mass8_PFHT300_;
    bool loaded_HLT_DoubleMu8_Mass8_PFHT300_;
    bool HLT_DoublePFJets100_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_DoublePFJets100_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_DoublePFJets100_CaloBTagDeepCSV_p71_;
    bool HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    TBranch *b_HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool loaded_HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    TBranch *b_HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool loaded_HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool HLT_DoublePFJets200_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_DoublePFJets200_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_DoublePFJets200_CaloBTagDeepCSV_p71_;
    bool HLT_DoublePFJets350_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_DoublePFJets350_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_DoublePFJets350_CaloBTagDeepCSV_p71_;
    bool HLT_DoublePFJets40_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_DoublePFJets40_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_DoublePFJets40_CaloBTagDeepCSV_p71_;
    bool HLT_DoublePhoton33_CaloIdL_;
    TBranch *b_HLT_DoublePhoton33_CaloIdL_;
    bool loaded_HLT_DoublePhoton33_CaloIdL_;
    bool HLT_DoublePhoton60_;
    TBranch *b_HLT_DoublePhoton60_;
    bool loaded_HLT_DoublePhoton60_;
    bool HLT_DoublePhoton70_;
    TBranch *b_HLT_DoublePhoton70_;
    bool loaded_HLT_DoublePhoton70_;
    bool HLT_DoublePhoton85_;
    TBranch *b_HLT_DoublePhoton85_;
    bool loaded_HLT_DoublePhoton85_;
    bool HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_;
    TBranch *b_HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_;
    bool loaded_HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_;
    bool HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;
    bool HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_;
    TBranch *b_HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_;
    bool loaded_HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_;
    bool HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_;
    bool HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
    bool HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_;
    TBranch *b_HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_;
    bool loaded_HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_;
    bool HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg_;
    bool loaded_HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg_;
    bool HLT_DoubleTrkMu_16_6_NoFiltersNoVtx_;
    TBranch *b_HLT_DoubleTrkMu_16_6_NoFiltersNoVtx_;
    bool loaded_HLT_DoubleTrkMu_16_6_NoFiltersNoVtx_;
    bool HLT_ECALHT800_;
    TBranch *b_HLT_ECALHT800_;
    bool loaded_HLT_ECALHT800_;
    bool HLT_EcalCalibration_;
    TBranch *b_HLT_EcalCalibration_;
    bool loaded_HLT_EcalCalibration_;
    bool HLT_Ele105_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele105_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele105_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13_;
    TBranch *b_HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13_;
    bool loaded_HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13_;
    bool HLT_Ele115_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele115_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele115_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele12_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    TBranch *b_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool loaded_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool HLT_Ele12_CaloIdM_TrackIdM_PFJet30_;
    TBranch *b_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_;
    bool loaded_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_;
    bool HLT_Ele135_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele135_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele135_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele145_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele145_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele145_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    TBranch *b_HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool loaded_HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400_;
    TBranch *b_HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400_;
    bool loaded_HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400_;
    bool HLT_Ele15_IsoVVVL_PFHT350_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT350_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT350_;
    bool HLT_Ele15_IsoVVVL_PFHT350_PFMET50_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT350_PFMET50_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT350_PFMET50_;
    bool HLT_Ele15_IsoVVVL_PFHT400_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT400_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT400_;
    bool HLT_Ele15_IsoVVVL_PFHT400_PFMET50_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT400_PFMET50_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT400_PFMET50_;
    bool HLT_Ele15_IsoVVVL_PFHT450_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT450_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT450_;
    bool HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_;
    bool HLT_Ele15_IsoVVVL_PFHT450_PFMET50_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT450_PFMET50_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT450_PFMET50_;
    bool HLT_Ele15_IsoVVVL_PFHT600_;
    TBranch *b_HLT_Ele15_IsoVVVL_PFHT600_;
    bool loaded_HLT_Ele15_IsoVVVL_PFHT600_;
    bool HLT_Ele15_WPLoose_Gsf_;
    TBranch *b_HLT_Ele15_WPLoose_Gsf_;
    bool loaded_HLT_Ele15_WPLoose_Gsf_;
    bool HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_;
    TBranch *b_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_;
    bool loaded_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_;
    bool HLT_Ele17_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_Ele17_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_Ele17_CaloIdL_GsfTrkIdVL_;
    bool HLT_Ele17_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Ele17_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Ele17_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    TBranch *b_HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool loaded_HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool HLT_Ele17_CaloIdM_TrackIdM_PFJet30_;
    TBranch *b_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_;
    bool loaded_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_;
    bool HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    TBranch *b_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool loaded_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Ele17_Ele8_Gsf_;
    TBranch *b_HLT_Ele17_Ele8_Gsf_;
    bool loaded_HLT_Ele17_Ele8_Gsf_;
    bool HLT_Ele17_WPLoose_Gsf_;
    TBranch *b_HLT_Ele17_WPLoose_Gsf_;
    bool loaded_HLT_Ele17_WPLoose_Gsf_;
    bool HLT_Ele200_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele200_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele200_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele20_WPLoose_Gsf_;
    TBranch *b_HLT_Ele20_WPLoose_Gsf_;
    bool loaded_HLT_Ele20_WPLoose_Gsf_;
    bool HLT_Ele20_WPTight_Gsf_;
    TBranch *b_HLT_Ele20_WPTight_Gsf_;
    bool loaded_HLT_Ele20_WPTight_Gsf_;
    bool HLT_Ele20_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele20_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele20_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28_;
    TBranch *b_HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28_;
    bool loaded_HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28_;
    bool HLT_Ele22_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele22_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele22_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29_;
    TBranch *b_HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29_;
    bool loaded_HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29_;
    bool HLT_Ele23_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    TBranch *b_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool loaded_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool HLT_Ele23_CaloIdM_TrackIdM_PFJet30_;
    TBranch *b_HLT_Ele23_CaloIdM_TrackIdM_PFJet30_;
    bool loaded_HLT_Ele23_CaloIdM_TrackIdM_PFJet30_;
    bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    TBranch *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool loaded_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_;
    TBranch *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_;
    bool loaded_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_;
    bool HLT_Ele23_WPLoose_Gsf_;
    TBranch *b_HLT_Ele23_WPLoose_Gsf_;
    bool loaded_HLT_Ele23_WPLoose_Gsf_;
    bool HLT_Ele23_WPLoose_Gsf_WHbbBoost_;
    TBranch *b_HLT_Ele23_WPLoose_Gsf_WHbbBoost_;
    bool loaded_HLT_Ele23_WPLoose_Gsf_WHbbBoost_;
    bool HLT_Ele24_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele24_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_;
    TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_;
    bool loaded_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_;
    bool HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_;
    TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_;
    bool loaded_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_;
    bool HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    bool loaded_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    bool HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    bool loaded_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    bool HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    bool loaded_HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    bool HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    bool loaded_HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    bool HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    bool loaded_HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1_;
    bool HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    bool loaded_HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_;
    bool HLT_Ele250_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele250_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele250_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele25_WPTight_Gsf_;
    TBranch *b_HLT_Ele25_WPTight_Gsf_;
    bool loaded_HLT_Ele25_WPTight_Gsf_;
    bool HLT_Ele25_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele25_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele25_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele25_eta2p1_WPTight_Gsf_;
    TBranch *b_HLT_Ele25_eta2p1_WPTight_Gsf_;
    bool loaded_HLT_Ele25_eta2p1_WPTight_Gsf_;
    bool HLT_Ele27_Ele37_CaloIdL_MW_;
    TBranch *b_HLT_Ele27_Ele37_CaloIdL_MW_;
    bool loaded_HLT_Ele27_Ele37_CaloIdL_MW_;
    bool HLT_Ele27_HighEta_Ele20_Mass55_;
    TBranch *b_HLT_Ele27_HighEta_Ele20_Mass55_;
    bool loaded_HLT_Ele27_HighEta_Ele20_Mass55_;
    bool HLT_Ele27_WPLoose_Gsf_;
    TBranch *b_HLT_Ele27_WPLoose_Gsf_;
    bool loaded_HLT_Ele27_WPLoose_Gsf_;
    bool HLT_Ele27_WPLoose_Gsf_WHbbBoost_;
    TBranch *b_HLT_Ele27_WPLoose_Gsf_WHbbBoost_;
    bool loaded_HLT_Ele27_WPLoose_Gsf_WHbbBoost_;
    bool HLT_Ele27_WPTight_Gsf_;
    TBranch *b_HLT_Ele27_WPTight_Gsf_;
    bool loaded_HLT_Ele27_WPTight_Gsf_;
    bool HLT_Ele27_WPTight_Gsf_L1JetTauSeeded_;
    TBranch *b_HLT_Ele27_WPTight_Gsf_L1JetTauSeeded_;
    bool loaded_HLT_Ele27_WPTight_Gsf_L1JetTauSeeded_;
    bool HLT_Ele27_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele27_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele27_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_;
    TBranch *b_HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_;
    bool loaded_HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_;
    bool HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool HLT_Ele27_eta2p1_WPTight_Gsf_;
    TBranch *b_HLT_Ele27_eta2p1_WPTight_Gsf_;
    bool loaded_HLT_Ele27_eta2p1_WPTight_Gsf_;
    bool HLT_Ele28_HighEta_SC20_Mass55_;
    TBranch *b_HLT_Ele28_HighEta_SC20_Mass55_;
    bool loaded_HLT_Ele28_HighEta_SC20_Mass55_;
    bool HLT_Ele28_WPTight_Gsf_;
    TBranch *b_HLT_Ele28_WPTight_Gsf_;
    bool loaded_HLT_Ele28_WPTight_Gsf_;
    bool HLT_Ele28_eta2p1_WPTight_Gsf_HT150_;
    TBranch *b_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_;
    bool loaded_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_;
    bool HLT_Ele300_CaloIdVT_GsfTrkIdT_;
    TBranch *b_HLT_Ele300_CaloIdVT_GsfTrkIdT_;
    bool loaded_HLT_Ele300_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele30WP60_Ele8_Mass55_;
    TBranch *b_HLT_Ele30WP60_Ele8_Mass55_;
    bool loaded_HLT_Ele30WP60_Ele8_Mass55_;
    bool HLT_Ele30WP60_SC4_Mass55_;
    TBranch *b_HLT_Ele30WP60_SC4_Mass55_;
    bool loaded_HLT_Ele30WP60_SC4_Mass55_;
    bool HLT_Ele30_WPTight_Gsf_;
    TBranch *b_HLT_Ele30_WPTight_Gsf_;
    bool loaded_HLT_Ele30_WPTight_Gsf_;
    bool HLT_Ele30_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele30_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele30_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele30_eta2p1_WPTight_Gsf_;
    TBranch *b_HLT_Ele30_eta2p1_WPTight_Gsf_;
    bool loaded_HLT_Ele30_eta2p1_WPTight_Gsf_;
    bool HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_;
    TBranch *b_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_;
    bool loaded_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_;
    bool HLT_Ele32_WPTight_Gsf_;
    TBranch *b_HLT_Ele32_WPTight_Gsf_;
    bool loaded_HLT_Ele32_WPTight_Gsf_;
    bool HLT_Ele32_WPTight_Gsf_L1DoubleEG_;
    TBranch *b_HLT_Ele32_WPTight_Gsf_L1DoubleEG_;
    bool loaded_HLT_Ele32_WPTight_Gsf_L1DoubleEG_;
    bool HLT_Ele32_eta2p1_WPLoose_Gsf_;
    TBranch *b_HLT_Ele32_eta2p1_WPLoose_Gsf_;
    bool loaded_HLT_Ele32_eta2p1_WPLoose_Gsf_;
    bool HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool HLT_Ele32_eta2p1_WPTight_Gsf_;
    TBranch *b_HLT_Ele32_eta2p1_WPTight_Gsf_;
    bool loaded_HLT_Ele32_eta2p1_WPTight_Gsf_;
    bool HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50_;
    TBranch *b_HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50_;
    bool loaded_HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50_;
    bool HLT_Ele35_WPLoose_Gsf_;
    TBranch *b_HLT_Ele35_WPLoose_Gsf_;
    bool loaded_HLT_Ele35_WPLoose_Gsf_;
    bool HLT_Ele35_WPTight_Gsf_;
    TBranch *b_HLT_Ele35_WPTight_Gsf_;
    bool loaded_HLT_Ele35_WPTight_Gsf_;
    bool HLT_Ele35_WPTight_Gsf_L1EGMT_;
    TBranch *b_HLT_Ele35_WPTight_Gsf_L1EGMT_;
    bool loaded_HLT_Ele35_WPTight_Gsf_L1EGMT_;
    bool HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
    bool HLT_Ele38_WPTight_Gsf_;
    TBranch *b_HLT_Ele38_WPTight_Gsf_;
    bool loaded_HLT_Ele38_WPTight_Gsf_;
    bool HLT_Ele40_WPTight_Gsf_;
    TBranch *b_HLT_Ele40_WPTight_Gsf_;
    bool loaded_HLT_Ele40_WPTight_Gsf_;
    bool HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_;
    TBranch *b_HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_;
    bool loaded_HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_;
    bool HLT_Ele45_WPLoose_Gsf_;
    TBranch *b_HLT_Ele45_WPLoose_Gsf_;
    bool loaded_HLT_Ele45_WPLoose_Gsf_;
    bool HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded_;
    TBranch *b_HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded_;
    bool loaded_HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded_;
    bool HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_;
    TBranch *b_HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_;
    bool loaded_HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_;
    bool HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_;
    TBranch *b_HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_;
    bool loaded_HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_;
    bool HLT_Ele50_IsoVVVL_PFHT400_;
    TBranch *b_HLT_Ele50_IsoVVVL_PFHT400_;
    bool loaded_HLT_Ele50_IsoVVVL_PFHT400_;
    bool HLT_Ele50_IsoVVVL_PFHT450_;
    TBranch *b_HLT_Ele50_IsoVVVL_PFHT450_;
    bool loaded_HLT_Ele50_IsoVVVL_PFHT450_;
    bool HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    TBranch *b_HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool loaded_HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_;
    bool HLT_Ele8_CaloIdM_TrackIdM_PFJet30_;
    TBranch *b_HLT_Ele8_CaloIdM_TrackIdM_PFJet30_;
    bool loaded_HLT_Ele8_CaloIdM_TrackIdM_PFJet30_;
    bool HLT_FullTracks_Multiplicity100_;
    TBranch *b_HLT_FullTracks_Multiplicity100_;
    bool loaded_HLT_FullTracks_Multiplicity100_;
    bool HLT_FullTracks_Multiplicity130_;
    TBranch *b_HLT_FullTracks_Multiplicity130_;
    bool loaded_HLT_FullTracks_Multiplicity130_;
    bool HLT_FullTracks_Multiplicity150_;
    TBranch *b_HLT_FullTracks_Multiplicity150_;
    bool loaded_HLT_FullTracks_Multiplicity150_;
    bool HLT_FullTracks_Multiplicity80_;
    TBranch *b_HLT_FullTracks_Multiplicity80_;
    bool loaded_HLT_FullTracks_Multiplicity80_;
    bool HLT_GlobalRunHPDNoise_;
    TBranch *b_HLT_GlobalRunHPDNoise_;
    bool loaded_HLT_GlobalRunHPDNoise_;
    bool HLT_HISinglePhoton10_;
    TBranch *b_HLT_HISinglePhoton10_;
    bool loaded_HLT_HISinglePhoton10_;
    bool HLT_HISinglePhoton15_;
    TBranch *b_HLT_HISinglePhoton15_;
    bool loaded_HLT_HISinglePhoton15_;
    bool HLT_HISinglePhoton20_;
    TBranch *b_HLT_HISinglePhoton20_;
    bool loaded_HLT_HISinglePhoton20_;
    bool HLT_HISinglePhoton40_;
    TBranch *b_HLT_HISinglePhoton40_;
    bool loaded_HLT_HISinglePhoton40_;
    bool HLT_HISinglePhoton60_;
    TBranch *b_HLT_HISinglePhoton60_;
    bool loaded_HLT_HISinglePhoton60_;
    bool HLT_HT200_;
    TBranch *b_HLT_HT200_;
    bool loaded_HLT_HT200_;
    bool HLT_HT2000_;
    TBranch *b_HLT_HT2000_;
    bool loaded_HLT_HT2000_;
    bool HLT_HT200_DisplacedDijet40_DisplacedTrack_;
    TBranch *b_HLT_HT200_DisplacedDijet40_DisplacedTrack_;
    bool loaded_HLT_HT200_DisplacedDijet40_DisplacedTrack_;
    bool HLT_HT2500_;
    TBranch *b_HLT_HT2500_;
    bool loaded_HLT_HT2500_;
    bool HLT_HT250_CaloMET70_;
    TBranch *b_HLT_HT250_CaloMET70_;
    bool loaded_HLT_HT250_CaloMET70_;
    bool HLT_HT250_DisplacedDijet40_DisplacedTrack_;
    TBranch *b_HLT_HT250_DisplacedDijet40_DisplacedTrack_;
    bool loaded_HLT_HT250_DisplacedDijet40_DisplacedTrack_;
    bool HLT_HT275_;
    TBranch *b_HLT_HT275_;
    bool loaded_HLT_HT275_;
    bool HLT_HT300_Beamspot_;
    TBranch *b_HLT_HT300_Beamspot_;
    bool loaded_HLT_HT300_Beamspot_;
    bool HLT_HT325_;
    TBranch *b_HLT_HT325_;
    bool loaded_HLT_HT325_;
    bool HLT_HT350_DisplacedDijet40_DisplacedTrack_;
    TBranch *b_HLT_HT350_DisplacedDijet40_DisplacedTrack_;
    bool loaded_HLT_HT350_DisplacedDijet40_DisplacedTrack_;
    bool HLT_HT350_DisplacedDijet40_Inclusive_;
    TBranch *b_HLT_HT350_DisplacedDijet40_Inclusive_;
    bool loaded_HLT_HT350_DisplacedDijet40_Inclusive_;
    bool HLT_HT350_DisplacedDijet80_DisplacedTrack_;
    TBranch *b_HLT_HT350_DisplacedDijet80_DisplacedTrack_;
    bool loaded_HLT_HT350_DisplacedDijet80_DisplacedTrack_;
    bool HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack_;
    TBranch *b_HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack_;
    bool loaded_HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack_;
    bool HLT_HT400_DisplacedDijet40_DisplacedTrack_;
    TBranch *b_HLT_HT400_DisplacedDijet40_DisplacedTrack_;
    bool loaded_HLT_HT400_DisplacedDijet40_DisplacedTrack_;
    bool HLT_HT400_DisplacedDijet40_Inclusive_;
    TBranch *b_HLT_HT400_DisplacedDijet40_Inclusive_;
    bool loaded_HLT_HT400_DisplacedDijet40_Inclusive_;
    bool HLT_HT410to430_;
    TBranch *b_HLT_HT410to430_;
    bool loaded_HLT_HT410to430_;
    bool HLT_HT425_;
    TBranch *b_HLT_HT425_;
    bool loaded_HLT_HT425_;
    bool HLT_HT430_DisplacedDijet40_DisplacedTrack_;
    TBranch *b_HLT_HT430_DisplacedDijet40_DisplacedTrack_;
    bool loaded_HLT_HT430_DisplacedDijet40_DisplacedTrack_;
    bool HLT_HT430_DisplacedDijet60_DisplacedTrack_;
    TBranch *b_HLT_HT430_DisplacedDijet60_DisplacedTrack_;
    bool loaded_HLT_HT430_DisplacedDijet60_DisplacedTrack_;
    bool HLT_HT430to450_;
    TBranch *b_HLT_HT430to450_;
    bool loaded_HLT_HT430to450_;
    bool HLT_HT450_Beamspot_;
    TBranch *b_HLT_HT450_Beamspot_;
    bool loaded_HLT_HT450_Beamspot_;
    bool HLT_HT450to470_;
    TBranch *b_HLT_HT450to470_;
    bool loaded_HLT_HT450to470_;
    bool HLT_HT470to500_;
    TBranch *b_HLT_HT470to500_;
    bool loaded_HLT_HT470to500_;
    bool HLT_HT500_DisplacedDijet40_DisplacedTrack_;
    TBranch *b_HLT_HT500_DisplacedDijet40_DisplacedTrack_;
    bool loaded_HLT_HT500_DisplacedDijet40_DisplacedTrack_;
    bool HLT_HT500_DisplacedDijet40_Inclusive_;
    TBranch *b_HLT_HT500_DisplacedDijet40_Inclusive_;
    bool loaded_HLT_HT500_DisplacedDijet40_Inclusive_;
    bool HLT_HT500to550_;
    TBranch *b_HLT_HT500to550_;
    bool loaded_HLT_HT500to550_;
    bool HLT_HT550_DisplacedDijet40_Inclusive_;
    TBranch *b_HLT_HT550_DisplacedDijet40_Inclusive_;
    bool loaded_HLT_HT550_DisplacedDijet40_Inclusive_;
    bool HLT_HT550_DisplacedDijet60_Inclusive_;
    TBranch *b_HLT_HT550_DisplacedDijet60_Inclusive_;
    bool loaded_HLT_HT550_DisplacedDijet60_Inclusive_;
    bool HLT_HT550_DisplacedDijet80_Inclusive_;
    TBranch *b_HLT_HT550_DisplacedDijet80_Inclusive_;
    bool loaded_HLT_HT550_DisplacedDijet80_Inclusive_;
    bool HLT_HT550to650_;
    TBranch *b_HLT_HT550to650_;
    bool loaded_HLT_HT550to650_;
    bool HLT_HT575_;
    TBranch *b_HLT_HT575_;
    bool loaded_HLT_HT575_;
    bool HLT_HT650_;
    TBranch *b_HLT_HT650_;
    bool loaded_HLT_HT650_;
    bool HLT_HT650_DisplacedDijet60_Inclusive_;
    TBranch *b_HLT_HT650_DisplacedDijet60_Inclusive_;
    bool loaded_HLT_HT650_DisplacedDijet60_Inclusive_;
    bool HLT_HT650_DisplacedDijet80_Inclusive_;
    TBranch *b_HLT_HT650_DisplacedDijet80_Inclusive_;
    bool loaded_HLT_HT650_DisplacedDijet80_Inclusive_;
    bool HLT_HT750_DisplacedDijet80_Inclusive_;
    TBranch *b_HLT_HT750_DisplacedDijet80_Inclusive_;
    bool loaded_HLT_HT750_DisplacedDijet80_Inclusive_;
    bool HLT_HcalCalibration_;
    TBranch *b_HLT_HcalCalibration_;
    bool loaded_HLT_HcalCalibration_;
    bool HLT_HcalIsolatedbunch_;
    TBranch *b_HLT_HcalIsolatedbunch_;
    bool loaded_HLT_HcalIsolatedbunch_;
    bool HLT_HcalNZS_;
    TBranch *b_HLT_HcalNZS_;
    bool loaded_HLT_HcalNZS_;
    bool HLT_HcalPhiSym_;
    TBranch *b_HLT_HcalPhiSym_;
    bool loaded_HLT_HcalPhiSym_;
    bool HLT_IsoMu16_eta2p1_MET30_;
    TBranch *b_HLT_IsoMu16_eta2p1_MET30_;
    bool loaded_HLT_IsoMu16_eta2p1_MET30_;
    bool HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1_;
    TBranch *b_HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1_;
    bool loaded_HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1_;
    bool HLT_IsoMu17_eta2p1_;
    TBranch *b_HLT_IsoMu17_eta2p1_;
    bool loaded_HLT_IsoMu17_eta2p1_;
    bool HLT_IsoMu17_eta2p1_LooseIsoPFTau20_;
    TBranch *b_HLT_IsoMu17_eta2p1_LooseIsoPFTau20_;
    bool loaded_HLT_IsoMu17_eta2p1_LooseIsoPFTau20_;
    bool HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1_;
    bool HLT_IsoMu18_;
    TBranch *b_HLT_IsoMu18_;
    bool loaded_HLT_IsoMu18_;
    bool HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20_;
    TBranch *b_HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20_;
    bool loaded_HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20_;
    bool HLT_IsoMu19_eta2p1_LooseIsoPFTau20_;
    TBranch *b_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_;
    bool loaded_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_;
    bool HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_;
    bool HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool loaded_HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_;
    bool loaded_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_;
    bool HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool loaded_HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool HLT_IsoMu20_;
    TBranch *b_HLT_IsoMu20_;
    bool loaded_HLT_IsoMu20_;
    bool HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    TBranch *b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    bool loaded_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    bool HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    TBranch *b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    bool loaded_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    bool HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    TBranch *b_HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    bool loaded_HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    bool HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    TBranch *b_HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    bool loaded_HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    bool HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    TBranch *b_HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    bool loaded_HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1_;
    bool HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    TBranch *b_HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    bool loaded_HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_;
    bool HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_;
    TBranch *b_HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_;
    bool loaded_HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_;
    bool HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1_;
    TBranch *b_HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1_;
    bool loaded_HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1_;
    bool HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool loaded_HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_;
    bool loaded_HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_;
    bool HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    TBranch *b_HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool loaded_HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_;
    bool HLT_IsoMu22_;
    TBranch *b_HLT_IsoMu22_;
    bool loaded_HLT_IsoMu22_;
    bool HLT_IsoMu22_eta2p1_;
    TBranch *b_HLT_IsoMu22_eta2p1_;
    bool loaded_HLT_IsoMu22_eta2p1_;
    bool HLT_IsoMu24_;
    TBranch *b_HLT_IsoMu24_;
    bool loaded_HLT_IsoMu24_;
    bool HLT_IsoMu24_TwoProngs35_;
    TBranch *b_HLT_IsoMu24_TwoProngs35_;
    bool loaded_HLT_IsoMu24_TwoProngs35_;
    bool HLT_IsoMu24_eta2p1_;
    TBranch *b_HLT_IsoMu24_eta2p1_;
    bool loaded_HLT_IsoMu24_eta2p1_;
    bool HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_;
    TBranch *b_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_;
    bool loaded_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_;
    bool HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1_;
    TBranch *b_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1_;
    bool loaded_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1_;
    bool HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1_;
    TBranch *b_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1_;
    bool loaded_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1_;
    bool HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1_;
    TBranch *b_HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1_;
    bool loaded_HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1_;
    bool HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1_;
    TBranch *b_HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1_;
    bool loaded_HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1_;
    bool HLT_IsoMu27_;
    TBranch *b_HLT_IsoMu27_;
    bool loaded_HLT_IsoMu27_;
    bool HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    TBranch *b_HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    bool loaded_HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    bool HLT_IsoMu27_MET90_;
    TBranch *b_HLT_IsoMu27_MET90_;
    bool loaded_HLT_IsoMu27_MET90_;
    bool HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    TBranch *b_HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    bool loaded_HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    bool HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    TBranch *b_HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    bool loaded_HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_;
    bool HLT_IsoMu30_;
    TBranch *b_HLT_IsoMu30_;
    bool loaded_HLT_IsoMu30_;
    bool HLT_IsoTkMu18_;
    TBranch *b_HLT_IsoTkMu18_;
    bool loaded_HLT_IsoTkMu18_;
    bool HLT_IsoTkMu20_;
    TBranch *b_HLT_IsoTkMu20_;
    bool loaded_HLT_IsoTkMu20_;
    bool HLT_IsoTkMu22_;
    TBranch *b_HLT_IsoTkMu22_;
    bool loaded_HLT_IsoTkMu22_;
    bool HLT_IsoTkMu22_eta2p1_;
    TBranch *b_HLT_IsoTkMu22_eta2p1_;
    bool loaded_HLT_IsoTkMu22_eta2p1_;
    bool HLT_IsoTkMu24_;
    TBranch *b_HLT_IsoTkMu24_;
    bool loaded_HLT_IsoTkMu24_;
    bool HLT_IsoTkMu27_;
    TBranch *b_HLT_IsoTkMu27_;
    bool loaded_HLT_IsoTkMu27_;
    bool HLT_IsoTrackHB_;
    TBranch *b_HLT_IsoTrackHB_;
    bool loaded_HLT_IsoTrackHB_;
    bool HLT_IsoTrackHE_;
    TBranch *b_HLT_IsoTrackHE_;
    bool loaded_HLT_IsoTrackHE_;
    bool HLT_JetE30_NoBPTX_;
    TBranch *b_HLT_JetE30_NoBPTX_;
    bool loaded_HLT_JetE30_NoBPTX_;
    bool HLT_JetE30_NoBPTX3BX_;
    TBranch *b_HLT_JetE30_NoBPTX3BX_;
    bool loaded_HLT_JetE30_NoBPTX3BX_;
    bool HLT_JetE50_NoBPTX3BX_;
    TBranch *b_HLT_JetE50_NoBPTX3BX_;
    bool loaded_HLT_JetE50_NoBPTX3BX_;
    bool HLT_JetE70_NoBPTX3BX_;
    TBranch *b_HLT_JetE70_NoBPTX3BX_;
    bool loaded_HLT_JetE70_NoBPTX3BX_;
    bool HLT_L1BeamGasMinus_;
    TBranch *b_HLT_L1BeamGasMinus_;
    bool loaded_HLT_L1BeamGasMinus_;
    bool HLT_L1BeamGasPlus_;
    TBranch *b_HLT_L1BeamGasPlus_;
    bool loaded_HLT_L1BeamGasPlus_;
    bool HLT_L1BptxMinus_;
    TBranch *b_HLT_L1BptxMinus_;
    bool loaded_HLT_L1BptxMinus_;
    bool HLT_L1BptxPlus_;
    TBranch *b_HLT_L1BptxPlus_;
    bool loaded_HLT_L1BptxPlus_;
    bool HLT_L1BptxXOR_;
    TBranch *b_HLT_L1BptxXOR_;
    bool loaded_HLT_L1BptxXOR_;
    bool HLT_L1ETMHadSeeds_;
    TBranch *b_HLT_L1ETMHadSeeds_;
    bool loaded_HLT_L1ETMHadSeeds_;
    bool HLT_L1FatEvents_;
    TBranch *b_HLT_L1FatEvents_;
    bool loaded_HLT_L1FatEvents_;
    bool HLT_L1FatEvents_part0_;
    TBranch *b_HLT_L1FatEvents_part0_;
    bool loaded_HLT_L1FatEvents_part0_;
    bool HLT_L1FatEvents_part1_;
    TBranch *b_HLT_L1FatEvents_part1_;
    bool loaded_HLT_L1FatEvents_part1_;
    bool HLT_L1FatEvents_part2_;
    TBranch *b_HLT_L1FatEvents_part2_;
    bool loaded_HLT_L1FatEvents_part2_;
    bool HLT_L1FatEvents_part3_;
    TBranch *b_HLT_L1FatEvents_part3_;
    bool loaded_HLT_L1FatEvents_part3_;
    bool HLT_L1MinimumBiasHF_AND_;
    TBranch *b_HLT_L1MinimumBiasHF_AND_;
    bool loaded_HLT_L1MinimumBiasHF_AND_;
    bool HLT_L1MinimumBiasHF_OR_;
    TBranch *b_HLT_L1MinimumBiasHF_OR_;
    bool loaded_HLT_L1MinimumBiasHF_OR_;
    bool HLT_L1NotBptxOR_;
    TBranch *b_HLT_L1NotBptxOR_;
    bool loaded_HLT_L1NotBptxOR_;
    bool HLT_L1SingleMu18_;
    TBranch *b_HLT_L1SingleMu18_;
    bool loaded_HLT_L1SingleMu18_;
    bool HLT_L1SingleMu25_;
    TBranch *b_HLT_L1SingleMu25_;
    bool loaded_HLT_L1SingleMu25_;
    bool HLT_L1SingleMuOpen_;
    TBranch *b_HLT_L1SingleMuOpen_;
    bool loaded_HLT_L1SingleMuOpen_;
    bool HLT_L1SingleMuOpen_DT_;
    TBranch *b_HLT_L1SingleMuOpen_DT_;
    bool loaded_HLT_L1SingleMuOpen_DT_;
    bool HLT_L1UnpairedBunchBptxMinus_;
    TBranch *b_HLT_L1UnpairedBunchBptxMinus_;
    bool loaded_HLT_L1UnpairedBunchBptxMinus_;
    bool HLT_L1UnpairedBunchBptxPlus_;
    TBranch *b_HLT_L1UnpairedBunchBptxPlus_;
    bool loaded_HLT_L1UnpairedBunchBptxPlus_;
    bool HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142_;
    TBranch *b_HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142_;
    bool loaded_HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142_;
    bool HLT_L1_TripleJet_VBF_;
    TBranch *b_HLT_L1_TripleJet_VBF_;
    bool loaded_HLT_L1_TripleJet_VBF_;
    bool HLT_L2DoubleMu23_NoVertex_;
    TBranch *b_HLT_L2DoubleMu23_NoVertex_;
    bool loaded_HLT_L2DoubleMu23_NoVertex_;
    bool HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_;
    TBranch *b_HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_;
    bool loaded_HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_;
    bool HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_;
    TBranch *b_HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_;
    bool loaded_HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_;
    bool HLT_L2Mu10_;
    TBranch *b_HLT_L2Mu10_;
    bool loaded_HLT_L2Mu10_;
    bool HLT_L2Mu10_NoVertex_NoBPTX_;
    TBranch *b_HLT_L2Mu10_NoVertex_NoBPTX_;
    bool loaded_HLT_L2Mu10_NoVertex_NoBPTX_;
    bool HLT_L2Mu10_NoVertex_NoBPTX3BX_;
    TBranch *b_HLT_L2Mu10_NoVertex_NoBPTX3BX_;
    bool loaded_HLT_L2Mu10_NoVertex_NoBPTX3BX_;
    bool HLT_L2Mu23NoVtx_2Cha_;
    TBranch *b_HLT_L2Mu23NoVtx_2Cha_;
    bool loaded_HLT_L2Mu23NoVtx_2Cha_;
    bool HLT_L2Mu23NoVtx_2Cha_CosmicSeed_;
    TBranch *b_HLT_L2Mu23NoVtx_2Cha_CosmicSeed_;
    bool loaded_HLT_L2Mu23NoVtx_2Cha_CosmicSeed_;
    bool HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX_;
    TBranch *b_HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX_;
    bool loaded_HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX_;
    bool HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX_;
    TBranch *b_HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX_;
    bool loaded_HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX_;
    bool HLT_L2Mu50_;
    TBranch *b_HLT_L2Mu50_;
    bool loaded_HLT_L2Mu50_;
    bool HLT_LooseIsoPFTau50_Trk30_eta2p1_;
    TBranch *b_HLT_LooseIsoPFTau50_Trk30_eta2p1_;
    bool loaded_HLT_LooseIsoPFTau50_Trk30_eta2p1_;
    bool HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110_;
    TBranch *b_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110_;
    bool loaded_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110_;
    bool HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_;
    TBranch *b_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_;
    bool loaded_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_;
    bool HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80_;
    TBranch *b_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80_;
    bool loaded_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80_;
    bool HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90_;
    TBranch *b_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90_;
    bool loaded_HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90_;
    bool HLT_MET100_;
    TBranch *b_HLT_MET100_;
    bool loaded_HLT_MET100_;
    bool HLT_MET105_IsoTrk50_;
    TBranch *b_HLT_MET105_IsoTrk50_;
    bool loaded_HLT_MET105_IsoTrk50_;
    bool HLT_MET120_IsoTrk50_;
    TBranch *b_HLT_MET120_IsoTrk50_;
    bool loaded_HLT_MET120_IsoTrk50_;
    bool HLT_MET150_;
    TBranch *b_HLT_MET150_;
    bool loaded_HLT_MET150_;
    bool HLT_MET200_;
    TBranch *b_HLT_MET200_;
    bool loaded_HLT_MET200_;
    bool HLT_MET250_;
    TBranch *b_HLT_MET250_;
    bool loaded_HLT_MET250_;
    bool HLT_MET300_;
    TBranch *b_HLT_MET300_;
    bool loaded_HLT_MET300_;
    bool HLT_MET600_;
    TBranch *b_HLT_MET600_;
    bool loaded_HLT_MET600_;
    bool HLT_MET60_IsoTrk35_Loose_;
    TBranch *b_HLT_MET60_IsoTrk35_Loose_;
    bool loaded_HLT_MET60_IsoTrk35_Loose_;
    bool HLT_MET700_;
    TBranch *b_HLT_MET700_;
    bool loaded_HLT_MET700_;
    bool HLT_MET75_IsoTrk50_;
    TBranch *b_HLT_MET75_IsoTrk50_;
    bool loaded_HLT_MET75_IsoTrk50_;
    bool HLT_MET90_IsoTrk50_;
    TBranch *b_HLT_MET90_IsoTrk50_;
    bool loaded_HLT_MET90_IsoTrk50_;
    bool HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_;
    TBranch *b_HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_;
    bool loaded_HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_;
    bool HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr_;
    TBranch *b_HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr_;
    bool loaded_HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr_;
    bool HLT_MediumChargedIsoPFTau200HighPtRelaxedIso_Trk50_eta2p1_;
    TBranch *b_HLT_MediumChargedIsoPFTau200HighPtRelaxedIso_Trk50_eta2p1_;
    bool loaded_HLT_MediumChargedIsoPFTau200HighPtRelaxedIso_Trk50_eta2p1_;
    bool HLT_MediumChargedIsoPFTau220HighPtRelaxedIso_Trk50_eta2p1_;
    TBranch *b_HLT_MediumChargedIsoPFTau220HighPtRelaxedIso_Trk50_eta2p1_;
    bool loaded_HLT_MediumChargedIsoPFTau220HighPtRelaxedIso_Trk50_eta2p1_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET140_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET140_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET140_;
    bool HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90_;
    TBranch *b_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90_;
    bool loaded_HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90_;
    bool HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    TBranch *b_HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    bool loaded_HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    bool HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_;
    TBranch *b_HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_;
    bool loaded_HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_;
    bool HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    TBranch *b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    bool loaded_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    bool HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight_;
    TBranch *b_HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight_;
    bool loaded_HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight_;
    bool HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight_;
    TBranch *b_HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight_;
    bool loaded_HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight_;
    bool HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    TBranch *b_HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    bool loaded_HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    bool HLT_Mu10_CentralPFJet30_BTagCSV_p13_;
    TBranch *b_HLT_Mu10_CentralPFJet30_BTagCSV_p13_;
    bool loaded_HLT_Mu10_CentralPFJet30_BTagCSV_p13_;
    bool HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60_;
    TBranch *b_HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60_;
    bool loaded_HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60_;
    bool HLT_Mu12_;
    TBranch *b_HLT_Mu12_;
    bool loaded_HLT_Mu12_;
    bool HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    TBranch *b_HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool loaded_HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_;
    bool HLT_Mu12_DoublePhoton20_;
    TBranch *b_HLT_Mu12_DoublePhoton20_;
    bool loaded_HLT_Mu12_DoublePhoton20_;
    bool HLT_Mu12_IP6_part0_;
    TBranch *b_HLT_Mu12_IP6_part0_;
    bool loaded_HLT_Mu12_IP6_part0_;
    bool HLT_Mu12_IP6_part1_;
    TBranch *b_HLT_Mu12_IP6_part1_;
    bool loaded_HLT_Mu12_IP6_part1_;
    bool HLT_Mu12_IP6_part2_;
    TBranch *b_HLT_Mu12_IP6_part2_;
    bool loaded_HLT_Mu12_IP6_part2_;
    bool HLT_Mu12_IP6_part3_;
    TBranch *b_HLT_Mu12_IP6_part3_;
    bool loaded_HLT_Mu12_IP6_part3_;
    bool HLT_Mu12_IP6_part4_;
    TBranch *b_HLT_Mu12_IP6_part4_;
    bool loaded_HLT_Mu12_IP6_part4_;
    bool HLT_Mu12_Photon25_CaloIdL_;
    TBranch *b_HLT_Mu12_Photon25_CaloIdL_;
    bool loaded_HLT_Mu12_Photon25_CaloIdL_;
    bool HLT_Mu12_Photon25_CaloIdL_L1ISO_;
    TBranch *b_HLT_Mu12_Photon25_CaloIdL_L1ISO_;
    bool loaded_HLT_Mu12_Photon25_CaloIdL_L1ISO_;
    bool HLT_Mu12_Photon25_CaloIdL_L1OR_;
    TBranch *b_HLT_Mu12_Photon25_CaloIdL_L1OR_;
    bool loaded_HLT_Mu12_Photon25_CaloIdL_L1OR_;
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    TBranch *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool loaded_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Mu14er_PFMET100_;
    TBranch *b_HLT_Mu14er_PFMET100_;
    bool loaded_HLT_Mu14er_PFMET100_;
    bool HLT_Mu15_;
    TBranch *b_HLT_Mu15_;
    bool loaded_HLT_Mu15_;
    bool HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400_;
    TBranch *b_HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400_;
    bool loaded_HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400_;
    bool HLT_Mu15_IsoVVVL_PFHT350_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT350_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT350_;
    bool HLT_Mu15_IsoVVVL_PFHT350_PFMET50_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT350_PFMET50_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT350_PFMET50_;
    bool HLT_Mu15_IsoVVVL_PFHT400_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT400_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT400_;
    bool HLT_Mu15_IsoVVVL_PFHT400_PFMET50_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT400_PFMET50_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT400_PFMET50_;
    bool HLT_Mu15_IsoVVVL_PFHT450_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT450_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT450_;
    bool HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_;
    bool HLT_Mu15_IsoVVVL_PFHT450_PFMET50_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT450_PFMET50_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT450_PFMET50_;
    bool HLT_Mu15_IsoVVVL_PFHT600_;
    TBranch *b_HLT_Mu15_IsoVVVL_PFHT600_;
    bool loaded_HLT_Mu15_IsoVVVL_PFHT600_;
    bool HLT_Mu16_TkMu0_dEta18_Onia_;
    TBranch *b_HLT_Mu16_TkMu0_dEta18_Onia_;
    bool loaded_HLT_Mu16_TkMu0_dEta18_Onia_;
    bool HLT_Mu16_TkMu0_dEta18_Phi_;
    TBranch *b_HLT_Mu16_TkMu0_dEta18_Phi_;
    bool loaded_HLT_Mu16_TkMu0_dEta18_Phi_;
    bool HLT_Mu16_eta2p1_MET30_;
    TBranch *b_HLT_Mu16_eta2p1_MET30_;
    bool loaded_HLT_Mu16_eta2p1_MET30_;
    bool HLT_Mu17_;
    TBranch *b_HLT_Mu17_;
    bool loaded_HLT_Mu17_;
    bool HLT_Mu17_Mu8_;
    TBranch *b_HLT_Mu17_Mu8_;
    bool loaded_HLT_Mu17_Mu8_;
    bool HLT_Mu17_Mu8_DZ_;
    TBranch *b_HLT_Mu17_Mu8_DZ_;
    bool loaded_HLT_Mu17_Mu8_DZ_;
    bool HLT_Mu17_Mu8_SameSign_;
    TBranch *b_HLT_Mu17_Mu8_SameSign_;
    bool loaded_HLT_Mu17_Mu8_SameSign_;
    bool HLT_Mu17_Mu8_SameSign_DZ_;
    TBranch *b_HLT_Mu17_Mu8_SameSign_DZ_;
    bool loaded_HLT_Mu17_Mu8_SameSign_DZ_;
    bool HLT_Mu17_Photon22_CaloIdL_L1ISO_;
    TBranch *b_HLT_Mu17_Photon22_CaloIdL_L1ISO_;
    bool loaded_HLT_Mu17_Photon22_CaloIdL_L1ISO_;
    bool HLT_Mu17_Photon30_CaloIdL_L1ISO_;
    TBranch *b_HLT_Mu17_Photon30_CaloIdL_L1ISO_;
    bool loaded_HLT_Mu17_Photon30_CaloIdL_L1ISO_;
    bool HLT_Mu17_Photon30_IsoCaloId_;
    TBranch *b_HLT_Mu17_Photon30_IsoCaloId_;
    bool loaded_HLT_Mu17_Photon30_IsoCaloId_;
    bool HLT_Mu17_Photon35_CaloIdL_L1ISO_;
    TBranch *b_HLT_Mu17_Photon35_CaloIdL_L1ISO_;
    bool loaded_HLT_Mu17_Photon35_CaloIdL_L1ISO_;
    bool HLT_Mu17_TkMu8_DZ_;
    TBranch *b_HLT_Mu17_TkMu8_DZ_;
    bool loaded_HLT_Mu17_TkMu8_DZ_;
    bool HLT_Mu17_TrkIsoVVL_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_;
    bool loaded_HLT_Mu17_TrkIsoVVL_;
    bool HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;
    bool loaded_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
    bool loaded_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
    bool loaded_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_;
    bool loaded_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_;
    bool HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    bool loaded_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    bool HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    TBranch *b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    bool loaded_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    bool HLT_Mu18_Mu9_;
    TBranch *b_HLT_Mu18_Mu9_;
    bool loaded_HLT_Mu18_Mu9_;
    bool HLT_Mu18_Mu9_DZ_;
    TBranch *b_HLT_Mu18_Mu9_DZ_;
    bool loaded_HLT_Mu18_Mu9_DZ_;
    bool HLT_Mu18_Mu9_SameSign_;
    TBranch *b_HLT_Mu18_Mu9_SameSign_;
    bool loaded_HLT_Mu18_Mu9_SameSign_;
    bool HLT_Mu18_Mu9_SameSign_DZ_;
    TBranch *b_HLT_Mu18_Mu9_SameSign_DZ_;
    bool loaded_HLT_Mu18_Mu9_SameSign_DZ_;
    bool HLT_Mu19_;
    TBranch *b_HLT_Mu19_;
    bool loaded_HLT_Mu19_;
    bool HLT_Mu19_TrkIsoVVL_;
    TBranch *b_HLT_Mu19_TrkIsoVVL_;
    bool loaded_HLT_Mu19_TrkIsoVVL_;
    bool HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_;
    TBranch *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_;
    bool loaded_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_;
    bool HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_;
    TBranch *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_;
    bool loaded_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_;
    bool HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_;
    TBranch *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_;
    bool loaded_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_;
    bool HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_;
    TBranch *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_;
    bool loaded_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_;
    bool HLT_Mu20_;
    TBranch *b_HLT_Mu20_;
    bool loaded_HLT_Mu20_;
    bool HLT_Mu20_Mu10_;
    TBranch *b_HLT_Mu20_Mu10_;
    bool loaded_HLT_Mu20_Mu10_;
    bool HLT_Mu20_Mu10_DZ_;
    TBranch *b_HLT_Mu20_Mu10_DZ_;
    bool loaded_HLT_Mu20_Mu10_DZ_;
    bool HLT_Mu20_Mu10_SameSign_;
    TBranch *b_HLT_Mu20_Mu10_SameSign_;
    bool loaded_HLT_Mu20_Mu10_SameSign_;
    bool HLT_Mu20_Mu10_SameSign_DZ_;
    TBranch *b_HLT_Mu20_Mu10_SameSign_DZ_;
    bool loaded_HLT_Mu20_Mu10_SameSign_DZ_;
    bool HLT_Mu20_TkMu0_Phi_;
    TBranch *b_HLT_Mu20_TkMu0_Phi_;
    bool loaded_HLT_Mu20_TkMu0_Phi_;
    bool HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL_;
    TBranch *b_HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL_;
    bool loaded_HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL_;
    bool HLT_Mu23_Mu12_;
    TBranch *b_HLT_Mu23_Mu12_;
    bool loaded_HLT_Mu23_Mu12_;
    bool HLT_Mu23_Mu12_DZ_;
    TBranch *b_HLT_Mu23_Mu12_DZ_;
    bool loaded_HLT_Mu23_Mu12_DZ_;
    bool HLT_Mu23_Mu12_SameSign_;
    TBranch *b_HLT_Mu23_Mu12_SameSign_;
    bool loaded_HLT_Mu23_Mu12_SameSign_;
    bool HLT_Mu23_Mu12_SameSign_DZ_;
    TBranch *b_HLT_Mu23_Mu12_SameSign_DZ_;
    bool loaded_HLT_Mu23_Mu12_SameSign_DZ_;
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    TBranch *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool loaded_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_;
    TBranch *b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool loaded_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Mu24_eta2p1_;
    TBranch *b_HLT_Mu24_eta2p1_;
    bool loaded_HLT_Mu24_eta2p1_;
    bool HLT_Mu25_TkMu0_Onia_;
    TBranch *b_HLT_Mu25_TkMu0_Onia_;
    bool loaded_HLT_Mu25_TkMu0_Onia_;
    bool HLT_Mu25_TkMu0_Phi_;
    TBranch *b_HLT_Mu25_TkMu0_Phi_;
    bool loaded_HLT_Mu25_TkMu0_Phi_;
    bool HLT_Mu25_TkMu0_dEta18_Onia_;
    TBranch *b_HLT_Mu25_TkMu0_dEta18_Onia_;
    bool loaded_HLT_Mu25_TkMu0_dEta18_Onia_;
    bool HLT_Mu27_;
    TBranch *b_HLT_Mu27_;
    bool loaded_HLT_Mu27_;
    bool HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_;
    bool HLT_Mu27_Ele37_CaloIdL_MW_;
    TBranch *b_HLT_Mu27_Ele37_CaloIdL_MW_;
    bool loaded_HLT_Mu27_Ele37_CaloIdL_MW_;
    bool HLT_Mu27_TkMu8_;
    TBranch *b_HLT_Mu27_TkMu8_;
    bool loaded_HLT_Mu27_TkMu8_;
    bool HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL_;
    TBranch *b_HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL_;
    bool loaded_HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL_;
    bool HLT_Mu28NoFiltersNoVtx_CentralCaloJet40_;
    TBranch *b_HLT_Mu28NoFiltersNoVtx_CentralCaloJet40_;
    bool loaded_HLT_Mu28NoFiltersNoVtx_CentralCaloJet40_;
    bool HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose_;
    TBranch *b_HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose_;
    bool loaded_HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose_;
    bool HLT_Mu300_;
    TBranch *b_HLT_Mu300_;
    bool loaded_HLT_Mu300_;
    bool HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_;
    bool HLT_Mu30_TkMu0_Psi_;
    TBranch *b_HLT_Mu30_TkMu0_Psi_;
    bool loaded_HLT_Mu30_TkMu0_Psi_;
    bool HLT_Mu30_TkMu0_Upsilon_;
    TBranch *b_HLT_Mu30_TkMu0_Upsilon_;
    bool loaded_HLT_Mu30_TkMu0_Upsilon_;
    bool HLT_Mu30_TkMu11_;
    TBranch *b_HLT_Mu30_TkMu11_;
    bool loaded_HLT_Mu30_TkMu11_;
    bool HLT_Mu30_eta2p1_PFJet150_PFJet50_;
    TBranch *b_HLT_Mu30_eta2p1_PFJet150_PFJet50_;
    bool loaded_HLT_Mu30_eta2p1_PFJet150_PFJet50_;
    bool HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose_;
    TBranch *b_HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose_;
    bool loaded_HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose_;
    bool HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight_;
    TBranch *b_HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight_;
    bool loaded_HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight_;
    bool HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL_;
    TBranch *b_HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL_;
    bool loaded_HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL_;
    bool HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_;
    bool HLT_Mu350_;
    TBranch *b_HLT_Mu350_;
    bool loaded_HLT_Mu350_;
    bool HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_;
    TBranch *b_HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_;
    bool loaded_HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_;
    bool HLT_Mu37_Ele27_CaloIdL_MW_;
    TBranch *b_HLT_Mu37_Ele27_CaloIdL_MW_;
    bool loaded_HLT_Mu37_Ele27_CaloIdL_MW_;
    bool HLT_Mu37_TkMu27_;
    TBranch *b_HLT_Mu37_TkMu27_;
    bool loaded_HLT_Mu37_TkMu27_;
    bool HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose_;
    TBranch *b_HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose_;
    bool loaded_HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose_;
    bool HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight_;
    TBranch *b_HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight_;
    bool loaded_HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight_;
    bool HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL_;
    TBranch *b_HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL_;
    bool loaded_HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL_;
    bool HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose_;
    TBranch *b_HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose_;
    bool loaded_HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose_;
    bool HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL_;
    TBranch *b_HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL_;
    bool loaded_HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL_;
    bool HLT_Mu3_L1SingleMu5orSingleMu7_;
    TBranch *b_HLT_Mu3_L1SingleMu5orSingleMu7_;
    bool loaded_HLT_Mu3_L1SingleMu5orSingleMu7_;
    bool HLT_Mu3_PFJet40_;
    TBranch *b_HLT_Mu3_PFJet40_;
    bool loaded_HLT_Mu3_PFJet40_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight_;
    bool HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    TBranch *b_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    bool loaded_HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    bool HLT_Mu3er_PFHT140_PFMET125_;
    TBranch *b_HLT_Mu3er_PFHT140_PFMET125_;
    bool loaded_HLT_Mu3er_PFHT140_PFMET125_;
    bool HLT_Mu40_TkMu11_;
    TBranch *b_HLT_Mu40_TkMu11_;
    bool loaded_HLT_Mu40_TkMu11_;
    bool HLT_Mu40_eta2p1_PFJet200_PFJet50_;
    TBranch *b_HLT_Mu40_eta2p1_PFJet200_PFJet50_;
    bool loaded_HLT_Mu40_eta2p1_PFJet200_PFJet50_;
    bool HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL_;
    TBranch *b_HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL_;
    bool loaded_HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL_;
    bool HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL_;
    TBranch *b_HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL_;
    bool loaded_HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL_;
    bool HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL_;
    TBranch *b_HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL_;
    bool loaded_HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL_;
    bool HLT_Mu45_eta2p1_;
    TBranch *b_HLT_Mu45_eta2p1_;
    bool loaded_HLT_Mu45_eta2p1_;
    bool HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL_;
    TBranch *b_HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL_;
    bool loaded_HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL_;
    bool HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_;
    TBranch *b_HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_;
    bool loaded_HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_;
    bool HLT_Mu50_;
    TBranch *b_HLT_Mu50_;
    bool loaded_HLT_Mu50_;
    bool HLT_Mu50_IsoVVVL_PFHT400_;
    TBranch *b_HLT_Mu50_IsoVVVL_PFHT400_;
    bool loaded_HLT_Mu50_IsoVVVL_PFHT400_;
    bool HLT_Mu50_IsoVVVL_PFHT450_;
    TBranch *b_HLT_Mu50_IsoVVVL_PFHT450_;
    bool loaded_HLT_Mu50_IsoVVVL_PFHT450_;
    bool HLT_Mu55_;
    TBranch *b_HLT_Mu55_;
    bool loaded_HLT_Mu55_;
    bool HLT_Mu6_PFHT200_PFMET100_;
    TBranch *b_HLT_Mu6_PFHT200_PFMET100_;
    bool loaded_HLT_Mu6_PFHT200_PFMET100_;
    bool HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067_;
    TBranch *b_HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067_;
    bool loaded_HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067_;
    bool HLT_Mu7_IP4_part0_;
    TBranch *b_HLT_Mu7_IP4_part0_;
    bool loaded_HLT_Mu7_IP4_part0_;
    bool HLT_Mu7_IP4_part1_;
    TBranch *b_HLT_Mu7_IP4_part1_;
    bool loaded_HLT_Mu7_IP4_part1_;
    bool HLT_Mu7_IP4_part2_;
    TBranch *b_HLT_Mu7_IP4_part2_;
    bool loaded_HLT_Mu7_IP4_part2_;
    bool HLT_Mu7_IP4_part3_;
    TBranch *b_HLT_Mu7_IP4_part3_;
    bool loaded_HLT_Mu7_IP4_part3_;
    bool HLT_Mu7_IP4_part4_;
    TBranch *b_HLT_Mu7_IP4_part4_;
    bool loaded_HLT_Mu7_IP4_part4_;
    bool HLT_Mu7p5_L2Mu2_Jpsi_;
    TBranch *b_HLT_Mu7p5_L2Mu2_Jpsi_;
    bool loaded_HLT_Mu7p5_L2Mu2_Jpsi_;
    bool HLT_Mu7p5_L2Mu2_Upsilon_;
    TBranch *b_HLT_Mu7p5_L2Mu2_Upsilon_;
    bool loaded_HLT_Mu7p5_L2Mu2_Upsilon_;
    bool HLT_Mu7p5_Track2_Jpsi_;
    TBranch *b_HLT_Mu7p5_Track2_Jpsi_;
    bool loaded_HLT_Mu7p5_Track2_Jpsi_;
    bool HLT_Mu7p5_Track2_Upsilon_;
    TBranch *b_HLT_Mu7p5_Track2_Upsilon_;
    bool loaded_HLT_Mu7p5_Track2_Upsilon_;
    bool HLT_Mu7p5_Track3p5_Jpsi_;
    TBranch *b_HLT_Mu7p5_Track3p5_Jpsi_;
    bool loaded_HLT_Mu7p5_Track3p5_Jpsi_;
    bool HLT_Mu7p5_Track3p5_Upsilon_;
    TBranch *b_HLT_Mu7p5_Track3p5_Upsilon_;
    bool loaded_HLT_Mu7p5_Track3p5_Upsilon_;
    bool HLT_Mu7p5_Track7_Jpsi_;
    TBranch *b_HLT_Mu7p5_Track7_Jpsi_;
    bool loaded_HLT_Mu7p5_Track7_Jpsi_;
    bool HLT_Mu7p5_Track7_Upsilon_;
    TBranch *b_HLT_Mu7p5_Track7_Upsilon_;
    bool loaded_HLT_Mu7p5_Track7_Upsilon_;
    bool HLT_Mu8_;
    TBranch *b_HLT_Mu8_;
    bool loaded_HLT_Mu8_;
    bool HLT_Mu8_DiEle12_CaloIdL_TrackIdL_;
    TBranch *b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_;
    bool loaded_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_;
    bool HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_;
    TBranch *b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_;
    bool loaded_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_;
    bool HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250_;
    TBranch *b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250_;
    bool loaded_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250_;
    bool HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_;
    TBranch *b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_;
    bool loaded_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_;
    bool HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_;
    TBranch *b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_;
    bool loaded_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_;
    bool HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ_;
    TBranch *b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ_;
    bool loaded_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ_;
    bool HLT_Mu8_IP3_part0_;
    TBranch *b_HLT_Mu8_IP3_part0_;
    bool loaded_HLT_Mu8_IP3_part0_;
    bool HLT_Mu8_IP3_part1_;
    TBranch *b_HLT_Mu8_IP3_part1_;
    bool loaded_HLT_Mu8_IP3_part1_;
    bool HLT_Mu8_IP3_part2_;
    TBranch *b_HLT_Mu8_IP3_part2_;
    bool loaded_HLT_Mu8_IP3_part2_;
    bool HLT_Mu8_IP3_part3_;
    TBranch *b_HLT_Mu8_IP3_part3_;
    bool loaded_HLT_Mu8_IP3_part3_;
    bool HLT_Mu8_IP3_part4_;
    TBranch *b_HLT_Mu8_IP3_part4_;
    bool loaded_HLT_Mu8_IP3_part4_;
    bool HLT_Mu8_IP5_part0_;
    TBranch *b_HLT_Mu8_IP5_part0_;
    bool loaded_HLT_Mu8_IP5_part0_;
    bool HLT_Mu8_IP5_part1_;
    TBranch *b_HLT_Mu8_IP5_part1_;
    bool loaded_HLT_Mu8_IP5_part1_;
    bool HLT_Mu8_IP5_part2_;
    TBranch *b_HLT_Mu8_IP5_part2_;
    bool loaded_HLT_Mu8_IP5_part2_;
    bool HLT_Mu8_IP5_part3_;
    TBranch *b_HLT_Mu8_IP5_part3_;
    bool loaded_HLT_Mu8_IP5_part3_;
    bool HLT_Mu8_IP5_part4_;
    TBranch *b_HLT_Mu8_IP5_part4_;
    bool loaded_HLT_Mu8_IP5_part4_;
    bool HLT_Mu8_IP6_part0_;
    TBranch *b_HLT_Mu8_IP6_part0_;
    bool loaded_HLT_Mu8_IP6_part0_;
    bool HLT_Mu8_IP6_part1_;
    TBranch *b_HLT_Mu8_IP6_part1_;
    bool loaded_HLT_Mu8_IP6_part1_;
    bool HLT_Mu8_IP6_part2_;
    TBranch *b_HLT_Mu8_IP6_part2_;
    bool loaded_HLT_Mu8_IP6_part2_;
    bool HLT_Mu8_IP6_part3_;
    TBranch *b_HLT_Mu8_IP6_part3_;
    bool loaded_HLT_Mu8_IP6_part3_;
    bool HLT_Mu8_IP6_part4_;
    TBranch *b_HLT_Mu8_IP6_part4_;
    bool loaded_HLT_Mu8_IP6_part4_;
    bool HLT_Mu8_TrkIsoVVL_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_;
    bool loaded_HLT_Mu8_TrkIsoVVL_;
    bool HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_;
    bool loaded_HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_;
    bool HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5_;
    TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5_;
    bool loaded_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5_;
    bool HLT_Mu9_IP4_part0_;
    TBranch *b_HLT_Mu9_IP4_part0_;
    bool loaded_HLT_Mu9_IP4_part0_;
    bool HLT_Mu9_IP4_part1_;
    TBranch *b_HLT_Mu9_IP4_part1_;
    bool loaded_HLT_Mu9_IP4_part1_;
    bool HLT_Mu9_IP4_part2_;
    TBranch *b_HLT_Mu9_IP4_part2_;
    bool loaded_HLT_Mu9_IP4_part2_;
    bool HLT_Mu9_IP4_part3_;
    TBranch *b_HLT_Mu9_IP4_part3_;
    bool loaded_HLT_Mu9_IP4_part3_;
    bool HLT_Mu9_IP4_part4_;
    TBranch *b_HLT_Mu9_IP4_part4_;
    bool loaded_HLT_Mu9_IP4_part4_;
    bool HLT_Mu9_IP5_part0_;
    TBranch *b_HLT_Mu9_IP5_part0_;
    bool loaded_HLT_Mu9_IP5_part0_;
    bool HLT_Mu9_IP5_part1_;
    TBranch *b_HLT_Mu9_IP5_part1_;
    bool loaded_HLT_Mu9_IP5_part1_;
    bool HLT_Mu9_IP5_part2_;
    TBranch *b_HLT_Mu9_IP5_part2_;
    bool loaded_HLT_Mu9_IP5_part2_;
    bool HLT_Mu9_IP5_part3_;
    TBranch *b_HLT_Mu9_IP5_part3_;
    bool loaded_HLT_Mu9_IP5_part3_;
    bool HLT_Mu9_IP5_part4_;
    TBranch *b_HLT_Mu9_IP5_part4_;
    bool loaded_HLT_Mu9_IP5_part4_;
    bool HLT_Mu9_IP6_part0_;
    TBranch *b_HLT_Mu9_IP6_part0_;
    bool loaded_HLT_Mu9_IP6_part0_;
    bool HLT_Mu9_IP6_part1_;
    TBranch *b_HLT_Mu9_IP6_part1_;
    bool loaded_HLT_Mu9_IP6_part1_;
    bool HLT_Mu9_IP6_part2_;
    TBranch *b_HLT_Mu9_IP6_part2_;
    bool loaded_HLT_Mu9_IP6_part2_;
    bool HLT_Mu9_IP6_part3_;
    TBranch *b_HLT_Mu9_IP6_part3_;
    bool loaded_HLT_Mu9_IP6_part3_;
    bool HLT_Mu9_IP6_part4_;
    TBranch *b_HLT_Mu9_IP6_part4_;
    bool loaded_HLT_Mu9_IP6_part4_;
    bool HLT_OldMu100_;
    TBranch *b_HLT_OldMu100_;
    bool loaded_HLT_OldMu100_;
    bool HLT_PFHT1050_;
    TBranch *b_HLT_PFHT1050_;
    bool loaded_HLT_PFHT1050_;
    bool HLT_PFHT125_;
    TBranch *b_HLT_PFHT125_;
    bool loaded_HLT_PFHT125_;
    bool HLT_PFHT180_;
    TBranch *b_HLT_PFHT180_;
    bool loaded_HLT_PFHT180_;
    bool HLT_PFHT200_;
    TBranch *b_HLT_PFHT200_;
    bool loaded_HLT_PFHT200_;
    bool HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57_;
    TBranch *b_HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57_;
    bool loaded_HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57_;
    bool HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63_;
    TBranch *b_HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63_;
    bool loaded_HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63_;
    bool HLT_PFHT200_PFAlphaT0p51_;
    TBranch *b_HLT_PFHT200_PFAlphaT0p51_;
    bool loaded_HLT_PFHT200_PFAlphaT0p51_;
    bool HLT_PFHT250_;
    TBranch *b_HLT_PFHT250_;
    bool loaded_HLT_PFHT250_;
    bool HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55_;
    TBranch *b_HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55_;
    bool loaded_HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55_;
    bool HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58_;
    TBranch *b_HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58_;
    bool loaded_HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58_;
    bool HLT_PFHT300_;
    TBranch *b_HLT_PFHT300_;
    bool loaded_HLT_PFHT300_;
    bool HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53_;
    TBranch *b_HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53_;
    bool loaded_HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53_;
    bool HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54_;
    TBranch *b_HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54_;
    bool loaded_HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54_;
    bool HLT_PFHT300_PFMET100_;
    TBranch *b_HLT_PFHT300_PFMET100_;
    bool loaded_HLT_PFHT300_PFMET100_;
    bool HLT_PFHT300_PFMET110_;
    TBranch *b_HLT_PFHT300_PFMET110_;
    bool loaded_HLT_PFHT300_PFMET110_;
    bool HLT_PFHT330PT30_QuadPFJet_75_60_45_40_;
    TBranch *b_HLT_PFHT330PT30_QuadPFJet_75_60_45_40_;
    bool loaded_HLT_PFHT330PT30_QuadPFJet_75_60_45_40_;
    bool HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
    TBranch *b_HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
    bool loaded_HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
    bool HLT_PFHT350_;
    TBranch *b_HLT_PFHT350_;
    bool loaded_HLT_PFHT350_;
    bool HLT_PFHT350MinPFJet15_;
    TBranch *b_HLT_PFHT350MinPFJet15_;
    bool loaded_HLT_PFHT350MinPFJet15_;
    bool HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52_;
    TBranch *b_HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52_;
    bool loaded_HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52_;
    bool HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53_;
    TBranch *b_HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53_;
    bool loaded_HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53_;
    bool HLT_PFHT370_;
    TBranch *b_HLT_PFHT370_;
    bool loaded_HLT_PFHT370_;
    bool HLT_PFHT400_;
    TBranch *b_HLT_PFHT400_;
    bool loaded_HLT_PFHT400_;
    bool HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51_;
    TBranch *b_HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51_;
    bool loaded_HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51_;
    bool HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52_;
    TBranch *b_HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52_;
    bool loaded_HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52_;
    bool HLT_PFHT400_SixJet30_;
    TBranch *b_HLT_PFHT400_SixJet30_;
    bool loaded_HLT_PFHT400_SixJet30_;
    bool HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;
    TBranch *b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;
    bool loaded_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;
    bool HLT_PFHT400_SixPFJet32_;
    TBranch *b_HLT_PFHT400_SixPFJet32_;
    bool loaded_HLT_PFHT400_SixPFJet32_;
    bool HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_;
    TBranch *b_HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_;
    bool loaded_HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_;
    bool HLT_PFHT430_;
    TBranch *b_HLT_PFHT430_;
    bool loaded_HLT_PFHT430_;
    bool HLT_PFHT450_SixJet40_;
    TBranch *b_HLT_PFHT450_SixJet40_;
    bool loaded_HLT_PFHT450_SixJet40_;
    bool HLT_PFHT450_SixJet40_BTagCSV_p056_;
    TBranch *b_HLT_PFHT450_SixJet40_BTagCSV_p056_;
    bool loaded_HLT_PFHT450_SixJet40_BTagCSV_p056_;
    bool HLT_PFHT450_SixPFJet36_;
    TBranch *b_HLT_PFHT450_SixPFJet36_;
    bool loaded_HLT_PFHT450_SixPFJet36_;
    bool HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_;
    TBranch *b_HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_;
    bool loaded_HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_;
    bool HLT_PFHT475_;
    TBranch *b_HLT_PFHT475_;
    bool loaded_HLT_PFHT475_;
    bool HLT_PFHT500_PFMET100_PFMHT100_IDTight_;
    TBranch *b_HLT_PFHT500_PFMET100_PFMHT100_IDTight_;
    bool loaded_HLT_PFHT500_PFMET100_PFMHT100_IDTight_;
    bool HLT_PFHT500_PFMET110_PFMHT110_IDTight_;
    TBranch *b_HLT_PFHT500_PFMET110_PFMHT110_IDTight_;
    bool loaded_HLT_PFHT500_PFMET110_PFMHT110_IDTight_;
    bool HLT_PFHT510_;
    TBranch *b_HLT_PFHT510_;
    bool loaded_HLT_PFHT510_;
    bool HLT_PFHT550_4JetPt50_;
    TBranch *b_HLT_PFHT550_4JetPt50_;
    bool loaded_HLT_PFHT550_4JetPt50_;
    bool HLT_PFHT590_;
    TBranch *b_HLT_PFHT590_;
    bool loaded_HLT_PFHT590_;
    bool HLT_PFHT600_;
    TBranch *b_HLT_PFHT600_;
    bool loaded_HLT_PFHT600_;
    bool HLT_PFHT650_;
    TBranch *b_HLT_PFHT650_;
    bool loaded_HLT_PFHT650_;
    bool HLT_PFHT650_4JetPt50_;
    TBranch *b_HLT_PFHT650_4JetPt50_;
    bool loaded_HLT_PFHT650_4JetPt50_;
    bool HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_;
    TBranch *b_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_;
    bool loaded_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_;
    bool HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_;
    TBranch *b_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_;
    bool loaded_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_;
    bool HLT_PFHT680_;
    TBranch *b_HLT_PFHT680_;
    bool loaded_HLT_PFHT680_;
    bool HLT_PFHT700_PFMET85_PFMHT85_IDTight_;
    TBranch *b_HLT_PFHT700_PFMET85_PFMHT85_IDTight_;
    bool loaded_HLT_PFHT700_PFMET85_PFMHT85_IDTight_;
    bool HLT_PFHT700_PFMET95_PFMHT95_IDTight_;
    TBranch *b_HLT_PFHT700_PFMET95_PFMHT95_IDTight_;
    bool loaded_HLT_PFHT700_PFMET95_PFMHT95_IDTight_;
    bool HLT_PFHT750_4JetPt50_;
    TBranch *b_HLT_PFHT750_4JetPt50_;
    bool loaded_HLT_PFHT750_4JetPt50_;
    bool HLT_PFHT750_4JetPt70_;
    TBranch *b_HLT_PFHT750_4JetPt70_;
    bool loaded_HLT_PFHT750_4JetPt70_;
    bool HLT_PFHT750_4JetPt80_;
    TBranch *b_HLT_PFHT750_4JetPt80_;
    bool loaded_HLT_PFHT750_4JetPt80_;
    bool HLT_PFHT780_;
    TBranch *b_HLT_PFHT780_;
    bool loaded_HLT_PFHT780_;
    bool HLT_PFHT800_;
    TBranch *b_HLT_PFHT800_;
    bool loaded_HLT_PFHT800_;
    bool HLT_PFHT800_4JetPt50_;
    TBranch *b_HLT_PFHT800_4JetPt50_;
    bool loaded_HLT_PFHT800_4JetPt50_;
    bool HLT_PFHT800_PFMET75_PFMHT75_IDTight_;
    TBranch *b_HLT_PFHT800_PFMET75_PFMHT75_IDTight_;
    bool loaded_HLT_PFHT800_PFMET75_PFMHT75_IDTight_;
    bool HLT_PFHT800_PFMET85_PFMHT85_IDTight_;
    TBranch *b_HLT_PFHT800_PFMET85_PFMHT85_IDTight_;
    bool loaded_HLT_PFHT800_PFMET85_PFMHT85_IDTight_;
    bool HLT_PFHT850_4JetPt50_;
    TBranch *b_HLT_PFHT850_4JetPt50_;
    bool loaded_HLT_PFHT850_4JetPt50_;
    bool HLT_PFHT890_;
    TBranch *b_HLT_PFHT890_;
    bool loaded_HLT_PFHT890_;
    bool HLT_PFHT900_;
    TBranch *b_HLT_PFHT900_;
    bool loaded_HLT_PFHT900_;
    bool HLT_PFJet140_;
    TBranch *b_HLT_PFJet140_;
    bool loaded_HLT_PFJet140_;
    bool HLT_PFJet15_;
    TBranch *b_HLT_PFJet15_;
    bool loaded_HLT_PFJet15_;
    bool HLT_PFJet15_NoCaloMatched_;
    TBranch *b_HLT_PFJet15_NoCaloMatched_;
    bool loaded_HLT_PFJet15_NoCaloMatched_;
    bool HLT_PFJet200_;
    TBranch *b_HLT_PFJet200_;
    bool loaded_HLT_PFJet200_;
    bool HLT_PFJet25_;
    TBranch *b_HLT_PFJet25_;
    bool loaded_HLT_PFJet25_;
    bool HLT_PFJet25_NoCaloMatched_;
    TBranch *b_HLT_PFJet25_NoCaloMatched_;
    bool loaded_HLT_PFJet25_NoCaloMatched_;
    bool HLT_PFJet260_;
    TBranch *b_HLT_PFJet260_;
    bool loaded_HLT_PFJet260_;
    bool HLT_PFJet320_;
    TBranch *b_HLT_PFJet320_;
    bool loaded_HLT_PFJet320_;
    bool HLT_PFJet40_;
    TBranch *b_HLT_PFJet40_;
    bool loaded_HLT_PFJet40_;
    bool HLT_PFJet400_;
    TBranch *b_HLT_PFJet400_;
    bool loaded_HLT_PFJet400_;
    bool HLT_PFJet450_;
    TBranch *b_HLT_PFJet450_;
    bool loaded_HLT_PFJet450_;
    bool HLT_PFJet500_;
    TBranch *b_HLT_PFJet500_;
    bool loaded_HLT_PFJet500_;
    bool HLT_PFJet550_;
    TBranch *b_HLT_PFJet550_;
    bool loaded_HLT_PFJet550_;
    bool HLT_PFJet60_;
    TBranch *b_HLT_PFJet60_;
    bool loaded_HLT_PFJet60_;
    bool HLT_PFJet80_;
    TBranch *b_HLT_PFJet80_;
    bool loaded_HLT_PFJet80_;
    bool HLT_PFJetFwd140_;
    TBranch *b_HLT_PFJetFwd140_;
    bool loaded_HLT_PFJetFwd140_;
    bool HLT_PFJetFwd15_;
    TBranch *b_HLT_PFJetFwd15_;
    bool loaded_HLT_PFJetFwd15_;
    bool HLT_PFJetFwd200_;
    TBranch *b_HLT_PFJetFwd200_;
    bool loaded_HLT_PFJetFwd200_;
    bool HLT_PFJetFwd25_;
    TBranch *b_HLT_PFJetFwd25_;
    bool loaded_HLT_PFJetFwd25_;
    bool HLT_PFJetFwd260_;
    TBranch *b_HLT_PFJetFwd260_;
    bool loaded_HLT_PFJetFwd260_;
    bool HLT_PFJetFwd320_;
    TBranch *b_HLT_PFJetFwd320_;
    bool loaded_HLT_PFJetFwd320_;
    bool HLT_PFJetFwd40_;
    TBranch *b_HLT_PFJetFwd40_;
    bool loaded_HLT_PFJetFwd40_;
    bool HLT_PFJetFwd400_;
    TBranch *b_HLT_PFJetFwd400_;
    bool loaded_HLT_PFJetFwd400_;
    bool HLT_PFJetFwd450_;
    TBranch *b_HLT_PFJetFwd450_;
    bool loaded_HLT_PFJetFwd450_;
    bool HLT_PFJetFwd500_;
    TBranch *b_HLT_PFJetFwd500_;
    bool loaded_HLT_PFJetFwd500_;
    bool HLT_PFJetFwd60_;
    TBranch *b_HLT_PFJetFwd60_;
    bool loaded_HLT_PFJetFwd60_;
    bool HLT_PFJetFwd80_;
    TBranch *b_HLT_PFJetFwd80_;
    bool loaded_HLT_PFJetFwd80_;
    bool HLT_PFMET100_PFMHT100_IDTight_;
    TBranch *b_HLT_PFMET100_PFMHT100_IDTight_;
    bool loaded_HLT_PFMET100_PFMHT100_IDTight_;
    bool HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned_;
    TBranch *b_HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned_;
    bool loaded_HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned_;
    bool HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1_;
    TBranch *b_HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1_;
    bool loaded_HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1_;
    bool HLT_PFMET100_PFMHT100_IDTight_PFHT60_;
    TBranch *b_HLT_PFMET100_PFMHT100_IDTight_PFHT60_;
    bool loaded_HLT_PFMET100_PFMHT100_IDTight_PFHT60_;
    bool HLT_PFMET110_PFMHT110_IDTight_;
    TBranch *b_HLT_PFMET110_PFMHT110_IDTight_;
    bool loaded_HLT_PFMET110_PFMHT110_IDTight_;
    bool HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1_;
    TBranch *b_HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1_;
    bool loaded_HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1_;
    bool HLT_PFMET120_BTagCSV_p067_;
    TBranch *b_HLT_PFMET120_BTagCSV_p067_;
    bool loaded_HLT_PFMET120_BTagCSV_p067_;
    bool HLT_PFMET120_Mu5_;
    TBranch *b_HLT_PFMET120_Mu5_;
    bool loaded_HLT_PFMET120_Mu5_;
    bool HLT_PFMET120_PFMHT120_IDTight_;
    TBranch *b_HLT_PFMET120_PFMHT120_IDTight_;
    bool loaded_HLT_PFMET120_PFMHT120_IDTight_;
    bool HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1_;
    TBranch *b_HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1_;
    bool loaded_HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1_;
    bool HLT_PFMET120_PFMHT120_IDTight_PFHT60_;
    TBranch *b_HLT_PFMET120_PFMHT120_IDTight_PFHT60_;
    bool loaded_HLT_PFMET120_PFMHT120_IDTight_PFHT60_;
    bool HLT_PFMET130_PFMHT130_IDTight_;
    TBranch *b_HLT_PFMET130_PFMHT130_IDTight_;
    bool loaded_HLT_PFMET130_PFMHT130_IDTight_;
    bool HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1_;
    TBranch *b_HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1_;
    bool loaded_HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1_;
    bool HLT_PFMET140_PFMHT140_IDTight_;
    TBranch *b_HLT_PFMET140_PFMHT140_IDTight_;
    bool loaded_HLT_PFMET140_PFMHT140_IDTight_;
    bool HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1_;
    TBranch *b_HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1_;
    bool loaded_HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1_;
    bool HLT_PFMET170_BeamHaloCleaned_;
    TBranch *b_HLT_PFMET170_BeamHaloCleaned_;
    bool loaded_HLT_PFMET170_BeamHaloCleaned_;
    bool HLT_PFMET170_HBHECleaned_;
    TBranch *b_HLT_PFMET170_HBHECleaned_;
    bool loaded_HLT_PFMET170_HBHECleaned_;
    bool HLT_PFMET170_HBHE_BeamHaloCleaned_;
    TBranch *b_HLT_PFMET170_HBHE_BeamHaloCleaned_;
    bool loaded_HLT_PFMET170_HBHE_BeamHaloCleaned_;
    bool HLT_PFMET170_JetIdCleaned_;
    TBranch *b_HLT_PFMET170_JetIdCleaned_;
    bool loaded_HLT_PFMET170_JetIdCleaned_;
    bool HLT_PFMET170_NoiseCleaned_;
    TBranch *b_HLT_PFMET170_NoiseCleaned_;
    bool loaded_HLT_PFMET170_NoiseCleaned_;
    bool HLT_PFMET170_NotCleaned_;
    TBranch *b_HLT_PFMET170_NotCleaned_;
    bool loaded_HLT_PFMET170_NotCleaned_;
    bool HLT_PFMET200_HBHECleaned_;
    TBranch *b_HLT_PFMET200_HBHECleaned_;
    bool loaded_HLT_PFMET200_HBHECleaned_;
    bool HLT_PFMET200_HBHE_BeamHaloCleaned_;
    TBranch *b_HLT_PFMET200_HBHE_BeamHaloCleaned_;
    bool loaded_HLT_PFMET200_HBHE_BeamHaloCleaned_;
    bool HLT_PFMET200_NotCleaned_;
    TBranch *b_HLT_PFMET200_NotCleaned_;
    bool loaded_HLT_PFMET200_NotCleaned_;
    bool HLT_PFMET250_HBHECleaned_;
    TBranch *b_HLT_PFMET250_HBHECleaned_;
    bool loaded_HLT_PFMET250_HBHECleaned_;
    bool HLT_PFMET300_;
    TBranch *b_HLT_PFMET300_;
    bool loaded_HLT_PFMET300_;
    bool HLT_PFMET300_HBHECleaned_;
    TBranch *b_HLT_PFMET300_HBHECleaned_;
    bool loaded_HLT_PFMET300_HBHECleaned_;
    bool HLT_PFMET400_;
    TBranch *b_HLT_PFMET400_;
    bool loaded_HLT_PFMET400_;
    bool HLT_PFMET500_;
    TBranch *b_HLT_PFMET500_;
    bool loaded_HLT_PFMET500_;
    bool HLT_PFMET600_;
    TBranch *b_HLT_PFMET600_;
    bool loaded_HLT_PFMET600_;
    bool HLT_PFMET90_PFMHT90_IDTight_;
    TBranch *b_HLT_PFMET90_PFMHT90_IDTight_;
    bool loaded_HLT_PFMET90_PFMHT90_IDTight_;
    bool HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    TBranch *b_HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    bool loaded_HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_;
    bool HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_;
    TBranch *b_HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_;
    bool loaded_HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_;
    bool HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_;
    TBranch *b_HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_;
    bool loaded_HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_;
    bool HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    TBranch *b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    bool loaded_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    bool HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_;
    TBranch *b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_;
    bool loaded_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_;
    bool HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_;
    TBranch *b_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_;
    bool loaded_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_;
    bool HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_;
    TBranch *b_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_;
    bool loaded_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_;
    bool HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    TBranch *b_HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    bool loaded_HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_;
    bool HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_;
    TBranch *b_HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_;
    bool loaded_HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_;
    bool HLT_PFMETTypeOne110_PFMHT110_IDTight_;
    TBranch *b_HLT_PFMETTypeOne110_PFMHT110_IDTight_;
    bool loaded_HLT_PFMETTypeOne110_PFMHT110_IDTight_;
    bool HLT_PFMETTypeOne120_PFMHT120_IDTight_;
    TBranch *b_HLT_PFMETTypeOne120_PFMHT120_IDTight_;
    bool loaded_HLT_PFMETTypeOne120_PFMHT120_IDTight_;
    bool HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_;
    TBranch *b_HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_;
    bool loaded_HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_;
    bool HLT_PFMETTypeOne130_PFMHT130_IDTight_;
    TBranch *b_HLT_PFMETTypeOne130_PFMHT130_IDTight_;
    bool loaded_HLT_PFMETTypeOne130_PFMHT130_IDTight_;
    bool HLT_PFMETTypeOne140_PFMHT140_IDTight_;
    TBranch *b_HLT_PFMETTypeOne140_PFMHT140_IDTight_;
    bool loaded_HLT_PFMETTypeOne140_PFMHT140_IDTight_;
    bool HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned_;
    TBranch *b_HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned_;
    bool loaded_HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned_;
    bool HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_;
    TBranch *b_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_;
    bool loaded_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_;
    bool HLT_PFTau120_eta2p1_;
    TBranch *b_HLT_PFTau120_eta2p1_;
    bool loaded_HLT_PFTau120_eta2p1_;
    bool HLT_PFTau140_eta2p1_;
    TBranch *b_HLT_PFTau140_eta2p1_;
    bool loaded_HLT_PFTau140_eta2p1_;
    bool HLT_Photon100EBHE10_;
    TBranch *b_HLT_Photon100EBHE10_;
    bool loaded_HLT_Photon100EBHE10_;
    bool HLT_Photon100EB_TightID_TightIso_;
    TBranch *b_HLT_Photon100EB_TightID_TightIso_;
    bool loaded_HLT_Photon100EB_TightID_TightIso_;
    bool HLT_Photon100EEHE10_;
    TBranch *b_HLT_Photon100EEHE10_;
    bool loaded_HLT_Photon100EEHE10_;
    bool HLT_Photon100EE_TightID_TightIso_;
    TBranch *b_HLT_Photon100EE_TightID_TightIso_;
    bool loaded_HLT_Photon100EE_TightID_TightIso_;
    bool HLT_Photon110EB_TightID_TightIso_;
    TBranch *b_HLT_Photon110EB_TightID_TightIso_;
    bool loaded_HLT_Photon110EB_TightID_TightIso_;
    bool HLT_Photon120_;
    TBranch *b_HLT_Photon120_;
    bool loaded_HLT_Photon120_;
    bool HLT_Photon120EB_TightID_TightIso_;
    TBranch *b_HLT_Photon120EB_TightID_TightIso_;
    bool loaded_HLT_Photon120EB_TightID_TightIso_;
    bool HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    TBranch *b_HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool loaded_HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_;
    TBranch *b_HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool loaded_HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool HLT_Photon120_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon120_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon120_R9Id90_HE10_IsoM_;
    bool HLT_Photon125_;
    TBranch *b_HLT_Photon125_;
    bool loaded_HLT_Photon125_;
    bool HLT_Photon135_PFMET100_;
    TBranch *b_HLT_Photon135_PFMET100_;
    bool loaded_HLT_Photon135_PFMET100_;
    bool HLT_Photon150_;
    TBranch *b_HLT_Photon150_;
    bool loaded_HLT_Photon150_;
    bool HLT_Photon165_HE10_;
    TBranch *b_HLT_Photon165_HE10_;
    bool loaded_HLT_Photon165_HE10_;
    bool HLT_Photon165_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon165_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon165_R9Id90_HE10_IsoM_;
    bool HLT_Photon175_;
    TBranch *b_HLT_Photon175_;
    bool loaded_HLT_Photon175_;
    bool HLT_Photon20_;
    TBranch *b_HLT_Photon20_;
    bool loaded_HLT_Photon20_;
    bool HLT_Photon200_;
    TBranch *b_HLT_Photon200_;
    bool loaded_HLT_Photon200_;
    bool HLT_Photon20_CaloIdVL_IsoL_;
    TBranch *b_HLT_Photon20_CaloIdVL_IsoL_;
    bool loaded_HLT_Photon20_CaloIdVL_IsoL_;
    bool HLT_Photon20_HoverELoose_;
    TBranch *b_HLT_Photon20_HoverELoose_;
    bool loaded_HLT_Photon20_HoverELoose_;
    bool HLT_Photon22_;
    TBranch *b_HLT_Photon22_;
    bool loaded_HLT_Photon22_;
    bool HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    TBranch *b_HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool loaded_HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_;
    TBranch *b_HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool loaded_HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool HLT_Photon22_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon22_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon22_R9Id90_HE10_IsoM_;
    bool HLT_Photon250_NoHE_;
    TBranch *b_HLT_Photon250_NoHE_;
    bool loaded_HLT_Photon250_NoHE_;
    bool HLT_Photon26_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon16_AND_HE10_R9Id65_Eta2_Mass60_;
    TBranch *b_HLT_Photon26_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon16_AND_HE10_R9Id65_Eta2_Mass60_;
    bool loaded_HLT_Photon26_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon16_AND_HE10_R9Id65_Eta2_Mass60_;
    bool HLT_Photon30_;
    TBranch *b_HLT_Photon30_;
    bool loaded_HLT_Photon30_;
    bool HLT_Photon300_NoHE_;
    TBranch *b_HLT_Photon300_NoHE_;
    bool loaded_HLT_Photon300_NoHE_;
    bool HLT_Photon30_HoverELoose_;
    TBranch *b_HLT_Photon30_HoverELoose_;
    bool loaded_HLT_Photon30_HoverELoose_;
    bool HLT_Photon30_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon30_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon30_R9Id90_HE10_IsoM_;
    bool HLT_Photon33_;
    TBranch *b_HLT_Photon33_;
    bool loaded_HLT_Photon33_;
    bool HLT_Photon35_TwoProngs35_;
    TBranch *b_HLT_Photon35_TwoProngs35_;
    bool loaded_HLT_Photon35_TwoProngs35_;
    bool HLT_Photon36_;
    TBranch *b_HLT_Photon36_;
    bool loaded_HLT_Photon36_;
    bool HLT_Photon36_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon22_AND_HE10_R9Id65_Eta2_Mass15_;
    TBranch *b_HLT_Photon36_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon22_AND_HE10_R9Id65_Eta2_Mass15_;
    bool loaded_HLT_Photon36_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon22_AND_HE10_R9Id65_Eta2_Mass15_;
    bool HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    TBranch *b_HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool loaded_HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_;
    TBranch *b_HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool loaded_HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool HLT_Photon36_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon36_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon36_R9Id90_HE10_IsoM_;
    bool HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15_;
    TBranch *b_HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15_;
    bool loaded_HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15_;
    bool HLT_Photon50_;
    TBranch *b_HLT_Photon50_;
    bool loaded_HLT_Photon50_;
    bool HLT_Photon500_;
    TBranch *b_HLT_Photon500_;
    bool loaded_HLT_Photon500_;
    bool HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    TBranch *b_HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool loaded_HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_;
    TBranch *b_HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool loaded_HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool HLT_Photon50_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon50_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon50_R9Id90_HE10_IsoM_;
    bool HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50_;
    TBranch *b_HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50_;
    bool loaded_HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50_;
    bool HLT_Photon600_;
    TBranch *b_HLT_Photon600_;
    bool loaded_HLT_Photon600_;
    bool HLT_Photon60_R9Id90_CaloIdL_IsoL_;
    TBranch *b_HLT_Photon60_R9Id90_CaloIdL_IsoL_;
    bool loaded_HLT_Photon60_R9Id90_CaloIdL_IsoL_;
    bool HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_;
    TBranch *b_HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_;
    bool loaded_HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_;
    bool HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15_;
    TBranch *b_HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15_;
    bool loaded_HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15_;
    bool HLT_Photon75_;
    TBranch *b_HLT_Photon75_;
    bool loaded_HLT_Photon75_;
    bool HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool loaded_HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool loaded_HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool HLT_Photon75_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon75_R9Id90_HE10_IsoM_;
    bool HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3_;
    bool loaded_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3_;
    bool HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3_;
    bool loaded_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3_;
    bool HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_;
    bool loaded_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_;
    bool HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3_;
    TBranch *b_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3_;
    bool loaded_HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3_;
    bool HLT_Photon90_;
    TBranch *b_HLT_Photon90_;
    bool loaded_HLT_Photon90_;
    bool HLT_Photon90_CaloIdL_HT300_;
    TBranch *b_HLT_Photon90_CaloIdL_HT300_;
    bool loaded_HLT_Photon90_CaloIdL_HT300_;
    bool HLT_Photon90_CaloIdL_PFHT500_;
    TBranch *b_HLT_Photon90_CaloIdL_PFHT500_;
    bool loaded_HLT_Photon90_CaloIdL_PFHT500_;
    bool HLT_Photon90_CaloIdL_PFHT600_;
    TBranch *b_HLT_Photon90_CaloIdL_PFHT600_;
    bool loaded_HLT_Photon90_CaloIdL_PFHT600_;
    bool HLT_Photon90_CaloIdL_PFHT700_;
    TBranch *b_HLT_Photon90_CaloIdL_PFHT700_;
    bool loaded_HLT_Photon90_CaloIdL_PFHT700_;
    bool HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    TBranch *b_HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool loaded_HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_;
    bool HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_;
    TBranch *b_HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool loaded_HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_;
    bool HLT_Photon90_R9Id90_HE10_IsoM_;
    TBranch *b_HLT_Photon90_R9Id90_HE10_IsoM_;
    bool loaded_HLT_Photon90_R9Id90_HE10_IsoM_;
    bool HLT_Physics_;
    TBranch *b_HLT_Physics_;
    bool loaded_HLT_Physics_;
    bool HLT_Physics_part0_;
    TBranch *b_HLT_Physics_part0_;
    bool loaded_HLT_Physics_part0_;
    bool HLT_Physics_part1_;
    TBranch *b_HLT_Physics_part1_;
    bool loaded_HLT_Physics_part1_;
    bool HLT_Physics_part2_;
    TBranch *b_HLT_Physics_part2_;
    bool loaded_HLT_Physics_part2_;
    bool HLT_Physics_part3_;
    TBranch *b_HLT_Physics_part3_;
    bool loaded_HLT_Physics_part3_;
    bool HLT_Physics_part4_;
    TBranch *b_HLT_Physics_part4_;
    bool loaded_HLT_Physics_part4_;
    bool HLT_Physics_part5_;
    TBranch *b_HLT_Physics_part5_;
    bool loaded_HLT_Physics_part5_;
    bool HLT_Physics_part6_;
    TBranch *b_HLT_Physics_part6_;
    bool loaded_HLT_Physics_part6_;
    bool HLT_Physics_part7_;
    TBranch *b_HLT_Physics_part7_;
    bool loaded_HLT_Physics_part7_;
    bool HLT_PixelTracks_Multiplicity110ForEndOfFill_;
    TBranch *b_HLT_PixelTracks_Multiplicity110ForEndOfFill_;
    bool loaded_HLT_PixelTracks_Multiplicity110ForEndOfFill_;
    bool HLT_PixelTracks_Multiplicity135ForEndOfFill_;
    TBranch *b_HLT_PixelTracks_Multiplicity135ForEndOfFill_;
    bool loaded_HLT_PixelTracks_Multiplicity135ForEndOfFill_;
    bool HLT_PixelTracks_Multiplicity160ForEndOfFill_;
    TBranch *b_HLT_PixelTracks_Multiplicity160ForEndOfFill_;
    bool loaded_HLT_PixelTracks_Multiplicity160ForEndOfFill_;
    bool HLT_PixelTracks_Multiplicity60ForEndOfFill_;
    TBranch *b_HLT_PixelTracks_Multiplicity60ForEndOfFill_;
    bool loaded_HLT_PixelTracks_Multiplicity60ForEndOfFill_;
    bool HLT_PixelTracks_Multiplicity85ForEndOfFill_;
    TBranch *b_HLT_PixelTracks_Multiplicity85ForEndOfFill_;
    bool loaded_HLT_PixelTracks_Multiplicity85ForEndOfFill_;
    bool HLT_QuadJet45_DoubleBTagCSV_p087_;
    TBranch *b_HLT_QuadJet45_DoubleBTagCSV_p087_;
    bool loaded_HLT_QuadJet45_DoubleBTagCSV_p087_;
    bool HLT_QuadJet45_TripleBTagCSV_p087_;
    TBranch *b_HLT_QuadJet45_TripleBTagCSV_p087_;
    bool loaded_HLT_QuadJet45_TripleBTagCSV_p087_;
    bool HLT_QuadMuon0_Dimuon0_Jpsi_;
    TBranch *b_HLT_QuadMuon0_Dimuon0_Jpsi_;
    bool loaded_HLT_QuadMuon0_Dimuon0_Jpsi_;
    bool HLT_QuadMuon0_Dimuon0_Upsilon_;
    TBranch *b_HLT_QuadMuon0_Dimuon0_Upsilon_;
    bool loaded_HLT_QuadMuon0_Dimuon0_Upsilon_;
    bool HLT_QuadPFJet103_88_75_15_;
    TBranch *b_HLT_QuadPFJet103_88_75_15_;
    bool loaded_HLT_QuadPFJet103_88_75_15_;
    bool HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    TBranch *b_HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool loaded_HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool HLT_QuadPFJet103_88_75_15_PFBTagDeepCSV_1p3_VBF2_;
    TBranch *b_HLT_QuadPFJet103_88_75_15_PFBTagDeepCSV_1p3_VBF2_;
    bool loaded_HLT_QuadPFJet103_88_75_15_PFBTagDeepCSV_1p3_VBF2_;
    bool HLT_QuadPFJet105_88_76_15_;
    TBranch *b_HLT_QuadPFJet105_88_76_15_;
    bool loaded_HLT_QuadPFJet105_88_76_15_;
    bool HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    TBranch *b_HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool loaded_HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool HLT_QuadPFJet105_88_76_15_PFBTagDeepCSV_1p3_VBF2_;
    TBranch *b_HLT_QuadPFJet105_88_76_15_PFBTagDeepCSV_1p3_VBF2_;
    bool loaded_HLT_QuadPFJet105_88_76_15_PFBTagDeepCSV_1p3_VBF2_;
    bool HLT_QuadPFJet111_90_80_15_;
    TBranch *b_HLT_QuadPFJet111_90_80_15_;
    bool loaded_HLT_QuadPFJet111_90_80_15_;
    bool HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    TBranch *b_HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool loaded_HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool HLT_QuadPFJet111_90_80_15_PFBTagDeepCSV_1p3_VBF2_;
    TBranch *b_HLT_QuadPFJet111_90_80_15_PFBTagDeepCSV_1p3_VBF2_;
    bool loaded_HLT_QuadPFJet111_90_80_15_PFBTagDeepCSV_1p3_VBF2_;
    bool HLT_QuadPFJet98_83_71_15_;
    TBranch *b_HLT_QuadPFJet98_83_71_15_;
    bool loaded_HLT_QuadPFJet98_83_71_15_;
    bool HLT_QuadPFJet98_83_71_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    TBranch *b_HLT_QuadPFJet98_83_71_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool loaded_HLT_QuadPFJet98_83_71_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1_;
    bool HLT_QuadPFJet98_83_71_15_PFBTagDeepCSV_1p3_VBF2_;
    TBranch *b_HLT_QuadPFJet98_83_71_15_PFBTagDeepCSV_1p3_VBF2_;
    bool loaded_HLT_QuadPFJet98_83_71_15_PFBTagDeepCSV_1p3_VBF2_;
    bool HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_;
    TBranch *b_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_;
    bool loaded_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_;
    bool HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_;
    TBranch *b_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_;
    bool loaded_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_;
    bool HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_;
    TBranch *b_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_;
    bool loaded_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_;
    bool HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_;
    TBranch *b_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_;
    bool loaded_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_;
    bool HLT_QuadPFJet_VBF_;
    TBranch *b_HLT_QuadPFJet_VBF_;
    bool loaded_HLT_QuadPFJet_VBF_;
    bool HLT_Random_;
    TBranch *b_HLT_Random_;
    bool loaded_HLT_Random_;
    bool HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200_;
    TBranch *b_HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200_;
    bool loaded_HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200_;
    bool HLT_Rsq0p02_MR400_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    TBranch *b_HLT_Rsq0p02_MR400_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool loaded_HLT_Rsq0p02_MR400_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    TBranch *b_HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool loaded_HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    TBranch *b_HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool loaded_HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    TBranch *b_HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool loaded_HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_;
    bool HLT_Rsq0p25_;
    TBranch *b_HLT_Rsq0p25_;
    bool loaded_HLT_Rsq0p25_;
    bool HLT_Rsq0p25_Calo_;
    TBranch *b_HLT_Rsq0p25_Calo_;
    bool loaded_HLT_Rsq0p25_Calo_;
    bool HLT_Rsq0p30_;
    TBranch *b_HLT_Rsq0p30_;
    bool loaded_HLT_Rsq0p30_;
    bool HLT_Rsq0p35_;
    TBranch *b_HLT_Rsq0p35_;
    bool loaded_HLT_Rsq0p35_;
    bool HLT_Rsq0p40_;
    TBranch *b_HLT_Rsq0p40_;
    bool loaded_HLT_Rsq0p40_;
    bool HLT_RsqMR240_Rsq0p09_MR200_;
    TBranch *b_HLT_RsqMR240_Rsq0p09_MR200_;
    bool loaded_HLT_RsqMR240_Rsq0p09_MR200_;
    bool HLT_RsqMR240_Rsq0p09_MR200_4jet_;
    TBranch *b_HLT_RsqMR240_Rsq0p09_MR200_4jet_;
    bool loaded_HLT_RsqMR240_Rsq0p09_MR200_4jet_;
    bool HLT_RsqMR240_Rsq0p09_MR200_4jet_Calo_;
    TBranch *b_HLT_RsqMR240_Rsq0p09_MR200_4jet_Calo_;
    bool loaded_HLT_RsqMR240_Rsq0p09_MR200_4jet_Calo_;
    bool HLT_RsqMR240_Rsq0p09_MR200_Calo_;
    TBranch *b_HLT_RsqMR240_Rsq0p09_MR200_Calo_;
    bool loaded_HLT_RsqMR240_Rsq0p09_MR200_Calo_;
    bool HLT_RsqMR270_Rsq0p09_MR200_;
    TBranch *b_HLT_RsqMR270_Rsq0p09_MR200_;
    bool loaded_HLT_RsqMR270_Rsq0p09_MR200_;
    bool HLT_RsqMR270_Rsq0p09_MR200_4jet_;
    TBranch *b_HLT_RsqMR270_Rsq0p09_MR200_4jet_;
    bool loaded_HLT_RsqMR270_Rsq0p09_MR200_4jet_;
    bool HLT_RsqMR300_Rsq0p09_MR200_;
    TBranch *b_HLT_RsqMR300_Rsq0p09_MR200_;
    bool loaded_HLT_RsqMR300_Rsq0p09_MR200_;
    bool HLT_RsqMR300_Rsq0p09_MR200_4jet_;
    TBranch *b_HLT_RsqMR300_Rsq0p09_MR200_4jet_;
    bool loaded_HLT_RsqMR300_Rsq0p09_MR200_4jet_;
    bool HLT_RsqMR320_Rsq0p09_MR200_;
    TBranch *b_HLT_RsqMR320_Rsq0p09_MR200_;
    bool loaded_HLT_RsqMR320_Rsq0p09_MR200_;
    bool HLT_RsqMR320_Rsq0p09_MR200_4jet_;
    TBranch *b_HLT_RsqMR320_Rsq0p09_MR200_4jet_;
    bool loaded_HLT_RsqMR320_Rsq0p09_MR200_4jet_;
    bool HLT_SingleCentralPFJet170_CFMax0p1_;
    TBranch *b_HLT_SingleCentralPFJet170_CFMax0p1_;
    bool loaded_HLT_SingleCentralPFJet170_CFMax0p1_;
    bool HLT_SingleJet30_Mu12_SinglePFJet40_;
    TBranch *b_HLT_SingleJet30_Mu12_SinglePFJet40_;
    bool loaded_HLT_SingleJet30_Mu12_SinglePFJet40_;
    bool HLT_SinglePhoton10_Eta3p1ForPPRef_;
    TBranch *b_HLT_SinglePhoton10_Eta3p1ForPPRef_;
    bool loaded_HLT_SinglePhoton10_Eta3p1ForPPRef_;
    bool HLT_SinglePhoton20_Eta3p1ForPPRef_;
    TBranch *b_HLT_SinglePhoton20_Eta3p1ForPPRef_;
    bool loaded_HLT_SinglePhoton20_Eta3p1ForPPRef_;
    bool HLT_SinglePhoton30_Eta3p1ForPPRef_;
    TBranch *b_HLT_SinglePhoton30_Eta3p1ForPPRef_;
    bool loaded_HLT_SinglePhoton30_Eta3p1ForPPRef_;
    bool HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_;
    TBranch *b_HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_;
    bool loaded_HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_;
    bool HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1_;
    TBranch *b_HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1_;
    bool loaded_HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1_;
    bool HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_;
    TBranch *b_HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_;
    bool loaded_HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_;
    bool HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1_;
    TBranch *b_HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1_;
    bool loaded_HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1_;
    bool HLT_TkMu100_;
    TBranch *b_HLT_TkMu100_;
    bool loaded_HLT_TkMu100_;
    bool HLT_TkMu17_;
    TBranch *b_HLT_TkMu17_;
    bool loaded_HLT_TkMu17_;
    bool HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    TBranch *b_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    bool loaded_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    bool HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    TBranch *b_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    bool loaded_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    bool HLT_TkMu20_;
    TBranch *b_HLT_TkMu20_;
    bool loaded_HLT_TkMu20_;
    bool HLT_TkMu24_eta2p1_;
    TBranch *b_HLT_TkMu24_eta2p1_;
    bool loaded_HLT_TkMu24_eta2p1_;
    bool HLT_TkMu27_;
    TBranch *b_HLT_TkMu27_;
    bool loaded_HLT_TkMu27_;
    bool HLT_TkMu50_;
    TBranch *b_HLT_TkMu50_;
    bool loaded_HLT_TkMu50_;
    bool HLT_Trimuon5_3p5_2_Upsilon_Muon_;
    TBranch *b_HLT_Trimuon5_3p5_2_Upsilon_Muon_;
    bool loaded_HLT_Trimuon5_3p5_2_Upsilon_Muon_;
    bool HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon_;
    TBranch *b_HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon_;
    bool loaded_HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon_;
    bool HLT_TripleJet110_35_35_Mjj650_PFMET110_;
    TBranch *b_HLT_TripleJet110_35_35_Mjj650_PFMET110_;
    bool loaded_HLT_TripleJet110_35_35_Mjj650_PFMET110_;
    bool HLT_TripleJet110_35_35_Mjj650_PFMET120_;
    TBranch *b_HLT_TripleJet110_35_35_Mjj650_PFMET120_;
    bool loaded_HLT_TripleJet110_35_35_Mjj650_PFMET120_;
    bool HLT_TripleJet110_35_35_Mjj650_PFMET130_;
    TBranch *b_HLT_TripleJet110_35_35_Mjj650_PFMET130_;
    bool loaded_HLT_TripleJet110_35_35_Mjj650_PFMET130_;
    bool HLT_TripleMu_10_5_5_DZ_;
    TBranch *b_HLT_TripleMu_10_5_5_DZ_;
    bool loaded_HLT_TripleMu_10_5_5_DZ_;
    bool HLT_TripleMu_12_10_5_;
    TBranch *b_HLT_TripleMu_12_10_5_;
    bool loaded_HLT_TripleMu_12_10_5_;
    bool HLT_TripleMu_5_3_3_;
    TBranch *b_HLT_TripleMu_5_3_3_;
    bool loaded_HLT_TripleMu_5_3_3_;
    bool HLT_TripleMu_5_3_3_Mass3p8_DCA_;
    TBranch *b_HLT_TripleMu_5_3_3_Mass3p8_DCA_;
    bool loaded_HLT_TripleMu_5_3_3_Mass3p8_DCA_;
    bool HLT_TripleMu_5_3_3_Mass3p8_DZ_;
    TBranch *b_HLT_TripleMu_5_3_3_Mass3p8_DZ_;
    bool loaded_HLT_TripleMu_5_3_3_Mass3p8_DZ_;
    bool HLT_TriplePhoton_20_20_20_CaloIdLV2_;
    TBranch *b_HLT_TriplePhoton_20_20_20_CaloIdLV2_;
    bool loaded_HLT_TriplePhoton_20_20_20_CaloIdLV2_;
    bool HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_;
    TBranch *b_HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_;
    bool loaded_HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_;
    bool HLT_TriplePhoton_30_30_10_CaloIdLV2_;
    TBranch *b_HLT_TriplePhoton_30_30_10_CaloIdLV2_;
    bool loaded_HLT_TriplePhoton_30_30_10_CaloIdLV2_;
    bool HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_;
    TBranch *b_HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_;
    bool loaded_HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_;
    bool HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_;
    TBranch *b_HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_;
    bool loaded_HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_;
    bool HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_;
    TBranch *b_HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_;
    bool loaded_HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_;
    bool HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_;
    TBranch *b_HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_;
    bool loaded_HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_;
    bool HLT_TrkMu16NoFiltersNoVtx_;
    TBranch *b_HLT_TrkMu16NoFiltersNoVtx_;
    bool loaded_HLT_TrkMu16NoFiltersNoVtx_;
    bool HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_;
    TBranch *b_HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_;
    bool loaded_HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_;
    bool HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_;
    TBranch *b_HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_;
    bool loaded_HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_;
    bool HLT_TrkMu6NoFiltersNoVtx_;
    TBranch *b_HLT_TrkMu6NoFiltersNoVtx_;
    bool loaded_HLT_TrkMu6NoFiltersNoVtx_;
    bool HLT_UncorrectedJetE30_NoBPTX_;
    TBranch *b_HLT_UncorrectedJetE30_NoBPTX_;
    bool loaded_HLT_UncorrectedJetE30_NoBPTX_;
    bool HLT_UncorrectedJetE30_NoBPTX3BX_;
    TBranch *b_HLT_UncorrectedJetE30_NoBPTX3BX_;
    bool loaded_HLT_UncorrectedJetE30_NoBPTX3BX_;
    bool HLT_UncorrectedJetE60_NoBPTX3BX_;
    TBranch *b_HLT_UncorrectedJetE60_NoBPTX3BX_;
    bool loaded_HLT_UncorrectedJetE60_NoBPTX3BX_;
    bool HLT_UncorrectedJetE70_NoBPTX3BX_;
    TBranch *b_HLT_UncorrectedJetE70_NoBPTX3BX_;
    bool loaded_HLT_UncorrectedJetE70_NoBPTX3BX_;
    bool HLT_VBF_DisplacedJet40_DisplacedTrack_;
    TBranch *b_HLT_VBF_DisplacedJet40_DisplacedTrack_;
    bool loaded_HLT_VBF_DisplacedJet40_DisplacedTrack_;
    bool HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5_;
    TBranch *b_HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5_;
    bool loaded_HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5_;
    bool HLT_VBF_DisplacedJet40_Hadronic_;
    TBranch *b_HLT_VBF_DisplacedJet40_Hadronic_;
    bool loaded_HLT_VBF_DisplacedJet40_Hadronic_;
    bool HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack_;
    TBranch *b_HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack_;
    bool loaded_HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack_;
    bool HLT_VBF_DisplacedJet40_TightID_DisplacedTrack_;
    TBranch *b_HLT_VBF_DisplacedJet40_TightID_DisplacedTrack_;
    bool loaded_HLT_VBF_DisplacedJet40_TightID_DisplacedTrack_;
    bool HLT_VBF_DisplacedJet40_TightID_Hadronic_;
    TBranch *b_HLT_VBF_DisplacedJet40_TightID_Hadronic_;
    bool loaded_HLT_VBF_DisplacedJet40_TightID_Hadronic_;
    bool HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack_;
    TBranch *b_HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack_;
    bool loaded_HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack_;
    bool HLT_VBF_DisplacedJet40_VTightID_Hadronic_;
    TBranch *b_HLT_VBF_DisplacedJet40_VTightID_Hadronic_;
    bool loaded_HLT_VBF_DisplacedJet40_VTightID_Hadronic_;
    bool HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack_;
    TBranch *b_HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack_;
    bool loaded_HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack_;
    bool HLT_VBF_DisplacedJet40_VVTightID_Hadronic_;
    TBranch *b_HLT_VBF_DisplacedJet40_VVTightID_Hadronic_;
    bool loaded_HLT_VBF_DisplacedJet40_VVTightID_Hadronic_;
    bool HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1_;
    TBranch *b_HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1_;
    bool loaded_HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1_;
    bool HLT_VBF_DoubleMediumChargedIsoPFTauHPS20_Trk1_eta2p1_;
    TBranch *b_HLT_VBF_DoubleMediumChargedIsoPFTauHPS20_Trk1_eta2p1_;
    bool loaded_HLT_VBF_DoubleMediumChargedIsoPFTauHPS20_Trk1_eta2p1_;
    bool HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_;
    TBranch *b_HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_;
    bool loaded_HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_;
    bool HLT_VLooseIsoPFTau120_Trk50_eta2p1_;
    TBranch *b_HLT_VLooseIsoPFTau120_Trk50_eta2p1_;
    bool loaded_HLT_VLooseIsoPFTau120_Trk50_eta2p1_;
    bool HLT_VLooseIsoPFTau140_Trk50_eta2p1_;
    TBranch *b_HLT_VLooseIsoPFTau140_Trk50_eta2p1_;
    bool loaded_HLT_VLooseIsoPFTau140_Trk50_eta2p1_;
    bool HLT_ZeroBias_;
    TBranch *b_HLT_ZeroBias_;
    bool loaded_HLT_ZeroBias_;
    bool HLT_ZeroBias_Alignment_;
    TBranch *b_HLT_ZeroBias_Alignment_;
    bool loaded_HLT_ZeroBias_Alignment_;
    bool HLT_ZeroBias_Beamspot_;
    TBranch *b_HLT_ZeroBias_Beamspot_;
    bool loaded_HLT_ZeroBias_Beamspot_;
    bool HLT_ZeroBias_FirstBXAfterTrain_;
    TBranch *b_HLT_ZeroBias_FirstBXAfterTrain_;
    bool loaded_HLT_ZeroBias_FirstBXAfterTrain_;
    bool HLT_ZeroBias_FirstCollisionAfterAbortGap_;
    TBranch *b_HLT_ZeroBias_FirstCollisionAfterAbortGap_;
    bool loaded_HLT_ZeroBias_FirstCollisionAfterAbortGap_;
    bool HLT_ZeroBias_FirstCollisionAfterAbortGap_TCDS_;
    TBranch *b_HLT_ZeroBias_FirstCollisionAfterAbortGap_TCDS_;
    bool loaded_HLT_ZeroBias_FirstCollisionAfterAbortGap_TCDS_;
    bool HLT_ZeroBias_FirstCollisionAfterAbortGap_copy_;
    TBranch *b_HLT_ZeroBias_FirstCollisionAfterAbortGap_copy_;
    bool loaded_HLT_ZeroBias_FirstCollisionAfterAbortGap_copy_;
    bool HLT_ZeroBias_FirstCollisionInTrain_;
    TBranch *b_HLT_ZeroBias_FirstCollisionInTrain_;
    bool loaded_HLT_ZeroBias_FirstCollisionInTrain_;
    bool HLT_ZeroBias_IsolatedBunches_;
    TBranch *b_HLT_ZeroBias_IsolatedBunches_;
    bool loaded_HLT_ZeroBias_IsolatedBunches_;
    bool HLT_ZeroBias_LastCollisionInTrain_;
    TBranch *b_HLT_ZeroBias_LastCollisionInTrain_;
    bool loaded_HLT_ZeroBias_LastCollisionInTrain_;
    bool HLT_ZeroBias_part0_;
    TBranch *b_HLT_ZeroBias_part0_;
    bool loaded_HLT_ZeroBias_part0_;
    bool HLT_ZeroBias_part1_;
    TBranch *b_HLT_ZeroBias_part1_;
    bool loaded_HLT_ZeroBias_part1_;
    bool HLT_ZeroBias_part2_;
    TBranch *b_HLT_ZeroBias_part2_;
    bool loaded_HLT_ZeroBias_part2_;
    bool HLT_ZeroBias_part3_;
    TBranch *b_HLT_ZeroBias_part3_;
    bool loaded_HLT_ZeroBias_part3_;
    bool HLT_ZeroBias_part4_;
    TBranch *b_HLT_ZeroBias_part4_;
    bool loaded_HLT_ZeroBias_part4_;
    bool HLT_ZeroBias_part5_;
    TBranch *b_HLT_ZeroBias_part5_;
    bool loaded_HLT_ZeroBias_part5_;
    bool HLT_ZeroBias_part6_;
    TBranch *b_HLT_ZeroBias_part6_;
    bool loaded_HLT_ZeroBias_part6_;
    bool HLT_ZeroBias_part7_;
    TBranch *b_HLT_ZeroBias_part7_;
    bool loaded_HLT_ZeroBias_part7_;
    bool HLTriggerFinalPath_;
    TBranch *b_HLTriggerFinalPath_;
    bool loaded_HLTriggerFinalPath_;
    bool HLTriggerFirstPath_;
    TBranch *b_HLTriggerFirstPath_;
    bool loaded_HLTriggerFirstPath_;
    float HTXS_Higgs_pt_;
    TBranch *b_HTXS_Higgs_pt_;
    bool loaded_HTXS_Higgs_pt_;
    float HTXS_Higgs_y_;
    TBranch *b_HTXS_Higgs_y_;
    bool loaded_HTXS_Higgs_y_;
    UChar_t HTXS_njets25_;
    TBranch *b_HTXS_njets25_;
    bool loaded_HTXS_njets25_;
    UChar_t HTXS_njets30_;
    TBranch *b_HTXS_njets30_;
    bool loaded_HTXS_njets30_;
    int HTXS_stage1_1_cat_pTjet25GeV_;
    TBranch *b_HTXS_stage1_1_cat_pTjet25GeV_;
    bool loaded_HTXS_stage1_1_cat_pTjet25GeV_;
    int HTXS_stage1_1_cat_pTjet30GeV_;
    TBranch *b_HTXS_stage1_1_cat_pTjet30GeV_;
    bool loaded_HTXS_stage1_1_cat_pTjet30GeV_;
    int HTXS_stage1_1_fine_cat_pTjet25GeV_;
    TBranch *b_HTXS_stage1_1_fine_cat_pTjet25GeV_;
    bool loaded_HTXS_stage1_1_fine_cat_pTjet25GeV_;
    int HTXS_stage1_1_fine_cat_pTjet30GeV_;
    TBranch *b_HTXS_stage1_1_fine_cat_pTjet30GeV_;
    bool loaded_HTXS_stage1_1_fine_cat_pTjet30GeV_;
    int HTXS_stage1_2_cat_pTjet25GeV_;
    TBranch *b_HTXS_stage1_2_cat_pTjet25GeV_;
    bool loaded_HTXS_stage1_2_cat_pTjet25GeV_;
    int HTXS_stage1_2_cat_pTjet30GeV_;
    TBranch *b_HTXS_stage1_2_cat_pTjet30GeV_;
    bool loaded_HTXS_stage1_2_cat_pTjet30GeV_;
    int HTXS_stage1_2_fine_cat_pTjet25GeV_;
    TBranch *b_HTXS_stage1_2_fine_cat_pTjet25GeV_;
    bool loaded_HTXS_stage1_2_fine_cat_pTjet25GeV_;
    int HTXS_stage1_2_fine_cat_pTjet30GeV_;
    TBranch *b_HTXS_stage1_2_fine_cat_pTjet30GeV_;
    bool loaded_HTXS_stage1_2_fine_cat_pTjet30GeV_;
    int HTXS_stage_0_;
    TBranch *b_HTXS_stage_0_;
    bool loaded_HTXS_stage_0_;
    int HTXS_stage_1_pTjet25_;
    TBranch *b_HTXS_stage_1_pTjet25_;
    bool loaded_HTXS_stage_1_pTjet25_;
    int HTXS_stage_1_pTjet30_;
    TBranch *b_HTXS_stage_1_pTjet30_;
    bool loaded_HTXS_stage_1_pTjet30_;
    float IsoTrack_dxy_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_dxy_;
    TBranch *b_IsoTrack_dxy_;
    bool loaded_IsoTrack_dxy_;
    float IsoTrack_dz_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_dz_;
    TBranch *b_IsoTrack_dz_;
    bool loaded_IsoTrack_dz_;
    float IsoTrack_eta_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_eta_;
    TBranch *b_IsoTrack_eta_;
    bool loaded_IsoTrack_eta_;
    int IsoTrack_fromPV_[NISOTRACK_MAX];
    vector<int> v_IsoTrack_fromPV_;
    TBranch *b_IsoTrack_fromPV_;
    bool loaded_IsoTrack_fromPV_;
    bool IsoTrack_isFromLostTrack_[NISOTRACK_MAX];
    vector<bool> v_IsoTrack_isFromLostTrack_;
    TBranch *b_IsoTrack_isFromLostTrack_;
    bool loaded_IsoTrack_isFromLostTrack_;
    bool IsoTrack_isHighPurityTrack_[NISOTRACK_MAX];
    vector<bool> v_IsoTrack_isHighPurityTrack_;
    TBranch *b_IsoTrack_isHighPurityTrack_;
    bool loaded_IsoTrack_isHighPurityTrack_;
    bool IsoTrack_isPFcand_[NISOTRACK_MAX];
    vector<bool> v_IsoTrack_isPFcand_;
    TBranch *b_IsoTrack_isPFcand_;
    bool loaded_IsoTrack_isPFcand_;
    float IsoTrack_miniPFRelIso_all_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_miniPFRelIso_all_;
    TBranch *b_IsoTrack_miniPFRelIso_all_;
    bool loaded_IsoTrack_miniPFRelIso_all_;
    float IsoTrack_miniPFRelIso_chg_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_miniPFRelIso_chg_;
    TBranch *b_IsoTrack_miniPFRelIso_chg_;
    bool loaded_IsoTrack_miniPFRelIso_chg_;
    int IsoTrack_pdgId_[NISOTRACK_MAX];
    vector<int> v_IsoTrack_pdgId_;
    TBranch *b_IsoTrack_pdgId_;
    bool loaded_IsoTrack_pdgId_;
    float IsoTrack_pfRelIso03_all_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_pfRelIso03_all_;
    TBranch *b_IsoTrack_pfRelIso03_all_;
    bool loaded_IsoTrack_pfRelIso03_all_;
    float IsoTrack_pfRelIso03_chg_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_pfRelIso03_chg_;
    TBranch *b_IsoTrack_pfRelIso03_chg_;
    bool loaded_IsoTrack_pfRelIso03_chg_;
    float IsoTrack_phi_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_phi_;
    TBranch *b_IsoTrack_phi_;
    bool loaded_IsoTrack_phi_;
    float IsoTrack_pt_[NISOTRACK_MAX];
    vector<float> v_IsoTrack_pt_;
    TBranch *b_IsoTrack_pt_;
    bool loaded_IsoTrack_pt_;
    float Jet_area_[NJET_MAX];
    vector<float> v_Jet_area_;
    TBranch *b_Jet_area_;
    bool loaded_Jet_area_;
    float Jet_bRegCorr_[NJET_MAX];
    vector<float> v_Jet_bRegCorr_;
    TBranch *b_Jet_bRegCorr_;
    bool loaded_Jet_bRegCorr_;
    float Jet_bRegRes_[NJET_MAX];
    vector<float> v_Jet_bRegRes_;
    TBranch *b_Jet_bRegRes_;
    bool loaded_Jet_bRegRes_;
    float Jet_btagCMVA_[NJET_MAX];
    vector<float> v_Jet_btagCMVA_;
    TBranch *b_Jet_btagCMVA_;
    bool loaded_Jet_btagCMVA_;
    float Jet_btagCSVV2_[NJET_MAX];
    vector<float> v_Jet_btagCSVV2_;
    TBranch *b_Jet_btagCSVV2_;
    bool loaded_Jet_btagCSVV2_;
    float Jet_btagDeepB_[NJET_MAX];
    vector<float> v_Jet_btagDeepB_;
    TBranch *b_Jet_btagDeepB_;
    bool loaded_Jet_btagDeepB_;
    float Jet_btagDeepC_[NJET_MAX];
    vector<float> v_Jet_btagDeepC_;
    TBranch *b_Jet_btagDeepC_;
    bool loaded_Jet_btagDeepC_;
    float Jet_btagDeepFlavB_[NJET_MAX];
    vector<float> v_Jet_btagDeepFlavB_;
    TBranch *b_Jet_btagDeepFlavB_;
    bool loaded_Jet_btagDeepFlavB_;
    float Jet_btagDeepFlavC_[NJET_MAX];
    vector<float> v_Jet_btagDeepFlavC_;
    TBranch *b_Jet_btagDeepFlavC_;
    bool loaded_Jet_btagDeepFlavC_;
    float Jet_cRegCorr_[NJET_MAX];
    vector<float> v_Jet_cRegCorr_;
    TBranch *b_Jet_cRegCorr_;
    bool loaded_Jet_cRegCorr_;
    float Jet_cRegRes_[NJET_MAX];
    vector<float> v_Jet_cRegRes_;
    TBranch *b_Jet_cRegRes_;
    bool loaded_Jet_cRegRes_;
    float Jet_chEmEF_[NJET_MAX];
    vector<float> v_Jet_chEmEF_;
    TBranch *b_Jet_chEmEF_;
    bool loaded_Jet_chEmEF_;
    float Jet_chFPV0EF_[NJET_MAX];
    vector<float> v_Jet_chFPV0EF_;
    TBranch *b_Jet_chFPV0EF_;
    bool loaded_Jet_chFPV0EF_;
    float Jet_chFPV1EF_[NJET_MAX];
    vector<float> v_Jet_chFPV1EF_;
    TBranch *b_Jet_chFPV1EF_;
    bool loaded_Jet_chFPV1EF_;
    float Jet_chFPV2EF_[NJET_MAX];
    vector<float> v_Jet_chFPV2EF_;
    TBranch *b_Jet_chFPV2EF_;
    bool loaded_Jet_chFPV2EF_;
    float Jet_chFPV3EF_[NJET_MAX];
    vector<float> v_Jet_chFPV3EF_;
    TBranch *b_Jet_chFPV3EF_;
    bool loaded_Jet_chFPV3EF_;
    float Jet_chHEF_[NJET_MAX];
    vector<float> v_Jet_chHEF_;
    TBranch *b_Jet_chHEF_;
    bool loaded_Jet_chHEF_;
    UChar_t Jet_cleanmask_[NJET_MAX];
    vector<UChar_t> v_Jet_cleanmask_;
    TBranch *b_Jet_cleanmask_;
    bool loaded_Jet_cleanmask_;
    int Jet_electronIdx1_[NJET_MAX];
    vector<int> v_Jet_electronIdx1_;
    TBranch *b_Jet_electronIdx1_;
    bool loaded_Jet_electronIdx1_;
    int Jet_electronIdx2_[NJET_MAX];
    vector<int> v_Jet_electronIdx2_;
    TBranch *b_Jet_electronIdx2_;
    bool loaded_Jet_electronIdx2_;
    float Jet_eta_[NJET_MAX];
    vector<float> v_Jet_eta_;
    TBranch *b_Jet_eta_;
    bool loaded_Jet_eta_;
    int Jet_genJetIdx_[NJET_MAX];
    vector<int> v_Jet_genJetIdx_;
    TBranch *b_Jet_genJetIdx_;
    bool loaded_Jet_genJetIdx_;
    int Jet_hadronFlavour_[NJET_MAX];
    vector<int> v_Jet_hadronFlavour_;
    TBranch *b_Jet_hadronFlavour_;
    bool loaded_Jet_hadronFlavour_;
    int Jet_jetId_[NJET_MAX];
    vector<int> v_Jet_jetId_;
    TBranch *b_Jet_jetId_;
    bool loaded_Jet_jetId_;
    float Jet_mass_[NJET_MAX];
    vector<float> v_Jet_mass_;
    TBranch *b_Jet_mass_;
    bool loaded_Jet_mass_;
    float Jet_muEF_[NJET_MAX];
    vector<float> v_Jet_muEF_;
    TBranch *b_Jet_muEF_;
    bool loaded_Jet_muEF_;
    int Jet_muonIdx1_[NJET_MAX];
    vector<int> v_Jet_muonIdx1_;
    TBranch *b_Jet_muonIdx1_;
    bool loaded_Jet_muonIdx1_;
    int Jet_muonIdx2_[NJET_MAX];
    vector<int> v_Jet_muonIdx2_;
    TBranch *b_Jet_muonIdx2_;
    bool loaded_Jet_muonIdx2_;
    float Jet_muonSubtrFactor_[NJET_MAX];
    vector<float> v_Jet_muonSubtrFactor_;
    TBranch *b_Jet_muonSubtrFactor_;
    bool loaded_Jet_muonSubtrFactor_;
    int Jet_nConstituents_[NJET_MAX];
    vector<int> v_Jet_nConstituents_;
    TBranch *b_Jet_nConstituents_;
    bool loaded_Jet_nConstituents_;
    int Jet_nElectrons_[NJET_MAX];
    vector<int> v_Jet_nElectrons_;
    TBranch *b_Jet_nElectrons_;
    bool loaded_Jet_nElectrons_;
    int Jet_nMuons_[NJET_MAX];
    vector<int> v_Jet_nMuons_;
    TBranch *b_Jet_nMuons_;
    bool loaded_Jet_nMuons_;
    float Jet_neEmEF_[NJET_MAX];
    vector<float> v_Jet_neEmEF_;
    TBranch *b_Jet_neEmEF_;
    bool loaded_Jet_neEmEF_;
    float Jet_neHEF_[NJET_MAX];
    vector<float> v_Jet_neHEF_;
    TBranch *b_Jet_neHEF_;
    bool loaded_Jet_neHEF_;
    vector<LorentzVector> v_Jet_p4_;
    TBranch *b_Jet_p4_;
    bool loaded_Jet_p4_;
    int Jet_partonFlavour_[NJET_MAX];
    vector<int> v_Jet_partonFlavour_;
    TBranch *b_Jet_partonFlavour_;
    bool loaded_Jet_partonFlavour_;
    float Jet_phi_[NJET_MAX];
    vector<float> v_Jet_phi_;
    TBranch *b_Jet_phi_;
    bool loaded_Jet_phi_;
    float Jet_pt_[NJET_MAX];
    vector<float> v_Jet_pt_;
    TBranch *b_Jet_pt_;
    bool loaded_Jet_pt_;
    int Jet_puId_[NJET_MAX];
    vector<int> v_Jet_puId_;
    TBranch *b_Jet_puId_;
    bool loaded_Jet_puId_;
    float Jet_puIdDisc_[NJET_MAX];
    vector<float> v_Jet_puIdDisc_;
    TBranch *b_Jet_puIdDisc_;
    bool loaded_Jet_puIdDisc_;
    float Jet_qgl_[NJET_MAX];
    vector<float> v_Jet_qgl_;
    TBranch *b_Jet_qgl_;
    bool loaded_Jet_qgl_;
    float Jet_rawFactor_[NJET_MAX];
    vector<float> v_Jet_rawFactor_;
    TBranch *b_Jet_rawFactor_;
    bool loaded_Jet_rawFactor_;
    float L1PreFiringWeight_Dn_;
    TBranch *b_L1PreFiringWeight_Dn_;
    bool loaded_L1PreFiringWeight_Dn_;
    float L1PreFiringWeight_Nom_;
    TBranch *b_L1PreFiringWeight_Nom_;
    bool loaded_L1PreFiringWeight_Nom_;
    float L1PreFiringWeight_Up_;
    TBranch *b_L1PreFiringWeight_Up_;
    bool loaded_L1PreFiringWeight_Up_;
    bool L1Reco_step_;
    TBranch *b_L1Reco_step_;
    bool loaded_L1Reco_step_;
    bool L1_AlwaysTrue_;
    TBranch *b_L1_AlwaysTrue_;
    bool loaded_L1_AlwaysTrue_;
    bool L1_BPTX_AND_Ref1_VME_;
    TBranch *b_L1_BPTX_AND_Ref1_VME_;
    bool loaded_L1_BPTX_AND_Ref1_VME_;
    bool L1_BPTX_AND_Ref3_VME_;
    TBranch *b_L1_BPTX_AND_Ref3_VME_;
    bool loaded_L1_BPTX_AND_Ref3_VME_;
    bool L1_BPTX_AND_Ref4_VME_;
    TBranch *b_L1_BPTX_AND_Ref4_VME_;
    bool loaded_L1_BPTX_AND_Ref4_VME_;
    bool L1_BPTX_BeamGas_B1_VME_;
    TBranch *b_L1_BPTX_BeamGas_B1_VME_;
    bool loaded_L1_BPTX_BeamGas_B1_VME_;
    bool L1_BPTX_BeamGas_B2_VME_;
    TBranch *b_L1_BPTX_BeamGas_B2_VME_;
    bool loaded_L1_BPTX_BeamGas_B2_VME_;
    bool L1_BPTX_BeamGas_Ref1_VME_;
    TBranch *b_L1_BPTX_BeamGas_Ref1_VME_;
    bool loaded_L1_BPTX_BeamGas_Ref1_VME_;
    bool L1_BPTX_BeamGas_Ref2_VME_;
    TBranch *b_L1_BPTX_BeamGas_Ref2_VME_;
    bool loaded_L1_BPTX_BeamGas_Ref2_VME_;
    bool L1_BPTX_NotOR_VME_;
    TBranch *b_L1_BPTX_NotOR_VME_;
    bool loaded_L1_BPTX_NotOR_VME_;
    bool L1_BPTX_OR_Ref3_VME_;
    TBranch *b_L1_BPTX_OR_Ref3_VME_;
    bool loaded_L1_BPTX_OR_Ref3_VME_;
    bool L1_BPTX_OR_Ref4_VME_;
    TBranch *b_L1_BPTX_OR_Ref4_VME_;
    bool loaded_L1_BPTX_OR_Ref4_VME_;
    bool L1_BPTX_RefAND_VME_;
    TBranch *b_L1_BPTX_RefAND_VME_;
    bool loaded_L1_BPTX_RefAND_VME_;
    bool L1_BRIL_TRIG0_AND_;
    TBranch *b_L1_BRIL_TRIG0_AND_;
    bool loaded_L1_BRIL_TRIG0_AND_;
    bool L1_BRIL_TRIG0_FstBunchInTrain_;
    TBranch *b_L1_BRIL_TRIG0_FstBunchInTrain_;
    bool loaded_L1_BRIL_TRIG0_FstBunchInTrain_;
    bool L1_BRIL_TRIG0_OR_;
    TBranch *b_L1_BRIL_TRIG0_OR_;
    bool loaded_L1_BRIL_TRIG0_OR_;
    bool L1_BRIL_TRIG0_delayedAND_;
    TBranch *b_L1_BRIL_TRIG0_delayedAND_;
    bool loaded_L1_BRIL_TRIG0_delayedAND_;
    bool L1_BeamGasB1_;
    TBranch *b_L1_BeamGasB1_;
    bool loaded_L1_BeamGasB1_;
    bool L1_BeamGasB2_;
    TBranch *b_L1_BeamGasB2_;
    bool loaded_L1_BeamGasB2_;
    bool L1_BeamGasMinus_;
    TBranch *b_L1_BeamGasMinus_;
    bool loaded_L1_BeamGasMinus_;
    bool L1_BeamGasPlus_;
    TBranch *b_L1_BeamGasPlus_;
    bool loaded_L1_BeamGasPlus_;
    bool L1_BptxMinus_;
    TBranch *b_L1_BptxMinus_;
    bool loaded_L1_BptxMinus_;
    bool L1_BptxOR_;
    TBranch *b_L1_BptxOR_;
    bool loaded_L1_BptxOR_;
    bool L1_BptxPlus_;
    TBranch *b_L1_BptxPlus_;
    bool loaded_L1_BptxPlus_;
    bool L1_BptxXOR_;
    TBranch *b_L1_BptxXOR_;
    bool loaded_L1_BptxXOR_;
    bool L1_CASTOR_Gap_BptxAND_;
    TBranch *b_L1_CASTOR_Gap_BptxAND_;
    bool loaded_L1_CASTOR_Gap_BptxAND_;
    bool L1_CASTOR_HaloMuon_;
    TBranch *b_L1_CASTOR_HaloMuon_;
    bool loaded_L1_CASTOR_HaloMuon_;
    bool L1_CASTOR_HaloMuon_BptxAND_;
    TBranch *b_L1_CASTOR_HaloMuon_BptxAND_;
    bool loaded_L1_CASTOR_HaloMuon_BptxAND_;
    bool L1_CASTOR_HighJet_BptxAND_;
    TBranch *b_L1_CASTOR_HighJet_BptxAND_;
    bool loaded_L1_CASTOR_HighJet_BptxAND_;
    bool L1_CASTOR_MediumJet_BptxAND_;
    TBranch *b_L1_CASTOR_MediumJet_BptxAND_;
    bool loaded_L1_CASTOR_MediumJet_BptxAND_;
    bool L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142_;
    TBranch *b_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142_;
    bool loaded_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142_;
    bool L1_DoubleEG6_HTT255_;
    TBranch *b_L1_DoubleEG6_HTT255_;
    bool loaded_L1_DoubleEG6_HTT255_;
    bool L1_DoubleEG8er2p5_HTT260er_;
    TBranch *b_L1_DoubleEG8er2p5_HTT260er_;
    bool loaded_L1_DoubleEG8er2p5_HTT260er_;
    bool L1_DoubleEG8er2p5_HTT280er_;
    TBranch *b_L1_DoubleEG8er2p5_HTT280er_;
    bool loaded_L1_DoubleEG8er2p5_HTT280er_;
    bool L1_DoubleEG8er2p5_HTT300er_;
    TBranch *b_L1_DoubleEG8er2p5_HTT300er_;
    bool loaded_L1_DoubleEG8er2p5_HTT300er_;
    bool L1_DoubleEG8er2p5_HTT320er_;
    TBranch *b_L1_DoubleEG8er2p5_HTT320er_;
    bool loaded_L1_DoubleEG8er2p5_HTT320er_;
    bool L1_DoubleEG8er2p5_HTT340er_;
    TBranch *b_L1_DoubleEG8er2p5_HTT340er_;
    bool loaded_L1_DoubleEG8er2p5_HTT340er_;
    bool L1_DoubleEG_15_10_;
    TBranch *b_L1_DoubleEG_15_10_;
    bool loaded_L1_DoubleEG_15_10_;
    bool L1_DoubleEG_15_10_er2p5_;
    TBranch *b_L1_DoubleEG_15_10_er2p5_;
    bool loaded_L1_DoubleEG_15_10_er2p5_;
    bool L1_DoubleEG_18_17_;
    TBranch *b_L1_DoubleEG_18_17_;
    bool loaded_L1_DoubleEG_18_17_;
    bool L1_DoubleEG_20_10_er2p5_;
    TBranch *b_L1_DoubleEG_20_10_er2p5_;
    bool loaded_L1_DoubleEG_20_10_er2p5_;
    bool L1_DoubleEG_20_18_;
    TBranch *b_L1_DoubleEG_20_18_;
    bool loaded_L1_DoubleEG_20_18_;
    bool L1_DoubleEG_22_10_;
    TBranch *b_L1_DoubleEG_22_10_;
    bool loaded_L1_DoubleEG_22_10_;
    bool L1_DoubleEG_22_10_er2p5_;
    TBranch *b_L1_DoubleEG_22_10_er2p5_;
    bool loaded_L1_DoubleEG_22_10_er2p5_;
    bool L1_DoubleEG_22_12_;
    TBranch *b_L1_DoubleEG_22_12_;
    bool loaded_L1_DoubleEG_22_12_;
    bool L1_DoubleEG_22_15_;
    TBranch *b_L1_DoubleEG_22_15_;
    bool loaded_L1_DoubleEG_22_15_;
    bool L1_DoubleEG_23_10_;
    TBranch *b_L1_DoubleEG_23_10_;
    bool loaded_L1_DoubleEG_23_10_;
    bool L1_DoubleEG_24_17_;
    TBranch *b_L1_DoubleEG_24_17_;
    bool loaded_L1_DoubleEG_24_17_;
    bool L1_DoubleEG_25_12_;
    TBranch *b_L1_DoubleEG_25_12_;
    bool loaded_L1_DoubleEG_25_12_;
    bool L1_DoubleEG_25_12_er2p5_;
    TBranch *b_L1_DoubleEG_25_12_er2p5_;
    bool loaded_L1_DoubleEG_25_12_er2p5_;
    bool L1_DoubleEG_25_14_er2p5_;
    TBranch *b_L1_DoubleEG_25_14_er2p5_;
    bool loaded_L1_DoubleEG_25_14_er2p5_;
    bool L1_DoubleEG_27_14_er2p5_;
    TBranch *b_L1_DoubleEG_27_14_er2p5_;
    bool loaded_L1_DoubleEG_27_14_er2p5_;
    bool L1_DoubleEG_LooseIso20_10_er2p5_;
    TBranch *b_L1_DoubleEG_LooseIso20_10_er2p5_;
    bool loaded_L1_DoubleEG_LooseIso20_10_er2p5_;
    bool L1_DoubleEG_LooseIso22_10_er2p5_;
    TBranch *b_L1_DoubleEG_LooseIso22_10_er2p5_;
    bool loaded_L1_DoubleEG_LooseIso22_10_er2p5_;
    bool L1_DoubleEG_LooseIso22_12_er2p5_;
    TBranch *b_L1_DoubleEG_LooseIso22_12_er2p5_;
    bool loaded_L1_DoubleEG_LooseIso22_12_er2p5_;
    bool L1_DoubleEG_LooseIso25_12_er2p5_;
    TBranch *b_L1_DoubleEG_LooseIso25_12_er2p5_;
    bool loaded_L1_DoubleEG_LooseIso25_12_er2p5_;
    bool L1_DoubleIsoTau28er_;
    TBranch *b_L1_DoubleIsoTau28er_;
    bool loaded_L1_DoubleIsoTau28er_;
    bool L1_DoubleIsoTau30er_;
    TBranch *b_L1_DoubleIsoTau30er_;
    bool loaded_L1_DoubleIsoTau30er_;
    bool L1_DoubleIsoTau32er_;
    TBranch *b_L1_DoubleIsoTau32er_;
    bool loaded_L1_DoubleIsoTau32er_;
    bool L1_DoubleIsoTau32er2p1_;
    TBranch *b_L1_DoubleIsoTau32er2p1_;
    bool loaded_L1_DoubleIsoTau32er2p1_;
    bool L1_DoubleIsoTau33er_;
    TBranch *b_L1_DoubleIsoTau33er_;
    bool loaded_L1_DoubleIsoTau33er_;
    bool L1_DoubleIsoTau34er_;
    TBranch *b_L1_DoubleIsoTau34er_;
    bool loaded_L1_DoubleIsoTau34er_;
    bool L1_DoubleIsoTau34er2p1_;
    TBranch *b_L1_DoubleIsoTau34er2p1_;
    bool loaded_L1_DoubleIsoTau34er2p1_;
    bool L1_DoubleIsoTau35er_;
    TBranch *b_L1_DoubleIsoTau35er_;
    bool loaded_L1_DoubleIsoTau35er_;
    bool L1_DoubleIsoTau36er_;
    TBranch *b_L1_DoubleIsoTau36er_;
    bool loaded_L1_DoubleIsoTau36er_;
    bool L1_DoubleIsoTau36er2p1_;
    TBranch *b_L1_DoubleIsoTau36er2p1_;
    bool loaded_L1_DoubleIsoTau36er2p1_;
    bool L1_DoubleJet100er2p3_dEta_Max1p6_;
    TBranch *b_L1_DoubleJet100er2p3_dEta_Max1p6_;
    bool loaded_L1_DoubleJet100er2p3_dEta_Max1p6_;
    bool L1_DoubleJet100er2p5_;
    TBranch *b_L1_DoubleJet100er2p5_;
    bool loaded_L1_DoubleJet100er2p5_;
    bool L1_DoubleJet112er2p3_dEta_Max1p6_;
    TBranch *b_L1_DoubleJet112er2p3_dEta_Max1p6_;
    bool loaded_L1_DoubleJet112er2p3_dEta_Max1p6_;
    bool L1_DoubleJet120er2p5_;
    TBranch *b_L1_DoubleJet120er2p5_;
    bool loaded_L1_DoubleJet120er2p5_;
    bool L1_DoubleJet12_ForwardBackward_;
    TBranch *b_L1_DoubleJet12_ForwardBackward_;
    bool loaded_L1_DoubleJet12_ForwardBackward_;
    bool L1_DoubleJet150er2p5_;
    TBranch *b_L1_DoubleJet150er2p5_;
    bool loaded_L1_DoubleJet150er2p5_;
    bool L1_DoubleJet16_ForwardBackward_;
    TBranch *b_L1_DoubleJet16_ForwardBackward_;
    bool loaded_L1_DoubleJet16_ForwardBackward_;
    bool L1_DoubleJet30_Mj30j30_400_Mu10_;
    TBranch *b_L1_DoubleJet30_Mj30j30_400_Mu10_;
    bool loaded_L1_DoubleJet30_Mj30j30_400_Mu10_;
    bool L1_DoubleJet30_Mj30j30_400_Mu6_;
    TBranch *b_L1_DoubleJet30_Mj30j30_400_Mu6_;
    bool loaded_L1_DoubleJet30_Mj30j30_400_Mu6_;
    bool L1_DoubleJet30er2p5_Mass_Min150_dEta_Max1p5_;
    TBranch *b_L1_DoubleJet30er2p5_Mass_Min150_dEta_Max1p5_;
    bool loaded_L1_DoubleJet30er2p5_Mass_Min150_dEta_Max1p5_;
    bool L1_DoubleJet30er2p5_Mass_Min200_dEta_Max1p5_;
    TBranch *b_L1_DoubleJet30er2p5_Mass_Min200_dEta_Max1p5_;
    bool loaded_L1_DoubleJet30er2p5_Mass_Min200_dEta_Max1p5_;
    bool L1_DoubleJet30er2p5_Mass_Min250_dEta_Max1p5_;
    TBranch *b_L1_DoubleJet30er2p5_Mass_Min250_dEta_Max1p5_;
    bool loaded_L1_DoubleJet30er2p5_Mass_Min250_dEta_Max1p5_;
    bool L1_DoubleJet30er2p5_Mass_Min300_dEta_Max1p5_;
    TBranch *b_L1_DoubleJet30er2p5_Mass_Min300_dEta_Max1p5_;
    bool loaded_L1_DoubleJet30er2p5_Mass_Min300_dEta_Max1p5_;
    bool L1_DoubleJet30er2p5_Mass_Min330_dEta_Max1p5_;
    TBranch *b_L1_DoubleJet30er2p5_Mass_Min330_dEta_Max1p5_;
    bool loaded_L1_DoubleJet30er2p5_Mass_Min330_dEta_Max1p5_;
    bool L1_DoubleJet30er2p5_Mass_Min360_dEta_Max1p5_;
    TBranch *b_L1_DoubleJet30er2p5_Mass_Min360_dEta_Max1p5_;
    bool loaded_L1_DoubleJet30er2p5_Mass_Min360_dEta_Max1p5_;
    bool L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp_;
    TBranch *b_L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp_;
    bool loaded_L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp_;
    bool L1_DoubleJet40er2p5_;
    TBranch *b_L1_DoubleJet40er2p5_;
    bool loaded_L1_DoubleJet40er2p5_;
    bool L1_DoubleJet8_ForwardBackward_;
    TBranch *b_L1_DoubleJet8_ForwardBackward_;
    bool loaded_L1_DoubleJet8_ForwardBackward_;
    bool L1_DoubleJetC100_;
    TBranch *b_L1_DoubleJetC100_;
    bool loaded_L1_DoubleJetC100_;
    bool L1_DoubleJetC112_;
    TBranch *b_L1_DoubleJetC112_;
    bool loaded_L1_DoubleJetC112_;
    bool L1_DoubleJetC120_;
    TBranch *b_L1_DoubleJetC120_;
    bool loaded_L1_DoubleJetC120_;
    bool L1_DoubleJetC40_;
    TBranch *b_L1_DoubleJetC40_;
    bool loaded_L1_DoubleJetC40_;
    bool L1_DoubleJetC50_;
    TBranch *b_L1_DoubleJetC50_;
    bool loaded_L1_DoubleJetC50_;
    bool L1_DoubleJetC60_;
    TBranch *b_L1_DoubleJetC60_;
    bool loaded_L1_DoubleJetC60_;
    bool L1_DoubleJetC60_ETM60_;
    TBranch *b_L1_DoubleJetC60_ETM60_;
    bool loaded_L1_DoubleJetC60_ETM60_;
    bool L1_DoubleJetC80_;
    TBranch *b_L1_DoubleJetC80_;
    bool loaded_L1_DoubleJetC80_;
    bool L1_DoubleJet_100_30_DoubleJet30_Mass_Min620_;
    TBranch *b_L1_DoubleJet_100_30_DoubleJet30_Mass_Min620_;
    bool loaded_L1_DoubleJet_100_30_DoubleJet30_Mass_Min620_;
    bool L1_DoubleJet_100_30_Mj30j30_620_;
    TBranch *b_L1_DoubleJet_100_30_Mj30j30_620_;
    bool loaded_L1_DoubleJet_100_30_Mj30j30_620_;
    bool L1_DoubleJet_110_35_DoubleJet35_Mass_Min620_;
    TBranch *b_L1_DoubleJet_110_35_DoubleJet35_Mass_Min620_;
    bool loaded_L1_DoubleJet_110_35_DoubleJet35_Mass_Min620_;
    bool L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_;
    TBranch *b_L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_;
    bool loaded_L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_;
    bool L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_Jet60TT28_;
    TBranch *b_L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_Jet60TT28_;
    bool loaded_L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_Jet60TT28_;
    bool L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_;
    TBranch *b_L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_;
    bool loaded_L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_;
    bool L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_Jet60TT28_;
    TBranch *b_L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_Jet60TT28_;
    bool loaded_L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_Jet60TT28_;
    bool L1_DoubleJet_80_30_Mass_Min420_DoubleMu0_SQ_;
    TBranch *b_L1_DoubleJet_80_30_Mass_Min420_DoubleMu0_SQ_;
    bool loaded_L1_DoubleJet_80_30_Mass_Min420_DoubleMu0_SQ_;
    bool L1_DoubleJet_80_30_Mass_Min420_IsoTau40_RmOvlp_;
    TBranch *b_L1_DoubleJet_80_30_Mass_Min420_IsoTau40_RmOvlp_;
    bool loaded_L1_DoubleJet_80_30_Mass_Min420_IsoTau40_RmOvlp_;
    bool L1_DoubleJet_80_30_Mass_Min420_Mu8_;
    TBranch *b_L1_DoubleJet_80_30_Mass_Min420_Mu8_;
    bool loaded_L1_DoubleJet_80_30_Mass_Min420_Mu8_;
    bool L1_DoubleJet_90_30_DoubleJet30_Mass_Min620_;
    TBranch *b_L1_DoubleJet_90_30_DoubleJet30_Mass_Min620_;
    bool loaded_L1_DoubleJet_90_30_DoubleJet30_Mass_Min620_;
    bool L1_DoubleJet_90_30_Mj30j30_620_;
    TBranch *b_L1_DoubleJet_90_30_Mj30j30_620_;
    bool loaded_L1_DoubleJet_90_30_Mj30j30_620_;
    bool L1_DoubleLooseIsoEG22er2p1_;
    TBranch *b_L1_DoubleLooseIsoEG22er2p1_;
    bool loaded_L1_DoubleLooseIsoEG22er2p1_;
    bool L1_DoubleLooseIsoEG24er2p1_;
    TBranch *b_L1_DoubleLooseIsoEG24er2p1_;
    bool loaded_L1_DoubleLooseIsoEG24er2p1_;
    bool L1_DoubleMu0_;
    TBranch *b_L1_DoubleMu0_;
    bool loaded_L1_DoubleMu0_;
    bool L1_DoubleMu0_ETM40_;
    TBranch *b_L1_DoubleMu0_ETM40_;
    bool loaded_L1_DoubleMu0_ETM40_;
    bool L1_DoubleMu0_ETM55_;
    TBranch *b_L1_DoubleMu0_ETM55_;
    bool loaded_L1_DoubleMu0_ETM55_;
    bool L1_DoubleMu0_ETM60_;
    TBranch *b_L1_DoubleMu0_ETM60_;
    bool loaded_L1_DoubleMu0_ETM60_;
    bool L1_DoubleMu0_ETM65_;
    TBranch *b_L1_DoubleMu0_ETM65_;
    bool loaded_L1_DoubleMu0_ETM65_;
    bool L1_DoubleMu0_ETM70_;
    TBranch *b_L1_DoubleMu0_ETM70_;
    bool loaded_L1_DoubleMu0_ETM70_;
    bool L1_DoubleMu0_Mass_Min1_;
    TBranch *b_L1_DoubleMu0_Mass_Min1_;
    bool loaded_L1_DoubleMu0_Mass_Min1_;
    bool L1_DoubleMu0_OQ_;
    TBranch *b_L1_DoubleMu0_OQ_;
    bool loaded_L1_DoubleMu0_OQ_;
    bool L1_DoubleMu0_SQ_;
    TBranch *b_L1_DoubleMu0_SQ_;
    bool loaded_L1_DoubleMu0_SQ_;
    bool L1_DoubleMu0_SQ_OS_;
    TBranch *b_L1_DoubleMu0_SQ_OS_;
    bool loaded_L1_DoubleMu0_SQ_OS_;
    bool L1_DoubleMu0_dR_Max1p6_Jet90er2p5_dR_Max0p8_;
    TBranch *b_L1_DoubleMu0_dR_Max1p6_Jet90er2p5_dR_Max0p8_;
    bool loaded_L1_DoubleMu0_dR_Max1p6_Jet90er2p5_dR_Max0p8_;
    bool L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4_;
    TBranch *b_L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4_;
    bool loaded_L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4_;
    bool L1_DoubleMu0er1p4_dEta_Max1p8_OS_;
    TBranch *b_L1_DoubleMu0er1p4_dEta_Max1p8_OS_;
    bool loaded_L1_DoubleMu0er1p4_dEta_Max1p8_OS_;
    bool L1_DoubleMu0er1p5_SQ_;
    TBranch *b_L1_DoubleMu0er1p5_SQ_;
    bool loaded_L1_DoubleMu0er1p5_SQ_;
    bool L1_DoubleMu0er1p5_SQ_OS_;
    TBranch *b_L1_DoubleMu0er1p5_SQ_OS_;
    bool loaded_L1_DoubleMu0er1p5_SQ_OS_;
    bool L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4_;
    TBranch *b_L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4_;
    bool loaded_L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4_;
    bool L1_DoubleMu0er1p5_SQ_dR_Max1p4_;
    TBranch *b_L1_DoubleMu0er1p5_SQ_dR_Max1p4_;
    bool loaded_L1_DoubleMu0er1p5_SQ_dR_Max1p4_;
    bool L1_DoubleMu0er1p6_dEta_Max1p8_;
    TBranch *b_L1_DoubleMu0er1p6_dEta_Max1p8_;
    bool loaded_L1_DoubleMu0er1p6_dEta_Max1p8_;
    bool L1_DoubleMu0er1p6_dEta_Max1p8_OS_;
    TBranch *b_L1_DoubleMu0er1p6_dEta_Max1p8_OS_;
    bool loaded_L1_DoubleMu0er1p6_dEta_Max1p8_OS_;
    bool L1_DoubleMu0er2p0_SQ_OS_dR_Max1p4_;
    TBranch *b_L1_DoubleMu0er2p0_SQ_OS_dR_Max1p4_;
    bool loaded_L1_DoubleMu0er2p0_SQ_OS_dR_Max1p4_;
    bool L1_DoubleMu0er2p0_SQ_dR_Max1p4_;
    TBranch *b_L1_DoubleMu0er2p0_SQ_dR_Max1p4_;
    bool loaded_L1_DoubleMu0er2p0_SQ_dR_Max1p4_;
    bool L1_DoubleMu10_SQ_;
    TBranch *b_L1_DoubleMu10_SQ_;
    bool loaded_L1_DoubleMu10_SQ_;
    bool L1_DoubleMu18er2p1_;
    TBranch *b_L1_DoubleMu18er2p1_;
    bool loaded_L1_DoubleMu18er2p1_;
    bool L1_DoubleMu3_OS_DoubleEG7p5Upsilon_;
    TBranch *b_L1_DoubleMu3_OS_DoubleEG7p5Upsilon_;
    bool loaded_L1_DoubleMu3_OS_DoubleEG7p5Upsilon_;
    bool L1_DoubleMu3_SQ_ETMHF50_HTT60er_;
    TBranch *b_L1_DoubleMu3_SQ_ETMHF50_HTT60er_;
    bool loaded_L1_DoubleMu3_SQ_ETMHF50_HTT60er_;
    bool L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_;
    TBranch *b_L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_;
    bool loaded_L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_;
    bool L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_OR_DoubleJet40er2p5_;
    TBranch *b_L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_OR_DoubleJet40er2p5_;
    bool loaded_L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_OR_DoubleJet40er2p5_;
    bool L1_DoubleMu3_SQ_ETMHF60_Jet60er2p5_;
    TBranch *b_L1_DoubleMu3_SQ_ETMHF60_Jet60er2p5_;
    bool loaded_L1_DoubleMu3_SQ_ETMHF60_Jet60er2p5_;
    bool L1_DoubleMu3_SQ_HTT220er_;
    TBranch *b_L1_DoubleMu3_SQ_HTT220er_;
    bool loaded_L1_DoubleMu3_SQ_HTT220er_;
    bool L1_DoubleMu3_SQ_HTT240er_;
    TBranch *b_L1_DoubleMu3_SQ_HTT240er_;
    bool loaded_L1_DoubleMu3_SQ_HTT240er_;
    bool L1_DoubleMu3_SQ_HTT260er_;
    TBranch *b_L1_DoubleMu3_SQ_HTT260er_;
    bool loaded_L1_DoubleMu3_SQ_HTT260er_;
    bool L1_DoubleMu3_dR_Max1p6_Jet90er2p5_dR_Max0p8_;
    TBranch *b_L1_DoubleMu3_dR_Max1p6_Jet90er2p5_dR_Max0p8_;
    bool loaded_L1_DoubleMu3_dR_Max1p6_Jet90er2p5_dR_Max0p8_;
    bool L1_DoubleMu4_SQ_EG9er2p5_;
    TBranch *b_L1_DoubleMu4_SQ_EG9er2p5_;
    bool loaded_L1_DoubleMu4_SQ_EG9er2p5_;
    bool L1_DoubleMu4_SQ_OS_;
    TBranch *b_L1_DoubleMu4_SQ_OS_;
    bool loaded_L1_DoubleMu4_SQ_OS_;
    bool L1_DoubleMu4_SQ_OS_dR_Max1p2_;
    TBranch *b_L1_DoubleMu4_SQ_OS_dR_Max1p2_;
    bool loaded_L1_DoubleMu4_SQ_OS_dR_Max1p2_;
    bool L1_DoubleMu4p5_SQ_OS_;
    TBranch *b_L1_DoubleMu4p5_SQ_OS_;
    bool loaded_L1_DoubleMu4p5_SQ_OS_;
    bool L1_DoubleMu4p5_SQ_OS_dR_Max1p2_;
    TBranch *b_L1_DoubleMu4p5_SQ_OS_dR_Max1p2_;
    bool loaded_L1_DoubleMu4p5_SQ_OS_dR_Max1p2_;
    bool L1_DoubleMu4p5er2p0_SQ_OS_;
    TBranch *b_L1_DoubleMu4p5er2p0_SQ_OS_;
    bool loaded_L1_DoubleMu4p5er2p0_SQ_OS_;
    bool L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18_;
    TBranch *b_L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18_;
    bool loaded_L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18_;
    bool L1_DoubleMu5Upsilon_OS_DoubleEG3_;
    TBranch *b_L1_DoubleMu5Upsilon_OS_DoubleEG3_;
    bool loaded_L1_DoubleMu5Upsilon_OS_DoubleEG3_;
    bool L1_DoubleMu5_SQ_EG9er2p5_;
    TBranch *b_L1_DoubleMu5_SQ_EG9er2p5_;
    bool loaded_L1_DoubleMu5_SQ_EG9er2p5_;
    bool L1_DoubleMu7_EG14_;
    TBranch *b_L1_DoubleMu7_EG14_;
    bool loaded_L1_DoubleMu7_EG14_;
    bool L1_DoubleMu7_EG7_;
    TBranch *b_L1_DoubleMu7_EG7_;
    bool loaded_L1_DoubleMu7_EG7_;
    bool L1_DoubleMu9_SQ_;
    TBranch *b_L1_DoubleMu9_SQ_;
    bool loaded_L1_DoubleMu9_SQ_;
    bool L1_DoubleMuOpen_;
    TBranch *b_L1_DoubleMuOpen_;
    bool loaded_L1_DoubleMuOpen_;
    bool L1_DoubleMu_10_0_dEta_Max1p8_;
    TBranch *b_L1_DoubleMu_10_0_dEta_Max1p8_;
    bool loaded_L1_DoubleMu_10_0_dEta_Max1p8_;
    bool L1_DoubleMu_10_3p5_;
    TBranch *b_L1_DoubleMu_10_3p5_;
    bool loaded_L1_DoubleMu_10_3p5_;
    bool L1_DoubleMu_10_Open_;
    TBranch *b_L1_DoubleMu_10_Open_;
    bool loaded_L1_DoubleMu_10_Open_;
    bool L1_DoubleMu_11_4_;
    TBranch *b_L1_DoubleMu_11_4_;
    bool loaded_L1_DoubleMu_11_4_;
    bool L1_DoubleMu_12_5_;
    TBranch *b_L1_DoubleMu_12_5_;
    bool loaded_L1_DoubleMu_12_5_;
    bool L1_DoubleMu_12_8_;
    TBranch *b_L1_DoubleMu_12_8_;
    bool loaded_L1_DoubleMu_12_8_;
    bool L1_DoubleMu_13_6_;
    TBranch *b_L1_DoubleMu_13_6_;
    bool loaded_L1_DoubleMu_13_6_;
    bool L1_DoubleMu_15_5_;
    TBranch *b_L1_DoubleMu_15_5_;
    bool loaded_L1_DoubleMu_15_5_;
    bool L1_DoubleMu_15_5_SQ_;
    TBranch *b_L1_DoubleMu_15_5_SQ_;
    bool loaded_L1_DoubleMu_15_5_SQ_;
    bool L1_DoubleMu_15_7_;
    TBranch *b_L1_DoubleMu_15_7_;
    bool loaded_L1_DoubleMu_15_7_;
    bool L1_DoubleMu_15_7_Mass_Min1_;
    TBranch *b_L1_DoubleMu_15_7_Mass_Min1_;
    bool loaded_L1_DoubleMu_15_7_Mass_Min1_;
    bool L1_DoubleMu_15_7_SQ_;
    TBranch *b_L1_DoubleMu_15_7_SQ_;
    bool loaded_L1_DoubleMu_15_7_SQ_;
    bool L1_DoubleTau50er_;
    TBranch *b_L1_DoubleTau50er_;
    bool loaded_L1_DoubleTau50er_;
    bool L1_DoubleTau70er_;
    TBranch *b_L1_DoubleTau70er_;
    bool loaded_L1_DoubleTau70er_;
    bool L1_DoubleTau70er2p1_;
    TBranch *b_L1_DoubleTau70er2p1_;
    bool loaded_L1_DoubleTau70er2p1_;
    bool L1_EG25er_HTT125_;
    TBranch *b_L1_EG25er_HTT125_;
    bool loaded_L1_EG25er_HTT125_;
    bool L1_EG27er_HTT200_;
    TBranch *b_L1_EG27er_HTT200_;
    bool loaded_L1_EG27er_HTT200_;
    bool L1_ETM100_;
    TBranch *b_L1_ETM100_;
    bool loaded_L1_ETM100_;
    bool L1_ETM105_;
    TBranch *b_L1_ETM105_;
    bool loaded_L1_ETM105_;
    bool L1_ETM110_;
    TBranch *b_L1_ETM110_;
    bool loaded_L1_ETM110_;
    bool L1_ETM115_;
    TBranch *b_L1_ETM115_;
    bool loaded_L1_ETM115_;
    bool L1_ETM120_;
    TBranch *b_L1_ETM120_;
    bool loaded_L1_ETM120_;
    bool L1_ETM150_;
    TBranch *b_L1_ETM150_;
    bool loaded_L1_ETM150_;
    bool L1_ETM30_;
    TBranch *b_L1_ETM30_;
    bool loaded_L1_ETM30_;
    bool L1_ETM40_;
    TBranch *b_L1_ETM40_;
    bool loaded_L1_ETM40_;
    bool L1_ETM50_;
    TBranch *b_L1_ETM50_;
    bool loaded_L1_ETM50_;
    bool L1_ETM60_;
    TBranch *b_L1_ETM60_;
    bool loaded_L1_ETM60_;
    bool L1_ETM70_;
    TBranch *b_L1_ETM70_;
    bool loaded_L1_ETM70_;
    bool L1_ETM75_;
    TBranch *b_L1_ETM75_;
    bool loaded_L1_ETM75_;
    bool L1_ETM75_Jet60_dPhi_Min0p4_;
    TBranch *b_L1_ETM75_Jet60_dPhi_Min0p4_;
    bool loaded_L1_ETM75_Jet60_dPhi_Min0p4_;
    bool L1_ETM80_;
    TBranch *b_L1_ETM80_;
    bool loaded_L1_ETM80_;
    bool L1_ETM85_;
    TBranch *b_L1_ETM85_;
    bool loaded_L1_ETM85_;
    bool L1_ETM90_;
    TBranch *b_L1_ETM90_;
    bool loaded_L1_ETM90_;
    bool L1_ETM95_;
    TBranch *b_L1_ETM95_;
    bool loaded_L1_ETM95_;
    bool L1_ETMHF100_;
    TBranch *b_L1_ETMHF100_;
    bool loaded_L1_ETMHF100_;
    bool L1_ETMHF100_HTT60er_;
    TBranch *b_L1_ETMHF100_HTT60er_;
    bool loaded_L1_ETMHF100_HTT60er_;
    bool L1_ETMHF110_;
    TBranch *b_L1_ETMHF110_;
    bool loaded_L1_ETMHF110_;
    bool L1_ETMHF110_HTT60er_;
    TBranch *b_L1_ETMHF110_HTT60er_;
    bool loaded_L1_ETMHF110_HTT60er_;
    bool L1_ETMHF110_HTT60er_NotSecondBunchInTrain_;
    TBranch *b_L1_ETMHF110_HTT60er_NotSecondBunchInTrain_;
    bool loaded_L1_ETMHF110_HTT60er_NotSecondBunchInTrain_;
    bool L1_ETMHF120_;
    TBranch *b_L1_ETMHF120_;
    bool loaded_L1_ETMHF120_;
    bool L1_ETMHF120_HTT60er_;
    TBranch *b_L1_ETMHF120_HTT60er_;
    bool loaded_L1_ETMHF120_HTT60er_;
    bool L1_ETMHF120_NotSecondBunchInTrain_;
    TBranch *b_L1_ETMHF120_NotSecondBunchInTrain_;
    bool loaded_L1_ETMHF120_NotSecondBunchInTrain_;
    bool L1_ETMHF130_;
    TBranch *b_L1_ETMHF130_;
    bool loaded_L1_ETMHF130_;
    bool L1_ETMHF130_HTT60er_;
    TBranch *b_L1_ETMHF130_HTT60er_;
    bool loaded_L1_ETMHF130_HTT60er_;
    bool L1_ETMHF140_;
    TBranch *b_L1_ETMHF140_;
    bool loaded_L1_ETMHF140_;
    bool L1_ETMHF150_;
    TBranch *b_L1_ETMHF150_;
    bool loaded_L1_ETMHF150_;
    bool L1_ETMHF90_HTT60er_;
    TBranch *b_L1_ETMHF90_HTT60er_;
    bool loaded_L1_ETMHF90_HTT60er_;
    bool L1_ETT1200_;
    TBranch *b_L1_ETT1200_;
    bool loaded_L1_ETT1200_;
    bool L1_ETT1600_;
    TBranch *b_L1_ETT1600_;
    bool loaded_L1_ETT1600_;
    bool L1_ETT2000_;
    TBranch *b_L1_ETT2000_;
    bool loaded_L1_ETT2000_;
    bool L1_ETT25_;
    TBranch *b_L1_ETT25_;
    bool loaded_L1_ETT25_;
    bool L1_ETT40_BptxAND_;
    TBranch *b_L1_ETT40_BptxAND_;
    bool loaded_L1_ETT40_BptxAND_;
    bool L1_ETT50_BptxAND_;
    TBranch *b_L1_ETT50_BptxAND_;
    bool loaded_L1_ETT50_BptxAND_;
    bool L1_ETT55_BptxAND_;
    TBranch *b_L1_ETT55_BptxAND_;
    bool loaded_L1_ETT55_BptxAND_;
    bool L1_ETT60_BptxAND_;
    TBranch *b_L1_ETT60_BptxAND_;
    bool loaded_L1_ETT60_BptxAND_;
    bool L1_ETT70_BptxAND_;
    TBranch *b_L1_ETT70_BptxAND_;
    bool loaded_L1_ETT70_BptxAND_;
    bool L1_ETT75_BptxAND_;
    TBranch *b_L1_ETT75_BptxAND_;
    bool loaded_L1_ETT75_BptxAND_;
    bool L1_FirstBunchAfterTrain_;
    TBranch *b_L1_FirstBunchAfterTrain_;
    bool loaded_L1_FirstBunchAfterTrain_;
    bool L1_FirstBunchBeforeTrain_;
    TBranch *b_L1_FirstBunchBeforeTrain_;
    bool loaded_L1_FirstBunchBeforeTrain_;
    bool L1_FirstBunchInTrain_;
    TBranch *b_L1_FirstBunchInTrain_;
    bool loaded_L1_FirstBunchInTrain_;
    bool L1_FirstCollisionInOrbit_;
    TBranch *b_L1_FirstCollisionInOrbit_;
    bool loaded_L1_FirstCollisionInOrbit_;
    bool L1_FirstCollisionInTrain_;
    TBranch *b_L1_FirstCollisionInTrain_;
    bool loaded_L1_FirstCollisionInTrain_;
    bool L1_HCAL_LaserMon_Trig_;
    TBranch *b_L1_HCAL_LaserMon_Trig_;
    bool loaded_L1_HCAL_LaserMon_Trig_;
    bool L1_HCAL_LaserMon_Veto_;
    TBranch *b_L1_HCAL_LaserMon_Veto_;
    bool loaded_L1_HCAL_LaserMon_Veto_;
    bool L1_HTM100_;
    TBranch *b_L1_HTM100_;
    bool loaded_L1_HTM100_;
    bool L1_HTM120_;
    TBranch *b_L1_HTM120_;
    bool loaded_L1_HTM120_;
    bool L1_HTM130_;
    TBranch *b_L1_HTM130_;
    bool loaded_L1_HTM130_;
    bool L1_HTM140_;
    TBranch *b_L1_HTM140_;
    bool loaded_L1_HTM140_;
    bool L1_HTM150_;
    TBranch *b_L1_HTM150_;
    bool loaded_L1_HTM150_;
    bool L1_HTM50_;
    TBranch *b_L1_HTM50_;
    bool loaded_L1_HTM50_;
    bool L1_HTM60_HTT260_;
    TBranch *b_L1_HTM60_HTT260_;
    bool loaded_L1_HTM60_HTT260_;
    bool L1_HTM70_;
    TBranch *b_L1_HTM70_;
    bool loaded_L1_HTM70_;
    bool L1_HTM80_;
    TBranch *b_L1_HTM80_;
    bool loaded_L1_HTM80_;
    bool L1_HTM80_HTT220_;
    TBranch *b_L1_HTM80_HTT220_;
    bool loaded_L1_HTM80_HTT220_;
    bool L1_HTT120_;
    TBranch *b_L1_HTT120_;
    bool loaded_L1_HTT120_;
    bool L1_HTT120er_;
    TBranch *b_L1_HTT120er_;
    bool loaded_L1_HTT120er_;
    bool L1_HTT160_;
    TBranch *b_L1_HTT160_;
    bool loaded_L1_HTT160_;
    bool L1_HTT160er_;
    TBranch *b_L1_HTT160er_;
    bool loaded_L1_HTT160er_;
    bool L1_HTT200_;
    TBranch *b_L1_HTT200_;
    bool loaded_L1_HTT200_;
    bool L1_HTT200er_;
    TBranch *b_L1_HTT200er_;
    bool loaded_L1_HTT200er_;
    bool L1_HTT220_;
    TBranch *b_L1_HTT220_;
    bool loaded_L1_HTT220_;
    bool L1_HTT240_;
    TBranch *b_L1_HTT240_;
    bool loaded_L1_HTT240_;
    bool L1_HTT255_;
    TBranch *b_L1_HTT255_;
    bool loaded_L1_HTT255_;
    bool L1_HTT255er_;
    TBranch *b_L1_HTT255er_;
    bool loaded_L1_HTT255er_;
    bool L1_HTT270_;
    TBranch *b_L1_HTT270_;
    bool loaded_L1_HTT270_;
    bool L1_HTT280_;
    TBranch *b_L1_HTT280_;
    bool loaded_L1_HTT280_;
    bool L1_HTT280er_;
    TBranch *b_L1_HTT280er_;
    bool loaded_L1_HTT280er_;
    bool L1_HTT280er_QuadJet_70_55_40_35_er2p4_;
    TBranch *b_L1_HTT280er_QuadJet_70_55_40_35_er2p4_;
    bool loaded_L1_HTT280er_QuadJet_70_55_40_35_er2p4_;
    bool L1_HTT300_;
    TBranch *b_L1_HTT300_;
    bool loaded_L1_HTT300_;
    bool L1_HTT320_;
    TBranch *b_L1_HTT320_;
    bool loaded_L1_HTT320_;
    bool L1_HTT320er_;
    TBranch *b_L1_HTT320er_;
    bool loaded_L1_HTT320er_;
    bool L1_HTT320er_QuadJet_70_55_40_40_er2p4_;
    TBranch *b_L1_HTT320er_QuadJet_70_55_40_40_er2p4_;
    bool loaded_L1_HTT320er_QuadJet_70_55_40_40_er2p4_;
    bool L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3_;
    TBranch *b_L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3_;
    bool loaded_L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3_;
    bool L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3_;
    TBranch *b_L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3_;
    bool loaded_L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3_;
    bool L1_HTT360er_;
    TBranch *b_L1_HTT360er_;
    bool loaded_L1_HTT360er_;
    bool L1_HTT400er_;
    TBranch *b_L1_HTT400er_;
    bool loaded_L1_HTT400er_;
    bool L1_HTT450er_;
    TBranch *b_L1_HTT450er_;
    bool loaded_L1_HTT450er_;
    bool L1_IsoEG18er_IsoTau24er_dEta_Min0p2_;
    TBranch *b_L1_IsoEG18er_IsoTau24er_dEta_Min0p2_;
    bool loaded_L1_IsoEG18er_IsoTau24er_dEta_Min0p2_;
    bool L1_IsoEG20er_IsoTau25er_dEta_Min0p2_;
    TBranch *b_L1_IsoEG20er_IsoTau25er_dEta_Min0p2_;
    bool loaded_L1_IsoEG20er_IsoTau25er_dEta_Min0p2_;
    bool L1_IsoEG22er_IsoTau26er_dEta_Min0p2_;
    TBranch *b_L1_IsoEG22er_IsoTau26er_dEta_Min0p2_;
    bool loaded_L1_IsoEG22er_IsoTau26er_dEta_Min0p2_;
    bool L1_IsoEG22er_Tau20er_dEta_Min0p2_;
    TBranch *b_L1_IsoEG22er_Tau20er_dEta_Min0p2_;
    bool loaded_L1_IsoEG22er_Tau20er_dEta_Min0p2_;
    bool L1_IsoEG32er2p5_Mt40_;
    TBranch *b_L1_IsoEG32er2p5_Mt40_;
    bool loaded_L1_IsoEG32er2p5_Mt40_;
    bool L1_IsoEG32er2p5_Mt44_;
    TBranch *b_L1_IsoEG32er2p5_Mt44_;
    bool loaded_L1_IsoEG32er2p5_Mt44_;
    bool L1_IsoEG32er2p5_Mt48_;
    TBranch *b_L1_IsoEG32er2p5_Mt48_;
    bool loaded_L1_IsoEG32er2p5_Mt48_;
    bool L1_IsoTau40er2p1_ETMHF100_;
    TBranch *b_L1_IsoTau40er2p1_ETMHF100_;
    bool loaded_L1_IsoTau40er2p1_ETMHF100_;
    bool L1_IsoTau40er2p1_ETMHF110_;
    TBranch *b_L1_IsoTau40er2p1_ETMHF110_;
    bool loaded_L1_IsoTau40er2p1_ETMHF110_;
    bool L1_IsoTau40er2p1_ETMHF120_;
    TBranch *b_L1_IsoTau40er2p1_ETMHF120_;
    bool loaded_L1_IsoTau40er2p1_ETMHF120_;
    bool L1_IsoTau40er2p1_ETMHF90_;
    TBranch *b_L1_IsoTau40er2p1_ETMHF90_;
    bool loaded_L1_IsoTau40er2p1_ETMHF90_;
    bool L1_IsolatedBunch_;
    TBranch *b_L1_IsolatedBunch_;
    bool loaded_L1_IsolatedBunch_;
    bool L1_Jet32_DoubleMu_10_0_dPhi_Jet_Mu0_Max0p4_dPhi_Mu_Mu_Min1p0_;
    TBranch *b_L1_Jet32_DoubleMu_10_0_dPhi_Jet_Mu0_Max0p4_dPhi_Mu_Mu_Min1p0_;
    bool loaded_L1_Jet32_DoubleMu_10_0_dPhi_Jet_Mu0_Max0p4_dPhi_Mu_Mu_Min1p0_;
    bool L1_Jet32_Mu0_EG10_dPhi_Jet_Mu_Max0p4_dPhi_Mu_EG_Min1p0_;
    TBranch *b_L1_Jet32_Mu0_EG10_dPhi_Jet_Mu_Max0p4_dPhi_Mu_EG_Min1p0_;
    bool loaded_L1_Jet32_Mu0_EG10_dPhi_Jet_Mu_Max0p4_dPhi_Mu_EG_Min1p0_;
    bool L1_LastBunchInTrain_;
    TBranch *b_L1_LastBunchInTrain_;
    bool loaded_L1_LastBunchInTrain_;
    bool L1_LastCollisionInTrain_;
    TBranch *b_L1_LastCollisionInTrain_;
    bool loaded_L1_LastCollisionInTrain_;
    bool L1_LooseIsoEG22er2p1_IsoTau26er2p1_dR_Min0p3_;
    TBranch *b_L1_LooseIsoEG22er2p1_IsoTau26er2p1_dR_Min0p3_;
    bool loaded_L1_LooseIsoEG22er2p1_IsoTau26er2p1_dR_Min0p3_;
    bool L1_LooseIsoEG22er2p1_Tau70er2p1_dR_Min0p3_;
    TBranch *b_L1_LooseIsoEG22er2p1_Tau70er2p1_dR_Min0p3_;
    bool loaded_L1_LooseIsoEG22er2p1_Tau70er2p1_dR_Min0p3_;
    bool L1_LooseIsoEG24er2p1_HTT100er_;
    TBranch *b_L1_LooseIsoEG24er2p1_HTT100er_;
    bool loaded_L1_LooseIsoEG24er2p1_HTT100er_;
    bool L1_LooseIsoEG24er2p1_IsoTau27er2p1_dR_Min0p3_;
    TBranch *b_L1_LooseIsoEG24er2p1_IsoTau27er2p1_dR_Min0p3_;
    bool loaded_L1_LooseIsoEG24er2p1_IsoTau27er2p1_dR_Min0p3_;
    bool L1_LooseIsoEG26er2p1_HTT100er_;
    TBranch *b_L1_LooseIsoEG26er2p1_HTT100er_;
    bool loaded_L1_LooseIsoEG26er2p1_HTT100er_;
    bool L1_LooseIsoEG26er2p1_Jet34er2p5_dR_Min0p3_;
    TBranch *b_L1_LooseIsoEG26er2p1_Jet34er2p5_dR_Min0p3_;
    bool loaded_L1_LooseIsoEG26er2p1_Jet34er2p5_dR_Min0p3_;
    bool L1_LooseIsoEG28er2p1_HTT100er_;
    TBranch *b_L1_LooseIsoEG28er2p1_HTT100er_;
    bool loaded_L1_LooseIsoEG28er2p1_HTT100er_;
    bool L1_LooseIsoEG28er2p1_Jet34er2p5_dR_Min0p3_;
    TBranch *b_L1_LooseIsoEG28er2p1_Jet34er2p5_dR_Min0p3_;
    bool loaded_L1_LooseIsoEG28er2p1_Jet34er2p5_dR_Min0p3_;
    bool L1_LooseIsoEG30er2p1_HTT100er_;
    TBranch *b_L1_LooseIsoEG30er2p1_HTT100er_;
    bool loaded_L1_LooseIsoEG30er2p1_HTT100er_;
    bool L1_LooseIsoEG30er2p1_Jet34er2p5_dR_Min0p3_;
    TBranch *b_L1_LooseIsoEG30er2p1_Jet34er2p5_dR_Min0p3_;
    bool loaded_L1_LooseIsoEG30er2p1_Jet34er2p5_dR_Min0p3_;
    bool L1_MU20_EG15_;
    TBranch *b_L1_MU20_EG15_;
    bool loaded_L1_MU20_EG15_;
    bool L1_MinimumBiasHF0_AND_;
    TBranch *b_L1_MinimumBiasHF0_AND_;
    bool loaded_L1_MinimumBiasHF0_AND_;
    bool L1_MinimumBiasHF0_AND_BptxAND_;
    TBranch *b_L1_MinimumBiasHF0_AND_BptxAND_;
    bool loaded_L1_MinimumBiasHF0_AND_BptxAND_;
    bool L1_MinimumBiasHF0_OR_;
    TBranch *b_L1_MinimumBiasHF0_OR_;
    bool loaded_L1_MinimumBiasHF0_OR_;
    bool L1_MinimumBiasHF0_OR_BptxAND_;
    TBranch *b_L1_MinimumBiasHF0_OR_BptxAND_;
    bool loaded_L1_MinimumBiasHF0_OR_BptxAND_;
    bool L1_MinimumBiasHF1_AND_;
    TBranch *b_L1_MinimumBiasHF1_AND_;
    bool loaded_L1_MinimumBiasHF1_AND_;
    bool L1_MinimumBiasHF1_AND_BptxAND_;
    TBranch *b_L1_MinimumBiasHF1_AND_BptxAND_;
    bool loaded_L1_MinimumBiasHF1_AND_BptxAND_;
    bool L1_MinimumBiasHF1_OR_;
    TBranch *b_L1_MinimumBiasHF1_OR_;
    bool loaded_L1_MinimumBiasHF1_OR_;
    bool L1_MinimumBiasHF1_OR_BptxAND_;
    TBranch *b_L1_MinimumBiasHF1_OR_BptxAND_;
    bool loaded_L1_MinimumBiasHF1_OR_BptxAND_;
    bool L1_Mu0er_ETM40_;
    TBranch *b_L1_Mu0er_ETM40_;
    bool loaded_L1_Mu0er_ETM40_;
    bool L1_Mu0er_ETM55_;
    TBranch *b_L1_Mu0er_ETM55_;
    bool loaded_L1_Mu0er_ETM55_;
    bool L1_Mu10er2p3_Jet32er2p3_dR_Max0p4_DoubleJet32er2p3_dEta_Max1p6_;
    TBranch *b_L1_Mu10er2p3_Jet32er2p3_dR_Max0p4_DoubleJet32er2p3_dEta_Max1p6_;
    bool loaded_L1_Mu10er2p3_Jet32er2p3_dR_Max0p4_DoubleJet32er2p3_dEta_Max1p6_;
    bool L1_Mu10er_ETM30_;
    TBranch *b_L1_Mu10er_ETM30_;
    bool loaded_L1_Mu10er_ETM30_;
    bool L1_Mu10er_ETM50_;
    TBranch *b_L1_Mu10er_ETM50_;
    bool loaded_L1_Mu10er_ETM50_;
    bool L1_Mu12_EG10_;
    TBranch *b_L1_Mu12_EG10_;
    bool loaded_L1_Mu12_EG10_;
    bool L1_Mu12er2p3_Jet40er2p1_dR_Max0p4_DoubleJet40er2p1_dEta_Max1p6_;
    TBranch *b_L1_Mu12er2p3_Jet40er2p1_dR_Max0p4_DoubleJet40er2p1_dEta_Max1p6_;
    bool loaded_L1_Mu12er2p3_Jet40er2p1_dR_Max0p4_DoubleJet40er2p1_dEta_Max1p6_;
    bool L1_Mu12er2p3_Jet40er2p3_dR_Max0p4_DoubleJet40er2p3_dEta_Max1p6_;
    TBranch *b_L1_Mu12er2p3_Jet40er2p3_dR_Max0p4_DoubleJet40er2p3_dEta_Max1p6_;
    bool loaded_L1_Mu12er2p3_Jet40er2p3_dR_Max0p4_DoubleJet40er2p3_dEta_Max1p6_;
    bool L1_Mu14er_ETM30_;
    TBranch *b_L1_Mu14er_ETM30_;
    bool loaded_L1_Mu14er_ETM30_;
    bool L1_Mu16er_Tau20er_;
    TBranch *b_L1_Mu16er_Tau20er_;
    bool loaded_L1_Mu16er_Tau20er_;
    bool L1_Mu16er_Tau24er_;
    TBranch *b_L1_Mu16er_Tau24er_;
    bool loaded_L1_Mu16er_Tau24er_;
    bool L1_Mu18er2p1_Tau24er2p1_;
    TBranch *b_L1_Mu18er2p1_Tau24er2p1_;
    bool loaded_L1_Mu18er2p1_Tau24er2p1_;
    bool L1_Mu18er2p1_Tau26er2p1_;
    TBranch *b_L1_Mu18er2p1_Tau26er2p1_;
    bool loaded_L1_Mu18er2p1_Tau26er2p1_;
    bool L1_Mu18er_IsoTau26er_;
    TBranch *b_L1_Mu18er_IsoTau26er_;
    bool loaded_L1_Mu18er_IsoTau26er_;
    bool L1_Mu18er_Tau20er_;
    TBranch *b_L1_Mu18er_Tau20er_;
    bool loaded_L1_Mu18er_Tau20er_;
    bool L1_Mu18er_Tau24er_;
    TBranch *b_L1_Mu18er_Tau24er_;
    bool loaded_L1_Mu18er_Tau24er_;
    bool L1_Mu20_EG10_;
    TBranch *b_L1_Mu20_EG10_;
    bool loaded_L1_Mu20_EG10_;
    bool L1_Mu20_EG10er2p5_;
    TBranch *b_L1_Mu20_EG10er2p5_;
    bool loaded_L1_Mu20_EG10er2p5_;
    bool L1_Mu20_EG17_;
    TBranch *b_L1_Mu20_EG17_;
    bool loaded_L1_Mu20_EG17_;
    bool L1_Mu20_IsoEG6_;
    TBranch *b_L1_Mu20_IsoEG6_;
    bool loaded_L1_Mu20_IsoEG6_;
    bool L1_Mu20er_IsoTau26er_;
    TBranch *b_L1_Mu20er_IsoTau26er_;
    bool loaded_L1_Mu20er_IsoTau26er_;
    bool L1_Mu22er2p1_IsoTau32er2p1_;
    TBranch *b_L1_Mu22er2p1_IsoTau32er2p1_;
    bool loaded_L1_Mu22er2p1_IsoTau32er2p1_;
    bool L1_Mu22er2p1_IsoTau34er2p1_;
    TBranch *b_L1_Mu22er2p1_IsoTau34er2p1_;
    bool loaded_L1_Mu22er2p1_IsoTau34er2p1_;
    bool L1_Mu22er2p1_IsoTau36er2p1_;
    TBranch *b_L1_Mu22er2p1_IsoTau36er2p1_;
    bool loaded_L1_Mu22er2p1_IsoTau36er2p1_;
    bool L1_Mu22er2p1_IsoTau40er2p1_;
    TBranch *b_L1_Mu22er2p1_IsoTau40er2p1_;
    bool loaded_L1_Mu22er2p1_IsoTau40er2p1_;
    bool L1_Mu22er2p1_Tau70er2p1_;
    TBranch *b_L1_Mu22er2p1_Tau70er2p1_;
    bool loaded_L1_Mu22er2p1_Tau70er2p1_;
    bool L1_Mu22er_IsoTau26er_;
    TBranch *b_L1_Mu22er_IsoTau26er_;
    bool loaded_L1_Mu22er_IsoTau26er_;
    bool L1_Mu23_EG10_;
    TBranch *b_L1_Mu23_EG10_;
    bool loaded_L1_Mu23_EG10_;
    bool L1_Mu23_IsoEG10_;
    TBranch *b_L1_Mu23_IsoEG10_;
    bool loaded_L1_Mu23_IsoEG10_;
    bool L1_Mu25er_IsoTau26er_;
    TBranch *b_L1_Mu25er_IsoTau26er_;
    bool loaded_L1_Mu25er_IsoTau26er_;
    bool L1_Mu3_Jet120er2p5_dR_Max0p4_;
    TBranch *b_L1_Mu3_Jet120er2p5_dR_Max0p4_;
    bool loaded_L1_Mu3_Jet120er2p5_dR_Max0p4_;
    bool L1_Mu3_Jet120er2p5_dR_Max0p8_;
    TBranch *b_L1_Mu3_Jet120er2p5_dR_Max0p8_;
    bool loaded_L1_Mu3_Jet120er2p5_dR_Max0p8_;
    bool L1_Mu3_Jet16er2p5_dR_Max0p4_;
    TBranch *b_L1_Mu3_Jet16er2p5_dR_Max0p4_;
    bool loaded_L1_Mu3_Jet16er2p5_dR_Max0p4_;
    bool L1_Mu3_Jet30er2p5_;
    TBranch *b_L1_Mu3_Jet30er2p5_;
    bool loaded_L1_Mu3_Jet30er2p5_;
    bool L1_Mu3_Jet35er2p5_dR_Max0p4_;
    TBranch *b_L1_Mu3_Jet35er2p5_dR_Max0p4_;
    bool loaded_L1_Mu3_Jet35er2p5_dR_Max0p4_;
    bool L1_Mu3_Jet60er2p5_dR_Max0p4_;
    TBranch *b_L1_Mu3_Jet60er2p5_dR_Max0p4_;
    bool loaded_L1_Mu3_Jet60er2p5_dR_Max0p4_;
    bool L1_Mu3_Jet80er2p5_dR_Max0p4_;
    TBranch *b_L1_Mu3_Jet80er2p5_dR_Max0p4_;
    bool loaded_L1_Mu3_Jet80er2p5_dR_Max0p4_;
    bool L1_Mu3_JetC120_;
    TBranch *b_L1_Mu3_JetC120_;
    bool loaded_L1_Mu3_JetC120_;
    bool L1_Mu3_JetC120_dEta_Max0p4_dPhi_Max0p4_;
    TBranch *b_L1_Mu3_JetC120_dEta_Max0p4_dPhi_Max0p4_;
    bool loaded_L1_Mu3_JetC120_dEta_Max0p4_dPhi_Max0p4_;
    bool L1_Mu3_JetC16_;
    TBranch *b_L1_Mu3_JetC16_;
    bool loaded_L1_Mu3_JetC16_;
    bool L1_Mu3_JetC16_dEta_Max0p4_dPhi_Max0p4_;
    TBranch *b_L1_Mu3_JetC16_dEta_Max0p4_dPhi_Max0p4_;
    bool loaded_L1_Mu3_JetC16_dEta_Max0p4_dPhi_Max0p4_;
    bool L1_Mu3_JetC60_;
    TBranch *b_L1_Mu3_JetC60_;
    bool loaded_L1_Mu3_JetC60_;
    bool L1_Mu3_JetC60_dEta_Max0p4_dPhi_Max0p4_;
    TBranch *b_L1_Mu3_JetC60_dEta_Max0p4_dPhi_Max0p4_;
    bool loaded_L1_Mu3_JetC60_dEta_Max0p4_dPhi_Max0p4_;
    bool L1_Mu3er1p5_Jet100er2p5_ETMHF40_;
    TBranch *b_L1_Mu3er1p5_Jet100er2p5_ETMHF40_;
    bool loaded_L1_Mu3er1p5_Jet100er2p5_ETMHF40_;
    bool L1_Mu3er1p5_Jet100er2p5_ETMHF50_;
    TBranch *b_L1_Mu3er1p5_Jet100er2p5_ETMHF50_;
    bool loaded_L1_Mu3er1p5_Jet100er2p5_ETMHF50_;
    bool L1_Mu5_EG15_;
    TBranch *b_L1_Mu5_EG15_;
    bool loaded_L1_Mu5_EG15_;
    bool L1_Mu5_EG20_;
    TBranch *b_L1_Mu5_EG20_;
    bool loaded_L1_Mu5_EG20_;
    bool L1_Mu5_EG23_;
    TBranch *b_L1_Mu5_EG23_;
    bool loaded_L1_Mu5_EG23_;
    bool L1_Mu5_EG23er2p5_;
    TBranch *b_L1_Mu5_EG23er2p5_;
    bool loaded_L1_Mu5_EG23er2p5_;
    bool L1_Mu5_IsoEG18_;
    TBranch *b_L1_Mu5_IsoEG18_;
    bool loaded_L1_Mu5_IsoEG18_;
    bool L1_Mu5_IsoEG20_;
    TBranch *b_L1_Mu5_IsoEG20_;
    bool loaded_L1_Mu5_IsoEG20_;
    bool L1_Mu5_LooseIsoEG20er2p5_;
    TBranch *b_L1_Mu5_LooseIsoEG20er2p5_;
    bool loaded_L1_Mu5_LooseIsoEG20er2p5_;
    bool L1_Mu6_DoubleEG10_;
    TBranch *b_L1_Mu6_DoubleEG10_;
    bool loaded_L1_Mu6_DoubleEG10_;
    bool L1_Mu6_DoubleEG10er2p5_;
    TBranch *b_L1_Mu6_DoubleEG10er2p5_;
    bool loaded_L1_Mu6_DoubleEG10er2p5_;
    bool L1_Mu6_DoubleEG12er2p5_;
    TBranch *b_L1_Mu6_DoubleEG12er2p5_;
    bool loaded_L1_Mu6_DoubleEG12er2p5_;
    bool L1_Mu6_DoubleEG15er2p5_;
    TBranch *b_L1_Mu6_DoubleEG15er2p5_;
    bool loaded_L1_Mu6_DoubleEG15er2p5_;
    bool L1_Mu6_DoubleEG17_;
    TBranch *b_L1_Mu6_DoubleEG17_;
    bool loaded_L1_Mu6_DoubleEG17_;
    bool L1_Mu6_DoubleEG17er2p5_;
    TBranch *b_L1_Mu6_DoubleEG17er2p5_;
    bool loaded_L1_Mu6_DoubleEG17er2p5_;
    bool L1_Mu6_HTT200_;
    TBranch *b_L1_Mu6_HTT200_;
    bool loaded_L1_Mu6_HTT200_;
    bool L1_Mu6_HTT240er_;
    TBranch *b_L1_Mu6_HTT240er_;
    bool loaded_L1_Mu6_HTT240er_;
    bool L1_Mu6_HTT250er_;
    TBranch *b_L1_Mu6_HTT250er_;
    bool loaded_L1_Mu6_HTT250er_;
    bool L1_Mu7_EG23er2p5_;
    TBranch *b_L1_Mu7_EG23er2p5_;
    bool loaded_L1_Mu7_EG23er2p5_;
    bool L1_Mu7_LooseIsoEG20er2p5_;
    TBranch *b_L1_Mu7_LooseIsoEG20er2p5_;
    bool loaded_L1_Mu7_LooseIsoEG20er2p5_;
    bool L1_Mu7_LooseIsoEG23er2p5_;
    TBranch *b_L1_Mu7_LooseIsoEG23er2p5_;
    bool loaded_L1_Mu7_LooseIsoEG23er2p5_;
    bool L1_Mu8_HTT150_;
    TBranch *b_L1_Mu8_HTT150_;
    bool loaded_L1_Mu8_HTT150_;
    bool L1_NotBptxOR_;
    TBranch *b_L1_NotBptxOR_;
    bool loaded_L1_NotBptxOR_;
    bool L1_QuadJet36er2p5_IsoTau52er2p1_;
    TBranch *b_L1_QuadJet36er2p5_IsoTau52er2p1_;
    bool loaded_L1_QuadJet36er2p5_IsoTau52er2p1_;
    bool L1_QuadJet60er2p5_;
    TBranch *b_L1_QuadJet60er2p5_;
    bool loaded_L1_QuadJet60er2p5_;
    bool L1_QuadJetC36_Tau52_;
    TBranch *b_L1_QuadJetC36_Tau52_;
    bool loaded_L1_QuadJetC36_Tau52_;
    bool L1_QuadJetC40_;
    TBranch *b_L1_QuadJetC40_;
    bool loaded_L1_QuadJetC40_;
    bool L1_QuadJetC50_;
    TBranch *b_L1_QuadJetC50_;
    bool loaded_L1_QuadJetC50_;
    bool L1_QuadJetC60_;
    TBranch *b_L1_QuadJetC60_;
    bool loaded_L1_QuadJetC60_;
    bool L1_QuadJet_95_75_65_20_DoubleJet_75_65_er2p5_Jet20_FWD3p0_;
    TBranch *b_L1_QuadJet_95_75_65_20_DoubleJet_75_65_er2p5_Jet20_FWD3p0_;
    bool loaded_L1_QuadJet_95_75_65_20_DoubleJet_75_65_er2p5_Jet20_FWD3p0_;
    bool L1_QuadMu0_;
    TBranch *b_L1_QuadMu0_;
    bool loaded_L1_QuadMu0_;
    bool L1_QuadMu0_OQ_;
    TBranch *b_L1_QuadMu0_OQ_;
    bool loaded_L1_QuadMu0_OQ_;
    bool L1_QuadMu0_SQ_;
    TBranch *b_L1_QuadMu0_SQ_;
    bool loaded_L1_QuadMu0_SQ_;
    bool L1_SecondBunchInTrain_;
    TBranch *b_L1_SecondBunchInTrain_;
    bool loaded_L1_SecondBunchInTrain_;
    bool L1_SecondLastBunchInTrain_;
    TBranch *b_L1_SecondLastBunchInTrain_;
    bool loaded_L1_SecondLastBunchInTrain_;
    bool L1_SingleEG10_;
    TBranch *b_L1_SingleEG10_;
    bool loaded_L1_SingleEG10_;
    bool L1_SingleEG10er2p5_;
    TBranch *b_L1_SingleEG10er2p5_;
    bool loaded_L1_SingleEG10er2p5_;
    bool L1_SingleEG15_;
    TBranch *b_L1_SingleEG15_;
    bool loaded_L1_SingleEG15_;
    bool L1_SingleEG15er2p5_;
    TBranch *b_L1_SingleEG15er2p5_;
    bool loaded_L1_SingleEG15er2p5_;
    bool L1_SingleEG18_;
    TBranch *b_L1_SingleEG18_;
    bool loaded_L1_SingleEG18_;
    bool L1_SingleEG24_;
    TBranch *b_L1_SingleEG24_;
    bool loaded_L1_SingleEG24_;
    bool L1_SingleEG26_;
    TBranch *b_L1_SingleEG26_;
    bool loaded_L1_SingleEG26_;
    bool L1_SingleEG26er2p5_;
    TBranch *b_L1_SingleEG26er2p5_;
    bool loaded_L1_SingleEG26er2p5_;
    bool L1_SingleEG28_;
    TBranch *b_L1_SingleEG28_;
    bool loaded_L1_SingleEG28_;
    bool L1_SingleEG2_BptxAND_;
    TBranch *b_L1_SingleEG2_BptxAND_;
    bool loaded_L1_SingleEG2_BptxAND_;
    bool L1_SingleEG30_;
    TBranch *b_L1_SingleEG30_;
    bool loaded_L1_SingleEG30_;
    bool L1_SingleEG32_;
    TBranch *b_L1_SingleEG32_;
    bool loaded_L1_SingleEG32_;
    bool L1_SingleEG34_;
    TBranch *b_L1_SingleEG34_;
    bool loaded_L1_SingleEG34_;
    bool L1_SingleEG34er2p5_;
    TBranch *b_L1_SingleEG34er2p5_;
    bool loaded_L1_SingleEG34er2p5_;
    bool L1_SingleEG36_;
    TBranch *b_L1_SingleEG36_;
    bool loaded_L1_SingleEG36_;
    bool L1_SingleEG36er2p5_;
    TBranch *b_L1_SingleEG36er2p5_;
    bool loaded_L1_SingleEG36er2p5_;
    bool L1_SingleEG38_;
    TBranch *b_L1_SingleEG38_;
    bool loaded_L1_SingleEG38_;
    bool L1_SingleEG38er2p5_;
    TBranch *b_L1_SingleEG38er2p5_;
    bool loaded_L1_SingleEG38er2p5_;
    bool L1_SingleEG40_;
    TBranch *b_L1_SingleEG40_;
    bool loaded_L1_SingleEG40_;
    bool L1_SingleEG40er2p5_;
    TBranch *b_L1_SingleEG40er2p5_;
    bool loaded_L1_SingleEG40er2p5_;
    bool L1_SingleEG42er2p5_;
    TBranch *b_L1_SingleEG42er2p5_;
    bool loaded_L1_SingleEG42er2p5_;
    bool L1_SingleEG45_;
    TBranch *b_L1_SingleEG45_;
    bool loaded_L1_SingleEG45_;
    bool L1_SingleEG45er2p5_;
    TBranch *b_L1_SingleEG45er2p5_;
    bool loaded_L1_SingleEG45er2p5_;
    bool L1_SingleEG5_;
    TBranch *b_L1_SingleEG5_;
    bool loaded_L1_SingleEG5_;
    bool L1_SingleEG50_;
    TBranch *b_L1_SingleEG50_;
    bool loaded_L1_SingleEG50_;
    bool L1_SingleEG60_;
    TBranch *b_L1_SingleEG60_;
    bool loaded_L1_SingleEG60_;
    bool L1_SingleEG8er2p5_;
    TBranch *b_L1_SingleEG8er2p5_;
    bool loaded_L1_SingleEG8er2p5_;
    bool L1_SingleIsoEG18_;
    TBranch *b_L1_SingleIsoEG18_;
    bool loaded_L1_SingleIsoEG18_;
    bool L1_SingleIsoEG18er_;
    TBranch *b_L1_SingleIsoEG18er_;
    bool loaded_L1_SingleIsoEG18er_;
    bool L1_SingleIsoEG20_;
    TBranch *b_L1_SingleIsoEG20_;
    bool loaded_L1_SingleIsoEG20_;
    bool L1_SingleIsoEG20er_;
    TBranch *b_L1_SingleIsoEG20er_;
    bool loaded_L1_SingleIsoEG20er_;
    bool L1_SingleIsoEG22_;
    TBranch *b_L1_SingleIsoEG22_;
    bool loaded_L1_SingleIsoEG22_;
    bool L1_SingleIsoEG22er_;
    TBranch *b_L1_SingleIsoEG22er_;
    bool loaded_L1_SingleIsoEG22er_;
    bool L1_SingleIsoEG24_;
    TBranch *b_L1_SingleIsoEG24_;
    bool loaded_L1_SingleIsoEG24_;
    bool L1_SingleIsoEG24er_;
    TBranch *b_L1_SingleIsoEG24er_;
    bool loaded_L1_SingleIsoEG24er_;
    bool L1_SingleIsoEG24er1p5_;
    TBranch *b_L1_SingleIsoEG24er1p5_;
    bool loaded_L1_SingleIsoEG24er1p5_;
    bool L1_SingleIsoEG24er2p1_;
    TBranch *b_L1_SingleIsoEG24er2p1_;
    bool loaded_L1_SingleIsoEG24er2p1_;
    bool L1_SingleIsoEG26_;
    TBranch *b_L1_SingleIsoEG26_;
    bool loaded_L1_SingleIsoEG26_;
    bool L1_SingleIsoEG26er_;
    TBranch *b_L1_SingleIsoEG26er_;
    bool loaded_L1_SingleIsoEG26er_;
    bool L1_SingleIsoEG26er1p5_;
    TBranch *b_L1_SingleIsoEG26er1p5_;
    bool loaded_L1_SingleIsoEG26er1p5_;
    bool L1_SingleIsoEG26er2p1_;
    TBranch *b_L1_SingleIsoEG26er2p1_;
    bool loaded_L1_SingleIsoEG26er2p1_;
    bool L1_SingleIsoEG26er2p5_;
    TBranch *b_L1_SingleIsoEG26er2p5_;
    bool loaded_L1_SingleIsoEG26er2p5_;
    bool L1_SingleIsoEG28_;
    TBranch *b_L1_SingleIsoEG28_;
    bool loaded_L1_SingleIsoEG28_;
    bool L1_SingleIsoEG28er_;
    TBranch *b_L1_SingleIsoEG28er_;
    bool loaded_L1_SingleIsoEG28er_;
    bool L1_SingleIsoEG28er1p5_;
    TBranch *b_L1_SingleIsoEG28er1p5_;
    bool loaded_L1_SingleIsoEG28er1p5_;
    bool L1_SingleIsoEG28er2p1_;
    TBranch *b_L1_SingleIsoEG28er2p1_;
    bool loaded_L1_SingleIsoEG28er2p1_;
    bool L1_SingleIsoEG28er2p5_;
    TBranch *b_L1_SingleIsoEG28er2p5_;
    bool loaded_L1_SingleIsoEG28er2p5_;
    bool L1_SingleIsoEG30_;
    TBranch *b_L1_SingleIsoEG30_;
    bool loaded_L1_SingleIsoEG30_;
    bool L1_SingleIsoEG30er_;
    TBranch *b_L1_SingleIsoEG30er_;
    bool loaded_L1_SingleIsoEG30er_;
    bool L1_SingleIsoEG30er2p1_;
    TBranch *b_L1_SingleIsoEG30er2p1_;
    bool loaded_L1_SingleIsoEG30er2p1_;
    bool L1_SingleIsoEG30er2p5_;
    TBranch *b_L1_SingleIsoEG30er2p5_;
    bool loaded_L1_SingleIsoEG30er2p5_;
    bool L1_SingleIsoEG32_;
    TBranch *b_L1_SingleIsoEG32_;
    bool loaded_L1_SingleIsoEG32_;
    bool L1_SingleIsoEG32er_;
    TBranch *b_L1_SingleIsoEG32er_;
    bool loaded_L1_SingleIsoEG32er_;
    bool L1_SingleIsoEG32er2p1_;
    TBranch *b_L1_SingleIsoEG32er2p1_;
    bool loaded_L1_SingleIsoEG32er2p1_;
    bool L1_SingleIsoEG32er2p5_;
    TBranch *b_L1_SingleIsoEG32er2p5_;
    bool loaded_L1_SingleIsoEG32er2p5_;
    bool L1_SingleIsoEG34_;
    TBranch *b_L1_SingleIsoEG34_;
    bool loaded_L1_SingleIsoEG34_;
    bool L1_SingleIsoEG34er_;
    TBranch *b_L1_SingleIsoEG34er_;
    bool loaded_L1_SingleIsoEG34er_;
    bool L1_SingleIsoEG34er2p5_;
    TBranch *b_L1_SingleIsoEG34er2p5_;
    bool loaded_L1_SingleIsoEG34er2p5_;
    bool L1_SingleIsoEG36_;
    TBranch *b_L1_SingleIsoEG36_;
    bool loaded_L1_SingleIsoEG36_;
    bool L1_SingleJet10erHE_;
    TBranch *b_L1_SingleJet10erHE_;
    bool loaded_L1_SingleJet10erHE_;
    bool L1_SingleJet120_;
    TBranch *b_L1_SingleJet120_;
    bool loaded_L1_SingleJet120_;
    bool L1_SingleJet120_FWD3p0_;
    TBranch *b_L1_SingleJet120_FWD3p0_;
    bool loaded_L1_SingleJet120_FWD3p0_;
    bool L1_SingleJet120er2p5_;
    TBranch *b_L1_SingleJet120er2p5_;
    bool loaded_L1_SingleJet120er2p5_;
    bool L1_SingleJet12_BptxAND_;
    TBranch *b_L1_SingleJet12_BptxAND_;
    bool loaded_L1_SingleJet12_BptxAND_;
    bool L1_SingleJet12erHE_;
    TBranch *b_L1_SingleJet12erHE_;
    bool loaded_L1_SingleJet12erHE_;
    bool L1_SingleJet140_;
    TBranch *b_L1_SingleJet140_;
    bool loaded_L1_SingleJet140_;
    bool L1_SingleJet140er2p5_;
    TBranch *b_L1_SingleJet140er2p5_;
    bool loaded_L1_SingleJet140er2p5_;
    bool L1_SingleJet140er2p5_ETMHF80_;
    TBranch *b_L1_SingleJet140er2p5_ETMHF80_;
    bool loaded_L1_SingleJet140er2p5_ETMHF80_;
    bool L1_SingleJet140er2p5_ETMHF90_;
    TBranch *b_L1_SingleJet140er2p5_ETMHF90_;
    bool loaded_L1_SingleJet140er2p5_ETMHF90_;
    bool L1_SingleJet150_;
    TBranch *b_L1_SingleJet150_;
    bool loaded_L1_SingleJet150_;
    bool L1_SingleJet16_;
    TBranch *b_L1_SingleJet16_;
    bool loaded_L1_SingleJet16_;
    bool L1_SingleJet160_;
    TBranch *b_L1_SingleJet160_;
    bool loaded_L1_SingleJet160_;
    bool L1_SingleJet160er2p5_;
    TBranch *b_L1_SingleJet160er2p5_;
    bool loaded_L1_SingleJet160er2p5_;
    bool L1_SingleJet170_;
    TBranch *b_L1_SingleJet170_;
    bool loaded_L1_SingleJet170_;
    bool L1_SingleJet180_;
    TBranch *b_L1_SingleJet180_;
    bool loaded_L1_SingleJet180_;
    bool L1_SingleJet180er2p5_;
    TBranch *b_L1_SingleJet180er2p5_;
    bool loaded_L1_SingleJet180er2p5_;
    bool L1_SingleJet20_;
    TBranch *b_L1_SingleJet20_;
    bool loaded_L1_SingleJet20_;
    bool L1_SingleJet200_;
    TBranch *b_L1_SingleJet200_;
    bool loaded_L1_SingleJet200_;
    bool L1_SingleJet20er2p5_NotBptxOR_;
    TBranch *b_L1_SingleJet20er2p5_NotBptxOR_;
    bool loaded_L1_SingleJet20er2p5_NotBptxOR_;
    bool L1_SingleJet20er2p5_NotBptxOR_3BX_;
    TBranch *b_L1_SingleJet20er2p5_NotBptxOR_3BX_;
    bool loaded_L1_SingleJet20er2p5_NotBptxOR_3BX_;
    bool L1_SingleJet35_;
    TBranch *b_L1_SingleJet35_;
    bool loaded_L1_SingleJet35_;
    bool L1_SingleJet35_FWD3p0_;
    TBranch *b_L1_SingleJet35_FWD3p0_;
    bool loaded_L1_SingleJet35_FWD3p0_;
    bool L1_SingleJet35er2p5_;
    TBranch *b_L1_SingleJet35er2p5_;
    bool loaded_L1_SingleJet35er2p5_;
    bool L1_SingleJet43er2p5_NotBptxOR_3BX_;
    TBranch *b_L1_SingleJet43er2p5_NotBptxOR_3BX_;
    bool loaded_L1_SingleJet43er2p5_NotBptxOR_3BX_;
    bool L1_SingleJet46er2p5_NotBptxOR_3BX_;
    TBranch *b_L1_SingleJet46er2p5_NotBptxOR_3BX_;
    bool loaded_L1_SingleJet46er2p5_NotBptxOR_3BX_;
    bool L1_SingleJet60_;
    TBranch *b_L1_SingleJet60_;
    bool loaded_L1_SingleJet60_;
    bool L1_SingleJet60_FWD3p0_;
    TBranch *b_L1_SingleJet60_FWD3p0_;
    bool loaded_L1_SingleJet60_FWD3p0_;
    bool L1_SingleJet60er2p5_;
    TBranch *b_L1_SingleJet60er2p5_;
    bool loaded_L1_SingleJet60er2p5_;
    bool L1_SingleJet8_BptxAND_;
    TBranch *b_L1_SingleJet8_BptxAND_;
    bool loaded_L1_SingleJet8_BptxAND_;
    bool L1_SingleJet8erHE_;
    TBranch *b_L1_SingleJet8erHE_;
    bool loaded_L1_SingleJet8erHE_;
    bool L1_SingleJet90_;
    TBranch *b_L1_SingleJet90_;
    bool loaded_L1_SingleJet90_;
    bool L1_SingleJet90_FWD3p0_;
    TBranch *b_L1_SingleJet90_FWD3p0_;
    bool loaded_L1_SingleJet90_FWD3p0_;
    bool L1_SingleJet90er2p5_;
    TBranch *b_L1_SingleJet90er2p5_;
    bool loaded_L1_SingleJet90er2p5_;
    bool L1_SingleJetC20_NotBptxOR_;
    TBranch *b_L1_SingleJetC20_NotBptxOR_;
    bool loaded_L1_SingleJetC20_NotBptxOR_;
    bool L1_SingleJetC20_NotBptxOR_3BX_;
    TBranch *b_L1_SingleJetC20_NotBptxOR_3BX_;
    bool loaded_L1_SingleJetC20_NotBptxOR_3BX_;
    bool L1_SingleJetC40_NotBptxOR_3BX_;
    TBranch *b_L1_SingleJetC40_NotBptxOR_3BX_;
    bool loaded_L1_SingleJetC40_NotBptxOR_3BX_;
    bool L1_SingleJetC40_NotBptxOR_5BX_;
    TBranch *b_L1_SingleJetC40_NotBptxOR_5BX_;
    bool loaded_L1_SingleJetC40_NotBptxOR_5BX_;
    bool L1_SingleLooseIsoEG28er1p5_;
    TBranch *b_L1_SingleLooseIsoEG28er1p5_;
    bool loaded_L1_SingleLooseIsoEG28er1p5_;
    bool L1_SingleLooseIsoEG30er1p5_;
    TBranch *b_L1_SingleLooseIsoEG30er1p5_;
    bool loaded_L1_SingleLooseIsoEG30er1p5_;
    bool L1_SingleMu0_BMTF_;
    TBranch *b_L1_SingleMu0_BMTF_;
    bool loaded_L1_SingleMu0_BMTF_;
    bool L1_SingleMu0_DQ_;
    TBranch *b_L1_SingleMu0_DQ_;
    bool loaded_L1_SingleMu0_DQ_;
    bool L1_SingleMu0_EMTF_;
    TBranch *b_L1_SingleMu0_EMTF_;
    bool loaded_L1_SingleMu0_EMTF_;
    bool L1_SingleMu0_OMTF_;
    TBranch *b_L1_SingleMu0_OMTF_;
    bool loaded_L1_SingleMu0_OMTF_;
    bool L1_SingleMu10_LowQ_;
    TBranch *b_L1_SingleMu10_LowQ_;
    bool loaded_L1_SingleMu10_LowQ_;
    bool L1_SingleMu10er1p5_;
    TBranch *b_L1_SingleMu10er1p5_;
    bool loaded_L1_SingleMu10er1p5_;
    bool L1_SingleMu12_;
    TBranch *b_L1_SingleMu12_;
    bool loaded_L1_SingleMu12_;
    bool L1_SingleMu12_DQ_BMTF_;
    TBranch *b_L1_SingleMu12_DQ_BMTF_;
    bool loaded_L1_SingleMu12_DQ_BMTF_;
    bool L1_SingleMu12_DQ_EMTF_;
    TBranch *b_L1_SingleMu12_DQ_EMTF_;
    bool loaded_L1_SingleMu12_DQ_EMTF_;
    bool L1_SingleMu12_DQ_OMTF_;
    TBranch *b_L1_SingleMu12_DQ_OMTF_;
    bool loaded_L1_SingleMu12_DQ_OMTF_;
    bool L1_SingleMu12er1p5_;
    TBranch *b_L1_SingleMu12er1p5_;
    bool loaded_L1_SingleMu12er1p5_;
    bool L1_SingleMu14_;
    TBranch *b_L1_SingleMu14_;
    bool loaded_L1_SingleMu14_;
    bool L1_SingleMu14er_;
    TBranch *b_L1_SingleMu14er_;
    bool loaded_L1_SingleMu14er_;
    bool L1_SingleMu14er1p5_;
    TBranch *b_L1_SingleMu14er1p5_;
    bool loaded_L1_SingleMu14er1p5_;
    bool L1_SingleMu15_DQ_;
    TBranch *b_L1_SingleMu15_DQ_;
    bool loaded_L1_SingleMu15_DQ_;
    bool L1_SingleMu16_;
    TBranch *b_L1_SingleMu16_;
    bool loaded_L1_SingleMu16_;
    bool L1_SingleMu16er_;
    TBranch *b_L1_SingleMu16er_;
    bool loaded_L1_SingleMu16er_;
    bool L1_SingleMu16er1p5_;
    TBranch *b_L1_SingleMu16er1p5_;
    bool loaded_L1_SingleMu16er1p5_;
    bool L1_SingleMu18_;
    TBranch *b_L1_SingleMu18_;
    bool loaded_L1_SingleMu18_;
    bool L1_SingleMu18er_;
    TBranch *b_L1_SingleMu18er_;
    bool loaded_L1_SingleMu18er_;
    bool L1_SingleMu18er1p5_;
    TBranch *b_L1_SingleMu18er1p5_;
    bool loaded_L1_SingleMu18er1p5_;
    bool L1_SingleMu20_;
    TBranch *b_L1_SingleMu20_;
    bool loaded_L1_SingleMu20_;
    bool L1_SingleMu20er_;
    TBranch *b_L1_SingleMu20er_;
    bool loaded_L1_SingleMu20er_;
    bool L1_SingleMu22_;
    TBranch *b_L1_SingleMu22_;
    bool loaded_L1_SingleMu22_;
    bool L1_SingleMu22_BMTF_;
    TBranch *b_L1_SingleMu22_BMTF_;
    bool loaded_L1_SingleMu22_BMTF_;
    bool L1_SingleMu22_EMTF_;
    TBranch *b_L1_SingleMu22_EMTF_;
    bool loaded_L1_SingleMu22_EMTF_;
    bool L1_SingleMu22_OMTF_;
    TBranch *b_L1_SingleMu22_OMTF_;
    bool loaded_L1_SingleMu22_OMTF_;
    bool L1_SingleMu22er_;
    TBranch *b_L1_SingleMu22er_;
    bool loaded_L1_SingleMu22er_;
    bool L1_SingleMu25_;
    TBranch *b_L1_SingleMu25_;
    bool loaded_L1_SingleMu25_;
    bool L1_SingleMu25er_;
    TBranch *b_L1_SingleMu25er_;
    bool loaded_L1_SingleMu25er_;
    bool L1_SingleMu3_;
    TBranch *b_L1_SingleMu3_;
    bool loaded_L1_SingleMu3_;
    bool L1_SingleMu30_;
    TBranch *b_L1_SingleMu30_;
    bool loaded_L1_SingleMu30_;
    bool L1_SingleMu30er_;
    TBranch *b_L1_SingleMu30er_;
    bool loaded_L1_SingleMu30er_;
    bool L1_SingleMu5_;
    TBranch *b_L1_SingleMu5_;
    bool loaded_L1_SingleMu5_;
    bool L1_SingleMu6er1p5_;
    TBranch *b_L1_SingleMu6er1p5_;
    bool loaded_L1_SingleMu6er1p5_;
    bool L1_SingleMu7_;
    TBranch *b_L1_SingleMu7_;
    bool loaded_L1_SingleMu7_;
    bool L1_SingleMu7_DQ_;
    TBranch *b_L1_SingleMu7_DQ_;
    bool loaded_L1_SingleMu7_DQ_;
    bool L1_SingleMu7er1p5_;
    TBranch *b_L1_SingleMu7er1p5_;
    bool loaded_L1_SingleMu7er1p5_;
    bool L1_SingleMu8er1p5_;
    TBranch *b_L1_SingleMu8er1p5_;
    bool loaded_L1_SingleMu8er1p5_;
    bool L1_SingleMu9er1p5_;
    TBranch *b_L1_SingleMu9er1p5_;
    bool loaded_L1_SingleMu9er1p5_;
    bool L1_SingleMuCosmics_;
    TBranch *b_L1_SingleMuCosmics_;
    bool loaded_L1_SingleMuCosmics_;
    bool L1_SingleMuCosmics_BMTF_;
    TBranch *b_L1_SingleMuCosmics_BMTF_;
    bool loaded_L1_SingleMuCosmics_BMTF_;
    bool L1_SingleMuCosmics_EMTF_;
    TBranch *b_L1_SingleMuCosmics_EMTF_;
    bool loaded_L1_SingleMuCosmics_EMTF_;
    bool L1_SingleMuCosmics_OMTF_;
    TBranch *b_L1_SingleMuCosmics_OMTF_;
    bool loaded_L1_SingleMuCosmics_OMTF_;
    bool L1_SingleMuOpen_;
    TBranch *b_L1_SingleMuOpen_;
    bool loaded_L1_SingleMuOpen_;
    bool L1_SingleMuOpen_NotBptxOR_;
    TBranch *b_L1_SingleMuOpen_NotBptxOR_;
    bool loaded_L1_SingleMuOpen_NotBptxOR_;
    bool L1_SingleMuOpen_NotBptxOR_3BX_;
    TBranch *b_L1_SingleMuOpen_NotBptxOR_3BX_;
    bool loaded_L1_SingleMuOpen_NotBptxOR_3BX_;
    bool L1_SingleMuOpen_er1p1_NotBptxOR_3BX_;
    TBranch *b_L1_SingleMuOpen_er1p1_NotBptxOR_3BX_;
    bool loaded_L1_SingleMuOpen_er1p1_NotBptxOR_3BX_;
    bool L1_SingleMuOpen_er1p4_NotBptxOR_3BX_;
    TBranch *b_L1_SingleMuOpen_er1p4_NotBptxOR_3BX_;
    bool loaded_L1_SingleMuOpen_er1p4_NotBptxOR_3BX_;
    bool L1_SingleTau100er_;
    TBranch *b_L1_SingleTau100er_;
    bool loaded_L1_SingleTau100er_;
    bool L1_SingleTau120er_;
    TBranch *b_L1_SingleTau120er_;
    bool loaded_L1_SingleTau120er_;
    bool L1_SingleTau120er2p1_;
    TBranch *b_L1_SingleTau120er2p1_;
    bool loaded_L1_SingleTau120er2p1_;
    bool L1_SingleTau130er2p1_;
    TBranch *b_L1_SingleTau130er2p1_;
    bool loaded_L1_SingleTau130er2p1_;
    bool L1_SingleTau80er_;
    TBranch *b_L1_SingleTau80er_;
    bool loaded_L1_SingleTau80er_;
    bool L1_TOTEM_1_;
    TBranch *b_L1_TOTEM_1_;
    bool loaded_L1_TOTEM_1_;
    bool L1_TOTEM_2_;
    TBranch *b_L1_TOTEM_2_;
    bool loaded_L1_TOTEM_2_;
    bool L1_TOTEM_3_;
    TBranch *b_L1_TOTEM_3_;
    bool loaded_L1_TOTEM_3_;
    bool L1_TOTEM_4_;
    TBranch *b_L1_TOTEM_4_;
    bool loaded_L1_TOTEM_4_;
    bool L1_TripleEG16er2p5_;
    TBranch *b_L1_TripleEG16er2p5_;
    bool loaded_L1_TripleEG16er2p5_;
    bool L1_TripleEG_14_10_8_;
    TBranch *b_L1_TripleEG_14_10_8_;
    bool loaded_L1_TripleEG_14_10_8_;
    bool L1_TripleEG_16_12_8_er2p5_;
    TBranch *b_L1_TripleEG_16_12_8_er2p5_;
    bool loaded_L1_TripleEG_16_12_8_er2p5_;
    bool L1_TripleEG_16_15_8_er2p5_;
    TBranch *b_L1_TripleEG_16_15_8_er2p5_;
    bool loaded_L1_TripleEG_16_15_8_er2p5_;
    bool L1_TripleEG_18_17_8_;
    TBranch *b_L1_TripleEG_18_17_8_;
    bool loaded_L1_TripleEG_18_17_8_;
    bool L1_TripleEG_18_17_8_er2p5_;
    TBranch *b_L1_TripleEG_18_17_8_er2p5_;
    bool loaded_L1_TripleEG_18_17_8_er2p5_;
    bool L1_TripleEG_18_18_12_er2p5_;
    TBranch *b_L1_TripleEG_18_18_12_er2p5_;
    bool loaded_L1_TripleEG_18_18_12_er2p5_;
    bool L1_TripleJet_100_80_70_DoubleJet_80_70_er2p5_;
    TBranch *b_L1_TripleJet_100_80_70_DoubleJet_80_70_er2p5_;
    bool loaded_L1_TripleJet_100_80_70_DoubleJet_80_70_er2p5_;
    bool L1_TripleJet_105_85_75_DoubleJet_85_75_er2p5_;
    TBranch *b_L1_TripleJet_105_85_75_DoubleJet_85_75_er2p5_;
    bool loaded_L1_TripleJet_105_85_75_DoubleJet_85_75_er2p5_;
    bool L1_TripleJet_84_68_48_VBF_;
    TBranch *b_L1_TripleJet_84_68_48_VBF_;
    bool loaded_L1_TripleJet_84_68_48_VBF_;
    bool L1_TripleJet_88_72_56_VBF_;
    TBranch *b_L1_TripleJet_88_72_56_VBF_;
    bool loaded_L1_TripleJet_88_72_56_VBF_;
    bool L1_TripleJet_92_76_64_VBF_;
    TBranch *b_L1_TripleJet_92_76_64_VBF_;
    bool loaded_L1_TripleJet_92_76_64_VBF_;
    bool L1_TripleJet_95_75_65_DoubleJet_75_65_er2p5_;
    TBranch *b_L1_TripleJet_95_75_65_DoubleJet_75_65_er2p5_;
    bool loaded_L1_TripleJet_95_75_65_DoubleJet_75_65_er2p5_;
    bool L1_TripleMu0_;
    TBranch *b_L1_TripleMu0_;
    bool loaded_L1_TripleMu0_;
    bool L1_TripleMu0_OQ_;
    TBranch *b_L1_TripleMu0_OQ_;
    bool loaded_L1_TripleMu0_OQ_;
    bool L1_TripleMu0_SQ_;
    TBranch *b_L1_TripleMu0_SQ_;
    bool loaded_L1_TripleMu0_SQ_;
    bool L1_TripleMu3_;
    TBranch *b_L1_TripleMu3_;
    bool loaded_L1_TripleMu3_;
    bool L1_TripleMu3_SQ_;
    TBranch *b_L1_TripleMu3_SQ_;
    bool loaded_L1_TripleMu3_SQ_;
    bool L1_TripleMu_5SQ_3SQ_0OQ_;
    TBranch *b_L1_TripleMu_5SQ_3SQ_0OQ_;
    bool loaded_L1_TripleMu_5SQ_3SQ_0OQ_;
    bool L1_TripleMu_5SQ_3SQ_0OQ_DoubleMu_5_3_SQ_OS_Mass_Max9_;
    TBranch *b_L1_TripleMu_5SQ_3SQ_0OQ_DoubleMu_5_3_SQ_OS_Mass_Max9_;
    bool loaded_L1_TripleMu_5SQ_3SQ_0OQ_DoubleMu_5_3_SQ_OS_Mass_Max9_;
    bool L1_TripleMu_5SQ_3SQ_0_DoubleMu_5_3_SQ_OS_Mass_Max9_;
    TBranch *b_L1_TripleMu_5SQ_3SQ_0_DoubleMu_5_3_SQ_OS_Mass_Max9_;
    bool loaded_L1_TripleMu_5SQ_3SQ_0_DoubleMu_5_3_SQ_OS_Mass_Max9_;
    bool L1_TripleMu_5_0_0_;
    TBranch *b_L1_TripleMu_5_0_0_;
    bool loaded_L1_TripleMu_5_0_0_;
    bool L1_TripleMu_5_3_3_;
    TBranch *b_L1_TripleMu_5_3_3_;
    bool loaded_L1_TripleMu_5_3_3_;
    bool L1_TripleMu_5_3_3_SQ_;
    TBranch *b_L1_TripleMu_5_3_3_SQ_;
    bool loaded_L1_TripleMu_5_3_3_SQ_;
    bool L1_TripleMu_5_3p5_2p5_;
    TBranch *b_L1_TripleMu_5_3p5_2p5_;
    bool loaded_L1_TripleMu_5_3p5_2p5_;
    bool L1_TripleMu_5_3p5_2p5_DoubleMu_5_2p5_OS_Mass_5to17_;
    TBranch *b_L1_TripleMu_5_3p5_2p5_DoubleMu_5_2p5_OS_Mass_5to17_;
    bool loaded_L1_TripleMu_5_3p5_2p5_DoubleMu_5_2p5_OS_Mass_5to17_;
    bool L1_TripleMu_5_3p5_2p5_OQ_DoubleMu_5_2p5_OQ_OS_Mass_5to17_;
    TBranch *b_L1_TripleMu_5_3p5_2p5_OQ_DoubleMu_5_2p5_OQ_OS_Mass_5to17_;
    bool loaded_L1_TripleMu_5_3p5_2p5_OQ_DoubleMu_5_2p5_OQ_OS_Mass_5to17_;
    bool L1_TripleMu_5_4_2p5_DoubleMu_5_2p5_OS_Mass_5to17_;
    TBranch *b_L1_TripleMu_5_4_2p5_DoubleMu_5_2p5_OS_Mass_5to17_;
    bool loaded_L1_TripleMu_5_4_2p5_DoubleMu_5_2p5_OS_Mass_5to17_;
    bool L1_TripleMu_5_5_3_;
    TBranch *b_L1_TripleMu_5_5_3_;
    bool loaded_L1_TripleMu_5_5_3_;
    bool L1_UnpairedBunchBptxMinus_;
    TBranch *b_L1_UnpairedBunchBptxMinus_;
    bool loaded_L1_UnpairedBunchBptxMinus_;
    bool L1_UnpairedBunchBptxPlus_;
    TBranch *b_L1_UnpairedBunchBptxPlus_;
    bool loaded_L1_UnpairedBunchBptxPlus_;
    bool L1_ZeroBias_;
    TBranch *b_L1_ZeroBias_;
    bool loaded_L1_ZeroBias_;
    bool L1_ZeroBias_FirstCollidingBunch_;
    TBranch *b_L1_ZeroBias_FirstCollidingBunch_;
    bool loaded_L1_ZeroBias_FirstCollidingBunch_;
    bool L1_ZeroBias_copy_;
    TBranch *b_L1_ZeroBias_copy_;
    bool loaded_L1_ZeroBias_copy_;
    bool L1simulation_step_;
    TBranch *b_L1simulation_step_;
    bool loaded_L1simulation_step_;
    float LHEPart_eta_[NLHEPART_MAX];
    vector<float> v_LHEPart_eta_;
    TBranch *b_LHEPart_eta_;
    bool loaded_LHEPart_eta_;
    float LHEPart_incomingpz_[NLHEPART_MAX];
    vector<float> v_LHEPart_incomingpz_;
    TBranch *b_LHEPart_incomingpz_;
    bool loaded_LHEPart_incomingpz_;
    float LHEPart_mass_[NLHEPART_MAX];
    vector<float> v_LHEPart_mass_;
    TBranch *b_LHEPart_mass_;
    bool loaded_LHEPart_mass_;
    vector<LorentzVector> v_LHEPart_p4_;
    TBranch *b_LHEPart_p4_;
    bool loaded_LHEPart_p4_;
    int LHEPart_pdgId_[NLHEPART_MAX];
    vector<int> v_LHEPart_pdgId_;
    TBranch *b_LHEPart_pdgId_;
    bool loaded_LHEPart_pdgId_;
    float LHEPart_phi_[NLHEPART_MAX];
    vector<float> v_LHEPart_phi_;
    TBranch *b_LHEPart_phi_;
    bool loaded_LHEPart_phi_;
    float LHEPart_pt_[NLHEPART_MAX];
    vector<float> v_LHEPart_pt_;
    TBranch *b_LHEPart_pt_;
    bool loaded_LHEPart_pt_;
    int LHEPart_spin_[NLHEPART_MAX];
    vector<int> v_LHEPart_spin_;
    TBranch *b_LHEPart_spin_;
    bool loaded_LHEPart_spin_;
    int LHEPart_status_[NLHEPART_MAX];
    vector<int> v_LHEPart_status_;
    TBranch *b_LHEPart_status_;
    bool loaded_LHEPart_status_;
    float LHEPdfWeight_[NLHEPDFWEIGHT_MAX];
    vector<float> v_LHEPdfWeight_;
    TBranch *b_LHEPdfWeight_;
    bool loaded_LHEPdfWeight_;
    float LHEReweightingWeight_[NLHEREWEIGHTINGWEIGHT_MAX];
    vector<float> v_LHEReweightingWeight_;
    TBranch *b_LHEReweightingWeight_;
    bool loaded_LHEReweightingWeight_;
    float LHEScaleWeight_[NLHESCALEWEIGHT_MAX];
    vector<float> v_LHEScaleWeight_;
    TBranch *b_LHEScaleWeight_;
    bool loaded_LHEScaleWeight_;
    float LHEWeight_originalXWGTUP_;
    TBranch *b_LHEWeight_originalXWGTUP_;
    bool loaded_LHEWeight_originalXWGTUP_;
    float LHE_AlphaS_;
    TBranch *b_LHE_AlphaS_;
    bool loaded_LHE_AlphaS_;
    float LHE_HT_;
    TBranch *b_LHE_HT_;
    bool loaded_LHE_HT_;
    float LHE_HTIncoming_;
    TBranch *b_LHE_HTIncoming_;
    bool loaded_LHE_HTIncoming_;
    UChar_t LHE_Nb_;
    TBranch *b_LHE_Nb_;
    bool loaded_LHE_Nb_;
    UChar_t LHE_Nc_;
    TBranch *b_LHE_Nc_;
    bool loaded_LHE_Nc_;
    UChar_t LHE_Nglu_;
    TBranch *b_LHE_Nglu_;
    bool loaded_LHE_Nglu_;
    UChar_t LHE_Njets_;
    TBranch *b_LHE_Njets_;
    bool loaded_LHE_Njets_;
    UChar_t LHE_NpLO_;
    TBranch *b_LHE_NpLO_;
    bool loaded_LHE_NpLO_;
    UChar_t LHE_NpNLO_;
    TBranch *b_LHE_NpNLO_;
    bool loaded_LHE_NpNLO_;
    UChar_t LHE_Nuds_;
    TBranch *b_LHE_Nuds_;
    bool loaded_LHE_Nuds_;
    float LHE_Vpt_;
    TBranch *b_LHE_Vpt_;
    bool loaded_LHE_Vpt_;
    float MET_MetUnclustEnUpDeltaX_;
    TBranch *b_MET_MetUnclustEnUpDeltaX_;
    bool loaded_MET_MetUnclustEnUpDeltaX_;
    float MET_MetUnclustEnUpDeltaY_;
    TBranch *b_MET_MetUnclustEnUpDeltaY_;
    bool loaded_MET_MetUnclustEnUpDeltaY_;
    float MET_covXX_;
    TBranch *b_MET_covXX_;
    bool loaded_MET_covXX_;
    float MET_covXY_;
    TBranch *b_MET_covXY_;
    bool loaded_MET_covXY_;
    float MET_covYY_;
    TBranch *b_MET_covYY_;
    bool loaded_MET_covYY_;
    float MET_fiducialGenPhi_;
    TBranch *b_MET_fiducialGenPhi_;
    bool loaded_MET_fiducialGenPhi_;
    float MET_fiducialGenPt_;
    TBranch *b_MET_fiducialGenPt_;
    bool loaded_MET_fiducialGenPt_;
    float MET_phi_;
    TBranch *b_MET_phi_;
    bool loaded_MET_phi_;
    float MET_pt_;
    TBranch *b_MET_pt_;
    bool loaded_MET_pt_;
    float MET_significance_;
    TBranch *b_MET_significance_;
    bool loaded_MET_significance_;
    float MET_sumEt_;
    TBranch *b_MET_sumEt_;
    bool loaded_MET_sumEt_;
    float MET_sumPtUnclustered_;
    TBranch *b_MET_sumPtUnclustered_;
    bool loaded_MET_sumPtUnclustered_;
    int Muon_charge_[NMUON_MAX];
    vector<int> v_Muon_charge_;
    TBranch *b_Muon_charge_;
    bool loaded_Muon_charge_;
    UChar_t Muon_cleanmask_[NMUON_MAX];
    vector<UChar_t> v_Muon_cleanmask_;
    TBranch *b_Muon_cleanmask_;
    bool loaded_Muon_cleanmask_;
    float Muon_dxy_[NMUON_MAX];
    vector<float> v_Muon_dxy_;
    TBranch *b_Muon_dxy_;
    bool loaded_Muon_dxy_;
    float Muon_dxyErr_[NMUON_MAX];
    vector<float> v_Muon_dxyErr_;
    TBranch *b_Muon_dxyErr_;
    bool loaded_Muon_dxyErr_;
    float Muon_dxybs_[NMUON_MAX];
    vector<float> v_Muon_dxybs_;
    TBranch *b_Muon_dxybs_;
    bool loaded_Muon_dxybs_;
    float Muon_dz_[NMUON_MAX];
    vector<float> v_Muon_dz_;
    TBranch *b_Muon_dz_;
    bool loaded_Muon_dz_;
    float Muon_dzErr_[NMUON_MAX];
    vector<float> v_Muon_dzErr_;
    TBranch *b_Muon_dzErr_;
    bool loaded_Muon_dzErr_;
    float Muon_eta_[NMUON_MAX];
    vector<float> v_Muon_eta_;
    TBranch *b_Muon_eta_;
    bool loaded_Muon_eta_;
    int Muon_fsrPhotonIdx_[NMUON_MAX];
    vector<int> v_Muon_fsrPhotonIdx_;
    TBranch *b_Muon_fsrPhotonIdx_;
    bool loaded_Muon_fsrPhotonIdx_;
    UChar_t Muon_genPartFlav_[NMUON_MAX];
    vector<UChar_t> v_Muon_genPartFlav_;
    TBranch *b_Muon_genPartFlav_;
    bool loaded_Muon_genPartFlav_;
    int Muon_genPartIdx_[NMUON_MAX];
    vector<int> v_Muon_genPartIdx_;
    TBranch *b_Muon_genPartIdx_;
    bool loaded_Muon_genPartIdx_;
    UChar_t Muon_highPtId_[NMUON_MAX];
    vector<UChar_t> v_Muon_highPtId_;
    TBranch *b_Muon_highPtId_;
    bool loaded_Muon_highPtId_;
    bool Muon_highPurity_[NMUON_MAX];
    vector<bool> v_Muon_highPurity_;
    TBranch *b_Muon_highPurity_;
    bool loaded_Muon_highPurity_;
    bool Muon_inTimeMuon_[NMUON_MAX];
    vector<bool> v_Muon_inTimeMuon_;
    TBranch *b_Muon_inTimeMuon_;
    bool loaded_Muon_inTimeMuon_;
    float Muon_ip3d_[NMUON_MAX];
    vector<float> v_Muon_ip3d_;
    TBranch *b_Muon_ip3d_;
    bool loaded_Muon_ip3d_;
    bool Muon_isGlobal_[NMUON_MAX];
    vector<bool> v_Muon_isGlobal_;
    TBranch *b_Muon_isGlobal_;
    bool loaded_Muon_isGlobal_;
    bool Muon_isPFcand_[NMUON_MAX];
    vector<bool> v_Muon_isPFcand_;
    TBranch *b_Muon_isPFcand_;
    bool loaded_Muon_isPFcand_;
    bool Muon_isTracker_[NMUON_MAX];
    vector<bool> v_Muon_isTracker_;
    TBranch *b_Muon_isTracker_;
    bool loaded_Muon_isTracker_;
    int Muon_jetIdx_[NMUON_MAX];
    vector<int> v_Muon_jetIdx_;
    TBranch *b_Muon_jetIdx_;
    bool loaded_Muon_jetIdx_;
    float Muon_jetPtRelv2_[NMUON_MAX];
    vector<float> v_Muon_jetPtRelv2_;
    TBranch *b_Muon_jetPtRelv2_;
    bool loaded_Muon_jetPtRelv2_;
    float Muon_jetRelIso_[NMUON_MAX];
    vector<float> v_Muon_jetRelIso_;
    TBranch *b_Muon_jetRelIso_;
    bool loaded_Muon_jetRelIso_;
    bool Muon_looseId_[NMUON_MAX];
    vector<bool> v_Muon_looseId_;
    TBranch *b_Muon_looseId_;
    bool loaded_Muon_looseId_;
    float Muon_mass_[NMUON_MAX];
    vector<float> v_Muon_mass_;
    TBranch *b_Muon_mass_;
    bool loaded_Muon_mass_;
    bool Muon_mediumId_[NMUON_MAX];
    vector<bool> v_Muon_mediumId_;
    TBranch *b_Muon_mediumId_;
    bool loaded_Muon_mediumId_;
    bool Muon_mediumPromptId_[NMUON_MAX];
    vector<bool> v_Muon_mediumPromptId_;
    TBranch *b_Muon_mediumPromptId_;
    bool loaded_Muon_mediumPromptId_;
    UChar_t Muon_miniIsoId_[NMUON_MAX];
    vector<UChar_t> v_Muon_miniIsoId_;
    TBranch *b_Muon_miniIsoId_;
    bool loaded_Muon_miniIsoId_;
    float Muon_miniPFRelIso_all_[NMUON_MAX];
    vector<float> v_Muon_miniPFRelIso_all_;
    TBranch *b_Muon_miniPFRelIso_all_;
    bool loaded_Muon_miniPFRelIso_all_;
    float Muon_miniPFRelIso_chg_[NMUON_MAX];
    vector<float> v_Muon_miniPFRelIso_chg_;
    TBranch *b_Muon_miniPFRelIso_chg_;
    bool loaded_Muon_miniPFRelIso_chg_;
    UChar_t Muon_multiIsoId_[NMUON_MAX];
    vector<UChar_t> v_Muon_multiIsoId_;
    TBranch *b_Muon_multiIsoId_;
    bool loaded_Muon_multiIsoId_;
    UChar_t Muon_mvaId_[NMUON_MAX];
    vector<UChar_t> v_Muon_mvaId_;
    TBranch *b_Muon_mvaId_;
    bool loaded_Muon_mvaId_;
    float Muon_mvaLowPt_[NMUON_MAX];
    vector<float> v_Muon_mvaLowPt_;
    TBranch *b_Muon_mvaLowPt_;
    bool loaded_Muon_mvaLowPt_;
    float Muon_mvaTTH_[NMUON_MAX];
    vector<float> v_Muon_mvaTTH_;
    TBranch *b_Muon_mvaTTH_;
    bool loaded_Muon_mvaTTH_;
    int Muon_nStations_[NMUON_MAX];
    vector<int> v_Muon_nStations_;
    TBranch *b_Muon_nStations_;
    bool loaded_Muon_nStations_;
    int Muon_nTrackerLayers_[NMUON_MAX];
    vector<int> v_Muon_nTrackerLayers_;
    TBranch *b_Muon_nTrackerLayers_;
    bool loaded_Muon_nTrackerLayers_;
    vector<LorentzVector> v_Muon_p4_;
    TBranch *b_Muon_p4_;
    bool loaded_Muon_p4_;
    int Muon_pdgId_[NMUON_MAX];
    vector<int> v_Muon_pdgId_;
    TBranch *b_Muon_pdgId_;
    bool loaded_Muon_pdgId_;
    UChar_t Muon_pfIsoId_[NMUON_MAX];
    vector<UChar_t> v_Muon_pfIsoId_;
    TBranch *b_Muon_pfIsoId_;
    bool loaded_Muon_pfIsoId_;
    float Muon_pfRelIso03_all_[NMUON_MAX];
    vector<float> v_Muon_pfRelIso03_all_;
    TBranch *b_Muon_pfRelIso03_all_;
    bool loaded_Muon_pfRelIso03_all_;
    float Muon_pfRelIso03_chg_[NMUON_MAX];
    vector<float> v_Muon_pfRelIso03_chg_;
    TBranch *b_Muon_pfRelIso03_chg_;
    bool loaded_Muon_pfRelIso03_chg_;
    float Muon_pfRelIso04_all_[NMUON_MAX];
    vector<float> v_Muon_pfRelIso04_all_;
    TBranch *b_Muon_pfRelIso04_all_;
    bool loaded_Muon_pfRelIso04_all_;
    float Muon_phi_[NMUON_MAX];
    vector<float> v_Muon_phi_;
    TBranch *b_Muon_phi_;
    bool loaded_Muon_phi_;
    float Muon_pt_[NMUON_MAX];
    vector<float> v_Muon_pt_;
    TBranch *b_Muon_pt_;
    bool loaded_Muon_pt_;
    float Muon_ptErr_[NMUON_MAX];
    vector<float> v_Muon_ptErr_;
    TBranch *b_Muon_ptErr_;
    bool loaded_Muon_ptErr_;
    float Muon_segmentComp_[NMUON_MAX];
    vector<float> v_Muon_segmentComp_;
    TBranch *b_Muon_segmentComp_;
    bool loaded_Muon_segmentComp_;
    float Muon_sip3d_[NMUON_MAX];
    vector<float> v_Muon_sip3d_;
    TBranch *b_Muon_sip3d_;
    bool loaded_Muon_sip3d_;
    bool Muon_softId_[NMUON_MAX];
    vector<bool> v_Muon_softId_;
    TBranch *b_Muon_softId_;
    bool loaded_Muon_softId_;
    float Muon_softMva_[NMUON_MAX];
    vector<float> v_Muon_softMva_;
    TBranch *b_Muon_softMva_;
    bool loaded_Muon_softMva_;
    bool Muon_softMvaId_[NMUON_MAX];
    vector<bool> v_Muon_softMvaId_;
    TBranch *b_Muon_softMvaId_;
    bool loaded_Muon_softMvaId_;
    int Muon_tightCharge_[NMUON_MAX];
    vector<int> v_Muon_tightCharge_;
    TBranch *b_Muon_tightCharge_;
    bool loaded_Muon_tightCharge_;
    bool Muon_tightId_[NMUON_MAX];
    vector<bool> v_Muon_tightId_;
    TBranch *b_Muon_tightId_;
    bool loaded_Muon_tightId_;
    UChar_t Muon_tkIsoId_[NMUON_MAX];
    vector<UChar_t> v_Muon_tkIsoId_;
    TBranch *b_Muon_tkIsoId_;
    bool loaded_Muon_tkIsoId_;
    float Muon_tkRelIso_[NMUON_MAX];
    vector<float> v_Muon_tkRelIso_;
    TBranch *b_Muon_tkRelIso_;
    bool loaded_Muon_tkRelIso_;
    bool Muon_triggerIdLoose_[NMUON_MAX];
    vector<bool> v_Muon_triggerIdLoose_;
    TBranch *b_Muon_triggerIdLoose_;
    bool loaded_Muon_triggerIdLoose_;
    float Muon_tunepRelPt_[NMUON_MAX];
    vector<float> v_Muon_tunepRelPt_;
    TBranch *b_Muon_tunepRelPt_;
    bool loaded_Muon_tunepRelPt_;
    float OtherPV_z_[NOTHERPV_MAX];
    vector<float> v_OtherPV_z_;
    TBranch *b_OtherPV_z_;
    bool loaded_OtherPV_z_;
    float PSWeight_[NPSWEIGHT_MAX];
    vector<float> v_PSWeight_;
    TBranch *b_PSWeight_;
    bool loaded_PSWeight_;
    float PV_chi2_;
    TBranch *b_PV_chi2_;
    bool loaded_PV_chi2_;
    float PV_ndof_;
    TBranch *b_PV_ndof_;
    bool loaded_PV_ndof_;
    int PV_npvs_;
    TBranch *b_PV_npvs_;
    bool loaded_PV_npvs_;
    int PV_npvsGood_;
    TBranch *b_PV_npvsGood_;
    bool loaded_PV_npvsGood_;
    float PV_score_;
    TBranch *b_PV_score_;
    bool loaded_PV_score_;
    float PV_x_;
    TBranch *b_PV_x_;
    bool loaded_PV_x_;
    float PV_y_;
    TBranch *b_PV_y_;
    bool loaded_PV_y_;
    float PV_z_;
    TBranch *b_PV_z_;
    bool loaded_PV_z_;
    int Photon_charge_[NPHOTON_MAX];
    vector<int> v_Photon_charge_;
    TBranch *b_Photon_charge_;
    bool loaded_Photon_charge_;
    UChar_t Photon_cleanmask_[NPHOTON_MAX];
    vector<UChar_t> v_Photon_cleanmask_;
    TBranch *b_Photon_cleanmask_;
    bool loaded_Photon_cleanmask_;
    int Photon_cutBased_[NPHOTON_MAX];
    vector<int> v_Photon_cutBased_;
    TBranch *b_Photon_cutBased_;
    bool loaded_Photon_cutBased_;
    int Photon_cutBased_Fall17V1Bitmap_[NPHOTON_MAX];
    vector<int> v_Photon_cutBased_Fall17V1Bitmap_;
    TBranch *b_Photon_cutBased_Fall17V1Bitmap_;
    bool loaded_Photon_cutBased_Fall17V1Bitmap_;
    int Photon_cutBased_Spring16V2p2_[NPHOTON_MAX];
    vector<int> v_Photon_cutBased_Spring16V2p2_;
    TBranch *b_Photon_cutBased_Spring16V2p2_;
    bool loaded_Photon_cutBased_Spring16V2p2_;
    float Photon_eCorr_[NPHOTON_MAX];
    vector<float> v_Photon_eCorr_;
    TBranch *b_Photon_eCorr_;
    bool loaded_Photon_eCorr_;
    int Photon_electronIdx_[NPHOTON_MAX];
    vector<int> v_Photon_electronIdx_;
    TBranch *b_Photon_electronIdx_;
    bool loaded_Photon_electronIdx_;
    bool Photon_electronVeto_[NPHOTON_MAX];
    vector<bool> v_Photon_electronVeto_;
    TBranch *b_Photon_electronVeto_;
    bool loaded_Photon_electronVeto_;
    float Photon_energyErr_[NPHOTON_MAX];
    vector<float> v_Photon_energyErr_;
    TBranch *b_Photon_energyErr_;
    bool loaded_Photon_energyErr_;
    float Photon_eta_[NPHOTON_MAX];
    vector<float> v_Photon_eta_;
    TBranch *b_Photon_eta_;
    bool loaded_Photon_eta_;
    UChar_t Photon_genPartFlav_[NPHOTON_MAX];
    vector<UChar_t> v_Photon_genPartFlav_;
    TBranch *b_Photon_genPartFlav_;
    bool loaded_Photon_genPartFlav_;
    int Photon_genPartIdx_[NPHOTON_MAX];
    vector<int> v_Photon_genPartIdx_;
    TBranch *b_Photon_genPartIdx_;
    bool loaded_Photon_genPartIdx_;
    float Photon_hoe_[NPHOTON_MAX];
    vector<float> v_Photon_hoe_;
    TBranch *b_Photon_hoe_;
    bool loaded_Photon_hoe_;
    bool Photon_isScEtaEB_[NPHOTON_MAX];
    vector<bool> v_Photon_isScEtaEB_;
    TBranch *b_Photon_isScEtaEB_;
    bool loaded_Photon_isScEtaEB_;
    bool Photon_isScEtaEE_[NPHOTON_MAX];
    vector<bool> v_Photon_isScEtaEE_;
    TBranch *b_Photon_isScEtaEE_;
    bool loaded_Photon_isScEtaEE_;
    int Photon_jetIdx_[NPHOTON_MAX];
    vector<int> v_Photon_jetIdx_;
    TBranch *b_Photon_jetIdx_;
    bool loaded_Photon_jetIdx_;
    float Photon_mass_[NPHOTON_MAX];
    vector<float> v_Photon_mass_;
    TBranch *b_Photon_mass_;
    bool loaded_Photon_mass_;
    float Photon_mvaID_[NPHOTON_MAX];
    vector<float> v_Photon_mvaID_;
    TBranch *b_Photon_mvaID_;
    bool loaded_Photon_mvaID_;
    float Photon_mvaID_Fall17V1p1_[NPHOTON_MAX];
    vector<float> v_Photon_mvaID_Fall17V1p1_;
    TBranch *b_Photon_mvaID_Fall17V1p1_;
    bool loaded_Photon_mvaID_Fall17V1p1_;
    float Photon_mvaID_Spring16nonTrigV1_[NPHOTON_MAX];
    vector<float> v_Photon_mvaID_Spring16nonTrigV1_;
    TBranch *b_Photon_mvaID_Spring16nonTrigV1_;
    bool loaded_Photon_mvaID_Spring16nonTrigV1_;
    bool Photon_mvaID_WP80_[NPHOTON_MAX];
    vector<bool> v_Photon_mvaID_WP80_;
    TBranch *b_Photon_mvaID_WP80_;
    bool loaded_Photon_mvaID_WP80_;
    bool Photon_mvaID_WP90_[NPHOTON_MAX];
    vector<bool> v_Photon_mvaID_WP90_;
    TBranch *b_Photon_mvaID_WP90_;
    bool loaded_Photon_mvaID_WP90_;
    vector<LorentzVector> v_Photon_p4_;
    TBranch *b_Photon_p4_;
    bool loaded_Photon_p4_;
    int Photon_pdgId_[NPHOTON_MAX];
    vector<int> v_Photon_pdgId_;
    TBranch *b_Photon_pdgId_;
    bool loaded_Photon_pdgId_;
    float Photon_pfRelIso03_all_[NPHOTON_MAX];
    vector<float> v_Photon_pfRelIso03_all_;
    TBranch *b_Photon_pfRelIso03_all_;
    bool loaded_Photon_pfRelIso03_all_;
    float Photon_pfRelIso03_chg_[NPHOTON_MAX];
    vector<float> v_Photon_pfRelIso03_chg_;
    TBranch *b_Photon_pfRelIso03_chg_;
    bool loaded_Photon_pfRelIso03_chg_;
    float Photon_phi_[NPHOTON_MAX];
    vector<float> v_Photon_phi_;
    TBranch *b_Photon_phi_;
    bool loaded_Photon_phi_;
    bool Photon_pixelSeed_[NPHOTON_MAX];
    vector<bool> v_Photon_pixelSeed_;
    TBranch *b_Photon_pixelSeed_;
    bool loaded_Photon_pixelSeed_;
    float Photon_pt_[NPHOTON_MAX];
    vector<float> v_Photon_pt_;
    TBranch *b_Photon_pt_;
    bool loaded_Photon_pt_;
    float Photon_r9_[NPHOTON_MAX];
    vector<float> v_Photon_r9_;
    TBranch *b_Photon_r9_;
    bool loaded_Photon_r9_;
    UChar_t Photon_seedGain_[NPHOTON_MAX];
    vector<UChar_t> v_Photon_seedGain_;
    TBranch *b_Photon_seedGain_;
    bool loaded_Photon_seedGain_;
    float Photon_sieie_[NPHOTON_MAX];
    vector<float> v_Photon_sieie_;
    TBranch *b_Photon_sieie_;
    bool loaded_Photon_sieie_;
    int Photon_vidNestedWPBitmap_[NPHOTON_MAX];
    vector<int> v_Photon_vidNestedWPBitmap_;
    TBranch *b_Photon_vidNestedWPBitmap_;
    bool loaded_Photon_vidNestedWPBitmap_;
    int Photon_vidNestedWPBitmap_Spring16V2p2_[NPHOTON_MAX];
    vector<int> v_Photon_vidNestedWPBitmap_Spring16V2p2_;
    TBranch *b_Photon_vidNestedWPBitmap_Spring16V2p2_;
    bool loaded_Photon_vidNestedWPBitmap_Spring16V2p2_;
    float Pileup_gpudensity_;
    TBranch *b_Pileup_gpudensity_;
    bool loaded_Pileup_gpudensity_;
    int Pileup_nPU_;
    TBranch *b_Pileup_nPU_;
    bool loaded_Pileup_nPU_;
    float Pileup_nTrueInt_;
    TBranch *b_Pileup_nTrueInt_;
    bool loaded_Pileup_nTrueInt_;
    float Pileup_pudensity_;
    TBranch *b_Pileup_pudensity_;
    bool loaded_Pileup_pudensity_;
    int Pileup_sumEOOT_;
    TBranch *b_Pileup_sumEOOT_;
    bool loaded_Pileup_sumEOOT_;
    int Pileup_sumLOOT_;
    TBranch *b_Pileup_sumLOOT_;
    bool loaded_Pileup_sumLOOT_;
    float PuppiMET_phi_;
    TBranch *b_PuppiMET_phi_;
    bool loaded_PuppiMET_phi_;
    float PuppiMET_phiJERUp_;
    TBranch *b_PuppiMET_phiJERUp_;
    bool loaded_PuppiMET_phiJERUp_;
    float PuppiMET_phiJESUp_;
    TBranch *b_PuppiMET_phiJESUp_;
    bool loaded_PuppiMET_phiJESUp_;
    float PuppiMET_pt_;
    TBranch *b_PuppiMET_pt_;
    bool loaded_PuppiMET_pt_;
    float PuppiMET_ptJERUp_;
    TBranch *b_PuppiMET_ptJERUp_;
    bool loaded_PuppiMET_ptJERUp_;
    float PuppiMET_ptJESUp_;
    TBranch *b_PuppiMET_ptJESUp_;
    bool loaded_PuppiMET_ptJESUp_;
    float PuppiMET_sumEt_;
    TBranch *b_PuppiMET_sumEt_;
    bool loaded_PuppiMET_sumEt_;
    float RawMET_phi_;
    TBranch *b_RawMET_phi_;
    bool loaded_RawMET_phi_;
    float RawMET_pt_;
    TBranch *b_RawMET_pt_;
    bool loaded_RawMET_pt_;
    float RawMET_sumEt_;
    TBranch *b_RawMET_sumEt_;
    bool loaded_RawMET_sumEt_;
    float RawPuppiMET_phi_;
    TBranch *b_RawPuppiMET_phi_;
    bool loaded_RawPuppiMET_phi_;
    float RawPuppiMET_pt_;
    TBranch *b_RawPuppiMET_pt_;
    bool loaded_RawPuppiMET_pt_;
    float RawPuppiMET_sumEt_;
    TBranch *b_RawPuppiMET_sumEt_;
    bool loaded_RawPuppiMET_sumEt_;
    float SV_chi2_[NSV_MAX];
    vector<float> v_SV_chi2_;
    TBranch *b_SV_chi2_;
    bool loaded_SV_chi2_;
    float SV_dlen_[NSV_MAX];
    vector<float> v_SV_dlen_;
    TBranch *b_SV_dlen_;
    bool loaded_SV_dlen_;
    float SV_dlenSig_[NSV_MAX];
    vector<float> v_SV_dlenSig_;
    TBranch *b_SV_dlenSig_;
    bool loaded_SV_dlenSig_;
    float SV_dxy_[NSV_MAX];
    vector<float> v_SV_dxy_;
    TBranch *b_SV_dxy_;
    bool loaded_SV_dxy_;
    float SV_dxySig_[NSV_MAX];
    vector<float> v_SV_dxySig_;
    TBranch *b_SV_dxySig_;
    bool loaded_SV_dxySig_;
    float SV_eta_[NSV_MAX];
    vector<float> v_SV_eta_;
    TBranch *b_SV_eta_;
    bool loaded_SV_eta_;
    float SV_mass_[NSV_MAX];
    vector<float> v_SV_mass_;
    TBranch *b_SV_mass_;
    bool loaded_SV_mass_;
    float SV_ndof_[NSV_MAX];
    vector<float> v_SV_ndof_;
    TBranch *b_SV_ndof_;
    bool loaded_SV_ndof_;
    vector<LorentzVector> v_SV_p4_;
    TBranch *b_SV_p4_;
    bool loaded_SV_p4_;
    float SV_pAngle_[NSV_MAX];
    vector<float> v_SV_pAngle_;
    TBranch *b_SV_pAngle_;
    bool loaded_SV_pAngle_;
    float SV_phi_[NSV_MAX];
    vector<float> v_SV_phi_;
    TBranch *b_SV_phi_;
    bool loaded_SV_phi_;
    float SV_pt_[NSV_MAX];
    vector<float> v_SV_pt_;
    TBranch *b_SV_pt_;
    bool loaded_SV_pt_;
    float SV_x_[NSV_MAX];
    vector<float> v_SV_x_;
    TBranch *b_SV_x_;
    bool loaded_SV_x_;
    float SV_y_[NSV_MAX];
    vector<float> v_SV_y_;
    TBranch *b_SV_y_;
    bool loaded_SV_y_;
    float SV_z_[NSV_MAX];
    vector<float> v_SV_z_;
    TBranch *b_SV_z_;
    bool loaded_SV_z_;
    float SoftActivityJetHT_;
    TBranch *b_SoftActivityJetHT_;
    bool loaded_SoftActivityJetHT_;
    float SoftActivityJetHT10_;
    TBranch *b_SoftActivityJetHT10_;
    bool loaded_SoftActivityJetHT10_;
    float SoftActivityJetHT2_;
    TBranch *b_SoftActivityJetHT2_;
    bool loaded_SoftActivityJetHT2_;
    float SoftActivityJetHT5_;
    TBranch *b_SoftActivityJetHT5_;
    bool loaded_SoftActivityJetHT5_;
    int SoftActivityJetNjets10_;
    TBranch *b_SoftActivityJetNjets10_;
    bool loaded_SoftActivityJetNjets10_;
    int SoftActivityJetNjets2_;
    TBranch *b_SoftActivityJetNjets2_;
    bool loaded_SoftActivityJetNjets2_;
    int SoftActivityJetNjets5_;
    TBranch *b_SoftActivityJetNjets5_;
    bool loaded_SoftActivityJetNjets5_;
    float SoftActivityJet_eta_[NSOFTACTIVITYJET_MAX];
    vector<float> v_SoftActivityJet_eta_;
    TBranch *b_SoftActivityJet_eta_;
    bool loaded_SoftActivityJet_eta_;
    float SoftActivityJet_phi_[NSOFTACTIVITYJET_MAX];
    vector<float> v_SoftActivityJet_phi_;
    TBranch *b_SoftActivityJet_phi_;
    bool loaded_SoftActivityJet_phi_;
    float SoftActivityJet_pt_[NSOFTACTIVITYJET_MAX];
    vector<float> v_SoftActivityJet_pt_;
    TBranch *b_SoftActivityJet_pt_;
    bool loaded_SoftActivityJet_pt_;
    float SubGenJetAK8_eta_[NSUBGENJETAK8_MAX];
    vector<float> v_SubGenJetAK8_eta_;
    TBranch *b_SubGenJetAK8_eta_;
    bool loaded_SubGenJetAK8_eta_;
    float SubGenJetAK8_mass_[NSUBGENJETAK8_MAX];
    vector<float> v_SubGenJetAK8_mass_;
    TBranch *b_SubGenJetAK8_mass_;
    bool loaded_SubGenJetAK8_mass_;
    vector<LorentzVector> v_SubGenJetAK8_p4_;
    TBranch *b_SubGenJetAK8_p4_;
    bool loaded_SubGenJetAK8_p4_;
    float SubGenJetAK8_phi_[NSUBGENJETAK8_MAX];
    vector<float> v_SubGenJetAK8_phi_;
    TBranch *b_SubGenJetAK8_phi_;
    bool loaded_SubGenJetAK8_phi_;
    float SubGenJetAK8_pt_[NSUBGENJETAK8_MAX];
    vector<float> v_SubGenJetAK8_pt_;
    TBranch *b_SubGenJetAK8_pt_;
    bool loaded_SubGenJetAK8_pt_;
    float SubJet_btagCMVA_[NSUBJET_MAX];
    vector<float> v_SubJet_btagCMVA_;
    TBranch *b_SubJet_btagCMVA_;
    bool loaded_SubJet_btagCMVA_;
    float SubJet_btagCSVV2_[NSUBJET_MAX];
    vector<float> v_SubJet_btagCSVV2_;
    TBranch *b_SubJet_btagCSVV2_;
    bool loaded_SubJet_btagCSVV2_;
    float SubJet_btagDeepB_[NSUBJET_MAX];
    vector<float> v_SubJet_btagDeepB_;
    TBranch *b_SubJet_btagDeepB_;
    bool loaded_SubJet_btagDeepB_;
    float SubJet_eta_[NSUBJET_MAX];
    vector<float> v_SubJet_eta_;
    TBranch *b_SubJet_eta_;
    bool loaded_SubJet_eta_;
    float SubJet_mass_[NSUBJET_MAX];
    vector<float> v_SubJet_mass_;
    TBranch *b_SubJet_mass_;
    bool loaded_SubJet_mass_;
    float SubJet_n2b1_[NSUBJET_MAX];
    vector<float> v_SubJet_n2b1_;
    TBranch *b_SubJet_n2b1_;
    bool loaded_SubJet_n2b1_;
    float SubJet_n3b1_[NSUBJET_MAX];
    vector<float> v_SubJet_n3b1_;
    TBranch *b_SubJet_n3b1_;
    bool loaded_SubJet_n3b1_;
    UChar_t SubJet_nBHadrons_[NSUBJET_MAX];
    vector<UChar_t> v_SubJet_nBHadrons_;
    TBranch *b_SubJet_nBHadrons_;
    bool loaded_SubJet_nBHadrons_;
    UChar_t SubJet_nCHadrons_[NSUBJET_MAX];
    vector<UChar_t> v_SubJet_nCHadrons_;
    TBranch *b_SubJet_nCHadrons_;
    bool loaded_SubJet_nCHadrons_;
    vector<LorentzVector> v_SubJet_p4_;
    TBranch *b_SubJet_p4_;
    bool loaded_SubJet_p4_;
    float SubJet_phi_[NSUBJET_MAX];
    vector<float> v_SubJet_phi_;
    TBranch *b_SubJet_phi_;
    bool loaded_SubJet_phi_;
    float SubJet_pt_[NSUBJET_MAX];
    vector<float> v_SubJet_pt_;
    TBranch *b_SubJet_pt_;
    bool loaded_SubJet_pt_;
    float SubJet_rawFactor_[NSUBJET_MAX];
    vector<float> v_SubJet_rawFactor_;
    TBranch *b_SubJet_rawFactor_;
    bool loaded_SubJet_rawFactor_;
    float SubJet_tau1_[NSUBJET_MAX];
    vector<float> v_SubJet_tau1_;
    TBranch *b_SubJet_tau1_;
    bool loaded_SubJet_tau1_;
    float SubJet_tau2_[NSUBJET_MAX];
    vector<float> v_SubJet_tau2_;
    TBranch *b_SubJet_tau2_;
    bool loaded_SubJet_tau2_;
    float SubJet_tau3_[NSUBJET_MAX];
    vector<float> v_SubJet_tau3_;
    TBranch *b_SubJet_tau3_;
    bool loaded_SubJet_tau3_;
    float SubJet_tau4_[NSUBJET_MAX];
    vector<float> v_SubJet_tau4_;
    TBranch *b_SubJet_tau4_;
    bool loaded_SubJet_tau4_;
    int Tau_charge_[NTAU_MAX];
    vector<int> v_Tau_charge_;
    TBranch *b_Tau_charge_;
    bool loaded_Tau_charge_;
    float Tau_chargedIso_[NTAU_MAX];
    vector<float> v_Tau_chargedIso_;
    TBranch *b_Tau_chargedIso_;
    bool loaded_Tau_chargedIso_;
    UChar_t Tau_cleanmask_[NTAU_MAX];
    vector<UChar_t> v_Tau_cleanmask_;
    TBranch *b_Tau_cleanmask_;
    bool loaded_Tau_cleanmask_;
    int Tau_decayMode_[NTAU_MAX];
    vector<int> v_Tau_decayMode_;
    TBranch *b_Tau_decayMode_;
    bool loaded_Tau_decayMode_;
    float Tau_dxy_[NTAU_MAX];
    vector<float> v_Tau_dxy_;
    TBranch *b_Tau_dxy_;
    bool loaded_Tau_dxy_;
    float Tau_dz_[NTAU_MAX];
    vector<float> v_Tau_dz_;
    TBranch *b_Tau_dz_;
    bool loaded_Tau_dz_;
    float Tau_eta_[NTAU_MAX];
    vector<float> v_Tau_eta_;
    TBranch *b_Tau_eta_;
    bool loaded_Tau_eta_;
    UChar_t Tau_genPartFlav_[NTAU_MAX];
    vector<UChar_t> v_Tau_genPartFlav_;
    TBranch *b_Tau_genPartFlav_;
    bool loaded_Tau_genPartFlav_;
    int Tau_genPartIdx_[NTAU_MAX];
    vector<int> v_Tau_genPartIdx_;
    TBranch *b_Tau_genPartIdx_;
    bool loaded_Tau_genPartIdx_;
    UChar_t Tau_idAntiEle_[NTAU_MAX];
    vector<UChar_t> v_Tau_idAntiEle_;
    TBranch *b_Tau_idAntiEle_;
    bool loaded_Tau_idAntiEle_;
    UChar_t Tau_idAntiEle2018_[NTAU_MAX];
    vector<UChar_t> v_Tau_idAntiEle2018_;
    TBranch *b_Tau_idAntiEle2018_;
    bool loaded_Tau_idAntiEle2018_;
    UChar_t Tau_idAntiMu_[NTAU_MAX];
    vector<UChar_t> v_Tau_idAntiMu_;
    TBranch *b_Tau_idAntiMu_;
    bool loaded_Tau_idAntiMu_;
    bool Tau_idDecayMode_[NTAU_MAX];
    vector<bool> v_Tau_idDecayMode_;
    TBranch *b_Tau_idDecayMode_;
    bool loaded_Tau_idDecayMode_;
    bool Tau_idDecayModeNewDMs_[NTAU_MAX];
    vector<bool> v_Tau_idDecayModeNewDMs_;
    TBranch *b_Tau_idDecayModeNewDMs_;
    bool loaded_Tau_idDecayModeNewDMs_;
    UChar_t Tau_idDeepTau2017v2p1VSe_[NTAU_MAX];
    vector<UChar_t> v_Tau_idDeepTau2017v2p1VSe_;
    TBranch *b_Tau_idDeepTau2017v2p1VSe_;
    bool loaded_Tau_idDeepTau2017v2p1VSe_;
    UChar_t Tau_idDeepTau2017v2p1VSjet_[NTAU_MAX];
    vector<UChar_t> v_Tau_idDeepTau2017v2p1VSjet_;
    TBranch *b_Tau_idDeepTau2017v2p1VSjet_;
    bool loaded_Tau_idDeepTau2017v2p1VSjet_;
    UChar_t Tau_idDeepTau2017v2p1VSmu_[NTAU_MAX];
    vector<UChar_t> v_Tau_idDeepTau2017v2p1VSmu_;
    TBranch *b_Tau_idDeepTau2017v2p1VSmu_;
    bool loaded_Tau_idDeepTau2017v2p1VSmu_;
    UChar_t Tau_idMVAnewDM2017v2_[NTAU_MAX];
    vector<UChar_t> v_Tau_idMVAnewDM2017v2_;
    TBranch *b_Tau_idMVAnewDM2017v2_;
    bool loaded_Tau_idMVAnewDM2017v2_;
    UChar_t Tau_idMVAoldDM_[NTAU_MAX];
    vector<UChar_t> v_Tau_idMVAoldDM_;
    TBranch *b_Tau_idMVAoldDM_;
    bool loaded_Tau_idMVAoldDM_;
    UChar_t Tau_idMVAoldDM2017v1_[NTAU_MAX];
    vector<UChar_t> v_Tau_idMVAoldDM2017v1_;
    TBranch *b_Tau_idMVAoldDM2017v1_;
    bool loaded_Tau_idMVAoldDM2017v1_;
    UChar_t Tau_idMVAoldDM2017v2_[NTAU_MAX];
    vector<UChar_t> v_Tau_idMVAoldDM2017v2_;
    TBranch *b_Tau_idMVAoldDM2017v2_;
    bool loaded_Tau_idMVAoldDM2017v2_;
    UChar_t Tau_idMVAoldDMdR032017v2_[NTAU_MAX];
    vector<UChar_t> v_Tau_idMVAoldDMdR032017v2_;
    TBranch *b_Tau_idMVAoldDMdR032017v2_;
    bool loaded_Tau_idMVAoldDMdR032017v2_;
    int Tau_jetIdx_[NTAU_MAX];
    vector<int> v_Tau_jetIdx_;
    TBranch *b_Tau_jetIdx_;
    bool loaded_Tau_jetIdx_;
    float Tau_leadTkDeltaEta_[NTAU_MAX];
    vector<float> v_Tau_leadTkDeltaEta_;
    TBranch *b_Tau_leadTkDeltaEta_;
    bool loaded_Tau_leadTkDeltaEta_;
    float Tau_leadTkDeltaPhi_[NTAU_MAX];
    vector<float> v_Tau_leadTkDeltaPhi_;
    TBranch *b_Tau_leadTkDeltaPhi_;
    bool loaded_Tau_leadTkDeltaPhi_;
    float Tau_leadTkPtOverTauPt_[NTAU_MAX];
    vector<float> v_Tau_leadTkPtOverTauPt_;
    TBranch *b_Tau_leadTkPtOverTauPt_;
    bool loaded_Tau_leadTkPtOverTauPt_;
    float Tau_mass_[NTAU_MAX];
    vector<float> v_Tau_mass_;
    TBranch *b_Tau_mass_;
    bool loaded_Tau_mass_;
    float Tau_neutralIso_[NTAU_MAX];
    vector<float> v_Tau_neutralIso_;
    TBranch *b_Tau_neutralIso_;
    bool loaded_Tau_neutralIso_;
    vector<LorentzVector> v_Tau_p4_;
    TBranch *b_Tau_p4_;
    bool loaded_Tau_p4_;
    float Tau_phi_[NTAU_MAX];
    vector<float> v_Tau_phi_;
    TBranch *b_Tau_phi_;
    bool loaded_Tau_phi_;
    float Tau_photonsOutsideSignalCone_[NTAU_MAX];
    vector<float> v_Tau_photonsOutsideSignalCone_;
    TBranch *b_Tau_photonsOutsideSignalCone_;
    bool loaded_Tau_photonsOutsideSignalCone_;
    float Tau_pt_[NTAU_MAX];
    vector<float> v_Tau_pt_;
    TBranch *b_Tau_pt_;
    bool loaded_Tau_pt_;
    float Tau_puCorr_[NTAU_MAX];
    vector<float> v_Tau_puCorr_;
    TBranch *b_Tau_puCorr_;
    bool loaded_Tau_puCorr_;
    float Tau_rawAntiEle_[NTAU_MAX];
    vector<float> v_Tau_rawAntiEle_;
    TBranch *b_Tau_rawAntiEle_;
    bool loaded_Tau_rawAntiEle_;
    float Tau_rawAntiEle2018_[NTAU_MAX];
    vector<float> v_Tau_rawAntiEle2018_;
    TBranch *b_Tau_rawAntiEle2018_;
    bool loaded_Tau_rawAntiEle2018_;
    int Tau_rawAntiEleCat_[NTAU_MAX];
    vector<int> v_Tau_rawAntiEleCat_;
    TBranch *b_Tau_rawAntiEleCat_;
    bool loaded_Tau_rawAntiEleCat_;
    int Tau_rawAntiEleCat2018_[NTAU_MAX];
    vector<int> v_Tau_rawAntiEleCat2018_;
    TBranch *b_Tau_rawAntiEleCat2018_;
    bool loaded_Tau_rawAntiEleCat2018_;
    float Tau_rawDeepTau2017v2p1VSe_[NTAU_MAX];
    vector<float> v_Tau_rawDeepTau2017v2p1VSe_;
    TBranch *b_Tau_rawDeepTau2017v2p1VSe_;
    bool loaded_Tau_rawDeepTau2017v2p1VSe_;
    float Tau_rawDeepTau2017v2p1VSjet_[NTAU_MAX];
    vector<float> v_Tau_rawDeepTau2017v2p1VSjet_;
    TBranch *b_Tau_rawDeepTau2017v2p1VSjet_;
    bool loaded_Tau_rawDeepTau2017v2p1VSjet_;
    float Tau_rawDeepTau2017v2p1VSmu_[NTAU_MAX];
    vector<float> v_Tau_rawDeepTau2017v2p1VSmu_;
    TBranch *b_Tau_rawDeepTau2017v2p1VSmu_;
    bool loaded_Tau_rawDeepTau2017v2p1VSmu_;
    float Tau_rawIso_[NTAU_MAX];
    vector<float> v_Tau_rawIso_;
    TBranch *b_Tau_rawIso_;
    bool loaded_Tau_rawIso_;
    float Tau_rawIsodR03_[NTAU_MAX];
    vector<float> v_Tau_rawIsodR03_;
    TBranch *b_Tau_rawIsodR03_;
    bool loaded_Tau_rawIsodR03_;
    float Tau_rawMVAnewDM2017v2_[NTAU_MAX];
    vector<float> v_Tau_rawMVAnewDM2017v2_;
    TBranch *b_Tau_rawMVAnewDM2017v2_;
    bool loaded_Tau_rawMVAnewDM2017v2_;
    float Tau_rawMVAoldDM_[NTAU_MAX];
    vector<float> v_Tau_rawMVAoldDM_;
    TBranch *b_Tau_rawMVAoldDM_;
    bool loaded_Tau_rawMVAoldDM_;
    float Tau_rawMVAoldDM2017v1_[NTAU_MAX];
    vector<float> v_Tau_rawMVAoldDM2017v1_;
    TBranch *b_Tau_rawMVAoldDM2017v1_;
    bool loaded_Tau_rawMVAoldDM2017v1_;
    float Tau_rawMVAoldDM2017v2_[NTAU_MAX];
    vector<float> v_Tau_rawMVAoldDM2017v2_;
    TBranch *b_Tau_rawMVAoldDM2017v2_;
    bool loaded_Tau_rawMVAoldDM2017v2_;
    float Tau_rawMVAoldDMdR032017v2_[NTAU_MAX];
    vector<float> v_Tau_rawMVAoldDMdR032017v2_;
    TBranch *b_Tau_rawMVAoldDMdR032017v2_;
    bool loaded_Tau_rawMVAoldDMdR032017v2_;
    float TkMET_phi_;
    TBranch *b_TkMET_phi_;
    bool loaded_TkMET_phi_;
    float TkMET_pt_;
    TBranch *b_TkMET_pt_;
    bool loaded_TkMET_pt_;
    float TkMET_sumEt_;
    TBranch *b_TkMET_sumEt_;
    bool loaded_TkMET_sumEt_;
    float TrigObj_eta_[NTRIGOBJ_MAX];
    vector<float> v_TrigObj_eta_;
    TBranch *b_TrigObj_eta_;
    bool loaded_TrigObj_eta_;
    int TrigObj_filterBits_[NTRIGOBJ_MAX];
    vector<int> v_TrigObj_filterBits_;
    TBranch *b_TrigObj_filterBits_;
    bool loaded_TrigObj_filterBits_;
    int TrigObj_id_[NTRIGOBJ_MAX];
    vector<int> v_TrigObj_id_;
    TBranch *b_TrigObj_id_;
    bool loaded_TrigObj_id_;
    int TrigObj_l1charge_[NTRIGOBJ_MAX];
    vector<int> v_TrigObj_l1charge_;
    TBranch *b_TrigObj_l1charge_;
    bool loaded_TrigObj_l1charge_;
    int TrigObj_l1iso_[NTRIGOBJ_MAX];
    vector<int> v_TrigObj_l1iso_;
    TBranch *b_TrigObj_l1iso_;
    bool loaded_TrigObj_l1iso_;
    float TrigObj_l1pt_[NTRIGOBJ_MAX];
    vector<float> v_TrigObj_l1pt_;
    TBranch *b_TrigObj_l1pt_;
    bool loaded_TrigObj_l1pt_;
    float TrigObj_l1pt_2_[NTRIGOBJ_MAX];
    vector<float> v_TrigObj_l1pt_2_;
    TBranch *b_TrigObj_l1pt_2_;
    bool loaded_TrigObj_l1pt_2_;
    float TrigObj_l2pt_[NTRIGOBJ_MAX];
    vector<float> v_TrigObj_l2pt_;
    TBranch *b_TrigObj_l2pt_;
    bool loaded_TrigObj_l2pt_;
    float TrigObj_phi_[NTRIGOBJ_MAX];
    vector<float> v_TrigObj_phi_;
    TBranch *b_TrigObj_phi_;
    bool loaded_TrigObj_phi_;
    float TrigObj_pt_[NTRIGOBJ_MAX];
    vector<float> v_TrigObj_pt_;
    TBranch *b_TrigObj_pt_;
    bool loaded_TrigObj_pt_;
    float btagWeight_CMVA_;
    TBranch *b_btagWeight_CMVA_;
    bool loaded_btagWeight_CMVA_;
    float btagWeight_CSVV2_;
    TBranch *b_btagWeight_CSVV2_;
    bool loaded_btagWeight_CSVV2_;
    float btagWeight_DeepCSVB_;
    TBranch *b_btagWeight_DeepCSVB_;
    bool loaded_btagWeight_DeepCSVB_;
    ULong64_t event_;
    TBranch *b_event_;
    bool loaded_event_;
    float fixedGridRhoFastjetAll_;
    TBranch *b_fixedGridRhoFastjetAll_;
    bool loaded_fixedGridRhoFastjetAll_;
    float fixedGridRhoFastjetCentral_;
    TBranch *b_fixedGridRhoFastjetCentral_;
    bool loaded_fixedGridRhoFastjetCentral_;
    float fixedGridRhoFastjetCentralCalo_;
    TBranch *b_fixedGridRhoFastjetCentralCalo_;
    bool loaded_fixedGridRhoFastjetCentralCalo_;
    float fixedGridRhoFastjetCentralChargedPileUp_;
    TBranch *b_fixedGridRhoFastjetCentralChargedPileUp_;
    bool loaded_fixedGridRhoFastjetCentralChargedPileUp_;
    float fixedGridRhoFastjetCentralNeutral_;
    TBranch *b_fixedGridRhoFastjetCentralNeutral_;
    bool loaded_fixedGridRhoFastjetCentralNeutral_;
    int genTtbarId_;
    TBranch *b_genTtbarId_;
    bool loaded_genTtbarId_;
    float genWeight_;
    TBranch *b_genWeight_;
    bool loaded_genWeight_;
    UInt_t luminosityBlock_;
    TBranch *b_luminosityBlock_;
    bool loaded_luminosityBlock_;
    UInt_t nCorrT1METJet_;
    TBranch *b_nCorrT1METJet_;
    bool loaded_nCorrT1METJet_;
    UInt_t nElectron_;
    TBranch *b_nElectron_;
    bool loaded_nElectron_;
    UInt_t nFatJet_;
    TBranch *b_nFatJet_;
    bool loaded_nFatJet_;
    UInt_t nFsrPhoton_;
    TBranch *b_nFsrPhoton_;
    bool loaded_nFsrPhoton_;
    UInt_t nGenDressedLepton_;
    TBranch *b_nGenDressedLepton_;
    bool loaded_nGenDressedLepton_;
    UInt_t nGenIsolatedPhoton_;
    TBranch *b_nGenIsolatedPhoton_;
    bool loaded_nGenIsolatedPhoton_;
    UInt_t nGenJet_;
    TBranch *b_nGenJet_;
    bool loaded_nGenJet_;
    UInt_t nGenJetAK8_;
    TBranch *b_nGenJetAK8_;
    bool loaded_nGenJetAK8_;
    UInt_t nGenPart_;
    TBranch *b_nGenPart_;
    bool loaded_nGenPart_;
    UInt_t nGenVisTau_;
    TBranch *b_nGenVisTau_;
    bool loaded_nGenVisTau_;
    UInt_t nIsoTrack_;
    TBranch *b_nIsoTrack_;
    bool loaded_nIsoTrack_;
    UInt_t nJet_;
    TBranch *b_nJet_;
    bool loaded_nJet_;
    UInt_t nLHEPart_;
    TBranch *b_nLHEPart_;
    bool loaded_nLHEPart_;
    UInt_t nLHEPdfWeight_;
    TBranch *b_nLHEPdfWeight_;
    bool loaded_nLHEPdfWeight_;
    UInt_t nLHEReweightingWeight_;
    TBranch *b_nLHEReweightingWeight_;
    bool loaded_nLHEReweightingWeight_;
    UInt_t nLHEScaleWeight_;
    TBranch *b_nLHEScaleWeight_;
    bool loaded_nLHEScaleWeight_;
    UInt_t nMuon_;
    TBranch *b_nMuon_;
    bool loaded_nMuon_;
    UInt_t nOtherPV_;
    TBranch *b_nOtherPV_;
    bool loaded_nOtherPV_;
    UInt_t nPSWeight_;
    TBranch *b_nPSWeight_;
    bool loaded_nPSWeight_;
    UInt_t nPhoton_;
    TBranch *b_nPhoton_;
    bool loaded_nPhoton_;
    UInt_t nSV_;
    TBranch *b_nSV_;
    bool loaded_nSV_;
    UInt_t nSoftActivityJet_;
    TBranch *b_nSoftActivityJet_;
    bool loaded_nSoftActivityJet_;
    UInt_t nSubGenJetAK8_;
    TBranch *b_nSubGenJetAK8_;
    bool loaded_nSubGenJetAK8_;
    UInt_t nSubJet_;
    TBranch *b_nSubJet_;
    bool loaded_nSubJet_;
    UInt_t nTau_;
    TBranch *b_nTau_;
    bool loaded_nTau_;
    UInt_t nTrigObj_;
    TBranch *b_nTrigObj_;
    bool loaded_nTrigObj_;
    UInt_t run_;
    TBranch *b_run_;
    bool loaded_run_;
    Int_t year_;
public:
    void Init(TTree *tree);
    void SetYear(int year);
    void ParseYear(TTree *tree);
    void PrintUsage();
    void GetEntry(unsigned int idx);
    const vector<float> &LHEWeight_mg_reweighting();
    const float &CaloMET_phi();
    const float &CaloMET_pt();
    const float &CaloMET_sumEt();
    const float &ChsMET_phi();
    const float &ChsMET_pt();
    const float &ChsMET_sumEt();
    const vector<float> &CorrT1METJet_area();
    const vector<float> &CorrT1METJet_eta();
    const vector<float> &CorrT1METJet_muonSubtrFactor();
    const vector<float> &CorrT1METJet_phi();
    const vector<float> &CorrT1METJet_rawPt();
    const vector<int> &Electron_charge();
    const vector<UChar_t> &Electron_cleanmask();
    const vector<bool> &Electron_convVeto();
    const vector<int> &Electron_cutBased();
    const vector<int> &Electron_cutBased_Fall17_V1();
    const vector<bool> &Electron_cutBased_HEEP();
    const vector<int> &Electron_cutBased_HLTPreSel();
    const vector<int> &Electron_cutBased_Spring15();
    const vector<int> &Electron_cutBased_Sum16();
    const vector<float> &Electron_deltaEtaSC();
    const vector<float> &Electron_dr03EcalRecHitSumEt();
    const vector<float> &Electron_dr03HcalDepth1TowerSumEt();
    const vector<float> &Electron_dr03TkSumPt();
    const vector<float> &Electron_dr03TkSumPtHEEP();
    const vector<float> &Electron_dxy();
    const vector<float> &Electron_dxyErr();
    const vector<float> &Electron_dz();
    const vector<float> &Electron_dzErr();
    const vector<float> &Electron_eCorr();
    const vector<float> &Electron_eInvMinusPInv();
    const vector<float> &Electron_energyErr();
    const vector<float> &Electron_eta();
    const vector<UChar_t> &Electron_genPartFlav();
    const vector<int> &Electron_genPartIdx();
    const vector<float> &Electron_hoe();
    const vector<float> &Electron_ip3d();
    const vector<bool> &Electron_isPFcand();
    const vector<int> &Electron_jetIdx();
    const vector<float> &Electron_jetPtRelv2();
    const vector<float> &Electron_jetRelIso();
    const vector<UChar_t> &Electron_lostHits();
    const vector<float> &Electron_mass();
    const vector<float> &Electron_miniPFRelIso_all();
    const vector<float> &Electron_miniPFRelIso_chg();
    const vector<float> &Electron_mvaFall17V1Iso();
    const vector<bool> &Electron_mvaFall17V1Iso_WP80();
    const vector<bool> &Electron_mvaFall17V1Iso_WP90();
    const vector<bool> &Electron_mvaFall17V1Iso_WPL();
    const vector<float> &Electron_mvaFall17V1noIso();
    const vector<bool> &Electron_mvaFall17V1noIso_WP80();
    const vector<bool> &Electron_mvaFall17V1noIso_WP90();
    const vector<bool> &Electron_mvaFall17V1noIso_WPL();
    const vector<float> &Electron_mvaFall17V2Iso();
    const vector<bool> &Electron_mvaFall17V2Iso_WP80();
    const vector<bool> &Electron_mvaFall17V2Iso_WP90();
    const vector<bool> &Electron_mvaFall17V2Iso_WPL();
    const vector<float> &Electron_mvaFall17V2noIso();
    const vector<bool> &Electron_mvaFall17V2noIso_WP80();
    const vector<bool> &Electron_mvaFall17V2noIso_WP90();
    const vector<bool> &Electron_mvaFall17V2noIso_WPL();
    const vector<float> &Electron_mvaSpring16GP();
    const vector<bool> &Electron_mvaSpring16GP_WP80();
    const vector<bool> &Electron_mvaSpring16GP_WP90();
    const vector<float> &Electron_mvaSpring16HZZ();
    const vector<bool> &Electron_mvaSpring16HZZ_WPL();
    const vector<float> &Electron_mvaTTH();
    const vector<LorentzVector> &Electron_p4();
    const vector<int> &Electron_pdgId();
    const vector<float> &Electron_pfRelIso03_all();
    const vector<float> &Electron_pfRelIso03_chg();
    const vector<float> &Electron_phi();
    const vector<int> &Electron_photonIdx();
    const vector<float> &Electron_pt();
    const vector<float> &Electron_r9();
    const vector<float> &Electron_scEtOverPt();
    const vector<UChar_t> &Electron_seedGain();
    const vector<float> &Electron_sieie();
    const vector<float> &Electron_sip3d();
    const vector<int> &Electron_tightCharge();
    const vector<int> &Electron_vidNestedWPBitmap();
    const vector<int> &Electron_vidNestedWPBitmapHEEP();
    const vector<int> &Electron_vidNestedWPBitmapSpring15();
    const vector<int> &Electron_vidNestedWPBitmapSum16();
    const vector<float> &FatJet_area();
    const vector<float> &FatJet_btagCMVA();
    const vector<float> &FatJet_btagCSVV2();
    const vector<float> &FatJet_btagDDBvL();
    const vector<float> &FatJet_btagDDBvL_noMD();
    const vector<float> &FatJet_btagDDCvB();
    const vector<float> &FatJet_btagDDCvB_noMD();
    const vector<float> &FatJet_btagDDCvL();
    const vector<float> &FatJet_btagDDCvL_noMD();
    const vector<float> &FatJet_btagDeepB();
    const vector<float> &FatJet_btagHbb();
    const vector<float> &FatJet_deepTagMD_H4qvsQCD();
    const vector<float> &FatJet_deepTagMD_HbbvsQCD();
    const vector<float> &FatJet_deepTagMD_TvsQCD();
    const vector<float> &FatJet_deepTagMD_WvsQCD();
    const vector<float> &FatJet_deepTagMD_ZHbbvsQCD();
    const vector<float> &FatJet_deepTagMD_ZHccvsQCD();
    const vector<float> &FatJet_deepTagMD_ZbbvsQCD();
    const vector<float> &FatJet_deepTagMD_ZvsQCD();
    const vector<float> &FatJet_deepTagMD_bbvsLight();
    const vector<float> &FatJet_deepTagMD_ccvsLight();
    const vector<float> &FatJet_deepTag_H();
    const vector<float> &FatJet_deepTag_QCD();
    const vector<float> &FatJet_deepTag_QCDothers();
    const vector<float> &FatJet_deepTag_TvsQCD();
    const vector<float> &FatJet_deepTag_WvsQCD();
    const vector<float> &FatJet_deepTag_ZvsQCD();
    const vector<int> &FatJet_electronIdx3SJ();
    const vector<float> &FatJet_eta();
    const vector<int> &FatJet_genJetAK8Idx();
    const vector<int> &FatJet_hadronFlavour();
    const vector<int> &FatJet_jetId();
    const vector<float> &FatJet_lsf3();
    const vector<float> &FatJet_mass();
    const vector<float> &FatJet_msoftdrop();
    const vector<int> &FatJet_muonIdx3SJ();
    const vector<float> &FatJet_n2b1();
    const vector<float> &FatJet_n3b1();
    const vector<UChar_t> &FatJet_nBHadrons();
    const vector<UChar_t> &FatJet_nCHadrons();
    const vector<LorentzVector> &FatJet_p4();
    const vector<float> &FatJet_phi();
    const vector<float> &FatJet_pt();
    const vector<float> &FatJet_rawFactor();
    const vector<int> &FatJet_subJetIdx1();
    const vector<int> &FatJet_subJetIdx2();
    const vector<float> &FatJet_tau1();
    const vector<float> &FatJet_tau2();
    const vector<float> &FatJet_tau3();
    const vector<float> &FatJet_tau4();
    const bool &Flag_BadChargedCandidateFilter();
    const bool &Flag_BadChargedCandidateSummer16Filter();
    const bool &Flag_BadPFMuonFilter();
    const bool &Flag_BadPFMuonSummer16Filter();
    const bool &Flag_CSCTightHalo2015Filter();
    const bool &Flag_CSCTightHaloFilter();
    const bool &Flag_CSCTightHaloTrkMuUnvetoFilter();
    const bool &Flag_EcalDeadCellBoundaryEnergyFilter();
    const bool &Flag_EcalDeadCellTriggerPrimitiveFilter();
    const bool &Flag_HBHENoiseFilter();
    const bool &Flag_HBHENoiseIsoFilter();
    const bool &Flag_HcalStripHaloFilter();
    const bool &Flag_METFilters();
    const bool &Flag_chargedHadronTrackResolutionFilter();
    const bool &Flag_ecalBadCalibFilter();
    const bool &Flag_ecalBadCalibFilterV2();
    const bool &Flag_ecalLaserCorrFilter();
    const bool &Flag_eeBadScFilter();
    const bool &Flag_globalSuperTightHalo2016Filter();
    const bool &Flag_globalTightHalo2016Filter();
    const bool &Flag_goodVertices();
    const bool &Flag_hcalLaserEventFilter();
    const bool &Flag_muonBadTrackFilter();
    const bool &Flag_trkPOGFilters();
    const bool &Flag_trkPOG_logErrorTooManyClusters();
    const bool &Flag_trkPOG_manystripclus53X();
    const bool &Flag_trkPOG_toomanystripclus53X();
    const vector<float> &FsrPhoton_dROverEt2();
    const vector<float> &FsrPhoton_eta();
    const vector<int> &FsrPhoton_muonIdx();
    const vector<float> &FsrPhoton_phi();
    const vector<float> &FsrPhoton_pt();
    const vector<float> &FsrPhoton_relIso03();
    const vector<float> &GenDressedLepton_eta();
    const vector<bool> &GenDressedLepton_hasTauAnc();
    const vector<float> &GenDressedLepton_mass();
    const vector<LorentzVector> &GenDressedLepton_p4();
    const vector<int> &GenDressedLepton_pdgId();
    const vector<float> &GenDressedLepton_phi();
    const vector<float> &GenDressedLepton_pt();
    const vector<float> &GenIsolatedPhoton_eta();
    const vector<float> &GenIsolatedPhoton_mass();
    const vector<LorentzVector> &GenIsolatedPhoton_p4();
    const vector<float> &GenIsolatedPhoton_phi();
    const vector<float> &GenIsolatedPhoton_pt();
    const vector<float> &GenJetAK8_eta();
    const vector<UChar_t> &GenJetAK8_hadronFlavour();
    const vector<float> &GenJetAK8_mass();
    const vector<LorentzVector> &GenJetAK8_p4();
    const vector<int> &GenJetAK8_partonFlavour();
    const vector<float> &GenJetAK8_phi();
    const vector<float> &GenJetAK8_pt();
    const vector<float> &GenJet_eta();
    const vector<UChar_t> &GenJet_hadronFlavour();
    const vector<float> &GenJet_mass();
    const vector<LorentzVector> &GenJet_p4();
    const vector<int> &GenJet_partonFlavour();
    const vector<float> &GenJet_phi();
    const vector<float> &GenJet_pt();
    const float &GenMET_phi();
    const float &GenMET_pt();
    const vector<float> &GenPart_eta();
    const vector<int> &GenPart_genPartIdxMother();
    const vector<float> &GenPart_mass();
    const vector<LorentzVector> &GenPart_p4();
    const vector<int> &GenPart_pdgId();
    const vector<float> &GenPart_phi();
    const vector<float> &GenPart_pt();
    const vector<int> &GenPart_status();
    const vector<int> &GenPart_statusFlags();
    const vector<int> &GenVisTau_charge();
    const vector<float> &GenVisTau_eta();
    const vector<int> &GenVisTau_genPartIdxMother();
    const vector<float> &GenVisTau_mass();
    const vector<LorentzVector> &GenVisTau_p4();
    const vector<float> &GenVisTau_phi();
    const vector<float> &GenVisTau_pt();
    const vector<int> &GenVisTau_status();
    const float &Generator_binvar();
    const int &Generator_id1();
    const int &Generator_id2();
    const float &Generator_scalePDF();
    const float &Generator_weight();
    const float &Generator_x1();
    const float &Generator_x2();
    const float &Generator_xpdf1();
    const float &Generator_xpdf2();
    const bool &HLT_AK4CaloJet100();
    const bool &HLT_AK4CaloJet120();
    const bool &HLT_AK4CaloJet30();
    const bool &HLT_AK4CaloJet40();
    const bool &HLT_AK4CaloJet50();
    const bool &HLT_AK4CaloJet80();
    const bool &HLT_AK4PFJet100();
    const bool &HLT_AK4PFJet120();
    const bool &HLT_AK4PFJet30();
    const bool &HLT_AK4PFJet50();
    const bool &HLT_AK4PFJet80();
    const bool &HLT_AK8DiPFJet250_200_TrimMass30();
    const bool &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20();
    const bool &HLT_AK8DiPFJet280_200_TrimMass30();
    const bool &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087();
    const bool &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20();
    const bool &HLT_AK8DiPFJet300_200_TrimMass30();
    const bool &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087();
    const bool &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20();
    const bool &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20();
    const bool &HLT_AK8PFHT650_TrimR0p1PT0p03Mass50();
    const bool &HLT_AK8PFHT700_TrimR0p1PT0p03Mass50();
    const bool &HLT_AK8PFHT750_TrimMass50();
    const bool &HLT_AK8PFHT800_TrimMass50();
    const bool &HLT_AK8PFHT850_TrimMass50();
    const bool &HLT_AK8PFHT900_TrimMass50();
    const bool &HLT_AK8PFJet140();
    const bool &HLT_AK8PFJet15();
    const bool &HLT_AK8PFJet200();
    const bool &HLT_AK8PFJet25();
    const bool &HLT_AK8PFJet260();
    const bool &HLT_AK8PFJet320();
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1();
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17();
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2();
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4();
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02();
    const bool &HLT_AK8PFJet360_TrimMass30();
    const bool &HLT_AK8PFJet380_TrimMass30();
    const bool &HLT_AK8PFJet40();
    const bool &HLT_AK8PFJet400();
    const bool &HLT_AK8PFJet400_TrimMass30();
    const bool &HLT_AK8PFJet420_TrimMass30();
    const bool &HLT_AK8PFJet450();
    const bool &HLT_AK8PFJet500();
    const bool &HLT_AK8PFJet550();
    const bool &HLT_AK8PFJet60();
    const bool &HLT_AK8PFJet80();
    const bool &HLT_AK8PFJetFwd140();
    const bool &HLT_AK8PFJetFwd15();
    const bool &HLT_AK8PFJetFwd200();
    const bool &HLT_AK8PFJetFwd25();
    const bool &HLT_AK8PFJetFwd260();
    const bool &HLT_AK8PFJetFwd320();
    const bool &HLT_AK8PFJetFwd40();
    const bool &HLT_AK8PFJetFwd400();
    const bool &HLT_AK8PFJetFwd450();
    const bool &HLT_AK8PFJetFwd500();
    const bool &HLT_AK8PFJetFwd60();
    const bool &HLT_AK8PFJetFwd80();
    const bool &HLT_BTagMu_AK4DiJet110_Mu5();
    const bool &HLT_BTagMu_AK4DiJet110_Mu5_noalgo();
    const bool &HLT_BTagMu_AK4DiJet170_Mu5();
    const bool &HLT_BTagMu_AK4DiJet170_Mu5_noalgo();
    const bool &HLT_BTagMu_AK4DiJet20_Mu5();
    const bool &HLT_BTagMu_AK4DiJet20_Mu5_noalgo();
    const bool &HLT_BTagMu_AK4DiJet40_Mu5();
    const bool &HLT_BTagMu_AK4DiJet40_Mu5_noalgo();
    const bool &HLT_BTagMu_AK4DiJet70_Mu5();
    const bool &HLT_BTagMu_AK4DiJet70_Mu5_noalgo();
    const bool &HLT_BTagMu_AK4Jet300_Mu5();
    const bool &HLT_BTagMu_AK4Jet300_Mu5_noalgo();
    const bool &HLT_BTagMu_AK8DiJet170_Mu5();
    const bool &HLT_BTagMu_AK8DiJet170_Mu5_noalgo();
    const bool &HLT_BTagMu_AK8Jet170_DoubleMu5();
    const bool &HLT_BTagMu_AK8Jet170_DoubleMu5_noalgo();
    const bool &HLT_BTagMu_AK8Jet300_Mu5();
    const bool &HLT_BTagMu_AK8Jet300_Mu5_noalgo();
    const bool &HLT_BTagMu_DiJet110_Mu5();
    const bool &HLT_BTagMu_DiJet170_Mu5();
    const bool &HLT_BTagMu_DiJet20_Mu5();
    const bool &HLT_BTagMu_DiJet40_Mu5();
    const bool &HLT_BTagMu_DiJet70_Mu5();
    const bool &HLT_BTagMu_Jet300_Mu5();
    const bool &HLT_CDC_L2cosmic_5_er1p0();
    const bool &HLT_CDC_L2cosmic_5p5_er1p0();
    const bool &HLT_CaloJet260();
    const bool &HLT_CaloJet500_NoJetID();
    const bool &HLT_CaloJet550_NoJetID();
    const bool &HLT_CaloMET100_HBHECleaned();
    const bool &HLT_CaloMET100_NotCleaned();
    const bool &HLT_CaloMET110_NotCleaned();
    const bool &HLT_CaloMET250_HBHECleaned();
    const bool &HLT_CaloMET250_NotCleaned();
    const bool &HLT_CaloMET300_HBHECleaned();
    const bool &HLT_CaloMET350_HBHECleaned();
    const bool &HLT_CaloMET70_HBHECleaned();
    const bool &HLT_CaloMET80_HBHECleaned();
    const bool &HLT_CaloMET80_NotCleaned();
    const bool &HLT_CaloMET90_HBHECleaned();
    const bool &HLT_CaloMET90_NotCleaned();
    const bool &HLT_CaloMHT90();
    const bool &HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight();
    const bool &HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067();
    const bool &HLT_DiCentralPFJet170();
    const bool &HLT_DiCentralPFJet170_CFMax0p1();
    const bool &HLT_DiCentralPFJet220_CFMax0p3();
    const bool &HLT_DiCentralPFJet330_CFMax0p5();
    const bool &HLT_DiCentralPFJet430();
    const bool &HLT_DiEle27_WPTightCaloOnly_L1DoubleEG();
    const bool &HLT_DiJet110_35_Mjj650_PFMET110();
    const bool &HLT_DiJet110_35_Mjj650_PFMET120();
    const bool &HLT_DiJet110_35_Mjj650_PFMET130();
    const bool &HLT_DiMu4_Ele9_CaloIdL_TrackIdL_DZ_Mass3p8();
    const bool &HLT_DiMu9_Ele9_CaloIdL_TrackIdL();
    const bool &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ();
    const bool &HLT_DiPFJet15_FBEta3_NoCaloMatched();
    const bool &HLT_DiPFJet15_NoCaloMatched();
    const bool &HLT_DiPFJet25_FBEta3_NoCaloMatched();
    const bool &HLT_DiPFJet25_NoCaloMatched();
    const bool &HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140();
    const bool &HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80();
    const bool &HLT_DiPFJetAve100_HFJEC();
    const bool &HLT_DiPFJetAve140();
    const bool &HLT_DiPFJetAve15_HFJEC();
    const bool &HLT_DiPFJetAve160_HFJEC();
    const bool &HLT_DiPFJetAve200();
    const bool &HLT_DiPFJetAve220_HFJEC();
    const bool &HLT_DiPFJetAve25_HFJEC();
    const bool &HLT_DiPFJetAve260();
    const bool &HLT_DiPFJetAve300_HFJEC();
    const bool &HLT_DiPFJetAve320();
    const bool &HLT_DiPFJetAve35_HFJEC();
    const bool &HLT_DiPFJetAve40();
    const bool &HLT_DiPFJetAve400();
    const bool &HLT_DiPFJetAve500();
    const bool &HLT_DiPFJetAve60();
    const bool &HLT_DiPFJetAve60_HFJEC();
    const bool &HLT_DiPFJetAve80();
    const bool &HLT_DiPFJetAve80_HFJEC();
    const bool &HLT_DiSC30_18_EIso_AND_HE_Mass70();
    const bool &HLT_Dimuon0_Jpsi();
    const bool &HLT_Dimuon0_Jpsi3p5_Muon2();
    const bool &HLT_Dimuon0_Jpsi_L1_4R_0er1p5R();
    const bool &HLT_Dimuon0_Jpsi_L1_NoOS();
    const bool &HLT_Dimuon0_Jpsi_Muon();
    const bool &HLT_Dimuon0_Jpsi_NoVertexing();
    const bool &HLT_Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R();
    const bool &HLT_Dimuon0_Jpsi_NoVertexing_NoOS();
    const bool &HLT_Dimuon0_LowMass();
    const bool &HLT_Dimuon0_LowMass_L1_0er1p5();
    const bool &HLT_Dimuon0_LowMass_L1_0er1p5R();
    const bool &HLT_Dimuon0_LowMass_L1_4();
    const bool &HLT_Dimuon0_LowMass_L1_4R();
    const bool &HLT_Dimuon0_LowMass_L1_TM530();
    const bool &HLT_Dimuon0_Phi_Barrel();
    const bool &HLT_Dimuon0_Upsilon_L1_4p5();
    const bool &HLT_Dimuon0_Upsilon_L1_4p5NoOS();
    const bool &HLT_Dimuon0_Upsilon_L1_4p5er2p0();
    const bool &HLT_Dimuon0_Upsilon_L1_4p5er2p0M();
    const bool &HLT_Dimuon0_Upsilon_L1_5();
    const bool &HLT_Dimuon0_Upsilon_L1_5M();
    const bool &HLT_Dimuon0_Upsilon_Muon();
    const bool &HLT_Dimuon0_Upsilon_Muon_L1_TM0();
    const bool &HLT_Dimuon0_Upsilon_Muon_NoL1Mass();
    const bool &HLT_Dimuon0_Upsilon_NoVertexing();
    const bool &HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing();
    const bool &HLT_Dimuon0er16_Jpsi_NoVertexing();
    const bool &HLT_Dimuon10_Jpsi_Barrel();
    const bool &HLT_Dimuon10_PsiPrime_Barrel_Seagulls();
    const bool &HLT_Dimuon12_Upsilon_y1p4();
    const bool &HLT_Dimuon13_PsiPrime();
    const bool &HLT_Dimuon13_Upsilon();
    const bool &HLT_Dimuon14_Phi_Barrel_Seagulls();
    const bool &HLT_Dimuon16_Jpsi();
    const bool &HLT_Dimuon18_PsiPrime();
    const bool &HLT_Dimuon18_PsiPrime_noCorrL1();
    const bool &HLT_Dimuon20_Jpsi();
    const bool &HLT_Dimuon20_Jpsi_Barrel_Seagulls();
    const bool &HLT_Dimuon24_Phi_noCorrL1();
    const bool &HLT_Dimuon24_Upsilon_noCorrL1();
    const bool &HLT_Dimuon25_Jpsi();
    const bool &HLT_Dimuon25_Jpsi_noCorrL1();
    const bool &HLT_Dimuon6_Jpsi_NoVertexing();
    const bool &HLT_Dimuon8_PsiPrime_Barrel();
    const bool &HLT_Dimuon8_Upsilon_Barrel();
    const bool &HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55();
    const bool &HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55();
    const bool &HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55();
    const bool &HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55();
    const bool &HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto();
    const bool &HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_Mass55();
    const bool &HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70();
    const bool &HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90();
    const bool &HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55();
    const bool &HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90();
    const bool &HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95();
    const bool &HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf();
    const bool &HLT_DoubleEle24_eta2p1_WPTight_Gsf();
    const bool &HLT_DoubleEle25_CaloIdL_GsfTrkIdVL();
    const bool &HLT_DoubleEle25_CaloIdL_MW();
    const bool &HLT_DoubleEle27_CaloIdL_MW();
    const bool &HLT_DoubleEle33_CaloIdL();
    const bool &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL();
    const bool &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW();
    const bool &HLT_DoubleEle33_CaloIdL_MW();
    const bool &HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL();
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350();
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250();
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300();
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350();
    const bool &HLT_DoubleIsoMu17_eta2p1();
    const bool &HLT_DoubleIsoMu17_eta2p1_noDzCut();
    const bool &HLT_DoubleIsoMu20_eta2p1();
    const bool &HLT_DoubleJet90_Double30_DoubleBTagCSV_p087();
    const bool &HLT_DoubleJet90_Double30_TripleBTagCSV_p087();
    const bool &HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6();
    const bool &HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160();
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p014();
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350();
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p026();
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350();
    const bool &HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6();
    const bool &HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172();
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha();
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed();
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_NoL2Matched();
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha_NoL2Matched();
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha();
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed();
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_Eta2p4();
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_NoL2Matched();
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4();
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_NoL2Matched();
    const bool &HLT_DoubleL2Mu30NoVtx_2Cha_CosmicSeed_Eta2p4();
    const bool &HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4();
    const bool &HLT_DoubleL2Mu50();
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg();
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg();
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1();
    const bool &HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1();
    const bool &HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleMu0();
    const bool &HLT_DoubleMu18NoFiltersNoVtx();
    const bool &HLT_DoubleMu20_7_Mass0to30_L1_DM4();
    const bool &HLT_DoubleMu20_7_Mass0to30_L1_DM4EG();
    const bool &HLT_DoubleMu20_7_Mass0to30_Photon23();
    const bool &HLT_DoubleMu23NoFiltersNoVtxDisplaced();
    const bool &HLT_DoubleMu28NoFiltersNoVtxDisplaced();
    const bool &HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi();
    const bool &HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05();
    const bool &HLT_DoubleMu33NoFiltersNoVtx();
    const bool &HLT_DoubleMu33NoFiltersNoVtxDisplaced();
    const bool &HLT_DoubleMu38NoFiltersNoVtx();
    const bool &HLT_DoubleMu3_DCA_PFMET50_PFMHT60();
    const bool &HLT_DoubleMu3_DZ_PFMET50_PFMHT60();
    const bool &HLT_DoubleMu3_DZ_PFMET70_PFMHT70();
    const bool &HLT_DoubleMu3_DZ_PFMET90_PFMHT90();
    const bool &HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon();
    const bool &HLT_DoubleMu3_PFMET50();
    const bool &HLT_DoubleMu3_TkMu_DsTau3Mu();
    const bool &HLT_DoubleMu3_Trk_Tau3mu();
    const bool &HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass();
    const bool &HLT_DoubleMu40NoFiltersNoVtxDisplaced();
    const bool &HLT_DoubleMu43NoFiltersNoVtx();
    const bool &HLT_DoubleMu48NoFiltersNoVtx();
    const bool &HLT_DoubleMu4_3_Bs();
    const bool &HLT_DoubleMu4_3_Jpsi();
    const bool &HLT_DoubleMu4_3_Jpsi_Displaced();
    const bool &HLT_DoubleMu4_JpsiTrkTrk_Displaced();
    const bool &HLT_DoubleMu4_JpsiTrk_Displaced();
    const bool &HLT_DoubleMu4_Jpsi_Displaced();
    const bool &HLT_DoubleMu4_Jpsi_NoVertexing();
    const bool &HLT_DoubleMu4_LowMassNonResonantTrk_Displaced();
    const bool &HLT_DoubleMu4_Mass3p8_DZ_PFHT350();
    const bool &HLT_DoubleMu4_PsiPrimeTrk_Displaced();
    const bool &HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL();
    const bool &HLT_DoubleMu8_Mass8_PFHT250();
    const bool &HLT_DoubleMu8_Mass8_PFHT300();
    const bool &HLT_DoublePFJets100_CaloBTagDeepCSV_p71();
    const bool &HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagDeepCSV_p71();
    const bool &HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagDeepCSV_p71();
    const bool &HLT_DoublePFJets200_CaloBTagDeepCSV_p71();
    const bool &HLT_DoublePFJets350_CaloBTagDeepCSV_p71();
    const bool &HLT_DoublePFJets40_CaloBTagDeepCSV_p71();
    const bool &HLT_DoublePhoton33_CaloIdL();
    const bool &HLT_DoublePhoton60();
    const bool &HLT_DoublePhoton70();
    const bool &HLT_DoublePhoton85();
    const bool &HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg();
    const bool &HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg();
    const bool &HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1();
    const bool &HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg();
    const bool &HLT_DoubleTrkMu_16_6_NoFiltersNoVtx();
    const bool &HLT_ECALHT800();
    const bool &HLT_EcalCalibration();
    const bool &HLT_Ele105_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13();
    const bool &HLT_Ele115_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele12_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30();
    const bool &HLT_Ele12_CaloIdM_TrackIdM_PFJet30();
    const bool &HLT_Ele135_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele145_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30();
    const bool &HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400();
    const bool &HLT_Ele15_IsoVVVL_PFHT350();
    const bool &HLT_Ele15_IsoVVVL_PFHT350_PFMET50();
    const bool &HLT_Ele15_IsoVVVL_PFHT400();
    const bool &HLT_Ele15_IsoVVVL_PFHT400_PFMET50();
    const bool &HLT_Ele15_IsoVVVL_PFHT450();
    const bool &HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5();
    const bool &HLT_Ele15_IsoVVVL_PFHT450_PFMET50();
    const bool &HLT_Ele15_IsoVVVL_PFHT600();
    const bool &HLT_Ele15_WPLoose_Gsf();
    const bool &HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL();
    const bool &HLT_Ele17_CaloIdL_GsfTrkIdVL();
    const bool &HLT_Ele17_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30();
    const bool &HLT_Ele17_CaloIdM_TrackIdM_PFJet30();
    const bool &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ();
    const bool &HLT_Ele17_Ele8_Gsf();
    const bool &HLT_Ele17_WPLoose_Gsf();
    const bool &HLT_Ele200_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele20_WPLoose_Gsf();
    const bool &HLT_Ele20_WPTight_Gsf();
    const bool &HLT_Ele20_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28();
    const bool &HLT_Ele22_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1();
    const bool &HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29();
    const bool &HLT_Ele23_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30();
    const bool &HLT_Ele23_CaloIdM_TrackIdM_PFJet30();
    const bool &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ();
    const bool &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded();
    const bool &HLT_Ele23_WPLoose_Gsf();
    const bool &HLT_Ele23_WPLoose_Gsf_WHbbBoost();
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20();
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1();
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30();
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1();
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1();
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1();
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1();
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1();
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1();
    const bool &HLT_Ele250_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele25_WPTight_Gsf();
    const bool &HLT_Ele25_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele25_eta2p1_WPTight_Gsf();
    const bool &HLT_Ele27_Ele37_CaloIdL_MW();
    const bool &HLT_Ele27_HighEta_Ele20_Mass55();
    const bool &HLT_Ele27_WPLoose_Gsf();
    const bool &HLT_Ele27_WPLoose_Gsf_WHbbBoost();
    const bool &HLT_Ele27_WPTight_Gsf();
    const bool &HLT_Ele27_WPTight_Gsf_L1JetTauSeeded();
    const bool &HLT_Ele27_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele27_eta2p1_WPLoose_Gsf_HT200();
    const bool &HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1();
    const bool &HLT_Ele27_eta2p1_WPTight_Gsf();
    const bool &HLT_Ele28_HighEta_SC20_Mass55();
    const bool &HLT_Ele28_WPTight_Gsf();
    const bool &HLT_Ele28_eta2p1_WPTight_Gsf_HT150();
    const bool &HLT_Ele300_CaloIdVT_GsfTrkIdT();
    const bool &HLT_Ele30WP60_Ele8_Mass55();
    const bool &HLT_Ele30WP60_SC4_Mass55();
    const bool &HLT_Ele30_WPTight_Gsf();
    const bool &HLT_Ele30_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele30_eta2p1_WPTight_Gsf();
    const bool &HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned();
    const bool &HLT_Ele32_WPTight_Gsf();
    const bool &HLT_Ele32_WPTight_Gsf_L1DoubleEG();
    const bool &HLT_Ele32_eta2p1_WPLoose_Gsf();
    const bool &HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1();
    const bool &HLT_Ele32_eta2p1_WPTight_Gsf();
    const bool &HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50();
    const bool &HLT_Ele35_WPLoose_Gsf();
    const bool &HLT_Ele35_WPTight_Gsf();
    const bool &HLT_Ele35_WPTight_Gsf_L1EGMT();
    const bool &HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1();
    const bool &HLT_Ele38_WPTight_Gsf();
    const bool &HLT_Ele40_WPTight_Gsf();
    const bool &HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50();
    const bool &HLT_Ele45_WPLoose_Gsf();
    const bool &HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded();
    const bool &HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140();
    const bool &HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165();
    const bool &HLT_Ele50_IsoVVVL_PFHT400();
    const bool &HLT_Ele50_IsoVVVL_PFHT450();
    const bool &HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30();
    const bool &HLT_Ele8_CaloIdM_TrackIdM_PFJet30();
    const bool &HLT_FullTracks_Multiplicity100();
    const bool &HLT_FullTracks_Multiplicity130();
    const bool &HLT_FullTracks_Multiplicity150();
    const bool &HLT_FullTracks_Multiplicity80();
    const bool &HLT_GlobalRunHPDNoise();
    const bool &HLT_HISinglePhoton10();
    const bool &HLT_HISinglePhoton15();
    const bool &HLT_HISinglePhoton20();
    const bool &HLT_HISinglePhoton40();
    const bool &HLT_HISinglePhoton60();
    const bool &HLT_HT200();
    const bool &HLT_HT2000();
    const bool &HLT_HT200_DisplacedDijet40_DisplacedTrack();
    const bool &HLT_HT2500();
    const bool &HLT_HT250_CaloMET70();
    const bool &HLT_HT250_DisplacedDijet40_DisplacedTrack();
    const bool &HLT_HT275();
    const bool &HLT_HT300_Beamspot();
    const bool &HLT_HT325();
    const bool &HLT_HT350_DisplacedDijet40_DisplacedTrack();
    const bool &HLT_HT350_DisplacedDijet40_Inclusive();
    const bool &HLT_HT350_DisplacedDijet80_DisplacedTrack();
    const bool &HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack();
    const bool &HLT_HT400_DisplacedDijet40_DisplacedTrack();
    const bool &HLT_HT400_DisplacedDijet40_Inclusive();
    const bool &HLT_HT410to430();
    const bool &HLT_HT425();
    const bool &HLT_HT430_DisplacedDijet40_DisplacedTrack();
    const bool &HLT_HT430_DisplacedDijet60_DisplacedTrack();
    const bool &HLT_HT430to450();
    const bool &HLT_HT450_Beamspot();
    const bool &HLT_HT450to470();
    const bool &HLT_HT470to500();
    const bool &HLT_HT500_DisplacedDijet40_DisplacedTrack();
    const bool &HLT_HT500_DisplacedDijet40_Inclusive();
    const bool &HLT_HT500to550();
    const bool &HLT_HT550_DisplacedDijet40_Inclusive();
    const bool &HLT_HT550_DisplacedDijet60_Inclusive();
    const bool &HLT_HT550_DisplacedDijet80_Inclusive();
    const bool &HLT_HT550to650();
    const bool &HLT_HT575();
    const bool &HLT_HT650();
    const bool &HLT_HT650_DisplacedDijet60_Inclusive();
    const bool &HLT_HT650_DisplacedDijet80_Inclusive();
    const bool &HLT_HT750_DisplacedDijet80_Inclusive();
    const bool &HLT_HcalCalibration();
    const bool &HLT_HcalIsolatedbunch();
    const bool &HLT_HcalNZS();
    const bool &HLT_HcalPhiSym();
    const bool &HLT_IsoMu16_eta2p1_MET30();
    const bool &HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1();
    const bool &HLT_IsoMu17_eta2p1();
    const bool &HLT_IsoMu17_eta2p1_LooseIsoPFTau20();
    const bool &HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1();
    const bool &HLT_IsoMu18();
    const bool &HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20();
    const bool &HLT_IsoMu19_eta2p1_LooseIsoPFTau20();
    const bool &HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1();
    const bool &HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg();
    const bool &HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg();
    const bool &HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg();
    const bool &HLT_IsoMu20();
    const bool &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1();
    const bool &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1();
    const bool &HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1();
    const bool &HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1();
    const bool &HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1();
    const bool &HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1();
    const bool &HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1();
    const bool &HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1();
    const bool &HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg();
    const bool &HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg();
    const bool &HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg();
    const bool &HLT_IsoMu22();
    const bool &HLT_IsoMu22_eta2p1();
    const bool &HLT_IsoMu24();
    const bool &HLT_IsoMu24_TwoProngs35();
    const bool &HLT_IsoMu24_eta2p1();
    const bool &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr();
    const bool &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1();
    const bool &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1();
    const bool &HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1();
    const bool &HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1();
    const bool &HLT_IsoMu27();
    const bool &HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1();
    const bool &HLT_IsoMu27_MET90();
    const bool &HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1();
    const bool &HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1();
    const bool &HLT_IsoMu30();
    const bool &HLT_IsoTkMu18();
    const bool &HLT_IsoTkMu20();
    const bool &HLT_IsoTkMu22();
    const bool &HLT_IsoTkMu22_eta2p1();
    const bool &HLT_IsoTkMu24();
    const bool &HLT_IsoTkMu27();
    const bool &HLT_IsoTrackHB();
    const bool &HLT_IsoTrackHE();
    const bool &HLT_JetE30_NoBPTX();
    const bool &HLT_JetE30_NoBPTX3BX();
    const bool &HLT_JetE50_NoBPTX3BX();
    const bool &HLT_JetE70_NoBPTX3BX();
    const bool &HLT_L1BeamGasMinus();
    const bool &HLT_L1BeamGasPlus();
    const bool &HLT_L1BptxMinus();
    const bool &HLT_L1BptxPlus();
    const bool &HLT_L1BptxXOR();
    const bool &HLT_L1ETMHadSeeds();
    const bool &HLT_L1FatEvents();
    const bool &HLT_L1FatEvents_part0();
    const bool &HLT_L1FatEvents_part1();
    const bool &HLT_L1FatEvents_part2();
    const bool &HLT_L1FatEvents_part3();
    const bool &HLT_L1MinimumBiasHF_AND();
    const bool &HLT_L1MinimumBiasHF_OR();
    const bool &HLT_L1NotBptxOR();
    const bool &HLT_L1SingleMu18();
    const bool &HLT_L1SingleMu25();
    const bool &HLT_L1SingleMuOpen();
    const bool &HLT_L1SingleMuOpen_DT();
    const bool &HLT_L1UnpairedBunchBptxMinus();
    const bool &HLT_L1UnpairedBunchBptxPlus();
    const bool &HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142();
    const bool &HLT_L1_TripleJet_VBF();
    const bool &HLT_L2DoubleMu23_NoVertex();
    const bool &HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10();
    const bool &HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10();
    const bool &HLT_L2Mu10();
    const bool &HLT_L2Mu10_NoVertex_NoBPTX();
    const bool &HLT_L2Mu10_NoVertex_NoBPTX3BX();
    const bool &HLT_L2Mu23NoVtx_2Cha();
    const bool &HLT_L2Mu23NoVtx_2Cha_CosmicSeed();
    const bool &HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX();
    const bool &HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX();
    const bool &HLT_L2Mu50();
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1();
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110();
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120();
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80();
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90();
    const bool &HLT_MET100();
    const bool &HLT_MET105_IsoTrk50();
    const bool &HLT_MET120_IsoTrk50();
    const bool &HLT_MET150();
    const bool &HLT_MET200();
    const bool &HLT_MET250();
    const bool &HLT_MET300();
    const bool &HLT_MET600();
    const bool &HLT_MET60_IsoTrk35_Loose();
    const bool &HLT_MET700();
    const bool &HLT_MET75_IsoTrk50();
    const bool &HLT_MET90_IsoTrk50();
    const bool &HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1();
    const bool &HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr();
    const bool &HLT_MediumChargedIsoPFTau200HighPtRelaxedIso_Trk50_eta2p1();
    const bool &HLT_MediumChargedIsoPFTau220HighPtRelaxedIso_Trk50_eta2p1();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET140();
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90();
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight();
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight();
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight();
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight();
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight();
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight();
    const bool &HLT_Mu10_CentralPFJet30_BTagCSV_p13();
    const bool &HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60();
    const bool &HLT_Mu12();
    const bool &HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71();
    const bool &HLT_Mu12_DoublePhoton20();
    const bool &HLT_Mu12_IP6_part0();
    const bool &HLT_Mu12_IP6_part1();
    const bool &HLT_Mu12_IP6_part2();
    const bool &HLT_Mu12_IP6_part3();
    const bool &HLT_Mu12_IP6_part4();
    const bool &HLT_Mu12_Photon25_CaloIdL();
    const bool &HLT_Mu12_Photon25_CaloIdL_L1ISO();
    const bool &HLT_Mu12_Photon25_CaloIdL_L1OR();
    const bool &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ();
    const bool &HLT_Mu14er_PFMET100();
    const bool &HLT_Mu15();
    const bool &HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400();
    const bool &HLT_Mu15_IsoVVVL_PFHT350();
    const bool &HLT_Mu15_IsoVVVL_PFHT350_PFMET50();
    const bool &HLT_Mu15_IsoVVVL_PFHT400();
    const bool &HLT_Mu15_IsoVVVL_PFHT400_PFMET50();
    const bool &HLT_Mu15_IsoVVVL_PFHT450();
    const bool &HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5();
    const bool &HLT_Mu15_IsoVVVL_PFHT450_PFMET50();
    const bool &HLT_Mu15_IsoVVVL_PFHT600();
    const bool &HLT_Mu16_TkMu0_dEta18_Onia();
    const bool &HLT_Mu16_TkMu0_dEta18_Phi();
    const bool &HLT_Mu16_eta2p1_MET30();
    const bool &HLT_Mu17();
    const bool &HLT_Mu17_Mu8();
    const bool &HLT_Mu17_Mu8_DZ();
    const bool &HLT_Mu17_Mu8_SameSign();
    const bool &HLT_Mu17_Mu8_SameSign_DZ();
    const bool &HLT_Mu17_Photon22_CaloIdL_L1ISO();
    const bool &HLT_Mu17_Photon30_CaloIdL_L1ISO();
    const bool &HLT_Mu17_Photon30_IsoCaloId();
    const bool &HLT_Mu17_Photon35_CaloIdL_L1ISO();
    const bool &HLT_Mu17_TkMu8_DZ();
    const bool &HLT_Mu17_TrkIsoVVL();
    const bool &HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL();
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ();
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8();
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8();
    const bool &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL();
    const bool &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ();
    const bool &HLT_Mu18_Mu9();
    const bool &HLT_Mu18_Mu9_DZ();
    const bool &HLT_Mu18_Mu9_SameSign();
    const bool &HLT_Mu18_Mu9_SameSign_DZ();
    const bool &HLT_Mu19();
    const bool &HLT_Mu19_TrkIsoVVL();
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL();
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ();
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8();
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8();
    const bool &HLT_Mu20();
    const bool &HLT_Mu20_Mu10();
    const bool &HLT_Mu20_Mu10_DZ();
    const bool &HLT_Mu20_Mu10_SameSign();
    const bool &HLT_Mu20_Mu10_SameSign_DZ();
    const bool &HLT_Mu20_TkMu0_Phi();
    const bool &HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL();
    const bool &HLT_Mu23_Mu12();
    const bool &HLT_Mu23_Mu12_DZ();
    const bool &HLT_Mu23_Mu12_SameSign();
    const bool &HLT_Mu23_Mu12_SameSign_DZ();
    const bool &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ();
    const bool &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ();
    const bool &HLT_Mu24_eta2p1();
    const bool &HLT_Mu25_TkMu0_Onia();
    const bool &HLT_Mu25_TkMu0_Phi();
    const bool &HLT_Mu25_TkMu0_dEta18_Onia();
    const bool &HLT_Mu27();
    const bool &HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL();
    const bool &HLT_Mu27_Ele37_CaloIdL_MW();
    const bool &HLT_Mu27_TkMu8();
    const bool &HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL();
    const bool &HLT_Mu28NoFiltersNoVtx_CentralCaloJet40();
    const bool &HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose();
    const bool &HLT_Mu300();
    const bool &HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL();
    const bool &HLT_Mu30_TkMu0_Psi();
    const bool &HLT_Mu30_TkMu0_Upsilon();
    const bool &HLT_Mu30_TkMu11();
    const bool &HLT_Mu30_eta2p1_PFJet150_PFJet50();
    const bool &HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose();
    const bool &HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight();
    const bool &HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL();
    const bool &HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL();
    const bool &HLT_Mu350();
    const bool &HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL();
    const bool &HLT_Mu37_Ele27_CaloIdL_MW();
    const bool &HLT_Mu37_TkMu27();
    const bool &HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose();
    const bool &HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight();
    const bool &HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL();
    const bool &HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose();
    const bool &HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL();
    const bool &HLT_Mu3_L1SingleMu5orSingleMu7();
    const bool &HLT_Mu3_PFJet40();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight();
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight();
    const bool &HLT_Mu3er_PFHT140_PFMET125();
    const bool &HLT_Mu40_TkMu11();
    const bool &HLT_Mu40_eta2p1_PFJet200_PFJet50();
    const bool &HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL();
    const bool &HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL();
    const bool &HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL();
    const bool &HLT_Mu45_eta2p1();
    const bool &HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL();
    const bool &HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60();
    const bool &HLT_Mu50();
    const bool &HLT_Mu50_IsoVVVL_PFHT400();
    const bool &HLT_Mu50_IsoVVVL_PFHT450();
    const bool &HLT_Mu55();
    const bool &HLT_Mu6_PFHT200_PFMET100();
    const bool &HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067();
    const bool &HLT_Mu7_IP4_part0();
    const bool &HLT_Mu7_IP4_part1();
    const bool &HLT_Mu7_IP4_part2();
    const bool &HLT_Mu7_IP4_part3();
    const bool &HLT_Mu7_IP4_part4();
    const bool &HLT_Mu7p5_L2Mu2_Jpsi();
    const bool &HLT_Mu7p5_L2Mu2_Upsilon();
    const bool &HLT_Mu7p5_Track2_Jpsi();
    const bool &HLT_Mu7p5_Track2_Upsilon();
    const bool &HLT_Mu7p5_Track3p5_Jpsi();
    const bool &HLT_Mu7p5_Track3p5_Upsilon();
    const bool &HLT_Mu7p5_Track7_Jpsi();
    const bool &HLT_Mu7p5_Track7_Upsilon();
    const bool &HLT_Mu8();
    const bool &HLT_Mu8_DiEle12_CaloIdL_TrackIdL();
    const bool &HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ();
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250();
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300();
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350();
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ();
    const bool &HLT_Mu8_IP3_part0();
    const bool &HLT_Mu8_IP3_part1();
    const bool &HLT_Mu8_IP3_part2();
    const bool &HLT_Mu8_IP3_part3();
    const bool &HLT_Mu8_IP3_part4();
    const bool &HLT_Mu8_IP5_part0();
    const bool &HLT_Mu8_IP5_part1();
    const bool &HLT_Mu8_IP5_part2();
    const bool &HLT_Mu8_IP5_part3();
    const bool &HLT_Mu8_IP5_part4();
    const bool &HLT_Mu8_IP6_part0();
    const bool &HLT_Mu8_IP6_part1();
    const bool &HLT_Mu8_IP6_part2();
    const bool &HLT_Mu8_IP6_part3();
    const bool &HLT_Mu8_IP6_part4();
    const bool &HLT_Mu8_TrkIsoVVL();
    const bool &HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60();
    const bool &HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL();
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ();
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30();
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5();
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30();
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5();
    const bool &HLT_Mu9_IP4_part0();
    const bool &HLT_Mu9_IP4_part1();
    const bool &HLT_Mu9_IP4_part2();
    const bool &HLT_Mu9_IP4_part3();
    const bool &HLT_Mu9_IP4_part4();
    const bool &HLT_Mu9_IP5_part0();
    const bool &HLT_Mu9_IP5_part1();
    const bool &HLT_Mu9_IP5_part2();
    const bool &HLT_Mu9_IP5_part3();
    const bool &HLT_Mu9_IP5_part4();
    const bool &HLT_Mu9_IP6_part0();
    const bool &HLT_Mu9_IP6_part1();
    const bool &HLT_Mu9_IP6_part2();
    const bool &HLT_Mu9_IP6_part3();
    const bool &HLT_Mu9_IP6_part4();
    const bool &HLT_OldMu100();
    const bool &HLT_PFHT1050();
    const bool &HLT_PFHT125();
    const bool &HLT_PFHT180();
    const bool &HLT_PFHT200();
    const bool &HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57();
    const bool &HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63();
    const bool &HLT_PFHT200_PFAlphaT0p51();
    const bool &HLT_PFHT250();
    const bool &HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55();
    const bool &HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58();
    const bool &HLT_PFHT300();
    const bool &HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53();
    const bool &HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54();
    const bool &HLT_PFHT300_PFMET100();
    const bool &HLT_PFHT300_PFMET110();
    const bool &HLT_PFHT330PT30_QuadPFJet_75_60_45_40();
    const bool &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5();
    const bool &HLT_PFHT350();
    const bool &HLT_PFHT350MinPFJet15();
    const bool &HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52();
    const bool &HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53();
    const bool &HLT_PFHT370();
    const bool &HLT_PFHT400();
    const bool &HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51();
    const bool &HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52();
    const bool &HLT_PFHT400_SixJet30();
    const bool &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056();
    const bool &HLT_PFHT400_SixPFJet32();
    const bool &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94();
    const bool &HLT_PFHT430();
    const bool &HLT_PFHT450_SixJet40();
    const bool &HLT_PFHT450_SixJet40_BTagCSV_p056();
    const bool &HLT_PFHT450_SixPFJet36();
    const bool &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59();
    const bool &HLT_PFHT475();
    const bool &HLT_PFHT500_PFMET100_PFMHT100_IDTight();
    const bool &HLT_PFHT500_PFMET110_PFMHT110_IDTight();
    const bool &HLT_PFHT510();
    const bool &HLT_PFHT550_4JetPt50();
    const bool &HLT_PFHT590();
    const bool &HLT_PFHT600();
    const bool &HLT_PFHT650();
    const bool &HLT_PFHT650_4JetPt50();
    const bool &HLT_PFHT650_WideJetMJJ900DEtaJJ1p5();
    const bool &HLT_PFHT650_WideJetMJJ950DEtaJJ1p5();
    const bool &HLT_PFHT680();
    const bool &HLT_PFHT700_PFMET85_PFMHT85_IDTight();
    const bool &HLT_PFHT700_PFMET95_PFMHT95_IDTight();
    const bool &HLT_PFHT750_4JetPt50();
    const bool &HLT_PFHT750_4JetPt70();
    const bool &HLT_PFHT750_4JetPt80();
    const bool &HLT_PFHT780();
    const bool &HLT_PFHT800();
    const bool &HLT_PFHT800_4JetPt50();
    const bool &HLT_PFHT800_PFMET75_PFMHT75_IDTight();
    const bool &HLT_PFHT800_PFMET85_PFMHT85_IDTight();
    const bool &HLT_PFHT850_4JetPt50();
    const bool &HLT_PFHT890();
    const bool &HLT_PFHT900();
    const bool &HLT_PFJet140();
    const bool &HLT_PFJet15();
    const bool &HLT_PFJet15_NoCaloMatched();
    const bool &HLT_PFJet200();
    const bool &HLT_PFJet25();
    const bool &HLT_PFJet25_NoCaloMatched();
    const bool &HLT_PFJet260();
    const bool &HLT_PFJet320();
    const bool &HLT_PFJet40();
    const bool &HLT_PFJet400();
    const bool &HLT_PFJet450();
    const bool &HLT_PFJet500();
    const bool &HLT_PFJet550();
    const bool &HLT_PFJet60();
    const bool &HLT_PFJet80();
    const bool &HLT_PFJetFwd140();
    const bool &HLT_PFJetFwd15();
    const bool &HLT_PFJetFwd200();
    const bool &HLT_PFJetFwd25();
    const bool &HLT_PFJetFwd260();
    const bool &HLT_PFJetFwd320();
    const bool &HLT_PFJetFwd40();
    const bool &HLT_PFJetFwd400();
    const bool &HLT_PFJetFwd450();
    const bool &HLT_PFJetFwd500();
    const bool &HLT_PFJetFwd60();
    const bool &HLT_PFJetFwd80();
    const bool &HLT_PFMET100_PFMHT100_IDTight();
    const bool &HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned();
    const bool &HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1();
    const bool &HLT_PFMET100_PFMHT100_IDTight_PFHT60();
    const bool &HLT_PFMET110_PFMHT110_IDTight();
    const bool &HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1();
    const bool &HLT_PFMET120_BTagCSV_p067();
    const bool &HLT_PFMET120_Mu5();
    const bool &HLT_PFMET120_PFMHT120_IDTight();
    const bool &HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1();
    const bool &HLT_PFMET120_PFMHT120_IDTight_PFHT60();
    const bool &HLT_PFMET130_PFMHT130_IDTight();
    const bool &HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1();
    const bool &HLT_PFMET140_PFMHT140_IDTight();
    const bool &HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1();
    const bool &HLT_PFMET170_BeamHaloCleaned();
    const bool &HLT_PFMET170_HBHECleaned();
    const bool &HLT_PFMET170_HBHE_BeamHaloCleaned();
    const bool &HLT_PFMET170_JetIdCleaned();
    const bool &HLT_PFMET170_NoiseCleaned();
    const bool &HLT_PFMET170_NotCleaned();
    const bool &HLT_PFMET200_HBHECleaned();
    const bool &HLT_PFMET200_HBHE_BeamHaloCleaned();
    const bool &HLT_PFMET200_NotCleaned();
    const bool &HLT_PFMET250_HBHECleaned();
    const bool &HLT_PFMET300();
    const bool &HLT_PFMET300_HBHECleaned();
    const bool &HLT_PFMET400();
    const bool &HLT_PFMET500();
    const bool &HLT_PFMET600();
    const bool &HLT_PFMET90_PFMHT90_IDTight();
    const bool &HLT_PFMETNoMu100_PFMHTNoMu100_IDTight();
    const bool &HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60();
    const bool &HLT_PFMETNoMu110_PFMHTNoMu110_IDTight();
    const bool &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight();
    const bool &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60();
    const bool &HLT_PFMETNoMu130_PFMHTNoMu130_IDTight();
    const bool &HLT_PFMETNoMu140_PFMHTNoMu140_IDTight();
    const bool &HLT_PFMETNoMu90_PFMHTNoMu90_IDTight();
    const bool &HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60();
    const bool &HLT_PFMETTypeOne110_PFMHT110_IDTight();
    const bool &HLT_PFMETTypeOne120_PFMHT120_IDTight();
    const bool &HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60();
    const bool &HLT_PFMETTypeOne130_PFMHT130_IDTight();
    const bool &HLT_PFMETTypeOne140_PFMHT140_IDTight();
    const bool &HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned();
    const bool &HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned();
    const bool &HLT_PFTau120_eta2p1();
    const bool &HLT_PFTau140_eta2p1();
    const bool &HLT_Photon100EBHE10();
    const bool &HLT_Photon100EB_TightID_TightIso();
    const bool &HLT_Photon100EEHE10();
    const bool &HLT_Photon100EE_TightID_TightIso();
    const bool &HLT_Photon110EB_TightID_TightIso();
    const bool &HLT_Photon120();
    const bool &HLT_Photon120EB_TightID_TightIso();
    const bool &HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40();
    const bool &HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF();
    const bool &HLT_Photon120_R9Id90_HE10_IsoM();
    const bool &HLT_Photon125();
    const bool &HLT_Photon135_PFMET100();
    const bool &HLT_Photon150();
    const bool &HLT_Photon165_HE10();
    const bool &HLT_Photon165_R9Id90_HE10_IsoM();
    const bool &HLT_Photon175();
    const bool &HLT_Photon20();
    const bool &HLT_Photon200();
    const bool &HLT_Photon20_CaloIdVL_IsoL();
    const bool &HLT_Photon20_HoverELoose();
    const bool &HLT_Photon22();
    const bool &HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40();
    const bool &HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF();
    const bool &HLT_Photon22_R9Id90_HE10_IsoM();
    const bool &HLT_Photon250_NoHE();
    const bool &HLT_Photon26_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon16_AND_HE10_R9Id65_Eta2_Mass60();
    const bool &HLT_Photon30();
    const bool &HLT_Photon300_NoHE();
    const bool &HLT_Photon30_HoverELoose();
    const bool &HLT_Photon30_R9Id90_HE10_IsoM();
    const bool &HLT_Photon33();
    const bool &HLT_Photon35_TwoProngs35();
    const bool &HLT_Photon36();
    const bool &HLT_Photon36_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon22_AND_HE10_R9Id65_Eta2_Mass15();
    const bool &HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40();
    const bool &HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF();
    const bool &HLT_Photon36_R9Id90_HE10_IsoM();
    const bool &HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15();
    const bool &HLT_Photon50();
    const bool &HLT_Photon500();
    const bool &HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40();
    const bool &HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF();
    const bool &HLT_Photon50_R9Id90_HE10_IsoM();
    const bool &HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50();
    const bool &HLT_Photon600();
    const bool &HLT_Photon60_R9Id90_CaloIdL_IsoL();
    const bool &HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL();
    const bool &HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15();
    const bool &HLT_Photon75();
    const bool &HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40();
    const bool &HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF();
    const bool &HLT_Photon75_R9Id90_HE10_IsoM();
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3();
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3();
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3();
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3();
    const bool &HLT_Photon90();
    const bool &HLT_Photon90_CaloIdL_HT300();
    const bool &HLT_Photon90_CaloIdL_PFHT500();
    const bool &HLT_Photon90_CaloIdL_PFHT600();
    const bool &HLT_Photon90_CaloIdL_PFHT700();
    const bool &HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40();
    const bool &HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF();
    const bool &HLT_Photon90_R9Id90_HE10_IsoM();
    const bool &HLT_Physics();
    const bool &HLT_Physics_part0();
    const bool &HLT_Physics_part1();
    const bool &HLT_Physics_part2();
    const bool &HLT_Physics_part3();
    const bool &HLT_Physics_part4();
    const bool &HLT_Physics_part5();
    const bool &HLT_Physics_part6();
    const bool &HLT_Physics_part7();
    const bool &HLT_PixelTracks_Multiplicity110ForEndOfFill();
    const bool &HLT_PixelTracks_Multiplicity135ForEndOfFill();
    const bool &HLT_PixelTracks_Multiplicity160ForEndOfFill();
    const bool &HLT_PixelTracks_Multiplicity60ForEndOfFill();
    const bool &HLT_PixelTracks_Multiplicity85ForEndOfFill();
    const bool &HLT_QuadJet45_DoubleBTagCSV_p087();
    const bool &HLT_QuadJet45_TripleBTagCSV_p087();
    const bool &HLT_QuadMuon0_Dimuon0_Jpsi();
    const bool &HLT_QuadMuon0_Dimuon0_Upsilon();
    const bool &HLT_QuadPFJet103_88_75_15();
    const bool &HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1();
    const bool &HLT_QuadPFJet103_88_75_15_PFBTagDeepCSV_1p3_VBF2();
    const bool &HLT_QuadPFJet105_88_76_15();
    const bool &HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1();
    const bool &HLT_QuadPFJet105_88_76_15_PFBTagDeepCSV_1p3_VBF2();
    const bool &HLT_QuadPFJet111_90_80_15();
    const bool &HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1();
    const bool &HLT_QuadPFJet111_90_80_15_PFBTagDeepCSV_1p3_VBF2();
    const bool &HLT_QuadPFJet98_83_71_15();
    const bool &HLT_QuadPFJet98_83_71_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1();
    const bool &HLT_QuadPFJet98_83_71_15_PFBTagDeepCSV_1p3_VBF2();
    const bool &HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460();
    const bool &HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500();
    const bool &HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200();
    const bool &HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240();
    const bool &HLT_QuadPFJet_VBF();
    const bool &HLT_Random();
    const bool &HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200();
    const bool &HLT_Rsq0p02_MR400_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200();
    const bool &HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200();
    const bool &HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200();
    const bool &HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200();
    const bool &HLT_Rsq0p25();
    const bool &HLT_Rsq0p25_Calo();
    const bool &HLT_Rsq0p30();
    const bool &HLT_Rsq0p35();
    const bool &HLT_Rsq0p40();
    const bool &HLT_RsqMR240_Rsq0p09_MR200();
    const bool &HLT_RsqMR240_Rsq0p09_MR200_4jet();
    const bool &HLT_RsqMR240_Rsq0p09_MR200_4jet_Calo();
    const bool &HLT_RsqMR240_Rsq0p09_MR200_Calo();
    const bool &HLT_RsqMR270_Rsq0p09_MR200();
    const bool &HLT_RsqMR270_Rsq0p09_MR200_4jet();
    const bool &HLT_RsqMR300_Rsq0p09_MR200();
    const bool &HLT_RsqMR300_Rsq0p09_MR200_4jet();
    const bool &HLT_RsqMR320_Rsq0p09_MR200();
    const bool &HLT_RsqMR320_Rsq0p09_MR200_4jet();
    const bool &HLT_SingleCentralPFJet170_CFMax0p1();
    const bool &HLT_SingleJet30_Mu12_SinglePFJet40();
    const bool &HLT_SinglePhoton10_Eta3p1ForPPRef();
    const bool &HLT_SinglePhoton20_Eta3p1ForPPRef();
    const bool &HLT_SinglePhoton30_Eta3p1ForPPRef();
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15();
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1();
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15();
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1();
    const bool &HLT_TkMu100();
    const bool &HLT_TkMu17();
    const bool &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL();
    const bool &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ();
    const bool &HLT_TkMu20();
    const bool &HLT_TkMu24_eta2p1();
    const bool &HLT_TkMu27();
    const bool &HLT_TkMu50();
    const bool &HLT_Trimuon5_3p5_2_Upsilon_Muon();
    const bool &HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon();
    const bool &HLT_TripleJet110_35_35_Mjj650_PFMET110();
    const bool &HLT_TripleJet110_35_35_Mjj650_PFMET120();
    const bool &HLT_TripleJet110_35_35_Mjj650_PFMET130();
    const bool &HLT_TripleMu_10_5_5_DZ();
    const bool &HLT_TripleMu_12_10_5();
    const bool &HLT_TripleMu_5_3_3();
    const bool &HLT_TripleMu_5_3_3_Mass3p8_DCA();
    const bool &HLT_TripleMu_5_3_3_Mass3p8_DZ();
    const bool &HLT_TriplePhoton_20_20_20_CaloIdLV2();
    const bool &HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL();
    const bool &HLT_TriplePhoton_30_30_10_CaloIdLV2();
    const bool &HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL();
    const bool &HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL();
    const bool &HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx();
    const bool &HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx();
    const bool &HLT_TrkMu16NoFiltersNoVtx();
    const bool &HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx();
    const bool &HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx();
    const bool &HLT_TrkMu6NoFiltersNoVtx();
    const bool &HLT_UncorrectedJetE30_NoBPTX();
    const bool &HLT_UncorrectedJetE30_NoBPTX3BX();
    const bool &HLT_UncorrectedJetE60_NoBPTX3BX();
    const bool &HLT_UncorrectedJetE70_NoBPTX3BX();
    const bool &HLT_VBF_DisplacedJet40_DisplacedTrack();
    const bool &HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5();
    const bool &HLT_VBF_DisplacedJet40_Hadronic();
    const bool &HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack();
    const bool &HLT_VBF_DisplacedJet40_TightID_DisplacedTrack();
    const bool &HLT_VBF_DisplacedJet40_TightID_Hadronic();
    const bool &HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack();
    const bool &HLT_VBF_DisplacedJet40_VTightID_Hadronic();
    const bool &HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack();
    const bool &HLT_VBF_DisplacedJet40_VVTightID_Hadronic();
    const bool &HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1();
    const bool &HLT_VBF_DoubleMediumChargedIsoPFTauHPS20_Trk1_eta2p1();
    const bool &HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1();
    const bool &HLT_VLooseIsoPFTau120_Trk50_eta2p1();
    const bool &HLT_VLooseIsoPFTau140_Trk50_eta2p1();
    const bool &HLT_ZeroBias();
    const bool &HLT_ZeroBias_Alignment();
    const bool &HLT_ZeroBias_Beamspot();
    const bool &HLT_ZeroBias_FirstBXAfterTrain();
    const bool &HLT_ZeroBias_FirstCollisionAfterAbortGap();
    const bool &HLT_ZeroBias_FirstCollisionAfterAbortGap_TCDS();
    const bool &HLT_ZeroBias_FirstCollisionAfterAbortGap_copy();
    const bool &HLT_ZeroBias_FirstCollisionInTrain();
    const bool &HLT_ZeroBias_IsolatedBunches();
    const bool &HLT_ZeroBias_LastCollisionInTrain();
    const bool &HLT_ZeroBias_part0();
    const bool &HLT_ZeroBias_part1();
    const bool &HLT_ZeroBias_part2();
    const bool &HLT_ZeroBias_part3();
    const bool &HLT_ZeroBias_part4();
    const bool &HLT_ZeroBias_part5();
    const bool &HLT_ZeroBias_part6();
    const bool &HLT_ZeroBias_part7();
    const bool &HLTriggerFinalPath();
    const bool &HLTriggerFirstPath();
    const float &HTXS_Higgs_pt();
    const float &HTXS_Higgs_y();
    const UChar_t &HTXS_njets25();
    const UChar_t &HTXS_njets30();
    const int &HTXS_stage1_1_cat_pTjet25GeV();
    const int &HTXS_stage1_1_cat_pTjet30GeV();
    const int &HTXS_stage1_1_fine_cat_pTjet25GeV();
    const int &HTXS_stage1_1_fine_cat_pTjet30GeV();
    const int &HTXS_stage1_2_cat_pTjet25GeV();
    const int &HTXS_stage1_2_cat_pTjet30GeV();
    const int &HTXS_stage1_2_fine_cat_pTjet25GeV();
    const int &HTXS_stage1_2_fine_cat_pTjet30GeV();
    const int &HTXS_stage_0();
    const int &HTXS_stage_1_pTjet25();
    const int &HTXS_stage_1_pTjet30();
    const vector<float> &IsoTrack_dxy();
    const vector<float> &IsoTrack_dz();
    const vector<float> &IsoTrack_eta();
    const vector<int> &IsoTrack_fromPV();
    const vector<bool> &IsoTrack_isFromLostTrack();
    const vector<bool> &IsoTrack_isHighPurityTrack();
    const vector<bool> &IsoTrack_isPFcand();
    const vector<float> &IsoTrack_miniPFRelIso_all();
    const vector<float> &IsoTrack_miniPFRelIso_chg();
    const vector<int> &IsoTrack_pdgId();
    const vector<float> &IsoTrack_pfRelIso03_all();
    const vector<float> &IsoTrack_pfRelIso03_chg();
    const vector<float> &IsoTrack_phi();
    const vector<float> &IsoTrack_pt();
    const vector<float> &Jet_area();
    const vector<float> &Jet_bRegCorr();
    const vector<float> &Jet_bRegRes();
    const vector<float> &Jet_btagCMVA();
    const vector<float> &Jet_btagCSVV2();
    const vector<float> &Jet_btagDeepB();
    const vector<float> &Jet_btagDeepC();
    const vector<float> &Jet_btagDeepFlavB();
    const vector<float> &Jet_btagDeepFlavC();
    const vector<float> &Jet_cRegCorr();
    const vector<float> &Jet_cRegRes();
    const vector<float> &Jet_chEmEF();
    const vector<float> &Jet_chFPV0EF();
    const vector<float> &Jet_chFPV1EF();
    const vector<float> &Jet_chFPV2EF();
    const vector<float> &Jet_chFPV3EF();
    const vector<float> &Jet_chHEF();
    const vector<UChar_t> &Jet_cleanmask();
    const vector<int> &Jet_electronIdx1();
    const vector<int> &Jet_electronIdx2();
    const vector<float> &Jet_eta();
    const vector<int> &Jet_genJetIdx();
    const vector<int> &Jet_hadronFlavour();
    const vector<int> &Jet_jetId();
    const vector<float> &Jet_mass();
    const vector<float> &Jet_muEF();
    const vector<int> &Jet_muonIdx1();
    const vector<int> &Jet_muonIdx2();
    const vector<float> &Jet_muonSubtrFactor();
    const vector<int> &Jet_nConstituents();
    const vector<int> &Jet_nElectrons();
    const vector<int> &Jet_nMuons();
    const vector<float> &Jet_neEmEF();
    const vector<float> &Jet_neHEF();
    const vector<LorentzVector> &Jet_p4();
    const vector<int> &Jet_partonFlavour();
    const vector<float> &Jet_phi();
    const vector<float> &Jet_pt();
    const vector<int> &Jet_puId();
    const vector<float> &Jet_puIdDisc();
    const vector<float> &Jet_qgl();
    const vector<float> &Jet_rawFactor();
    const float &L1PreFiringWeight_Dn();
    const float &L1PreFiringWeight_Nom();
    const float &L1PreFiringWeight_Up();
    const bool &L1Reco_step();
    const bool &L1_AlwaysTrue();
    const bool &L1_BPTX_AND_Ref1_VME();
    const bool &L1_BPTX_AND_Ref3_VME();
    const bool &L1_BPTX_AND_Ref4_VME();
    const bool &L1_BPTX_BeamGas_B1_VME();
    const bool &L1_BPTX_BeamGas_B2_VME();
    const bool &L1_BPTX_BeamGas_Ref1_VME();
    const bool &L1_BPTX_BeamGas_Ref2_VME();
    const bool &L1_BPTX_NotOR_VME();
    const bool &L1_BPTX_OR_Ref3_VME();
    const bool &L1_BPTX_OR_Ref4_VME();
    const bool &L1_BPTX_RefAND_VME();
    const bool &L1_BRIL_TRIG0_AND();
    const bool &L1_BRIL_TRIG0_FstBunchInTrain();
    const bool &L1_BRIL_TRIG0_OR();
    const bool &L1_BRIL_TRIG0_delayedAND();
    const bool &L1_BeamGasB1();
    const bool &L1_BeamGasB2();
    const bool &L1_BeamGasMinus();
    const bool &L1_BeamGasPlus();
    const bool &L1_BptxMinus();
    const bool &L1_BptxOR();
    const bool &L1_BptxPlus();
    const bool &L1_BptxXOR();
    const bool &L1_CASTOR_Gap_BptxAND();
    const bool &L1_CASTOR_HaloMuon();
    const bool &L1_CASTOR_HaloMuon_BptxAND();
    const bool &L1_CASTOR_HighJet_BptxAND();
    const bool &L1_CASTOR_MediumJet_BptxAND();
    const bool &L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142();
    const bool &L1_DoubleEG6_HTT255();
    const bool &L1_DoubleEG8er2p5_HTT260er();
    const bool &L1_DoubleEG8er2p5_HTT280er();
    const bool &L1_DoubleEG8er2p5_HTT300er();
    const bool &L1_DoubleEG8er2p5_HTT320er();
    const bool &L1_DoubleEG8er2p5_HTT340er();
    const bool &L1_DoubleEG_15_10();
    const bool &L1_DoubleEG_15_10_er2p5();
    const bool &L1_DoubleEG_18_17();
    const bool &L1_DoubleEG_20_10_er2p5();
    const bool &L1_DoubleEG_20_18();
    const bool &L1_DoubleEG_22_10();
    const bool &L1_DoubleEG_22_10_er2p5();
    const bool &L1_DoubleEG_22_12();
    const bool &L1_DoubleEG_22_15();
    const bool &L1_DoubleEG_23_10();
    const bool &L1_DoubleEG_24_17();
    const bool &L1_DoubleEG_25_12();
    const bool &L1_DoubleEG_25_12_er2p5();
    const bool &L1_DoubleEG_25_14_er2p5();
    const bool &L1_DoubleEG_27_14_er2p5();
    const bool &L1_DoubleEG_LooseIso20_10_er2p5();
    const bool &L1_DoubleEG_LooseIso22_10_er2p5();
    const bool &L1_DoubleEG_LooseIso22_12_er2p5();
    const bool &L1_DoubleEG_LooseIso25_12_er2p5();
    const bool &L1_DoubleIsoTau28er();
    const bool &L1_DoubleIsoTau30er();
    const bool &L1_DoubleIsoTau32er();
    const bool &L1_DoubleIsoTau32er2p1();
    const bool &L1_DoubleIsoTau33er();
    const bool &L1_DoubleIsoTau34er();
    const bool &L1_DoubleIsoTau34er2p1();
    const bool &L1_DoubleIsoTau35er();
    const bool &L1_DoubleIsoTau36er();
    const bool &L1_DoubleIsoTau36er2p1();
    const bool &L1_DoubleJet100er2p3_dEta_Max1p6();
    const bool &L1_DoubleJet100er2p5();
    const bool &L1_DoubleJet112er2p3_dEta_Max1p6();
    const bool &L1_DoubleJet120er2p5();
    const bool &L1_DoubleJet12_ForwardBackward();
    const bool &L1_DoubleJet150er2p5();
    const bool &L1_DoubleJet16_ForwardBackward();
    const bool &L1_DoubleJet30_Mj30j30_400_Mu10();
    const bool &L1_DoubleJet30_Mj30j30_400_Mu6();
    const bool &L1_DoubleJet30er2p5_Mass_Min150_dEta_Max1p5();
    const bool &L1_DoubleJet30er2p5_Mass_Min200_dEta_Max1p5();
    const bool &L1_DoubleJet30er2p5_Mass_Min250_dEta_Max1p5();
    const bool &L1_DoubleJet30er2p5_Mass_Min300_dEta_Max1p5();
    const bool &L1_DoubleJet30er2p5_Mass_Min330_dEta_Max1p5();
    const bool &L1_DoubleJet30er2p5_Mass_Min360_dEta_Max1p5();
    const bool &L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp();
    const bool &L1_DoubleJet40er2p5();
    const bool &L1_DoubleJet8_ForwardBackward();
    const bool &L1_DoubleJetC100();
    const bool &L1_DoubleJetC112();
    const bool &L1_DoubleJetC120();
    const bool &L1_DoubleJetC40();
    const bool &L1_DoubleJetC50();
    const bool &L1_DoubleJetC60();
    const bool &L1_DoubleJetC60_ETM60();
    const bool &L1_DoubleJetC80();
    const bool &L1_DoubleJet_100_30_DoubleJet30_Mass_Min620();
    const bool &L1_DoubleJet_100_30_Mj30j30_620();
    const bool &L1_DoubleJet_110_35_DoubleJet35_Mass_Min620();
    const bool &L1_DoubleJet_115_40_DoubleJet40_Mass_Min620();
    const bool &L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_Jet60TT28();
    const bool &L1_DoubleJet_120_45_DoubleJet45_Mass_Min620();
    const bool &L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_Jet60TT28();
    const bool &L1_DoubleJet_80_30_Mass_Min420_DoubleMu0_SQ();
    const bool &L1_DoubleJet_80_30_Mass_Min420_IsoTau40_RmOvlp();
    const bool &L1_DoubleJet_80_30_Mass_Min420_Mu8();
    const bool &L1_DoubleJet_90_30_DoubleJet30_Mass_Min620();
    const bool &L1_DoubleJet_90_30_Mj30j30_620();
    const bool &L1_DoubleLooseIsoEG22er2p1();
    const bool &L1_DoubleLooseIsoEG24er2p1();
    const bool &L1_DoubleMu0();
    const bool &L1_DoubleMu0_ETM40();
    const bool &L1_DoubleMu0_ETM55();
    const bool &L1_DoubleMu0_ETM60();
    const bool &L1_DoubleMu0_ETM65();
    const bool &L1_DoubleMu0_ETM70();
    const bool &L1_DoubleMu0_Mass_Min1();
    const bool &L1_DoubleMu0_OQ();
    const bool &L1_DoubleMu0_SQ();
    const bool &L1_DoubleMu0_SQ_OS();
    const bool &L1_DoubleMu0_dR_Max1p6_Jet90er2p5_dR_Max0p8();
    const bool &L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4();
    const bool &L1_DoubleMu0er1p4_dEta_Max1p8_OS();
    const bool &L1_DoubleMu0er1p5_SQ();
    const bool &L1_DoubleMu0er1p5_SQ_OS();
    const bool &L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4();
    const bool &L1_DoubleMu0er1p5_SQ_dR_Max1p4();
    const bool &L1_DoubleMu0er1p6_dEta_Max1p8();
    const bool &L1_DoubleMu0er1p6_dEta_Max1p8_OS();
    const bool &L1_DoubleMu0er2p0_SQ_OS_dR_Max1p4();
    const bool &L1_DoubleMu0er2p0_SQ_dR_Max1p4();
    const bool &L1_DoubleMu10_SQ();
    const bool &L1_DoubleMu18er2p1();
    const bool &L1_DoubleMu3_OS_DoubleEG7p5Upsilon();
    const bool &L1_DoubleMu3_SQ_ETMHF50_HTT60er();
    const bool &L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5();
    const bool &L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_OR_DoubleJet40er2p5();
    const bool &L1_DoubleMu3_SQ_ETMHF60_Jet60er2p5();
    const bool &L1_DoubleMu3_SQ_HTT220er();
    const bool &L1_DoubleMu3_SQ_HTT240er();
    const bool &L1_DoubleMu3_SQ_HTT260er();
    const bool &L1_DoubleMu3_dR_Max1p6_Jet90er2p5_dR_Max0p8();
    const bool &L1_DoubleMu4_SQ_EG9er2p5();
    const bool &L1_DoubleMu4_SQ_OS();
    const bool &L1_DoubleMu4_SQ_OS_dR_Max1p2();
    const bool &L1_DoubleMu4p5_SQ_OS();
    const bool &L1_DoubleMu4p5_SQ_OS_dR_Max1p2();
    const bool &L1_DoubleMu4p5er2p0_SQ_OS();
    const bool &L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18();
    const bool &L1_DoubleMu5Upsilon_OS_DoubleEG3();
    const bool &L1_DoubleMu5_SQ_EG9er2p5();
    const bool &L1_DoubleMu7_EG14();
    const bool &L1_DoubleMu7_EG7();
    const bool &L1_DoubleMu9_SQ();
    const bool &L1_DoubleMuOpen();
    const bool &L1_DoubleMu_10_0_dEta_Max1p8();
    const bool &L1_DoubleMu_10_3p5();
    const bool &L1_DoubleMu_10_Open();
    const bool &L1_DoubleMu_11_4();
    const bool &L1_DoubleMu_12_5();
    const bool &L1_DoubleMu_12_8();
    const bool &L1_DoubleMu_13_6();
    const bool &L1_DoubleMu_15_5();
    const bool &L1_DoubleMu_15_5_SQ();
    const bool &L1_DoubleMu_15_7();
    const bool &L1_DoubleMu_15_7_Mass_Min1();
    const bool &L1_DoubleMu_15_7_SQ();
    const bool &L1_DoubleTau50er();
    const bool &L1_DoubleTau70er();
    const bool &L1_DoubleTau70er2p1();
    const bool &L1_EG25er_HTT125();
    const bool &L1_EG27er_HTT200();
    const bool &L1_ETM100();
    const bool &L1_ETM105();
    const bool &L1_ETM110();
    const bool &L1_ETM115();
    const bool &L1_ETM120();
    const bool &L1_ETM150();
    const bool &L1_ETM30();
    const bool &L1_ETM40();
    const bool &L1_ETM50();
    const bool &L1_ETM60();
    const bool &L1_ETM70();
    const bool &L1_ETM75();
    const bool &L1_ETM75_Jet60_dPhi_Min0p4();
    const bool &L1_ETM80();
    const bool &L1_ETM85();
    const bool &L1_ETM90();
    const bool &L1_ETM95();
    const bool &L1_ETMHF100();
    const bool &L1_ETMHF100_HTT60er();
    const bool &L1_ETMHF110();
    const bool &L1_ETMHF110_HTT60er();
    const bool &L1_ETMHF110_HTT60er_NotSecondBunchInTrain();
    const bool &L1_ETMHF120();
    const bool &L1_ETMHF120_HTT60er();
    const bool &L1_ETMHF120_NotSecondBunchInTrain();
    const bool &L1_ETMHF130();
    const bool &L1_ETMHF130_HTT60er();
    const bool &L1_ETMHF140();
    const bool &L1_ETMHF150();
    const bool &L1_ETMHF90_HTT60er();
    const bool &L1_ETT1200();
    const bool &L1_ETT1600();
    const bool &L1_ETT2000();
    const bool &L1_ETT25();
    const bool &L1_ETT40_BptxAND();
    const bool &L1_ETT50_BptxAND();
    const bool &L1_ETT55_BptxAND();
    const bool &L1_ETT60_BptxAND();
    const bool &L1_ETT70_BptxAND();
    const bool &L1_ETT75_BptxAND();
    const bool &L1_FirstBunchAfterTrain();
    const bool &L1_FirstBunchBeforeTrain();
    const bool &L1_FirstBunchInTrain();
    const bool &L1_FirstCollisionInOrbit();
    const bool &L1_FirstCollisionInTrain();
    const bool &L1_HCAL_LaserMon_Trig();
    const bool &L1_HCAL_LaserMon_Veto();
    const bool &L1_HTM100();
    const bool &L1_HTM120();
    const bool &L1_HTM130();
    const bool &L1_HTM140();
    const bool &L1_HTM150();
    const bool &L1_HTM50();
    const bool &L1_HTM60_HTT260();
    const bool &L1_HTM70();
    const bool &L1_HTM80();
    const bool &L1_HTM80_HTT220();
    const bool &L1_HTT120();
    const bool &L1_HTT120er();
    const bool &L1_HTT160();
    const bool &L1_HTT160er();
    const bool &L1_HTT200();
    const bool &L1_HTT200er();
    const bool &L1_HTT220();
    const bool &L1_HTT240();
    const bool &L1_HTT255();
    const bool &L1_HTT255er();
    const bool &L1_HTT270();
    const bool &L1_HTT280();
    const bool &L1_HTT280er();
    const bool &L1_HTT280er_QuadJet_70_55_40_35_er2p4();
    const bool &L1_HTT300();
    const bool &L1_HTT320();
    const bool &L1_HTT320er();
    const bool &L1_HTT320er_QuadJet_70_55_40_40_er2p4();
    const bool &L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3();
    const bool &L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3();
    const bool &L1_HTT360er();
    const bool &L1_HTT400er();
    const bool &L1_HTT450er();
    const bool &L1_IsoEG18er_IsoTau24er_dEta_Min0p2();
    const bool &L1_IsoEG20er_IsoTau25er_dEta_Min0p2();
    const bool &L1_IsoEG22er_IsoTau26er_dEta_Min0p2();
    const bool &L1_IsoEG22er_Tau20er_dEta_Min0p2();
    const bool &L1_IsoEG32er2p5_Mt40();
    const bool &L1_IsoEG32er2p5_Mt44();
    const bool &L1_IsoEG32er2p5_Mt48();
    const bool &L1_IsoTau40er2p1_ETMHF100();
    const bool &L1_IsoTau40er2p1_ETMHF110();
    const bool &L1_IsoTau40er2p1_ETMHF120();
    const bool &L1_IsoTau40er2p1_ETMHF90();
    const bool &L1_IsolatedBunch();
    const bool &L1_Jet32_DoubleMu_10_0_dPhi_Jet_Mu0_Max0p4_dPhi_Mu_Mu_Min1p0();
    const bool &L1_Jet32_Mu0_EG10_dPhi_Jet_Mu_Max0p4_dPhi_Mu_EG_Min1p0();
    const bool &L1_LastBunchInTrain();
    const bool &L1_LastCollisionInTrain();
    const bool &L1_LooseIsoEG22er2p1_IsoTau26er2p1_dR_Min0p3();
    const bool &L1_LooseIsoEG22er2p1_Tau70er2p1_dR_Min0p3();
    const bool &L1_LooseIsoEG24er2p1_HTT100er();
    const bool &L1_LooseIsoEG24er2p1_IsoTau27er2p1_dR_Min0p3();
    const bool &L1_LooseIsoEG26er2p1_HTT100er();
    const bool &L1_LooseIsoEG26er2p1_Jet34er2p5_dR_Min0p3();
    const bool &L1_LooseIsoEG28er2p1_HTT100er();
    const bool &L1_LooseIsoEG28er2p1_Jet34er2p5_dR_Min0p3();
    const bool &L1_LooseIsoEG30er2p1_HTT100er();
    const bool &L1_LooseIsoEG30er2p1_Jet34er2p5_dR_Min0p3();
    const bool &L1_MU20_EG15();
    const bool &L1_MinimumBiasHF0_AND();
    const bool &L1_MinimumBiasHF0_AND_BptxAND();
    const bool &L1_MinimumBiasHF0_OR();
    const bool &L1_MinimumBiasHF0_OR_BptxAND();
    const bool &L1_MinimumBiasHF1_AND();
    const bool &L1_MinimumBiasHF1_AND_BptxAND();
    const bool &L1_MinimumBiasHF1_OR();
    const bool &L1_MinimumBiasHF1_OR_BptxAND();
    const bool &L1_Mu0er_ETM40();
    const bool &L1_Mu0er_ETM55();
    const bool &L1_Mu10er2p3_Jet32er2p3_dR_Max0p4_DoubleJet32er2p3_dEta_Max1p6();
    const bool &L1_Mu10er_ETM30();
    const bool &L1_Mu10er_ETM50();
    const bool &L1_Mu12_EG10();
    const bool &L1_Mu12er2p3_Jet40er2p1_dR_Max0p4_DoubleJet40er2p1_dEta_Max1p6();
    const bool &L1_Mu12er2p3_Jet40er2p3_dR_Max0p4_DoubleJet40er2p3_dEta_Max1p6();
    const bool &L1_Mu14er_ETM30();
    const bool &L1_Mu16er_Tau20er();
    const bool &L1_Mu16er_Tau24er();
    const bool &L1_Mu18er2p1_Tau24er2p1();
    const bool &L1_Mu18er2p1_Tau26er2p1();
    const bool &L1_Mu18er_IsoTau26er();
    const bool &L1_Mu18er_Tau20er();
    const bool &L1_Mu18er_Tau24er();
    const bool &L1_Mu20_EG10();
    const bool &L1_Mu20_EG10er2p5();
    const bool &L1_Mu20_EG17();
    const bool &L1_Mu20_IsoEG6();
    const bool &L1_Mu20er_IsoTau26er();
    const bool &L1_Mu22er2p1_IsoTau32er2p1();
    const bool &L1_Mu22er2p1_IsoTau34er2p1();
    const bool &L1_Mu22er2p1_IsoTau36er2p1();
    const bool &L1_Mu22er2p1_IsoTau40er2p1();
    const bool &L1_Mu22er2p1_Tau70er2p1();
    const bool &L1_Mu22er_IsoTau26er();
    const bool &L1_Mu23_EG10();
    const bool &L1_Mu23_IsoEG10();
    const bool &L1_Mu25er_IsoTau26er();
    const bool &L1_Mu3_Jet120er2p5_dR_Max0p4();
    const bool &L1_Mu3_Jet120er2p5_dR_Max0p8();
    const bool &L1_Mu3_Jet16er2p5_dR_Max0p4();
    const bool &L1_Mu3_Jet30er2p5();
    const bool &L1_Mu3_Jet35er2p5_dR_Max0p4();
    const bool &L1_Mu3_Jet60er2p5_dR_Max0p4();
    const bool &L1_Mu3_Jet80er2p5_dR_Max0p4();
    const bool &L1_Mu3_JetC120();
    const bool &L1_Mu3_JetC120_dEta_Max0p4_dPhi_Max0p4();
    const bool &L1_Mu3_JetC16();
    const bool &L1_Mu3_JetC16_dEta_Max0p4_dPhi_Max0p4();
    const bool &L1_Mu3_JetC60();
    const bool &L1_Mu3_JetC60_dEta_Max0p4_dPhi_Max0p4();
    const bool &L1_Mu3er1p5_Jet100er2p5_ETMHF40();
    const bool &L1_Mu3er1p5_Jet100er2p5_ETMHF50();
    const bool &L1_Mu5_EG15();
    const bool &L1_Mu5_EG20();
    const bool &L1_Mu5_EG23();
    const bool &L1_Mu5_EG23er2p5();
    const bool &L1_Mu5_IsoEG18();
    const bool &L1_Mu5_IsoEG20();
    const bool &L1_Mu5_LooseIsoEG20er2p5();
    const bool &L1_Mu6_DoubleEG10();
    const bool &L1_Mu6_DoubleEG10er2p5();
    const bool &L1_Mu6_DoubleEG12er2p5();
    const bool &L1_Mu6_DoubleEG15er2p5();
    const bool &L1_Mu6_DoubleEG17();
    const bool &L1_Mu6_DoubleEG17er2p5();
    const bool &L1_Mu6_HTT200();
    const bool &L1_Mu6_HTT240er();
    const bool &L1_Mu6_HTT250er();
    const bool &L1_Mu7_EG23er2p5();
    const bool &L1_Mu7_LooseIsoEG20er2p5();
    const bool &L1_Mu7_LooseIsoEG23er2p5();
    const bool &L1_Mu8_HTT150();
    const bool &L1_NotBptxOR();
    const bool &L1_QuadJet36er2p5_IsoTau52er2p1();
    const bool &L1_QuadJet60er2p5();
    const bool &L1_QuadJetC36_Tau52();
    const bool &L1_QuadJetC40();
    const bool &L1_QuadJetC50();
    const bool &L1_QuadJetC60();
    const bool &L1_QuadJet_95_75_65_20_DoubleJet_75_65_er2p5_Jet20_FWD3p0();
    const bool &L1_QuadMu0();
    const bool &L1_QuadMu0_OQ();
    const bool &L1_QuadMu0_SQ();
    const bool &L1_SecondBunchInTrain();
    const bool &L1_SecondLastBunchInTrain();
    const bool &L1_SingleEG10();
    const bool &L1_SingleEG10er2p5();
    const bool &L1_SingleEG15();
    const bool &L1_SingleEG15er2p5();
    const bool &L1_SingleEG18();
    const bool &L1_SingleEG24();
    const bool &L1_SingleEG26();
    const bool &L1_SingleEG26er2p5();
    const bool &L1_SingleEG28();
    const bool &L1_SingleEG2_BptxAND();
    const bool &L1_SingleEG30();
    const bool &L1_SingleEG32();
    const bool &L1_SingleEG34();
    const bool &L1_SingleEG34er2p5();
    const bool &L1_SingleEG36();
    const bool &L1_SingleEG36er2p5();
    const bool &L1_SingleEG38();
    const bool &L1_SingleEG38er2p5();
    const bool &L1_SingleEG40();
    const bool &L1_SingleEG40er2p5();
    const bool &L1_SingleEG42er2p5();
    const bool &L1_SingleEG45();
    const bool &L1_SingleEG45er2p5();
    const bool &L1_SingleEG5();
    const bool &L1_SingleEG50();
    const bool &L1_SingleEG60();
    const bool &L1_SingleEG8er2p5();
    const bool &L1_SingleIsoEG18();
    const bool &L1_SingleIsoEG18er();
    const bool &L1_SingleIsoEG20();
    const bool &L1_SingleIsoEG20er();
    const bool &L1_SingleIsoEG22();
    const bool &L1_SingleIsoEG22er();
    const bool &L1_SingleIsoEG24();
    const bool &L1_SingleIsoEG24er();
    const bool &L1_SingleIsoEG24er1p5();
    const bool &L1_SingleIsoEG24er2p1();
    const bool &L1_SingleIsoEG26();
    const bool &L1_SingleIsoEG26er();
    const bool &L1_SingleIsoEG26er1p5();
    const bool &L1_SingleIsoEG26er2p1();
    const bool &L1_SingleIsoEG26er2p5();
    const bool &L1_SingleIsoEG28();
    const bool &L1_SingleIsoEG28er();
    const bool &L1_SingleIsoEG28er1p5();
    const bool &L1_SingleIsoEG28er2p1();
    const bool &L1_SingleIsoEG28er2p5();
    const bool &L1_SingleIsoEG30();
    const bool &L1_SingleIsoEG30er();
    const bool &L1_SingleIsoEG30er2p1();
    const bool &L1_SingleIsoEG30er2p5();
    const bool &L1_SingleIsoEG32();
    const bool &L1_SingleIsoEG32er();
    const bool &L1_SingleIsoEG32er2p1();
    const bool &L1_SingleIsoEG32er2p5();
    const bool &L1_SingleIsoEG34();
    const bool &L1_SingleIsoEG34er();
    const bool &L1_SingleIsoEG34er2p5();
    const bool &L1_SingleIsoEG36();
    const bool &L1_SingleJet10erHE();
    const bool &L1_SingleJet120();
    const bool &L1_SingleJet120_FWD3p0();
    const bool &L1_SingleJet120er2p5();
    const bool &L1_SingleJet12_BptxAND();
    const bool &L1_SingleJet12erHE();
    const bool &L1_SingleJet140();
    const bool &L1_SingleJet140er2p5();
    const bool &L1_SingleJet140er2p5_ETMHF80();
    const bool &L1_SingleJet140er2p5_ETMHF90();
    const bool &L1_SingleJet150();
    const bool &L1_SingleJet16();
    const bool &L1_SingleJet160();
    const bool &L1_SingleJet160er2p5();
    const bool &L1_SingleJet170();
    const bool &L1_SingleJet180();
    const bool &L1_SingleJet180er2p5();
    const bool &L1_SingleJet20();
    const bool &L1_SingleJet200();
    const bool &L1_SingleJet20er2p5_NotBptxOR();
    const bool &L1_SingleJet20er2p5_NotBptxOR_3BX();
    const bool &L1_SingleJet35();
    const bool &L1_SingleJet35_FWD3p0();
    const bool &L1_SingleJet35er2p5();
    const bool &L1_SingleJet43er2p5_NotBptxOR_3BX();
    const bool &L1_SingleJet46er2p5_NotBptxOR_3BX();
    const bool &L1_SingleJet60();
    const bool &L1_SingleJet60_FWD3p0();
    const bool &L1_SingleJet60er2p5();
    const bool &L1_SingleJet8_BptxAND();
    const bool &L1_SingleJet8erHE();
    const bool &L1_SingleJet90();
    const bool &L1_SingleJet90_FWD3p0();
    const bool &L1_SingleJet90er2p5();
    const bool &L1_SingleJetC20_NotBptxOR();
    const bool &L1_SingleJetC20_NotBptxOR_3BX();
    const bool &L1_SingleJetC40_NotBptxOR_3BX();
    const bool &L1_SingleJetC40_NotBptxOR_5BX();
    const bool &L1_SingleLooseIsoEG28er1p5();
    const bool &L1_SingleLooseIsoEG30er1p5();
    const bool &L1_SingleMu0_BMTF();
    const bool &L1_SingleMu0_DQ();
    const bool &L1_SingleMu0_EMTF();
    const bool &L1_SingleMu0_OMTF();
    const bool &L1_SingleMu10_LowQ();
    const bool &L1_SingleMu10er1p5();
    const bool &L1_SingleMu12();
    const bool &L1_SingleMu12_DQ_BMTF();
    const bool &L1_SingleMu12_DQ_EMTF();
    const bool &L1_SingleMu12_DQ_OMTF();
    const bool &L1_SingleMu12er1p5();
    const bool &L1_SingleMu14();
    const bool &L1_SingleMu14er();
    const bool &L1_SingleMu14er1p5();
    const bool &L1_SingleMu15_DQ();
    const bool &L1_SingleMu16();
    const bool &L1_SingleMu16er();
    const bool &L1_SingleMu16er1p5();
    const bool &L1_SingleMu18();
    const bool &L1_SingleMu18er();
    const bool &L1_SingleMu18er1p5();
    const bool &L1_SingleMu20();
    const bool &L1_SingleMu20er();
    const bool &L1_SingleMu22();
    const bool &L1_SingleMu22_BMTF();
    const bool &L1_SingleMu22_EMTF();
    const bool &L1_SingleMu22_OMTF();
    const bool &L1_SingleMu22er();
    const bool &L1_SingleMu25();
    const bool &L1_SingleMu25er();
    const bool &L1_SingleMu3();
    const bool &L1_SingleMu30();
    const bool &L1_SingleMu30er();
    const bool &L1_SingleMu5();
    const bool &L1_SingleMu6er1p5();
    const bool &L1_SingleMu7();
    const bool &L1_SingleMu7_DQ();
    const bool &L1_SingleMu7er1p5();
    const bool &L1_SingleMu8er1p5();
    const bool &L1_SingleMu9er1p5();
    const bool &L1_SingleMuCosmics();
    const bool &L1_SingleMuCosmics_BMTF();
    const bool &L1_SingleMuCosmics_EMTF();
    const bool &L1_SingleMuCosmics_OMTF();
    const bool &L1_SingleMuOpen();
    const bool &L1_SingleMuOpen_NotBptxOR();
    const bool &L1_SingleMuOpen_NotBptxOR_3BX();
    const bool &L1_SingleMuOpen_er1p1_NotBptxOR_3BX();
    const bool &L1_SingleMuOpen_er1p4_NotBptxOR_3BX();
    const bool &L1_SingleTau100er();
    const bool &L1_SingleTau120er();
    const bool &L1_SingleTau120er2p1();
    const bool &L1_SingleTau130er2p1();
    const bool &L1_SingleTau80er();
    const bool &L1_TOTEM_1();
    const bool &L1_TOTEM_2();
    const bool &L1_TOTEM_3();
    const bool &L1_TOTEM_4();
    const bool &L1_TripleEG16er2p5();
    const bool &L1_TripleEG_14_10_8();
    const bool &L1_TripleEG_16_12_8_er2p5();
    const bool &L1_TripleEG_16_15_8_er2p5();
    const bool &L1_TripleEG_18_17_8();
    const bool &L1_TripleEG_18_17_8_er2p5();
    const bool &L1_TripleEG_18_18_12_er2p5();
    const bool &L1_TripleJet_100_80_70_DoubleJet_80_70_er2p5();
    const bool &L1_TripleJet_105_85_75_DoubleJet_85_75_er2p5();
    const bool &L1_TripleJet_84_68_48_VBF();
    const bool &L1_TripleJet_88_72_56_VBF();
    const bool &L1_TripleJet_92_76_64_VBF();
    const bool &L1_TripleJet_95_75_65_DoubleJet_75_65_er2p5();
    const bool &L1_TripleMu0();
    const bool &L1_TripleMu0_OQ();
    const bool &L1_TripleMu0_SQ();
    const bool &L1_TripleMu3();
    const bool &L1_TripleMu3_SQ();
    const bool &L1_TripleMu_5SQ_3SQ_0OQ();
    const bool &L1_TripleMu_5SQ_3SQ_0OQ_DoubleMu_5_3_SQ_OS_Mass_Max9();
    const bool &L1_TripleMu_5SQ_3SQ_0_DoubleMu_5_3_SQ_OS_Mass_Max9();
    const bool &L1_TripleMu_5_0_0();
    const bool &L1_TripleMu_5_3_3();
    const bool &L1_TripleMu_5_3_3_SQ();
    const bool &L1_TripleMu_5_3p5_2p5();
    const bool &L1_TripleMu_5_3p5_2p5_DoubleMu_5_2p5_OS_Mass_5to17();
    const bool &L1_TripleMu_5_3p5_2p5_OQ_DoubleMu_5_2p5_OQ_OS_Mass_5to17();
    const bool &L1_TripleMu_5_4_2p5_DoubleMu_5_2p5_OS_Mass_5to17();
    const bool &L1_TripleMu_5_5_3();
    const bool &L1_UnpairedBunchBptxMinus();
    const bool &L1_UnpairedBunchBptxPlus();
    const bool &L1_ZeroBias();
    const bool &L1_ZeroBias_FirstCollidingBunch();
    const bool &L1_ZeroBias_copy();
    const bool &L1simulation_step();
    const vector<float> &LHEPart_eta();
    const vector<float> &LHEPart_incomingpz();
    const vector<float> &LHEPart_mass();
    const vector<LorentzVector> &LHEPart_p4();
    const vector<int> &LHEPart_pdgId();
    const vector<float> &LHEPart_phi();
    const vector<float> &LHEPart_pt();
    const vector<int> &LHEPart_spin();
    const vector<int> &LHEPart_status();
    const vector<float> &LHEPdfWeight();
    const vector<float> &LHEReweightingWeight();
    const vector<float> &LHEScaleWeight();
    const float &LHEWeight_originalXWGTUP();
    const float &LHE_AlphaS();
    const float &LHE_HT();
    const float &LHE_HTIncoming();
    const UChar_t &LHE_Nb();
    const UChar_t &LHE_Nc();
    const UChar_t &LHE_Nglu();
    const UChar_t &LHE_Njets();
    const UChar_t &LHE_NpLO();
    const UChar_t &LHE_NpNLO();
    const UChar_t &LHE_Nuds();
    const float &LHE_Vpt();
    const float &MET_MetUnclustEnUpDeltaX();
    const float &MET_MetUnclustEnUpDeltaY();
    const float &MET_covXX();
    const float &MET_covXY();
    const float &MET_covYY();
    const float &MET_fiducialGenPhi();
    const float &MET_fiducialGenPt();
    const float &MET_phi();
    const float &MET_pt();
    const float &MET_significance();
    const float &MET_sumEt();
    const float &MET_sumPtUnclustered();
    const vector<int> &Muon_charge();
    const vector<UChar_t> &Muon_cleanmask();
    const vector<float> &Muon_dxy();
    const vector<float> &Muon_dxyErr();
    const vector<float> &Muon_dxybs();
    const vector<float> &Muon_dz();
    const vector<float> &Muon_dzErr();
    const vector<float> &Muon_eta();
    const vector<int> &Muon_fsrPhotonIdx();
    const vector<UChar_t> &Muon_genPartFlav();
    const vector<int> &Muon_genPartIdx();
    const vector<UChar_t> &Muon_highPtId();
    const vector<bool> &Muon_highPurity();
    const vector<bool> &Muon_inTimeMuon();
    const vector<float> &Muon_ip3d();
    const vector<bool> &Muon_isGlobal();
    const vector<bool> &Muon_isPFcand();
    const vector<bool> &Muon_isTracker();
    const vector<int> &Muon_jetIdx();
    const vector<float> &Muon_jetPtRelv2();
    const vector<float> &Muon_jetRelIso();
    const vector<bool> &Muon_looseId();
    const vector<float> &Muon_mass();
    const vector<bool> &Muon_mediumId();
    const vector<bool> &Muon_mediumPromptId();
    const vector<UChar_t> &Muon_miniIsoId();
    const vector<float> &Muon_miniPFRelIso_all();
    const vector<float> &Muon_miniPFRelIso_chg();
    const vector<UChar_t> &Muon_multiIsoId();
    const vector<UChar_t> &Muon_mvaId();
    const vector<float> &Muon_mvaLowPt();
    const vector<float> &Muon_mvaTTH();
    const vector<int> &Muon_nStations();
    const vector<int> &Muon_nTrackerLayers();
    const vector<LorentzVector> &Muon_p4();
    const vector<int> &Muon_pdgId();
    const vector<UChar_t> &Muon_pfIsoId();
    const vector<float> &Muon_pfRelIso03_all();
    const vector<float> &Muon_pfRelIso03_chg();
    const vector<float> &Muon_pfRelIso04_all();
    const vector<float> &Muon_phi();
    const vector<float> &Muon_pt();
    const vector<float> &Muon_ptErr();
    const vector<float> &Muon_segmentComp();
    const vector<float> &Muon_sip3d();
    const vector<bool> &Muon_softId();
    const vector<float> &Muon_softMva();
    const vector<bool> &Muon_softMvaId();
    const vector<int> &Muon_tightCharge();
    const vector<bool> &Muon_tightId();
    const vector<UChar_t> &Muon_tkIsoId();
    const vector<float> &Muon_tkRelIso();
    const vector<bool> &Muon_triggerIdLoose();
    const vector<float> &Muon_tunepRelPt();
    const vector<float> &OtherPV_z();
    const vector<float> &PSWeight();
    const float &PV_chi2();
    const float &PV_ndof();
    const int &PV_npvs();
    const int &PV_npvsGood();
    const float &PV_score();
    const float &PV_x();
    const float &PV_y();
    const float &PV_z();
    const vector<int> &Photon_charge();
    const vector<UChar_t> &Photon_cleanmask();
    const vector<int> &Photon_cutBased();
    const vector<int> &Photon_cutBased_Fall17V1Bitmap();
    const vector<int> &Photon_cutBased_Spring16V2p2();
    const vector<float> &Photon_eCorr();
    const vector<int> &Photon_electronIdx();
    const vector<bool> &Photon_electronVeto();
    const vector<float> &Photon_energyErr();
    const vector<float> &Photon_eta();
    const vector<UChar_t> &Photon_genPartFlav();
    const vector<int> &Photon_genPartIdx();
    const vector<float> &Photon_hoe();
    const vector<bool> &Photon_isScEtaEB();
    const vector<bool> &Photon_isScEtaEE();
    const vector<int> &Photon_jetIdx();
    const vector<float> &Photon_mass();
    const vector<float> &Photon_mvaID();
    const vector<float> &Photon_mvaID_Fall17V1p1();
    const vector<float> &Photon_mvaID_Spring16nonTrigV1();
    const vector<bool> &Photon_mvaID_WP80();
    const vector<bool> &Photon_mvaID_WP90();
    const vector<LorentzVector> &Photon_p4();
    const vector<int> &Photon_pdgId();
    const vector<float> &Photon_pfRelIso03_all();
    const vector<float> &Photon_pfRelIso03_chg();
    const vector<float> &Photon_phi();
    const vector<bool> &Photon_pixelSeed();
    const vector<float> &Photon_pt();
    const vector<float> &Photon_r9();
    const vector<UChar_t> &Photon_seedGain();
    const vector<float> &Photon_sieie();
    const vector<int> &Photon_vidNestedWPBitmap();
    const vector<int> &Photon_vidNestedWPBitmap_Spring16V2p2();
    const float &Pileup_gpudensity();
    const int &Pileup_nPU();
    const float &Pileup_nTrueInt();
    const float &Pileup_pudensity();
    const int &Pileup_sumEOOT();
    const int &Pileup_sumLOOT();
    const float &PuppiMET_phi();
    const float &PuppiMET_phiJERUp();
    const float &PuppiMET_phiJESUp();
    const float &PuppiMET_pt();
    const float &PuppiMET_ptJERUp();
    const float &PuppiMET_ptJESUp();
    const float &PuppiMET_sumEt();
    const float &RawMET_phi();
    const float &RawMET_pt();
    const float &RawMET_sumEt();
    const float &RawPuppiMET_phi();
    const float &RawPuppiMET_pt();
    const float &RawPuppiMET_sumEt();
    const vector<float> &SV_chi2();
    const vector<float> &SV_dlen();
    const vector<float> &SV_dlenSig();
    const vector<float> &SV_dxy();
    const vector<float> &SV_dxySig();
    const vector<float> &SV_eta();
    const vector<float> &SV_mass();
    const vector<float> &SV_ndof();
    const vector<LorentzVector> &SV_p4();
    const vector<float> &SV_pAngle();
    const vector<float> &SV_phi();
    const vector<float> &SV_pt();
    const vector<float> &SV_x();
    const vector<float> &SV_y();
    const vector<float> &SV_z();
    const float &SoftActivityJetHT();
    const float &SoftActivityJetHT10();
    const float &SoftActivityJetHT2();
    const float &SoftActivityJetHT5();
    const int &SoftActivityJetNjets10();
    const int &SoftActivityJetNjets2();
    const int &SoftActivityJetNjets5();
    const vector<float> &SoftActivityJet_eta();
    const vector<float> &SoftActivityJet_phi();
    const vector<float> &SoftActivityJet_pt();
    const vector<float> &SubGenJetAK8_eta();
    const vector<float> &SubGenJetAK8_mass();
    const vector<LorentzVector> &SubGenJetAK8_p4();
    const vector<float> &SubGenJetAK8_phi();
    const vector<float> &SubGenJetAK8_pt();
    const vector<float> &SubJet_btagCMVA();
    const vector<float> &SubJet_btagCSVV2();
    const vector<float> &SubJet_btagDeepB();
    const vector<float> &SubJet_eta();
    const vector<float> &SubJet_mass();
    const vector<float> &SubJet_n2b1();
    const vector<float> &SubJet_n3b1();
    const vector<UChar_t> &SubJet_nBHadrons();
    const vector<UChar_t> &SubJet_nCHadrons();
    const vector<LorentzVector> &SubJet_p4();
    const vector<float> &SubJet_phi();
    const vector<float> &SubJet_pt();
    const vector<float> &SubJet_rawFactor();
    const vector<float> &SubJet_tau1();
    const vector<float> &SubJet_tau2();
    const vector<float> &SubJet_tau3();
    const vector<float> &SubJet_tau4();
    const vector<int> &Tau_charge();
    const vector<float> &Tau_chargedIso();
    const vector<UChar_t> &Tau_cleanmask();
    const vector<int> &Tau_decayMode();
    const vector<float> &Tau_dxy();
    const vector<float> &Tau_dz();
    const vector<float> &Tau_eta();
    const vector<UChar_t> &Tau_genPartFlav();
    const vector<int> &Tau_genPartIdx();
    const vector<UChar_t> &Tau_idAntiEle();
    const vector<UChar_t> &Tau_idAntiEle2018();
    const vector<UChar_t> &Tau_idAntiMu();
    const vector<bool> &Tau_idDecayMode();
    const vector<bool> &Tau_idDecayModeNewDMs();
    const vector<UChar_t> &Tau_idDeepTau2017v2p1VSe();
    const vector<UChar_t> &Tau_idDeepTau2017v2p1VSjet();
    const vector<UChar_t> &Tau_idDeepTau2017v2p1VSmu();
    const vector<UChar_t> &Tau_idMVAnewDM2017v2();
    const vector<UChar_t> &Tau_idMVAoldDM();
    const vector<UChar_t> &Tau_idMVAoldDM2017v1();
    const vector<UChar_t> &Tau_idMVAoldDM2017v2();
    const vector<UChar_t> &Tau_idMVAoldDMdR032017v2();
    const vector<int> &Tau_jetIdx();
    const vector<float> &Tau_leadTkDeltaEta();
    const vector<float> &Tau_leadTkDeltaPhi();
    const vector<float> &Tau_leadTkPtOverTauPt();
    const vector<float> &Tau_mass();
    const vector<float> &Tau_neutralIso();
    const vector<LorentzVector> &Tau_p4();
    const vector<float> &Tau_phi();
    const vector<float> &Tau_photonsOutsideSignalCone();
    const vector<float> &Tau_pt();
    const vector<float> &Tau_puCorr();
    const vector<float> &Tau_rawAntiEle();
    const vector<float> &Tau_rawAntiEle2018();
    const vector<int> &Tau_rawAntiEleCat();
    const vector<int> &Tau_rawAntiEleCat2018();
    const vector<float> &Tau_rawDeepTau2017v2p1VSe();
    const vector<float> &Tau_rawDeepTau2017v2p1VSjet();
    const vector<float> &Tau_rawDeepTau2017v2p1VSmu();
    const vector<float> &Tau_rawIso();
    const vector<float> &Tau_rawIsodR03();
    const vector<float> &Tau_rawMVAnewDM2017v2();
    const vector<float> &Tau_rawMVAoldDM();
    const vector<float> &Tau_rawMVAoldDM2017v1();
    const vector<float> &Tau_rawMVAoldDM2017v2();
    const vector<float> &Tau_rawMVAoldDMdR032017v2();
    const float &TkMET_phi();
    const float &TkMET_pt();
    const float &TkMET_sumEt();
    const vector<float> &TrigObj_eta();
    const vector<int> &TrigObj_filterBits();
    const vector<int> &TrigObj_id();
    const vector<int> &TrigObj_l1charge();
    const vector<int> &TrigObj_l1iso();
    const vector<float> &TrigObj_l1pt();
    const vector<float> &TrigObj_l1pt_2();
    const vector<float> &TrigObj_l2pt();
    const vector<float> &TrigObj_phi();
    const vector<float> &TrigObj_pt();
    const float &btagWeight_CMVA();
    const float &btagWeight_CSVV2();
    const float &btagWeight_DeepCSVB();
    const ULong64_t &event();
    const float &fixedGridRhoFastjetAll();
    const float &fixedGridRhoFastjetCentral();
    const float &fixedGridRhoFastjetCentralCalo();
    const float &fixedGridRhoFastjetCentralChargedPileUp();
    const float &fixedGridRhoFastjetCentralNeutral();
    const int &genTtbarId();
    const float &genWeight();
    const UInt_t &luminosityBlock();
    const UInt_t &nCorrT1METJet();
    const UInt_t &nElectron();
    const UInt_t &nFatJet();
    const UInt_t &nFsrPhoton();
    const UInt_t &nGenDressedLepton();
    const UInt_t &nGenIsolatedPhoton();
    const UInt_t &nGenJet();
    const UInt_t &nGenJetAK8();
    const UInt_t &nGenPart();
    const UInt_t &nGenVisTau();
    const UInt_t &nIsoTrack();
    const UInt_t &nJet();
    const UInt_t &nLHEPart();
    const UInt_t &nLHEPdfWeight();
    const UInt_t &nLHEReweightingWeight();
    const UInt_t &nLHEScaleWeight();
    const UInt_t &nMuon();
    const UInt_t &nOtherPV();
    const UInt_t &nPSWeight();
    const UInt_t &nPhoton();
    const UInt_t &nSV();
    const UInt_t &nSoftActivityJet();
    const UInt_t &nSubGenJetAK8();
    const UInt_t &nSubJet();
    const UInt_t &nTau();
    const UInt_t &nTrigObj();
    const UInt_t &run();
    Bool_t isData();
    const Int_t &year();
};

#ifndef __CINT__
extern Nano nt;
#endif

namespace tas {
    const vector<float> &LHEWeight_mg_reweighting(); // mg_reweighting
    const float &CaloMET_phi(); // phi
    const float &CaloMET_pt(); // pt
    const float &CaloMET_sumEt(); // scalar sum of Et
    const float &ChsMET_phi(); // raw chs PF MET phi
    const float &ChsMET_pt(); // raw chs PF MET pt
    const float &ChsMET_sumEt(); // raw chs PF scalar sum of Et
    const vector<float> &CorrT1METJet_area(); // jet catchment area, for JECs
    const vector<float> &CorrT1METJet_eta(); // eta
    const vector<float> &CorrT1METJet_muonSubtrFactor(); // 1-(muon-subtracted raw pt)/(raw pt)
    const vector<float> &CorrT1METJet_phi(); // phi
    const vector<float> &CorrT1METJet_rawPt(); // pt()*jecFactor('Uncorrected')
    const vector<int> &Electron_charge(); // electric charge
    const vector<UChar_t> &Electron_cleanmask(); // simple cleaning mask with priority to leptons
    const vector<bool> &Electron_convVeto(); // pass conversion veto
    const vector<int> &Electron_cutBased(); // cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
    const vector<int> &Electron_cutBased_Fall17_V1(); // cut-based ID Fall17 V1 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
    const vector<bool> &Electron_cutBased_HEEP(); // cut-based HEEP ID
    const vector<int> &Electron_cutBased_HLTPreSel(); // cut-based HLT pre-selection ID
    const vector<int> &Electron_cutBased_Spring15(); // cut-based Spring15 ID (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
    const vector<int> &Electron_cutBased_Sum16(); // cut-based Summer16 ID (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
    const vector<float> &Electron_deltaEtaSC(); // delta eta (SC,ele) with sign
    const vector<float> &Electron_dr03EcalRecHitSumEt(); // Non-PF Ecal isolation within a delta R cone of 0.3 with electron pt > 35 GeV
    const vector<float> &Electron_dr03HcalDepth1TowerSumEt(); // Non-PF Hcal isolation within a delta R cone of 0.3 with electron pt > 35 GeV
    const vector<float> &Electron_dr03TkSumPt(); // Non-PF track isolation within a delta R cone of 0.3 with electron pt > 35 GeV
    const vector<float> &Electron_dr03TkSumPtHEEP(); // Non-PF track isolation within a delta R cone of 0.3 with electron pt > 35 GeV used in HEEP ID
    const vector<float> &Electron_dxy(); // dxy (with sign) wrt first PV, in cm
    const vector<float> &Electron_dxyErr(); // dxy uncertainty, in cm
    const vector<float> &Electron_dz(); // dz (with sign) wrt first PV, in cm
    const vector<float> &Electron_dzErr(); // dz uncertainty, in cm
    const vector<float> &Electron_eCorr(); // ratio of the calibrated energy/miniaod energy
    const vector<float> &Electron_eInvMinusPInv(); // 1/E_SC - 1/p_trk
    const vector<float> &Electron_energyErr(); // energy error of the cluster-track combination
    const vector<float> &Electron_eta(); // eta
    const vector<UChar_t> &Electron_genPartFlav(); // Flavour of genParticle for MC matching to status==1 electrons or photons: 1 = prompt electron (including gamma*->mu mu), 15 = electron from prompt tau, 22 = prompt photon (likely conversion), 5 = electron from b, 4 = electron from c, 3 = electron from light or unknown, 0 = unmatched
    const vector<int> &Electron_genPartIdx(); // Index into genParticle list for MC matching to status==1 electrons or photons
    const vector<float> &Electron_hoe(); // H over E
    const vector<float> &Electron_ip3d(); // 3D impact parameter wrt first PV, in cm
    const vector<bool> &Electron_isPFcand(); // electron is PF candidate
    const vector<int> &Electron_jetIdx(); // index of the associated jet (-1 if none)
    const vector<float> &Electron_jetPtRelv2(); // Relative momentum of the lepton with respect to the closest jet after subtracting the lepton
    const vector<float> &Electron_jetRelIso(); // Relative isolation in matched jet (1/ptRatio-1, pfRelIso04_all if no matched jet)
    const vector<UChar_t> &Electron_lostHits(); // number of missing inner hits
    const vector<float> &Electron_mass(); // mass
    const vector<float> &Electron_miniPFRelIso_all(); // mini PF relative isolation, total (with scaled rho*EA PU corrections)
    const vector<float> &Electron_miniPFRelIso_chg(); // mini PF relative isolation, charged component
    const vector<float> &Electron_mvaFall17V1Iso(); // MVA Iso ID V1 score
    const vector<bool> &Electron_mvaFall17V1Iso_WP80(); // MVA Iso ID V1 WP80
    const vector<bool> &Electron_mvaFall17V1Iso_WP90(); // MVA Iso ID V1 WP90
    const vector<bool> &Electron_mvaFall17V1Iso_WPL(); // MVA Iso ID V1 loose WP
    const vector<float> &Electron_mvaFall17V1noIso(); // MVA noIso ID V1 score
    const vector<bool> &Electron_mvaFall17V1noIso_WP80(); // MVA noIso ID V1 WP80
    const vector<bool> &Electron_mvaFall17V1noIso_WP90(); // MVA noIso ID V1 WP90
    const vector<bool> &Electron_mvaFall17V1noIso_WPL(); // MVA noIso ID V1 loose WP
    const vector<float> &Electron_mvaFall17V2Iso(); // MVA Iso ID V2 score
    const vector<bool> &Electron_mvaFall17V2Iso_WP80(); // MVA Iso ID V2 WP80
    const vector<bool> &Electron_mvaFall17V2Iso_WP90(); // MVA Iso ID V2 WP90
    const vector<bool> &Electron_mvaFall17V2Iso_WPL(); // MVA Iso ID V2 loose WP
    const vector<float> &Electron_mvaFall17V2noIso(); // MVA noIso ID V2 score
    const vector<bool> &Electron_mvaFall17V2noIso_WP80(); // MVA noIso ID V2 WP80
    const vector<bool> &Electron_mvaFall17V2noIso_WP90(); // MVA noIso ID V2 WP90
    const vector<bool> &Electron_mvaFall17V2noIso_WPL(); // MVA noIso ID V2 loose WP
    const vector<float> &Electron_mvaSpring16GP(); // MVA Spring16 general-purpose ID score
    const vector<bool> &Electron_mvaSpring16GP_WP80(); // MVA Spring16 general-purpose ID WP80
    const vector<bool> &Electron_mvaSpring16GP_WP90(); // MVA Spring16 general-purpose ID WP90
    const vector<float> &Electron_mvaSpring16HZZ(); // MVA Spring16 HZZ ID score
    const vector<bool> &Electron_mvaSpring16HZZ_WPL(); // MVA Spring16 HZZ ID loose WP
    const vector<float> &Electron_mvaTTH(); // TTH MVA lepton ID score
    const vector<LorentzVector> &Electron_p4(); // from Electron_pt,eta,phi,mass
    const vector<int> &Electron_pdgId(); // PDG code assigned by the event reconstruction (not by MC truth)
    const vector<float> &Electron_pfRelIso03_all(); // PF relative isolation dR=0.3, total (with rho*EA PU corrections)
    const vector<float> &Electron_pfRelIso03_chg(); // PF relative isolation dR=0.3, charged component
    const vector<float> &Electron_phi(); // phi
    const vector<int> &Electron_photonIdx(); // index of the associated photon (-1 if none)
    const vector<float> &Electron_pt(); // p_{T}
    const vector<float> &Electron_r9(); // R9 of the supercluster, calculated with full 5x5 region
    const vector<float> &Electron_scEtOverPt(); // (supercluster transverse energy)/pt-1
    const vector<UChar_t> &Electron_seedGain(); // Gain of the seed crystal
    const vector<float> &Electron_sieie(); // sigma_IetaIeta of the supercluster, calculated with full 5x5 region
    const vector<float> &Electron_sip3d(); // 3D impact parameter significance wrt first PV, in cm
    const vector<int> &Electron_tightCharge(); // Tight charge criteria (0:none, 1:isGsfScPixChargeConsistent, 2:isGsfCtfScPixChargeConsistent)
    const vector<int> &Electron_vidNestedWPBitmap(); // VID compressed bitmap (MinPtCut,GsfEleSCEtaMultiRangeCut,GsfEleDEtaInSeedCut,GsfEleDPhiInCut,GsfEleFull5x5SigmaIEtaIEtaCut,GsfEleHadronicOverEMEnergyScaledCut,GsfEleEInverseMinusPInverseCut,GsfEleRelPFIsoScaledCut,GsfEleConversionVetoCut,GsfEleMissingHitsCut), 3 bits per cut
    const vector<int> &Electron_vidNestedWPBitmapHEEP(); // VID compressed bitmap (MinPtCut,GsfEleSCEtaMultiRangeCut,GsfEleDEtaInSeedCut,GsfEleDPhiInCut,GsfEleFull5x5SigmaIEtaIEtaWithSatCut,GsfEleFull5x5E2x5OverE5x5WithSatCut,GsfEleHadronicOverEMLinearCut,GsfEleValueMapIsoRhoCut,GsfEleEmHadD1IsoRhoCut,GsfEleDxyCut,GsfEleMissingHitsCut,GsfEleEcalDrivenCut), 1 bits per cut
    const vector<int> &Electron_vidNestedWPBitmapSpring15(); // VID compressed bitmap (MinPtCut,GsfEleSCEtaMultiRangeCut,GsfEleDEtaInCut,GsfEleDPhiInCut,GsfEleFull5x5SigmaIEtaIEtaCut,GsfEleHadronicOverEMCut,GsfEleDxyCut,GsfEleDzCut,GsfEleEInverseMinusPInverseCut,GsfEleEffAreaPFIsoCut,GsfEleConversionVetoCut,GsfEleMissingHitsCut), 2 bits per cut
    const vector<int> &Electron_vidNestedWPBitmapSum16(); // VID compressed bitmap (MinPtCut,GsfEleSCEtaMultiRangeCut,GsfEleDEtaInSeedCut,GsfEleDPhiInCut,GsfEleFull5x5SigmaIEtaIEtaCut,GsfEleHadronicOverEMCut,GsfEleEInverseMinusPInverseCut,GsfEleEffAreaPFIsoCut,GsfEleConversionVetoCut,GsfEleMissingHitsCut), 3 bits per cut
    const vector<float> &FatJet_area(); // jet catchment area, for JECs
    const vector<float> &FatJet_btagCMVA(); // CMVA V2 btag discriminator
    const vector<float> &FatJet_btagCSVV2(); //  pfCombinedInclusiveSecondaryVertexV2 b-tag discriminator (aka CSVV2)
    const vector<float> &FatJet_btagDDBvL(); // DeepDoubleX (mass-decorrelated) discriminator for H(Z)->bb vs QCD
    const vector<float> &FatJet_btagDDBvL_noMD(); // DeepDoubleX discriminator (no mass-decorrelation) for H(Z)->bb vs QCD
    const vector<float> &FatJet_btagDDCvB(); // DeepDoubleX (mass-decorrelated) discriminator for H(Z)->cc vs H(Z)->bb
    const vector<float> &FatJet_btagDDCvB_noMD(); // DeepDoubleX discriminator (no mass-decorrelation) for H(Z)->cc vs H(Z)->bb
    const vector<float> &FatJet_btagDDCvL(); // DeepDoubleX (mass-decorrelated) discriminator for H(Z)->cc vs QCD
    const vector<float> &FatJet_btagDDCvL_noMD(); // DeepDoubleX discriminator (no mass-decorrelation) for H(Z)->cc vs QCD
    const vector<float> &FatJet_btagDeepB(); // DeepCSV b+bb tag discriminator
    const vector<float> &FatJet_btagHbb(); // Higgs to BB tagger discriminator
    const vector<float> &FatJet_deepTagMD_H4qvsQCD(); // Mass-decorrelated DeepBoostedJet tagger H->4q vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_HbbvsQCD(); // Mass-decorrelated DeepBoostedJet tagger H->bb vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_TvsQCD(); // Mass-decorrelated DeepBoostedJet tagger top vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_WvsQCD(); // Mass-decorrelated DeepBoostedJet tagger W vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_ZHbbvsQCD(); // Mass-decorrelated DeepBoostedJet tagger Z/H->bb vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_ZHccvsQCD(); // Mass-decorrelated DeepBoostedJet tagger Z/H->cc vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_ZbbvsQCD(); // Mass-decorrelated DeepBoostedJet tagger Z->bb vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_ZvsQCD(); // Mass-decorrelated DeepBoostedJet tagger Z vs QCD discriminator
    const vector<float> &FatJet_deepTagMD_bbvsLight(); // Mass-decorrelated DeepBoostedJet tagger Z/H/gluon->bb vs light flavour discriminator
    const vector<float> &FatJet_deepTagMD_ccvsLight(); // Mass-decorrelated DeepBoostedJet tagger Z/H/gluon->cc vs light flavour discriminator
    const vector<float> &FatJet_deepTag_H(); // DeepBoostedJet tagger H(bb,cc,4q) sum
    const vector<float> &FatJet_deepTag_QCD(); // DeepBoostedJet tagger QCD(bb,cc,b,c,others) sum
    const vector<float> &FatJet_deepTag_QCDothers(); // DeepBoostedJet tagger QCDothers value
    const vector<float> &FatJet_deepTag_TvsQCD(); // DeepBoostedJet tagger top vs QCD discriminator
    const vector<float> &FatJet_deepTag_WvsQCD(); // DeepBoostedJet tagger W vs QCD discriminator
    const vector<float> &FatJet_deepTag_ZvsQCD(); // DeepBoostedJet tagger Z vs QCD discriminator
    const vector<int> &FatJet_electronIdx3SJ(); // index of electron matched to jet
    const vector<float> &FatJet_eta(); // eta
    const vector<int> &FatJet_genJetAK8Idx(); // index of matched gen AK8 jet
    const vector<int> &FatJet_hadronFlavour(); // flavour from hadron ghost clustering
    const vector<int> &FatJet_jetId(); // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
    const vector<float> &FatJet_lsf3(); // Lepton Subjet Fraction (3 subjets)
    const vector<float> &FatJet_mass(); // mass
    const vector<float> &FatJet_msoftdrop(); // Corrected soft drop mass with PUPPI
    const vector<int> &FatJet_muonIdx3SJ(); // index of muon matched to jet
    const vector<float> &FatJet_n2b1(); // N2 with beta=1
    const vector<float> &FatJet_n3b1(); // N3 with beta=1
    const vector<UChar_t> &FatJet_nBHadrons(); // number of b-hadrons
    const vector<UChar_t> &FatJet_nCHadrons(); // number of c-hadrons
    const vector<LorentzVector> &FatJet_p4(); // from FatJet_pt,eta,phi,mass
    const vector<float> &FatJet_phi(); // phi
    const vector<float> &FatJet_pt(); // pt
    const vector<float> &FatJet_rawFactor(); // 1 - Factor to get back to raw pT
    const vector<int> &FatJet_subJetIdx1(); // index of first subjet
    const vector<int> &FatJet_subJetIdx2(); // index of second subjet
    const vector<float> &FatJet_tau1(); // Nsubjettiness (1 axis)
    const vector<float> &FatJet_tau2(); // Nsubjettiness (2 axis)
    const vector<float> &FatJet_tau3(); // Nsubjettiness (3 axis)
    const vector<float> &FatJet_tau4(); // Nsubjettiness (4 axis)
    const bool &Flag_BadChargedCandidateFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_BadChargedCandidateSummer16Filter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_BadPFMuonFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_BadPFMuonSummer16Filter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_CSCTightHalo2015Filter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_CSCTightHaloFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_CSCTightHaloTrkMuUnvetoFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_EcalDeadCellBoundaryEnergyFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_EcalDeadCellTriggerPrimitiveFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_HBHENoiseFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_HBHENoiseIsoFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_HcalStripHaloFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_METFilters(); // Trigger/flag bit (process: PAT)
    const bool &Flag_chargedHadronTrackResolutionFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_ecalBadCalibFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_ecalBadCalibFilterV2(); // Bad ECAL calib flag (updated xtal list)
    const bool &Flag_ecalLaserCorrFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_eeBadScFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_globalSuperTightHalo2016Filter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_globalTightHalo2016Filter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_goodVertices(); // Trigger/flag bit (process: PAT)
    const bool &Flag_hcalLaserEventFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_muonBadTrackFilter(); // Trigger/flag bit (process: PAT)
    const bool &Flag_trkPOGFilters(); // Trigger/flag bit (process: PAT)
    const bool &Flag_trkPOG_logErrorTooManyClusters(); // Trigger/flag bit (process: PAT)
    const bool &Flag_trkPOG_manystripclus53X(); // Trigger/flag bit (process: PAT)
    const bool &Flag_trkPOG_toomanystripclus53X(); // Trigger/flag bit (process: PAT)
    const vector<float> &FsrPhoton_dROverEt2(); // deltaR to associated muon divided by photon et2
    const vector<float> &FsrPhoton_eta(); // eta
    const vector<int> &FsrPhoton_muonIdx(); // index of associated muon
    const vector<float> &FsrPhoton_phi(); // phi
    const vector<float> &FsrPhoton_pt(); // pt
    const vector<float> &FsrPhoton_relIso03(); // relative isolation in a 0.3 cone without CHS
    const vector<float> &GenDressedLepton_eta(); // eta
    const vector<bool> &GenDressedLepton_hasTauAnc(); // true if Dressed lepton has a tau as ancestor
    const vector<float> &GenDressedLepton_mass(); // mass
    const vector<LorentzVector> &GenDressedLepton_p4(); // from GenDressedLepton_pt,eta,phi,mass
    const vector<int> &GenDressedLepton_pdgId(); // PDG id
    const vector<float> &GenDressedLepton_phi(); // phi
    const vector<float> &GenDressedLepton_pt(); // pt
    const vector<float> &GenIsolatedPhoton_eta(); // eta
    const vector<float> &GenIsolatedPhoton_mass(); // mass
    const vector<LorentzVector> &GenIsolatedPhoton_p4(); // from GenIsolatedPhoton_pt,eta,phi,mass
    const vector<float> &GenIsolatedPhoton_phi(); // phi
    const vector<float> &GenIsolatedPhoton_pt(); // pt
    const vector<float> &GenJetAK8_eta(); // eta
    const vector<UChar_t> &GenJetAK8_hadronFlavour(); // flavour from hadron ghost clustering
    const vector<float> &GenJetAK8_mass(); // mass
    const vector<LorentzVector> &GenJetAK8_p4(); // from GenJetAK8_pt,eta,phi,mass
    const vector<int> &GenJetAK8_partonFlavour(); // flavour from parton matching
    const vector<float> &GenJetAK8_phi(); // phi
    const vector<float> &GenJetAK8_pt(); // pt
    const vector<float> &GenJet_eta(); // eta
    const vector<UChar_t> &GenJet_hadronFlavour(); // flavour from hadron ghost clustering
    const vector<float> &GenJet_mass(); // mass
    const vector<LorentzVector> &GenJet_p4(); // from GenJet_pt,eta,phi,mass
    const vector<int> &GenJet_partonFlavour(); // flavour from parton matching
    const vector<float> &GenJet_phi(); // phi
    const vector<float> &GenJet_pt(); // pt
    const float &GenMET_phi(); // phi
    const float &GenMET_pt(); // pt
    const vector<float> &GenPart_eta(); // eta
    const vector<int> &GenPart_genPartIdxMother(); // index of the mother particle
    const vector<float> &GenPart_mass(); // Mass stored for all particles with the exception of quarks (except top), leptons/neutrinos, photons with mass < 1 GeV, gluons, pi0(111), pi+(211), D0(421), and D+(411). For these particles, you can lookup the value from PDG.
    const vector<LorentzVector> &GenPart_p4(); // from GenPart_pt,eta,phi,mass
    const vector<int> &GenPart_pdgId(); // PDG id
    const vector<float> &GenPart_phi(); // phi
    const vector<float> &GenPart_pt(); // pt
    const vector<int> &GenPart_status(); // Particle status. 1=stable
    const vector<int> &GenPart_statusFlags(); // gen status flags stored bitwise, bits are: 0 : isPrompt, 1 : isDecayedLeptonHadron, 2 : isTauDecayProduct, 3 : isPromptTauDecayProduct, 4 : isDirectTauDecayProduct, 5 : isDirectPromptTauDecayProduct, 6 : isDirectHadronDecayProduct, 7 : isHardProcess, 8 : fromHardProcess, 9 : isHardProcessTauDecayProduct, 10 : isDirectHardProcessTauDecayProduct, 11 : fromHardProcessBeforeFSR, 12 : isFirstCopy, 13 : isLastCopy, 14 : isLastCopyBeforeFSR, 
    const vector<int> &GenVisTau_charge(); // charge
    const vector<float> &GenVisTau_eta(); // eta
    const vector<int> &GenVisTau_genPartIdxMother(); // index of the mother particle
    const vector<float> &GenVisTau_mass(); // mass
    const vector<LorentzVector> &GenVisTau_p4(); // from GenVisTau_pt,eta,phi,mass
    const vector<float> &GenVisTau_phi(); // phi
    const vector<float> &GenVisTau_pt(); // pt
    const vector<int> &GenVisTau_status(); // Hadronic tau decay mode. 0=OneProng0PiZero, 1=OneProng1PiZero, 2=OneProng2PiZero, 10=ThreeProng0PiZero, 11=ThreeProng1PiZero, 15=Other
    const float &Generator_binvar(); // MC generation binning value
    const int &Generator_id1(); // id of first parton
    const int &Generator_id2(); // id of second parton
    const float &Generator_scalePDF(); // Q2 scale for PDF
    const float &Generator_weight(); // MC generator weight
    const float &Generator_x1(); // x1 fraction of proton momentum carried by the first parton
    const float &Generator_x2(); // x2 fraction of proton momentum carried by the second parton
    const float &Generator_xpdf1(); // x*pdf(x) for the first parton
    const float &Generator_xpdf2(); // x*pdf(x) for the second parton
    const bool &HLT_AK4CaloJet100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4CaloJet120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4CaloJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4CaloJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4CaloJet50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4CaloJet80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4PFJet100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4PFJet120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4PFJet50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK4PFJet80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet250_200_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet280_200_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet300_200_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT650_TrimR0p1PT0p03Mass50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT700_TrimR0p1PT0p03Mass50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT750_TrimMass50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT800_TrimMass50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT850_TrimMass50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFHT900_TrimMass50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet25(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet260(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet320(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet360_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet380_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet400_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet420_TrimMass30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet550(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJet80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd25(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd260(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd320(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_AK8PFJetFwd80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet110_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet110_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet170_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet170_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet20_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet20_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet40_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet40_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet70_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4DiJet70_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4Jet300_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK4Jet300_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK8DiJet170_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK8DiJet170_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK8Jet170_DoubleMu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK8Jet170_DoubleMu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK8Jet300_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_AK8Jet300_Mu5_noalgo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_DiJet110_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_DiJet170_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_DiJet20_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_DiJet40_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_DiJet70_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_BTagMu_Jet300_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CDC_L2cosmic_5_er1p0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CDC_L2cosmic_5p5_er1p0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloJet260(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloJet500_NoJetID(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloJet550_NoJetID(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET100_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET100_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET110_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET250_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET250_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET300_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET350_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET70_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET80_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET80_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET90_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMET90_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMHT90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiCentralPFJet170(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiCentralPFJet170_CFMax0p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiCentralPFJet220_CFMax0p3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiCentralPFJet330_CFMax0p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiCentralPFJet430(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiEle27_WPTightCaloOnly_L1DoubleEG(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiJet110_35_Mjj650_PFMET110(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiJet110_35_Mjj650_PFMET120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiJet110_35_Mjj650_PFMET130(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiMu4_Ele9_CaloIdL_TrackIdL_DZ_Mass3p8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiMu9_Ele9_CaloIdL_TrackIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJet15_FBEta3_NoCaloMatched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJet15_NoCaloMatched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJet25_FBEta3_NoCaloMatched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJet25_NoCaloMatched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve100_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve15_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve160_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve220_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve25_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve260(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve300_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve320(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve35_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve60_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiPFJetAve80_HFJEC(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DiSC30_18_EIso_AND_HE_Mass70(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi3p5_Muon2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi_L1_4R_0er1p5R(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi_L1_NoOS(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi_Muon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi_NoVertexing(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Jpsi_NoVertexing_NoOS(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_LowMass(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_LowMass_L1_0er1p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_LowMass_L1_0er1p5R(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_LowMass_L1_4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_LowMass_L1_4R(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_LowMass_L1_TM530(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Phi_Barrel(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_L1_4p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_L1_4p5NoOS(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_L1_4p5er2p0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_L1_4p5er2p0M(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_L1_5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_L1_5M(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_Muon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_Muon_L1_TM0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_Muon_NoL1Mass(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0_Upsilon_NoVertexing(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon0er16_Jpsi_NoVertexing(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon10_Jpsi_Barrel(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon10_PsiPrime_Barrel_Seagulls(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon12_Upsilon_y1p4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon13_PsiPrime(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon13_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon14_Phi_Barrel_Seagulls(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon16_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon18_PsiPrime(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon18_PsiPrime_noCorrL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon20_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon20_Jpsi_Barrel_Seagulls(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon24_Phi_noCorrL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon24_Upsilon_noCorrL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon25_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon25_Jpsi_noCorrL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon6_Jpsi_NoVertexing(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon8_PsiPrime_Barrel(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Dimuon8_Upsilon_Barrel(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle24_eta2p1_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle25_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle25_CaloIdL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle27_CaloIdL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle33_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle33_CaloIdL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleIsoMu17_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleIsoMu17_eta2p1_noDzCut(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleIsoMu20_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJet90_Double30_DoubleBTagCSV_p087(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJet90_Double30_TripleBTagCSV_p087(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p014(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p026(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_NoL2Matched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu23NoVtx_2Cha_NoL2Matched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_Eta2p4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_NoL2Matched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu25NoVtx_2Cha_NoL2Matched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu30NoVtx_2Cha_CosmicSeed_Eta2p4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleL2Mu50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu18NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu20_7_Mass0to30_L1_DM4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu20_7_Mass0to30_L1_DM4EG(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu20_7_Mass0to30_Photon23(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu23NoFiltersNoVtxDisplaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu28NoFiltersNoVtxDisplaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu33NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu33NoFiltersNoVtxDisplaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu38NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_DCA_PFMET50_PFMHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_DZ_PFMET50_PFMHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_DZ_PFMET70_PFMHT70(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_DZ_PFMET90_PFMHT90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_TkMu_DsTau3Mu(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_Trk_Tau3mu(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu40NoFiltersNoVtxDisplaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu43NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu48NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_3_Bs(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_3_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_3_Jpsi_Displaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_JpsiTrkTrk_Displaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_JpsiTrk_Displaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_Jpsi_Displaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_Jpsi_NoVertexing(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_LowMassNonResonantTrk_Displaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_Mass3p8_DZ_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu4_PsiPrimeTrk_Displaced(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu8_Mass8_PFHT250(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleMu8_Mass8_PFHT300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePFJets100_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePFJets200_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePFJets350_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePFJets40_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePhoton33_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePhoton60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePhoton70(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoublePhoton85(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_DoubleTrkMu_16_6_NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ECALHT800(); // Trigger/flag bit (process: HLT)
    const bool &HLT_EcalCalibration(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele105_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele115_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele12_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele12_CaloIdM_TrackIdM_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele135_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele145_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT350_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT400_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT450_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_IsoVVVL_PFHT600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele15_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_CaloIdM_TrackIdM_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_Ele8_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele17_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele200_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele20_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele20_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele20_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele22_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_CaloIdM_TrackIdM_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele23_WPLoose_Gsf_WHbbBoost(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele250_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele25_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele25_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele25_eta2p1_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_Ele37_CaloIdL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_HighEta_Ele20_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_WPLoose_Gsf_WHbbBoost(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_WPTight_Gsf_L1JetTauSeeded(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_eta2p1_WPLoose_Gsf_HT200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele27_eta2p1_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele28_HighEta_SC20_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele28_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele28_eta2p1_WPTight_Gsf_HT150(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele300_CaloIdVT_GsfTrkIdT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele30WP60_Ele8_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele30WP60_SC4_Mass55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele30_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele30_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele30_eta2p1_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele32_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele32_WPTight_Gsf_L1DoubleEG(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele32_eta2p1_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele32_eta2p1_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele35_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele35_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele35_WPTight_Gsf_L1EGMT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele38_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele40_WPTight_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele45_WPLoose_Gsf(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele50_IsoVVVL_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele50_IsoVVVL_PFHT450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Ele8_CaloIdM_TrackIdM_PFJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_FullTracks_Multiplicity100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_FullTracks_Multiplicity130(); // Trigger/flag bit (process: HLT)
    const bool &HLT_FullTracks_Multiplicity150(); // Trigger/flag bit (process: HLT)
    const bool &HLT_FullTracks_Multiplicity80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_GlobalRunHPDNoise(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HISinglePhoton10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HISinglePhoton15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HISinglePhoton20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HISinglePhoton40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HISinglePhoton60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT2000(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT200_DisplacedDijet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT2500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT250_CaloMET70(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT250_DisplacedDijet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT275(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT300_Beamspot(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT325(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT350_DisplacedDijet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT350_DisplacedDijet40_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT350_DisplacedDijet80_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT400_DisplacedDijet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT400_DisplacedDijet40_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT410to430(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT425(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT430_DisplacedDijet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT430_DisplacedDijet60_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT430to450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT450_Beamspot(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT450to470(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT470to500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT500_DisplacedDijet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT500_DisplacedDijet40_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT500to550(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT550_DisplacedDijet40_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT550_DisplacedDijet60_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT550_DisplacedDijet80_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT550to650(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT575(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT650(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT650_DisplacedDijet60_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT650_DisplacedDijet80_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HT750_DisplacedDijet80_Inclusive(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HcalCalibration(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HcalIsolatedbunch(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HcalNZS(); // Trigger/flag bit (process: HLT)
    const bool &HLT_HcalPhiSym(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu16_eta2p1_MET30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu17_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu17_eta2p1_LooseIsoPFTau20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu18(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu19_eta2p1_LooseIsoPFTau20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu22(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu22_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_TwoProngs35(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu27(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu27_MET90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoMu30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTkMu18(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTkMu20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTkMu22(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTkMu22_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTkMu24(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTkMu27(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTrackHB(); // Trigger/flag bit (process: HLT)
    const bool &HLT_IsoTrackHE(); // Trigger/flag bit (process: HLT)
    const bool &HLT_JetE30_NoBPTX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_JetE30_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_JetE50_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_JetE70_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1BeamGasMinus(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1BeamGasPlus(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1BptxMinus(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1BptxPlus(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1BptxXOR(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1ETMHadSeeds(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1FatEvents(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1FatEvents_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1FatEvents_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1FatEvents_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1FatEvents_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1MinimumBiasHF_AND(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1MinimumBiasHF_OR(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1NotBptxOR(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1SingleMu18(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1SingleMu25(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1SingleMuOpen(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1SingleMuOpen_DT(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1UnpairedBunchBptxMinus(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1UnpairedBunchBptxPlus(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L1_TripleJet_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2DoubleMu23_NoVertex(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu10_NoVertex_NoBPTX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu10_NoVertex_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu23NoVtx_2Cha(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu23NoVtx_2Cha_CosmicSeed(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_L2Mu50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110(); // Trigger/flag bit (process: HLT)
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET105_IsoTrk50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET120_IsoTrk50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET150(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET250(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET60_IsoTrk35_Loose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET700(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET75_IsoTrk50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MET90_IsoTrk50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau200HighPtRelaxedIso_Trk50_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau220HighPtRelaxedIso_Trk50_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu10_CentralPFJet30_BTagCSV_p13(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_DoublePhoton20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_IP6_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_IP6_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_IP6_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_IP6_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_IP6_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_Photon25_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_Photon25_CaloIdL_L1ISO(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_Photon25_CaloIdL_L1OR(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu14er_PFMET100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT350_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT400_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT450_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu15_IsoVVVL_PFHT600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu16_TkMu0_dEta18_Onia(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu16_TkMu0_dEta18_Phi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu16_eta2p1_MET30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Mu8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Mu8_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Mu8_SameSign(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Mu8_SameSign_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Photon22_CaloIdL_L1ISO(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Photon30_CaloIdL_L1ISO(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Photon30_IsoCaloId(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_Photon35_CaloIdL_L1ISO(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TkMu8_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu18_Mu9(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu18_Mu9_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu18_Mu9_SameSign(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu18_Mu9_SameSign_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu19(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu19_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu20_Mu10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu20_Mu10_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu20_Mu10_SameSign(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu20_Mu10_SameSign_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu20_TkMu0_Phi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_Mu12(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_Mu12_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_Mu12_SameSign(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_Mu12_SameSign_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu24_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu25_TkMu0_Onia(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu25_TkMu0_Phi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu25_TkMu0_dEta18_Onia(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu27(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu27_Ele37_CaloIdL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu27_TkMu8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu28NoFiltersNoVtx_CentralCaloJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu30_TkMu0_Psi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu30_TkMu0_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu30_TkMu11(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu30_eta2p1_PFJet150_PFJet50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu37_Ele27_CaloIdL_MW(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu37_TkMu27(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3_L1SingleMu5orSingleMu7(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3_PFJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu3er_PFHT140_PFMET125(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu40_TkMu11(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu40_eta2p1_PFJet200_PFJet50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu45_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu50_IsoVVVL_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu50_IsoVVVL_PFHT450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu6_PFHT200_PFMET100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7_IP4_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7_IP4_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7_IP4_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7_IP4_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7_IP4_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_L2Mu2_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_L2Mu2_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_Track2_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_Track2_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_Track3p5_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_Track3p5_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_Track7_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu7p5_Track7_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_DiEle12_CaloIdL_TrackIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP3_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP3_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP3_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP3_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP3_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP5_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP5_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP5_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP5_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP5_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP6_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP6_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP6_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP6_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_IP6_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP4_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP4_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP4_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP4_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP4_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP5_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP5_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP5_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP5_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP5_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP6_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP6_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP6_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP6_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Mu9_IP6_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_OldMu100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT1050(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT125(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT180(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT200_PFAlphaT0p51(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT250(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT300_PFMET100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT300_PFMET110(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT330PT30_QuadPFJet_75_60_45_40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT350(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT350MinPFJet15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT370(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400_SixJet30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400_SixPFJet32(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT430(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT450_SixJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT450_SixJet40_BTagCSV_p056(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT450_SixPFJet36(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT475(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT500_PFMET100_PFMHT100_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT500_PFMET110_PFMHT110_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT510(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT550_4JetPt50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT590(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT650(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT650_4JetPt50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT650_WideJetMJJ900DEtaJJ1p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT650_WideJetMJJ950DEtaJJ1p5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT680(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT700_PFMET85_PFMHT85_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT700_PFMET95_PFMHT95_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT750_4JetPt50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT750_4JetPt70(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT750_4JetPt80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT780(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT800(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT800_4JetPt50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT800_PFMET75_PFMHT75_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT800_PFMET85_PFMHT85_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT850_4JetPt50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT890(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFHT900(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet15_NoCaloMatched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet25(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet25_NoCaloMatched(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet260(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet320(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet550(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJet80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd140(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd25(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd260(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd320(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd450(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFJetFwd80(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET100_PFMHT100_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET100_PFMHT100_IDTight_PFHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET110_PFMHT110_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET120_BTagCSV_p067(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET120_Mu5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET120_PFMHT120_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET120_PFMHT120_IDTight_PFHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET130_PFMHT130_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET140_PFMHT140_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET170_BeamHaloCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET170_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET170_HBHE_BeamHaloCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET170_JetIdCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET170_NoiseCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET170_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET200_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET200_HBHE_BeamHaloCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET200_NotCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET250_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET300_HBHECleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET400(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMET90_PFMHT90_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu100_PFMHTNoMu100_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu110_PFMHTNoMu110_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu130_PFMHTNoMu130_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu140_PFMHTNoMu140_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETNoMu90_PFMHTNoMu90_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne110_PFMHT110_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne120_PFMHT120_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne130_PFMHT130_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne140_PFMHT140_IDTight(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFTau120_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PFTau140_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon100EBHE10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon100EB_TightID_TightIso(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon100EEHE10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon100EE_TightID_TightIso(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon110EB_TightID_TightIso(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon120EB_TightID_TightIso(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon120_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon125(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon135_PFMET100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon150(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon165_HE10(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon165_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon175(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon20_CaloIdVL_IsoL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon20_HoverELoose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon22(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon22_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon250_NoHE(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon26_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon16_AND_HE10_R9Id65_Eta2_Mass60(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon300_NoHE(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon30_HoverELoose(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon30_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon33(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon35_TwoProngs35(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon36(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon36_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon22_AND_HE10_R9Id65_Eta2_Mass15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon36_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon50_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon60_R9Id90_CaloIdL_IsoL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_CaloIdL_HT300(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_CaloIdL_PFHT500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_CaloIdL_PFHT600(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_CaloIdL_PFHT700(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Photon90_R9Id90_HE10_IsoM(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part6(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Physics_part7(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PixelTracks_Multiplicity110ForEndOfFill(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PixelTracks_Multiplicity135ForEndOfFill(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PixelTracks_Multiplicity160ForEndOfFill(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PixelTracks_Multiplicity60ForEndOfFill(); // Trigger/flag bit (process: HLT)
    const bool &HLT_PixelTracks_Multiplicity85ForEndOfFill(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadJet45_DoubleBTagCSV_p087(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadJet45_TripleBTagCSV_p087(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadMuon0_Dimuon0_Jpsi(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadMuon0_Dimuon0_Upsilon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet103_88_75_15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet103_88_75_15_PFBTagDeepCSV_1p3_VBF2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet105_88_76_15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet105_88_76_15_PFBTagDeepCSV_1p3_VBF2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet111_90_80_15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet111_90_80_15_PFBTagDeepCSV_1p3_VBF2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet98_83_71_15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet98_83_71_15_DoublePFBTagDeepCSV_1p3_7p7_VBF1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet98_83_71_15_PFBTagDeepCSV_1p3_VBF2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240(); // Trigger/flag bit (process: HLT)
    const bool &HLT_QuadPFJet_VBF(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Random(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p02_MR400_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p25(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p25_Calo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p30(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p35(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Rsq0p40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR240_Rsq0p09_MR200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR240_Rsq0p09_MR200_4jet(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR240_Rsq0p09_MR200_4jet_Calo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR240_Rsq0p09_MR200_Calo(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR270_Rsq0p09_MR200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR270_Rsq0p09_MR200_4jet(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR300_Rsq0p09_MR200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR300_Rsq0p09_MR200_4jet(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR320_Rsq0p09_MR200(); // Trigger/flag bit (process: HLT)
    const bool &HLT_RsqMR320_Rsq0p09_MR200_4jet(); // Trigger/flag bit (process: HLT)
    const bool &HLT_SingleCentralPFJet170_CFMax0p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_SingleJet30_Mu12_SinglePFJet40(); // Trigger/flag bit (process: HLT)
    const bool &HLT_SinglePhoton10_Eta3p1ForPPRef(); // Trigger/flag bit (process: HLT)
    const bool &HLT_SinglePhoton20_Eta3p1ForPPRef(); // Trigger/flag bit (process: HLT)
    const bool &HLT_SinglePhoton30_Eta3p1ForPPRef(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu100(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu17(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu20(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu24_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu27(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TkMu50(); // Trigger/flag bit (process: HLT)
    const bool &HLT_Trimuon5_3p5_2_Upsilon_Muon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleJet110_35_35_Mjj650_PFMET110(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleJet110_35_35_Mjj650_PFMET120(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleJet110_35_35_Mjj650_PFMET130(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleMu_10_5_5_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleMu_12_10_5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleMu_5_3_3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleMu_5_3_3_Mass3p8_DCA(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TripleMu_5_3_3_Mass3p8_DZ(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TriplePhoton_20_20_20_CaloIdLV2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TriplePhoton_30_30_10_CaloIdLV2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrkMu16NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_TrkMu6NoFiltersNoVtx(); // Trigger/flag bit (process: HLT)
    const bool &HLT_UncorrectedJetE30_NoBPTX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_UncorrectedJetE30_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_UncorrectedJetE60_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_UncorrectedJetE70_NoBPTX3BX(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_Hadronic(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_TightID_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_TightID_Hadronic(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_VTightID_Hadronic(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DisplacedJet40_VVTightID_Hadronic(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DoubleMediumChargedIsoPFTauHPS20_Trk1_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VLooseIsoPFTau120_Trk50_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_VLooseIsoPFTau140_Trk50_eta2p1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_Alignment(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_Beamspot(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_FirstBXAfterTrain(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_FirstCollisionAfterAbortGap(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_FirstCollisionAfterAbortGap_TCDS(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_FirstCollisionAfterAbortGap_copy(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_FirstCollisionInTrain(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_IsolatedBunches(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_LastCollisionInTrain(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part0(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part1(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part2(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part3(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part4(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part5(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part6(); // Trigger/flag bit (process: HLT)
    const bool &HLT_ZeroBias_part7(); // Trigger/flag bit (process: HLT)
    const bool &HLTriggerFinalPath(); // Trigger/flag bit (process: HLT)
    const bool &HLTriggerFirstPath(); // Trigger/flag bit (process: HLT)
    const float &HTXS_Higgs_pt(); // pt of the Higgs boson as identified in HTXS
    const float &HTXS_Higgs_y(); // rapidity of the Higgs boson as identified in HTXS
    const UChar_t &HTXS_njets25(); // number of jets with pt>25 GeV as identified in HTXS
    const UChar_t &HTXS_njets30(); // number of jets with pt>30 GeV as identified in HTXS
    const int &HTXS_stage1_1_cat_pTjet25GeV(); // HTXS stage-1.1 category(jet pt>25 GeV)
    const int &HTXS_stage1_1_cat_pTjet30GeV(); // HTXS stage-1.1 category(jet pt>30 GeV)
    const int &HTXS_stage1_1_fine_cat_pTjet25GeV(); // HTXS stage-1.1-fine category(jet pt>25 GeV)
    const int &HTXS_stage1_1_fine_cat_pTjet30GeV(); // HTXS stage-1.1-fine category(jet pt>30 GeV)
    const int &HTXS_stage1_2_cat_pTjet25GeV(); // HTXS stage-1.2 category(jet pt>25 GeV)
    const int &HTXS_stage1_2_cat_pTjet30GeV(); // HTXS stage-1.2 category(jet pt>30 GeV)
    const int &HTXS_stage1_2_fine_cat_pTjet25GeV(); // HTXS stage-1.2-fine category(jet pt>25 GeV)
    const int &HTXS_stage1_2_fine_cat_pTjet30GeV(); // HTXS stage-1.2-fine category(jet pt>30 GeV)
    const int &HTXS_stage_0(); // HTXS stage-0 category
    const int &HTXS_stage_1_pTjet25(); // HTXS stage-1 category (jet pt>25 GeV)
    const int &HTXS_stage_1_pTjet30(); // HTXS stage-1 category (jet pt>30 GeV)
    const vector<float> &IsoTrack_dxy(); // dxy (with sign) wrt first PV, in cm
    const vector<float> &IsoTrack_dz(); // dz (with sign) wrt first PV, in cm
    const vector<float> &IsoTrack_eta(); // eta
    const vector<int> &IsoTrack_fromPV(); // isolated track comes from PV
    const vector<bool> &IsoTrack_isFromLostTrack(); // if isolated track comes from a lost track
    const vector<bool> &IsoTrack_isHighPurityTrack(); // track is high purity
    const vector<bool> &IsoTrack_isPFcand(); // if isolated track is a PF candidate
    const vector<float> &IsoTrack_miniPFRelIso_all(); // mini PF relative isolation, total (with scaled rho*EA PU corrections)
    const vector<float> &IsoTrack_miniPFRelIso_chg(); // mini PF relative isolation, charged component
    const vector<int> &IsoTrack_pdgId(); // PDG id of PF cand
    const vector<float> &IsoTrack_pfRelIso03_all(); // PF relative isolation dR=0.3, total (deltaBeta corrections)
    const vector<float> &IsoTrack_pfRelIso03_chg(); // PF relative isolation dR=0.3, charged component
    const vector<float> &IsoTrack_phi(); // phi
    const vector<float> &IsoTrack_pt(); // pt
    const vector<float> &Jet_area(); // jet catchment area, for JECs
    const vector<float> &Jet_bRegCorr(); // pt correction for b-jet energy regression
    const vector<float> &Jet_bRegRes(); // res on pt corrected with b-jet regression
    const vector<float> &Jet_btagCMVA(); // CMVA V2 btag discriminator
    const vector<float> &Jet_btagCSVV2(); //  pfCombinedInclusiveSecondaryVertexV2 b-tag discriminator (aka CSVV2)
    const vector<float> &Jet_btagDeepB(); // DeepCSV b+bb tag discriminator
    const vector<float> &Jet_btagDeepC(); // DeepCSV charm btag discriminator
    const vector<float> &Jet_btagDeepFlavB(); // DeepFlavour b+bb+lepb tag discriminator
    const vector<float> &Jet_btagDeepFlavC(); // DeepFlavour charm tag discriminator
    const vector<float> &Jet_cRegCorr(); // pt correction for c-jet energy regression
    const vector<float> &Jet_cRegRes(); // res on pt corrected with c-jet regression
    const vector<float> &Jet_chEmEF(); // charged Electromagnetic Energy Fraction
    const vector<float> &Jet_chFPV0EF(); // charged fromPV==0 Energy Fraction (energy excluded from CHS jets). Previously called betastar.
    const vector<float> &Jet_chFPV1EF(); // charged fromPV==1 Energy Fraction (component of the total charged Energy Fraction).
    const vector<float> &Jet_chFPV2EF(); // charged fromPV==2 Energy Fraction (component of the total charged Energy Fraction).
    const vector<float> &Jet_chFPV3EF(); // charged fromPV==3 Energy Fraction (component of the total charged Energy Fraction).
    const vector<float> &Jet_chHEF(); // charged Hadron Energy Fraction
    const vector<UChar_t> &Jet_cleanmask(); // simple cleaning mask with priority to leptons
    const vector<int> &Jet_electronIdx1(); // index of first matching electron
    const vector<int> &Jet_electronIdx2(); // index of second matching electron
    const vector<float> &Jet_eta(); // eta
    const vector<int> &Jet_genJetIdx(); // index of matched gen jet
    const vector<int> &Jet_hadronFlavour(); // flavour from hadron ghost clustering
    const vector<int> &Jet_jetId(); // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
    const vector<float> &Jet_mass(); // mass
    const vector<float> &Jet_muEF(); // muon Energy Fraction
    const vector<int> &Jet_muonIdx1(); // index of first matching muon
    const vector<int> &Jet_muonIdx2(); // index of second matching muon
    const vector<float> &Jet_muonSubtrFactor(); // 1-(muon-subtracted raw pt)/(raw pt)
    const vector<int> &Jet_nConstituents(); // Number of particles in the jet
    const vector<int> &Jet_nElectrons(); // number of electrons in the jet
    const vector<int> &Jet_nMuons(); // number of muons in the jet
    const vector<float> &Jet_neEmEF(); // neutral Electromagnetic Energy Fraction
    const vector<float> &Jet_neHEF(); // neutral Hadron Energy Fraction
    const vector<LorentzVector> &Jet_p4(); // from Jet_pt,eta,phi,mass
    const vector<int> &Jet_partonFlavour(); // flavour from parton matching
    const vector<float> &Jet_phi(); // phi
    const vector<float> &Jet_pt(); // pt
    const vector<int> &Jet_puId(); // Pilup ID flags with 80X (2016) training
    const vector<float> &Jet_puIdDisc(); // Pilup ID discriminant with 102X (2018) training
    const vector<float> &Jet_qgl(); // Quark vs Gluon likelihood discriminator
    const vector<float> &Jet_rawFactor(); // 1 - Factor to get back to raw pT
    const float &L1PreFiringWeight_Dn(); // L1 pre-firing event correction weight (1-probability), down var.
    const float &L1PreFiringWeight_Nom(); // L1 pre-firing event correction weight (1-probability)
    const float &L1PreFiringWeight_Up(); // L1 pre-firing event correction weight (1-probability), up var.
    const bool &L1Reco_step(); // Trigger/flag bit (process: RECO)
    const bool &L1_AlwaysTrue(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_AND_Ref1_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_AND_Ref3_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_AND_Ref4_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_BeamGas_B1_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_BeamGas_B2_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_BeamGas_Ref1_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_BeamGas_Ref2_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_NotOR_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_OR_Ref3_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_OR_Ref4_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BPTX_RefAND_VME(); // Trigger/flag bit (process: NANO)
    const bool &L1_BRIL_TRIG0_AND(); // Trigger/flag bit (process: NANO)
    const bool &L1_BRIL_TRIG0_FstBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_BRIL_TRIG0_OR(); // Trigger/flag bit (process: NANO)
    const bool &L1_BRIL_TRIG0_delayedAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_BeamGasB1(); // Trigger/flag bit (process: NANO)
    const bool &L1_BeamGasB2(); // Trigger/flag bit (process: NANO)
    const bool &L1_BeamGasMinus(); // Trigger/flag bit (process: NANO)
    const bool &L1_BeamGasPlus(); // Trigger/flag bit (process: NANO)
    const bool &L1_BptxMinus(); // Trigger/flag bit (process: NANO)
    const bool &L1_BptxOR(); // Trigger/flag bit (process: NANO)
    const bool &L1_BptxPlus(); // Trigger/flag bit (process: NANO)
    const bool &L1_BptxXOR(); // Trigger/flag bit (process: NANO)
    const bool &L1_CASTOR_Gap_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_CASTOR_HaloMuon(); // Trigger/flag bit (process: NANO)
    const bool &L1_CASTOR_HaloMuon_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_CASTOR_HighJet_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_CASTOR_MediumJet_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG6_HTT255(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG8er2p5_HTT260er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG8er2p5_HTT280er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG8er2p5_HTT300er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG8er2p5_HTT320er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG8er2p5_HTT340er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_15_10(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_15_10_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_18_17(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_20_10_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_20_18(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_22_10(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_22_10_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_22_12(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_22_15(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_23_10(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_24_17(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_25_12(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_25_12_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_25_14_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_27_14_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_LooseIso20_10_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_LooseIso22_10_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_LooseIso22_12_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleEG_LooseIso25_12_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau28er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau30er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau32er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau32er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau33er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau34er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau34er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau35er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau36er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleIsoTau36er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet100er2p3_dEta_Max1p6(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet100er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet112er2p3_dEta_Max1p6(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet120er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet12_ForwardBackward(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet150er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet16_ForwardBackward(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30_Mj30j30_400_Mu10(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30_Mj30j30_400_Mu6(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30er2p5_Mass_Min150_dEta_Max1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30er2p5_Mass_Min200_dEta_Max1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30er2p5_Mass_Min250_dEta_Max1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30er2p5_Mass_Min300_dEta_Max1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30er2p5_Mass_Min330_dEta_Max1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet30er2p5_Mass_Min360_dEta_Max1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet40er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet8_ForwardBackward(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC100(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC112(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC120(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC40(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC50(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC60(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC60_ETM60(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJetC80(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_100_30_DoubleJet30_Mass_Min620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_100_30_Mj30j30_620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_110_35_DoubleJet35_Mass_Min620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_115_40_DoubleJet40_Mass_Min620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_115_40_DoubleJet40_Mass_Min620_Jet60TT28(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_120_45_DoubleJet45_Mass_Min620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_120_45_DoubleJet45_Mass_Min620_Jet60TT28(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_80_30_Mass_Min420_DoubleMu0_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_80_30_Mass_Min420_IsoTau40_RmOvlp(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_80_30_Mass_Min420_Mu8(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_90_30_DoubleJet30_Mass_Min620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleJet_90_30_Mj30j30_620(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleLooseIsoEG22er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleLooseIsoEG24er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_ETM40(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_ETM55(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_ETM60(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_ETM65(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_ETM70(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_Mass_Min1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_OQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_SQ_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0_dR_Max1p6_Jet90er2p5_dR_Max0p8(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p4_dEta_Max1p8_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p5_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p5_SQ_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p5_SQ_dR_Max1p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p6_dEta_Max1p8(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er1p6_dEta_Max1p8_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er2p0_SQ_OS_dR_Max1p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu0er2p0_SQ_dR_Max1p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu10_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu18er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_OS_DoubleEG7p5Upsilon(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_ETMHF50_HTT60er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_ETMHF50_Jet60er2p5_OR_DoubleJet40er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_ETMHF60_Jet60er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_HTT220er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_HTT240er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_SQ_HTT260er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu3_dR_Max1p6_Jet90er2p5_dR_Max0p8(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4_SQ_EG9er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4_SQ_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4_SQ_OS_dR_Max1p2(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4p5_SQ_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4p5_SQ_OS_dR_Max1p2(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4p5er2p0_SQ_OS(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu5Upsilon_OS_DoubleEG3(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu5_SQ_EG9er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu7_EG14(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu7_EG7(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu9_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMuOpen(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_10_0_dEta_Max1p8(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_10_3p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_10_Open(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_11_4(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_12_5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_12_8(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_13_6(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_15_5(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_15_5_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_15_7(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_15_7_Mass_Min1(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleMu_15_7_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleTau50er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleTau70er(); // Trigger/flag bit (process: NANO)
    const bool &L1_DoubleTau70er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_EG25er_HTT125(); // Trigger/flag bit (process: NANO)
    const bool &L1_EG27er_HTT200(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM100(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM105(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM110(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM115(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM120(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM150(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM30(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM40(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM50(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM60(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM70(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM75(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM75_Jet60_dPhi_Min0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM80(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM85(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM90(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETM95(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF100(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF100_HTT60er(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF110(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF110_HTT60er(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF110_HTT60er_NotSecondBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF120(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF120_HTT60er(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF120_NotSecondBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF130(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF130_HTT60er(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF140(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF150(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETMHF90_HTT60er(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT1200(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT1600(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT2000(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT25(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT40_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT50_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT55_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT60_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT70_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_ETT75_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_FirstBunchAfterTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_FirstBunchBeforeTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_FirstBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_FirstCollisionInOrbit(); // Trigger/flag bit (process: NANO)
    const bool &L1_FirstCollisionInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_HCAL_LaserMon_Trig(); // Trigger/flag bit (process: NANO)
    const bool &L1_HCAL_LaserMon_Veto(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM100(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM120(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM130(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM140(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM150(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM50(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM60_HTT260(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM70(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM80(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTM80_HTT220(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT120(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT120er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT160(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT160er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT200(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT200er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT220(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT240(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT255(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT255er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT270(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT280(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT280er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT280er_QuadJet_70_55_40_35_er2p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT300(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT320(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT320er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT320er_QuadJet_70_55_40_40_er2p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT360er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT400er(); // Trigger/flag bit (process: NANO)
    const bool &L1_HTT450er(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG18er_IsoTau24er_dEta_Min0p2(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG20er_IsoTau25er_dEta_Min0p2(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG22er_IsoTau26er_dEta_Min0p2(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG22er_Tau20er_dEta_Min0p2(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG32er2p5_Mt40(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG32er2p5_Mt44(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoEG32er2p5_Mt48(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoTau40er2p1_ETMHF100(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoTau40er2p1_ETMHF110(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoTau40er2p1_ETMHF120(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsoTau40er2p1_ETMHF90(); // Trigger/flag bit (process: NANO)
    const bool &L1_IsolatedBunch(); // Trigger/flag bit (process: NANO)
    const bool &L1_Jet32_DoubleMu_10_0_dPhi_Jet_Mu0_Max0p4_dPhi_Mu_Mu_Min1p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_Jet32_Mu0_EG10_dPhi_Jet_Mu_Max0p4_dPhi_Mu_EG_Min1p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_LastBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_LastCollisionInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG22er2p1_IsoTau26er2p1_dR_Min0p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG22er2p1_Tau70er2p1_dR_Min0p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG24er2p1_HTT100er(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG24er2p1_IsoTau27er2p1_dR_Min0p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG26er2p1_HTT100er(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG26er2p1_Jet34er2p5_dR_Min0p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG28er2p1_HTT100er(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG28er2p1_Jet34er2p5_dR_Min0p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG30er2p1_HTT100er(); // Trigger/flag bit (process: NANO)
    const bool &L1_LooseIsoEG30er2p1_Jet34er2p5_dR_Min0p3(); // Trigger/flag bit (process: NANO)
    const bool &L1_MU20_EG15(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF0_AND(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF0_AND_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF0_OR(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF0_OR_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF1_AND(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF1_AND_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF1_OR(); // Trigger/flag bit (process: NANO)
    const bool &L1_MinimumBiasHF1_OR_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu0er_ETM40(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu0er_ETM55(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu10er2p3_Jet32er2p3_dR_Max0p4_DoubleJet32er2p3_dEta_Max1p6(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu10er_ETM30(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu10er_ETM50(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu12_EG10(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu12er2p3_Jet40er2p1_dR_Max0p4_DoubleJet40er2p1_dEta_Max1p6(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu12er2p3_Jet40er2p3_dR_Max0p4_DoubleJet40er2p3_dEta_Max1p6(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu14er_ETM30(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu16er_Tau20er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu16er_Tau24er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu18er2p1_Tau24er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu18er2p1_Tau26er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu18er_IsoTau26er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu18er_Tau20er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu18er_Tau24er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu20_EG10(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu20_EG10er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu20_EG17(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu20_IsoEG6(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu20er_IsoTau26er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu22er2p1_IsoTau32er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu22er2p1_IsoTau34er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu22er2p1_IsoTau36er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu22er2p1_IsoTau40er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu22er2p1_Tau70er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu22er_IsoTau26er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu23_EG10(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu23_IsoEG10(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu25er_IsoTau26er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet120er2p5_dR_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet120er2p5_dR_Max0p8(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet16er2p5_dR_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet30er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet35er2p5_dR_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet60er2p5_dR_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_Jet80er2p5_dR_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_JetC120(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_JetC120_dEta_Max0p4_dPhi_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_JetC16(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_JetC16_dEta_Max0p4_dPhi_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_JetC60(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3_JetC60_dEta_Max0p4_dPhi_Max0p4(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3er1p5_Jet100er2p5_ETMHF40(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu3er1p5_Jet100er2p5_ETMHF50(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_EG15(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_EG20(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_EG23(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_EG23er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_IsoEG18(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_IsoEG20(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu5_LooseIsoEG20er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_DoubleEG10(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_DoubleEG10er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_DoubleEG12er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_DoubleEG15er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_DoubleEG17(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_DoubleEG17er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_HTT200(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_HTT240er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu6_HTT250er(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu7_EG23er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu7_LooseIsoEG20er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu7_LooseIsoEG23er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_Mu8_HTT150(); // Trigger/flag bit (process: NANO)
    const bool &L1_NotBptxOR(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJet36er2p5_IsoTau52er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJet60er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJetC36_Tau52(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJetC40(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJetC50(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJetC60(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadJet_95_75_65_20_DoubleJet_75_65_er2p5_Jet20_FWD3p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadMu0(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadMu0_OQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_QuadMu0_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_SecondBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_SecondLastBunchInTrain(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG10(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG10er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG15(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG15er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG18(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG24(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG26(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG26er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG28(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG2_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG30(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG32(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG34(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG34er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG36(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG36er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG38(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG38er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG40(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG40er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG42er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG45(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG45er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG50(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG60(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleEG8er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG18(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG18er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG20(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG20er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG22(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG22er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG24(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG24er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG24er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG24er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG26(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG26er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG26er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG26er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG26er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG28(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG28er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG28er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG28er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG28er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG30(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG30er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG30er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG30er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG32(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG32er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG32er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG32er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG34(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG34er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG34er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleIsoEG36(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet10erHE(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet120(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet120_FWD3p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet120er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet12_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet12erHE(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet140(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet140er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet140er2p5_ETMHF80(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet140er2p5_ETMHF90(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet150(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet16(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet160(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet160er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet170(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet180(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet180er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet20(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet200(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet20er2p5_NotBptxOR(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet20er2p5_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet35(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet35_FWD3p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet35er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet43er2p5_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet46er2p5_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet60(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet60_FWD3p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet60er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet8_BptxAND(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet8erHE(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet90(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet90_FWD3p0(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJet90er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJetC20_NotBptxOR(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJetC20_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJetC40_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleJetC40_NotBptxOR_5BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleLooseIsoEG28er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleLooseIsoEG30er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu0_BMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu0_DQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu0_EMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu0_OMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu10_LowQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu10er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu12(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu12_DQ_BMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu12_DQ_EMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu12_DQ_OMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu12er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu14(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu14er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu14er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu15_DQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu16(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu16er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu16er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu18(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu18er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu18er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu20(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu20er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu22(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu22_BMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu22_EMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu22_OMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu22er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu25(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu25er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu3(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu30(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu30er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu6er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu7(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu7_DQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu7er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu8er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMu9er1p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuCosmics(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuCosmics_BMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuCosmics_EMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuCosmics_OMTF(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuOpen(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuOpen_NotBptxOR(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuOpen_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuOpen_er1p1_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleMuOpen_er1p4_NotBptxOR_3BX(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleTau100er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleTau120er(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleTau120er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleTau130er2p1(); // Trigger/flag bit (process: NANO)
    const bool &L1_SingleTau80er(); // Trigger/flag bit (process: NANO)
    const bool &L1_TOTEM_1(); // Trigger/flag bit (process: NANO)
    const bool &L1_TOTEM_2(); // Trigger/flag bit (process: NANO)
    const bool &L1_TOTEM_3(); // Trigger/flag bit (process: NANO)
    const bool &L1_TOTEM_4(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG16er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG_14_10_8(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG_16_12_8_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG_16_15_8_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG_18_17_8(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG_18_17_8_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleEG_18_18_12_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleJet_100_80_70_DoubleJet_80_70_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleJet_105_85_75_DoubleJet_85_75_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleJet_84_68_48_VBF(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleJet_88_72_56_VBF(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleJet_92_76_64_VBF(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleJet_95_75_65_DoubleJet_75_65_er2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu0(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu0_OQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu0_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu3(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu3_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5SQ_3SQ_0OQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5SQ_3SQ_0OQ_DoubleMu_5_3_SQ_OS_Mass_Max9(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5SQ_3SQ_0_DoubleMu_5_3_SQ_OS_Mass_Max9(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_0_0(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_3_3(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_3_3_SQ(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_3p5_2p5(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_3p5_2p5_DoubleMu_5_2p5_OS_Mass_5to17(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_3p5_2p5_OQ_DoubleMu_5_2p5_OQ_OS_Mass_5to17(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_4_2p5_DoubleMu_5_2p5_OS_Mass_5to17(); // Trigger/flag bit (process: NANO)
    const bool &L1_TripleMu_5_5_3(); // Trigger/flag bit (process: NANO)
    const bool &L1_UnpairedBunchBptxMinus(); // Trigger/flag bit (process: NANO)
    const bool &L1_UnpairedBunchBptxPlus(); // Trigger/flag bit (process: NANO)
    const bool &L1_ZeroBias(); // Trigger/flag bit (process: NANO)
    const bool &L1_ZeroBias_FirstCollidingBunch(); // Trigger/flag bit (process: NANO)
    const bool &L1_ZeroBias_copy(); // Trigger/flag bit (process: NANO)
    const bool &L1simulation_step(); // Trigger/flag bit (process: HLT)
    const vector<float> &LHEPart_eta(); // Pseodorapidity of LHE particles
    const vector<float> &LHEPart_incomingpz(); // Pz of incoming LHE particles
    const vector<float> &LHEPart_mass(); // Mass of LHE particles
    const vector<LorentzVector> &LHEPart_p4(); // from LHEPart_pt,eta,phi,mass
    const vector<int> &LHEPart_pdgId(); // PDG ID of LHE particles
    const vector<float> &LHEPart_phi(); // Phi of LHE particles
    const vector<float> &LHEPart_pt(); // Pt of LHE particles
    const vector<int> &LHEPart_spin(); // Spin of LHE particles
    const vector<int> &LHEPart_status(); // LHE particle status; -1:incoming, 1:outgoing
    const vector<float> &LHEPdfWeight(); // 
    const vector<float> &LHEReweightingWeight(); // 
    const vector<float> &LHEScaleWeight(); // 
    const float &LHEWeight_originalXWGTUP(); // Nominal event weight in the LHE file
    const float &LHE_AlphaS(); // Per-event alphaS
    const float &LHE_HT(); // HT, scalar sum of parton pTs at LHE step
    const float &LHE_HTIncoming(); // HT, scalar sum of parton pTs at LHE step, restricted to partons
    const UChar_t &LHE_Nb(); // Number of b partons at LHE step
    const UChar_t &LHE_Nc(); // Number of c partons at LHE step
    const UChar_t &LHE_Nglu(); // Number of gluon partons at LHE step
    const UChar_t &LHE_Njets(); // Number of jets (partons) at LHE step
    const UChar_t &LHE_NpLO(); // number of partons at LO
    const UChar_t &LHE_NpNLO(); // number of partons at NLO
    const UChar_t &LHE_Nuds(); // Number of u,d,s partons at LHE step
    const float &LHE_Vpt(); // pT of the W or Z boson at LHE step
    const float &MET_MetUnclustEnUpDeltaX(); // Delta (METx_mod-METx) Unclustered Energy Up
    const float &MET_MetUnclustEnUpDeltaY(); // Delta (METy_mod-METy) Unclustered Energy Up
    const float &MET_covXX(); // xx element of met covariance matrix
    const float &MET_covXY(); // xy element of met covariance matrix
    const float &MET_covYY(); // yy element of met covariance matrix
    const float &MET_fiducialGenPhi(); // phi
    const float &MET_fiducialGenPt(); // pt
    const float &MET_phi(); // phi
    const float &MET_pt(); // pt
    const float &MET_significance(); // MET significance
    const float &MET_sumEt(); // scalar sum of Et
    const float &MET_sumPtUnclustered(); // sumPt used for MET significance
    const vector<int> &Muon_charge(); // electric charge
    const vector<UChar_t> &Muon_cleanmask(); // simple cleaning mask with priority to leptons
    const vector<float> &Muon_dxy(); // dxy (with sign) wrt first PV, in cm
    const vector<float> &Muon_dxyErr(); // dxy uncertainty, in cm
    const vector<float> &Muon_dxybs(); // dxy (with sign) wrt the beam spot, in cm
    const vector<float> &Muon_dz(); // dz (with sign) wrt first PV, in cm
    const vector<float> &Muon_dzErr(); // dz uncertainty, in cm
    const vector<float> &Muon_eta(); // eta
    const vector<int> &Muon_fsrPhotonIdx(); // Index of the associated FSR photon
    const vector<UChar_t> &Muon_genPartFlav(); // Flavour of genParticle for MC matching to status==1 muons: 1 = prompt muon (including gamma*->mu mu), 15 = muon from prompt tau, 5 = muon from b, 4 = muon from c, 3 = muon from light or unknown, 0 = unmatched
    const vector<int> &Muon_genPartIdx(); // Index into genParticle list for MC matching to status==1 muons
    const vector<UChar_t> &Muon_highPtId(); // high-pT cut-based ID (1 = tracker high pT, 2 = global high pT, which includes tracker high pT)
    const vector<bool> &Muon_highPurity(); // inner track is high purity
    const vector<bool> &Muon_inTimeMuon(); // inTimeMuon ID
    const vector<float> &Muon_ip3d(); // 3D impact parameter wrt first PV, in cm
    const vector<bool> &Muon_isGlobal(); // muon is global muon
    const vector<bool> &Muon_isPFcand(); // muon is PF candidate
    const vector<bool> &Muon_isTracker(); // muon is tracker muon
    const vector<int> &Muon_jetIdx(); // index of the associated jet (-1 if none)
    const vector<float> &Muon_jetPtRelv2(); // Relative momentum of the lepton with respect to the closest jet after subtracting the lepton
    const vector<float> &Muon_jetRelIso(); // Relative isolation in matched jet (1/ptRatio-1, pfRelIso04_all if no matched jet)
    const vector<bool> &Muon_looseId(); // muon is loose muon
    const vector<float> &Muon_mass(); // mass
    const vector<bool> &Muon_mediumId(); // cut-based ID, medium WP
    const vector<bool> &Muon_mediumPromptId(); // cut-based ID, medium prompt WP
    const vector<UChar_t> &Muon_miniIsoId(); // MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
    const vector<float> &Muon_miniPFRelIso_all(); // mini PF relative isolation, total (with scaled rho*EA PU corrections)
    const vector<float> &Muon_miniPFRelIso_chg(); // mini PF relative isolation, charged component
    const vector<UChar_t> &Muon_multiIsoId(); // MultiIsoId from miniAOD selector (1=MultiIsoLoose, 2=MultiIsoMedium)
    const vector<UChar_t> &Muon_mvaId(); // Mva ID from miniAOD selector (1=MvaLoose, 2=MvaMedium, 3=MvaTight)
    const vector<float> &Muon_mvaLowPt(); // Low pt muon ID score
    const vector<float> &Muon_mvaTTH(); // TTH MVA lepton ID score
    const vector<int> &Muon_nStations(); // number of matched stations with default arbitration (segment & track)
    const vector<int> &Muon_nTrackerLayers(); // number of layers in the tracker
    const vector<LorentzVector> &Muon_p4(); // from Muon_pt,eta,phi,mass
    const vector<int> &Muon_pdgId(); // PDG code assigned by the event reconstruction (not by MC truth)
    const vector<UChar_t> &Muon_pfIsoId(); // PFIso ID from miniAOD selector (1=PFIsoVeryLoose, 2=PFIsoLoose, 3=PFIsoMedium, 4=PFIsoTight, 5=PFIsoVeryTight, 6=PFIsoVeryVeryTight)
    const vector<float> &Muon_pfRelIso03_all(); // PF relative isolation dR=0.3, total (deltaBeta corrections)
    const vector<float> &Muon_pfRelIso03_chg(); // PF relative isolation dR=0.3, charged component
    const vector<float> &Muon_pfRelIso04_all(); // PF relative isolation dR=0.4, total (deltaBeta corrections)
    const vector<float> &Muon_phi(); // phi
    const vector<float> &Muon_pt(); // pt
    const vector<float> &Muon_ptErr(); // ptError of the muon track
    const vector<float> &Muon_segmentComp(); // muon segment compatibility
    const vector<float> &Muon_sip3d(); // 3D impact parameter significance wrt first PV
    const vector<bool> &Muon_softId(); // soft cut-based ID
    const vector<float> &Muon_softMva(); // soft MVA ID score
    const vector<bool> &Muon_softMvaId(); // soft MVA ID
    const vector<int> &Muon_tightCharge(); // Tight charge criterion using pterr/pt of muonBestTrack (0:fail, 2:pass)
    const vector<bool> &Muon_tightId(); // cut-based ID, tight WP
    const vector<UChar_t> &Muon_tkIsoId(); // TkIso ID (1=TkIsoLoose, 2=TkIsoTight)
    const vector<float> &Muon_tkRelIso(); // Tracker-based relative isolation dR=0.3 for highPt, trkIso/tunePpt
    const vector<bool> &Muon_triggerIdLoose(); // TriggerIdLoose ID
    const vector<float> &Muon_tunepRelPt(); // TuneP relative pt, tunePpt/pt
    const vector<float> &OtherPV_z(); // Z position of other primary vertices, excluding the main PV
    const vector<float> &PSWeight(); // PS weights (w_var / w_nominal); [0] is ISR=0.5 FSR=1; [1] is ISR=1 FSR=0.5; [2] is ISR=2 FSR=1; [3] is ISR=1 FSR=2 
    const float &PV_chi2(); // main primary vertex reduced chi2
    const float &PV_ndof(); // main primary vertex number of degree of freedom
    const int &PV_npvs(); // total number of reconstructed primary vertices
    const int &PV_npvsGood(); // number of good reconstructed primary vertices. selection:!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2
    const float &PV_score(); // main primary vertex score, i.e. sum pt2 of clustered objects
    const float &PV_x(); // main primary vertex position x coordinate
    const float &PV_y(); // main primary vertex position y coordinate
    const float &PV_z(); // main primary vertex position z coordinate
    const vector<int> &Photon_charge(); // electric charge
    const vector<UChar_t> &Photon_cleanmask(); // simple cleaning mask with priority to leptons
    const vector<int> &Photon_cutBased(); // cut-based ID bitmap, Fall17V2, (0:fail, 1:loose, 2:medium, 3:tight)
    const vector<int> &Photon_cutBased_Fall17V1Bitmap(); // cut-based ID bitmap, Fall17V1, 2^(0:loose, 1:medium, 2:tight).
    const vector<int> &Photon_cutBased_Spring16V2p2(); // cut-based ID bitmap, Spring16V2p2, (0:fail, 1:loose, 2:medium, 3:tight)
    const vector<float> &Photon_eCorr(); // ratio of the calibrated energy/miniaod energy
    const vector<int> &Photon_electronIdx(); // index of the associated electron (-1 if none)
    const vector<bool> &Photon_electronVeto(); // pass electron veto
    const vector<float> &Photon_energyErr(); // energy error of the cluster from regression
    const vector<float> &Photon_eta(); // eta
    const vector<UChar_t> &Photon_genPartFlav(); // Flavour of genParticle for MC matching to status==1 photons or electrons: 1 = prompt photon, 11 = prompt electron, 0 = unknown or unmatched
    const vector<int> &Photon_genPartIdx(); // Index into genParticle list for MC matching to status==1 photons or electrons
    const vector<float> &Photon_hoe(); // H over E
    const vector<bool> &Photon_isScEtaEB(); // is supercluster eta within barrel acceptance
    const vector<bool> &Photon_isScEtaEE(); // is supercluster eta within endcap acceptance
    const vector<int> &Photon_jetIdx(); // index of the associated jet (-1 if none)
    const vector<float> &Photon_mass(); // mass
    const vector<float> &Photon_mvaID(); // MVA ID score, Fall17V2
    const vector<float> &Photon_mvaID_Fall17V1p1(); // MVA ID score, Fall17V1p1
    const vector<float> &Photon_mvaID_Spring16nonTrigV1(); // MVA ID score, Spring16nonTrigV1
    const vector<bool> &Photon_mvaID_WP80(); // MVA ID WP80, Fall17V2
    const vector<bool> &Photon_mvaID_WP90(); // MVA ID WP90, Fall17V2
    const vector<LorentzVector> &Photon_p4(); // from Photon_pt,eta,phi,mass
    const vector<int> &Photon_pdgId(); // PDG code assigned by the event reconstruction (not by MC truth)
    const vector<float> &Photon_pfRelIso03_all(); // PF relative isolation dR=0.3, total (with rho*EA PU corrections)
    const vector<float> &Photon_pfRelIso03_chg(); // PF relative isolation dR=0.3, charged component (with rho*EA PU corrections)
    const vector<float> &Photon_phi(); // phi
    const vector<bool> &Photon_pixelSeed(); // has pixel seed
    const vector<float> &Photon_pt(); // p_{T}
    const vector<float> &Photon_r9(); // R9 of the supercluster, calculated with full 5x5 region
    const vector<UChar_t> &Photon_seedGain(); // Gain of the seed crystal
    const vector<float> &Photon_sieie(); // sigma_IetaIeta of the supercluster, calculated with full 5x5 region
    const vector<int> &Photon_vidNestedWPBitmap(); // Fall17V2 VID compressed bitmap (MinPtCut,PhoSCEtaMultiRangeCut,PhoSingleTowerHadOverEmCut,PhoFull5x5SigmaIEtaIEtaCut,PhoAnyPFIsoWithEACut,PhoAnyPFIsoWithEAAndQuadScalingCut,PhoAnyPFIsoWithEACut), 2 bits per cut
    const vector<int> &Photon_vidNestedWPBitmap_Spring16V2p2(); // Spring16V2p2 VID compressed bitmap (MinPtCut,PhoSCEtaMultiRangeCut,PhoSingleTowerHadOverEmCut,PhoFull5x5SigmaIEtaIEtaCut,PhoAnyPFIsoWithEACut,PhoAnyPFIsoWithEAAndQuadScalingCut,PhoAnyPFIsoWithEACut), 2 bits per cut
    const float &Pileup_gpudensity(); // Generator-level PU vertices / mm
    const int &Pileup_nPU(); // the number of pileup interactions that have been added to the event in the current bunch crossing
    const float &Pileup_nTrueInt(); // the true mean number of the poisson distribution for this event from which the number of interactions each bunch crossing has been sampled
    const float &Pileup_pudensity(); // PU vertices / mm
    const int &Pileup_sumEOOT(); // number of early out of time pileup
    const int &Pileup_sumLOOT(); // number of late out of time pileup
    const float &PuppiMET_phi(); // phi
    const float &PuppiMET_phiJERUp(); // JER up phi
    const float &PuppiMET_phiJESUp(); // JES up phi
    const float &PuppiMET_pt(); // pt
    const float &PuppiMET_ptJERUp(); // JER up pt
    const float &PuppiMET_ptJESUp(); // JES up pt
    const float &PuppiMET_sumEt(); // scalar sum of Et
    const float &RawMET_phi(); // phi
    const float &RawMET_pt(); // pt
    const float &RawMET_sumEt(); // scalar sum of Et
    const float &RawPuppiMET_phi(); // phi
    const float &RawPuppiMET_pt(); // pt
    const float &RawPuppiMET_sumEt(); // scalar sum of Et
    const vector<float> &SV_chi2(); // reduced chi2, i.e. chi/ndof
    const vector<float> &SV_dlen(); // decay length in cm
    const vector<float> &SV_dlenSig(); // decay length significance
    const vector<float> &SV_dxy(); // 2D decay length in cm
    const vector<float> &SV_dxySig(); // 2D decay length significance
    const vector<float> &SV_eta(); // eta
    const vector<float> &SV_mass(); // mass
    const vector<float> &SV_ndof(); // number of degrees of freedom
    const vector<LorentzVector> &SV_p4(); // from SV_pt,eta,phi,mass
    const vector<float> &SV_pAngle(); // pointing angle, i.e. acos(p_SV * (SV - PV)) 
    const vector<float> &SV_phi(); // phi
    const vector<float> &SV_pt(); // pt
    const vector<float> &SV_x(); // secondary vertex X position, in cm
    const vector<float> &SV_y(); // secondary vertex Y position, in cm
    const vector<float> &SV_z(); // secondary vertex Z position, in cm
    const float &SoftActivityJetHT(); // scalar sum of soft activity jet pt, pt>1
    const float &SoftActivityJetHT10(); // scalar sum of soft activity jet pt , pt >10
    const float &SoftActivityJetHT2(); // scalar sum of soft activity jet pt, pt >2
    const float &SoftActivityJetHT5(); // scalar sum of soft activity jet pt, pt>5
    const int &SoftActivityJetNjets10(); // number of soft activity jet pt, pt >2
    const int &SoftActivityJetNjets2(); // number of soft activity jet pt, pt >10
    const int &SoftActivityJetNjets5(); // number of soft activity jet pt, pt >5
    const vector<float> &SoftActivityJet_eta(); // eta
    const vector<float> &SoftActivityJet_phi(); // phi
    const vector<float> &SoftActivityJet_pt(); // pt
    const vector<float> &SubGenJetAK8_eta(); // eta
    const vector<float> &SubGenJetAK8_mass(); // mass
    const vector<LorentzVector> &SubGenJetAK8_p4(); // from SubGenJetAK8_pt,eta,phi,mass
    const vector<float> &SubGenJetAK8_phi(); // phi
    const vector<float> &SubGenJetAK8_pt(); // pt
    const vector<float> &SubJet_btagCMVA(); // CMVA V2 btag discriminator
    const vector<float> &SubJet_btagCSVV2(); //  pfCombinedInclusiveSecondaryVertexV2 b-tag discriminator (aka CSVV2)
    const vector<float> &SubJet_btagDeepB(); // DeepCSV b+bb tag discriminator
    const vector<float> &SubJet_eta(); // eta
    const vector<float> &SubJet_mass(); // mass
    const vector<float> &SubJet_n2b1(); // N2 with beta=1
    const vector<float> &SubJet_n3b1(); // N3 with beta=1
    const vector<UChar_t> &SubJet_nBHadrons(); // number of b-hadrons
    const vector<UChar_t> &SubJet_nCHadrons(); // number of c-hadrons
    const vector<LorentzVector> &SubJet_p4(); // from SubJet_pt,eta,phi,mass
    const vector<float> &SubJet_phi(); // phi
    const vector<float> &SubJet_pt(); // pt
    const vector<float> &SubJet_rawFactor(); // 1 - Factor to get back to raw pT
    const vector<float> &SubJet_tau1(); // Nsubjettiness (1 axis)
    const vector<float> &SubJet_tau2(); // Nsubjettiness (2 axis)
    const vector<float> &SubJet_tau3(); // Nsubjettiness (3 axis)
    const vector<float> &SubJet_tau4(); // Nsubjettiness (4 axis)
    const vector<int> &Tau_charge(); // electric charge
    const vector<float> &Tau_chargedIso(); // charged isolation
    const vector<UChar_t> &Tau_cleanmask(); // simple cleaning mask with priority to leptons
    const vector<int> &Tau_decayMode(); // decayMode()
    const vector<float> &Tau_dxy(); // d_{xy} of lead track with respect to PV, in cm (with sign)
    const vector<float> &Tau_dz(); // d_{z} of lead track with respect to PV, in cm (with sign)
    const vector<float> &Tau_eta(); // eta
    const vector<UChar_t> &Tau_genPartFlav(); // Flavour of genParticle for MC matching to status==2 taus: 1 = prompt electron, 2 = prompt muon, 3 = tau->e decay, 4 = tau->mu decay, 5 = hadronic tau decay, 0 = unknown or unmatched
    const vector<int> &Tau_genPartIdx(); // Index into genParticle list for MC matching to status==2 taus
    const vector<UChar_t> &Tau_idAntiEle(); // Anti-electron MVA discriminator V6: bitmask 1 = VLoose, 2 = Loose, 4 = Medium, 8 = Tight, 16 = VTight
    const vector<UChar_t> &Tau_idAntiEle2018(); // Anti-electron MVA discriminator V6 (2018): bitmask 1 = VLoose, 2 = Loose, 4 = Medium, 8 = Tight, 16 = VTight
    const vector<UChar_t> &Tau_idAntiMu(); // Anti-muon discriminator V3: : bitmask 1 = Loose, 2 = Tight
    const vector<bool> &Tau_idDecayMode(); // tauID('decayModeFinding')
    const vector<bool> &Tau_idDecayModeNewDMs(); // tauID('decayModeFindingNewDMs')
    const vector<UChar_t> &Tau_idDeepTau2017v2p1VSe(); // byDeepTau2017v2p1VSe ID working points (deepTau2017v2p1): bitmask 1 = VVVLoose, 2 = VVLoose, 4 = VLoose, 8 = Loose, 16 = Medium, 32 = Tight, 64 = VTight, 128 = VVTight
    const vector<UChar_t> &Tau_idDeepTau2017v2p1VSjet(); // byDeepTau2017v2p1VSjet ID working points (deepTau2017v2p1): bitmask 1 = VVVLoose, 2 = VVLoose, 4 = VLoose, 8 = Loose, 16 = Medium, 32 = Tight, 64 = VTight, 128 = VVTight
    const vector<UChar_t> &Tau_idDeepTau2017v2p1VSmu(); // byDeepTau2017v2p1VSmu ID working points (deepTau2017v2p1): bitmask 1 = VLoose, 2 = Loose, 4 = Medium, 8 = Tight
    const vector<UChar_t> &Tau_idMVAnewDM2017v2(); // IsolationMVArun2v1DBnewDMwLT ID working point (2017v2): bitmask 1 = VVLoose, 2 = VLoose, 4 = Loose, 8 = Medium, 16 = Tight, 32 = VTight, 64 = VVTight
    const vector<UChar_t> &Tau_idMVAoldDM(); // IsolationMVArun2v1DBoldDMwLT ID working point (2015): bitmask 1 = VLoose, 2 = Loose, 4 = Medium, 8 = Tight, 16 = VTight, 32 = VVTight
    const vector<UChar_t> &Tau_idMVAoldDM2017v1(); // IsolationMVArun2v1DBoldDMwLT ID working point (2017v1): bitmask 1 = VVLoose, 2 = VLoose, 4 = Loose, 8 = Medium, 16 = Tight, 32 = VTight, 64 = VVTight
    const vector<UChar_t> &Tau_idMVAoldDM2017v2(); // IsolationMVArun2v1DBoldDMwLT ID working point (2017v2): bitmask 1 = VVLoose, 2 = VLoose, 4 = Loose, 8 = Medium, 16 = Tight, 32 = VTight, 64 = VVTight
    const vector<UChar_t> &Tau_idMVAoldDMdR032017v2(); // IsolationMVArun2v1DBoldDMdR0p3wLT ID working point (2017v2): bitmask 1 = VVLoose, 2 = VLoose, 4 = Loose, 8 = Medium, 16 = Tight, 32 = VTight, 64 = VVTight
    const vector<int> &Tau_jetIdx(); // index of the associated jet (-1 if none)
    const vector<float> &Tau_leadTkDeltaEta(); // eta of the leading track, minus tau eta
    const vector<float> &Tau_leadTkDeltaPhi(); // phi of the leading track, minus tau phi
    const vector<float> &Tau_leadTkPtOverTauPt(); // pt of the leading track divided by tau pt
    const vector<float> &Tau_mass(); // mass
    const vector<float> &Tau_neutralIso(); // neutral (photon) isolation
    const vector<LorentzVector> &Tau_p4(); // from Tau_pt,eta,phi,mass
    const vector<float> &Tau_phi(); // phi
    const vector<float> &Tau_photonsOutsideSignalCone(); // sum of photons outside signal cone
    const vector<float> &Tau_pt(); // pt
    const vector<float> &Tau_puCorr(); // pileup correction
    const vector<float> &Tau_rawAntiEle(); // Anti-electron MVA discriminator V6 raw output discriminator
    const vector<float> &Tau_rawAntiEle2018(); // Anti-electron MVA discriminator V6 raw output discriminator (2018)
    const vector<int> &Tau_rawAntiEleCat(); // Anti-electron MVA discriminator V6 category
    const vector<int> &Tau_rawAntiEleCat2018(); // Anti-electron MVA discriminator V6 category (2018)
    const vector<float> &Tau_rawDeepTau2017v2p1VSe(); // byDeepTau2017v2p1VSe raw output discriminator (deepTau2017v2p1)
    const vector<float> &Tau_rawDeepTau2017v2p1VSjet(); // byDeepTau2017v2p1VSjet raw output discriminator (deepTau2017v2p1)
    const vector<float> &Tau_rawDeepTau2017v2p1VSmu(); // byDeepTau2017v2p1VSmu raw output discriminator (deepTau2017v2p1)
    const vector<float> &Tau_rawIso(); // combined isolation (deltaBeta corrections)
    const vector<float> &Tau_rawIsodR03(); // combined isolation (deltaBeta corrections, dR=0.3)
    const vector<float> &Tau_rawMVAnewDM2017v2(); // byIsolationMVArun2v1DBnewDMwLT raw output discriminator (2017v2)
    const vector<float> &Tau_rawMVAoldDM(); // byIsolationMVArun2v1DBoldDMwLT raw output discriminator (2015)
    const vector<float> &Tau_rawMVAoldDM2017v1(); // byIsolationMVArun2v1DBoldDMwLT raw output discriminator (2017v1)
    const vector<float> &Tau_rawMVAoldDM2017v2(); // byIsolationMVArun2v1DBoldDMwLT raw output discriminator (2017v2)
    const vector<float> &Tau_rawMVAoldDMdR032017v2(); // byIsolationMVArun2v1DBdR03oldDMwLT raw output discriminator (2017v2)
    const float &TkMET_phi(); // raw track MET phi
    const float &TkMET_pt(); // raw track MET pt
    const float &TkMET_sumEt(); // raw track scalar sum of Et
    const vector<float> &TrigObj_eta(); // eta
    const vector<int> &TrigObj_filterBits(); // extra bits of associated information: 1 = CaloIdL_TrackIdL_IsoVL, 2 = 1e (WPTight), 4 = 1e (WPLoose), 8 = OverlapFilter PFTau, 16 = 2e, 32 = 1e-1mu, 64 = 1e-1tau, 128 = 3e, 256 = 2e-1mu, 512 = 1e-2mu, 1024 = 1e (32_L1DoubleEG_AND_L1SingleEGOr), 2048 = 1e (CaloIdVT_GsfTrkIdT), 4096 = 1e (PFJet), 8192 = 1e (Photon175_OR_Photon200) for Electron (PixelMatched e/gamma); 1 = TrkIsoVVL, 2 = Iso, 4 = OverlapFilter PFTau, 8 = 1mu, 16 = 2mu, 32 = 1mu-1e, 64 = 1mu-1tau, 128 = 3mu, 256 = 2mu-1e, 512 = 1mu-2e, 1024 = 1mu (Mu50), 2048 = 1mu (Mu100) for Muon; 1 = LooseChargedIso, 2 = MediumChargedIso, 4 = TightChargedIso, 8 = TightID OOSC photons, 16 = HPS, 32 = single-tau + tau+MET, 64 = di-tau, 128 = e-tau, 256 = mu-tau, 512 = VBF+di-tau for Tau; Jet bits: bit 0 for VBF cross-cleaned from loose iso PFTau, bit 1 for hltBTagCaloCSVp087Triple, bit 2 for hltDoubleCentralJet90, bit 3 for hltDoublePFCentralJetLooseID90, bit 4 for hltL1sTripleJetVBFIorHTTIorDoubleJetCIorSingleJet, bit 5 for hltQuadCentralJet30, bit 6 for hltQuadPFCentralJetLooseID30, bit 7 for hltL1sQuadJetC50IorQuadJetC60IorHTT280IorHTT300IorHTT320IorTripleJet846848VBFIorTripleJet887256VBFIorTripleJet927664VBF or hltL1sQuadJetCIorTripleJetVBFIorHTT, bit 8 for hltQuadCentralJet45, bit 9 for hltQuadPFCentralJetLooseID45, bit 10  for hltL1sQuadJetC60IorHTT380IorHTT280QuadJetIorHTT300QuadJet or hltL1sQuadJetC50to60IorHTT280to500IorHTT250to340QuadJet bit 11 for hltBTagCaloCSVp05Double or hltBTagCaloDeepCSVp17Double, bit 12 for hltPFCentralJetLooseIDQuad30, bit 13 for hlt1PFCentralJetLooseID75, bit 14 for hlt2PFCentralJetLooseID60, bit 15 for hlt3PFCentralJetLooseID45, bit 16 for hlt4PFCentralJetLooseID40, bit 17 for hltBTagPFCSVp070Triple or hltBTagPFDeepCSVp24Triple or hltBTagPFDeepCSV4p5Triple  for Jet; HT bits: bit 0 for hltL1sTripleJetVBFIorHTTIorDoubleJetCIorSingleJet, bit 1 for hltL1sQuadJetC50IorQuadJetC60IorHTT280IorHTT300IorHTT320IorTripleJet846848VBFIorTripleJet887256VBFIorTripleJet927664VBF or hltL1sQuadJetCIorTripleJetVBFIorHTT, bit 2 for hltL1sQuadJetC60IorHTT380IorHTT280QuadJetIorHTT300QuadJet or hltL1sQuadJetC50to60IorHTT280to500IorHTT250to340QuadJet, bit 3 for hltCaloQuadJet30HT300 or hltCaloQuadJet30HT320, bit 4 for hltPFCentralJetsLooseIDQuad30HT300 or hltPFCentralJetsLooseIDQuad30HT330 for HT; MHT bits: bit 0 for hltCaloQuadJet30HT300 or hltCaloQuadJet30HT320, bit 1 for hltPFCentralJetsLooseIDQuad30HT300 or hltPFCentralJetsLooseIDQuad30HT330 for MHT; 
    const vector<int> &TrigObj_id(); // ID of the object: 11 = Electron (PixelMatched e/gamma), 22 = Photon (PixelMatch-vetoed e/gamma), 13 = Muon, 15 = Tau, 1 = Jet, 6 = FatJet, 2 = MET, 3 = HT, 4 = MHT
    const vector<int> &TrigObj_l1charge(); // charge of associated L1 seed
    const vector<int> &TrigObj_l1iso(); // iso of associated L1 seed
    const vector<float> &TrigObj_l1pt(); // pt of associated L1 seed
    const vector<float> &TrigObj_l1pt_2(); // pt of associated secondary L1 seed
    const vector<float> &TrigObj_l2pt(); // pt of associated 'L2' seed (i.e. HLT before tracking/PF)
    const vector<float> &TrigObj_phi(); // phi
    const vector<float> &TrigObj_pt(); // pt
    const float &btagWeight_CMVA(); // b-tag event weight for CMVA
    const float &btagWeight_CSVV2(); // b-tag event weight for CSVV2
    const float &btagWeight_DeepCSVB(); // b-tag event weight for DeepCSVB
    const ULong64_t &event(); // event/l
    const float &fixedGridRhoFastjetAll(); // rho from all PF Candidates, used e.g. for JECs
    const float &fixedGridRhoFastjetCentral(); // rho from all PF Candidates for central region, used e.g. for JECs
    const float &fixedGridRhoFastjetCentralCalo(); // rho from calo towers with |eta| < 2.5, used e.g. egamma PFCluster isolation
    const float &fixedGridRhoFastjetCentralChargedPileUp(); // rho from charged PF Candidates for central region, used e.g. for JECs
    const float &fixedGridRhoFastjetCentralNeutral(); // rho from neutral PF Candidates with |eta| < 2.5, used e.g. for rho corrections of some lepton isolations
    const int &genTtbarId(); // ttbar categorization
    const float &genWeight(); // generator weight
    const UInt_t &luminosityBlock(); // luminosityBlock/i
    const UInt_t &nCorrT1METJet(); // Additional low-pt jets for Type-1 MET re-correction
    const UInt_t &nElectron(); // slimmedElectrons after basic selection (pt > 5 )
    const UInt_t &nFatJet(); // slimmedJetsAK8, i.e. ak8 fat jets for boosted analysis
    const UInt_t &nFsrPhoton(); // Final state radiation photons emitted by muons
    const UInt_t &nGenDressedLepton(); // Dressed leptons from Rivet-based ParticleLevelProducer
    const UInt_t &nGenIsolatedPhoton(); // Isolated photons from Rivet-based ParticleLevelProducer
    const UInt_t &nGenJet(); // slimmedGenJets, i.e. ak4 Jets made with visible genparticles
    const UInt_t &nGenJetAK8(); // slimmedGenJetsAK8, i.e. ak8 Jets made with visible genparticles
    const UInt_t &nGenPart(); // interesting gen particles 
    const UInt_t &nGenVisTau(); // gen hadronic taus 
    const UInt_t &nIsoTrack(); // isolated tracks after basic selection (((pt>5 && (abs(pdgId) == 11 || abs(pdgId) == 13)) || pt > 10) && (abs(pdgId) < 15 || abs(eta) < 2.5) && abs(dxy) < 0.2 && abs(dz) < 0.1 && ((pfIsolationDR03().chargedHadronIso < 5 && pt < 25) || pfIsolationDR03().chargedHadronIso/pt < 0.2)) and lepton veto
    const UInt_t &nJet(); // slimmedJets, i.e. ak4 PFJets CHS with JECs applied, after basic selection (pt > 15)
    const UInt_t &nLHEPart(); // 
    const UInt_t &nLHEPdfWeight(); // 
    const UInt_t &nLHEReweightingWeight(); // 
    const UInt_t &nLHEScaleWeight(); // 
    const UInt_t &nMuon(); // slimmedMuons after basic selection (pt > 3 && (passed('CutBasedIdLoose') || passed('SoftCutBasedId') || passed('SoftMvaId') || passed('CutBasedIdGlobalHighPt') || passed('CutBasedIdTrkHighPt')))
    const UInt_t &nOtherPV(); // 
    const UInt_t &nPSWeight(); // 
    const UInt_t &nPhoton(); // slimmedPhotons after basic selection (pt > 5 )
    const UInt_t &nSV(); // 
    const UInt_t &nSoftActivityJet(); // jets clustered from charged candidates compatible with primary vertex (charge()!=0 && pvAssociationQuality()>=5 && vertexRef().key()==0)
    const UInt_t &nSubGenJetAK8(); // slimmedGenJetsAK8SoftDropSubJets, i.e. subjets of ak8 Jets made with visible genparticles
    const UInt_t &nSubJet(); // slimmedJetsAK8, i.e. ak8 fat jets for boosted analysis
    const UInt_t &nTau(); // slimmedTaus after basic selection (pt > 18 && tauID('decayModeFindingNewDMs') && (tauID('byLooseCombinedIsolationDeltaBetaCorr3Hits') || tauID('byVLooseIsolationMVArun2v1DBoldDMwLT2015') || tauID('byVLooseIsolationMVArun2v1DBnewDMwLT') || tauID('byVLooseIsolationMVArun2v1DBdR03oldDMwLT') || tauID('byVVLooseIsolationMVArun2v1DBoldDMwLT') || tauID('byVVLooseIsolationMVArun2v1DBoldDMwLT2017v2') || tauID('byVVLooseIsolationMVArun2v1DBnewDMwLT2017v2') || tauID('byVVLooseIsolationMVArun2v1DBdR03oldDMwLT2017v2') || tauID('byVVVLooseDeepTau2017v2p1VSjet')))
    const UInt_t &nTrigObj(); // 
    const UInt_t &run(); // run/i
    Bool_t isData();
    const Int_t &year();
    vector<float> GetVF(const string &name);
    int GetI(const string &name);
    float GetF(const string &name);
    vector<int> GetVI(const string &name);
    vector<LorentzVector> GetVLV(const string &name);
    bool GetB(const string &name);
    vector<bool> GetVB(const string &name);
}
#endif
