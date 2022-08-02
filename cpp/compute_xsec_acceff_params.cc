#include <cassert>
#include <thread>
#include <functional>

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
#include "TH1D.h"
#include "TH2D.h"


using namespace std;
using namespace IvyStreamHelpers;


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
/*

void parallel_for(std::vector<TString> const& samples, TString const& period, TString const& production_dir,
                  std::function<void(int, int, std::vector<TString> const&, TString const&, TString const&)> functor,
                  bool use_threads)
{
  unsigned nb_elements = samples.size();
  // -------
  unsigned nb_threads_hint = std::thread::hardware_concurrency();
  unsigned nb_threads = nb_threads_hint == 0 ? 8 : (nb_threads_hint);

  unsigned batch_size = nb_elements / nb_threads;
  unsigned batch_remainder = nb_elements % nb_threads;

  std::vector< std::thread > my_threads(nb_threads);

  if (use_threads){
    // Multithread execution
    for (unsigned i = 0; i < nb_threads; ++i){
      int start = i * batch_size;
      my_threads[i] = std::thread(functor, start, start+batch_size, samples, period, production_dir);
    }
  }
  else{
    // Single thread execution (for easy debugging)
    for (unsigned i = 0; i < nb_threads; ++i){
      int start = i * batch_size;
      functor(start, start+batch_size, samples, period, production_dir);
    }
  }

  // Deform the elements left
  int start = nb_threads * batch_size;
  functor(start, start+batch_remainder, samples, period, production_dir);

  // Wait for the other thread to finish their task
  if (use_threads) std::for_each(my_threads.begin(), my_threads.end(), std::mem_fn(&std::thread::join));
}

void compute_perparton_xsec(){
  BaseTree::setRobustInputCheck(false);

  TString const production_dir = "/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404";
  TString const period = "RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_private";
  auto const samples = SampleHelpers::lsdir(production_dir.Data());
  parallel_for(
    samples,
    period,
    production_dir,
    [&](int start, int end, std::vector<TString> const& ss, TString const& pp, TString const& pd){ for (int i = start; i < end; ++i) compute_single_proc(ss.at(i), pp, pd); },
    false
  );
}
*/


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

void parametrize_xsec(TString const& cinput, bool useModelAveraged=true){
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
      else if (cl==Form("xsec_ss%s", (useFinalXS ? "_ModelAveraged" : ""))) xsec_ss = std::stod(csvreader[cl].at(irow));
      else if (cl==Form("xsec_sb%s", (useFinalXS ? "_ModelAveraged" : ""))) xsec_sb = std::stod(csvreader[cl].at(irow));
      else if (cl==Form("xsec_bb%s", (useFinalXS ? "_ModelAveraged" : ""))) xsec_bb = std::stod(csvreader[cl].at(irow));
    }

    if (!HelperFunctions::checkListVariable(hypos, strhypo)) hypos.push_back(strhypo);
    if (hypo_mass_xsec_ss_pairs_map.find(strhypo)==hypo_mass_xsec_ss_pairs_map.end()) hypo_mass_xsec_ss_pairs_map[strhypo] = std::vector<std::pair<double, double>>();
    if (hypo_mass_xsec_sb_pairs_map.find(strhypo)==hypo_mass_xsec_sb_pairs_map.end()) hypo_mass_xsec_sb_pairs_map[strhypo] = std::vector<std::pair<double, double>>();
    if (hypo_mass_xsec_bb_pairs_map.find(strhypo)==hypo_mass_xsec_bb_pairs_map.end()) hypo_mass_xsec_bb_pairs_map[strhypo] = std::vector<std::pair<double, double>>();

    if (xsec_ss>1e-4) HelperFunctions::addByLowest(hypo_mass_xsec_ss_pairs_map[strhypo], mass, std::log(xsec_ss));
    HelperFunctions::addByLowest(hypo_mass_xsec_sb_pairs_map[strhypo], mass, std::log(xsec_sb));
    HelperFunctions::addByLowest(hypo_mass_xsec_bb_pairs_map[strhypo], mass, std::log(xsec_bb));
  }

  TFile* foutput = TFile::Open(Form("xsec_interpolation%s.root", (useFinalXS ? "_final" : "")), "recreate");
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

