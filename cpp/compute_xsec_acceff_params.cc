/*
The following functions are implemented in this file:

=> std::vector<std::string> get_states():
- Returns a list of ff states for the possible Z'ff couplings (i.e., ['ss', 'sb', 'bb']).

=> std::vector<std::pair<std::string, std::string>> get_categories():
- Returns a list of category name-title pairs. Currently, the pairs are [ 'N1':'Nb_eq_1', 'N2':'Nb_geq_2' ].

=> void compute_initial_xsec(TString const& sample, TString coutput_main, TString production_dir):
- IMPORTANT NOTE: Please run this function through the script xsec_parallel.sh in the cpp/ directory.
- Makes an initial cross sections csv file by looping over the XSEC text files in a sample, and then looping over the sample ROOT files to divide them into Z'- ss, sb, and bb couplings.
- 'sample' is the main tag of the sample as it would exist on DAS/DIS (e.g., 'ZPrimeToMuMuSB_M1000_bestfit_TuneCP5_13TeV_Allanach_Y3_5f_madgraph_pythia8_NoPSWgts').
  > This string should be such that when split by the character '_', the second position refers to the mass, and the seventh position refers to the model name.
  > It should also contain 'MuMuSB' since the samples with Z'->mumu are grouped together.
- 'coutput_main' is the output directory, the current directory by default.
- 'production_dir' is the directory in which the MC samples are kept. Currently, the variable defaults to '/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404'.
- The product of this function is 'xsec_collected_initial.csv'.
The script is designed to run in parallel over multiple independent processes over bash but in a screen environment.
For that reason, the output file is produced by appending to it, so if you want to remake a file from scratch, you should delete this output first.
- If the output directory also contains a file called 'xsec_collected_origin.csv' (any csv you pick that contains all six of the model, mass, xsec_total, xsec_ss, xsec_sb, xsec_bb columns),
the script will open this file and read the ratios [xsec_ss, xsec_sb, xsec_bb]/xsec_total instead of looping over the ROOT files, which takes more time.
Looping over XSEC files takes very little time, so no functionality is implemented for that purpose.

=> void calculate_final_xsec(TString coutput_main):
- Makes the final xsec_collected.csv file by analyzing xsec_collected_initial.csv.
- The reason why this is done in a second stage is to put columns that also compare across the different models.
- In principle, xsec(model_1, xy->Z'->mumu)/xsec(model_2, xy->Z'->mumu) = [Gamma(Z'->xy*Gamma(Z'->mumu)/Gamma(Z')] (model_1) / [Gamma(Z'->xy*Gamma(Z'->mumu)/Gamma(Z')] (model_2).
That is because when you look at the individual Z'xy coupling states, their initial state and PDF composition should be the same,
and phase space factor in the computation of xsec or total/partial widths should drop out in ratios.
One can use this fact to reweight all models by 1/[Gamma(Z'->xy*Gamma(Z'->mumu)/Gamma(Z')], take an average, and then reweight the average back to compare.
We do not use these model-averaged cross sections, but it is good to see the level of agreement.
- The single argument is 'coutput_main' for the output directory.

=> void replaceXS(TString const& csvname, TString const& csvref):
- This is just a function that receives a csv file (path='csvname') and a reference csv (path='csvref') to replace the xsec_* entries so that xsec_total is the same as what is in the reference.

=> void parametrize_xsec(TString const& cinput, bool useModelAveraged):
- This is the main function that parametrizes the cross section for each model based on the csv file.
- 'cinput' is the path to the csv file for cross sections (e.g., '../data/xsec_collected.csv').
- 'useModelAveraged' is the flag that controls whether you want to parametrize xsec_[coupling state] entries as read directly from XSEC text files (useModelAveraged=false),
or xsec_[coupling state]_final entries from the model-averaged computations. The default is 'false'.
- The output is 'xsec_interpolation["" or "_ModelAveraged"].root', with TSpline3 objects named as 'spline_[model]_xsec_[ss,sb, or bb]'.
TGraph objects with the same name except 'spline'->'gr' are also provided to compare splines to the nodes.

=> void parametrize_acceff(TString const& period, TString const& cinput_xs, TString const& cinput_yields):
- This is the main function that parametrizes the acceptance*efficiency over all models.
- 'period' is the data period, which can be '2016_APV', '2016_NonAPV', '2017', '2018', 'Run2' (=2016-2018). It is needed to divide out the luminosity from the yields.
- 'cinput_xs' is the path to the csv file for cross sections.
- 'cinput_yields' is the path to the csv file for yields.
This input external to these functions and must contain the following columns: model, M, N1ss_w, N1bs_w, N1bb_w, N2ss_w, N2bs_w, N2bb_w, N1ss_r, N1bs_r, N1bb_r, N2ss_r, N2bs_r, N2bb_r.
- The output is 'acceff_interpolation_[period].root', with TSpline3 objects named as 'spline_[model or avg]_acceff_[ss, sb, or bb]_[Nb_eq_1 or Nb_geq_2]_[period]'.
TGraph objects with the same name except 'spline'->'gr' are also provided to compare splines to the nodes.
- In addition, for spline_avg* cases, the splines of squared uncertainties are also provided as 'spline_avg_errsq_[dn or up]_acceff_[ss, sb, or bb]_[Nb_eq_1 or Nb_geq_2]_[period]'.
- The category titles in the spline names may change if the function get_categories() does.

=> template<typename T> std::string get_plottable_label/get_plottable_hexcolor(T* obj) and void set_plottable_attributes(T* obj):
- These are functions to determine the plotting properties of TSpline3 and TGraph objects in one fell swoop.
- The first one determines the process label string as it would be written in LaTeX (e.g., "Y_{3}").
- The second one determines the color of the lines or markers.
- The last sets the line and marker attributes.
- One can change the behavior of these functions to influence how plots look.

=> void make_plots(TString const& cinput_xs_params, TString const& cinput_acceff_params):
- This is the function to plot cross sections and acceptance*efficiency parametrizations.
- 'cinput_xs_params' is the cross section parametrization file path.
- 'cinput_acceff_params' is the acceptance*efficiency parametrization file path.
- PDF and PNG files are placed into the current directory.
- Please note the horizontal dimension of the canvas for acceptance*efficiency plots is wider
in order to fit the y-axis labels for small acceptance values.
*/

#include <cassert>

#include "HostHelpersCore.h"
#include "SampleHelpersCore.h"
#include "IvyStreamHelpers.hh"
#include "HelperFunctions.h"
#include "IvyPDGHelpers.h"
#include "BaseTree.h"
#include "StatisticsHelpers.h"
#include "IvyCSVReader.h"

#include "TString.h"
#include "TDirectory.h"
#include "TFile.h"


using namespace std;
using namespace IvyStreamHelpers;


void run_dummy(TString const& sample, TString coutput_main=".", TString production_dir="/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404"){
  IVYout << "HELLO" << endl;
}

std::vector<std::string> get_states(){ return std::vector<std::string>{ "ss", "sb", "bb" }; }

std::vector<std::pair<std::string, std::string>> get_categories(){ return std::vector<std::pair<std::string, std::string>>{ { "N1", "Nb_eq_1" }, { "N2", "Nb_geq_2" } }; }

