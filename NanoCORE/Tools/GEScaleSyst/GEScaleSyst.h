#ifndef GEScaleSyst_h
#define GEScaleSyst_h

#include <string>
#include <cmath>
#include <map>

#include "TLorentzVector.h"

class GEScaleSyst {
  public:
    GEScaleSyst();
    GEScaleSyst(std::string era_);

    void Init();

    float GEScaleCorrPt(float pt, float eta, float phi, int charge, int mode, int icopy, bool doOpp = false);
    TLorentzVector GEScaleCorrLvec(float pt, float eta, float phi, int charge, int mode, int icopy, bool doOpp = false);

    void SetVerbose(int _v) {
      verbose = _v;
    };

  private:
    const double mu_mass = 0.105658;

    int GetCopyIndex(int mode, int icopy);
    float GetGEScaleKappa(float eta, float phi, int mode = 0, int icopy = 0);

    std::string era;

    const int neta = 6;
    const double etaBinEdge[7] = { -2.4, -2.1, -1.2, 0, 1.2, 2.1, 2.4 };
    const int nphi = 3;
    const double phiBinEdge[4] = { -M_PI, -M_PI/3.0, M_PI/3.0, M_PI };

    // eta bin #:
    //   0: [-2.4, -2.1]
    //   1: [-2.1, -1.2]
    //   2: [-1.2, 0.0]
    //   3: [0.0, 1.2]
    //   4: [1.2, 2.1]
    //   5: [2.1, 2.4]

    // phi bin #:
    //   0: [-180, -60]
    //   1: [-60, 60]
    //   2: [60, 180]

    // copy indices:
    //     mode = 0
    //         icopy = 0:  kappa (original)
    //         icopy = 1:  kappa + 1 sigma variation
    //         icopy = 2:  kappa - 1 sigma variation
    //         icopy = 3:  kappa + 2 sigma variation
    //         icopy = 4:  kappa - 2 sigma variation
    //     mode = 1
    //         icopy = 0-49: random copies from gaus(kappa, sigma)
    //     mode = 2
    //         icopy = 0-49: random copies with sign constraint, restrict sign of bias if (k + 1 sigma)(k - 1 sigma) > 0

    std::map<int, std::map<int, std::map<int, float> > > _matrix;

    int verbose;
};

#endif
