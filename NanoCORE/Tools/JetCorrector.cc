#include "JetCorrector.h"
#include "jetcorr/JetCorrectorParameters.icc"
#include "jetcorr/FactorizedJetCorrector.icc"
#include "jetcorr/SimpleJetCorrector.icc"

//this bullshit
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

class FactorizedJetCorrector *makeJetCorrector (const std::vector<std::string> &corrs)
{
    //See if the files exist and fucking warn me if not instead of fucking crashing
    for (unsigned int i = 0; i < corrs.size(); i++){
      if (!is_file_exist(corrs[i].c_str())) std::cout << "ERROR!! This JEC does not exist: " << corrs[i] << std::endl;
    }


    std::vector<JetCorrectorParameters> vParam;
    for (std::vector<std::string>::const_iterator i = corrs.begin(), i_end = corrs.end();
         i != i_end; ++i) {
        // do some rigmarole to evaluate env variables in the strings
        const std::string cmd = "echo ";
        FILE *f = popen((cmd + *i).c_str(), "r");
        if (!f) {
            perror((std::string("Opening pipe to execute ") + cmd + *i).c_str());
            return 0;
        }
        char corr_name[1024];
        int s = fscanf(f, " %1024s\n", corr_name);
        if (s != 1) {
            perror("reading file list");
        }
        assert(s == 1);
        JetCorrectorParameters JetCorPar(corr_name);
        // printf("%s\n", corr_name);
        vParam.push_back(JetCorrectorParameters(corr_name));
        pclose(f);
    }
    return new FactorizedJetCorrector(vParam);
}
