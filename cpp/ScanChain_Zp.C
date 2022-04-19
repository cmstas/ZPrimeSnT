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
#define SUM_GT(vec,num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x,float y){return ((y > (num)) ? x+y : x); });
#define COUNT_GT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name,nbins,low,high,xtitle) TH1F *h_##name = new TH1F(#name,"",nbins,low,high); h_##name->GetXaxis()->SetTitle(xtitle); h_##name->GetYaxis()->SetTitle("Events");
#define HTemp(name,nbins,low,high,xtitle) TH1F *h_temp = new TH1F(name,"",nbins,low,high); h_temp->GetXaxis()->SetTitle(xtitle); h_temp->GetYaxis()->SetTitle("Events");

// #define DEBUG

bool removeSpikes = false;

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

  map<TString, int> nbins { {"mll_pf", 240}, {"mu1_pt", 200}, {"mu2_pt", 200}, {"mu1_eta", 60}, {"mu2_eta", 60}, {"mu1_trkRelIso", 50}, {"mu2_trkRelIso", 50}, {"nCand_Muons", 4}, {"nbtagDeepFlavB", 5}, {"bjet1_pt", 200}, {"bjet1_eta", 60}, {"bjet2_pt", 200}, {"bjet2_eta", 60}, {"min_mlb", 200}, {"pfmet_pt", 120}, {"pfmet_phi", 65}, {"puppimet_pt", 120}, {"puppimet_phi", 65}, {"nExtra_muons", 6}, {"nExtra_electrons", 6}, {"nExtra_lepIsoTracks", 6}, {"nExtra_chhIsoTracks", 6} };
  map<TString, float> low { {"mll_pf", 100}, {"mu1_pt", 0}, {"mu2_pt", 0}, {"mu1_eta", -3}, {"mu2_eta", -3}, {"mu1_trkRelIso", 0}, {"mu2_trkRelIso", 0}, {"nCand_Muons", 2}, {"nbtagDeepFlavB", 0}, {"bjet1_pt", 0}, {"bjet1_eta", -3}, {"bjet2_pt", 0}, {"bjet2_eta", -3}, {"min_mlb", 0}, {"pfmet_pt", 0}, {"pfmet_phi", -3.25}, {"puppimet_pt", 0}, {"puppimet_phi", -3.25}, {"nExtra_muons", 0}, {"nExtra_electrons", 0}, {"nExtra_lepIsoTracks", 0}, {"nExtra_chhIsoTracks", 0} };
  map<TString, float> high { {"mll_pf", 2500}, {"mu1_pt", 1000}, {"mu2_pt", 1000}, {"mu1_eta", 3}, {"mu2_eta", 3}, {"mu1_trkRelIso", 0.5}, {"mu2_trkRelIso", 0.5}, {"nCand_Muons", 6}, {"nbtagDeepFlavB", 5}, {"bjet1_pt", 1000}, {"bjet1_eta", 3}, {"bjet2_pt", 1000}, {"bjet2_eta", 3}, {"min_mlb", 2000}, {"pfmet_pt", 600}, {"pfmet_phi", 3.25}, {"puppimet_pt", 600}, {"puppimet_phi", 3.25}, {"nExtra_muons", 6}, {"nExtra_electrons", 6}, {"nExtra_lepIsoTracks", 6}, {"nExtra_chhIsoTracks", 6} };
  map<TString, TString> title { {"mll_pf", "m_{ll} [GeV]"}, {"mu1_pt", "p_{T} (leading #mu) [GeV]"}, {"mu2_pt", "p_{T} (subleading #mu) [GeV]"}, {"mu1_eta", "#eta (leading #mu)"}, {"mu2_eta", "#eta (subleading #mu)"}, {"mu1_trkRelIso", "Track iso./p_{T} (leading #mu)"}, {"mu2_trkRelIso", "Track iso./p_{T} (subleading #mu)"}, {"nCand_Muons", "Number of #mu candidates"}, {"nbtagDeepFlavB", "Number of b-tags (medium WP)"}, {"bjet1_pt", "p_{T} (leading b-tagged jet) [GeV]"}, {"bjet1_eta", "#eta (leading b-tagged jet) [GeV]"}, {"bjet2_pt", "p_{T} (subleading b-tagged jet) [GeV]"}, {"bjet2_eta", "#eta (subleading b-tagged jet) [GeV]"}, {"min_mlb", "min m_{lb} [GeV]"}, {"pfmet_pt", "PF MET p_{T} [GeV]"}, {"pfmet_phi", "PF MET #phi [GeV]"}, {"puppimet_pt", "PUPPI MET p_{T} [GeV]"}, {"puppimet_phi", "PUPPI MET #phi [GeV]"}, {"nExtra_muons", "Number of additional #mu's"}, {"nExtra_electrons", "Number of electrons"}, {"nExtra_lepIsoTracks", "Number of (additional) lepton (e/#mu) PF candidates"}, {"nExtra_chhIsoTracks", "Number of (additional) charged hadron PF candidates"} };

  vector<TString> selection = {"sel0","sel1","sel2","sel3","sel4","sel5","sel6","sel7","sel8","sel9"};

  vector<TString> plot_names = {"pfmet_pt","pfmet_phi","puppimet_pt","puppimet_phi"};
  map<TString, TH1F*> histos;
  for ( unsigned int isel=0; isel < selection.size(); isel++ )
  {
    if (isel==5)
    {
      plot_names.push_back("mll_pf"); plot_names.push_back("mu1_pt"); plot_names.push_back("mu2_pt"); plot_names.push_back("mu1_eta"); plot_names.push_back("mu2_eta"); plot_names.push_back("mu1_trkRelIso"); plot_names.push_back("mu2_trkRelIso"); plot_names.push_back("nCand_Muons");
    }
    if (isel==6)
    {
      plot_names.push_back("nExtra_muons"); plot_names.push_back("nExtra_electrons"); plot_names.push_back("nExtra_lepIsoTracks"); plot_names.push_back("nExtra_chhIsoTracks");
    }
    if (isel==7)
    {
      plot_names.push_back("nbtagDeepFlavB"); plot_names.push_back("bjet1_pt"); plot_names.push_back("bjet1_eta"); plot_names.push_back("bjet2_pt"); plot_names.push_back("bjet2_eta"); plot_names.push_back("min_mlb");
    }
    for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
    {
      TString plot_name = plot_names[iplot];
      TString name = plot_name+"_"+selection[isel];
      HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
      histos[name] = h_temp;
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
    h_cutflow->Fill(icutflow,xsec*lumi);
    h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Total");

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

      plot_names = {"pfmet_pt","pfmet_phi","puppimet_pt","puppimet_phi"};
      map<TString, float> variable { {"pfmet_pt", pfmet_pt}, {"pfmet_phi", pfmet_phi}, {"puppimet_pt", puppimet_pt}, {"puppimet_phi", puppimet_phi} };

      // Define vector of muon candidate indices here.....
      vector<int> cand_muons_pf_id;
      vector<int> cand_muons_pf_id_and_pteta;
      vector<int> cand_muons_pf;
      //vector<int> cand_muons_tunep;

      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);

      // After skim
      icutflow = 1;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"After skim");
      icutflow++;

      // HLT selection
      if ( (year=="2016nonAPV" || year=="2016APV") && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
      if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"HLT");
      icutflow++;

      // Number of good primary vertices
      if ( nt.PV_npvsGood() < 1 ) continue;
      // Fill histos: sel0
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,">0 good PVs");
      icutflow++;
      TString sel = "sel0";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      // Single muon selection loop
      int nMu_id = 0;
      int nMu_pt = 0;
      int nMu_iso = 0;
      for ( unsigned int mu = 0; mu < nt.nMuon(); mu++ ){
        bool mu_trk_and_global = ( nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu) );
        bool mu_id = ( nt.Muon_highPtId().at(mu) == 2 );
        bool mu_pt_pf = ( nt.Muon_pt().at(mu) > 53 && fabs(nt.Muon_eta().at(mu)) < 2.4 );
        bool mu_relIso = ( nt.Muon_tkRelIso().at(mu) < 0.1 );
	      
        if ( mu_trk_and_global && mu_id ){
          nMu_id++;
          cand_muons_pf_id.push_back(mu);
          if ( mu_pt_pf ){
            nMu_pt++;
            cand_muons_pf_id_and_pteta.push_back(mu);
            if ( mu_relIso ){
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
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,">1 muons w/ highPt ID");
      icutflow++;
      sel = "sel1";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      if ( !pt_req ) continue;
      // Fill histos: sel2
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,">1 muons w/ pT>53 GeV & |eta|<2.4");
      icutflow++;
      sel = "sel2";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      if ( !iso_req ) continue;
      // Fill histos: sel3
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,">1 muons w/ track iso./pT<0.1");
      icutflow++;
      sel = "sel3";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }


      // Trigger object finding
      bool atLeastSelectedMu_matchedToTrigObj = false;
      vector<bool> muMatchedToTrigObj;
      for ( int n = 0; n < nt.nTrigObj(); n++ ){
	if ( abs(nt.TrigObj_id().at(n)) != 13 ) continue;
	if ( !(nt.TrigObj_filterBits().at(n) & 8) ) continue;
	for ( auto i_cand_muons_pf : cand_muons_pf ){
	  float deta = nt.TrigObj_eta().at(n) - nt.Muon_eta().at(i_cand_muons_pf);
	  float dphi = TVector2::Phi_mpi_pi(nt.TrigObj_phi().at(n) - nt.Muon_phi().at(i_cand_muons_pf));
	  float dr = TMath::Sqrt( deta*deta+dphi*dphi );
	  if ( dr < 0.02 ){
	    muMatchedToTrigObj.push_back(true);
	    atLeastSelectedMu_matchedToTrigObj = true;
	  }
	  else muMatchedToTrigObj.push_back(false);
	}
      }
      if ( !atLeastSelectedMu_matchedToTrigObj ) continue;
      // Fill histos: sel4
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,">0 HLT match (dR<0.02)");
      icutflow++;
      sel = "sel4";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      int leadingMu_idx = -1, subleadingMu_idx = -1;
      float selectedPair_M = -1.0;
      bool Zboson = false;
      for ( unsigned int i=0; i<cand_muons_pf.size(); i++ ){
	TVector3 mu_1(nt.Muon_p4().at(cand_muons_pf[i]).Px(),nt.Muon_p4().at(cand_muons_pf[i]).Py(),nt.Muon_p4().at(cand_muons_pf[i]).Pz());
	for ( unsigned int j=i+1; j<cand_muons_pf.size(); j++ ){
	  if ( nt.Muon_pdgId().at(cand_muons_pf[i]) + nt.Muon_pdgId().at(cand_muons_pf[j]) != 0 ) continue; // Opposite sign, same flavor
	  if ( !(muMatchedToTrigObj[i] || muMatchedToTrigObj[j]) ) continue; // At least one muon in pair matched to HLT
	  TVector3 mu_2(nt.Muon_p4().at(cand_muons_pf[j]).Px(),nt.Muon_p4().at(cand_muons_pf[j]).Py(),nt.Muon_p4().at(cand_muons_pf[j]).Pz());
	  if ( !(IsSeparated( mu_1,mu_2 ) ) ) continue; // 3D angle between muons > pi - 0.02
	  float m_ll_pf = (nt.Muon_p4().at(cand_muons_pf[i])+nt.Muon_p4().at(cand_muons_pf[j])).M();
	  if ( m_ll_pf > 70 && m_ll_pf < 110 ){ // Reject event if it contains dimuon pair compatible with Z mass
	    Zboson = true;
	    continue;
	  }
	  if ( selectedPair_M < 0.0 ){
	    leadingMu_idx = cand_muons_pf[i];
	    subleadingMu_idx = cand_muons_pf[j];
	    selectedPair_M = m_ll_pf;
	  }
	}
	if ( Zboson ) break;
      }
      if ( selectedPair_M < 0.0 || Zboson ) continue;
      // Add histos: sel5
      plot_names.push_back("mll_pf"); plot_names.push_back("mu1_pt"); plot_names.push_back("mu2_pt"); plot_names.push_back("mu1_eta"); plot_names.push_back("mu2_eta"); plot_names.push_back("mu1_trkRelIso"); plot_names.push_back("mu2_trkRelIso"); plot_names.push_back("nCand_Muons");
      variable.insert({"mll_pf", selectedPair_M}); variable.insert({"mu1_pt", nt.Muon_pt().at(leadingMu_idx)}); variable.insert({"mu2_pt", nt.Muon_pt().at(subleadingMu_idx)}); variable.insert({"mu1_eta", nt.Muon_eta().at(leadingMu_idx)}); variable.insert({"mu2_eta", nt.Muon_eta().at(subleadingMu_idx)}); variable.insert({"mu1_trkRelIso", nt.Muon_tkRelIso().at(leadingMu_idx)}); variable.insert({"mu2_trkRelIso", nt.Muon_tkRelIso().at(subleadingMu_idx)}); variable.insert({"nCand_Muons", cand_muons_pf.size()});
      // Add histos: sel5
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Muon pair (OS, !Z)");
      icutflow++;
      sel = "sel5";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      // Look for a third isolated lepton and then veto the event if it is found
      // Muons
      vector<int> extra_muons;
      for ( int i = 0; i < nt.nMuon(); i++ ){
	if ( nt.Muon_pt().at(i) > 10. && 
	     fabs(nt.Muon_eta().at(i)) < 2.4 &&
	     nt.Muon_looseId().at(i) > 0 && 
	     fabs(nt.Muon_dxy().at(i)) < 0.2 && fabs(nt.Muon_dz().at(i)) < 0.5 &&
	     nt.Muon_miniPFRelIso_all().at(i) < 0.2 &&
	     !( i == leadingMu_idx || i == subleadingMu_idx)){
	  extra_muons.push_back(i);
	}
      }

      // Electrons
      vector<int> extra_electrons;
      for ( int i = 0; i < nt.nElectron(); i++ ){
	if ( nt.Electron_pt().at(i) > 10. &&
	     fabs(nt.Electron_eta().at(i)) < 2.4 &&
	     nt.Electron_cutBased().at(i) > 0 && 
	     nt.Electron_miniPFRelIso_all().at(i) < 0.1){
	  extra_electrons.push_back(i);
	}
      }

      // IsoTracks
      vector<int> extra_isotracks_lep;
      for ( int i = 0; i < nt.nIsoTrack(); i++ ){
        if ( nt.IsoTrack_isPFcand().at(i) && 
	     nt.IsoTrack_pt().at(i) > 5. && (abs(nt.IsoTrack_pdgId().at(i))==11 || (abs(nt.IsoTrack_pdgId().at(i))==13)) &&
	     fabs(nt.IsoTrack_eta().at(i)) < 2.4 &&
	     fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
	     nt.IsoTrack_pfRelIso03_chg().at(i) < 0.2){
	  float mindr=1e9;
          for ( auto i_cand_muons_pf : cand_muons_pf ){
	    if (i_cand_muons_pf!=leadingMu_idx && i_cand_muons_pf!=subleadingMu_idx) continue;
	    float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons_pf);
	    float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons_pf));
	    float dr = TMath::Sqrt( deta*deta+dphi*dphi );
	    if ( dr < mindr ){
	      mindr = dr;
	    }
	  }
	  if ( mindr > 0.02 )
	    extra_isotracks_lep.push_back(i);
        }
      }
      vector<int> extra_isotracks_chh;
      for ( int i = 0; i < nt.nIsoTrack(); i++ ){
        if ( nt.IsoTrack_isPFcand().at(i) && 
	     nt.IsoTrack_pt().at(i) > 10. && abs(nt.IsoTrack_pdgId().at(i))==211 &&
	     fabs(nt.IsoTrack_eta().at(i)) < 2.4 &&
	     fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
	     nt.IsoTrack_pfRelIso03_chg().at(i) < 0.1){
	  float mindr=1e9;
          for ( auto i_cand_muons_pf : cand_muons_pf ){
	    if (i_cand_muons_pf!=leadingMu_idx && i_cand_muons_pf!=subleadingMu_idx) continue;
	    float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons_pf);
	    float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons_pf));
	    float dr = TMath::Sqrt( deta*deta+dphi*dphi );
	    if ( dr < mindr ){
	      mindr = dr;
	    }
	  }
	  if ( mindr > 0.02 )
	    extra_isotracks_chh.push_back(i);
        }
      }

      if ( extra_muons.size() > 0 || extra_electrons.size() > 0 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Third lepton veto");
      icutflow++;

      if ( extra_isotracks_lep.size() > 0 || extra_isotracks_chh.size() > 0 ) continue;
      // Add histos: sel6
      plot_names.push_back("nExtra_muons"); plot_names.push_back("nExtra_electrons"); plot_names.push_back("nExtra_lepIsoTracks"); plot_names.push_back("nExtra_chhIsoTracks");
      variable.insert({"nExtra_muons", extra_muons.size()}); variable.insert({"nExtra_electrons",extra_electrons.size()}); variable.insert({"nExtra_lepIsoTracks",extra_isotracks_lep.size()}); variable.insert({"nExtra_chhIsoTracks",extra_isotracks_chh.size()});
      // Fill histos: sel6
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"IsoTrack veto");
      icutflow++;
      sel = "sel6";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      vector<int> cand_bJets;
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
	if ( nt.Jet_pt().at(jet) > 30 && nt.Jet_jetId().at(jet) > 0 && nt.Jet_btagDeepFlavB().at(jet) > 0.2783 ) // 0.0490 for loose, 0.7100 for tight
	  {
	    cand_bJets.push_back(jet);  // Medium DeepJet WP
	  }
      }
      if ( cand_bJets.size() < 1 ) continue;
      float bjet1_pt = nt.Jet_pt().at(cand_bJets[0]);
      float bjet2_pt = (cand_bJets.size() > 1 ? nt.Jet_pt().at(cand_bJets[1]) : -1.0);
      float bjet1_eta = nt.Jet_eta().at(cand_bJets[0]);
      float bjet2_eta = (cand_bJets.size() > 1 ? nt.Jet_eta().at(cand_bJets[1]) : -1.0);

      //Construct mlb pairs from selected muon pair and candidate b jets
      float min_mlb = 1e9;
      for ( int bjet = 0; bjet < cand_bJets.size(); bjet++ ){
	if ( bjet > 2 ) continue;
	float m_mu1_b = (nt.Muon_p4().at(leadingMu_idx)+nt.Jet_p4().at(cand_bJets[bjet])).M();
	if ( m_mu1_b < min_mlb ){
	  min_mlb = m_mu1_b;
	}
	float m_mu2_b = (nt.Muon_p4().at(subleadingMu_idx)+nt.Jet_p4().at(cand_bJets[bjet])).M();
	if ( m_mu2_b < min_mlb ){
	  min_mlb = m_mu2_b;
	}
      }
             

      // Add histos: sel7
      plot_names.push_back("nbtagDeepFlavB"); plot_names.push_back("bjet1_pt"); plot_names.push_back("bjet1_eta"); plot_names.push_back("bjet2_pt"); plot_names.push_back("bjet2_eta"); plot_names.push_back("min_mlb");
      variable.insert({"nbtagDeepFlavB", cand_bJets.size()}); variable.insert({"bjet1_pt", bjet1_pt}); variable.insert({"bjet1_eta", bjet1_eta}); variable.insert({"bjet2_pt", bjet2_pt}); variable.insert({"bjet2_eta", bjet2_eta}); variable.insert({"min_mlb", min_mlb});
      // Fill histos: sel7
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,">0 b-tag (medium WP)");
      icutflow++;
      sel = "sel7";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }
        
      if ( selectedPair_M < 150 ) continue;
      // Fill histos: sel8
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"m(ll)>150 GeV");
      icutflow++;
      sel = "sel8";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }

      if ( min_mlb < 175.0 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"min m(lb)>175 GeV");
      icutflow++;
      sel = "sel9";
      for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ )
      {
        TString plot_name = plot_names[iplot];
        if ( plot_name.Contains("bjet2") && cand_bJets.size() < 2 ) continue;
        TString name = plot_name+"_"+sel;
        histos[name]->Fill(variable[plot_name],weight*factor);
      }
      h_cutflow->GetXaxis()->SetRangeUser(0,icutflow);
      h_cutflow->GetXaxis()->SetLabelSize(0.025);

    } // Event loop

    delete file;


  } // File loop
  bar.finish();

  fout->Write();
  fout->Close();
  return 0;
}
