#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TLorentzVector.h"
#include "math.h"
#include "TVector2.h"
#include "TVector3.h"

#include "../NanoCORE/Nano.h"
#include "../NanoCORE/Base.h"
#include "../NanoCORE/tqdm.h"
#include "../NanoCORE/ZPrimeTools.cc"
#include "../NanoCORE/XYMETCorrection_withUL17andUL18andUL16.h"
#include "../NanoCORE/Tools/goodrun.h"
#include "../NanoCORE/Tools/dorky.h"
#include "../NanoCORE/Tools/puWeight.h"
#include "../NanoCORE/Tools/muonRecoSF.h"
#include "../NanoCORE/Tools/muonIDSF.h"
#include "../NanoCORE/Tools/muonIsoSF.h"
#include "../NanoCORE/Tools/muonTriggerSF.h"
#include "../NanoCORE/Tools/bTagEff.h"
#include "../NanoCORE/Tools/btagsf/BTagCalibrationStandalone_v2.h"

#include <iostream>
#include <iomanip>
#include <sys/stat.h>

#define SUM(vec) std::accumulate((vec).begin(), (vec).end(), 0);
#define SUM_GT(vec,num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x,float y) { return ((y > (num)) ? x+y : x); });
#define COUNT_GT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name,nbins,low,high,xtitle) TH1F *h_##name = new TH1F(#name,"",nbins,low,high); h_##name->GetXaxis()->SetTitle(xtitle); h_##name->GetYaxis()->SetTitle("Events");
#define HTemp(name,nbins,low,high,xtitle) TH1F *h_temp = new TH1F(name,"",nbins,low,high); h_temp->GetXaxis()->SetTitle(xtitle); h_temp->GetYaxis()->SetTitle("Events");

// #define DEBUG
#define Zmass 91.1876

// For testing purposes only
bool useOnlyRun2018B = true;

// Looper setup flags
bool muonDebug = false;
bool doMllBins = false;
bool doNbTagBins = true;
bool doTTEnriched = true;
bool doDYEnriched = false;
bool doMuDetRegionBins = true;

// General flags
bool removeSpikes = true;
bool removeDataDuplicates = false;
bool useTuneP = true;
bool usePuppiMET = false;
//
// Event weights / scale factors
bool applyTopPtWeight = true;

bool applyPUWeight = true;
bool varyPUWeightUp = false;
bool varyPUWeightDown = false;

bool applyMuonSF = true;
bool varyMuonSFUp = false;
bool varyMuonSFDown = false;

bool applyTriggerSF = true;
bool varyTriggerSFUp = false;
bool varyTriggerSFDown = false;

bool applyBTagSF = true;
bool varyBTagSFUp = false;
bool varyBTagSFDown = false;
//
// HEM15/16 veto
bool doHEMveto = false;
float HEM_region[4] = {-3.2, -1.3, -1.57, -0.87}; // etalow, etahigh, philow, phihigh
unsigned int HEM_startRun = 319077; // affects 38.75 out of 59.83 fb-1 in 2018
unsigned int HEM_fracNum = 1205, HEM_fracDen = 1860; // 38.75/59.83 = 0.648 ~= 1205/1860. Used for figuring out if we should veto MC events
bool useHEMjets      = true;
float HEM_jetPtCut = 20.0;  // veto on jets above this threshold
bool useHEMmuons     = true;
bool useHEMelectrons = true;
float HEM_lepPtCut = 10.0;  // veto on leptons above this threshold
bool useHEMisotracks = false;
float HEM_trkPtCut = 10.0;  // veto on iso-tracks above this threshold
//

const char* outdir = "temp_data";
int mdir = mkdir(outdir,0755);

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
#define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
#define debug(args...)
#endif

using namespace std;
using namespace tas;
using namespace duplicate_removal;

