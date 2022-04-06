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
#include "TVector3.h"

#include "../NanoCORE/Nano.h"
#include "../NanoCORE/Base.h"
#include "../NanoCORE/SSSelections.cc"
#include "../NanoCORE/MetSelections.cc"
#include "../NanoCORE/tqdm.h"
#include "../NanoCORE/ZPrimeTools.cc"

#include <iostream>
#include <iomanip>

#define SUM(vec) std::accumulate((vec).begin(), (vec).end(), 0);
#define SUM_GT(vec,num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x,float y){return ((y > (num)) ? x+y : x); });
#define COUNT_GT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name,nbins,low,high) TH1F *h_##name = new TH1F(#name,#name,nbins,low,high);

// #define DEBUG

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
    #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
    #define debug(args...)
#endif

using namespace std;
using namespace tas;

int ScanChain(TChain *ch, TString year, TString process) {

    // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
    TFile* f1 = new TFile("output_"+process+"_"+year+".root", "RECREATE");
    H1(cutflow,20,0,20);
    H1(mll_pf,30,0,-1);
    H1(mu1_pt,30,0,-1);
    H1(mu2_pt,30,0,-1);
    //H1(type,4,0,4);
    //H1(hyp_class,6,0.5,6.5);
    //H1(filt,2,0,2);
    //H1(met,50,0,-1);
    //H1(njets,15,0,15);
    //H1(nbtags,8,0,8);
    //H1(ht,50,0,-1);
    //H1(n_mus_nano,6,-0.5,5.5);
    //H1(weight,300,0,-1);

    int nEventsTotal = 0;
    int nEvents_c0 = 0;
    int nEvents_c1 = 0;
    int nEvents_c2 = 0;
    int nEvents_c3 = 0;
    int nEvents_c4 = 0;
    int nEvents_c5 = 0;
    int nEvents_c6 = 0;
    int nEvents_c7 = 0;
    int nEvents_c8 = 0;
    int nEvents_c9 = 0;
    int nEvents_c10 = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // set configuration parameters
    //gconf.year = 2017;

    while ( (currentFile = (TFile*)fileIter.Next()) ) {
        TFile *file = TFile::Open( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        TString filename(currentFile->GetTitle());

        tree->SetCacheSize(128*1024*1024);
        tree->SetCacheLearnEntries(100);

        nt.Init(tree);

        for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

            nt.GetEntry(event);
            tree->LoadTree(event);

            // Define vector of muon candidate indices here.....
            std::vector<int> cand_muons_pf;
            //std::vector<int> cand_muons_tunep;

            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            // HLT selection
            if ( year == "2016" && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
            if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;

            nEvents_c0++;

            // Number of good primary vertices
            if ( nt.PV_npvsGood > 0 ) continue;

            nEvents_c7++;            


	    // Single muon selection loop
	    int nEvents_pt = 0;
            int nEvents_iso = 0;
            int nEvents_tracker = 0;
            int nEvents_id = 0;
            int nEvents_trk_glb = 0;
            for ( unsigned int mu = 0; mu < nt.nMuon(); mu++ ){
                  //bool cand_mu_pf = false;
                  //bool cand_mu_tunep = false; 
                  //add booleans for tracker and global muon
                  bool mu_pt_pf = ( nt.Muon_pt().at(mu) > 53 );
		  bool mu_relIso = ( nt.Muon_tkRelIso().at(mu) < 0.1 );
                  bool mu_trk_and_global = ( nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu) );
                  
                  int mu_id = nt.Muon_highPtId().at(mu);

	          // Add muon high_pt Id requirement to this if statement....			
		  if ( mu_pt_pf ){
	               nEvents_pt++;
	               if ( mu_relIso ){
			    nEvents_iso++;	
			    if ( nt.Muon_isTracker().at(mu) ){
                                 nEvents_tracker++;
				 if ( mu_id == 2 ){
                                    nEvents_id++;
				    if ( mu_trk_and_global ){
                                       nEvents_trk_glb++;
                                       cand_muons_pf.push_back(mu);
				       }
					
				    }
 
				}

			}	       
                  }    
            }

            // Defining booleans for cutflow.....
            bool pt_req = ( nEvents_pt > 1 );
            bool iso_req = ( nEvents_iso > 1);
            bool trk_req = ( nEvents_tracker > 1);
            bool id_req = ( nEvents_id > 1 );
            bool trk_glob_req = ( nEvents_trk_glb > 1 );
            bool two_cand_lep = (pt_req && iso_req && trk_req && id_req && trk_glob_req );


            if ( pt_req ) nEvents_c1++;
            if ( pt_req && iso_req ) nEvents_c2++;
            if ( pt_req && iso_req && trk_req ) nEvents_c3++;
            if ( pt_req && iso_req && trk_req && id_req ) nEvents_c4++;
            if ( two_cand_lep ) nEvents_c5++;           


            // Trigger object finding
	    std::vector<int> cand_trigObj;
            for ( int n = 0; n < nt.nTrigObj(); n++ ){
		  if ( abs(nt.TrigObj_id().at(n)) != 13 ) continue;
		  else{
		      if ( !(nt.TrigObj_filterBits().at(n) & 8) ) continue;
		      else{
			  cand_trigObj.push_back(n);
		      }
		  } 

	    }


	    //std::cout<<"Number of candidate trigger objects = "<<cand_trigObj.size()<<endl;


            bool dimuon_pf = false;        

            // Need to generalize this later for more muons passing selection....
            // Use for loop to construct all possible pairs.....    

	    // If we have 2 candidate muons
	    if ( cand_muons_pf.size() == 2 && two_cand_lep ){
                    nEvents_c6++;
		 //if ( nt.PV_npvsGood() > 0 ){
		 //   nEvents_c7++;
                 //Muons should be opposite sign
                 bool opp_sign = ( nt.Muon_pdgId().at(cand_muons_pf[0]) + nt.Muon_pdgId().at(cand_muons_pf[1]) == 0 );

                 TVector3 mu_1(nt.Muon_p4().at(cand_muons_pf[0]).Px(),nt.Muon_p4().at(cand_muons_pf[0]).Py(),nt.Muon_p4().at(cand_muons_pf[0]).Pz());
	         TVector3 mu_2(nt.Muon_p4().at(cand_muons_pf[1]).Px(),nt.Muon_p4().at(cand_muons_pf[1]).Py(),nt.Muon_p4().at(cand_muons_pf[1]).Pz());

                 bool mu_mom_sep = IsSeparated(mu_1,mu_2);

                 bool mu_1_matched = IsMatched(nt.Muon_eta().at(cand_muons_pf[0]),nt.Muon_phi().at(cand_muons_pf[0]),cand_trigObj);
		 bool mu_2_matched = IsMatched(nt.Muon_eta().at(cand_muons_pf[1]),nt.Muon_phi().at(cand_muons_pf[1]),cand_trigObj);

	         // Add flag for candidate muon matched to HLT trigger object
	         if ( opp_sign ){
                      nEvents_c8++;
		      if ( mu_mom_sep ){
			   nEvents_c9++;
	                   if ( mu_1_matched || mu_2_matched ){
				nEvents_c10++;
		      		dimuon_pf = true;
			   }
                      }
		 }  	  
		// }
            }
            
            // Same as above, but for tuneP pT
            //if ( cand_muons_tunepf.size() == 2 && nt.PV_npvsGood() > 0 ){
		 //Dimuon selection
	    //}

            float weight = genWeight();           

 
            // Fill histograms if we have a dimuon pair.....
            if ( dimuon_pf ){
                 float m_ll_pf = (nt.Muon_p4().at(cand_muons_pf[0])+nt.Muon_p4().at(cand_muons_pf[1])).M();
	         h_mll_pf->Fill(m_ll_pf); 	 
                 h_mu1_pt->Fill(nt.Muon_pt().at(cand_muons_pf[0]));
		 h_mu2_pt->Fill(nt.Muon_pt().at(cand_muons_pf[1]));
            }
            

            //h_type->Fill(type);
            //h_mll->Fill(mll);
            //h_hyp_class->Fill(hyp_class);
            //h_filt->Fill(passfilt);
            //h_nbtags->Fill(nbtags);
            //h_met->Fill(met);
            //h_njets->Fill(njets);
            //h_ht->Fill(ht);
            //h_nleps->Fill(leps.size());
            //h_weight->Fill(weight);


        } // Event loop

        // Fill the cutflow histogram
        h_cutflow->SetBinContent(1,nEventsTotal);
        h_cutflow->SetBinContent(2,nEvents_c0);
        h_cutflow->SetBinContent(3,nEvents_c7);
        h_cutflow->SetBinContent(4,nEvents_c1);
        h_cutflow->SetBinContent(5,nEvents_c2);
        h_cutflow->SetBinContent(6,nEvents_c3);
        h_cutflow->SetBinContent(7,nEvents_c4);
        h_cutflow->SetBinContent(8,nEvents_c5);
        h_cutflow->SetBinContent(9,nEvents_c6);
        h_cutflow->SetBinContent(10,nEvents_c8);
        h_cutflow->SetBinContent(11,nEvents_c9);
        h_cutflow->SetBinContent(12,nEvents_c10);

        delete file;


    } // File loop
    bar.finish();

    //std::cout <<  "Mean of h_njets: " << h_njets->GetMean() <<  std::endl;
    f1->Write();
    f1->Close();
    return 0;
}