void parametrize_acceff(TString period, TString cinput_xs, TString cinput_yields){
  TDirectory* curdir = gDirectory;

  std::string cinput_xsec = "${CMSSW_BASE}/src/ZPrimeSnT/data/xsec_interpolation_ZPrimeToMuMuSB_bestfit_13TeV_Allanach.root";
  HostHelpers::ExpandEnvironmentVariables(cinput_xsec);
  std::vector<std::string> const states{ "ss", "sb", "bb" };

  double lumi=-1;
  if (period=="2016_APV") lumi=19.5;
  else if (period=="2016_NonAPV") lumi=16.8;
  else if (period=="2017") lumi=41.48;
  else if (period=="2018") lumi=59.83;
  else if (period=="Run2") lumi=19.5+16.8+41.48+59.83;
  else assert(0);

  std::unordered_map<std::string, std::vector<std::pair<double, double>> > hypo_mass_yield_pairs_map[3][2];
  std::unordered_map<std::string, std::vector<std::pair<double, double>> > hypo_mass_count_pairs_map[3][2];

  std::unordered_map<std::string, std::vector<std::string>> csventries;

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
    // Input xsecs should ALWAYS be what is in the looper, not what is 'model-averaged'.
    input_xseclist.push_back(std::stod(csv_xs["xsec_ss"].at(irow)));
    input_xseclist.push_back(std::stod(csv_xs["xsec_sb"].at(irow)));
    input_xseclist.push_back(std::stod(csv_xs["xsec_bb"].at(irow)));
  }

  std::vector<std::string> hypos;
  for (unsigned int irow=0; irow<nrows_yields; irow++){
    std::string strhypo;
    int mass=0;
    double yield[3][2]={ { 0 } };
    double count[3][2]={ { 0 } };
    for (auto const& lb:labels_yields){
      if (lb=="model") strhypo = csv_yields[lb].at(irow);
      else if (lb=="M") mass = std::stoi(csv_yields[lb].at(irow));
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
    for (unsigned int is=0; is<3; is++){ // ss, sb, bb
      for (unsigned char ic=0; ic<2; ic++){ // Category
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
  for (unsigned char is=0; is<states.size(); is++){
    auto const& state = states.at(is);
    for (unsigned char ic=0; ic<2; ic++){
      TGraph* gr_tmp = nullptr;
      TSpline3* sp_tmp = nullptr;

      std::vector<double> masses_all;

      for (auto const& strhypo:hypos){
        sp_tmp = HelperFunctions::convertPointsToSpline3(hypo_mass_yield_pairs_map[is][ic][strhypo], false, true);
        if (sp_tmp){
          sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", strhypo.data(), state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
          foutput->WriteTObject(sp_tmp); delete sp_tmp;
          gr_tmp = HelperFunctions::makeGraphFromPair(hypo_mass_yield_pairs_map[is][ic][strhypo], Form("gr_%s_acceff_%s_%s_%s", strhypo.data(), state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
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
          auto const& count = hypo_mass_count_pairs_map[is][ic][strhypo].at(ip).second;

          double val_dn=val, val_up=val;
          StatisticsHelpers::getPoissonCountingConfidenceInterval_Frequentist(count, 0.95, val_dn, val_up); val_dn *= val/count; val_up *= val/count;

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
        IVYerr << "No masses exist in " << state << " " << (ic==0 ? "Nb=1" : "Nb>1") << "." << endl;
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

      sp_tmp = HelperFunctions::convertPointsToSpline3(mass_acceff_pairs_allhypos_nominal, false, true);
      if (sp_tmp){
        sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", "avg", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(sp_tmp); delete sp_tmp;
        gr_tmp = HelperFunctions::makeGraphFromPair(mass_acceff_pairs_allhypos_nominal, Form("gr_%s_acceff_%s_%s_%s", "avg", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(gr_tmp); delete gr_tmp;
      }

      sp_tmp = HelperFunctions::convertPointsToSpline3(mass_acceff_pairs_allhypos_errdn, false, true);
      if (sp_tmp){
        sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", "avg_errsq_dn", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(sp_tmp); delete sp_tmp;
        gr_tmp = HelperFunctions::makeGraphFromPair(mass_acceff_pairs_allhypos_errdn, Form("gr_%s_acceff_%s_%s_%s", "avg_errsq_dn", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(gr_tmp); delete gr_tmp;
      }

      sp_tmp = HelperFunctions::convertPointsToSpline3(mass_acceff_pairs_allhypos_errup, false, true);
      if (sp_tmp){
        sp_tmp->SetName(Form("spline_%s_acceff_%s_%s_%s", "avg_errsq_up", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(sp_tmp); delete sp_tmp;
        gr_tmp = HelperFunctions::makeGraphFromPair(mass_acceff_pairs_allhypos_errup, Form("gr_%s_acceff_%s_%s_%s", "avg_errsq_up", state.data(), (ic==0 ? "Nb_eq_1" : "Nb_geq_2"), period.Data()));
        foutput->WriteTObject(gr_tmp); delete gr_tmp;
      }
    }
  }
  foutput->Close();
}
