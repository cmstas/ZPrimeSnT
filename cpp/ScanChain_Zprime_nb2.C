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
#include "../NanoCORE/Tools/goodrun.h"
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

  if ( process.Contains("data") ) {
    xsec = 1.0; // fb
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

  /*
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
  */
  if ( isMC )
    factor = xsec*lumi/genEventSumw;

  // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
  TFile* fout = new TFile("temp_data/output_"+process+"_"+year+"nb2.root", "RECREATE");
  float m_ll, wgt, weighted_evts;
  bool flag_20TT, flag_20TM, flag_20MM, flag_20TL, flag_20ML, flag_30TT, flag_30TM, flag_30MM, flag_30TL, flag_30ML;
  TTree tree_out("tree","");
  tree_out.Branch("m_ll",&m_ll);
  tree_out.Branch("wgt",&wgt);
  tree_out.Branch("weighted_evts",&weighted_evts);
  tree_out.Branch("flag_20TT",&flag_20TT);
  tree_out.Branch("flag_20TM",&flag_20TM);
  tree_out.Branch("flag_20MM",&flag_20MM);
  tree_out.Branch("flag_20TL",&flag_20TL);
  tree_out.Branch("flag_20ML",&flag_20ML);
  tree_out.Branch("flag_30TT",&flag_30TT);
  tree_out.Branch("flag_30TM",&flag_30TM);
  tree_out.Branch("flag_30MM",&flag_30MM);
  tree_out.Branch("flag_30TL",&flag_30TL);
  tree_out.Branch("flag_30ML",&flag_30ML);
      

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

    for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

      flag_20TT = false;
      flag_20TM = false;
      flag_20MM = false;
      flag_20TL = false;
      flag_20ML = false;
      flag_30TT = false;
      flag_30TM = false;
      flag_30MM = false;
      flag_30TL = false;
      flag_30ML = false; 

      nt.GetEntry(event);
      tree->LoadTree(event);

      float weight = 1.0;
      wgt = 1.0;
      if ( isMC )
	weight = genWeight();
        wgt = weight;
        weighted_evts = weight*factor;
      if(removeSpikes && weight*factor>1e2) continue;

      int runnb = nt.run();
      int lumiblock = nt.luminosityBlock();
      int npv = nt.PV_npvs();

      // Apply Golden JSON
      if ( !isMC )
	if ( !(goodrun(runnb, lumiblock)) )
	  continue;

      // For test: use Run2018B, with exclusion of HEM15/16 affcted runs:
      if ( !isMC )
	if ( runnb >= 319077 )
	  continue;


      // Define vector of muon candidate indices here.....
      vector<int> cand_muons_pf_id;
      vector<int> cand_muons_pf_id_and_pteta;
      vector<int> cand_muons_pf;
      //vector<int> cand_muons_tunep;

      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);

      // HLT selection
      if ( (year=="2016nonAPV" || year=="2016APV") && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
      if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;

      // Number of good primary vertices
      if ( nt.PV_npvsGood() < 1 ) continue;
      // MET filters: https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2#UL_data
      if ( process.Contains("data") && !( nt.Flag_goodVertices()>=1 && nt.Flag_globalSuperTightHalo2016Filter()>=1 && nt.Flag_HBHENoiseFilter()>=1 && nt.Flag_HBHENoiseIsoFilter()>=1 && nt.Flag_EcalDeadCellTriggerPrimitiveFilter()>=1 && nt.Flag_BadPFMuonFilter()>=1 && nt.Flag_BadPFMuonDzFilter()>=1 && nt.Flag_eeBadScFilter()>=1 && ( year=="2016" ? 1 : nt.Flag_ecalBadCalibFilter()>=1 ) ) ) continue;

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
     

      if ( !pt_req ) continue;
      

      if ( !iso_req ) continue;

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

      if ( selectedPair_M < 150 ) continue;

      m_ll = selectedPair_M;

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


      if ( extra_muons.size() > 0 || extra_electrons.size() > 0 ) continue;

      if ( extra_isotracks_lep.size() > 0 || extra_isotracks_chh.size() > 0 ) continue;


      //vector<int> cand_bJets;
      vector<int> bjet_idx_loose_20;
      vector<int> bjet_idx_med_20;
      vector<int> bjet_idx_tight_20;
      vector<int> bjet_idx_loose_30;
      vector<int> bjet_idx_med_30;
      vector<int> bjet_idx_tight_30;
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
	     nt.Jet_btagDeepFlavB().at(jet) > 0.0490 ){ // Using medium WP for 2018 (0.0490 for loose, 0.7100 for tight, 0.2783 for medium)
	     bjet_idx_loose_20.push_back(jet);
             if ( nt.Jet_btagDeepFlavB().at(jet) > 0.2783 ){
                  bjet_idx_med_20.push_back(jet);
                  if ( nt.Jet_pt().at(jet) > 30 ) bjet_idx_med_30.push_back(jet);
             }
             if ( nt.Jet_btagDeepFlavB().at(jet) > 0.7100 ){ 
                  bjet_idx_tight_20.push_back(jet);
                  if ( nt.Jet_pt().at(jet) > 30 ) bjet_idx_tight_30.push_back(jet);
             }
             if ( nt.Jet_pt().at(jet) > 30 ) bjet_idx_loose_30.push_back(jet);
             
	}
      }
 
      //std::cout << "Number of M 20 jets = " << bjet_idx_med_20.size() << endl;
      //std::cout << "Number of T 20 jets = " << bjet_idx_tight_20.size() << endl;
      //std::cout << "Number of M 30 jets = " << bjet_idx_med_30.size() << endl;
      //std::cout << "Number of T 30 jets = " << bjet_idx_tight_30.size() << endl;
     

      // Construct mlb pairs from selected muon pair and candidate b jets
      auto leadingMu_p4 = nt.Muon_p4().at(leadingMu_idx);
      auto subleadingMu_p4 = nt.Muon_p4().at(subleadingMu_idx);
      auto selectedPair_p4 = leadingMu_p4 + subleadingMu_p4;
     
      //std::cout << "1" << endl; 
      if ( bjet_idx_med_20.size() < 1 ) continue;
      float min_mlb_ml_20 = -1;
      float min_mlb_mm_20 = -1;
      float min_mlb_tl_20 = -1;
      float min_mlb_tm_20 = -1;
      float min_mlb_tt_20 = -1;
      float min_mlb_ml_30 = -1;
      float min_mlb_mm_30 = -1;
      float min_mlb_tl_30 = -1;
      float min_mlb_tm_30 = -1;
      float min_mlb_tt_30 = -1;
      //std::cout << "2" << endl;
      // 1 medium, 1 loose, pT > 20 
      if ( bjet_idx_med_20.size() > 0 && bjet_idx_loose_20.size() > 0 ){
           min_mlb_ml_20 = 1e9;
           float min_mlb_m_20 = 1e9;
           float min_mlb_l_20 = 1e9;
           for ( int i = 0; i < bjet_idx_med_20.size(); i++ ) {
	        auto bjet_p4 = nt.Jet_p4().at(bjet_idx_med_20[i]);
        	float m_mu1_b = (leadingMu_p4+bjet_p4).M();
        	if ( m_mu1_b < min_mlb_m_20 ) {
          	     min_mlb_m_20 = m_mu1_b;
        	}
        	float m_mu2_b = (subleadingMu_p4+bjet_p4).M();
        	if ( m_mu2_b < min_mlb_m_20 ) {
          	     min_mlb_m_20 = m_mu2_b;
        	}
      	   }           
           for ( int j = 0; j < bjet_idx_loose_20.size(); j++ ) {
	        auto bjet_p4_1 = nt.Jet_p4().at(bjet_idx_loose_20[j]);
        	float m_mu1_b_1 = (leadingMu_p4+bjet_p4_1).M();
        	if ( m_mu1_b_1 < min_mlb_l_20 ) {
            	     min_mlb_l_20 = m_mu1_b_1;
                }
        	float m_mu2_b_1 = (subleadingMu_p4+bjet_p4_1).M();
        	if ( m_mu2_b_1 < min_mlb_l_20 ) {
          	     min_mlb_l_20 = m_mu2_b_1;
        	}
           }  
           
           if ( min_mlb_l_20 > min_mlb_m_20 ){
                min_mlb_ml_20 = min_mlb_m_20;
           }
           else{
                min_mlb_ml_20 = min_mlb_l_20;
           }
      }

      // 1 medium, 1 loose, pT > 30
      if ( bjet_idx_med_30.size() > 0 && bjet_idx_loose_30.size() > 0 ){
           min_mlb_ml_30 = 1e9;
           float min_mlb_m_30 = 1e9;
           float min_mlb_l_30 = 1e9;
           for ( int c = 0; c < bjet_idx_med_30.size(); c++ ) {
                auto bjet_p4_14 = nt.Jet_p4().at(bjet_idx_med_30[c]);
                float m_mu1_b_14 = (leadingMu_p4+bjet_p4_14).M();
                if ( m_mu1_b_14 < min_mlb_m_30 ) {
                     min_mlb_m_30 = m_mu1_b_14;
                }
                float m_mu2_b_14 = (subleadingMu_p4+bjet_p4_14).M();
                if ( m_mu2_b_14 < min_mlb_m_30 ) {
                     min_mlb_m_30 = m_mu2_b_14;
                }
           }
           for ( int d = 0; d < bjet_idx_loose_30.size(); d++ ) {
                auto bjet_p4_15 = nt.Jet_p4().at(bjet_idx_loose_30[d]);
                float m_mu1_b_15 = (leadingMu_p4+bjet_p4_15).M();
                if ( m_mu1_b_15 < min_mlb_l_30 ) {
                     min_mlb_l_30 = m_mu1_b_15;
                }
                float m_mu2_b_15 = (subleadingMu_p4+bjet_p4_15).M();
                if ( m_mu2_b_15 < min_mlb_l_30 ) {
                     min_mlb_l_30 = m_mu2_b_15;
                }
           }

           if ( min_mlb_l_30 > min_mlb_m_30 ){
                min_mlb_ml_30 = min_mlb_m_30;
           }
           else{
                min_mlb_ml_30 = min_mlb_l_30;
           }
      }

      //std::cout << "3" << endl;
      // 2 medium b tags, pT > 20 
      if ( bjet_idx_med_20.size() > 1 ){
           min_mlb_mm_20 = 1e9;
           for ( int k = 0; k < bjet_idx_med_20.size(); k++ ) {
                auto bjet_p4_2 = nt.Jet_p4().at(bjet_idx_med_20[k]);
                float m_mu1_b_2 = (leadingMu_p4+bjet_p4_2).M();
                if ( m_mu1_b_2 < min_mlb_mm_20 ) {
                     min_mlb_mm_20 = m_mu1_b_2;
                }
                float m_mu2_b_2 = (subleadingMu_p4+bjet_p4_2).M();
                if ( m_mu2_b_2 < min_mlb_mm_20 ) {
                     min_mlb_mm_20 = m_mu2_b_2;
                }
           }
      }
      // 2 medium b tags, pT > 30
      if ( bjet_idx_med_30.size() > 1 ){
           min_mlb_mm_30 = 1e9;
           for ( int p = 0; p < bjet_idx_med_30.size(); p++ ) {
                auto bjet_p4_8 = nt.Jet_p4().at(bjet_idx_med_30[p]);
                float m_mu1_b_8 = (leadingMu_p4+bjet_p4_8).M();
                if ( m_mu1_b_8 < min_mlb_mm_30 ) {
                     min_mlb_mm_30 = m_mu1_b_8;
                }
                float m_mu2_b_8 = (subleadingMu_p4+bjet_p4_8).M();
                if ( m_mu2_b_8 < min_mlb_mm_30 ) {
                     min_mlb_mm_30 = m_mu2_b_8;
                }
           }
      }
 
      //std::cout << "4" << endl;
      // 1 tight, 1 loose, pT > 20
      if ( bjet_idx_tight_20.size() > 0 && bjet_idx_loose_20.size() > 0 ){
           min_mlb_tl_20 = 1e9;
           float min_mlb_t_20 = 1e9;
           float min_mlb_l_20_1 = 1e9;

           for ( int l = 0; l < bjet_idx_tight_20.size(); l++ ) {
                auto bjet_p4_3 = nt.Jet_p4().at(bjet_idx_tight_20[l]);
                float m_mu1_b_3 = (leadingMu_p4+bjet_p4_3).M();
                if ( m_mu1_b_3 < min_mlb_t_20 ) {
                     min_mlb_t_20 = m_mu1_b_3;
                }
                float m_mu2_b_3 = (subleadingMu_p4+bjet_p4_3).M();
                if ( m_mu2_b_3 < min_mlb_t_20 ) {
                     min_mlb_t_20 = m_mu2_b_3;
                }
           }

           for ( int m = 0; m < bjet_idx_loose_20.size(); m++ ) {
                auto bjet_p4_4 = nt.Jet_p4().at(bjet_idx_loose_20[m]);
                float m_mu1_b_4 = (leadingMu_p4+bjet_p4_4).M();
                if ( m_mu1_b_4 < min_mlb_l_20_1 ) {
                     min_mlb_l_20_1 = m_mu1_b_4;
                }
                float m_mu2_b_4 = (subleadingMu_p4+bjet_p4_4).M();
                if ( m_mu2_b_4 < min_mlb_l_20_1 ) {
                     min_mlb_l_20_1 = m_mu2_b_4;
                }

           }

           if ( min_mlb_l_20_1 > min_mlb_t_20 ){
                min_mlb_tl_20 = min_mlb_t_20;
           }
           else{
                min_mlb_tl_20 = min_mlb_l_20_1;
           }
      }
      // 1 tight, 1 loose, pT > 30
      if ( bjet_idx_tight_30.size() > 0 && bjet_idx_loose_30.size() > 0 ){
           min_mlb_tl_30 = 1e9;
           float min_mlb_t_30 = 1e9;
           float min_mlb_l_30_1 = 1e9;

           for ( int a = 0; a < bjet_idx_tight_30.size(); a++ ) {
                auto bjet_p4_12 = nt.Jet_p4().at(bjet_idx_tight_30[a]);
                float m_mu1_b_12 = (leadingMu_p4+bjet_p4_12).M();
                if ( m_mu1_b_12 < min_mlb_t_30 ) {
                     min_mlb_t_30 = m_mu1_b_12;
                }
                float m_mu2_b_12 = (subleadingMu_p4+bjet_p4_12).M();
                if ( m_mu2_b_12 < min_mlb_t_30 ) {
                     min_mlb_t_30 = m_mu2_b_12;
                }
           }

           for ( int b = 0; b < bjet_idx_loose_30.size(); b++ ) {
                auto bjet_p4_13 = nt.Jet_p4().at(bjet_idx_loose_30[b]);
                float m_mu1_b_13 = (leadingMu_p4+bjet_p4_13).M();
                if ( m_mu1_b_13 < min_mlb_l_30_1 ) {
                     min_mlb_l_30_1 = m_mu1_b_13;
                }
                float m_mu2_b_13 = (subleadingMu_p4+bjet_p4_13).M();
                if ( m_mu2_b_13 < min_mlb_l_30_1 ) {
                     min_mlb_l_30_1 = m_mu2_b_13;
                }

           }

           if ( min_mlb_l_30_1 > min_mlb_t_30 ){
                min_mlb_tl_30 = min_mlb_t_30;
           }
           else{
                min_mlb_tl_30 = min_mlb_l_30_1;
           }
      }

      //std::cout << "5" << endl;
      // 1 tight, 1 medium, pT > 20 
      if ( bjet_idx_tight_20.size() > 0 && bjet_idx_med_20.size() > 0 ){
           min_mlb_tm_20 = 1e9;
           float min_mlb_t_20_1 = 1e9;
           float min_mlb_m_20_2 = 1e9;

           for ( int n = 0; n < bjet_idx_tight_20.size(); n++ ) {
                auto bjet_p4_5 = nt.Jet_p4().at(bjet_idx_tight_20[n]);
                float m_mu1_b_5 = (leadingMu_p4+bjet_p4_5).M();
                if ( m_mu1_b_5 < min_mlb_t_20_1 ) {
                     min_mlb_t_20_1 = m_mu1_b_5;
                }
                float m_mu2_b_5 = (subleadingMu_p4+bjet_p4_5).M();
                if ( m_mu2_b_5 < min_mlb_t_20_1 ) {
                     min_mlb_t_20_1 = m_mu2_b_5;
                }
           }

           for ( int p = 0; p < bjet_idx_med_20.size(); p++ ) {
                auto bjet_p4_6 = nt.Jet_p4().at(bjet_idx_med_20[p]);
                float m_mu1_b_6 = (leadingMu_p4+bjet_p4_6).M();
                if ( m_mu1_b_6 < min_mlb_m_20_2 ) {
                     min_mlb_m_20_2 = m_mu1_b_6;
                }
                float m_mu2_b_6 = (subleadingMu_p4+bjet_p4_6).M();
                if ( m_mu2_b_6 < min_mlb_m_20_2 ) {
                     min_mlb_m_20_2 = m_mu2_b_6;
                }

           }

           if ( min_mlb_m_20_2 > min_mlb_t_20_1 ){
                min_mlb_tm_20 = min_mlb_t_20_1;
           }
           else{
                min_mlb_tm_20 = min_mlb_m_20_2;
           }
      }
      // 1 tight, 1 medium, pT > 30
      if ( bjet_idx_tight_30.size() > 0 && bjet_idx_med_30.size() > 0 ){
           min_mlb_tm_30 = 1e9;
           float min_mlb_t_30_1 = 1e9;
           float min_mlb_m_30_2 = 1e9;

           for ( int u = 0; u < bjet_idx_tight_30.size(); u++ ) {
                auto bjet_p4_10 = nt.Jet_p4().at(bjet_idx_tight_30[u]);
                float m_mu1_b_10 = (leadingMu_p4+bjet_p4_10).M();
                if ( m_mu1_b_10 < min_mlb_t_30_1 ) {
                     min_mlb_t_30_1 = m_mu1_b_10;
                }
                float m_mu2_b_10 = (subleadingMu_p4+bjet_p4_10).M();
                if ( m_mu2_b_10 < min_mlb_t_30_1 ) {
                     min_mlb_t_30_1 = m_mu2_b_10;
                }
           }

           for ( int v = 0; v < bjet_idx_med_30.size(); v++ ) {
                auto bjet_p4_11 = nt.Jet_p4().at(bjet_idx_med_30[v]);
                float m_mu1_b_11 = (leadingMu_p4+bjet_p4_11).M();
                if ( m_mu1_b_11 < min_mlb_m_30_2 ) {
                     min_mlb_m_30_2 = m_mu1_b_11;
                }
                float m_mu2_b_11 = (subleadingMu_p4+bjet_p4_11).M();
                if ( m_mu2_b_11 < min_mlb_m_30_2 ) {
                     min_mlb_m_30_2 = m_mu2_b_11;
                }

           }

           if ( min_mlb_m_30_2 > min_mlb_t_30_1 ){
                min_mlb_tm_30 = min_mlb_t_30_1;
           }
           else{
                min_mlb_tm_30 = min_mlb_m_30_2;
           }
      }
 
      //std::cout << "6" << endl;
      // 2 tight, pT > 20 
      if ( bjet_idx_tight_20.size() > 1 ){
           min_mlb_tt_20 = 1e9;
           for ( int q = 0; q < bjet_idx_tight_20.size(); q++ ) {
                auto bjet_p4_7 = nt.Jet_p4().at(bjet_idx_tight_20[q]);
                float m_mu1_b_7 = (leadingMu_p4+bjet_p4_7).M();
                if ( m_mu1_b_7 < min_mlb_tt_20 ) {
                     min_mlb_tt_20 = m_mu1_b_7;
                }
                float m_mu2_b_7 = (subleadingMu_p4+bjet_p4_7).M();
                if ( m_mu2_b_7 < min_mlb_tt_20 ) {
                     min_mlb_tt_20 = m_mu2_b_7;
                }
           }
      }
      // 2 tight, pT > 30
      if ( bjet_idx_tight_30.size() > 1 ){
           min_mlb_tt_30 = 1e9;
           for ( int r = 0; r < bjet_idx_tight_30.size(); r++ ) {
                auto bjet_p4_9 = nt.Jet_p4().at(bjet_idx_tight_30[r]);
                float m_mu1_b_9 = (leadingMu_p4+bjet_p4_9).M();
                if ( m_mu1_b_9 < min_mlb_tt_30 ) {
                     min_mlb_tt_30 = m_mu1_b_9;
                }
                float m_mu2_b_9 = (subleadingMu_p4+bjet_p4_9).M();
                if ( m_mu2_b_9 < min_mlb_tt_30 ) {
                     min_mlb_tt_30 = m_mu2_b_9;
                }
           }
      }


      //std::cout << "7" << endl;

      if ( min_mlb_ml_20 > 175 ) flag_20ML = true;
      // Set corresponding boolean to true
      //flag_20ML = true;
      
      if ( min_mlb_mm_20 > 175 ){
           // Set corresponding boolean to true
           flag_20MM = true;
      }
      if ( min_mlb_tl_20 > 175 ){
           // Set corresponding boolean to true
           flag_20TL = true;
      }
      if ( min_mlb_tm_20 > 175 ){
           // Set corresponding boolean to true
           flag_20TM = true; 
      }
      if ( min_mlb_tt_20 > 175 ){
           flag_20TT = true;
      }
      if ( min_mlb_ml_30 > 175 ) flag_30ML = true;
      if ( min_mlb_mm_30 > 175 ) flag_30MM = true;
      if ( min_mlb_tl_30 > 175 ) flag_30TL = true;
      if ( min_mlb_tm_30 > 175 ) flag_30TM = true;
      if ( min_mlb_tt_30 > 175 ) flag_30TT = true;

      // Fill the tree
      tree_out.Fill();    

    } // Event loop

    delete file;

  } // File loop
  bar.finish();
  
  fout->Write();
  fout->Close();
  return 0;
}