void compute_initial_xsec(TString const& sample, TString coutput_main=".", TString production_dir="/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404"){
  if (!sample.Contains("MuMuSB")) return;

  TString const coutput = coutput_main + "/xsec_collected_initial.csv";
  TString const coutput_origin = coutput_main + "/xsec_collected_origin.csv";
  TString const script_compute_width = "${CMSSW_BASE}/src/ZPrimeSnT/python/compute_width.py";

  std::vector<TString> sample_opts;
  HelperFunctions::splitOptionRecursive(sample, sample_opts, '_', false);
  TString strmass = sample_opts.at(1); HelperFunctions::replaceString<TString, TString const>(strmass, "M", "");
  int mass = -1; HelperFunctions::castStringToValue(strmass, mass);
  TString const& strmodel = sample_opts.at(6);

  IVYout << "Processing " << sample << ":" << endl;
  IVYout << "\t- Model: " << strmodel << endl;
  IVYout << "\t- Mass: " << mass << endl;

  TString cinput_main = production_dir + '/' + sample;
  auto const periods = SampleHelpers::lsdir(cinput_main);
  std::unordered_map<TString, std::pair<double, double>> xsecfile_xsecpair_map;
  for (auto const& period:periods){
    TString cinput_xsec = cinput_main + '/' + period + "/XSEC";
    auto const xsecfiles = SampleHelpers::lsdir(cinput_xsec);
    unsigned int ifile=0;
    for (auto const& xsecfile:xsecfiles){
      if (xsecfile_xsecpair_map.find(xsecfile)!=xsecfile_xsecpair_map.end()) continue;
      TString cinput = cinput_xsec + '/' + xsecfile;
      HelperFunctions::progressbar(ifile, xsecfiles.size());

      string str_in;
      double xsec, xsecerr;
      ifstream fin(cinput.Data());
      while (!fin.eof()){
        getline(fin, str_in);
        if (str_in.find("After filter: final cross section = ")!=std::string::npos){
          std::vector<std::string> tmpss;
          HelperFunctions::splitOptionRecursive(str_in, tmpss, ' ', false);
          xsec = std::stod(tmpss.at(6));
          xsecerr = std::stod(tmpss.at(8));
          break;
        }
      }
      fin.close();

      xsecfile_xsecpair_map[xsecfile] = std::pair<double, double>(xsec, xsecerr);
      ifile++;
    }
  }
  double xsec_all=0, xsec_wgt_all=0;
  for (auto const& pp:xsecfile_xsecpair_map){
    //double wgt_tmp = std::pow(pp.second.second, -2); // MG uncertainties are utter nonsense.
    double wgt_tmp = 1;
    double xsec_wgt_tmp = wgt_tmp * pp.second.first;
    xsec_all += xsec_wgt_tmp;
    xsec_wgt_all += wgt_tmp;
  }
  xsec_all /= xsec_wgt_all;
  xsec_wgt_all = 1./std::sqrt(xsec_wgt_all);
  IVYout << "\t- Total xsec: "  << xsec_all /*<< " +- " << xsec_wgt_all*/ << endl;

  std::unordered_map<unsigned int, double> proc_sumw_map;
  if (HostHelpers::FileReadable(coutput_origin.Data())){
    IvyCSVReader csvorigin(coutput_origin.Data());
    auto const& c_model = csvorigin["model"];
    auto const& c_mass = csvorigin["mass"];
    auto const& c_xsec_total = csvorigin["xsec_total"];
    auto const& c_xsec_ss = csvorigin["xsec_ss"];
    auto const& c_xsec_sb = csvorigin["xsec_sb"];
    auto const& c_xsec_bb = csvorigin["xsec_bb"];
    unsigned int nrows = csvorigin.getNRows();
    for (unsigned int irow=0; irow<nrows; irow++){
      if (c_model.at(irow)!=strmodel.Data()) continue;
      int v_mass = std::stod(c_mass.at(irow));
      if (v_mass!=mass) continue;
      double v_xsec_total = std::stod(c_xsec_total.at(irow));
      proc_sumw_map[9] = std::stod(c_xsec_ss.at(irow))/v_xsec_total;
      proc_sumw_map[15] = std::stod(c_xsec_sb.at(irow))/v_xsec_total;
      proc_sumw_map[25] = std::stod(c_xsec_bb.at(irow))/v_xsec_total;
      break;
    }
  }
  else{
    double sum_wgts = 0;
    for (auto const& period:periods){
      TString strfiles = cinput_main + '/' + period + "/NANOAODSIM/*.root";
      BaseTree tin(strfiles, "Events", "", "");
      tin.silenceUnused();
      tin.bookBranch<float>("genWeight", 0);
      tin.bookBranch<unsigned int>("nLHEPart", 0);
      tin.bookArrayBranch<int>("LHEPart_pdgId", -9000, 50);
      tin.bookArrayBranch<int>("LHEPart_status", 0, 50);
      float* wgt = nullptr; tin.getValRef("genWeight", wgt);
      unsigned int* nparts = nullptr; tin.getValRef("nLHEPart", nparts);
      int* const* ids = nullptr; tin.getValRef<int* const>("LHEPart_pdgId", ids);
      int* const* stats = nullptr; tin.getValRef<int* const>("LHEPart_status", stats);
      int nEntries = tin.getNEvents();
      IVYout << "\t- Looping over " << nEntries << " events..." << endl;
      for (int ev=0; ev<nEntries; ev++){
        tin.getEvent(ev);
        HelperFunctions::progressbar(ev, nEntries);
        unsigned int idx_fs = 1;
        for (unsigned int ip=0; ip<(*nparts); ip++){
          if (IvyPDGHelpers::isAQuark((*ids)[ip])){
            idx_fs *= std::abs((*ids)[ip]);
          }
        }
        if (proc_sumw_map.find(idx_fs)==proc_sumw_map.end()) proc_sumw_map[idx_fs]=0;
        proc_sumw_map[idx_fs] += *wgt;
      }
      break;
    }
    for (auto const& pp:proc_sumw_map) sum_wgts += pp.second;
    for (auto& pp:proc_sumw_map) pp.second /= sum_wgts;
  }

  IVYout << "\t- Process relative xsecs:" << endl;
  for (auto const& pp:proc_sumw_map) IVYout << "\t\t- " << pp.first << " => " << pp.second << endl;
  double xsec_ss = (proc_sumw_map.find(9)!=proc_sumw_map.end() ? proc_sumw_map[9] : 0.)*xsec_all;
  double xsec_sb = (proc_sumw_map.find(15)!=proc_sumw_map.end() ? proc_sumw_map[15] : 0.)*xsec_all;
  double xsec_bb = (proc_sumw_map.find(25)!=proc_sumw_map.end() ? proc_sumw_map[25] : 0.)*xsec_all;

  double xsec_ss_undoModel = xsec_ss;
  double xsec_sb_undoModel = xsec_sb;
  double xsec_bb_undoModel = xsec_bb;

  if (!HostHelpers::FileExists(coutput.Data())){
    IVYout.open(coutput.Data(), std::ios_base::out);
    IVYout << "model,mass,xsec_total,xsec_ss,xsec_sb,xsec_bb,xsec_ss_undoModel,xsec_sb_undoModel,xsec_bb_undoModel" << endl;
    IVYout.close();
  }

  {
    TString tmpfile = Form("tmp_%s_%i.txt", strmodel.Data(), mass);
    TString strCmdCore = Form("python %s --model %s --MZp %i --gzpfit 0 --t23 0 --useBaselineModelParams", script_compute_width.Data(), strmodel.Data(), mass);
    HostHelpers::ExecuteCommand((strCmdCore + " --channel \"ss~\" >> " + tmpfile).Data());
    HostHelpers::ExecuteCommand((strCmdCore + " --channel \"sb~\" >> " + tmpfile).Data());
    HostHelpers::ExecuteCommand((strCmdCore + " --channel \"bb~\" >> " + tmpfile).Data());
    HostHelpers::ExecuteCommand((strCmdCore + " --channel \"mu-mu+\" >> " + tmpfile).Data());
    HostHelpers::ExecuteCommand((strCmdCore + " --channel \"Zp\" >> " + tmpfile).Data());

    double tmpvals[5];
    ifstream ftmp(tmpfile.Data());
    for (unsigned char ic=0; ic<5; ic++) ftmp >> tmpvals[ic];
    ftmp.close();

    xsec_ss_undoModel *= tmpvals[4]/(tmpvals[0]*tmpvals[3]);
    xsec_sb_undoModel *= tmpvals[4]/(tmpvals[1]*tmpvals[3]);
    xsec_bb_undoModel *= tmpvals[4]/(tmpvals[2]*tmpvals[3]);

    HostHelpers::ExecuteCommand((TString("rm ") + tmpfile).Data());
  }

  IVYout.open(coutput.Data(), std::ios_base::app);
  IVYout
    << strmodel << ',' << mass
    << ',' << xsec_all*1000.
    << ',' << xsec_ss*1000. << ',' << xsec_sb*1000. << ',' << xsec_bb*1000.
    << ',' << xsec_ss_undoModel*1000. << ',' << xsec_sb_undoModel*1000. << ',' << xsec_bb_undoModel*1000.
    << endl;
  IVYout.close();
}

