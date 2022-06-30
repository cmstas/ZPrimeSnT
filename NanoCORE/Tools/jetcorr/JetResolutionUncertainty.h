#ifndef JetResolutionUncertainty_h
#define JetResolutionUncertainty_h

#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"

#include "PhysicsTools/NanoAODTools/interface/PyJetParametersWrapper.h"
#include "PhysicsTools/NanoAODTools/interface/PyJetResolutionScaleFactorWrapper.h"
#include "PhysicsTools/NanoAODTools/interface/PyJetResolutionWrapper.h"

#include <string>

class JetResolutionUncertainty
{
  private:
    PyJetParametersWrapper params;

    JME::JetResolution resolutions;
    JME::JetResolutionScaleFactor scaleFactors;

  public:
    JetResolutionUncertainty()
    {
      resolutions = PyJetResolutionWrapper();
      scaleFactors = PyJetResolutionScaleFactorWrapper();
    }
    JetResolutionUncertainty(const std::string& fJERInputFullPath, const std::string& fJERUncInputFullPath)
    {
      resolutions = PyJetResolutionWrapper(fJERInputFullPath);
      scaleFactors = PyJetResolutionScaleFactorWrapper(fJERUncInputFullPath);
    }
    ~JetResolutionUncertainty() {};

    void setJetEta(float fEta)
    {
      params.setJetEta(fEta);
    }
    void setJetPt(float fPt)
    {
      params.setJetPt(fPt);
    }
    void setRho(float fRho)
    {
      params.setRho(fRho);
    }

    float getResolution()
    {
      return resolutions.getResolution(params);
    }
    float getScaleFactor(Variation fVariation)
    {
      return scaleFactors.getScaleFactor(params, fVariation);
    }
};

#endif
