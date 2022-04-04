#ifndef BTagEntry_v2_H
#define BTagEntry_v2_H

//**********************
// NOTE: This is for UL and beyond CSV file after the change: https://indico.cern.ch/event/1096988/contributions/4615134/attachments/2346047/4000529/Nov21_btaggingSFjsons.pdf
//**********************

/**
 *
 * BTagEntry_v2
 *
 * Represents one pt- or discriminator-dependent calibration function.
 *
 * measurement_type:    e.g. comb, ttbar, di-mu, boosted, ...
 * sys_type:            e.g. central, plus, minus, plus_JEC, plus_JER, ...
 *
 * Everything is converted into a function, as it is easiest to store it in a
 * txt or json file.
 *
 ************************************************************/

#include <string>
#include <TF1.h>
#include <TH1.h>


class BTagEntry_v2
{
public:
  enum OperatingPoint {
    OP_LOOSE=0,
    OP_MEDIUM=1,
    OP_TIGHT=2,
    OP_RESHAPING=3,
  };
  enum JetFlavor {
    FLAV_B=0,
    FLAV_C=1,
    FLAV_UDSG=2,
  };
  struct Parameters {
    OperatingPoint operatingPoint;
    std::string measurementType;
    std::string sysType;
    JetFlavor jetFlavor;
    float etaMin;
    float etaMax;
    float ptMin;
    float ptMax;
    float discrMin;
    float discrMax;

    // default constructor
    Parameters(
      OperatingPoint op=OP_TIGHT,
      std::string measurement_type="comb",
      std::string sys_type="central",
      JetFlavor jf=FLAV_B,
      float eta_min=-99999.,
      float eta_max=99999.,
      float pt_min=0.,
      float pt_max=99999.,
      float discr_min=0.,
      float discr_max=99999.
    );

  };

  BTagEntry_v2() {}
  BTagEntry_v2(const std::string &csvLine);
  BTagEntry_v2(const std::string &func, Parameters p);
  BTagEntry_v2(const TF1* func, Parameters p);
  BTagEntry_v2(const TH1* histo, Parameters p);
  ~BTagEntry_v2() {}
  static std::string makeCSVHeader();
  std::string makeCSVLine() const;
  static std::string trimStr(std::string str);

  // public, no getters needed
  std::string formula;
  Parameters params;

};

#endif  // BTagEntry_v2_H


#ifndef BTagCalibration_v2_H
#define BTagCalibration_v2_H

/**
 * BTagCalibration_v2
 *
 * The 'hierarchy' of stored information is this:
 * - by tagger (BTagCalibration_v2)
 *   - by operating point or reshape bin
 *     - by jet parton flavor
 *       - by type of measurement
 *         - by systematic
 *           - by eta bin
 *             - as 1D-function dependent of pt or discriminant
 *
 ************************************************************/

#include <map>
#include <vector>
#include <string>
#include <istream>
#include <ostream>


class BTagCalibration_v2
{
public:
  BTagCalibration_v2() {}
  BTagCalibration_v2(const std::string &tagger);
  BTagCalibration_v2(const std::string &tagger, const std::string &filename);
  ~BTagCalibration_v2() {}

  std::string tagger() const {return tagger_;}

  void addEntry(const BTagEntry_v2 &entry);
  const std::vector<BTagEntry_v2>& getEntries(const BTagEntry_v2::Parameters &par) const;

  void readCSV(std::istream &s);
  void readCSV(const std::string &s);
  void makeCSV(std::ostream &s) const;
  std::string makeCSV() const;

protected:
  static std::string token(const BTagEntry_v2::Parameters &par);

  std::string tagger_;
  std::map<std::string, std::vector<BTagEntry_v2> > data_;

};

#endif  // BTagCalibration_v2_H


#ifndef BTagCalibrationReader_v2_H
#define BTagCalibrationReader_v2_H

/**
 * BTagCalibrationReader_v2
 *
 * Helper class to pull out a specific set of BTagEntry's out of a
 * BTagCalibration. TF1 functions are set up at initialization time.
 *
 ************************************************************/

#include <memory>
#include <string>



class BTagCalibrationReader_v2
{
public:
  class BTagCalibrationReaderImpl_v2;

  BTagCalibrationReader_v2() {}
  BTagCalibrationReader_v2(BTagEntry_v2::OperatingPoint op,
                        const std::string & sysType="central",
                        const std::vector<std::string> & otherSysTypes={});

  void load(const BTagCalibration_v2 & c,
            BTagEntry_v2::JetFlavor jf,
            const std::string & measurementType="comb");

  double eval(BTagEntry_v2::JetFlavor jf,
              float eta,
              float pt,
              float discr=0.) const;

  double eval_auto_bounds(const std::string & sys,
                          BTagEntry_v2::JetFlavor jf,
                          float eta,
                          float pt,
                          float discr=0.) const;

  std::pair<float, float> min_max_pt(BTagEntry_v2::JetFlavor jf,
                                     float eta,
                                     float discr=0.) const;

protected:
  std::shared_ptr<BTagCalibrationReaderImpl_v2> pimpl;
};


#endif  // BTagCalibrationReader_v2_H