void calculate_final_xsec(TString coutput_main="."){
  std::vector<std::string> models;
  std::vector<int> masses;
  std::unordered_map<int, std::unordered_map<std::string, std::vector<double>> > mass_model_xsec_map;
  {
    TString const script_compute_width = "${CMSSW_BASE}/src/ZPrimeSnT/python/compute_width.py";
    TString const cinput = coutput_main + "/xsec_collected_initial.csv";
    IvyCSVReader csv(cinput.Data());
    for (unsigned int irow=0; irow<csv.getNRows(); irow++){
      auto const& model = csv["model"].at(irow);
      int mass = std::stoi(csv["mass"].at(irow));
      if (!HelperFunctions::checkListVariable(models, model)) models.push_back(model);
      if (!HelperFunctions::checkListVariable(masses, mass)) HelperFunctions::addByLowest(masses, mass, true);
      auto it_mass_model_xsec_map = mass_model_xsec_map.begin();
      if (!HelperFunctions::getUnorderedMapIterator(mass, mass_model_xsec_map, it_mass_model_xsec_map)){
        mass_model_xsec_map[mass] = std::unordered_map<std::string, std::vector<double>>();
        HelperFunctions::getUnorderedMapIterator(mass, mass_model_xsec_map, it_mass_model_xsec_map);
      }
      auto it_model_xsec_map = it_mass_model_xsec_map->second.begin();
      if (!HelperFunctions::getUnorderedMapIterator(model, it_mass_model_xsec_map->second, it_model_xsec_map)){
        it_mass_model_xsec_map->second[model] = std::vector<double>();
        HelperFunctions::getUnorderedMapIterator(model, it_mass_model_xsec_map->second, it_model_xsec_map);
      }
      auto& input_xseclist = it_model_xsec_map->second;
      input_xseclist.push_back(std::stod(csv["xsec_total"].at(irow)));
      input_xseclist.push_back(std::stod(csv["xsec_ss"].at(irow)));
      input_xseclist.push_back(std::stod(csv["xsec_sb"].at(irow)));
      input_xseclist.push_back(std::stod(csv["xsec_bb"].at(irow)));
      input_xseclist.push_back(std::stod(csv["xsec_ss_undoModel"].at(irow)));
      input_xseclist.push_back(std::stod(csv["xsec_sb_undoModel"].at(irow)));
      input_xseclist.push_back(std::stod(csv["xsec_bb_undoModel"].at(irow)));

      {
        TString tmpfile = Form("tmp_%s_%i.txt", model.data(), mass);
        TString strCmdCore = Form("python %s --model %s --MZp %i --gzpfit 0 --t23 0 --useBaselineModelParams", script_compute_width.Data(), model.data(), mass);
        HostHelpers::ExecuteCommand((strCmdCore + " --channel \"ss~\" >> " + tmpfile).Data());
        HostHelpers::ExecuteCommand((strCmdCore + " --channel \"sb~\" >> " + tmpfile).Data());
        HostHelpers::ExecuteCommand((strCmdCore + " --channel \"bb~\" >> " + tmpfile).Data());
        HostHelpers::ExecuteCommand((strCmdCore + " --channel \"mu-mu+\" >> " + tmpfile).Data());
        HostHelpers::ExecuteCommand((strCmdCore + " --channel \"Zp\" >> " + tmpfile).Data());

        double tmpval;
        ifstream ftmp(tmpfile.Data());
        for (unsigned char ic=0; ic<5; ic++){
          ftmp >> tmpval;
          input_xseclist.push_back(tmpval);
        }
        ftmp.close();

        HostHelpers::ExecuteCommand((TString("rm ") + tmpfile).Data());
      }
    }
  }

  TString const coutput = coutput_main + "/xsec_collected.csv";
  IVYout.open(coutput.Data());
  IVYout
    << "model,mass"
    << ",xsec_total"
    << ",xsec_ss,xsec_sb,xsec_bb"
    << ",xsec_ss_undoModel,xsec_sb_undoModel,xsec_bb_undoModel"
    << ",Gamma_ss~,Gamma_sb~,Gamma_bb~,Gamma_mumu,Gamma_Zp"
    << ",xsec_ss_undoModel_final,xsec_sb_undoModel_final,xsec_bb_undoModel_final"
    << ",xsec_ss_final,xsec_sb_final,xsec_bb_final"
    << ",xsec_total_final"
    << ",xsec_ss_unc,xsec_sb_unc,xsec_bb_unc"
    << endl;

  for (auto& mass:masses){
    auto& model_xsec_map = mass_model_xsec_map.find(mass)->second;
    bool const isMass100 = (mass==100);
    unsigned int avg_nmodels[3] = { 0 };
    double avg_xsec_channel_undoModel[3]={ 0 };
    double avg_xsecsq_channel_undoModel[3]={ 0 };
    for (auto const& pp:model_xsec_map){
      auto const& model = pp.first;
      auto const& xsecvals = pp.second;
      for (unsigned int ich=0; ich<3; ich++){
        if (isMass100 && model=="Y3" && ich!=1) continue;
        double const& xx = xsecvals.at(ich+4);
        if (xx==0.) continue;
        avg_xsec_channel_undoModel[ich] += xx;
        avg_xsecsq_channel_undoModel[ich] += xx*xx;
        avg_nmodels[ich]++;
      }
    }

    for (unsigned int ich=0; ich<3; ich++){
      avg_xsec_channel_undoModel[ich] /= static_cast<double>(avg_nmodels[ich]);
      avg_xsecsq_channel_undoModel[ich] /= static_cast<double>(avg_nmodels[ich]);
      avg_xsecsq_channel_undoModel[ich] = std::sqrt((avg_xsecsq_channel_undoModel[ich] - std::pow(avg_xsec_channel_undoModel[ich], 2))/(avg_nmodels[ich]-1))/avg_xsec_channel_undoModel[ich];
    }

    for (auto& pp:model_xsec_map){
      auto const& model = pp.first;
      auto& xsecvals = pp.second;
      bool const useSelfXS = (isMass100 && model=="Y3");
      for (unsigned int ich=0; ich<3; ich++){
        xsecvals.push_back(((useSelfXS && ich!=1) ? xsecvals.at(ich+4) : avg_xsec_channel_undoModel[ich]));
      }
      unsigned int tmp_size = xsecvals.size();
      assert(tmp_size==15);
      double xsec_total_final = 0;
      for (unsigned int ich=0; ich<3; ich++){
        xsecvals.push_back(xsecvals.at(tmp_size-3+ich)*xsecvals.at(tmp_size-8+ich)*xsecvals.at(tmp_size-5)/xsecvals.at(tmp_size-4));
        xsec_total_final += xsecvals.back();
      }
      xsecvals.push_back(xsec_total_final);
      for (unsigned int ich=0; ich<3; ich++) xsecvals.push_back(avg_xsecsq_channel_undoModel[ich]);

      IVYout << model << "," << mass;
      for (auto const& xx:xsecvals) IVYout << "," << xx;
      IVYout << endl;
    }
  }

  IVYout.close();
}

