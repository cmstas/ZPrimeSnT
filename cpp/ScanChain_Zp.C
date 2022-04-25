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
#include "../NanoCORE/XYMETCorrection_withUL17andUL18andUL16.h"
#include "../NanoCORE/ZPrimeTools.cc"

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

bool removeSpikes = true;
bool doMllBins = true;
bool doNbTagBins = true;

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

int ScanChain(TChain *ch, double genEventSumw, TString year, TString process) {

  float factor = 1.0;
  float lumi = 1.0;
  float xsec = 1.0;
  bool isMC = true;

  // SM processes and cross-sections:
  if ( process == "ttbar" )               xsec = 87310.0; // fb
  if ( process == "DY" )                  xsec = 5765400.0; // fb
  if ( process == "ZToMuMu_50_120" )      xsec = 2112904.0; // fb
  if ( process == "ZToMuMu_120_200" )     xsec = 20553.0; // fb
  if ( process == "ZToMuMu_200_400" )     xsec = 2886.0; // fb
  if ( process == "ZToMuMu_400_800" )     xsec = 251.7; // fb
  if ( process == "ZToMuMu_800_1400" )    xsec = 17.07; // fb
  if ( process == "ZToMuMu_1400_2300" )   xsec = 1.366; // fb
  if ( process == "ZToMuMu_2300_3500" )   xsec = 0.08178; // fb
  if ( process == "ZToMuMu_3500_4500" )   xsec = 0.003191; // fb
  if ( process == "ZToMuMu_4500_6000" )   xsec = 0.0002787; // fb
  if ( process == "ZToMuMu_6000_Inf" )    xsec = 0.000009569; // fb
  if ( process == "WW" )                  xsec = 118700.0; // fb 
  if ( process == "WZ" )                  xsec = 47130.0; // fb
  if ( process == "ZZ" )                  xsec = 16523.0; // fb
  if ( process == "tW" )                  xsec = 19550; // fb
  if ( process == "tbarW" )               xsec = 19550; // fb
  if ( process == "TTW" )                 xsec = 204.3; // fb
  if ( process == "TTZ" )                 xsec = 252.9; // fb
  if ( process == "TTHToNonbb" )          xsec = 507.5*(1-0.575); // fb
  if ( process == "TTHTobb" )             xsec = 507.5*0.575; // fb

  // Signal processes and cross-sections:
  if ( year == "2018" )
    {
      lumi = 59.83; // fb-1
      if ( process == "Y3_M100" )     xsec = 0.0211369709127*1000; // fb
      if ( process == "Y3_M200" )     xsec = 0.01597959*1000; // fb
      if ( process == "Y3_M400" )     xsec = 0.00290934734735*1000; // fb
      if ( process == "Y3_M700" )     xsec = 0.000614377054108*1000; // fb
      if ( process == "Y3_M1000" )    xsec = 0.000192622380952*1000; // fb
      if ( process == "Y3_M1500" )    xsec = 3.636946e-05*1000; // fb
      if ( process == "Y3_M2000" )    xsec = 8.253412e-06*1000; // fb
    }

  if ( year == "2017" )       lumi = 41.48; // fb-1
  if ( year == "2016APV" )    lumi = 19.5;  // fb-1
  if ( year == "2016nonAPV" ) lumi = 16.8;  // fb-1

  factor = xsec*lumi/genEventSumw;

  // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
  TFile* fout = new TFile("temp_data/output_"+process+"_"+year+".root", "RECREATE");

  H1(cutflow,20,0,20,"");
  H1(btag_bins,7,0,7,"");
  H1(reg1_matched_btag,5,0,5,"");
  H1(reg2_matched_btag,5,0,5,"");
  H1(reg3_matched_btag,5,0,5,"");
  H1(reg4_matched_btag,5,0,5,"");
  H1(reg5_matched_btag,5,0,5,"");

  // Define histo info maps
  map<TString, int> nbins { };
  map<TString, float> low { };
  map<TString, float> high { };
  map<TString, TString> title { };

  // Define histos
  nbins.insert({"pfmet_pt", 120});
  low.insert({"pfmet_pt", 0});
  high.insert({"pfmet_pt", 600});
  title.insert({"pfmet_pt", "PF MET p_{T} [GeV]"});

  nbins.insert({"pfmet_phi", 65});
  low.insert({"pfmet_phi", -3.25});
  high.insert({"pfmet_phi", 3.25});
  title.insert({"pfmet_phi", "PF MET #phi [GeV]"});

  nbins.insert({"puppimet_pt", 120});
  low.insert({"puppimet_pt", 0});
  high.insert({"puppimet_pt", 600});
  title.insert({"puppimet_pt", "PUPPI MET p_{T} [GeV]"});

  nbins.insert({"puppimet_phi", 65});
  low.insert({"puppimet_phi", -3.25});
  high.insert({"puppimet_phi", 3.25});
  title.insert({"puppimet_phi", "PUPPI MET #phi [GeV]"});

  nbins.insert({"mll_pf", 240});
  low.insert({"mll_pf", 100});
  high.insert({"mll_pf", 2500});
  title.insert({"mll_pf", "m_{ll} [GeV]"});

  nbins.insert({"mu1_pt", 200});
  low.insert({"mu1_pt", 0});
  high.insert({"mu1_pt", 1000});
  title.insert({"mu1_pt", "p_{T} (leading #mu) [GeV]"});

  nbins.insert({"mu2_pt", 200});
  low.insert({"mu2_pt", 0});
  high.insert({"mu2_pt", 1000});
  title.insert({"mu2_pt", "p_{T} (subleading #mu) [GeV]"});

  nbins.insert({"mu1_eta", 60});
  low.insert({"mu1_eta", -3});
  high.insert({"mu1_eta", 3});
  title.insert({"mu1_eta", "#eta (leading #mu)"});

  nbins.insert({"mu2_eta", 60});
  low.insert({"mu2_eta", -3});
  high.insert({"mu2_eta", 3});
  title.insert({"mu2_eta", "#eta (subleading #mu)"});

  nbins.insert({"dPhi_ll", 32});
  low.insert({"dPhi_ll", 0});
  high.insert({"dPhi_ll", 3.2});
  title.insert({"dPhi_ll", "min #Delta#phi(ll)"});

  nbins.insert({"mu1_trkRelIso", 50});
  low.insert({"mu1_trkRelIso", 0});
  high.insert({"mu1_trkRelIso", 0.5});
  title.insert({"mu1_trkRelIso", "Track iso./p_{T} (leading #mu)"});

  nbins.insert({"mu2_trkRelIso", 50});
  low.insert({"mu2_trkRelIso", 0});
  high.insert({"mu2_trkRelIso", 0.5});
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
  low.insert({"mu3_pt", 0});
  high.insert({"mu3_pt", 1000});
  title.insert({"mu3_pt", "p_{T} (third #mu) [GeV]"});

  nbins.insert({"mu3_eta", 60});
  low.insert({"mu3_eta", -3});
  high.insert({"mu3_eta", 3});
  title.insert({"mu3_eta", "#eta (third #mu)"});

  nbins.insert({"mu3_trkRelIso", 10});
  low.insert({"mu3_trkRelIso", 0});
  high.insert({"mu3_trkRelIso", 0.1});
  title.insert({"mu3_trkRelIso", "Track iso./p_{T} (third #mu)"});

  nbins.insert({"nExtra_electrons", 6});
  low.insert({"nExtra_electrons", 0});
  high.insert({"nExtra_electrons", 6});
  title.insert({"nExtra_electrons", "Number of electrons"});

  nbins.insert({"ele_extra_pt", 200});
  low.insert({"ele_extra_pt", 0});
  high.insert({"ele_extra_pt", 1000});
  title.insert({"ele_extra_pt", "p_{T} (extra electron) [GeV]"});

  nbins.insert({"ele_extra_eta", 60});
  low.insert({"ele_extra_eta", -3});
  high.insert({"ele_extra_eta", 3});
  title.insert({"ele_extra_eta", "#eta (extra electron)"});

  nbins.insert({"ele_extra_miniPFRelIso", 10});
  low.insert({"ele_extra_miniPFRelIso", 0});
  high.insert({"ele_extra_miniPFRelIso", 0.1});
  title.insert({"ele_extra_miniPFRelIso", "PF mini-iso./p_{T} (extra electron)"});

  nbins.insert({"nExtra_lepIsoTracks", 6});
  low.insert({"nExtra_lepIsoTracks", 0});
  high.insert({"nExtra_lepIsoTracks", 6});
  title.insert({"nExtra_lepIsoTracks", "Number of (additional) lepton (e/#mu) PF candidates"});

  nbins.insert({"lepIsoTrack_extra_pt", 200});
  low.insert({"lepIsoTrack_extra_pt", 0});
  high.insert({"lepIsoTrack_extra_pt", 1000});
  title.insert({"lepIsoTrack_extra_pt", "p_{T} (extra lepton isoTrack) [GeV]"});

  nbins.insert({"lepIsoTrack_extra_eta", 60});
  low.insert({"lepIsoTrack_extra_eta", -3});
  high.insert({"lepIsoTrack_extra_eta", 3});
  title.insert({"lepIsoTrack_extra_eta", "#eta (extra lepton isoTrack)"});

  nbins.insert({"lepIsoTrack_extra_PFRelIsoChg", 10});
  low.insert({"lepIsoTrack_extra_PFRelIsoChg", 0});
  high.insert({"lepIsoTrack_extra_PFRelIsoChg", 0.1});
  title.insert({"lepIsoTrack_extra_PFRelIsoChg", "PF charged iso./p_{T} (extra lepton isoTrack)"});

  nbins.insert({"nExtra_chhIsoTracks", 6});
  low.insert({"nExtra_chhIsoTracks", 0});
  high.insert({"nExtra_chhIsoTracks", 6});
  title.insert({"nExtra_chhIsoTracks", "Number of (additional) charged hadron PF candidates"});

  nbins.insert({"chhIsoTrack_extra_pt", 200});
  low.insert({"chhIsoTrack_extra_pt", 0});
  high.insert({"chhIsoTrack_extra_pt", 1000});
  title.insert({"chhIsoTrack_extra_pt", "p_{T} (extra ch. hadron isoTrack) [GeV]"});

  nbins.insert({"chhIsoTrack_extra_eta", 60});
  low.insert({"chhIsoTrack_extra_eta", -3});
  high.insert({"chhIsoTrack_extra_eta", 3});
  title.insert({"chhIsoTrack_extra_eta", "#eta (extra ch. hadron isoTrack)"});

  nbins.insert({"chhIsoTrack_extra_PFRelIsoChg", 10});
  low.insert({"chhIsoTrack_extra_PFRelIsoChg", 0});
  high.insert({"chhIsoTrack_extra_PFRelIsoChg", 0.1});
  title.insert({"chhIsoTrack_extra_PFRelIsoChg", "PF charged iso./p_{T} (extra ch. hadron isoTrack)"});

  nbins.insert({"nbtagDeepFlavB", 5});
  low.insert({"nbtagDeepFlavB", 0});
  high.insert({"nbtagDeepFlavB", 5});
  title.insert({"nbtagDeepFlavB", "Number of b-tags (medium WP)"});

  nbins.insert({"bjet1_pt", 200});
  low.insert({"bjet1_pt", 0});
  high.insert({"bjet1_pt", 1000});
  title.insert({"bjet1_pt", "p_{T} (leading b-tagged jet) [GeV]"});

  nbins.insert({"bjet1_eta", 60});
  low.insert({"bjet1_eta", -3});
  high.insert({"bjet1_eta", 3});
  title.insert({"bjet1_eta", "#eta (leading b-tagged jet) [GeV]"});

  nbins.insert({"bjet2_pt", 200});
  low.insert({"bjet2_pt", 0});
  high.insert({"bjet2_pt", 1000});
  title.insert({"bjet2_pt", "p_{T} (subleading b-tagged jet) [GeV]"});

  nbins.insert({"bjet2_eta", 60});
  low.insert({"bjet2_eta", -3});
  high.insert({"bjet2_eta", 3});
  title.insert({"bjet2_eta", "#eta (subleading b-tagged jet) [GeV]"});

  /*
  nbins.insert({"n_matched_med_bjets",5});
  low.insert({"n_matched_med_bjets", 0});
  high.insert({"n_matched_med_bjets", 5});
  title.insert({"n_matched_med_bjets", "Number of matched medium candidate bjets"});

  nbins.insert({"n_matched_tight_bjets",5});
  low.insert({"n_matched_tight_bjets", 0});
  high.insert({"n_matched_tight_bjets", 5});
  title.insert({"n_matched_tight_bjets", "Number of matched tight candidate bjets"});
 
  nbins.insert({"pt_leading_matched_med_bjet",200});
  low.insert({"pt_leading_matched_med_bjet", 0});
  high.insert({"pt_leading_matched_med_bjet", 1000});
  title.insert({"pt_leading_matched_med_bjet", "p_{T} (leading matched medium candidate bjet) [GeV]"});

  nbins.insert({"pt_leading_matched_tight_bjet",200});
  low.insert({"pt_leading_matched_tight_bjet", 0});
  high.insert({"pt_leading_matched_tight_bjet", 1000});
  title.insert({"pt_leading_matched_tight_bjet", "p_{T} (leading matched tight candidate bjet) [GeV]"});

  nbins.insert({"pt_subleading_matched_med_bjet",200});
  low.insert({"pt_subleading_matched_med_bjet", 0});
  high.insert({"pt_subleading_matched_med_bjet", 1000});
  title.insert({"pt_subleading_matched_med_bjet", "p_{T} (subleading matched medium candidate bjet) [GeV]"});

  nbins.insert({"pt_subleading_matched_tight_bjet",200});
  low.insert({"pt_subleading_matched_tight_bjet", 0});
  high.insert({"pt_subleading_matched_tight_bjet", 1000});
  title.insert({"pt_subleading_matched_tight_bjet", "p_{T} (subleading matched tight candidate bjet) [GeV]"});
 
  nbins.insert({"eta_leading_matched_med_bjet", 60});
  low.insert({"eta_leading_matched_med_bjet", -3});
  high.insert({"eta_leading_matched_med_bjet", 3});
  title.insert({"eta_leading_matched_med_bjet", "#eta (leading matched medium candidate bjet)"});

  nbins.insert({"eta_leading_matched_tight_bjet", 60});
  low.insert({"eta_leading_matched_tight_bjet", -3});
  high.insert({"eta_leading_matched_tight_bjet", 3});
  title.insert({"eta_leading_matched_tight_bjet", "#eta (leading matched tight candidate bjet)"});

  nbins.insert({"eta_subleading_matched_med_bjet", 60});
  low.insert({"eta_subleading_matched_med_bjet", -3});
  high.insert({"eta_subleading_matched_med_bjet", 3});
  title.insert({"eta_subleading_matched_med_bjet", "#eta (subleading matched medium candidate bjet)"});

  nbins.insert({"eta_subleading_matched_tight_bjet", 60});
  low.insert({"eta_subleading_matched_tight_bjet", -3});
  high.insert({"eta_subleading_matched_tight_bjet", 3});
  title.insert({"eta_subleading_matched_tight_bjet", "#eta (subleading matched tight candidate bjet)"});
  
  nbins.insert({"phi_leading_matched_med_bjet", 65});
  low.insert({"phi_leading_matched_med_bjet", -3.25});
  high.insert({"phi_leading_matched_med_bjet", 3.25});
  title.insert({"phi_leading_matched_med_bjet", "#phi (leading matched medium candidate bjet)"});

  nbins.insert({"phi_leading_matched_tight_bjet", 65});
  low.insert({"phi_leading_matched_tight_bjet", -3.25});
  high.insert({"phi_leading_matched_tight_bjet", 3.25});
  title.insert({"phi_leading_matched_tight_bjet", "#phi (leading matched tight candidate bjet)"});

  nbins.insert({"phi_subleading_matched_med_bjet", 65});
  low.insert({"phi_subleading_matched_med_bjet", -3.25});
  high.insert({"phi_subleading_matched_med_bjet", 3.25});
  title.insert({"phi_subleading_matched_med_bjet", "#phi (subleading matched medium candidate bjet)"});

  nbins.insert({"phi_subleading_matched_tight_bjet", 65});
  low.insert({"phi_subleading_matched_tight_bjet", -3.25});
  high.insert({"phi_subleading_matched_tight_bjet", 3.25});
  title.insert({"phi_subleading_matched_tight_bjet", "#phi (subleading matched tight candidate bjet)"});
  */

  nbins.insert({"min_mlb", 200});
  low.insert({"min_mlb", 0});
  high.insert({"min_mlb", 2000});
  title.insert({"min_mlb", "min m_{lb} [GeV]"});

  nbins.insert({"min_mbb", 200});
  low.insert({"min_mbb", 0});
  high.insert({"min_mbb", 2000});
  title.insert({"min_mbb", "min m_{bb} [GeV]"});

  nbins.insert({"max_mbb", 200});
  low.insert({"max_mbb", 0});
  high.insert({"max_mbb", 2000});
  title.insert({"max_mbb", "max m_{bb} [GeV]"});

  nbins.insert({"minDPhi_b_MET", 32});
  low.insert({"minDPhi_b_MET", 0});
  high.insert({"minDPhi_b_MET", 3.2});
  title.insert({"minDPhi_b_MET", "min #Delta#phi(b,MET)"});

  nbins.insert({"minDPhi_lb_MET", 32});
  low.insert({"minDPhi_lb_MET", 0});
  high.insert({"minDPhi_lb_MET", 3.2});
  title.insert({"minDPhi_lb_MET", "min #Delta#phi(lb,MET)"});

  nbins.insert({"minDPhi_llb_MET", 32});
  low.insert({"minDPhi_llb_MET", 0});
  high.insert({"minDPhi_llb_MET", 3.2});
  title.insert({"minDPhi_llb_MET", "min #Delta#phi(llb,MET)"});

  nbins.insert({"dPhi_ll_MET", 32});
  low.insert({"dPhi_ll_MET", 0});
  high.insert({"dPhi_ll_MET", 3.2});
  title.insert({"dPhi_ll_MET", "min #Delta#phi(ll,MET)"});


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
    nbtag.push_back("nBTag1");
    nbtag.push_back("nBTag2p");
  }
  const int nBTagBins = nbtag.size();
  bool nbtagsel[nBTagBins];

  map<TString, TString> nbtagbinlabel;
  nbtagbinlabel["nBTag1p"]="N_{b-tag}#geq 1 (p_{T}>20 GeV, medium WP)";
  nbtagbinlabel["nBTag1"]="N_{b-tag}= 1 (p_{T}>20 GeV, medium WP)";
  nbtagbinlabel["nBTag2p"]="N_{b-tag}#geq 2 (p_{T}>20 GeV, medium WP)";

  // Define cutflow histograms in bins of mll and number of b-tags
  map<TString, TH1F*> slicedcutflows;
  for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
    for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
      TString plot_name = TString("cutflow_")+mllbin[imll]+TString("_")+nbtag[inb];
      TString slice = mllbin[imll]+TString("_")+nbtag[inb];
      HTemp(plot_name,20,0,20,"");
      slicedcutflows[slice] = h_temp;
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
  selection.push_back("sel6"); // No extra lepton / isoTrack
  selection.push_back("sel7"); // NbTag >= 1 (medium WP)
  selection.push_back("sel8"); // Mmumu > 150 GeV
  selection.push_back("sel9"); // minMlb > 175 GeV

  vector<TString> plot_names = { };
  vector<TString> plot_names_2b = { };
  plot_names.push_back("pfmet_pt");
  plot_names.push_back("pfmet_phi");
  plot_names.push_back("puppimet_pt");
  plot_names.push_back("puppimet_phi");
  map<TString, TH1F*> histos;
  int nExtraHistos = 0;
  for ( unsigned int isel=0; isel < selection.size(); isel++ ) {
    if (isel==5) {
      plot_names.push_back("mll_pf");
      plot_names.push_back("mu1_pt");
      plot_names.push_back("mu2_pt");
      plot_names.push_back("mu1_eta");
      plot_names.push_back("mu2_eta");
      plot_names.push_back("dPhi_ll");
      plot_names.push_back("mu1_trkRelIso");
      plot_names.push_back("mu2_trkRelIso");
      plot_names.push_back("nCand_Muons");
      // Add also extra plots before third lepton/isotrack veto
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
    if (isel==6) {
      // Remove plots added for thid lepton/isotrack veto
      for (int e=0; e<nExtraHistos; ++e)
	plot_names.pop_back();
    }
    if (isel==7) {
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
      plot_names.push_back("dPhi_ll_MET");
      plot_names.push_back("n_matched_med_bjets");
      plot_names.push_back("n_matched_tight_bjets");
      plot_names.push_back("pt_leading_matched_med_bjet");
      plot_names.push_back("pt_leading_matched_tight_bjet"); 
      plot_names.push_back("pt_subleading_matched_med_bjet");
      plot_names.push_back("pt_subleading_matched_tight_bjet"); 
      plot_names.push_back("eta_leading_matched_med_bjet");
      plot_names.push_back("eta_leading_matched_tight_bjet");
      plot_names.push_back("eta_subleading_matched_med_bjet");
      plot_names.push_back("eta_subleading_matched_tight_bjet");
      plot_names.push_back("phi_leading_matched_med_bjet");
      plot_names.push_back("phi_leading_matched_tight_bjet");
      plot_names.push_back("phi_subleading_matched_med_bjet");
      plot_names.push_back("phi_subleading_matched_tight_bjet");      
      //
      plot_names_2b.push_back("bjet2_pt");
      plot_names_2b.push_back("bjet2_eta");
      plot_names_2b.push_back("min_mbb");
      plot_names_2b.push_back("max_mbb");
    }
    for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
      if(isel<5) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+selection[isel]+"_"+mllbin[0]+"_"+nbtag[0];
	HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
	histos[name] = h_temp;
      }
      else if(isel>=5 && isel<7) {
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  TString plot_name = plot_names[iplot];
	  TString name = plot_name+"_"+selection[isel]+"_"+mllbin[imll]+"_"+nbtag[0];
	  HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
	  histos[name] = h_temp;
	}
      }
      else if(isel>=7) {
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	    TString plot_name = plot_names[iplot];
	    if ( std::find(plot_names_2b.begin(), plot_names_2b.end(), plot_name) != plot_names_2b.end() && nbtag[inb]=="nBTag1" )
	      continue;
	    TString name = plot_name+"_"+selection[isel]+"_"+mllbin[imll]+"_"+nbtag[inb];
	    HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
	    histos[name] = h_temp;
	  }
	}
      }
    }
  }

  int nEventsTotal = 0;
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
    h_cutflow->Fill(icutflow,xsec*lumi);
    h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
    for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
      for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	TString slice = mllbin[imll]+"_"+nbtag[inb];
	slicedcutflows[slice]->Fill(icutflow,xsec*lumi);
	slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
      }
    }

    for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

      nt.GetEntry(event);
      tree->LoadTree(event);

      float weight = genWeight();
      if(removeSpikes && weight*factor>1e2) continue;

      int runnb = nt.run();
      int npv = nt.PV_npvs();

      // MET xy correction: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections#xy_Shift_Correction_MET_phi_modu
      // METXYCorr_Met_MetPhi(double uncormet, double uncormet_phi, int runnb, TString year, bool isMC, int npv, bool isUL =false,bool ispuppi=false)
      std::pair<double,double> pfmet = METXYCorr_Met_MetPhi(nt.MET_pt(), nt.MET_phi(), runnb, year, isMC, npv, true, false);
      double pfmet_pt  = pfmet.first;
      double pfmet_phi = pfmet.second;
      std::pair<double,double> puppimet = METXYCorr_Met_MetPhi(nt.PuppiMET_pt(), nt.PuppiMET_phi(), runnb, year, isMC, npv, true, true);
      double puppimet_pt  = puppimet.first;
      double puppimet_phi = puppimet.second;

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


      // Define vector of muon candidate indices here.....
      vector<int> cand_muons_pf_id;
      vector<int> cand_muons_pf_id_and_pteta;
      vector<int> cand_muons_pf;
      //vector<int> cand_muons_tunep;

      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);

      // After skim
      icutflow = 1;
      label = "After skim";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;

      // HLT selection
      if ( (year=="2016nonAPV" || year=="2016APV") && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
      if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;
      label = "HLT";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;

      // Number of good primary vertices
      if ( nt.PV_npvsGood() < 1 ) continue;
      // Fill histos: sel0
      label = ">0 good PVs";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      TString sel = "sel0";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0]+"_"+nbtag[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      // Single muon selection loop
      int nMu_id = 0;
      int nMu_pt = 0;
      int nMu_iso = 0;
      for ( unsigned int mu = 0; mu < nt.nMuon(); mu++ ) {
        bool mu_trk_and_global = ( nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu) );
        bool mu_id = ( nt.Muon_highPtId().at(mu) >= 2 );
        bool mu_pt_pf = ( nt.Muon_pt().at(mu) > 53 && fabs(nt.Muon_eta().at(mu)) < 2.4 );
        bool mu_relIso = ( nt.Muon_tkRelIso().at(mu) < 0.1 );
	      
        if ( mu_trk_and_global && mu_id ) {
          nMu_id++;
          cand_muons_pf_id.push_back(mu);
          if ( mu_pt_pf ) {
            nMu_pt++;
            cand_muons_pf_id_and_pteta.push_back(mu);
            if ( mu_relIso ) {
              nMu_iso++;
              cand_muons_pf.push_back(mu);
            }
          }
        }
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
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      sel = "sel1";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0]+"_"+nbtag[0];
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
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      sel = "sel2";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0]+"_"+nbtag[0];
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
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      sel = "sel3";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0]+"_"+nbtag[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      // Trigger object finding
      bool atLeastSelectedMu_matchedToTrigObj = false;
      vector<bool> muMatchedToTrigObj;
      for ( int n = 0; n < nt.nTrigObj(); n++ ) {
        if ( abs(nt.TrigObj_id().at(n)) != 13 ) continue;
        if ( !(nt.TrigObj_filterBits().at(n) & 8) ) continue;
        for ( auto i_cand_muons_pf : cand_muons_pf ) {
          float deta = nt.TrigObj_eta().at(n) - nt.Muon_eta().at(i_cand_muons_pf);
          float dphi = TVector2::Phi_mpi_pi(nt.TrigObj_phi().at(n) - nt.Muon_phi().at(i_cand_muons_pf));
          float dr = TMath::Sqrt( deta*deta+dphi*dphi );
          if ( dr < 0.02 ) {
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
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      sel = "sel4";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	TString name = plot_name+"_"+sel+"_"+mllbin[0]+"_"+nbtag[0];
	histos[name]->Fill(variable[plot_name],weight*factor);
      }

      int leadingMu_idx = -1, subleadingMu_idx = -1;
      float selectedPair_M = -1.0;
      bool Zboson = false;
      for ( unsigned int i=0; i<cand_muons_pf.size(); i++ ) {
        TVector3 mu_1(nt.Muon_p4().at(cand_muons_pf[i]).Px(),nt.Muon_p4().at(cand_muons_pf[i]).Py(),nt.Muon_p4().at(cand_muons_pf[i]).Pz());
        for ( unsigned int j=i+1; j<cand_muons_pf.size(); j++ ) {
          if ( nt.Muon_pdgId().at(cand_muons_pf[i]) + nt.Muon_pdgId().at(cand_muons_pf[j]) != 0 ) continue; // Opposite sign, same flavor
          if ( !(muMatchedToTrigObj[i] || muMatchedToTrigObj[j]) ) continue; // At least one muon in pair matched to HLT
          TVector3 mu_2(nt.Muon_p4().at(cand_muons_pf[j]).Px(),nt.Muon_p4().at(cand_muons_pf[j]).Py(),nt.Muon_p4().at(cand_muons_pf[j]).Pz());
          if ( !(IsSeparated( mu_1,mu_2 ) ) ) continue; // 3D angle between muons > pi - 0.02
          float m_ll_pf = (nt.Muon_p4().at(cand_muons_pf[i])+nt.Muon_p4().at(cand_muons_pf[j])).M();
          if ( m_ll_pf > 70 && m_ll_pf < 110 ) { // Reject event if it contains dimuon pair compatible with Z mass
            Zboson = true;
            continue;
          }
          if ( selectedPair_M < 0.0 ) {
            leadingMu_idx = cand_muons_pf[i];
            subleadingMu_idx = cand_muons_pf[j];
            selectedPair_M = m_ll_pf;
          }
        }
        if ( Zboson ) break;
      }
      if ( selectedPair_M < 0.0 || Zboson ) continue;
      
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

      // Add histos: sel5
      plot_names.push_back("mll_pf");
      variable.insert({"mll_pf", selectedPair_M});

      plot_names.push_back("mu1_pt");
      variable.insert({"mu1_pt", nt.Muon_pt().at(leadingMu_idx)});

      plot_names.push_back("mu2_pt");
      variable.insert({"mu2_pt", nt.Muon_pt().at(subleadingMu_idx)});

      plot_names.push_back("mu1_eta");
      variable.insert({"mu1_eta", nt.Muon_eta().at(leadingMu_idx)});

      plot_names.push_back("mu2_eta");
      variable.insert({"mu2_eta", nt.Muon_eta().at(subleadingMu_idx)});

      plot_names.push_back("dPhi_ll");
      variable.insert({"dPhi_ll", fabs( TVector2::Phi_mpi_pi( nt.Muon_phi().at(leadingMu_idx) - nt.Muon_phi().at(subleadingMu_idx) ) )});

      plot_names.push_back("mu1_trkRelIso");
      variable.insert({"mu1_trkRelIso", nt.Muon_tkRelIso().at(leadingMu_idx)});

      plot_names.push_back("mu2_trkRelIso");
      variable.insert({"mu2_trkRelIso", nt.Muon_tkRelIso().at(subleadingMu_idx)});

      plot_names.push_back("nCand_Muons");
      variable.insert({"nCand_Muons", cand_muons_pf.size()});

      // Fill histos: sel5
      label = "Muon pair (OS, !Z)";
      slicedlabel = "Muon pair (OS), ";
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  TString tlabel = slicedlabel+mllbinlabel[mllbin[imll]];
	  if ( mllbinsel[imll] )
	    slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,tlabel);
	}
      }
      icutflow++;
      // Look for a third isolated lepton and then veto the event if it is found
      // Muons (using same ID and isolation as for selected muons, to avoid scale factor combinatorics)
      vector<int> extra_muons;
      for ( int i = 0; i < nt.nMuon(); i++ ) {
        if ( nt.Muon_pt().at(i) > 10. && 
	     fabs(nt.Muon_eta().at(i)) < 2.4 &&
	     nt.Muon_highPtId().at(i) >= 2 && 
	     nt.Muon_tkRelIso().at(i) < 0.1 &&
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
          for ( auto i_cand_muons_pf : cand_muons_pf ) {
            if (i_cand_muons_pf!=leadingMu_idx && i_cand_muons_pf!=subleadingMu_idx) continue;
            float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons_pf);
            float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons_pf));
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
          for ( auto i_cand_muons_pf : cand_muons_pf ) {
            if (i_cand_muons_pf!=leadingMu_idx && i_cand_muons_pf!=subleadingMu_idx) continue;
            float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons_pf);
            float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons_pf));
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
	extra_variable.insert({"mu3_pt", nt.Muon_pt().at(extra_muons[0])});

	extra_plot_names.push_back("mu3_eta");
	extra_variable.insert({"mu3_eta", nt.Muon_eta().at(extra_muons[0])});

	extra_plot_names.push_back("mu3_trkRelIso");
	extra_variable.insert({"mu3_trkRelIso", nt.Muon_tkRelIso().at(extra_muons[0])});
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

      // Fill standard histos for sel5
      sel = "sel5";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  TString name = plot_name+"_"+sel+"_"+mllbin[imll]+"_"+nbtag[0];
	  if ( mllbinsel[imll] )
	    histos[name]->Fill(variable[plot_name],weight*factor);
	}
      }
      // Now fill extra histos for sel5 (before third lepton/isotrack veto)
      for ( unsigned int iplot=0; iplot < extra_plot_names.size(); iplot++ ) {
	TString plot_name = extra_plot_names[iplot];
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  TString name = plot_name+"_"+sel+= "_"+mllbin[imll]+"_"+nbtag[0];
	  if ( mllbinsel[imll] )
	    histos[name]->Fill(extra_variable[plot_name],weight*factor);
	}
      }

      if ( extra_muons.size() > 0 || extra_electrons.size() > 0 ) continue;
      label = "Third lepton veto";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  if ( mllbinsel[imll] )
	    slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;

      if ( extra_isotracks_lep.size() > 0 || extra_isotracks_chh.size() > 0 ) continue;
      label = "IsoTrack veto";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  if ( mllbinsel[imll] )
	    slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;

      // Fill histos: sel6
      sel = "sel6";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  TString name = plot_name+"_"+sel+= "_"+mllbin[imll]+"_"+nbtag[0];
	  if ( mllbinsel[imll] )
	    histos[name]->Fill(variable[plot_name],weight*factor);
	}
      }

      vector<int> cand_bJets;
      vector<int> cand_tight_bJets;
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
	     fabs(nt.Jet_eta().at(jet))<2.5 && 
	     nt.Jet_jetId().at(jet) > 0 && 
	     nt.Jet_btagDeepFlavB().at(jet) > 0.2783 ) { // Using medium WP for 2018 (0.0490 for loose, 0.7100 for tight)
	  cand_bJets.push_back(jet);  // Medium DeepJet WP
	}
        if ( nt.Jet_pt().at(jet) > 20 &&
	     nt.Jet_jetId().at(jet) > 0 && 
	     nt.Jet_btagDeepFlavB().at(jet) > 0.7100 && 
	     fabs(nt.Jet_eta().at(jet)) < 2.5) {
          cand_tight_bJets.push_back(jet);
        }
      }

      
      if ( cand_bJets.size() < 1 ) continue;

      /*

      // Perform b jet matching after selecting medium b jets
      vector<int> matched_med_bjets;
      for ( int i = 0; i < cand_bJets.size(); i++ ){
            bool med_pF = ( abs(nt.Jet_partonFlavour().at(cand_bJets[i])) == 5 );
            bool med_hF = ( abs(nt.Jet_partonFlavour().at(cand_bJets[i])) == 5 );
            if ( med_hF && med_pF ){
                 matched_med_bjets.push_back(i);
            }
      }


      // Perform b jet matching after selecting tight b jets
      vector<int> matched_tight_bjets;
      for ( int i = 0; i < cand_tight_bJets.size(); i++ ){
            bool tight_pF = ( abs(nt.Jet_partonFlavour().at(cand_tight_bJets[i])) == 5 );
            bool tight_hF = ( abs(nt.Jet_partonFlavour().at(cand_tight_bJets[i])) == 5 );
            if ( tight_hF && tight_pF ){
                 matched_tight_bjets.push_back(i);
            }
      }

      */

      float bjet1_pt = nt.Jet_pt().at(cand_bJets[0]);
      float bjet2_pt = (cand_bJets.size() > 1 ? nt.Jet_pt().at(cand_bJets[1]) : -1.0);
      float bjet1_eta = nt.Jet_eta().at(cand_bJets[0]);
      float bjet2_eta = (cand_bJets.size() > 1 ? nt.Jet_eta().at(cand_bJets[1]) : -1.0);

      // Construct mlb pairs from selected muon pair and candidate b jets
      auto leadingMu_p4 = nt.Muon_p4().at(leadingMu_idx);
      auto subleadingMu_p4 = nt.Muon_p4().at(subleadingMu_idx);
      auto selectedPair_p4 = leadingMu_p4 + subleadingMu_p4;
      float minDPhi_b_MET = 1e9, minDPhi_lb_MET = 1e9, minDPhi_llb_MET = 1e9;
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

        float dPhi_b_MET = fabs(TVector2::Phi_mpi_pi(bjet_p4.Phi() - nt.MET_phi()));
        if ( dPhi_b_MET < minDPhi_b_MET ) minDPhi_b_MET = dPhi_b_MET;
        dPhi_b_MET = fabs(TVector2::Phi_mpi_pi(bjet_p4.Phi() - nt.MET_phi()));
        if ( dPhi_b_MET < minDPhi_b_MET ) minDPhi_b_MET = dPhi_b_MET;

        float dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((leadingMu_p4 + bjet_p4).Phi() - nt.MET_phi()));
        if ( dPhi_lb_MET < minDPhi_lb_MET ) minDPhi_lb_MET = dPhi_lb_MET;
        dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((subleadingMu_p4 + bjet_p4).Phi() - nt.MET_phi()));
        if ( dPhi_lb_MET < minDPhi_lb_MET ) minDPhi_lb_MET = dPhi_lb_MET;

        float dPhi_llb_MET = fabs(TVector2::Phi_mpi_pi((selectedPair_p4 + bjet_p4).Phi() - nt.MET_phi()));
        if ( dPhi_llb_MET < minDPhi_llb_MET ) minDPhi_llb_MET = dPhi_llb_MET;

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
      float dPhi_ll_MET = fabs(TVector2::Phi_mpi_pi(selectedPair_p4.Phi() - nt.MET_phi()));

      // Add histos: sel7
      plot_names.push_back("nbtagDeepFlavB");
      variable.insert({"nbtagDeepFlavB", cand_bJets.size()});

      plot_names.push_back("bjet1_pt");
      variable.insert({"bjet1_pt", bjet1_pt});

      plot_names.push_back("bjet1_eta");
      variable.insert({"bjet1_eta", bjet1_eta});

      plot_names.push_back("nbtagDeepFlavB_tight");
      variable.insert({"nbtagDeepFlavB_tight", cand_tight_bJets.size()});
      
      
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


      // Define the four regions of interest: 1 Medium b jet, >1 medium b jet, 1 tight b jet + no other jets, 1 tight b jet + >0 medium b jets, 2 tight b jets.... 


      // Region 1: 1 medium b jet
      if ( cand_bJets.size() == 1 && cand_tight_bJets.size() == 0 ){
           h_btag_bins->Fill(1,weight*factor);
           if ( abs(nt.Jet_hadronFlavour().at(cand_bJets[0])) == 5 && abs(nt.Jet_partonFlavour().at(cand_bJets[0])) == 5 ){
	        h_reg1_matched_btag->Fill(1,weight*factor); 	
	   }    
           else{
                h_reg1_matched_btag->Fill(2,weight*factor);
           }   
      }
      else if ( cand_bJets.size() == 2 && cand_tight_bJets.size() == 0 ){  // Region 2: 2 medium b jets
           h_btag_bins->Fill(2,weight*factor);
           bool reg2_first_matched = ( abs(nt.Jet_partonFlavour().at(cand_bJets[0])) == 5 && abs(nt.Jet_hadronFlavour().at(cand_bJets[0])) == 5);
           bool reg2_second_matched = ( abs(nt.Jet_partonFlavour().at(cand_bJets[1])) == 5 && abs(nt.Jet_hadronFlavour().at(cand_bJets[1])) == 5);
           if ( reg2_first_matched && reg2_second_matched ){
                h_reg2_matched_btag->Fill(1,weight*factor);
           }
           else if( reg2_first_matched && !reg2_second_matched ){
                h_reg2_matched_btag->Fill(2,weight*factor);
           }
           else if( !reg2_first_matched && reg2_second_matched ){
                h_reg2_matched_btag->Fill(3,weight*factor);
           }
           else{
                h_reg2_matched_btag->Fill(4,weight*factor);
           }
      }
      else if ( cand_tight_bJets.size() == 1 && cand_bJets.size() == 1 ){  // Region 3: 1 tight b, no other jets
           h_btag_bins->Fill(3,weight*factor);
           if ( abs(nt.Jet_hadronFlavour().at(cand_tight_bJets[0])) == 5 && abs(nt.Jet_partonFlavour().at(cand_tight_bJets[0])) == 5 ){
                h_reg3_matched_btag->Fill(1,weight*factor);
           }
           else{
                h_reg3_matched_btag->Fill(2,weight*factor);
           }     
      }
      else if ( cand_tight_bJets.size() == 1 && cand_bJets.size() == 2 ){  // Region 4: 1 tight b + 1 medium b
           h_btag_bins->Fill(4,weight*factor);
           bool reg4_tight_matched = ( abs(nt.Jet_hadronFlavour().at(cand_tight_bJets[0])) == 5 && abs(nt.Jet_partonFlavour().at(cand_tight_bJets[0])) == 5 );
           // Determine which medium b tag is matched to the tight b tag
           bool reg4_medium_matched;
           if ( cand_tight_bJets[0] == cand_bJets[0] ){
                reg4_medium_matched = ( abs(nt.Jet_hadronFlavour().at(cand_bJets[1])) == 5 && abs(nt.Jet_partonFlavour().at(cand_bJets[1])) == 5 );
           }
           else{
                reg4_medium_matched = ( abs(nt.Jet_hadronFlavour().at(cand_bJets[0])) == 5 && abs(nt.Jet_partonFlavour().at(cand_bJets[0])) == 5 ); 
           }

           
           if ( reg4_tight_matched && reg4_medium_matched ){
                h_reg4_matched_btag->Fill(1,weight*factor);
	   }    
           else if ( reg4_tight_matched && !reg4_medium_matched ){
                h_reg4_matched_btag->Fill(2,weight*factor);
           }
           else if ( !reg4_tight_matched && reg4_medium_matched ){
                h_reg4_matched_btag->Fill(3,weight*factor);
           }
           else{
                h_reg4_matched_btag->Fill(4,weight*factor);
           }

      }
      else if ( cand_tight_bJets.size() == 2 && cand_bJets.size() == 2 ){  // Region 5: 2 tight b jets
           h_btag_bins->Fill(5,weight*factor);
           bool reg5_first_matched = ( abs(nt.Jet_hadronFlavour().at(cand_tight_bJets[0])) == 5 && abs(nt.Jet_partonFlavour().at(cand_tight_bJets[0])) == 5 );
           bool reg5_second_matched = ( abs(nt.Jet_hadronFlavour().at(cand_tight_bJets[1])) == 5 && abs(nt.Jet_partonFlavour().at(cand_tight_bJets[1])) == 5 );
           if ( reg5_first_matched && reg5_second_matched ){
                h_reg5_matched_btag->Fill(1,weight*factor);
           }
           else if ( reg5_first_matched && !reg5_second_matched ){
                h_reg5_matched_btag->Fill(2,weight*factor);
           }
           else if ( !reg5_first_matched && reg5_second_matched ){
                h_reg5_matched_btag->Fill(3,weight*factor);
           }
           else{
                h_reg5_matched_btag->Fill(4,weight*factor);
           }

      }
      else {
           h_btag_bins->Fill(6,weight*factor);
      }

      plot_names.push_back("min_mlb");
      variable.insert({"min_mlb", min_mlb});

      plot_names.push_back("minDPhi_b_MET");
      variable.insert({"minDPhi_b_MET", minDPhi_b_MET});

      plot_names.push_back("minDPhi_lb_MET");
      variable.insert({"minDPhi_lb_MET", minDPhi_lb_MET});

      plot_names.push_back("minDPhi_llb_MET");
      variable.insert({"minDPhi_llb_MET", minDPhi_llb_MET});

      plot_names.push_back("dPhi_ll_MET");
      variable.insert({"dPhi_ll_MET", dPhi_ll_MET});

      if (cand_bJets.size()>=1) nbtagsel[0] = true;
      else nbtagsel[0] = false;
      if (doNbTagBins) {
	if (cand_bJets.size()==1) nbtagsel[1] = true;
	else nbtagsel[1] = false;
	if (cand_bJets.size()>=2) nbtagsel[2] = true;
	else nbtagsel[2] = false;
      }

      // Fill histos: sel7
      label = ">0 b-tag (medium WP)";
      slicedlabel = "";
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  TString tlabel = slicedlabel+nbtagbinlabel[nbtag[inb]];
	  if ( mllbinsel[imll] && nbtagsel[inb] )
	    slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,tlabel);
	}
      }
      icutflow++;
      sel = "sel7";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	//if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	    TString name = plot_name+"_"+sel+"_"+mllbin[imll]+"_"+nbtag[inb];
	    if ( mllbinsel[imll] && nbtagsel[inb] )
	      histos[name]->Fill(variable[plot_name],weight*factor);
	  }
	}
      }


      if ( selectedPair_M < 150 ) continue;
      // Fill histos: sel8
      label = "m(ll)>150 GeV";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  if ( mllbinsel[imll] && nbtagsel[inb] )
	    slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      sel = "sel8";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	//if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	    TString name = plot_name+"_"+sel+"_"+mllbin[imll]+"_"+nbtag[inb];
	    if ( mllbinsel[imll] && nbtagsel[inb] ) 
	      histos[name]->Fill(variable[plot_name],weight*factor);
	  }
	}
      }
      
      if ( min_mlb < 175.0 ) continue;
      label = "min m(lb)>175 GeV";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	  TString slice = mllbin[imll]+"_"+nbtag[inb];
	  if ( mllbinsel[imll] && nbtagsel[inb] )
	    slicedcutflows[slice]->Fill(icutflow,weight*factor);
	  slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
	}
      }
      icutflow++;
      sel = "sel9";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
	TString plot_name = plot_names[iplot];
	//if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
	for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
	  for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
	    TString name = plot_name+"_"+sel+"_"+mllbin[imll]+"_"+nbtag[inb];
	    if ( mllbinsel[imll] && nbtagsel[inb] )
	      histos[name]->Fill(variable[plot_name],weight*factor);
	  }
	}
      }

    } // Event loop

    delete file;

  } // File loop
  bar.finish();

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
