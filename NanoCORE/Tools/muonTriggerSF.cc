#include "muonTriggerSF.h"

using namespace std;

TString get_triggerSFPtBin(const float pt)
{
  vector<float> thresholds = {52.0, 55.0, 60.0, 120.0, 200.0, 300.0, 500.0};
  vector<TString> ptbins = {"pt0", "pt1", "pt2", "pt3", "pt4", "pt5", "pt6", "pt7"};
  for ( unsigned int b=0; b < thresholds.size(); b++ ) {
    if ( pt < thresholds.at(b) ) {
      return ptbins.at(b);
    }
  }
  return ptbins.at(ptbins.size()-1);
}

TString get_triggerSFEtaBin(const float abseta)
{
  vector<float> thresholds = {0.9, 1.2, 2.1, 2.4};
  vector<TString> etabins = {"eta0", "eta1", "eta2", "eta3"};
  for ( unsigned int b=0; b < thresholds.size(); b++ ) {
    if ( abseta < thresholds.at(b) ) { 
      return etabins.at(b);
    }
  }
  cout << "WARNING: muon pseudo-rapidity beyond " << thresholds.at(etabins.size()-1) << endl;
  return etabins.at(etabins.size()-1);
}

float get_triggerSF(const float pt, const float eta, const TString year, const TString variation)
{

  TString tyear = year;
  if ( tyear.Contains("2016") ) tyear = "2016";
  TString ptbin = get_triggerSFPtBin(pt);
  TString etabin = get_triggerSFEtaBin(fabs(eta));

  if ( variation=="central" ) return tsf[tyear][ptbin][etabin];
  else if ( variation=="up" ) return tsf[tyear][ptbin][etabin]+unc[tyear][ptbin][etabin];
  else if ( variation=="down" ) return tsf[tyear][ptbin][etabin]-unc[tyear][ptbin][etabin];
  else {
    cout << "WARNING: unknown variation (central, up, down), returning unity scale factor!" << endl;
    return 1.0;
  }
}