// Just in case we have to replace csv files for total xsec...
void replaceXS(TString const& csvname, TString const& csvref){
  IvyCSVReader csv(csvname.Data());
  IvyCSVReader xsref(csvref.Data());

  IVYout.open("replacement.csv");

  auto const& labels = csv.getLabels();
  for (unsigned int il=0; il<labels.size(); il++) IVYout << labels.at(il) << (il==labels.size()-1 ? "" : ",");
  IVYout << endl;
  for (unsigned int irow=0; irow<csv.getNRows(); irow++){
    std::string model;
    int mass=0;
    double xsec_total_csv=0;
    double xsec_ss_csv=0;
    double xsec_sb_csv=0;
    double xsec_bb_csv=0;
    double xsec_total_ref=0;

    for (auto const& lb:labels){
      if (lb=="model") model = csv[lb].at(irow);
      else if (lb=="mass") mass = std::stoi(csv[lb].at(irow));
      else if (lb=="xsec_total") xsec_total_csv = std::stod(csv[lb].at(irow));
      else if (lb=="xsec_ss") xsec_ss_csv = std::stod(csv[lb].at(irow));
      else if (lb=="xsec_sb") xsec_sb_csv = std::stod(csv[lb].at(irow));
      else if (lb=="xsec_bb") xsec_bb_csv = std::stod(csv[lb].at(irow));
    }

    for (unsigned int jrow=0; jrow<xsref.getNRows(); jrow++){
      std::string model_j;
      int mass_j=0;

      for (auto const& lbr:xsref.getLabels()){
        if (lbr=="model") model_j = xsref[lbr].at(jrow);
        else if (lbr=="mass") mass_j = std::stoi(xsref[lbr].at(jrow));
        else if (lbr=="xsec_total") xsec_total_ref = std::stod(xsref[lbr].at(jrow))*1000.;
      }

      if (mass_j==mass && model_j==model) break;
    }

    double sf = xsec_total_ref/xsec_total_csv;
    xsec_total_csv *= sf;
    xsec_ss_csv *= sf;
    xsec_sb_csv *= sf;
    xsec_bb_csv *= sf;

    for (unsigned int il=0; il<labels.size(); il++){
      auto const& lb = labels.at(il);
      if (lb == "xsec_total") IVYout << xsec_total_csv;
      else if (lb == "xsec_ss") IVYout << xsec_ss_csv;
      else if (lb == "xsec_sb") IVYout << xsec_sb_csv;
      else if (lb == "xsec_bb") IVYout << xsec_bb_csv;
      else IVYout << csv[lb].at(irow);
      IVYout << (il==labels.size()-1 ? "" : ",");
    }
    IVYout << endl;
  }

  IVYout.close();
}

void parametrize_xsec(TString const& cinput, bool useModelAveraged=false){
  std::unordered_map<std::string, std::vector<std::pair<double, double>> > hypo_mass_xsec_ss_pairs_map;
  std::unordered_map<std::string, std::vector<std::pair<double, double>> > hypo_mass_xsec_sb_pairs_map;
  std::unordered_map<std::string, std::vector<std::pair<double, double>> > hypo_mass_xsec_bb_pairs_map;

  IvyCSVReader csvreader(cinput.Data(), "#");
  std::vector<std::string> const& labels = csvreader.getLabels();

  std::vector<std::string> hypos;
  for (unsigned long long irow=0; irow<csvreader.getNRows(); irow++){
    std::string strhypo;
    double mass=0;
    double xsec_ss=0;
    double xsec_sb=0;
    double xsec_bb=0;
    for (auto const& cl:labels){
      if (cl=="model") strhypo = csvreader[cl].at(irow);
      else if (cl=="mass") mass = std::stod(csvreader[cl].at(irow));
      else if (cl==Form("xsec_ss%s", (useModelAveraged ? "_final" : ""))) xsec_ss = std::stod(csvreader[cl].at(irow));
      else if (cl==Form("xsec_sb%s", (useModelAveraged ? "_final" : ""))) xsec_sb = std::stod(csvreader[cl].at(irow));
      else if (cl==Form("xsec_bb%s", (useModelAveraged ? "_final" : ""))) xsec_bb = std::stod(csvreader[cl].at(irow));
    }

    if (!HelperFunctions::checkListVariable(hypos, strhypo)) hypos.push_back(strhypo);
    if (hypo_mass_xsec_ss_pairs_map.find(strhypo)==hypo_mass_xsec_ss_pairs_map.end()) hypo_mass_xsec_ss_pairs_map[strhypo] = std::vector<std::pair<double, double>>();
    if (hypo_mass_xsec_sb_pairs_map.find(strhypo)==hypo_mass_xsec_sb_pairs_map.end()) hypo_mass_xsec_sb_pairs_map[strhypo] = std::vector<std::pair<double, double>>();
    if (hypo_mass_xsec_bb_pairs_map.find(strhypo)==hypo_mass_xsec_bb_pairs_map.end()) hypo_mass_xsec_bb_pairs_map[strhypo] = std::vector<std::pair<double, double>>();

    if (xsec_ss>1e-4) HelperFunctions::addByLowest(hypo_mass_xsec_ss_pairs_map[strhypo], mass, std::log(xsec_ss));
    HelperFunctions::addByLowest(hypo_mass_xsec_sb_pairs_map[strhypo], mass, std::log(xsec_sb));
    HelperFunctions::addByLowest(hypo_mass_xsec_bb_pairs_map[strhypo], mass, std::log(xsec_bb));
  }

  TFile* foutput = TFile::Open(Form("xsec_interpolation%s.root", (useModelAveraged ? "_ModelAveraged" : "")), "recreate");
  for (auto const& strhypo:hypos){
    TGraph* gr_tmp = nullptr;
    TSpline3* sp_tmp = nullptr;
    sp_tmp = HelperFunctions::convertPointsToSpline3(hypo_mass_xsec_ss_pairs_map[strhypo], false, true);
    if (sp_tmp){
      sp_tmp->SetName(Form("spline_%s_xsec_ss", strhypo.data()));
      foutput->WriteTObject(sp_tmp); delete sp_tmp;
      gr_tmp = HelperFunctions::makeGraphFromPair(hypo_mass_xsec_ss_pairs_map[strhypo], Form("gr_%s_xsec_ss", strhypo.data()));
      foutput->WriteTObject(gr_tmp); delete gr_tmp;
    }
    sp_tmp = HelperFunctions::convertPointsToSpline3(hypo_mass_xsec_sb_pairs_map[strhypo], false, true);
    if (sp_tmp){
      sp_tmp->SetName(Form("spline_%s_xsec_sb", strhypo.data()));
      foutput->WriteTObject(sp_tmp); delete sp_tmp;
      gr_tmp = HelperFunctions::makeGraphFromPair(hypo_mass_xsec_sb_pairs_map[strhypo], Form("gr_%s_xsec_sb", strhypo.data()));
      foutput->WriteTObject(gr_tmp); delete gr_tmp;
    }
    sp_tmp = HelperFunctions::convertPointsToSpline3(hypo_mass_xsec_bb_pairs_map[strhypo], false, true);
    if (sp_tmp){
      sp_tmp->SetName(Form("spline_%s_xsec_bb", strhypo.data()));
      foutput->WriteTObject(sp_tmp); delete sp_tmp;
      gr_tmp = HelperFunctions::makeGraphFromPair(hypo_mass_xsec_bb_pairs_map[strhypo], Form("gr_%s_xsec_bb", strhypo.data()));
      foutput->WriteTObject(gr_tmp); delete gr_tmp;
    }
  }
  foutput->Close();
}

