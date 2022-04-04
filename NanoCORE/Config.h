#ifndef CONFIG_H
#define CONFIG_H
#include <string>

/*
  Kept this as simple as possible.
  Need to check the year in a CORE function (or your own)? `gconf` is a global instance.
  if (gconf.year == 2017) { ... }
  Want to update the year in your babymaker?
  gconf.year = 2018;
  Need another variable? Add a line with a dummy default.
*/

class GlobalConfig {
  public:
    int year = 0;
    int nanoAOD_ver = 0; // 74, 80, 94, 101, ...
    int isAPV = 0; // if isAPV=1 it is first part of 2016 (HIPM)
    bool is_data = false;
    bool is_signal = false;
    float lumi = 0;
    std::string samptype = ""; // to be moved to enum
    std::string analysis = "";

    // Control for this class
    bool verbose = false;

    // JECs
    std::string jecEraA;
    std::string jecEraB;
    std::string jecEraC;
    std::string jecEraD;
    std::string jecEraE;
    std::string jecEraF;
    std::string jecEraG;
    std::string jecEraH;
    std::string jecEraMC;

    //_________________________________
    // B-tag working points
    float WP_DeepFlav_tight = -1;
    float WP_DeepFlav_medium = -1;
    float WP_DeepFlav_loose = -1;

    float WP_DeepCSV_tight = -1;
    float WP_DeepCSV_medium = -1;
    float WP_DeepCSV_loose = -1;

    float WP_CSVv2_tight = -1;
    float WP_CSVv2_medium = -1;
    float WP_CSVv2_loose = -1;

    // btagSF version (filename)
    std::string fn_btagSF_DeepFlav;
    std::string fn_btagSF_DeepCSV;
    std::string fn_btagSF_CSVv2;

    // Centrally maintained function
    void GetConfigs(int year = 0);          // pass in year or nothing
    void GetSampleType(std::string dsname); // reduce the sample name to shorter sample types
    void GetConfigsFromDatasetName(
        std::string dsname); // pass in the datasetname or filename (that contains the dataset info)
};

#ifndef __CINT__
extern GlobalConfig gconf;
#endif

#endif