int ScanChain(TChain *ch, double genEventSumw, TString year, TString process) {

  float factor = 1.0;
  float lumi = 1.0;
  float xsec = 1.0;
  bool isMC = true;

  if ( process.Contains("data") ) {
    isMC = false;
  }
  // SM processes and cross-sections:
  else if ( process == "ttbar" )             xsec = 87310.0; // fb
  else if ( process == "DY" )                xsec = 5765400.0; // fb
  else if ( process == "ZToMuMu_50_120" )    xsec = 2112904.0; // fb
  else if ( process == "ZToMuMu_120_200" )   xsec = 20553.0; // fb
  else if ( process == "ZToMuMu_200_400" )   xsec = 2886.0; // fb
  else if ( process == "ZToMuMu_400_800" )   xsec = 251.7; // fb
  else if ( process == "ZToMuMu_800_1400" )  xsec = 17.07; // fb
  else if ( process == "ZToMuMu_1400_2300" ) xsec = 1.366; // fb
  else if ( process == "ZToMuMu_2300_3500" ) xsec = 0.08178; // fb
  else if ( process == "ZToMuMu_3500_4500" ) xsec = 0.003191; // fb
  else if ( process == "ZToMuMu_4500_6000" ) xsec = 0.0002787; // fb
  else if ( process == "ZToMuMu_6000_Inf" )  xsec = 0.000009569; // fb
  else if ( process == "WW" )                xsec = 118700.0; // fb 
  else if ( process == "WZ" )                xsec = 47130.0; // fb
  else if ( process == "ZZ" )                xsec = 16523.0; // fb
  else if ( process == "tW" )                xsec = 19550; // fb
  else if ( process == "tbarW" )             xsec = 19550; // fb
  else if ( process == "tZq" )               xsec = 75.8; // fb
  else if ( process == "TTW" )               xsec = 204.3; // fb
  else if ( process == "TTZ" )               xsec = 252.9; // fb
  else if ( process == "TTHToNonbb" )        xsec = 507.5*(1-0.575); // fb
  else if ( process == "TTHTobb" )           xsec = 507.5*0.575; // fb
  // Signal processes and cross-sections:
  else if ( process == "Y3_M100"  )    xsec = 0.0211372800*1000;
  else if ( process == "Y3_M200"  )    xsec = 0.0159797150*1000;
  else if ( process == "Y3_M400"  )    xsec = 0.0029093405*1000;
  else if ( process == "Y3_M700"  )    xsec = 0.0006143530*1000;
  else if ( process == "Y3_M1000" )    xsec = 0.0001919544*1000;
  else if ( process == "Y3_M1500" )    xsec = 0.0000363696*1000;
  else if ( process == "Y3_M2000" )    xsec = 0.0000082510*1000;

  else if ( process == "DY3_M100"  )   xsec = 0.0337049425*1000;
  else if ( process == "DY3_M200"  )   xsec = 0.0127905600*1000;
  else if ( process == "DY3_M400"  )   xsec = 0.0038605973*1000;
  else if ( process == "DY3_M700"  )   xsec = 0.0009411330*1000;
  else if ( process == "DY3_M1000" )   xsec = 0.0003003987*1000;
  else if ( process == "DY3_M1500" )   xsec = 0.0000595791*1000;
  else if ( process == "DY3_M2000" )   xsec = 0.0000154994*1000;

  else if ( process == "DYp3_M100"  )  xsec = 0.0313425200*1000;
  else if ( process == "DYp3_M200"  )  xsec = 0.0091705403*1000;
  else if ( process == "DYp3_M400"  )  xsec = 0.0025317413*1000;
  else if ( process == "DYp3_M700"  )  xsec = 0.0006051238*1000;
  else if ( process == "DYp3_M1000" )  xsec = 0.0001939990*1000;
  else if ( process == "DYp3_M1500" )  xsec = 0.0000367774*1000;
  else if ( process == "DYp3_M2000" )  xsec = 0.0000082788*1000;

  else if ( process == "B3mL2_M100"  ) xsec = 0.2895163696*1000;
  else if ( process == "B3mL2_M200"  ) xsec = 0.1236243250*1000;
  else if ( process == "B3mL2_M400"  ) xsec = 0.0307822425*1000;
  else if ( process == "B3mL2_M700"  ) xsec = 0.0071884160*1000;
  else if ( process == "B3mL2_M1000" ) xsec = 0.0022984062*1000;
  else if ( process == "B3mL2_M1500" ) xsec = 0.0004383351*1000;
  else if ( process == "B3mL2_M2000" ) xsec = 0.0001029249*1000;
  else
  {
    cout<<"Non-valid process: Exiting!"<<endl;
    return 1;
  }

  if ( year == "2018" )       lumi = 59.83; // fb-1
  if ( year == "2017" )       lumi = 41.48; // fb-1
  if ( year == "2016APV" )    lumi = 19.5;  // fb-1
  if ( year == "2016nonAPV" ) lumi = 16.8;  // fb-1

  gconf.nanoAOD_ver = 9;
  gconf.GetConfigs(year.Atoi());

  if ( !isMC ) {
    if ( year == "2016APV" )
      set_goodrun_file_json("../utils/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt");
    if ( year == "2016nonAPV" )
      set_goodrun_file_json("../utils/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt");
    if ( year == "2017" )
      set_goodrun_file_json("../utils/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt");
    if ( year == "2018" )
      set_goodrun_file_json("../utils/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt");
  }

  if ( isMC )
    factor = xsec*lumi/genEventSumw;

  // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
  TFile* fout = new TFile("temp_data/output_"+process+"_"+year+".root", "RECREATE");

  H1(cutflow,20,0,20,"");

  // Define histo info maps
  map<TString, int> nbins { };
  map<TString, float> low { };
  map<TString, float> high { };
  map<TString, TString> title { };

  // Define histos
  nbins.insert({"pfmet_pt", 120});
  low.insert({"pfmet_pt", 5});
  high.insert({"pfmet_pt", 605});
  title.insert({"pfmet_pt", "PF MET [GeV]"});

  nbins.insert({"pfmet_phi", 65});
  low.insert({"pfmet_phi", -3.25});
  high.insert({"pfmet_phi", 3.25});
  title.insert({"pfmet_phi", "PF MET #phi [GeV]"});

  nbins.insert({"puppimet_pt", 120});
  low.insert({"puppimet_pt", 5});
  high.insert({"puppimet_pt", 605});
  title.insert({"puppimet_pt", "PUPPI MET [GeV]"});

  nbins.insert({"puppimet_phi", 65});
  low.insert({"puppimet_phi", -3.25});
  high.insert({"puppimet_phi", 3.25});
  title.insert({"puppimet_phi", "PUPPI MET #phi [GeV]"});

  nbins.insert({"mmumu", 480});
  low.insert({"mmumu", 100});
  high.insert({"mmumu", 2500});
  title.insert({"mmumu", "m_{#mu#mu} [GeV]"});

  nbins.insert({"mu1_pt", 200});
  low.insert({"mu1_pt", 10});
  high.insert({"mu1_pt", 1010});
  title.insert({"mu1_pt", "p_{T} (leading #mu) [GeV]"});

  nbins.insert({"mu2_pt", 200});
  low.insert({"mu2_pt", 10});
  high.insert({"mu2_pt", 1010});
  title.insert({"mu2_pt", "p_{T} (subleading #mu) [GeV]"});

  nbins.insert({"mu1_eta", 60});
  low.insert({"mu1_eta", -3});
  high.insert({"mu1_eta", 3});
  title.insert({"mu1_eta", "#eta (leading #mu)"});

  nbins.insert({"mu2_eta", 60});
  low.insert({"mu2_eta", -3});
  high.insert({"mu2_eta", 3});
  title.insert({"mu2_eta", "#eta (subleading #mu)"});

  nbins.insert({"mu1_phi", 64});
  low.insert({"mu1_phi", -3.2});
  high.insert({"mu1_phi", 3.2});
  title.insert({"mu1_phi", "#phi (leading #mu)"});

  nbins.insert({"mu2_phi", 64});
  low.insert({"mu2_phi", -3.2});
  high.insert({"mu2_phi", 3.2});
  title.insert({"mu2_phi", "#phi (subleading #mu)"});

  nbins.insert({"dPhi_ll", 32});
  low.insert({"dPhi_ll",  0});
  high.insert({"dPhi_ll", 3.2});
  title.insert({"dPhi_ll", "|#Delta#phi(#mu,#mu)|"});

  nbins.insert({"dEta_ll", 50});
  low.insert({"dEta_ll",  0});
  high.insert({"dEta_ll", 5.0});
  title.insert({"dEta_ll", "|#Delta#eta(#mu,#mu)|"});

  nbins.insert({"dEta_dPhi_ratio_ll", 50});
  low.insert({"dEta_dPhi_ratio_ll", -5.0});
  high.insert({"dEta_dPhi_ratio_ll", 5.0});
  title.insert({"dEta_dPhi_ratio_ll", "log_{10} |#Delta#eta(#mu,#mu)/#Delta#phi(#mu,#mu)|"});

  nbins.insert({"mu1_dxy", 100});
  low.insert({"mu1_dxy", 0.01});
  high.insert({"mu1_dxy", 1.01});
  title.insert({"mu1_dxy", "d_{xy} (leading #mu)"});

  nbins.insert({"mu2_dxy", 100});
  low.insert({"mu2_dxy", 0.01});
  high.insert({"mu2_dxy", 1.01});
  title.insert({"mu2_dxy", "d_{xy} (subleading #mu)"});

  nbins.insert({"mu1_dz", 100});
  low.insert({"mu1_dz", 0.01});
  high.insert({"mu1_dz", 1.01});
  title.insert({"mu1_dz", "d_{z} (leading #mu)"});

  nbins.insert({"mu2_dz", 100});
  low.insert({"mu2_dz", 0.01});
  high.insert({"mu2_dz", 1.01});
  title.insert({"mu2_dz", "d_{z} (subleading #mu)"});

  nbins.insert({"mu1_trkRelIso", 50});
  low.insert({"mu1_trkRelIso", 0.01});
  high.insert({"mu1_trkRelIso", 0.51});
  title.insert({"mu1_trkRelIso", "Track iso./p_{T} (leading #mu)"});

  nbins.insert({"mu2_trkRelIso", 50});
  low.insert({"mu2_trkRelIso", 0.01});
  high.insert({"mu2_trkRelIso", 0.51});
  title.insert({"mu2_trkRelIso", "Track iso./p_{T} (subleading #mu)"});

  nbins.insert({"nCand_Muons", 4});
  low.insert({"nCand_Muons", 2});
  high.insert({"nCand_Muons", 6});
  title.insert({"nCand_Muons", "Number of #mu candidates"});

  nbins.insert({"nExtra_muons", 6});
  low.insert({"nExtra_muons", 0});
  high.insert({"nExtra_muons", 6});
  title.insert({"nExtra_muons", "Number of additional #mu's"});

  nbins.insert({"mu3_pt", 200});
  low.insert({"mu3_pt", 5});
  high.insert({"mu3_pt", 1005});
  title.insert({"mu3_pt", "p_{T} (third #mu) [GeV]"});

  nbins.insert({"mu3_eta", 60});
  low.insert({"mu3_eta", -3});
  high.insert({"mu3_eta", 3});
  title.insert({"mu3_eta", "#eta (third #mu)"});

  nbins.insert({"mu3_trkRelIso", 50});
  low.insert({"mu3_trkRelIso", 0.01});
  high.insert({"mu3_trkRelIso", 0.51});
  title.insert({"mu3_trkRelIso", "Track iso./p_{T} (third #mu)"});

  nbins.insert({"nExtra_electrons", 6});
  low.insert({"nExtra_electrons", 0});
  high.insert({"nExtra_electrons", 6});
  title.insert({"nExtra_electrons", "Number of electrons"});

  nbins.insert({"ele_extra_pt", 200});
  low.insert({"ele_extra_pt", 5});
  high.insert({"ele_extra_pt", 1005});
  title.insert({"ele_extra_pt", "p_{T} (extra electron) [GeV]"});

  nbins.insert({"ele_extra_eta", 60});
  low.insert({"ele_extra_eta", -3});
  high.insert({"ele_extra_eta", 3});
  title.insert({"ele_extra_eta", "#eta (extra electron)"});

  nbins.insert({"ele_extra_miniPFRelIso", 50});
  low.insert({"ele_extra_miniPFRelIso", 0.01});
  high.insert({"ele_extra_miniPFRelIso", 0.51});
  title.insert({"ele_extra_miniPFRelIso", "PF mini-iso./p_{T} (extra electron)"});

  nbins.insert({"nExtra_lepIsoTracks", 6});
  low.insert({"nExtra_lepIsoTracks", 0});
  high.insert({"nExtra_lepIsoTracks", 6});
  title.insert({"nExtra_lepIsoTracks", "Number of (additional) lepton (e/#mu) PF candidates"});

  nbins.insert({"lepIsoTrack_extra_pt", 200});
  low.insert({"lepIsoTrack_extra_pt", 5});
  high.insert({"lepIsoTrack_extra_pt", 1005});
  title.insert({"lepIsoTrack_extra_pt", "p_{T} (extra lepton isoTrack) [GeV]"});

  nbins.insert({"lepIsoTrack_extra_eta", 60});
  low.insert({"lepIsoTrack_extra_eta", -3});
  high.insert({"lepIsoTrack_extra_eta", 3});
  title.insert({"lepIsoTrack_extra_eta", "#eta (extra lepton isoTrack)"});

  nbins.insert({"lepIsoTrack_extra_PFRelIsoChg", 50});
  low.insert({"lepIsoTrack_extra_PFRelIsoChg", 0.01});
  high.insert({"lepIsoTrack_extra_PFRelIsoChg", 0.51});
  title.insert({"lepIsoTrack_extra_PFRelIsoChg", "PF charged iso./p_{T} (extra lepton isoTrack)"});

  nbins.insert({"nExtra_chhIsoTracks", 6});
  low.insert({"nExtra_chhIsoTracks", 0});
  high.insert({"nExtra_chhIsoTracks", 6});
  title.insert({"nExtra_chhIsoTracks", "Number of (additional) charged hadron PF candidates"});

  nbins.insert({"chhIsoTrack_extra_pt", 200});
  low.insert({"chhIsoTrack_extra_pt", 5});
  high.insert({"chhIsoTrack_extra_pt", 1005});
  title.insert({"chhIsoTrack_extra_pt", "p_{T} (extra ch. hadron isoTrack) [GeV]"});

  nbins.insert({"chhIsoTrack_extra_eta", 60});
  low.insert({"chhIsoTrack_extra_eta", -3});
  high.insert({"chhIsoTrack_extra_eta", 3});
  title.insert({"chhIsoTrack_extra_eta", "#eta (extra ch. hadron isoTrack)"});

  nbins.insert({"chhIsoTrack_extra_PFRelIsoChg", 50});
  low.insert({"chhIsoTrack_extra_PFRelIsoChg", 0.01});
  high.insert({"chhIsoTrack_extra_PFRelIsoChg", 0.51});
  title.insert({"chhIsoTrack_extra_PFRelIsoChg", "PF charged iso./p_{T} (extra ch. hadron isoTrack)"});

  nbins.insert({"nbtagDeepFlavB", 5});
  low.insert({"nbtagDeepFlavB", 0});
  high.insert({"nbtagDeepFlavB", 5});
  title.insert({"nbtagDeepFlavB", "Number of b-tags (medium WP)"});

  nbins.insert({"bjet1_pt", 300});
  low.insert({"bjet1_pt", 20});
  high.insert({"bjet1_pt", 1520});
  title.insert({"bjet1_pt", "p_{T} (leading b-tagged jet) [GeV]"});

  nbins.insert({"bjet1_eta", 60});
  low.insert({"bjet1_eta", -3});
  high.insert({"bjet1_eta", 3});
  title.insert({"bjet1_eta", "#eta (leading b-tagged jet) [GeV]"});

  nbins.insert({"bjet2_pt", 300});
  low.insert({"bjet2_pt", 20});
  high.insert({"bjet2_pt", 1520});
  title.insert({"bjet2_pt", "p_{T} (subleading b-tagged jet) [GeV]"});

  nbins.insert({"bjet2_eta", 60});
  low.insert({"bjet2_eta", -3});
  high.insert({"bjet2_eta", 3});
  title.insert({"bjet2_eta", "#eta (subleading b-tagged jet) [GeV]"});

  nbins.insert({"min_mlb", 300});
  low.insert({"min_mlb", 0.1});
  high.insert({"min_mlb", 1500.1});
  title.insert({"min_mlb", "min m_{#mu b} [GeV]"});

  nbins.insert({"min_mbb", 300});
  low.insert({"min_mbb", 0.1});
  high.insert({"min_mbb", 1500.1});
  title.insert({"min_mbb", "min m_{bb} [GeV]"});

  nbins.insert({"max_mbb", 300});
  low.insert({"max_mbb", 0.1});
  high.insert({"max_mbb", 1500.1});
  title.insert({"max_mbb", "max m_{bb} [GeV]"});

  nbins.insert({"minDPhi_b_MET", 32});
  low.insert({"minDPhi_b_MET", 0});
  high.insert({"minDPhi_b_MET", 3.2});
  title.insert({"minDPhi_b_MET", "min #Delta#phi(b,MET)"});

  nbins.insert({"minDPhi_lb_MET", 32});
  low.insert({"minDPhi_lb_MET", 0});
  high.insert({"minDPhi_lb_MET", 3.2});
  title.insert({"minDPhi_lb_MET", "min #Delta#phi(#mu b,MET)"});

  nbins.insert({"minDPhi_llb_MET", 32});
  low.insert({"minDPhi_llb_MET", 0});
  high.insert({"minDPhi_llb_MET", 3.2});
  title.insert({"minDPhi_llb_MET", "min #Delta#phi(#mu#mu b,MET)"});

  nbins.insert({"minDPhi_l_MET", 32});
  low.insert({"minDPhi_l_MET", 0});
  high.insert({"minDPhi_l_MET", 3.2});
  title.insert({"minDPhi_l_MET", "min #Delta#phi(#mu,MET)"});

  nbins.insert({"minDPhi_l_b", 32});
  low.insert({"minDPhi_l_b", 0});
  high.insert({"minDPhi_l_b", 3.2});
  title.insert({"minDPhi_l_b", "min #Delta#phi(#mu, b)"});

  nbins.insert({"dPhi_ll_MET", 32});
  low.insert({"dPhi_ll_MET", 0});
  high.insert({"dPhi_ll_MET", 3.2});
  title.insert({"dPhi_ll_MET", "|#Delta#phi(#mu#mu,MET)|"});

  // Define (overlapping) mll bins
  vector<TString> mllbin = { };
  mllbin.push_back("mllinclusive");
  if ( doMllBins ) {
    mllbin.push_back("mll150to250");
    mllbin.push_back("mll200to600");
    mllbin.push_back("mll500to900");
    mllbin.push_back("mll700to1300");
    mllbin.push_back("mll1100to1900");
    mllbin.push_back("mll1500to2500");
  }
  const int nMllBins = mllbin.size();
  bool mllbinsel[nMllBins];

  map<TString, TString> mllbinlabel;
  mllbinlabel["mllinclusive"]="m_{#mu#mu} > 0 GeV";
  mllbinlabel["mll150to250"]="150 < m_{#mu#mu} < 250 GeV";
  mllbinlabel["mll200to600"]="200 < m_{#mu#mu} < 600 GeV";
  mllbinlabel["mll500to900"]="500 < m_{#mu#mu} < 900 GeV";
  mllbinlabel["mll700to1300"]="700 <m_{#mu#mu} < 1300 GeV";
  mllbinlabel["mll1100to1900"]="1.1 < m_{#mu#mu} < 1.9 TeV";
  mllbinlabel["mll1500to2500"]="1.5 < m_{#mu#mu} < 2.5 TeV";

  // Define number of b-tag bins
  vector<TString> nbtag = { };
  nbtag.push_back("nBTag1p");
  if ( doNbTagBins ) {
    if (doDYEnriched) nbtag.push_back("nBTag0");
    nbtag.push_back("nBTag1");
    nbtag.push_back("nBTag2p");
  }
  const int nBTagBins = nbtag.size();
  bool nbtagsel[nBTagBins];

  map<TString, TString> nbtagbinlabel;
  nbtagbinlabel["nBTag1p"]="N_{b-tag}#geq 1 (p_{T}>20 GeV, medium WP)";
  if (doDYEnriched) nbtagbinlabel["nBTag0"] = "N_{b-tag}= 0 (p_{T}>20 GeV, medium WP)";
  nbtagbinlabel["nBTag1"]="N_{b-tag}= 1 (p_{T}>20 GeV, medium WP)";
  nbtagbinlabel["nBTag2p"]="N_{b-tag}#geq 2 (p_{T}>20 GeV, medium WP)";

  // Define muon detector region bins
   vector<TString> MuDetRegion = {};
   MuDetRegion.push_back("MuDetAll");
   if (doMuDetRegionBins)
   {
     MuDetRegion.push_back("BB");
     MuDetRegion.push_back("BE");
     MuDetRegion.push_back("EE");
   }
   const int MuDetRegionBins = MuDetRegion.size();
   bool MuDetRegionsel[MuDetRegionBins];

   map<TString, TString> MuDetRegionbinlabel;
   MuDetRegionbinlabel["BB"] = "2 muons in Barrel";
   MuDetRegionbinlabel["BE"] = "1 muon in Barrel, 1 muon in Endcap)";
   MuDetRegionbinlabel["EE"] = "2 muons in Endcap";

  // Define cutflow histograms in bins of mll and number of b-tags
  map<TString, TH1F*> slicedcutflows;
  for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
    for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
      for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++){
        TString plot_name = TString("cutflow_") + mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
        TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
        HTemp(plot_name,20,0,20,"");
        slicedcutflows[slice] = h_temp;
      }
    }
  }

  // Define selection
  vector<TString> selection = { };
  selection.push_back("sel0"); // Skimming + HLT + Good PV
  selection.push_back("sel1"); // 2 high-pT ID muons
  selection.push_back("sel2"); // pT > 53 GeV && |eta| < 2.4 muons
  selection.push_back("sel3"); // Relative track isolation < 0.1
  selection.push_back("sel4"); // Selected muon matched to HLT > 1 (DeltaR < 0.02)
  selection.push_back("sel5"); // At least one OS dimuon pair, not from Z
  selection.push_back("sel6"); // Mmumu > 150 GeV
  selection.push_back("sel7"); // No extra lepton / isoTrack
  selection.push_back("sel8"); // NbTag >= 1 (medium WP)
  selection.push_back("sel9"); // minMlb > 175 GeV
  if (doTTEnriched) selection.push_back("antisel9"); // minMlb < 175 GeV, used for ttbar bkg reduction

  vector<TString> plot_names = { };
  vector<TString> plot_names_b = { };
  vector<TString> plot_names_2b = { };
  plot_names.push_back("pfmet_pt");
  plot_names.push_back("pfmet_phi");
  plot_names.push_back("puppimet_pt");
  plot_names.push_back("puppimet_phi");
  if ( muonDebug ) {
    plot_names.push_back("mu1_pt");
    plot_names.push_back("mu2_pt");
    plot_names.push_back("mu1_eta");
    plot_names.push_back("mu2_eta");
    plot_names.push_back("mu1_phi");
    plot_names.push_back("mu2_phi");
    plot_names.push_back("mu1_dxy");
    plot_names.push_back("mu2_dxy");
    plot_names.push_back("mu1_dz");
    plot_names.push_back("mu2_dz");
    plot_names.push_back("mu1_trkRelIso");
    plot_names.push_back("mu2_trkRelIso");
    plot_names.push_back("nCand_Muons");
  }
  map<TString, TH1F*> histos;
  int nExtraHistos = 0;
  for ( unsigned int isel=0; isel < selection.size(); isel++ ) {
    if (isel==5) {
      plot_names.push_back("mmumu");
      if ( !muonDebug ) {
        plot_names.push_back("mu1_pt");
        plot_names.push_back("mu2_pt");
        plot_names.push_back("mu1_eta");
        plot_names.push_back("mu2_eta");
        plot_names.push_back("mu1_phi");
        plot_names.push_back("mu2_phi");
        plot_names.push_back("mu1_dxy");
        plot_names.push_back("mu2_dxy");
        plot_names.push_back("mu1_dz");
        plot_names.push_back("mu2_dz");
        plot_names.push_back("mu1_trkRelIso");
        plot_names.push_back("mu2_trkRelIso");
        plot_names.push_back("nCand_Muons");
      }
      plot_names.push_back("dPhi_ll");
      plot_names.push_back("dEta_ll");
      plot_names.push_back("dEta_dPhi_ratio_ll");
      plot_names.push_back("dPhi_ll_MET");
      plot_names.push_back("minDPhi_l_MET");
    }
      // Add also extra plots before third lepton/isotrack veto
    if (isel==6) {
      plot_names.push_back("nExtra_muons"); ++nExtraHistos;
      plot_names.push_back("nExtra_electrons"); ++nExtraHistos;
      plot_names.push_back("nExtra_lepIsoTracks"); ++nExtraHistos;
      plot_names.push_back("nExtra_chhIsoTracks"); ++nExtraHistos;
      plot_names.push_back("mu3_pt"); ++nExtraHistos;
      plot_names.push_back("mu3_eta"); ++nExtraHistos;
      plot_names.push_back("mu3_trkRelIso"); ++nExtraHistos;
      plot_names.push_back("ele_extra_pt"); ++nExtraHistos;
      plot_names.push_back("ele_extra_eta"); ++nExtraHistos;
      plot_names.push_back("ele_extra_miniPFRelIso"); ++nExtraHistos;
      plot_names.push_back("lepIsoTrack_extra_pt"); ++nExtraHistos;
      plot_names.push_back("lepIsoTrack_extra_eta"); ++nExtraHistos;
      plot_names.push_back("lepIsoTrack_extra_PFRelIsoChg"); ++nExtraHistos;
      plot_names.push_back("chhIsoTrack_extra_pt"); ++nExtraHistos;
      plot_names.push_back("chhIsoTrack_extra_eta"); ++nExtraHistos;
      plot_names.push_back("chhIsoTrack_extra_PFRelIsoChg"); ++nExtraHistos;
    }

    // Third lepton/isotrack veto
    if (isel==7) {
      // Remove plots added for thid lepton/isotrack veto
      for (int e=0; e<nExtraHistos; ++e)
	plot_names.pop_back();
    }
    if (isel==8) {
      plot_names.push_back("nbtagDeepFlavB");
      plot_names.push_back("bjet1_pt");
      plot_names.push_back("bjet1_eta");
      plot_names.push_back("bjet2_pt");
      plot_names.push_back("bjet2_eta");
      plot_names.push_back("min_mlb");
      plot_names.push_back("min_mbb");
      plot_names.push_back("max_mbb");
      plot_names.push_back("minDPhi_b_MET");
      plot_names.push_back("minDPhi_lb_MET");
      plot_names.push_back("minDPhi_llb_MET");
      plot_names.push_back("minDPhi_l_b");
      //
      plot_names_b.push_back("bjet1_pt");
      plot_names_b.push_back("bjet1_eta");
      plot_names_b.push_back("min_mlb");
      plot_names_b.push_back("minDPhi_b_MET");
      plot_names_b.push_back("minDPhi_lb_MET");
      plot_names_b.push_back("minDPhi_llb_MET");
      plot_names_b.push_back("minDPhi_l_b");
      //
      plot_names_2b.push_back("bjet2_pt");
      plot_names_2b.push_back("bjet2_eta");
      plot_names_2b.push_back("min_mbb");
      plot_names_2b.push_back("max_mbb");
    }
    for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
      if(isel<5) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+selection[isel]+"_"+mllbin[0];
	HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
	histos[name] = h_temp;
      }
      else if(isel>=5 && isel<8) {
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString plot_name = plot_names[iplot];
            TString name = plot_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet];
            HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
            histos[name] = h_temp;
          }
        }
      }
      else if(isel>=8) {
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              TString plot_name = plot_names[iplot];
              if ( std::find(plot_names_b.begin(), plot_names_b.end(), plot_name) != plot_names_b.end() && nbtag[inb]=="nBTag0" )
                continue;
              if ( std::find(plot_names_2b.begin(), plot_names_2b.end(), plot_name) != plot_names_2b.end() && ( nbtag[inb]=="nBTag1" || nbtag[inb]=="nBTag0" ) )
                continue;
              TString name = plot_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet];
              HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
              histos[name] = h_temp;
            }
          }
        }
      }
    }
  }

  if ( applyPUWeight ) set_puWeights();
  if ( applyMuonSF ) {
    // If muon p>100 GeV or (p>50 GeV and |eta|<1.6), high-pT RECO SF are applied as a function of muon p and |eta|
    // (central high-pT RECO SFs equal zero elsewhere)
    // Else medium-pT RECO SF are applied as a function of muon pT and |eta|, to avoid zero SFs
    set_muonRecoSF();
    set_muonIDSF();
    set_muonIsoSF();
  }
  if ( applyTriggerSF ) set_triggerSF();
  if ( applyBTagSF ) set_allbTagEff();

  // Setting up btagging scale factors
  BTagCalibration_v2* btagCalib;
  BTagCalibrationReader_v2* btagReaderTight = new BTagCalibrationReader_v2(BTagEntry_v2::OP_TIGHT, "central", {"up", "down"});
  BTagCalibrationReader_v2* btagReaderMedium = new BTagCalibrationReader_v2(BTagEntry_v2::OP_MEDIUM, "central", {"up", "down"});
  BTagCalibrationReader_v2* btagReaderLoose = new BTagCalibrationReader_v2(BTagEntry_v2::OP_LOOSE, "central", {"up", "down"});
  if ( isMC ) {
    if (year == "2016APV")
    {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL16preVFP_v2.csv");
    }
    else if (year == "2016nonAPV")
    {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL16postVFP_v3.csv");
    }
    else if (year == "2017")
    {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL17_v3.csv");
    }
    else if (year == "2018")
    {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL18_v2.csv");
    }
    else
    {
      cout<<"Non-valid year for setting bTag SFs: Exiting!"<<endl;
      return 1;
    }

    btagReaderTight->load(*btagCalib, BTagEntry_v2::FLAV_B, "comb");
    btagReaderTight->load(*btagCalib, BTagEntry_v2::FLAV_C, "comb");
    btagReaderTight->load(*btagCalib, BTagEntry_v2::FLAV_UDSG, "incl");
    btagReaderMedium->load(*btagCalib, BTagEntry_v2::FLAV_B, "comb");
    btagReaderMedium->load(*btagCalib, BTagEntry_v2::FLAV_C, "comb");
    btagReaderMedium->load(*btagCalib, BTagEntry_v2::FLAV_UDSG, "incl");
    btagReaderLoose->load(*btagCalib, BTagEntry_v2::FLAV_B, "comb");
    btagReaderLoose->load(*btagCalib, BTagEntry_v2::FLAV_C, "comb");
    btagReaderLoose->load(*btagCalib, BTagEntry_v2::FLAV_UDSG, "incl");
  }

  int nEventsTotal = 0;
  int nDuplicates = 0;
  int nEventsChain = ch->GetEntries();
  TFile *currentFile = 0;
  TObjArray *listOfFiles = ch->GetListOfFiles();
  TIter fileIter(listOfFiles);
  tqdm bar;

  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    TFile *file = TFile::Open( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    TString filename(currentFile->GetTitle());

    tree->SetCacheSize(128*1024*1024);
    tree->SetCacheLearnEntries(100);

    nt.Init(tree);

    // Before any cuts
    int icutflow = 0;
    TString label = "Total";
    TString slicedlabel = label;
    if ( isMC )
      h_cutflow->Fill(icutflow,xsec*lumi);
    h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
    for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
      for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
        for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
          TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
          if ( isMC )
            slicedcutflows[slice]->Fill(icutflow,xsec*lumi);
          slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
        }
      }
    }

    for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

      nt.GetEntry(event);
      tree->LoadTree(event);

      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);

      float weight = 1.0;
      if ( isMC ) {
	weight = nt.genWeight();
	if(removeSpikes && weight*factor>1e2) continue;

	// Apply L1 muon pre-firing weight (available in nanoAODv9):
	// https://twiki.cern.ch/twiki/bin/view/CMS/L1PrefiringWeightRecipe
	weight *= nt.L1PreFiringWeight_Muon_Nom();

	// Apply PU reweight
	if ( applyPUWeight ) {
	  unsigned int nTrueInt = nt.Pileup_nTrueInt();
	  TString whichPUWeight = "central";
	  if ( varyPUWeightUp ) whichPUWeight = "up";
	  else if ( varyPUWeightDown ) whichPUWeight = "down";
	  TString puyear = year;
	  if ( useOnlyRun2018B ) puyear = "2018B";
	  weight *= get_puWeight(nTrueInt, puyear, whichPUWeight);
	}

	// Apply top pT weight:
	// https://twiki.cern.ch/twiki/bin/view/CMS/TopPtReweighting#TOP_PAG_corrections_based_on_dat
	if ( applyTopPtWeight && process == "ttbar" ) {
	  float exp_p0 =  0.0615;
	  float exp_p1 = -0.0005;
	  float topweight = 1.0;
	  float maxtoppt = 500.0;
	  int ntop = 0;
	  for ( unsigned int t=0; t<nt.nGenPart(); t++ ) {
	    if ( ntop >=2 ) break;
	    if ( abs(nt.GenPart_pdgId().at(t))!=6 or nt.GenPart_status().at(t)!=62 ) continue;
	    if ( abs(nt.GenPart_pdgId().at(t))==6 ) {
	      float tpt = std::min(nt.GenPart_pt().at(t), maxtoppt);
	      topweight *= TMath::Exp( exp_p0 + exp_p1*tpt );
	      ++ntop;
	    }
	  }
	  weight *= TMath::Sqrt(topweight);
	}

      }

      unsigned int runnb = nt.run();
      unsigned int lumiblock = nt.luminosityBlock();
      unsigned long int evtnb = nt.event();
      int npv = nt.PV_npvs();

      // Apply Golden JSON
      if ( !isMC ) {
	if ( !(goodrun(runnb, lumiblock)) )
	  continue;
	if ( removeDataDuplicates ) {
	  DorkyEventIdentifier id(runnb, evtnb, lumiblock);
	  if ( is_duplicate(id) ){
	    ++nDuplicates;
	    continue;
	  }
	}
      }

      // MET xy correction: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections#xy_Shift_Correction_MET_phi_modu
      // METXYCorr_Met_MetPhi(double uncormet, double uncormet_phi, int runnb, TString year, bool isMC, int npv, bool isUL =false,bool ispuppi=false)
      std::pair<double,double> pfmet = METXYCorr_Met_MetPhi(nt.MET_pt(), nt.MET_phi(), runnb, year, isMC, npv, true, false);
      double pfmet_pt  = pfmet.first;
      double pfmet_phi = pfmet.second;
      std::pair<double,double> puppimet = METXYCorr_Met_MetPhi(nt.PuppiMET_pt(), nt.PuppiMET_phi(), runnb, year, isMC, npv, true, true);
      double puppimet_pt  = puppimet.first;
      double puppimet_phi = puppimet.second;

      // Account for tunepRelPt if useTuneP
      vector<LorentzVector> Muon_p4 = {};
      vector<double> Muon_pt = {};
      vector<double> Muon_tkRelIso = {};
      TVector2 pfmet_temp;
      pfmet_temp.SetMagPhi(pfmet_pt,pfmet_phi);
      TVector2 puppimet_temp;
      puppimet_temp.SetMagPhi(puppimet_pt,puppimet_phi);
      // Muon selection loop
      int nMu_id = 0;
      vector<int> cand_muons_id;
      int nMu_pt = 0;
      vector<int> cand_muons_id_pteta;
      int nMu_iso = 0;
      vector<int> cand_muons;
      //
      float triggerSF = -1.0;
      //
      for ( unsigned int mu = 0; mu < nt.nMuon(); mu++ ) {
	Muon_pt.push_back(nt.Muon_pt().at(mu));
	Muon_p4.push_back(LorentzVector(nt.Muon_pt().at(mu),nt.Muon_eta().at(mu),nt.Muon_phi().at(mu),nt.Muon_mass().at(mu)));
	Muon_tkRelIso.push_back(nt.Muon_tkRelIso().at(mu));
	//
        bool mu_trk_and_global = ( nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu) );
        bool mu_id = ( nt.Muon_highPtId().at(mu) >= 2 );
	bool mu_pt = false;
	bool mu_relIso = false;
        if ( mu_trk_and_global && mu_id ) {
          nMu_id++;
          cand_muons_id.push_back(mu);
	  if ( useTuneP ) {
	    TVector2 muon_temp;
	    TVector2 muon_temp_tunep;
	    muon_temp.SetMagPhi(Muon_pt[mu],nt.Muon_phi().at(mu));
	    Muon_pt[mu] *= nt.Muon_tunepRelPt().at(mu);
	    Muon_p4[mu] = LorentzVector(Muon_pt[mu],nt.Muon_eta().at(mu),nt.Muon_phi().at(mu),nt.Muon_mass().at(mu));
	    muon_temp_tunep.SetMagPhi(Muon_pt[mu],nt.Muon_phi().at(mu));
	    // Correct MET for highPtId muon candidates
	    pfmet_temp+=muon_temp;
	    pfmet_temp-=muon_temp_tunep;
	    puppimet_temp+=muon_temp;
	    puppimet_temp-=muon_temp_tunep;
	  }
	  else {
	    Muon_tkRelIso[mu] *= nt.Muon_tunepRelPt().at(mu);
	  }
	  mu_pt = ( Muon_pt.at(mu) > 53 && fabs(nt.Muon_eta().at(mu)) < 2.4 );
	  mu_relIso = ( Muon_tkRelIso.at(mu) < 0.1 );
          if ( mu_pt ) {
            nMu_pt++;
            cand_muons_id_pteta.push_back(mu);
            if ( mu_relIso ) {
              nMu_iso++;
              cand_muons.push_back(mu);
            }
          }
        }
	if ( isMC ) {
	  // 2016: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2016
	  // 2017: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2017
	  // 2018: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2018
	  if ( applyMuonSF ) {
	    // Apply muon (RECO, ID, ISO) SFs
	    TString tvariation = "central";
	    if ( varyTriggerSFUp ) tvariation = "up";
	    else if ( varyTriggerSFDown ) tvariation = "down";
	    // If muon p>100 GeV or (p>50 GeV and |eta|<1.6), high-pT RECO SF are applied as a function of muon p and |eta|
	    // (central high-pT RECO SFs equal zero elsewhere)
	    // Else medium-pT RECO SF are applied as a function of muon pT and |eta|, to avoid zero SFs
	    weight *= get_muonRecoSF(Muon_p4.at(mu).P(), Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	    if ( mu_id ) {
	      weight *= get_muonIDSF(Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	      if ( mu_relIso ) {
		weight *= get_muonIsoSF(Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	      }
	    }
	  }
	  if ( applyTriggerSF && triggerSF < 0.0 ) {
	    // Apply trigger SF
	    TString tvariation = "central";
	    if ( varyTriggerSFUp ) tvariation = "up";
	    else if ( varyTriggerSFDown ) tvariation = "down";
	    float minPt  = 52.0;
	    float maxEta = 2.4; 
	    if ( Muon_pt.at(mu) < minPt ) {
	      triggerSF = 0.0;
	    }
	    else if ( fabs(nt.Muon_eta().at(mu) ) < maxEta && mu_id ) {
	      triggerSF = get_triggerSF(Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	    }
	    else continue;
	  }
	}
      }

      pfmet_pt  = pfmet_temp.Mod();
      pfmet_phi = TVector2::Phi_mpi_pi(pfmet_temp.Phi());
      puppimet_pt  = puppimet_temp.Mod();
      puppimet_phi = TVector2::Phi_mpi_pi(puppimet_temp.Phi());

      icutflow=0;
      // For data, fill "total" in cutflow after golden JSON
      if ( !isMC ) {
        h_cutflow->Fill(icutflow,weight*factor);
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
              slicedcutflows[slice]->Fill(icutflow,weight*factor);
            }
          }
        }
      }
      icutflow++;

      // Define histo names and variables
      plot_names = { };
      map<TString, float> variable { };

      // Define extra histo names and variables (for third lepton/isotrack veto variables)
      vector<TString> extra_plot_names = { };
      map<TString, float> extra_variable { };

      // Book histo names and variables
      plot_names.push_back("pfmet_pt");
      variable.insert({"pfmet_pt", pfmet_pt});

      plot_names.push_back("pfmet_phi");
      variable.insert({"pfmet_phi", pfmet_phi});

      plot_names.push_back("puppimet_pt");
      variable.insert({"puppimet_pt", puppimet_pt});

      plot_names.push_back("puppimet_phi");
      variable.insert({"puppimet_phi", puppimet_phi});

      if ( muonDebug ) {
        plot_names.push_back("mu1_pt");
        variable.insert({"mu1_pt", Muon_pt.at(0)});

        plot_names.push_back("mu2_pt");
        variable.insert({"mu2_pt", Muon_pt.at(1)});

        plot_names.push_back("mu1_eta");
        variable.insert({"mu1_eta", nt.Muon_eta().at(0)});

        plot_names.push_back("mu2_eta");
        variable.insert({"mu2_eta", nt.Muon_eta().at(1)});

        plot_names.push_back("mu1_phi");
        variable.insert({"mu1_phi", nt.Muon_phi().at(0)});

        plot_names.push_back("mu2_phi");
        variable.insert({"mu2_phi", nt.Muon_phi().at(1)});

        plot_names.push_back("mu1_dxy");
        variable.insert({"mu1_dxy", fabs(nt.Muon_dxy().at(0))});

        plot_names.push_back("mu2_dxy");
        variable.insert({"mu2_dxy", fabs(nt.Muon_dxy().at(1))});

        plot_names.push_back("mu1_dz");
        variable.insert({"mu1_dz", fabs(nt.Muon_dz().at(0))});

        plot_names.push_back("mu2_dz");
        variable.insert({"mu2_dz", fabs(nt.Muon_dz().at(1))});

        plot_names.push_back("mu1_trkRelIso");
        variable.insert({"mu1_trkRelIso", Muon_tkRelIso.at(0)});

        plot_names.push_back("mu2_trkRelIso");
        variable.insert({"mu2_trkRelIso", Muon_tkRelIso.at(1)});

        plot_names.push_back("nCand_Muons");
        variable.insert({"nCand_Muons", nt.nMuon()});
      }


      // After skim
      label = "After skim";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
      icutflow++;

      // HLT selection
      if ( (year=="2016nonAPV" || year=="2016APV") && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
      if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;

      // Apply trigger SF:
      if ( isMC && applyTriggerSF )  {
	if ( triggerSF < 0.0 )
	  weight *= 0.0;
	else
	  weight *= triggerSF;
      }

      label = "HLT";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
      icutflow++;

      // Number of good primary vertices
      if ( nt.PV_npvsGood() < 1 ) continue;
      // MET filters: https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2#UL_data
      if ( // process.Contains("data") &&
	   !( nt.Flag_goodVertices()>=1 &&
	      nt.Flag_globalSuperTightHalo2016Filter()>=1 &&
	      nt.Flag_HBHENoiseFilter()>=1 &&
	      nt.Flag_HBHENoiseIsoFilter()>=1 &&
	      nt.Flag_EcalDeadCellTriggerPrimitiveFilter()>=1 &&
	      nt.Flag_BadPFMuonFilter()>=1 &&
	      nt.Flag_BadPFMuonDzFilter()>=1 &&
	      nt.Flag_eeBadScFilter()>=1 &&
	      ( year=="2016" ? 1 : nt.Flag_ecalBadCalibFilter()>=1 ) &&
	      ( year=="2016" ? 1 : nt.Flag_hfNoisyHitsFilter()>=1 ) )
	   ) continue;

      // Apply extra noise cleaning
      if ( !usePuppiMET ) {
	if( isinf(pfmet_pt) || isnan(pfmet_pt) )
	  continue;
      }
      else {
	if ( isinf(puppimet_pt) || isnan(puppimet_pt) )
	  continue;
      }
      if ( nt.nJet()>0 && nt.Jet_pt().at(0)>13000.0 )
	continue;
      if ( nt.nMuon()>0 && Muon_pt.at(0)>13000.0 )
	continue;

      // For test: use Run2018B, with exclusion of HEM15/16 affcted runs:
      if ( !isMC )
	if ( runnb >= HEM_startRun )
	  continue;

      // HEM15/16 veto
      if ( doHEMveto && year == "2018" ) {
	if ( ( !isMC && runnb >= HEM_startRun ) || ( isMC && evtnb % HEM_fracDen < HEM_fracNum ) ) {
	  // Jets
	  bool hasHEMjet = false;
	  if ( useHEMjets )
	    for ( unsigned int i=0; i < nt.nJet(); i++ ) {
	      if ( nt.Jet_pt().at(i) < HEM_jetPtCut )
		break;
	      // For jets, increase affected area by half of jet cone (i.e., by 0.2)
	      if ( nt.Jet_jetId().at(i) > 1 &&
		   nt.Jet_eta().at(i) > HEM_region[0]-0.2 && nt.Jet_eta().at(i) < HEM_region[1]+0.2 &&
		   nt.Jet_phi().at(i) > HEM_region[2]-0.2 && nt.Jet_phi().at(i) < HEM_region[3]+0.2 ) {
		hasHEMjet = true;
		break;
	      }
	    }
	  // Muons (using same ID as for analysis)
	  bool hasHEMmuon = false;
	  if ( useHEMmuons )
	    for ( unsigned int i = 0; i < nt.nMuon(); i++ ) {
	      if ( Muon_pt.at(i) < HEM_lepPtCut )
		break;
	      if ( nt.Muon_isGlobal().at(i) && nt.Muon_isTracker().at(i) &&
		   nt.Muon_highPtId().at(i) >= 2 &&
		   Muon_tkRelIso.at(i) < 0.1 &&
		   nt.Muon_eta().at(i) > HEM_region[0] && nt.Muon_eta().at(i) < HEM_region[1] &&
		   nt.Muon_phi().at(i) > HEM_region[2] && nt.Muon_phi().at(i) < HEM_region[3] ) {
		hasHEMmuon = true;
		break;
	      }
	    }
	  // Electrons
	  bool hasHEMelectron = false;
	  if ( useHEMelectrons )
	    for ( unsigned int i = 0; i < nt.nElectron(); i++ ) {
	      if ( nt.Electron_pt().at(i) < HEM_lepPtCut )
		break;
	      if ( nt.Electron_cutBased().at(i) > 0 &&
		   nt.Electron_miniPFRelIso_all().at(i) < 0.1 &&
		   fabs(nt.Electron_dxy().at(i)) < 0.2 &&
		   fabs(nt.Electron_dz().at(i)) < 0.5 &&
		   nt.Electron_eta().at(i) > HEM_region[0] && nt.Electron_eta().at(i) < HEM_region[1] &&
		   nt.Electron_phi().at(i) > HEM_region[2] && nt.Electron_phi().at(i) < HEM_region[3] ) {
		hasHEMelectron = true;
		break;
	      }
	    }
	  // IsoTracks (using both PF candidates and highPurity lost tracks)
	  bool hasHEMisotrack = false;
	  if ( useHEMisotracks )
	    for ( unsigned int i = 0; i < nt.nIsoTrack(); i++ ) {
	      if ( nt.IsoTrack_pt().at(i) < HEM_trkPtCut )
		break;
	      if ( (nt.IsoTrack_isPFcand().at(i) || nt.IsoTrack_isHighPurityTrack().at(i)) &&
		 (abs(nt.IsoTrack_pdgId().at(i))==11 || abs(nt.IsoTrack_pdgId().at(i))==13 || abs(nt.IsoTrack_pdgId().at(i))==211) &&
		   fabs(nt.IsoTrack_dxy().at(i)) < 0.2 &&
		   fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
		   (((abs(nt.IsoTrack_pdgId().at(i))==11 || abs(nt.IsoTrack_pdgId().at(i))==13) && nt.IsoTrack_pfRelIso03_chg().at(i) < 0.2) ||
		    (abs(nt.IsoTrack_pdgId().at(i))==211 && nt.IsoTrack_pfRelIso03_chg().at(i) < 0.1)) &&
		   nt.IsoTrack_eta().at(i) > HEM_region[0] && nt.IsoTrack_eta().at(i) < HEM_region[1] &&
		   nt.IsoTrack_phi().at(i) > HEM_region[2] && nt.IsoTrack_phi().at(i) < HEM_region[3] ) {
		hasHEMisotrack = true;
		break;
	      }
	    }
	  // Apply HEM veto
	  if( hasHEMjet || hasHEMmuon || hasHEMelectron || hasHEMisotrack ) {
	    continue;
	  }
	}
      }

      // Fill histos: sel0
      label = ">0 good PVs & MET Filters";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
      icutflow++;
      TString sel = "sel0";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      // Defining booleans for cutflow
      bool id_req = ( nMu_id > 1 );
      bool pt_req = ( nMu_pt > 1 );
      bool iso_req = ( nMu_iso > 1);

      if ( !id_req ) continue;
      // Fill histos: sel1
      label = ">1 muons w/ highPt ID";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
      icutflow++;
      sel = "sel1";
      if ( muonDebug ) {
        variable["mu1_pt"] = Muon_pt.at(cand_muons_id[0]);
        variable["mu2_pt"] = Muon_pt.at(cand_muons_id[1]);
        variable["mu1_eta"] = nt.Muon_eta().at(cand_muons_id[0]);
        variable["mu2_eta"] = nt.Muon_eta().at(cand_muons_id[1]);
        variable["mu1_phi"] = nt.Muon_phi().at(cand_muons_id[0]);
        variable["mu2_phi"] = nt.Muon_phi().at(cand_muons_id[1]);
        variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id[0]));
        variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id[1]));
        variable["mu1_dz"] = fabs(nt.Muon_dz().at(cand_muons_id[0]));
        variable["mu2_dz"] = fabs(nt.Muon_dz().at(cand_muons_id[1]));
        variable["mu1_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id[0]);
        variable["mu2_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id[1]);
        variable["nCand_Muons"] = cand_muons.size();
      }
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      if ( !pt_req ) continue;
      // Fill histos: sel2
      label = ">1 muons w/ pT>53 GeV & |eta|<2.4";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
      icutflow++;
      sel = "sel2";
      if ( muonDebug ) {
        variable["mu1_pt"] = Muon_pt.at(cand_muons_id_pteta[0]);
        variable["mu2_pt"] = Muon_pt.at(cand_muons_id_pteta[1]);
        variable["mu1_eta"] = nt.Muon_eta().at(cand_muons_id_pteta[0]);
        variable["mu2_eta"] = nt.Muon_eta().at(cand_muons_id_pteta[1]);
        variable["mu1_phi"] = nt.Muon_phi().at(cand_muons_id_pteta[0]);
        variable["mu2_phi"] = nt.Muon_phi().at(cand_muons_id_pteta[1]);
        variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id_pteta[0]));
        variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id_pteta[1]));
        variable["mu1_dz"] = fabs(nt.Muon_dz().at(cand_muons_id_pteta[0]));
        variable["mu2_dz"] = fabs(nt.Muon_dz().at(cand_muons_id_pteta[1]));
        variable["mu1_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id_pteta[0]);
        variable["mu2_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id_pteta[1]);
        variable["nCand_Muons"] = cand_muons.size();
      }
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      if ( !iso_req ) continue;
      // Fill histos: sel3
      label = ">1 muons w/ track iso./pT<0.1";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }

      icutflow++;
      sel = "sel3";
      if ( muonDebug ) {
        variable["mu1_pt"] = Muon_pt.at(cand_muons[0]);
        variable["mu2_pt"] = Muon_pt.at(cand_muons[1]);
        variable["mu1_eta"] = nt.Muon_eta().at(cand_muons[0]);
        variable["mu2_eta"] = nt.Muon_eta().at(cand_muons[1]);
        variable["mu1_phi"] = nt.Muon_phi().at(cand_muons[0]);
        variable["mu2_phi"] = nt.Muon_phi().at(cand_muons[1]);
        variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(cand_muons[0]));
        variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(cand_muons[1]));
        variable["mu1_dz"] = fabs(nt.Muon_dz().at(cand_muons[0]));
        variable["mu2_dz"] = fabs(nt.Muon_dz().at(cand_muons[1]));
        variable["mu1_trkRelIso"] = Muon_tkRelIso.at(cand_muons[0]);
        variable["mu2_trkRelIso"] = Muon_tkRelIso.at(cand_muons[1]);
        variable["nCand_Muons"] = cand_muons.size();
      }
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      // Trigger object finding (match: dR<0.02)
      bool atLeastSelectedMu_matchedToTrigObj = false;
      vector<bool> muMatchedToTrigObj;
      for ( int n = 0; n < nt.nTrigObj(); n++ ) {
        if ( abs(nt.TrigObj_id().at(n)) != 13 ) continue;
        if ( !(nt.TrigObj_filterBits().at(n) & 8) ) continue;
        for ( auto i_cand_muons : cand_muons ) {
	  if ( IsMatched( nt.Muon_eta().at(i_cand_muons), nt.Muon_phi().at(i_cand_muons), nt.TrigObj_eta().at(n), nt.TrigObj_phi().at(n), 0.02 ) ) {
            muMatchedToTrigObj.push_back(true);
            atLeastSelectedMu_matchedToTrigObj = true;
          }
          else muMatchedToTrigObj.push_back(false);
        }
      }
      if ( !atLeastSelectedMu_matchedToTrigObj ) continue;
      // Fill histos: sel4
      label = ">0 HLT match (dR<0.02)";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            slicedcutflows[slice]->Fill(icutflow,weight*factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
      icutflow++;
      sel = "sel4";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      int leadingMu_idx = -1, subleadingMu_idx = -1;
      float selectedPair_M = -1.0;
      bool Zboson = false;
      for ( unsigned int i=0; i<cand_muons.size(); i++ ) {
        TVector3 mu_1(Muon_p4.at(cand_muons[i]).Px(),Muon_p4.at(cand_muons[i]).Py(),Muon_p4.at(cand_muons[i]).Pz());
        for ( unsigned int j=i+1; j<cand_muons.size(); j++ ) {
          if ( nt.Muon_pdgId().at(cand_muons[i]) + nt.Muon_pdgId().at(cand_muons[j]) != 0 ) continue; // Opposite sign, same flavor
          if ( !(muMatchedToTrigObj[i] || muMatchedToTrigObj[j]) ) continue; // At least one muon in pair matched to HLT
          TVector3 mu_2(Muon_p4.at(cand_muons[j]).Px(),Muon_p4.at(cand_muons[j]).Py(),Muon_p4.at(cand_muons[j]).Pz());
          if ( !(IsSeparated( mu_1, mu_2, 0.02 ) ) ) continue; // 3D angle between muons > pi - 0.02
          float m_ll = (Muon_p4.at(cand_muons[i])+Muon_p4.at(cand_muons[j])).M();
          if ( fabs(m_ll - Zmass)<20.0 ) { // Reject event if it contains dimuon pair compatible with Z mass (within 20 GeV)
            Zboson = true;
            continue;
          }
          if ( selectedPair_M < 0.0 ) {
            leadingMu_idx = cand_muons[i];
            subleadingMu_idx = cand_muons[j];
            selectedPair_M = m_ll;
          }
        }
        if ( Zboson ) break;
      }
      if ( selectedPair_M < 0.0 || Zboson ) continue;

      auto leadingMu_p4 = Muon_p4.at(leadingMu_idx);
      auto subleadingMu_p4 = Muon_p4.at(subleadingMu_idx);
      auto selectedPair_p4 = leadingMu_p4 + subleadingMu_p4;
      float dPhi_ll_MET = fabs(TVector2::Phi_mpi_pi(selectedPair_p4.Phi() - puppimet_phi));
      if ( !(usePuppiMET) )
	dPhi_ll_MET = fabs(TVector2::Phi_mpi_pi(selectedPair_p4.Phi() - pfmet_phi));

      float minDPhi_l_MET = 1e9;
      float dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(leadingMu_p4.Phi() - puppimet_phi));
      if ( !(usePuppiMET) )
	dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(leadingMu_p4.Phi() - pfmet_phi));
      if ( dPhi_l_MET < minDPhi_l_MET ) minDPhi_l_MET = dPhi_l_MET;
      dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(subleadingMu_p4.Phi() - puppimet_phi));
      if ( !(usePuppiMET) )
	dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(subleadingMu_p4.Phi() - pfmet_phi));
      if ( dPhi_l_MET < minDPhi_l_MET ) minDPhi_l_MET = dPhi_l_MET;

      mllbinsel[0] = true;
      if (doMllBins) {
        if ( selectedPair_M > 150. && selectedPair_M < 250)
          mllbinsel[1] = true;
        else mllbinsel[1] = false;
        if ( selectedPair_M > 200. && selectedPair_M < 600)
          mllbinsel[2] = true;
        else mllbinsel[2] = false;
        if ( selectedPair_M > 500. && selectedPair_M < 900)
          mllbinsel[3] = true;
        else mllbinsel[3] = false;
        if ( selectedPair_M > 700. && selectedPair_M < 1300.)
          mllbinsel[4] = true;
        else mllbinsel[4] = false;
        if ( selectedPair_M > 1100. && selectedPair_M < 1900.)
          mllbinsel[5] = true;
        else mllbinsel[5] = false;
        if ( selectedPair_M > 1500. && selectedPair_M < 2500.)
          mllbinsel[6] = true;
        else mllbinsel[6] = false;
      }

      MuDetRegionsel[0] = true;
      if (doMuDetRegionBins){
        if (fabs(nt.Muon_eta().at(leadingMu_idx)) < 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) < 1.2)
          MuDetRegionsel[1] = true;
        else
          MuDetRegionsel[1] = false;
        if ((fabs(nt.Muon_eta().at(leadingMu_idx)) < 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) > 1.2) || (fabs(nt.Muon_eta().at(leadingMu_idx)) > 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) < 1.2))
          MuDetRegionsel[2] = true;
        else
          MuDetRegionsel[2] = false;
        if (fabs(nt.Muon_eta().at(leadingMu_idx)) > 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) > 1.2)
          MuDetRegionsel[3] = true;
        else
          MuDetRegionsel[3] = false;
        }

      // Add histos: sel5
      plot_names.push_back("mmumu");
      variable.insert({"mmumu", selectedPair_M});

      if ( muonDebug ) {
        variable["mu1_pt"] = Muon_pt.at(leadingMu_idx);
        variable["mu2_pt"] = Muon_pt.at(subleadingMu_idx);
        variable["mu1_eta"] = nt.Muon_eta().at(leadingMu_idx);
        variable["mu2_eta"] = nt.Muon_eta().at(subleadingMu_idx);
        variable["mu1_phi"] = nt.Muon_phi().at(leadingMu_idx);
        variable["mu2_phi"] = nt.Muon_phi().at(subleadingMu_idx);
        variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(leadingMu_idx));
        variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(subleadingMu_idx));
        variable["mu1_dz"] = fabs(nt.Muon_dz().at(leadingMu_idx));
        variable["mu2_dz"] = fabs(nt.Muon_dz().at(subleadingMu_idx));
        variable["mu1_trkRelIso"] = Muon_tkRelIso.at(leadingMu_idx);
        variable["mu2_trkRelIso"] = Muon_tkRelIso.at(subleadingMu_idx);
        variable["nCand_Muons"] = cand_muons.size();
      }
      else {
        plot_names.push_back("mu1_pt");
        variable.insert({"mu1_pt", Muon_pt.at(leadingMu_idx)});

        plot_names.push_back("mu2_pt");
        variable.insert({"mu2_pt", Muon_pt.at(subleadingMu_idx)});

        plot_names.push_back("mu1_eta");
        variable.insert({"mu1_eta", nt.Muon_eta().at(leadingMu_idx)});

        plot_names.push_back("mu2_eta");
        variable.insert({"mu2_eta", nt.Muon_eta().at(subleadingMu_idx)});

        plot_names.push_back("mu1_phi");
        variable.insert({"mu1_phi", nt.Muon_phi().at(leadingMu_idx)});

        plot_names.push_back("mu2_phi");
        variable.insert({"mu2_phi", nt.Muon_phi().at(subleadingMu_idx)});

        plot_names.push_back("mu1_dxy");
        variable.insert({"mu1_dxy", fabs(nt.Muon_dxy().at(leadingMu_idx))});

        plot_names.push_back("mu2_dxy");
        variable.insert({"mu2_dxy", fabs(nt.Muon_dxy().at(subleadingMu_idx))});

        plot_names.push_back("mu1_dz");
        variable.insert({"mu1_dz", fabs(nt.Muon_dz().at(leadingMu_idx))});

        plot_names.push_back("mu2_dz");
        variable.insert({"mu2_dz", fabs(nt.Muon_dz().at(subleadingMu_idx))});

        plot_names.push_back("mu1_trkRelIso");
        variable.insert({"mu1_trkRelIso", Muon_tkRelIso.at(leadingMu_idx)});

        plot_names.push_back("mu2_trkRelIso");
        variable.insert({"mu2_trkRelIso", Muon_tkRelIso.at(subleadingMu_idx)});

        plot_names.push_back("nCand_Muons");
        variable.insert({"nCand_Muons", cand_muons.size()});
      }

      plot_names.push_back("dPhi_ll");
      variable.insert({"dPhi_ll", fabs( TVector2::Phi_mpi_pi( nt.Muon_phi().at(leadingMu_idx) - nt.Muon_phi().at(subleadingMu_idx) ) )});

      plot_names.push_back("dEta_ll");
      variable.insert({"dEta_ll", fabs( nt.Muon_eta().at(leadingMu_idx) - nt.Muon_eta().at(subleadingMu_idx) )});

      plot_names.push_back("dEta_dPhi_ratio_ll");
      variable.insert({"dEta_dPhi_ratio_ll", TMath::Log10( fabs( nt.Muon_eta().at(leadingMu_idx) - nt.Muon_eta().at(subleadingMu_idx) ) / fabs( TVector2::Phi_mpi_pi( nt.Muon_phi().at(leadingMu_idx) - nt.Muon_phi().at(subleadingMu_idx) ) ) )});

      plot_names.push_back("dPhi_ll_MET");
      variable.insert({"dPhi_ll_MET", dPhi_ll_MET});

      plot_names.push_back("minDPhi_l_MET");
      variable.insert({"minDPhi_l_MET", minDPhi_l_MET});

      // Fill histos: sel5
      label = "Muon pair (OS, !Z)";
      slicedlabel = "Muon pair (OS), ";
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            TString tlabel = slicedlabel + mllbinlabel[mllbin[imll]] + MuDetRegionbinlabel[MuDetRegion[iMuDet]];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              slicedcutflows[slice]->Fill(icutflow, weight * factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, tlabel);
          }
        }
      }

      icutflow++;
      sel = "sel5";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
        TString plot_name = plot_names[iplot];
        for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              histos[name]->Fill(variable[plot_name], weight * factor);
           }
         }
      }

      if ( selectedPair_M < 150 ) continue;
      // Fill histos: sel6
      label = "m_{#mu#mu}>150 GeV";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
        for (unsigned int inb = 0; inb < nbtag.size(); inb++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              slicedcutflows[slice]->Fill(icutflow, weight * factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
          }
        }
      }
      icutflow++;

      // Look for a third isolated lepton and then veto the event if it is found
      // Muons (using same ID and isolation as for selected muons, to avoid scale factor combinatorics)
      vector<int> extra_muons;
      for ( int i = 0; i < nt.nMuon(); i++ ) {
        if ( Muon_pt.at(i) > 10. &&
	     fabs(nt.Muon_eta().at(i)) < 2.4 &&
	     nt.Muon_isGlobal().at(i) && nt.Muon_isTracker().at(i) &&
	     nt.Muon_highPtId().at(i) >= 2 &&
	     Muon_tkRelIso.at(i) < 0.1 &&
	     !( i == leadingMu_idx || i == subleadingMu_idx)) {
          extra_muons.push_back(i);
        }
      }

      // Electrons
      vector<int> extra_electrons;
      for ( int i = 0; i < nt.nElectron(); i++ ) {
        if ( nt.Electron_pt().at(i) > 10. &&
	     fabs(nt.Electron_eta().at(i)) < 2.5 &&
	     nt.Electron_cutBased().at(i) > 0 &&
	     nt.Electron_miniPFRelIso_all().at(i) < 0.1 &&
	     fabs(nt.Electron_dxy().at(i)) < 0.2 &&
	     fabs(nt.Electron_dz().at(i)) < 0.5 ) {
          extra_electrons.push_back(i);
        }
      }

      // IsoTracks
      vector<int> extra_isotracks_lep;
      for ( int i = 0; i < nt.nIsoTrack(); i++ ) {
        if ( nt.IsoTrack_isPFcand().at(i) &&
	     (abs(nt.IsoTrack_pdgId().at(i))==11 || (abs(nt.IsoTrack_pdgId().at(i))==13)) &&
	     nt.IsoTrack_pt().at(i) > 5. && 
	     fabs(nt.IsoTrack_eta().at(i)) < 2.5 &&
	     fabs(nt.IsoTrack_dxy().at(i)) < 0.2 &&
	     fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
	     nt.IsoTrack_pfRelIso03_chg().at(i) < 0.2) {
          float mindr=1e9;
          for ( auto i_cand_muons : cand_muons ) {
            if (i_cand_muons!=leadingMu_idx && i_cand_muons!=subleadingMu_idx) continue;
            float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons);
            float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons));
            float dr = TMath::Sqrt( deta*deta+dphi*dphi );
            if ( dr < mindr ) {
              mindr = dr;
            }
          }
	  // Avoid overlap with muon isolation cone: otherwise, muons and isotracks are anyways likely to fail isolation requirement
          if ( mindr > 0.3 )
            extra_isotracks_lep.push_back(i);
        }
      }

      vector<int> extra_isotracks_chh;
      for ( int i = 0; i < nt.nIsoTrack(); i++ ) {
        if ( nt.IsoTrack_isPFcand().at(i) &&
	     abs(nt.IsoTrack_pdgId().at(i))==211 &&
	     nt.IsoTrack_pt().at(i) > 10. &&
	     fabs(nt.IsoTrack_eta().at(i)) < 2.5 &&
	     fabs(nt.IsoTrack_dxy().at(i)) < 0.2 &&
	     fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
	     nt.IsoTrack_pfRelIso03_chg().at(i) < 0.1) {
          float mindr=1e9;
          for ( auto i_cand_muons : cand_muons ) {
            if (i_cand_muons!=leadingMu_idx && i_cand_muons!=subleadingMu_idx) continue;
            float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons);
            float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons));
            float dr = TMath::Sqrt( deta*deta+dphi*dphi );
            if ( dr < mindr ) {
              mindr = dr;
            }
          }
	  // Avoid overlap with muon isolation cone: otherwise, muons and isotracks are anyways likely to fail isolation requirement
          if ( mindr > 0.3 )
            extra_isotracks_chh.push_back(i);
        }
      }

      // Add extra histos: before sel6 (third lepton/isotrack veto)
      extra_plot_names.push_back("nExtra_muons");
      extra_variable.insert({"nExtra_muons", extra_muons.size()});

      extra_plot_names.push_back("nExtra_electrons");
      extra_variable.insert({"nExtra_electrons",extra_electrons.size()});

      extra_plot_names.push_back("nExtra_lepIsoTracks");
      extra_variable.insert({"nExtra_lepIsoTracks",extra_isotracks_lep.size()});

      extra_plot_names.push_back("nExtra_chhIsoTracks");
      extra_variable.insert({"nExtra_chhIsoTracks",extra_isotracks_chh.size()});

      if ( extra_muons.size() > 0 ) {
	extra_plot_names.push_back("mu3_pt");
	extra_variable.insert({"mu3_pt", Muon_pt.at(extra_muons[0])});

	extra_plot_names.push_back("mu3_eta");
	extra_variable.insert({"mu3_eta", nt.Muon_eta().at(extra_muons[0])});

	extra_plot_names.push_back("mu3_trkRelIso");
	extra_variable.insert({"mu3_trkRelIso", Muon_tkRelIso.at(extra_muons[0])});
      }

      if ( extra_electrons.size() > 0 ) {
	extra_plot_names.push_back("ele_extra_pt");
	extra_variable.insert({"ele_extra_pt", nt.Electron_pt().at(extra_electrons[0])});

	extra_plot_names.push_back("ele_extra_eta");
	extra_variable.insert({"ele_extra_eta", nt.Electron_eta().at(extra_electrons[0])});

	extra_plot_names.push_back("ele_extra_miniPFRelIso");
	extra_variable.insert({"ele_extra_miniPFRelIso", nt.Electron_miniPFRelIso_all().at(extra_electrons[0])});
      }

      if ( extra_isotracks_lep.size() > 0 ) {
	extra_plot_names.push_back("lepIsoTrack_extra_pt");
	extra_variable.insert({"lepIsoTrack_extra_pt", nt.IsoTrack_pt().at(extra_isotracks_lep[0])});

	extra_plot_names.push_back("lepIsoTrack_extra_eta");
	extra_variable.insert({"lepIsoTrack_extra_eta", nt.IsoTrack_eta().at(extra_isotracks_lep[0])});

	extra_plot_names.push_back("lepIsoTrack_extra_PFRelIsoChg");
	extra_variable.insert({"lepIsoTrack_extra_PFRelIsoChg", nt.IsoTrack_pfRelIso03_chg().at(extra_isotracks_lep[0])});
      }

      if ( extra_isotracks_chh.size() > 0 ) {
	extra_plot_names.push_back("chhIsoTrack_extra_pt");
	extra_variable.insert({"chhIsoTrack_extra_pt", nt.IsoTrack_pt().at(extra_isotracks_chh[0])});

	extra_plot_names.push_back("chhIsoTrack_extra_eta");
	extra_variable.insert({"chhIsoTrack_extra_eta", nt.IsoTrack_eta().at(extra_isotracks_chh[0])});

	extra_plot_names.push_back("chhIsoTrack_extra_PFRelIsoChg");
	extra_variable.insert({"chhIsoTrack_extra_PFRelIsoChg", nt.IsoTrack_pfRelIso03_chg().at(extra_isotracks_chh[0])});
      }

      // Fill standard histos for sel6
      sel = "sel6";
      for (unsigned int iplot = 0; iplot < plot_names.size(); iplot++) {
        TString plot_name = plot_names[iplot];
        for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
      }
      // Now fill extra histos for sel6 (before third lepton/isotrack veto)
      for ( unsigned int iplot=0; iplot < extra_plot_names.size(); iplot++ ) {
        TString plot_name = extra_plot_names[iplot];
        for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
      }

      if ( extra_muons.size() > 0 || extra_electrons.size() > 0 ) continue;
      label = "Third lepton veto";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
        for (unsigned int inb = 0; inb < nbtag.size(); inb++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              slicedcutflows[slice]->Fill(icutflow, weight * factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
          }
        }
      }
      icutflow++;

      if ( extra_isotracks_lep.size() > 0 || extra_isotracks_chh.size() > 0 ) continue;
      label = "Iso. track veto";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
        for (unsigned int inb = 0; inb < nbtag.size(); inb++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              slicedcutflows[slice]->Fill(icutflow, weight * factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
          }
        }
      }
      icutflow++;

      // Fill histos: sel7
      sel = "sel7";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
        TString plot_name = plot_names[iplot];
        for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
      }

      float btag_prob_DATA=1.0, btag_up_prob_DATA=1.0, btag_dn_prob_DATA=1.0, btag_prob_MC=1.0;
      vector<int> cand_bJets_tight, cand_bJets;
      unsigned int nbtagDeepFlavB = 0;
      for ( unsigned int jet = 0; jet < nt.nJet(); jet++ ) {
        float d_eta_1 = nt.Muon_eta().at(leadingMu_idx) - nt.Jet_eta().at(jet);
        float d_eta_2 = nt.Muon_eta().at(subleadingMu_idx) - nt.Jet_eta().at(jet);
        float d_phi_1 = TVector2::Phi_mpi_pi(nt.Muon_phi().at(leadingMu_idx) - nt.Jet_phi().at(jet));
        float d_phi_2 = TVector2::Phi_mpi_pi(nt.Muon_phi().at(subleadingMu_idx) - nt.Jet_phi().at(jet));
        float dr_jmu1 = TMath::Sqrt( d_eta_1*d_eta_1+d_phi_1*d_phi_1 );
        float dr_jmu2 = TMath::Sqrt( d_eta_2*d_eta_2+d_phi_2*d_phi_2 );
        // Reject jets if they are within dR = 0.4 of the candidate leptons
        if ( dr_jmu1 < 0.4 || dr_jmu2 < 0.4 ) continue;
        if ( nt.Jet_pt().at(jet) > 20 &&
             fabs(nt.Jet_eta().at(jet)) < 2.5 &&
             nt.Jet_jetId().at(jet) > 1 ) {
          bool isBTagMedium = false, isBTagTight = false;
          if ( nt.Jet_btagDeepFlavB().at(jet) > gconf.WP_DeepFlav_medium ) {
            isBTagMedium = true;
            cand_bJets.push_back(jet);
          }
          if ( nt.Jet_btagDeepFlavB().at(jet) > gconf.WP_DeepFlav_tight ) {
            isBTagTight = true;
            cand_bJets_tight.push_back(jet);
          }

          // https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#1a_Event_reweighting_using_scale
          if ( isMC && applyBTagSF ) {
            float pt = nt.Jet_pt().at(jet);
            float eta = nt.Jet_eta().at(jet);
            int flavor = nt.Jet_hadronFlavour().at(jet);

            float eff_tight = get_bTagEff(pt, eta, year, "tight", flavor, "central");
            float eff_med = get_bTagEff(pt, eta, year, "med", flavor, "central");

            float sf_tight =
                flavor == 4 ? btagReaderTight->eval_auto_bounds("central", BTagEntry_v2::FLAV_C, eta, pt) : (
                flavor == 5 ? btagReaderTight->eval_auto_bounds("central", BTagEntry_v2::FLAV_B, eta, pt) :
                              btagReaderTight->eval_auto_bounds("central", BTagEntry_v2::FLAV_UDSG, eta, pt));
            float sf_up_tight =
                flavor == 4 ? btagReaderTight->eval_auto_bounds("up", BTagEntry_v2::FLAV_C, eta, pt) : (
                flavor == 5 ? btagReaderTight->eval_auto_bounds("up", BTagEntry_v2::FLAV_B, eta, pt) :
                              btagReaderTight->eval_auto_bounds("up", BTagEntry_v2::FLAV_UDSG, eta, pt));
            float sf_dn_tight =
                flavor == 4 ? btagReaderTight->eval_auto_bounds("down", BTagEntry_v2::FLAV_C, eta, pt) : (
                flavor == 5 ? btagReaderTight->eval_auto_bounds("down", BTagEntry_v2::FLAV_B, eta, pt) :
                              btagReaderTight->eval_auto_bounds("down", BTagEntry_v2::FLAV_UDSG, eta, pt));
            float sf_med =
                flavor == 4 ? btagReaderMedium->eval_auto_bounds("central", BTagEntry_v2::FLAV_C, eta, pt) : (
                flavor == 5 ? btagReaderMedium->eval_auto_bounds("central", BTagEntry_v2::FLAV_B, eta, pt) :
                              btagReaderMedium->eval_auto_bounds("central", BTagEntry_v2::FLAV_UDSG, eta, pt));
            float sf_up_med =
                flavor == 4 ? btagReaderMedium->eval_auto_bounds("up", BTagEntry_v2::FLAV_C, eta, pt) : (
                flavor == 5 ? btagReaderMedium->eval_auto_bounds("up", BTagEntry_v2::FLAV_B, eta, pt) :
                              btagReaderMedium->eval_auto_bounds("up", BTagEntry_v2::FLAV_UDSG, eta, pt));
            float sf_dn_med =
                flavor == 4 ? btagReaderMedium->eval_auto_bounds("down", BTagEntry_v2::FLAV_C, eta, pt) : (
                flavor == 5 ? btagReaderMedium->eval_auto_bounds("down", BTagEntry_v2::FLAV_B, eta, pt) :
                              btagReaderMedium->eval_auto_bounds("down", BTagEntry_v2::FLAV_UDSG, eta, pt));

            if ( isBTagTight ) {
              btag_prob_MC *= eff_tight;
              if ( varyBTagSFUp )
                btag_up_prob_DATA *= sf_up_tight * eff_tight;
              else if ( varyBTagSFDown )
                btag_dn_prob_DATA *= sf_dn_tight * eff_tight;
              else
                btag_prob_DATA *= sf_tight * eff_tight;
            }
            else if ( isBTagMedium ) {
              btag_prob_MC *= (eff_med - eff_tight);
              if ( varyBTagSFUp )
                btag_up_prob_DATA *= (sf_up_med * eff_med - sf_up_tight * eff_tight);
              else if ( varyBTagSFDown )
                btag_dn_prob_DATA *= (sf_dn_med * eff_med - sf_dn_tight * eff_tight);
              else
                btag_prob_DATA *= (sf_med * eff_med - sf_tight * eff_tight);
            }
            else {
              btag_prob_MC *= (1 - eff_med);
              if ( varyBTagSFUp )
                btag_up_prob_DATA *= (1 - sf_up_med * eff_med);
              else if ( varyBTagSFDown )
                btag_dn_prob_DATA *= (1 - sf_dn_med * eff_med);
              else
                btag_prob_DATA *= (1 - sf_med * eff_med);
            }
          }
        }
      }

      if (cand_bJets_tight.size()>=1) nbtagsel[0] = true;
      else nbtagsel[0] = false;
      if (doNbTagBins) {
        if ( doDYEnriched ) {
          if (cand_bJets_tight.size() == 0) nbtagsel[1] = true;
          else nbtagsel[1] = false;
          if (cand_bJets_tight.size() == 1) nbtagsel[2] = true;
          else nbtagsel[2] = false;
          if (cand_bJets_tight.size() >= 1 && cand_bJets.size() >= 2) nbtagsel[3] = true;
          else nbtagsel[3] = false;
        }
        else {
          if (cand_bJets.size() == 1) nbtagsel[1] = true;
          else nbtagsel[1] = false;
          if (cand_bJets_tight.size() >= 1 && cand_bJets.size() >= 2) nbtagsel[2] = true;
          else nbtagsel[2] = false;
        }
      }

      if ( doDYEnriched && cand_bJets.size() ==0 )  {
        sel = "sel8";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          //if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            unsigned int inb=1;
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet];
              if (mllbinsel[imll] && MuDetRegionsel[iMuDet])
              histos[name]->Fill(variable[plot_name], weight * factor);
            }
          }
        }
      }

      if ( cand_bJets_tight.size() < 1 ) continue;

      if ( isMC && applyBTagSF ) {
        if ( varyBTagSFUp )
          weight *= btag_up_prob_DATA / btag_prob_MC;
        else if ( varyBTagSFDown )
          weight *= btag_dn_prob_DATA / btag_prob_MC;
        else
          weight *= btag_prob_DATA / btag_prob_MC;
      }

      float bjet1_pt = nt.Jet_pt().at(cand_bJets[0]);
      float bjet2_pt = (cand_bJets.size() > 1 ? nt.Jet_pt().at(cand_bJets[1]) : -1.0);
      float bjet1_eta = nt.Jet_eta().at(cand_bJets[0]);
      float bjet2_eta = (cand_bJets.size() > 1 ? nt.Jet_eta().at(cand_bJets[1]) : -1.0);

      // Construct mlb pairs from selected muon pair and candidate b jets
      float minDPhi_b_MET = 1e9, minDPhi_lb_MET = 1e9, minDPhi_llb_MET = 1e9, minDPhi_l_b = 1e9;
      float min_mlb = 1e9;
      float min_mbb = 1e9, max_mbb = -1e9;
      for ( int bjet = 0; bjet < cand_bJets.size(); bjet++ ) {
        //if ( bjet > 2 ) continue;
        auto bjet_p4 = nt.Jet_p4().at(cand_bJets[bjet]);
        float m_mu1_b = (leadingMu_p4+bjet_p4).M();
        if ( m_mu1_b < min_mlb ) {
          min_mlb = m_mu1_b;
        }
        float m_mu2_b = (subleadingMu_p4+bjet_p4).M();
        if ( m_mu2_b < min_mlb ) {
          min_mlb = m_mu2_b;
        }

        float dPhi_b_MET = fabs(TVector2::Phi_mpi_pi(bjet_p4.Phi() - puppimet_phi));
        if ( !(usePuppiMET) )
	  dPhi_b_MET = fabs(TVector2::Phi_mpi_pi(bjet_p4.Phi() - pfmet_phi));
        if ( dPhi_b_MET < minDPhi_b_MET ) minDPhi_b_MET = dPhi_b_MET;

        float dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((leadingMu_p4 + bjet_p4).Phi() - puppimet_phi));
        if ( !(usePuppiMET) )
	  dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((leadingMu_p4 + bjet_p4).Phi() - pfmet_phi));
        if ( dPhi_lb_MET < minDPhi_lb_MET ) minDPhi_lb_MET = dPhi_lb_MET;
        dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((subleadingMu_p4 + bjet_p4).Phi() - puppimet_phi));
	if ( !(usePuppiMET) )
	  dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((subleadingMu_p4 + bjet_p4).Phi() - pfmet_phi));
        if ( dPhi_lb_MET < minDPhi_lb_MET ) minDPhi_lb_MET = dPhi_lb_MET;

        float dPhi_llb_MET = fabs(TVector2::Phi_mpi_pi((selectedPair_p4 + bjet_p4).Phi() - puppimet_phi));
	if ( !(usePuppiMET) )
	  dPhi_llb_MET = fabs(TVector2::Phi_mpi_pi((selectedPair_p4 + bjet_p4).Phi() - pfmet_phi));
        if ( dPhi_llb_MET < minDPhi_llb_MET ) minDPhi_llb_MET = dPhi_llb_MET;

        float dPhi_l_b = fabs(TVector2::Phi_mpi_pi(leadingMu_p4.Phi() - bjet_p4.Phi()));
        if ( dPhi_l_b < minDPhi_l_b ) minDPhi_l_b = dPhi_l_b;
        dPhi_l_b = fabs(TVector2::Phi_mpi_pi(subleadingMu_p4.Phi() - bjet_p4.Phi()));
        if ( dPhi_l_b < minDPhi_l_b ) minDPhi_l_b = dPhi_l_b;

	for ( int bbjet = bjet+1; bbjet < cand_bJets.size(); bbjet++) {
	  auto bbjet_p4 = nt.Jet_p4().at(cand_bJets[bbjet]);
	  float mbb = (bjet_p4+bbjet_p4).M();
	  if ( mbb < min_mbb ) {
	    min_mbb = mbb;
	  }
	  if ( mbb > max_mbb ) {
	    max_mbb = mbb;
	  }
	}

      }

      // Add histos: sel8
      plot_names.push_back("nbtagDeepFlavB");
      variable.insert({"nbtagDeepFlavB", cand_bJets.size()});

      if ( cand_bJets.size() >= 1 ) {

        plot_names.push_back("bjet1_pt");
        variable.insert({"bjet1_pt", bjet1_pt});

        plot_names.push_back("bjet1_eta");
        variable.insert({"bjet1_eta", bjet1_eta});

        plot_names.push_back("min_mlb");
        variable.insert({"min_mlb", min_mlb});

        plot_names.push_back("minDPhi_b_MET");
        variable.insert({"minDPhi_b_MET", minDPhi_b_MET});

        plot_names.push_back("minDPhi_lb_MET");
        variable.insert({"minDPhi_lb_MET", minDPhi_lb_MET});

        plot_names.push_back("minDPhi_llb_MET");
        variable.insert({"minDPhi_llb_MET", minDPhi_llb_MET});

        plot_names.push_back("minDPhi_l_b");
        variable.insert({"minDPhi_l_b", minDPhi_l_b});

        if ( cand_bJets.size() > 1 ) {

          plot_names.push_back("bjet2_pt");
          variable.insert({"bjet2_pt", bjet2_pt});

          plot_names.push_back("bjet2_eta");
          variable.insert({"bjet2_eta", bjet2_eta});

          plot_names.push_back("min_mbb");
          variable.insert({"min_mbb", min_mbb});

          plot_names.push_back("max_mbb");
          variable.insert({"max_mbb", max_mbb});
        }
      }

      // Fill histos: sel8
      label = ">0 b-tag (Tight+Mediums WP)";
      slicedlabel = "";
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            TString tlabel = slicedlabel + nbtagbinlabel[nbtag[inb]];
            if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionsel[iMuDet])
              slicedcutflows[slice]->Fill(icutflow, weight * factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, tlabel);
          }
        }
      }
      icutflow++;

      sel = "sel8";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
        TString plot_name = plot_names[iplot];
        //if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet];
              if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionsel[iMuDet])
              histos[name]->Fill(variable[plot_name], weight * factor);
            }
          }
        }
      }

    if (min_mlb > 175.0){
      label = "min m_{#mu b}>175 GeV";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet];
            if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionsel[iMuDet])
              slicedcutflows[slice]->Fill(icutflow, weight * factor);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
          }
        }
      }

      icutflow++;
      sel = "sel9";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
        TString plot_name = plot_names[iplot];
        //if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet];
              if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionsel[iMuDet])
                histos[name]->Fill(variable[plot_name], weight * factor);
              }
            }
          }
        }
      }
    if (min_mlb < 175.0 && doTTEnriched){
      label = "min m_{#mu b}<175 GeV";
      slicedlabel = label;
      sel = "antisel9";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
        TString plot_name = plot_names[iplot];
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet];
              if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionsel[iMuDet])
                histos[name]->Fill(variable[plot_name], weight * factor);
            }
          }
        }
      }
    }

    } // Event loop

    delete file;

  } // File loop
  bar.finish();

  if ( applyMuonSF ) {
    reset_muonRecoSF();
    reset_muonIDSF();
    reset_muonIsoSF();
  }
  if ( applyTriggerSF ) reset_triggerSF();
  if ( applyBTagSF ) reset_bTagEff();

  if ( removeDataDuplicates )
    cout << "Number of duplicates found: " << nDuplicates << endl;

  // Avoid histograms with unphysical negative bin content (due to negative GEN weights)
  map<TString, TH1F*>::iterator it;
  for ( it = histos.begin(); it != histos.end(); it++ ) {
    for ( unsigned int b=1; b<(it->second)->GetNbinsX()+1; b++ ) { 
      if ( (it->second)->GetBinContent(b)<0.0) {
	(it->second)->SetBinContent(b,0.0);
	(it->second)->SetBinError(b,0.0);
      }
    }
  }

  fout->Write();
  fout->Close();

  return 0;
}