void parametrize_acceff(TString const& period, TString const& cinput_xs, TString const& cinput_yields){
  TDirectory* curdir = gDirectory;

  auto const states = get_states();
  unsigned int const nstates = states.size();

  auto const cats = get_categories();
  unsigned int const ncats = cats.size();

  double lumi=-1;
  if (period=="2016_APV") lumi=19.5;
  else if (period=="2016_NonAPV") lumi=16.8;
  else if (period=="2017") lumi=41.48;
  else if (period=="2018") lumi=59.83;
  else if (period=="Run2") lumi=19.5+16.8+41.48+59.83;
  else assert(0);

  typedef std::unordered_map<std::string, std::vector<std::pair<double, double>> > hmycp_map_t;
  std::vector<std::vector<hmycp_map_t>> hypo_mass_yield_pairs_map(nstates, std::vector<hmycp_map_t>(ncats, hmycp_map_t()));
  std::vector<std::vector<hmycp_map_t>> hypo_mass_count_pairs_map(nstates, std::vector<hmycp_map_t>(ncats, hmycp_map_t()));

  IvyCSVReader csv_yields(cinput_yields.Data());
  auto const& labels_yields = csv_yields.getLabels();
  unsigned int nrows_yields = csv_yields.getNRows();

  IvyCSVReader csv_xs(cinput_xs.Data());
  auto const& labels_xs = csv_xs.getLabels();
  unsigned int nrows_xs = csv_xs.getNRows();
  std::unordered_map<int, std::unordered_map<std::string, std::vector<double>> > mass_model_xsec_map;
  for (unsigned int irow=0; irow<nrows_xs; irow++){
    std::string model = csv_xs["model"].at(irow);
    int mass = std::stoi(csv_xs["mass"].at(irow));
    auto it_mass_model_xsec_map = mass_model_xsec_map.begin();
    if (!HelperFunctions::getUnorderedMapIterator(mass, mass_model_xsec_map, it_mass_model_xsec_map)){
      mass_model_xsec_map[mass] = std::unordered_map<std::string, std::vector<double>>();
      HelperFunctions::getUnorderedMapIterator(mass, mass_model_xsec_map, it_mass_model_xsec_map);
    }
    auto it_model_xsec_map = it_mass_model_xsec_map->second.begin();
    if (!HelperFunctions::getUnorderedMapIterator(model, it_mass_model_xsec_map->second, it_model_xsec_map)){
      it_mass_model_xsec_map->second[model] = std::vector<double>();
      HelperFunctions::getUnorderedMapIterator(model, it_mass_model_xsec_map->second, it_model_xsec_map);
    }
    auto& input_xseclist = it_model_xsec_map->second;
    // Input xsecs should ALWAYS be what is in the looper, not what is 'model-averaged' (i.e., not 'xsec_X_final').
    for (auto const& state:states) input_xseclist.push_back(std::stod(csv_xs[Form("xsec_%s", state.data())].at(irow)));
  }

  std::vector<std::string> hypos;
  for (unsigned int irow=0; irow<nrows_yields; irow++){
    std::string strhypo;
    int mass=0;
    std::vector<std::vector<double>> yield(nstates, std::vector<double>(ncats, 0));
    std::vector<std::vector<double>> count(nstates, std::vector<double>(ncats, 0));
    for (auto const& lb:labels_yields){
      if (lb=="model") strhypo = csv_yields[lb].at(irow);
      else if (lb=="M") mass = std::stoi(csv_yields[lb].at(irow));
      // THE ENTIRE REASON FOR A ZILLION IF-STATEMENTS IS BS VS SB!!!
      else if (lb=="N1ss_w") yield[0][0] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N1bs_w") yield[1][0] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N1bb_w") yield[2][0] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N2ss_w") yield[0][1] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N2bs_w") yield[1][1] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N2bb_w") yield[2][1] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N1ss_r") count[0][0] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N1bs_r") count[1][0] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N1bb_r") count[2][0] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N2ss_r") count[0][1] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N2bs_r") count[1][1] = std::stod(csv_yields[lb].at(irow));
      else if (lb=="N2bb_r") count[2][1] = std::stod(csv_yields[lb].at(irow));
    }

    if (!HelperFunctions::checkListVariable(hypos, strhypo)) hypos.push_back(strhypo);
    for (unsigned int is=0; is<nstates; is++){ // ss, sb, bb
      for (unsigned char ic=0; ic<ncats; ic++){ // Category
        if (hypo_mass_yield_pairs_map[is][ic].find(strhypo)==hypo_mass_yield_pairs_map[is][ic].end()) hypo_mass_yield_pairs_map[is][ic][strhypo] = std::vector<std::pair<double, double>>();
        if (hypo_mass_count_pairs_map[is][ic].find(strhypo)==hypo_mass_count_pairs_map[is][ic].end()) hypo_mass_count_pairs_map[is][ic][strhypo] = std::vector<std::pair<double, double>>();

        if (count[is][ic]>0){
          HelperFunctions::addByLowest(hypo_mass_yield_pairs_map[is][ic][strhypo], static_cast<double>(mass), yield[is][ic]/lumi/mass_model_xsec_map[mass][strhypo].at(is));
          HelperFunctions::addByLowest(hypo_mass_count_pairs_map[is][ic][strhypo], static_cast<double>(mass), count[is][ic]);
        }
      }
    }
  }

  TFile* foutput = TFile::Open(Form("acceff_interpolation_%s.root", period.Data()), "recreate");
  for (unsigned char is=0; is<nstates; is++){
    auto const& state = states.at(is);
    for (unsigned char ic=0; ic<ncats; ic++){
      TGraph* gr_tmp = nullptr;
      TSpline3* sp_tmp = nullptr;

      std::vector<double> masses_all;

      for (auto const& strhypo:hypos){
        sp_tmp = HelperFunctions::convertPointsToSpline3(hypo_mass_yield_pairs_map[is][ic][strhypo], false, true);
        if (sp_tmp){
          sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", strhypo.data(), state.data(), cats.at(ic).second.data(), period.Data()));
          foutput->WriteTObject(sp_tmp); delete sp_tmp;

          std::vector<std::pair<double, double>> errs_dn; errs_dn.reserve(hypo_mass_yield_pairs_map[is][ic][strhypo].size());
          std::vector<std::pair<double, double>> errs_up; errs_up.reserve(hypo_mass_yield_pairs_map[is][ic][strhypo].size());
          for (unsigned int ip=0; ip<hypo_mass_yield_pairs_map[is][ic][strhypo].size(); ip++){
            double val = hypo_mass_yield_pairs_map[is][ic][strhypo].at(ip).second;
            double count = hypo_mass_count_pairs_map[is][ic][strhypo].at(ip).second*0.5; // FIXME: We reduce counts to account for weight distributions, which is typical Neff reduction in standard MC.
            double val_dn=val, val_up=val;
            StatisticsHelpers::getPoissonCountingConfidenceInterval_Frequentist(count, 0.684, val_dn, val_up); val_dn *= val/count; val_up *= val/count;

            errs_dn.emplace_back(0., std::abs(val_dn-val));
            errs_up.emplace_back(0., val_up-val);
          }

          gr_tmp = HelperFunctions::makeGraphAsymErrFromPair(hypo_mass_yield_pairs_map[is][ic][strhypo], errs_dn, errs_up, Form("gr_%s_acceff_%s_%s_%s", strhypo.data(), state.data(), cats.at(ic).second.data(), period.Data()));
          foutput->WriteTObject(gr_tmp); delete gr_tmp;

          for (auto const& pp:hypo_mass_yield_pairs_map[is][ic][strhypo]) HelperFunctions::addByLowest(masses_all, pp.first, true);
        }
      }

      std::vector<std::vector<double>> acceff_hypos_nominal;
      std::vector<std::vector<double>> acceff_hypos_errdn;
      std::vector<std::vector<double>> acceff_hypos_errup;
      acceff_hypos_nominal.assign(masses_all.size(), std::vector<double>());
      acceff_hypos_errdn.assign(masses_all.size(), std::vector<double>());
      acceff_hypos_errup.assign(masses_all.size(), std::vector<double>());
      for (auto const& strhypo:hypos){
        unsigned int npoints = hypo_mass_yield_pairs_map[is][ic][strhypo].size();
        for (unsigned int ip=0; ip<npoints; ip++){
          auto const& pp = hypo_mass_yield_pairs_map[is][ic][strhypo].at(ip);
          auto const& mass = pp.first;
          auto const& val = pp.second;
          auto const& count = hypo_mass_count_pairs_map[is][ic][strhypo].at(ip).second*0.5; // FIXME: We reduce counts to account for weight distributions, which is typical Neff reduction in standard MC.

          double val_dn=val, val_up=val;
          StatisticsHelpers::getPoissonCountingConfidenceInterval_Frequentist(count, 0.684, val_dn, val_up); val_dn *= val/count; val_up *= val/count;

          unsigned int jp=0;
          for (auto const& mm:masses_all){
            if (mm==mass) break;
            jp++;
          }

          acceff_hypos_nominal.at(jp).push_back(val);
          acceff_hypos_errdn.at(jp).push_back(val-val_dn);
          acceff_hypos_errup.at(jp).push_back(val_up-val);
        }
      }

      if (masses_all.empty()){
        IVYerr << "No masses exist in " << state << " " << cats.at(ic).second << "." << endl;
      }

      std::vector<std::pair<double, double>> mass_acceff_pairs_allhypos_nominal;
      std::vector<std::pair<double, double>> mass_acceff_pairs_allhypos_errdn;
      std::vector<std::pair<double, double>> mass_acceff_pairs_allhypos_errup;
      for (unsigned int ip=0; ip<masses_all.size(); ip++){
        double const& mass = masses_all.at(ip);

        double sum_acceff = 0;
        double sumerrsq_acceff = 0;
        double sumerrsqdn_acceff = 0;
        double sumerrsqup_acceff = 0;

        for (unsigned int ih=0; ih<acceff_hypos_nominal.at(ip).size(); ih++){
          double const& nom = acceff_hypos_nominal.at(ip).at(ih);
          double const& errdn = acceff_hypos_errdn.at(ip).at(ih);
          double const& errup = acceff_hypos_errup.at(ip).at(ih);
          double err = (errdn + errup)/2.;
          sum_acceff += nom/std::pow(err, 2);
          sumerrsq_acceff += 1./std::pow(err, 2);
          sumerrsqdn_acceff += 1./std::pow(errdn, 2);
          sumerrsqup_acceff += 1./std::pow(errup, 2);
        }

        sum_acceff /= sumerrsq_acceff;
        sumerrsqdn_acceff = 1./sumerrsqdn_acceff;
        sumerrsqup_acceff = 1./sumerrsqup_acceff;

        mass_acceff_pairs_allhypos_nominal.emplace_back(mass, sum_acceff);
        mass_acceff_pairs_allhypos_errdn.emplace_back(mass, sumerrsqdn_acceff);
        mass_acceff_pairs_allhypos_errup.emplace_back(mass, sumerrsqup_acceff);
      }

      // This is an ad hoc fix, but it works.
      // Otherwise, the spline goes negative.
      if (state=="ss" && cats.at(ic).second=="Nb_eq_1"){
        for (auto const& xx:std::vector<double>{495., 525., 705.}){
          double x1=0, x2=0, y1=0, y2=0;
          for (auto const& pp:mass_acceff_pairs_allhypos_nominal){
            if (pp.first<xx){
              x1=pp.first;
              y1=pp.second;
            }
            else{
              x2=pp.first;
              y2=pp.second;
              break;
            }
          }
          double yy = y1 + (y2-y1)/(x2-x1)*(xx-x1);
          HelperFunctions::addByLowest(mass_acceff_pairs_allhypos_nominal, xx, yy);
        }
      }
      sp_tmp = HelperFunctions::convertPointsToSpline3(mass_acceff_pairs_allhypos_nominal, false, true);
      if (sp_tmp){
        sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", "avg", state.data(), cats.at(ic).second.data(), period.Data()));
        foutput->WriteTObject(sp_tmp); delete sp_tmp;
        gr_tmp = HelperFunctions::makeGraphFromPair(mass_acceff_pairs_allhypos_nominal, Form("gr_%s_acceff_%s_%s_%s", "avg", state.data(), cats.at(ic).second.data(), period.Data()));
        foutput->WriteTObject(gr_tmp); delete gr_tmp;
      }

      sp_tmp = HelperFunctions::convertPointsToSpline3(mass_acceff_pairs_allhypos_errdn, false, true);
      if (sp_tmp){
        sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", "avg_errsq_dn", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(sp_tmp); delete sp_tmp;
        gr_tmp = HelperFunctions::makeGraphFromPair(mass_acceff_pairs_allhypos_errdn, Form("gr_%s_acceff_%s_%s_%s", "avg_errsq_dn", state.data(), cats.at(ic).second.data(), period.Data()));
        foutput->WriteTObject(gr_tmp); delete gr_tmp;
      }

      sp_tmp = HelperFunctions::convertPointsToSpline3(mass_acceff_pairs_allhypos_errup, false, true);
      if (sp_tmp){
        sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", "avg_errsq_up", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(sp_tmp); delete sp_tmp;
        gr_tmp = HelperFunctions::makeGraphFromPair(mass_acceff_pairs_allhypos_errup, Form("gr_%s_acceff_%s_%s_%s", "avg_errsq_up", state.data(), cats.at(ic).second.data(), period.Data()));
        foutput->WriteTObject(gr_tmp); delete gr_tmp;
      }
    }
  }
  foutput->Close();
}


