#ifndef JetResolutionUncertainty_h
#define JetResolutionUncertainty_h

#include "PhysicsTools/NanoAODTools/interface/PyJetParametersWrapper.h"
#include "PhysicsTools/NanoAODTools/interface/PyJetResolutionScaleFactorWrapper.h"
#include "PhysicsTools/NanoAODTools/interface/PyJetResolutionWrapper.h"

#include "TLorentzVector.h"
#include "TRandom3.h"

#include <string>

class JetResolutionUncertainty
{
  private:
    PyJetParametersWrapper params;

    JME::JetResolution resolutions;
    JME::JetResolutionScaleFactor scaleFactors;

    float getResolution() { return resolutions.getResolution(params); }
    float getScaleFactor(Variation fVariation) { return scaleFactors.getScaleFactor(params, fVariation); }

  public:
    JetResolutionUncertainty() {
      resolutions = PyJetResolutionWrapper();
      scaleFactors = PyJetResolutionScaleFactorWrapper();
    }
    JetResolutionUncertainty(const std::string& fJERInputFullPath, const std::string& fJERUncInputFullPath) {
      resolutions = PyJetResolutionWrapper(fJERInputFullPath);
      scaleFactors = PyJetResolutionScaleFactorWrapper(fJERUncInputFullPath);
    }
    ~JetResolutionUncertainty() {};

    void setJetEta(float fEta) { params.setJetEta(fEta); }
    void setJetPt(float fPt) { params.setJetPt(fPt); }
    void setRho(float fRho) { params.setRho(fRho); }

    void applyJER(LorentzVector &jet_p4, const int JERUnc, const std::vector<LorentzVector> &GenJet_p4, TRandom3 &rnd) {
      // JERUnc == 1 means the nominal value is applied, +/-2 means a variation is applied, anything else means JERs are not applied.
      // rnd is a pseudo-number generator, initialized outside the analysis looper.
      // At the start of each event, its seed needs to be set to:                                                                                                                                                
      // ( 1 + ( nt.run() << 20 ) + ( nt.luminosityBlock() << 10 ) + nt.event() + ( nt.nJet() > 0 ? nt.Jet_eta().at(0) / 0.01 : 0 ) )

      float jerSF, smearFactor = 1.0;
      if ( JERUnc == 1 ) jerSF = getScaleFactor(Variation::NOMINAL);
      else if ( JERUnc == 2 ) jerSF = getScaleFactor(Variation::UP);
      else if ( JERUnc ==-2 ) jerSF = getScaleFactor(Variation::DOWN);
      else return;

      int genJet_idx=-1;
      float drmin = 1e9;
      for ( unsigned int igenjet=0; igenjet < GenJet_p4.size(); igenjet++ ) {
        float deta = GenJet_p4[igenjet].Eta() - jet_p4.Eta();
        float dphi = TVector2::Phi_mpi_pi(GenJet_p4[igenjet].Phi() - jet_p4.Phi());
        float dr = TMath::Sqrt( deta*deta+dphi*dphi );
        if ( dr < drmin ) {
          drmin = dr;
          genJet_idx = igenjet;
        }
      }

      if ( drmin < 0.4 ) {
        float dPt = jet_p4.Pt() - GenJet_p4[genJet_idx].Pt();

        float smearFactor = ( 1.0 + ( jerSF - 1.0 ) * dPt / jet_p4.Pt() );
      }
      else {
        float jerRes = getResolution();

        float rand = rnd.Gaus(0, jerRes);
        if ( jerSF > 1. ) {
          smearFactor = ( 1.0 + rand * TMath::Sqrt( jerSF*jerSF - 1.0 ) );
        }
        else {
          smearFactor = 1.0;
        }
      }

      if ( smearFactor * jet_p4.E() < 1e-2 ) smearFactor = 1e-2 / jet_p4.E();

      jet_p4 *= smearFactor;
    }
};

#endif
