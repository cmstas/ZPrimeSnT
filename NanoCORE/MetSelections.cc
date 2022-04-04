#include <iostream>

#include "Config.h"
#include "Math/VectorUtil.h"
#include "MetSelections.h"

using namespace tas;

pair<float, float> getT1CHSMET(FactorizedJetCorrector *jet_corrector, JetCorrectionUncertainty *jecUnc, bool uncUp) {
    // T1 MET correction implementation in central nanoAOD-tools:
    // https://github.com/cms-nanoAOD/nanoAOD-tools/blob/6b4870f6c62dbffc717e82de80ce3e51a254c284/python/postprocessing/modules/jme/jetmetUncertainties.py#L412-L417
    // CMSSW T1 MET code
    // https://github.com/cms-sw/cmssw/blob/CMSSW_7_4_X/JetMETCorrections/Type1MET/interface/PFJetMETcorrInputProducerT.h#L188
    // https://github.com/cms-sw/cmssw/blob/8706dbe8a09e7e1314f2127288cfc39051851eea/PhysicsTools/PatUtils/interface/PATJetCorrExtractor.h#L74-L77
    // https://github.com/cms-sw/cmssw/blob/8706dbe8a09e7e1314f2127288cfc39051851eea/JetMETCorrections/Type1MET/interface/JetCorrExtractorT.h#L54-L70

    float T1_met = RawMET_pt();
    float T1_metPhi = RawMET_phi();

    float T1_metx = T1_met * cos(T1_metPhi);
    float T1_mety = T1_met * sin(T1_metPhi);

    unsigned int njets_lowpt = CorrT1METJet_rawPt().size();
    unsigned int njets_nominal = Jet_pt().size();
    unsigned int njets_total = njets_lowpt + njets_nominal;

    for (unsigned int ijet = 0; ijet < njets_total; ijet++) {

        float area = 0.;
        float fracEM = 0.;
        float muonSubtrFactor = 0.;

        // LorentzVector jetp4_uncorr(0,0,0,0);
        LorentzVector jetp4_uncorr;
        if (ijet < njets_lowpt) {
            // look into lowpt jet collection and set raw muon-subtracted p4
            int idx = ijet;
            jetp4_uncorr =
                LorentzVector(CorrT1METJet_rawPt()[idx], CorrT1METJet_eta()[idx], CorrT1METJet_phi()[idx], 0.);
            muonSubtrFactor = CorrT1METJet_muonSubtrFactor()[idx];
            area = CorrT1METJet_area()[idx];
            fracEM = 0.;
        } else {
            // look into nominal jet collection and set raw muon-subtracted p4
            int idx = ijet - njets_lowpt;
            jetp4_uncorr = LorentzVector(Jet_pt()[idx], Jet_eta()[idx], Jet_phi()[idx], Jet_mass()[idx]);
            jetp4_uncorr *= (1 - Jet_rawFactor()[idx]);
            muonSubtrFactor = Jet_muonSubtrFactor()[idx];
            area = Jet_area()[idx];
            fracEM = Jet_neEmEF()[idx] + Jet_chEmEF()[idx];
        }

        if (fracEM > 0.9) continue;
        if (fabs(jetp4_uncorr.eta()) > 9.9) continue;

        if (year() == 2017) { // 2017 EE noise fix (exclude jets with raw pT < 50)
            if (jetp4_uncorr.pt() < 50. && abs(jetp4_uncorr.eta()) >= 2.65 && abs(jetp4_uncorr.eta()) <= 3.139)
                continue;
        }

        jet_corrector->setJetPtEtaARho(jetp4_uncorr.pt(), jetp4_uncorr.eta(), area, fixedGridRhoFastjetAll());

        // note the subcorrections are stored with corr_vals(N) = corr(N)*corr(N-1)*...*corr(1)
        vector<float> corr_vals = jet_corrector->getSubCorrections();
        double corr = corr_vals.at(corr_vals.size() - 1); // all corrections
        double corr_l1 = corr_vals.at(0);                 // offset correction

        double totalshift = 1.0;
        if (jecUnc != 0 and not isData()) {
            jecUnc->setJetEta(jetp4_uncorr.eta());
            jecUnc->setJetPt(jetp4_uncorr.pt() * corr);
            double shift = jecUnc->getUncertainty(true);
            if (uncUp)
                totalshift += shift;
            else
                totalshift -= shift;
        }

        // Now subtract the muon
        jetp4_uncorr *= (1 - muonSubtrFactor);

        if (corr * jetp4_uncorr.pt() > 15.) {
            T1_metx += jetp4_uncorr.px() * (corr_l1 - corr * totalshift);
            T1_mety += jetp4_uncorr.py() * (corr_l1 - corr * totalshift);
        }
    }

    T1_met = std::sqrt(pow(T1_metx, 2) + pow(T1_mety, 2));
    T1_metPhi = std::atan2(T1_mety, T1_metx);

    return make_pair(T1_met, T1_metPhi);
}

bool passesMETfilters(bool isData) {

    if (gconf.year == 2016) {
        if (isData) {}
    } else if (gconf.year == 2017) {
        if (!Flag_globalTightHalo2016Filter()) return false;
        if (!Flag_HBHENoiseFilter()) return false;
        if (!Flag_HBHENoiseIsoFilter()) return false;
        if (!Flag_EcalDeadCellTriggerPrimitiveFilter()) return false;
        if (!Flag_eeBadScFilter()) return false;
        if (!Flag_goodVertices()) return false;
        if (!Flag_chargedHadronTrackResolutionFilter()) return false;
        if (!Flag_muonBadTrackFilter()) return false;
        if (isData) {}
    } else if (gconf.year == 2018) {
        if (isData) {}
    } else {
        std::cout << "uh, I don't know what year this is" << std::endl;
    }

    // otherwise, good
    return true;
}