////////////////////
// Plotting stuff //
////////////////////
#include "TText.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TStyle.h"


template<typename T> std::string get_plottable_label(T* obj){
  std::string res;
  TString sname = obj->GetName();
  // When testing for model names, make sure to put an '_' at the beginning and end.
  // Otherwise, model==Y3 also tests true for DY3.
  if (sname.Contains("_Y3_")) res = "Y_{3}";
  else if (sname.Contains("_DY3_")) res = "DY_{3}";
  else if (sname.Contains("_DYp3_")) res = "DY'_{3}";
  else if (sname.Contains("_B3mL2_")) res = "B_{3}-L_{2}";
  return res;
}

template<typename T> std::string get_plottable_hexcolor(T* obj){
  std::string res = "#000000";

  TString sname = obj->GetName();
  // When testing for model names, make sure to put an '_' at the beginning and end.
  // Otherwise, model==Y3 also tests true for DY3.
  if (sname.Contains("_Y3_")) res = "#ff0000";
  else if (sname.Contains("_DY3_")) res = "#ffcc00";
  else if (sname.Contains("_DYp3_")) res = "#9900cc";
  else if (sname.Contains("_B3mL2_")) res = "#3333ff";

  return res;
}

template<typename T> void set_plottable_attributes(T* obj){
  std::string hex = get_plottable_hexcolor(obj);
  TAttLine* line = dynamic_cast<TAttLine*>(obj);
  if (line){
    line->SetLineColor(TColor::GetColor(hex.data()));
    line->SetLineWidth(2);
  }
  TAttMarker* marker = dynamic_cast<TAttMarker*>(obj);
  if (marker){
    marker->SetMarkerColor(TColor::GetColor(hex.data()));
    marker->SetMarkerSize(1.2);
  }
}

