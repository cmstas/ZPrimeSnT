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

#define H1(name,nbins,low,high) TH1F *h_##name = new TH1F(#name,"",nbins,low,high);

// #define DEBUG

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
  TFile* f1 = new TFile("temp_data/output_"+process+"_"+year+".root", "RECREATE");
  H1(cutflow,20,0,20);
  H1(mll_pf_sel6,241,90,2500);
  H1(mll_pf_sel7,241,90,2500);
  H1(mll_pf_sel8,241,90,2500);
  H1(mll_pf_sel9,241,90,2500);
  H1(mu1_pt_sel1,200,0,1000);
  H1(mu2_pt_sel1,200,0,1000);
  H1(mu1_pt_sel2,200,0,1000);
  H1(mu2_pt_sel2,200,0,1000);
  H1(mu1_pt_sel8,200,0,1000);
  H1(mu2_pt_sel8,200,0,1000);
  H1(mu1_pt_sel9,200,0,1000);
  H1(mu2_pt_sel9,200,0,1000);
  H1(mu1_trkRelIso_sel2,50,0,0.5);
  H1(mu2_trkRelIso_sel2,50,0,0.5);
  H1(mu1_trkRelIso_sel3,50,0,0.5);
  H1(mu2_trkRelIso_sel3,50,0,0.5);
  H1(mu1_trkRelIso_sel8,50,0,0.1);
  H1(mu2_trkRelIso_sel8,50,0,0.1);
  H1(mu1_trkRelIso_sel9,50,0,0.1);
  H1(mu2_trkRelIso_sel9,50,0,0.1);
  H1(nCand_Muons_sel4,5,0,5);
  //H1(btagDeepFlavB_sel6,50,0,1);
  H1(nbtagDeepFlavB_sel6,5,0,5);
  H1(bjet1_pt_sel8,200,0,1000);
  H1(bjet2_pt_sel8,200,0,1000);
  H1(min_mlb_sel8,200,0,2000);
  H1(min_mlb_sel9,200,0,2000);
  H1(met_pt_sel8,120,0,600);
  H1(met_pt_sel9,120,0,600);
  H1(met_phi_sel8,65,-3.25,3.25);
  H1(met_phi_sel9,65,-3.25,3.25);
  H1(nExtra_muons_sel5,6,0,6);
  H1(nExtra_electrons_sel5,6,0,6);
  H1(nExtra_lepIsoTracks_sel5,6,0,6);
  H1(nExtra_chhIsoTracks_sel5,6,0,6);
  //H1(third_mu_pt_sel5,100,0,500);
  //H1(fourth_mu_pt_sel5,100,0,500);
  //H1(first_el_pt_sel5,100,0,500);
  //H1(second_el_pt_sel5,100,0,500);
  //H1(dr_trigobj_sel3,50,0,0.5);

  int nEventsTotal = 0;
  int nEvents_more_leps = 0;
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
    h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Total (before skim)");

    for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

      nt.GetEntry(event);
      tree->LoadTree(event);

      float weight = genWeight();
      if(weight>1e3) continue;

      int runnb = nt.run();
      int npv = nt.PV_npvs();

      // MET xy correction: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections#xy_Shift_Correction_MET_phi_modu
      // METXYCorr_Met_MetPhi(double uncormet, double uncormet_phi, int runnb, TString year, bool isMC, int npv, bool isUL =false,bool ispuppi=false)
      std::pair<double,double> pfmet = METXYCorr_Met_MetPhi(nt.MET_pt(), nt.MET_phi(), runnb, year, isMC, npv, true, false);
      double pfmet_pt  = pfmet.first;
      double pfmet_phi = pfmet.second;
      //std::pair<double,double> puppimet = METXYCorr_Met_MetPhi(nt.PuppiMET_pt(), nt.PuppiMET_phi(), runnb, year, isMC, npv, true, true);
      //double puppimet_pt  = puppimet.first;
      //double puppimet_phi = puppimet.second;

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
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Total (after skim)");
      icutflow++;

      // HLT selection
      if ( (year=="2016nonAPV" || year=="2016APV") && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
      if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"HLT");
      icutflow++;

      // Number of good primary vertices
      if ( nt.PV_npvsGood() < 1 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"At least 1 good PV");
      icutflow++;

      // Single muon selection loop
      int nMu_id = 0;
      int nMu_pt = 0;
      int nMu_iso = 0;
      for ( unsigned int mu = 0; mu < nt.nMuon(); mu++ ){
	bool mu_trk_and_global = ( nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu) );
	bool mu_id = ( nt.Muon_highPtId().at(mu) == 2 );
	bool mu_pt_pf = ( nt.Muon_pt().at(mu) > 53 && fabs(nt.Muon_eta().at(mu)) < 2.4 );
	bool mu_relIso = ( nt.Muon_tkRelIso().at(mu) < 0.02 );
	      
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
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Muon ID (highPt)");
      icutflow++;

      //Fill histograms before and after these requirements!
      h_mu1_pt_sel1->Fill(nt.Muon_pt().at(cand_muons_pf_id[0]),weight*factor);
      h_mu2_pt_sel1->Fill(nt.Muon_pt().at(cand_muons_pf_id[1]),weight*factor);
      if ( !pt_req ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Muon pT>53 GeV & |eta|<2.4");
      icutflow++;
      h_mu1_pt_sel2->Fill(nt.Muon_pt().at(cand_muons_pf_id_and_pteta[0]),weight*factor);
      h_mu2_pt_sel2->Fill(nt.Muon_pt().at(cand_muons_pf_id_and_pteta[1]),weight*factor);

      h_mu1_trkRelIso_sel2->Fill(nt.Muon_tkRelIso().at(cand_muons_pf_id_and_pteta[0]),weight*factor);
      h_mu2_trkRelIso_sel2->Fill(nt.Muon_tkRelIso().at(cand_muons_pf_id_and_pteta[1]),weight*factor);
      if ( !iso_req ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Muon track iso./pT<0.1");
      icutflow++;
      h_mu1_trkRelIso_sel3->Fill(nt.Muon_tkRelIso().at(cand_muons_pf[0]),weight*factor);
      h_mu2_trkRelIso_sel3->Fill(nt.Muon_tkRelIso().at(cand_muons_pf[1]),weight*factor);


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
	  //h_dr_trigobj_sel3->Fill(dr,weight*factor);
	  if ( dr < 0.02 ){
	    muMatchedToTrigObj.push_back(true);
	    atLeastSelectedMu_matchedToTrigObj = true;
	  }
	  else muMatchedToTrigObj.push_back(false);
	}
      }
      if ( !atLeastSelectedMu_matchedToTrigObj ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"At least one muon HLT match");
      icutflow++;

      h_nCand_Muons_sel4->Fill(cand_muons_pf.size(),weight*factor);

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
      if ( selectedPair_M < 0.0 ) continue;
      if ( Zboson ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Muon pair (OS, !Z)");
      icutflow++;

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

      //// IsoTracks
      //vector<int> extra_isotracks_lep;
      //for ( int i = 0; i < nt.nIsoTrack(); i++ ){
      //  if ( nt.IsoTrack_isPFcand().at(i) && 
      //	   nt.IsoTrack_pt().at(i) > 5. && (abs(nt.IsoTrack_pdgId().at(i))==11 || (abs(nt.IsoTrack_pdgId().at(i))==13)) &&
      //	   fabs(nt.IsoTrack_eta().at(i)) < 2.4 &&
      //	   fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
      //	   nt.IsoTrack_pfRelIso03_chg().at(i) < 0.2){
      //	float mindr=1e9;
      //    for ( auto i_cand_muons_pf : cand_muons_pf ){
      //	  float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons_pf);
      //	  float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons_pf));
      //	  float dr = TMath::Sqrt( deta*deta+dphi*dphi );
      //	  if ( dr < mindr ){
      //	    mindr = dr;
      //	  }
      //	}
      //	if ( mindr > 0.02)
      //	  extra_isotracks_lep.push_back(i);
      //  }
      //}
      //vector<int> extra_isotracks_chh;
      //for ( int i = 0; i < nt.nIsoTrack(); i++ ){
      //  if ( nt.IsoTrack_isPFcand().at(i) && 
      //	   nt.IsoTrack_pt().at(i) > 10. && abs(nt.IsoTrack_pdgId().at(i))==211 &&
      //	   fabs(nt.IsoTrack_eta().at(i)) < 2.4 &&
      //	   fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
      //	   nt.IsoTrack_pfRelIso03_chg().at(i) < 0.1){
      //	float mindr=1e9;
      //    for ( auto i_cand_muons_pf : cand_muons_pf ){
      //	  float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons_pf);
      //	  float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons_pf));
      //	  float dr = TMath::Sqrt( deta*deta+dphi*dphi );
      //	  if ( dr < mindr ){
      //	    mindr = dr;
      //	  }
      //	}
      //	if ( mindr > 0.02)
      //	  extra_isotracks_chh.push_back(i);
      //  }
      //}

      //Fill relevant histograms for extra electrons, muons
      h_nExtra_muons_sel5->Fill(extra_muons.size(),weight*factor);
      h_nExtra_electrons_sel5->Fill(extra_electrons.size(),weight*factor);
      //h_nExtra_lepIsoTracks_sel5->Fill(extra_isotracks_lep.size(),weight*factor);
      //h_nExtra_chhIsoTracks_sel5->Fill(extra_isotracks_chh.size(),weight*factor);

      //if ( extra_muons.size() == 1 ) h_third_mu_pt_sel5->Fill(nt.Muon_pt().at(extra_muons[0]),weight*factor);
      //if ( extra_electrons.size() == 1 ) h_first_el_pt_sel5->Fill(nt.Electron_pt().at(extra_electrons[0]),weight*factor);
      //if ( extra_muons.size() > 1 ){
      //     h_third_mu_pt_sel5->Fill(nt.Muon_pt().at(extra_muons[0]),weight*factor);
      //	 h_fourth_mu_pt_sel5->Fill(nt.Muon_pt().at(extra_muons[1]),weight*factor); 
      //}
      //if ( extra_electrons.size() > 1 ){
      //     h_first_el_pt_sel5->Fill(nt.Electron_pt().at(extra_electrons[0]),weight*factor);
      //     h_second_el_pt_sel5->Fill(nt.Electron_pt().at(extra_electrons[1]),weight*factor);
      //}
 
      if ( extra_muons.size() > 0 || extra_electrons.size() > 0 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"Third lepton veto");
      icutflow++;

      //if ( extra_lepIsoTracks.size() > 0 || extra_isotracks_chh.size() > 0 ) continue;
      //h_cutflow->Fill(icutflow,weight*factor);
      //h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"IsoTrack veto");
      //icutflow++;

      vector<int> cand_bJets;
      unsigned int nbtagDeepFlavB = 0;
      //bool mu_jet_sep = true;
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
	    //h_btagDeepFlavB_sel6->Fill(nt.Jet_btagDeepFlavB().at(jet),weight*factor);
	  }
      }
      h_nbtagDeepFlavB_sel6->Fill(cand_bJets.size(),weight*factor);
      h_mll_pf_sel6->Fill(selectedPair_M,weight*factor);
      if ( cand_bJets.size() < 1 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"At least 1 b-tag");
      icutflow++;
      h_mll_pf_sel7->Fill(selectedPair_M,weight*factor);
      if ( selectedPair_M < 150 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"m(ll)>150 GeV");
      icutflow++;

      //Fill pT distributions for the bjets....
      if ( cand_bJets.size() == 1 ){
	h_bjet1_pt_sel8->Fill(nt.Jet_pt().at(cand_bJets[0]),weight*factor);
      }

      if ( cand_bJets.size() > 1 ){
	h_bjet1_pt_sel8->Fill(nt.Jet_pt().at(cand_bJets[0]),weight*factor);
	h_bjet2_pt_sel8->Fill(nt.Jet_pt().at(cand_bJets[1]),weight*factor);
      }


      //Construct mlb pairs from selected muon pair and candidate b jets
      //float m_lb = 0;
      vector<float> m_lb_vec;
      for ( int bjet = 0; bjet < cand_bJets.size(); bjet++ ){
	if ( bjet > 2 ) continue;
	float m_mu1_b = (nt.Muon_p4().at(leadingMu_idx)+nt.Jet_p4().at(cand_bJets[bjet])).M();
	float m_mu2_b = (nt.Muon_p4().at(subleadingMu_idx)+nt.Jet_p4().at(cand_bJets[bjet])).M();
	m_lb_vec.push_back(m_mu1_b);
	m_lb_vec.push_back(m_mu2_b);		  
      }
             

      float min_mlb = 1e9;
      for ( int k = 0; k < m_lb_vec.size(); k++ ){
	if ( m_lb_vec[k] < min_mlb ){
	  min_mlb = m_lb_vec[k];
	}
      }

      h_met_pt_sel8->Fill(pfmet_pt,weight*factor);
      h_met_phi_sel8->Fill(pfmet_phi,weight*factor);
      h_mu1_trkRelIso_sel8->Fill(nt.Muon_tkRelIso().at(leadingMu_idx),weight*factor);
      h_mu2_trkRelIso_sel8->Fill(nt.Muon_tkRelIso().at(subleadingMu_idx),weight*factor);
      h_mll_pf_sel8->Fill(selectedPair_M,weight*factor); 	 
      h_mu1_pt_sel8->Fill(nt.Muon_pt().at(leadingMu_idx),weight*factor);
      h_mu2_pt_sel8->Fill(nt.Muon_pt().at(subleadingMu_idx),weight*factor);
      h_min_mlb_sel8->Fill(min_mlb,weight*factor);
            
      if ( min_mlb < 175.0 ) continue;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,"min m(lb)>175 GeV");
      icutflow++;
      h_met_pt_sel9->Fill(pfmet_pt,weight*factor);
      h_met_phi_sel9->Fill(pfmet_phi,weight*factor);
      h_mu1_trkRelIso_sel9->Fill(nt.Muon_tkRelIso().at(leadingMu_idx),weight*factor);
      h_mu2_trkRelIso_sel9->Fill(nt.Muon_tkRelIso().at(subleadingMu_idx),weight*factor);
      h_mll_pf_sel9->Fill(selectedPair_M,weight*factor); 	 
      h_mu1_pt_sel9->Fill(nt.Muon_pt().at(leadingMu_idx),weight*factor);
      h_mu2_pt_sel9->Fill(nt.Muon_pt().at(subleadingMu_idx),weight*factor);
      h_min_mlb_sel9->Fill(min_mlb,weight*factor);

    } // Event loop

    delete file;


  } // File loop
  bar.finish();

  f1->Write();
  f1->Close();
  return 0;
}
