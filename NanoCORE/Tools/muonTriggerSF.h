
#ifndef MUONTRIGGERSF_H
#define MUONTRIGGERSF_H

#include <map>
#include <vector>
#include <iostream>
#include <TString.h>

using namespace std;

map<TString,map<TString,map<TString,float>>> tsf = { };
map<TString,map<TString,map<TString,float>>> unc = { };

TString get_triggerSFPtBin(const float pt);

TString get_triggerSFEtaBin(const float abseta);

float get_triggerSF(const float pt, const float eta, const TString year, const TString variation="central");

inline void reset_triggerSF() {

  tsf.clear();
  unc.clear();

}

inline void set_triggerSF() {

  // 2018: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2018#Trigger_efficiency_AN2
  tsf.insert({"2018", { }});
  unc.insert({"2018", { }});

  tsf["2018"].insert({"pt0", { }});
  tsf["2018"]["pt0"].insert({"eta0", 0.0});
  tsf["2018"]["pt0"].insert({"eta1", 0.0});
  tsf["2018"]["pt0"].insert({"eta2", 0.0});
  tsf["2018"]["pt0"].insert({"eta3", 0.0});  
  unc["2018"].insert({"pt0", { }});
  unc["2018"]["pt0"].insert({"eta0", 0.0});
  unc["2018"]["pt0"].insert({"eta1", 0.0});
  unc["2018"]["pt0"].insert({"eta2", 0.0});
  unc["2018"]["pt0"].insert({"eta3", 0.0});

  tsf["2018"].insert({"pt1", { }});
  tsf["2018"]["pt1"].insert({"eta0", 0.980});
  tsf["2018"]["pt1"].insert({"eta1", 0.982});
  tsf["2018"]["pt1"].insert({"eta2", 0.983});
  tsf["2018"]["pt1"].insert({"eta3", 0.987});  
  unc["2018"].insert({"pt1", { }});
  unc["2018"]["pt1"].insert({"eta0", 0.016});
  unc["2018"]["pt1"].insert({"eta1", 0.02});
  unc["2018"]["pt1"].insert({"eta2", 0.02});
  unc["2018"]["pt1"].insert({"eta3", 0.04});

  tsf["2018"].insert({"pt2", { }});
  tsf["2018"]["pt2"].insert({"eta0", 0.982});
  tsf["2018"]["pt2"].insert({"eta1", 0.966});
  tsf["2018"]["pt2"].insert({"eta2", 1.012});
  tsf["2018"]["pt2"].insert({"eta3", 0.952});  
  unc["2018"].insert({"pt2", { }});
  unc["2018"]["pt2"].insert({"eta0", 0.014});
  unc["2018"]["pt2"].insert({"eta1", 0.015});
  unc["2018"]["pt2"].insert({"eta2", 0.018});
  unc["2018"]["pt2"].insert({"eta3", 0.03});

  tsf["2018"].insert({"pt3", { }});
  tsf["2018"]["pt3"].insert({"eta0", 0.976});
  tsf["2018"]["pt3"].insert({"eta1", 0.967});
  tsf["2018"]["pt3"].insert({"eta2", 1.002});
  tsf["2018"]["pt3"].insert({"eta3", 0.999});  
  unc["2018"].insert({"pt3", { }});
  unc["2018"]["pt3"].insert({"eta0", 0.011});
  unc["2018"]["pt3"].insert({"eta1", 0.012});
  unc["2018"]["pt3"].insert({"eta2", 0.013});
  unc["2018"]["pt3"].insert({"eta3", 0.018});

  tsf["2018"].insert({"pt4", { }});
  tsf["2018"]["pt4"].insert({"eta0", 0.980});
  tsf["2018"]["pt4"].insert({"eta1", 0.964});
  tsf["2018"]["pt4"].insert({"eta2", 1.004});
  tsf["2018"]["pt4"].insert({"eta3", 1.003});  
  unc["2018"].insert({"pt4", { }});
  unc["2018"]["pt4"].insert({"eta0", 0.012});
  unc["2018"]["pt4"].insert({"eta1", 0.014});
  unc["2018"]["pt4"].insert({"eta2", 0.014});
  unc["2018"]["pt4"].insert({"eta3", 0.02});

  tsf["2018"].insert({"pt5", { }});
  tsf["2018"]["pt5"].insert({"eta0", 0.978});
  tsf["2018"]["pt5"].insert({"eta1", 0.960});
  tsf["2018"]["pt5"].insert({"eta2", 1.009});
  tsf["2018"]["pt5"].insert({"eta3", 1.024});  
  unc["2018"].insert({"pt5", { }});
  unc["2018"]["pt5"].insert({"eta0", 0.024});
  unc["2018"]["pt5"].insert({"eta1", 0.029});
  unc["2018"]["pt5"].insert({"eta2", 0.029});
  unc["2018"]["pt5"].insert({"eta3", 0.03});

  tsf["2018"].insert({"pt6", { }});
  tsf["2018"]["pt6"].insert({"eta0", 0.973});
  tsf["2018"]["pt6"].insert({"eta1", 0.985});
  tsf["2018"]["pt6"].insert({"eta2", 0.993});
  tsf["2018"]["pt6"].insert({"eta3", 0.993});  
  unc["2018"].insert({"pt6", { }});
  unc["2018"]["pt6"].insert({"eta0", 0.019});
  unc["2018"]["pt6"].insert({"eta1", 0.03});
  unc["2018"]["pt6"].insert({"eta2", 0.02});
  unc["2018"]["pt6"].insert({"eta3", 0.06});

  tsf["2018"].insert({"pt7", { }});
  tsf["2018"]["pt7"].insert({"eta0", 0.957});
  tsf["2018"]["pt7"].insert({"eta1", 0.988});
  tsf["2018"]["pt7"].insert({"eta2", 1.062});
  tsf["2018"]["pt7"].insert({"eta3", 1.070});  
  unc["2018"].insert({"pt7", { }});
  unc["2018"]["pt7"].insert({"eta0", 0.05});
  unc["2018"]["pt7"].insert({"eta1", 0.07});
  unc["2018"]["pt7"].insert({"eta2", 0.06});
  unc["2018"]["pt7"].insert({"eta3", 0.2});

  // 2017: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2017#Trigger_efficiency_AN2
  tsf.insert({"2017", { }});
  unc.insert({"2017", { }});

  tsf["2017"].insert({"pt0", { }});
  tsf["2017"]["pt0"].insert({"eta0", 0.0});
  tsf["2017"]["pt0"].insert({"eta1", 0.0});
  tsf["2017"]["pt0"].insert({"eta2", 0.0});
  tsf["2017"]["pt0"].insert({"eta3", 0.0});  
  unc["2017"].insert({"pt0", { }});
  unc["2017"]["pt0"].insert({"eta0", 0.0});
  unc["2017"]["pt0"].insert({"eta1", 0.0});
  unc["2017"]["pt0"].insert({"eta2", 0.0});
  unc["2017"]["pt0"].insert({"eta3", 0.0});

  tsf["2017"].insert({"pt1", { }});
  tsf["2017"]["pt1"].insert({"eta0", 0.986});
  tsf["2017"]["pt1"].insert({"eta1", 0.929});
  tsf["2017"]["pt1"].insert({"eta2", 0.980});
  tsf["2017"]["pt1"].insert({"eta3", 0.869});  
  unc["2017"].insert({"pt1", { }});
  unc["2017"]["pt1"].insert({"eta0", 0.016});
  unc["2017"]["pt1"].insert({"eta1", 0.02});
  unc["2017"]["pt1"].insert({"eta2", 0.02});
  unc["2017"]["pt1"].insert({"eta3", 0.05});

  tsf["2017"].insert({"pt2", { }});
  tsf["2017"]["pt2"].insert({"eta0", 0.968});
  tsf["2017"]["pt2"].insert({"eta1", 0.953});
  tsf["2017"]["pt2"].insert({"eta2", 0.981});
  tsf["2017"]["pt2"].insert({"eta3", 0.864});  
  unc["2017"].insert({"pt2", { }});
  unc["2017"]["pt2"].insert({"eta0", 0.014});
  unc["2017"]["pt2"].insert({"eta1", 0.017});
  unc["2017"]["pt2"].insert({"eta2", 0.02});
  unc["2017"]["pt2"].insert({"eta3", 0.03});

  tsf["2017"].insert({"pt3", { }});
  tsf["2017"]["pt3"].insert({"eta0", 0.969});
  tsf["2017"]["pt3"].insert({"eta1", 0.945});
  tsf["2017"]["pt3"].insert({"eta2", 0.985});
  tsf["2017"]["pt3"].insert({"eta3", 0.926});  
  unc["2017"].insert({"pt3", { }});
  unc["2017"]["pt3"].insert({"eta0", 0.012});
  unc["2017"]["pt3"].insert({"eta1", 0.013});
  unc["2017"]["pt3"].insert({"eta2", 0.013});
  unc["2017"]["pt3"].insert({"eta3", 0.02});

  tsf["2017"].insert({"pt4", { }});
  tsf["2017"]["pt4"].insert({"eta0", 0.967});
  tsf["2017"]["pt4"].insert({"eta1", 0.946});
  tsf["2017"]["pt4"].insert({"eta2", 0.991});
  tsf["2017"]["pt4"].insert({"eta3", 0.992});  
  unc["2017"].insert({"pt4", { }});
  unc["2017"]["pt4"].insert({"eta0", 0.012});
  unc["2017"]["pt4"].insert({"eta1", 0.015});
  unc["2017"]["pt4"].insert({"eta2", 0.014});
  unc["2017"]["pt4"].insert({"eta3", 0.02});

  tsf["2017"].insert({"pt5", { }});
  tsf["2017"]["pt5"].insert({"eta0", 0.964});
  tsf["2017"]["pt5"].insert({"eta1", 0.948});
  tsf["2017"]["pt5"].insert({"eta2", 0.986});
  tsf["2017"]["pt5"].insert({"eta3", 1.023});  
  unc["2017"].insert({"pt5", { }});
  unc["2017"]["pt5"].insert({"eta0", 0.015});
  unc["2017"]["pt5"].insert({"eta1", 0.02});
  unc["2017"]["pt5"].insert({"eta2", 0.02});
  unc["2017"]["pt5"].insert({"eta3", 0.03});

  tsf["2017"].insert({"pt6", { }});
  tsf["2017"]["pt6"].insert({"eta0", 0.963});
  tsf["2017"]["pt6"].insert({"eta1", 0.939});
  tsf["2017"]["pt6"].insert({"eta2", 1.002});
  tsf["2017"]["pt6"].insert({"eta3", 0.905});  
  unc["2017"].insert({"pt6", { }});
  unc["2017"]["pt6"].insert({"eta0", 0.02});
  unc["2017"]["pt6"].insert({"eta1", 0.03});
  unc["2017"]["pt6"].insert({"eta2", 0.03});
  unc["2017"]["pt6"].insert({"eta3", 0.07});

  tsf["2017"].insert({"pt7", { }});
  tsf["2017"]["pt7"].insert({"eta0", 0.951});
  tsf["2017"]["pt7"].insert({"eta1", 0.896});
  tsf["2017"]["pt7"].insert({"eta2", 0.922});
  tsf["2017"]["pt7"].insert({"eta3", 0.424});  
  unc["2017"].insert({"pt7", { }});
  unc["2017"]["pt7"].insert({"eta0", 0.06});
  unc["2017"]["pt7"].insert({"eta1", 0.11});
  unc["2017"]["pt7"].insert({"eta2", 0.10});
  unc["2017"]["pt7"].insert({"eta3", 0.52});

  // 2016: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2016#Trigger_efficiency_AN2
  tsf.insert({"2016", { }});
  unc.insert({"2016", { }});

  tsf["2016"].insert({"pt0", { }});
  tsf["2016"]["pt0"].insert({"eta0", 0.0});
  tsf["2016"]["pt0"].insert({"eta1", 0.0});
  tsf["2016"]["pt0"].insert({"eta2", 0.0});
  tsf["2016"]["pt0"].insert({"eta3", 0.0});  
  unc["2016"].insert({"pt0", { }});
  unc["2016"]["pt0"].insert({"eta0", 0.0});
  unc["2016"]["pt0"].insert({"eta1", 0.0});
  unc["2016"]["pt0"].insert({"eta2", 0.0});
  unc["2016"]["pt0"].insert({"eta3", 0.0});

  tsf["2016"].insert({"pt1", { }});
  tsf["2016"]["pt1"].insert({"eta0", 0.980});
  tsf["2016"]["pt1"].insert({"eta1", 0.938});
  tsf["2016"]["pt1"].insert({"eta2", 0.996});
  tsf["2016"]["pt1"].insert({"eta3", 0.934});  
  unc["2016"].insert({"pt1", { }});
  unc["2016"]["pt1"].insert({"eta0", 0.017});
  unc["2016"]["pt1"].insert({"eta1", 0.016});
  unc["2016"]["pt1"].insert({"eta2", 0.02});
  unc["2016"]["pt1"].insert({"eta3", 0.04});

  tsf["2016"].insert({"pt2", { }});
  tsf["2016"]["pt2"].insert({"eta0", 0.983});
  tsf["2016"]["pt2"].insert({"eta1", 0.958});
  tsf["2016"]["pt2"].insert({"eta2", 1.005});
  tsf["2016"]["pt2"].insert({"eta3", 0.954});  
  unc["2016"].insert({"pt2", { }});
  unc["2016"]["pt2"].insert({"eta0", 0.014});
  unc["2016"]["pt2"].insert({"eta1", 0.015});
  unc["2016"]["pt2"].insert({"eta2", 0.019});
  unc["2016"]["pt2"].insert({"eta3", 0.1});

  tsf["2016"].insert({"pt3", { }});
  tsf["2016"]["pt3"].insert({"eta0", 0.980});
  tsf["2016"]["pt3"].insert({"eta1", 0.956});
  tsf["2016"]["pt3"].insert({"eta2", 0.990});
  tsf["2016"]["pt3"].insert({"eta3", 0.948});  
  unc["2016"].insert({"pt3", { }});
  unc["2016"]["pt3"].insert({"eta0", 0.012});
  unc["2016"]["pt3"].insert({"eta1", 0.012});
  unc["2016"]["pt3"].insert({"eta2", 0.013});
  unc["2016"]["pt3"].insert({"eta3", 0.017});

  tsf["2016"].insert({"pt4", { }});
  tsf["2016"]["pt4"].insert({"eta0", 0.980});
  tsf["2016"]["pt4"].insert({"eta1", 0.948});
  tsf["2016"]["pt4"].insert({"eta2", 0.988});
  tsf["2016"]["pt4"].insert({"eta3", 0.935});  
  unc["2016"].insert({"pt4", { }});
  unc["2016"]["pt4"].insert({"eta0", 0.013});
  unc["2016"]["pt4"].insert({"eta1", 0.015});
  unc["2016"]["pt4"].insert({"eta2", 0.015});
  unc["2016"]["pt4"].insert({"eta3", 0.02});

  tsf["2016"].insert({"pt5", { }});
  tsf["2016"]["pt5"].insert({"eta0", 0.980});
  tsf["2016"]["pt5"].insert({"eta1", 0.927});
  tsf["2016"]["pt5"].insert({"eta2", 0.977});
  tsf["2016"]["pt5"].insert({"eta3", 0.888});  
  unc["2016"].insert({"pt5", { }});
  unc["2016"]["pt5"].insert({"eta0", 0.017});
  unc["2016"]["pt5"].insert({"eta1", 0.02});
  unc["2016"]["pt5"].insert({"eta2", 0.02});
  unc["2016"]["pt5"].insert({"eta3", 0.04});

  tsf["2016"].insert({"pt6", { }});
  tsf["2016"]["pt6"].insert({"eta0", 0.962});
  tsf["2016"]["pt6"].insert({"eta1", 0.911});
  tsf["2016"]["pt6"].insert({"eta2", 1.010});
  tsf["2016"]["pt6"].insert({"eta3", 0.953});  
  unc["2016"].insert({"pt6", { }});
  unc["2016"]["pt6"].insert({"eta0", 0.02});
  unc["2016"]["pt6"].insert({"eta1", 0.04});
  unc["2016"]["pt6"].insert({"eta2", 0.03});
  unc["2016"]["pt6"].insert({"eta3", 0.08});

  tsf["2016"].insert({"pt7", { }});
  tsf["2016"]["pt7"].insert({"eta0", 0.983});
  tsf["2016"]["pt7"].insert({"eta1", 0.824});
  tsf["2016"]["pt7"].insert({"eta2", 1.020});
  tsf["2016"]["pt7"].insert({"eta3", 1.134});  
  unc["2016"].insert({"pt7", { }});
  unc["2016"]["pt7"].insert({"eta0", 0.07});
  unc["2016"]["pt7"].insert({"eta1", 0.3});
  unc["2016"]["pt7"].insert({"eta2", 0.3});
  unc["2016"]["pt7"].insert({"eta3", 0.7});

}

#endif