void make_plots(TString const& cinput_xs_params, TString const& cinput_acceff_params){
  gStyle->SetOptStat(0);

  // Magic numbers
  constexpr double npixels_stdframe_xy = 800;
  constexpr double relmargin_frame_right = 0.05;
  constexpr double relmargin_frame_CMS = 0.07;
  constexpr double relmargin_frame_XTitle = 0.15;
  constexpr double relsize_CMSlogo = 0.98;
  constexpr double relsize_CMSlogo_sqrts = 0.8;
  constexpr double relsize_XYTitle = 0.9;
  constexpr double relsize_XYLabel = 0.8;
  constexpr double offset_xlabel = 0.02;
  constexpr double offset_ylabel = 0.02;
  constexpr double offset_xtitle = 1.09;

  TDirectory* curdir = gDirectory;

  auto const states = get_states();
  unsigned int const nstates = states.size();

  auto const cats = get_categories();
  unsigned int const ncats = cats.size();

  {
    constexpr double relmargin_frame_left = 0.20;
    constexpr double offset_ytitle = 1.3;
    const double npixels_CMSlogo = npixels_stdframe_xy*relmargin_frame_CMS*relsize_CMSlogo;
    const double npixels_CMSlogo_sqrts = npixels_CMSlogo*relsize_CMSlogo_sqrts;
    const double npixels_XYTitle = npixels_CMSlogo*relsize_XYTitle;
    const double npixels_XYLabel = npixels_CMSlogo*relsize_XYLabel;
    const double npixels_x = int(
      npixels_stdframe_xy*(
        1.
        + relmargin_frame_left
        + relmargin_frame_right
        ) + 0.5
      );
    const double npixels_y = int(
      npixels_stdframe_xy*(
        relmargin_frame_CMS
        + 1.
        + relmargin_frame_XTitle
        ) + 0.5
      );
    const double margin_left = double(int(relmargin_frame_left*npixels_stdframe_xy))/npixels_x;
    const double margin_right = double(int(relmargin_frame_right*npixels_stdframe_xy))/npixels_x;
    const double margin_top = double(int(relmargin_frame_CMS*npixels_stdframe_xy)-1)/npixels_y;
    const double margin_bot = double(int(relmargin_frame_XTitle*npixels_stdframe_xy))/npixels_y;

    TFile* fxs = TFile::Open(cinput_xs_params.Data(), "read");

    std::vector<TSpline3*> splines_xs;
    HelperFunctions::extractObjectsFromDirectory(fxs, splines_xs);
    std::vector<TGraph*> grs_xs;
    HelperFunctions::extractObjectsFromDirectory(fxs, grs_xs);

    for (auto const& state:states){
      double xmin = 9e9;
      double xmax = -9e9;
      double ymin = 9e9;
      double ymax = -9e9;

      std::vector<TSpline3*> splines_plottable; splines_plottable.reserve(splines_xs.size());
      for (auto const& obj:splines_xs){
        TString sname = obj->GetName();
        if (sname.Contains(Form("xsec_%s", state.data()))){
          set_plottable_attributes(obj);
          obj->SetLineStyle(7);
          splines_plottable.push_back(obj);
          xmin = std::min(xmin, obj->GetXmin());
          xmax = std::max(xmax, obj->GetXmax());
        }
      }
      std::sort(splines_plottable.begin(), splines_plottable.end(), [] (TSpline* a, TSpline* b){ return get_plottable_label(a)<get_plottable_label(b); });

      std::vector<TGraph*> grs_plottable; grs_plottable.reserve(grs_xs.size());
      for (auto const& obj:grs_xs){
        TString sname = obj->GetName();
        if (sname.Contains(Form("xsec_%s", state.data()))){
          set_plottable_attributes(obj);
          obj->SetMarkerStyle(29); // Since xsec graphs do not have error bars, make sure to put a visible shape.
          obj->SetMarkerSize(3.5);
          grs_plottable.push_back(obj);
          for (int ip=0; ip<obj->GetN(); ip++){
            ymin = std::min(ymin, obj->GetY()[ip]);
            ymax = std::max(ymax, obj->GetY()[ip]);
          }
        }
      }
      std::sort(grs_plottable.begin(), grs_plottable.end(), [] (TGraph* a, TGraph* b){ return get_plottable_label(a)<get_plottable_label(b); });

      xmin -= 20.;
      xmax += 20.;
      ymin -= std::abs(ymax - ymin)*0.1;
      ymax += std::abs(ymax - ymin)*0.1;
      unsigned int nleg = grs_plottable.size();

      TCanvas canvas(Form("c_xsec_%s_params", state.data()), "", 8, 30, npixels_x, npixels_y);
      canvas.cd();
      canvas.SetFillColor(0);
      canvas.SetBorderMode(0);
      canvas.SetBorderSize(2);
      canvas.SetTickx(1);
      canvas.SetTicky(1);
      canvas.SetFrameFillStyle(0);
      canvas.SetFrameBorderMode(0);
      canvas.SetFrameFillStyle(0);
      canvas.SetFrameBorderMode(0);
      canvas.SetLeftMargin(margin_left);
      canvas.SetRightMargin(margin_right);
      canvas.SetTopMargin(margin_top);
      canvas.SetBottomMargin(margin_bot);

      double leg_xmax = (0.97 + relmargin_frame_left)/(1. + relmargin_frame_left + relmargin_frame_right);
      double leg_xmin = (0.6 + relmargin_frame_left)/(1. + relmargin_frame_left + relmargin_frame_right);
      double leg_ymax=(npixels_y - npixels_stdframe_xy*(0.05 + relmargin_frame_CMS))/npixels_y;
      double leg_ymin=leg_ymax; leg_ymin -= npixels_XYTitle*nleg/npixels_y*1.25;
      TLegend legend(leg_xmin, leg_ymin, leg_xmax, leg_ymax);
      legend.SetBorderSize(0);
      legend.SetTextFont(43);
      legend.SetTextSize(npixels_XYTitle);
      legend.SetLineColor(1);
      legend.SetLineStyle(1);
      legend.SetLineWidth(1);
      legend.SetFillColor(0);
      legend.SetFillStyle(0);

      TH1F htmp("htmp", "", 1, xmin, xmax);
      htmp.SetBinContent(1, -9999.);
      htmp.SetLineColor(kBlack);

      htmp.GetXaxis()->SetNdivisions(505);
      htmp.GetXaxis()->SetLabelFont(43);
      htmp.GetXaxis()->SetLabelOffset(offset_xlabel);
      htmp.GetXaxis()->SetLabelSize(npixels_XYLabel);
      htmp.GetXaxis()->SetTitleFont(42);
      htmp.GetXaxis()->SetTitleSize(npixels_XYTitle/npixels_y);
      htmp.GetXaxis()->SetTitleOffset(offset_xtitle);
      htmp.GetYaxis()->SetLabelFont(43);
      htmp.GetYaxis()->SetLabelOffset(offset_ylabel);
      htmp.GetYaxis()->SetLabelSize(npixels_XYLabel);
      htmp.GetYaxis()->SetTitleFont(42);
      htmp.GetYaxis()->SetTitleSize(npixels_XYTitle/npixels_y);
      htmp.GetYaxis()->SetTitleOffset(offset_ytitle);

      htmp.GetXaxis()->SetTitle("m_{Z'} (GeV)");
      htmp.GetXaxis()->CenterTitle();
      htmp.GetYaxis()->SetTitle(Form("ln[#sigma_{%s}] (ln[fb])", state.data()));
      htmp.GetYaxis()->SetRangeUser(ymin, ymax);
      htmp.GetYaxis()->CenterTitle();
      htmp.Draw("hist");

      for (auto const& obj:splines_plottable){
        obj->SetTitle("");
        obj->Draw("csame");
      }
      for (auto const& obj:grs_plottable){
        obj->SetTitle("");
        obj->Draw("psame");
        legend.AddEntry(obj, get_plottable_label(obj).data(), "p");
      }

      TText* text;
      TPaveText pt(
        margin_left,
        1.-margin_top,
        1.-margin_right,
        1.,
        "brNDC"
      );
      pt.SetBorderSize(0);
      pt.SetFillStyle(0);
      pt.SetTextAlign(22);
      pt.SetTextFont(43);
      text = pt.AddText(0.001, 0.5, "CMS");
      text->SetTextFont(63);
      text->SetTextSize(npixels_CMSlogo);
      text->SetTextAlign(12);
      text = pt.AddText(npixels_CMSlogo*2.2/npixels_stdframe_xy, 0.45, "Simulation");
      text->SetTextFont(53);
      text->SetTextSize(npixels_CMSlogo*relsize_CMSlogo_sqrts);
      text->SetTextAlign(12);
      int theSqrts=13;
      TString cErgTev = Form("%i TeV", theSqrts);
      text = pt.AddText(0.999, 0.45, cErgTev);
      text->SetTextFont(43);
      text->SetTextSize(npixels_CMSlogo*relsize_CMSlogo_sqrts);
      text->SetTextAlign(32);

      canvas.cd();
      legend.Draw();
      pt.Draw();
      //ptc.Draw();

      canvas.RedrawAxis();
      canvas.Modified();
      canvas.Update();
      canvas.SaveAs(TString(canvas.GetName()) + ".pdf");
      canvas.SaveAs(TString(canvas.GetName()) + ".png");

      canvas.Close();
    }

    fxs->Close();
  }

  curdir->cd();
  
  {
    constexpr double relmargin_frame_left = 0.30;
    constexpr double offset_ytitle = 2.1;
    const double npixels_CMSlogo = npixels_stdframe_xy*relmargin_frame_CMS*relsize_CMSlogo;
    const double npixels_CMSlogo_sqrts = npixels_CMSlogo*relsize_CMSlogo_sqrts;
    const double npixels_XYTitle = npixels_CMSlogo*relsize_XYTitle;
    const double npixels_XYLabel = npixels_CMSlogo*relsize_XYLabel;
    const double npixels_x = int(
      npixels_stdframe_xy*(
        1.
        + relmargin_frame_left
        + relmargin_frame_right
        ) + 0.5
      );
    const double npixels_y = int(
      npixels_stdframe_xy*(
        relmargin_frame_CMS
        + 1.
        + relmargin_frame_XTitle
        ) + 0.5
      );
    const double margin_left = double(int(relmargin_frame_left*npixels_stdframe_xy))/npixels_x;
    const double margin_right = double(int(relmargin_frame_right*npixels_stdframe_xy))/npixels_x;
    const double margin_top = double(int(relmargin_frame_CMS*npixels_stdframe_xy)-1)/npixels_y;
    const double margin_bot = double(int(relmargin_frame_XTitle*npixels_stdframe_xy))/npixels_y;

    TFile* facceff = TFile::Open(cinput_acceff_params.Data(), "read");
    std::vector<TSpline3*> splines;
    HelperFunctions::extractObjectsFromDirectory(facceff, splines);
    std::vector<TGraphAsymmErrors*> grs;
    HelperFunctions::extractObjectsFromDirectory(facceff, grs);

    for (auto const& state:states){
      for (auto const& cat:cats){
        double xmin = 9e9;
        double xmax = -9e9;
        double ymin = 0;
        double ymax = -9e9;

        std::vector<TSpline3*> splines_plottable; splines_plottable.reserve(splines.size());
        for (auto const& obj:splines){
          TString sname = obj->GetName();
          if (sname.Contains(Form("avg_acceff_%s_%s", state.data(), cat.second.data())) && sname.Contains("avg") && !sname.Contains("errsq")){
            set_plottable_attributes(obj);
            splines_plottable.push_back(obj);
            xmin = std::min(xmin, obj->GetXmin());
            xmax = std::max(xmax, obj->GetXmax());
            obj->SetNpx(10000);
          }
        }
        std::sort(splines_plottable.begin(), splines_plottable.end(), [] (TSpline3* a, TSpline3* b){ return get_plottable_label(a)<get_plottable_label(b); });

        std::vector<TGraph*> grs_plottable; grs_plottable.reserve(grs.size());
        for (auto const& obj:grs){
          TString sname = obj->GetName();
          if (sname.Contains(Form("acceff_%s_%s", state.data(), cat.second.data())) && !sname.Contains("avg") && !sname.Contains("errsq")){
            set_plottable_attributes(obj);
            grs_plottable.push_back(obj);
            for (int ip=0; ip<obj->GetN(); ip++){
              ymax = std::max(ymax, obj->GetY()[ip]+obj->GetEYhigh()[ip]);
            }
          }
        }
        std::sort(grs_plottable.begin(), grs_plottable.end(), [] (TGraph* a, TGraph* b){ return get_plottable_label(a)<get_plottable_label(b); });

        xmin -= 20.;
        xmax += 20.;
        ymax += std::abs(ymax - ymin)*0.5;
        ymax = std::min(ymax, 1.);
        unsigned int nleg = grs_plottable.size()+1;

        TCanvas canvas(Form("c_acceff_%s_%s_params", state.data(), cat.second.data()), "", 8, 30, npixels_x, npixels_y);
        canvas.cd();
        canvas.SetFillColor(0);
        canvas.SetBorderMode(0);
        canvas.SetBorderSize(2);
        canvas.SetTickx(1);
        canvas.SetTicky(1);
        canvas.SetFrameFillStyle(0);
        canvas.SetFrameBorderMode(0);
        canvas.SetFrameFillStyle(0);
        canvas.SetFrameBorderMode(0);
        canvas.SetLeftMargin(margin_left);
        canvas.SetRightMargin(margin_right);
        canvas.SetTopMargin(margin_top);
        canvas.SetBottomMargin(margin_bot);

        double leg_xmax = (0.35 + relmargin_frame_left)/(1. + relmargin_frame_left + relmargin_frame_right);
        double leg_xmin = (0.05 + relmargin_frame_left)/(1. + relmargin_frame_left + relmargin_frame_right);
        double leg_ymax=(npixels_y - npixels_stdframe_xy*(0.05 + relmargin_frame_CMS))/npixels_y;
        double leg_ymin=leg_ymax; leg_ymin -= npixels_XYTitle*nleg/npixels_y*1.25;
        TLegend legend(leg_xmin, leg_ymin, leg_xmax, leg_ymax);
        legend.SetBorderSize(0);
        legend.SetTextFont(43);
        legend.SetTextSize(npixels_XYTitle);
        legend.SetLineColor(1);
        legend.SetLineStyle(1);
        legend.SetLineWidth(1);
        legend.SetFillColor(0);
        legend.SetFillStyle(0);

        TPaveText ptc(
          leg_xmax,
          leg_ymax - npixels_XYTitle/npixels_y*(1.25+0.15),
          leg_xmax + 0.2/(1. + relmargin_frame_left + relmargin_frame_right),
          leg_ymax,
          "brNDC"
        );
        ptc.SetBorderSize(0);
        ptc.SetFillStyle(0);
        ptc.SetTextAlign(12);
        ptc.SetTextFont(43);
        ptc.SetTextSize(npixels_XYTitle);
        ptc.AddText(0.001, 0.5, Form("Z'%s in N_{b}%s", state.data(), (cat.second=="Nb_eq_1" ? "=1" : "#geq2")));

        TH1F htmp("htmp", "", 1, xmin, xmax);
        htmp.SetBinContent(1, -9999.);
        htmp.SetLineColor(kBlack);

        htmp.GetXaxis()->SetNdivisions(505);
        htmp.GetXaxis()->SetLabelFont(43);
        htmp.GetXaxis()->SetLabelOffset(offset_xlabel);
        htmp.GetXaxis()->SetLabelSize(npixels_XYLabel);
        htmp.GetXaxis()->SetTitleFont(42);
        htmp.GetXaxis()->SetTitleSize(npixels_XYTitle/npixels_y);
        htmp.GetXaxis()->SetTitleOffset(offset_xtitle);
        htmp.GetYaxis()->SetNdivisions(505);
        htmp.GetYaxis()->SetLabelFont(43);
        htmp.GetYaxis()->SetLabelOffset(offset_ylabel);
        htmp.GetYaxis()->SetLabelSize(npixels_XYLabel);
        htmp.GetYaxis()->SetTitleFont(42);
        htmp.GetYaxis()->SetTitleSize(npixels_XYTitle/npixels_y);
        htmp.GetYaxis()->SetTitleOffset(offset_ytitle);

        htmp.GetXaxis()->SetTitle("m_{Z'} (GeV)");
        htmp.GetXaxis()->CenterTitle();
        htmp.GetYaxis()->SetTitle("acc. #times eff.");
        htmp.GetYaxis()->SetRangeUser(ymin, ymax);
        htmp.GetYaxis()->CenterTitle();
        htmp.Draw("hist");

        for (auto const& obj:splines_plottable){
          obj->SetTitle("");
          obj->Draw("csame");
        }
        for (auto const& obj:grs_plottable){
          obj->SetTitle("");
          obj->Draw("psame");
          legend.AddEntry(obj, get_plottable_label(obj).data(), "ep");
        }
        legend.AddEntry(splines_plottable.front(), "Average", "l");

        TText* text;
        TPaveText pt(
          margin_left,
          1.-margin_top,
          1.-margin_right,
          1.,
          "brNDC"
        );
        pt.SetBorderSize(0);
        pt.SetFillStyle(0);
        pt.SetTextAlign(22);
        pt.SetTextFont(43);
        text = pt.AddText(0.001, 0.5, "CMS");
        text->SetTextFont(63);
        text->SetTextSize(npixels_CMSlogo);
        text->SetTextAlign(12);
        text = pt.AddText(npixels_CMSlogo*2.2/npixels_stdframe_xy, 0.45, "Simulation");
        text->SetTextFont(53);
        text->SetTextSize(npixels_CMSlogo*relsize_CMSlogo_sqrts);
        text->SetTextAlign(12);
        int theSqrts=13;
        TString cErgTev = Form("%i TeV", theSqrts);
        text = pt.AddText(0.999, 0.45, cErgTev);
        text->SetTextFont(43);
        text->SetTextSize(npixels_CMSlogo*relsize_CMSlogo_sqrts);
        text->SetTextAlign(32);

        canvas.cd();
        legend.Draw();
        pt.Draw();
        ptc.Draw();

        canvas.RedrawAxis();
        canvas.Modified();
        canvas.Update();
        canvas.SaveAs(TString(canvas.GetName()) + ".pdf");
        canvas.SaveAs(TString(canvas.GetName()) + ".png");

        canvas.Close();
      }
    }

    facceff->Close();
  }
}
