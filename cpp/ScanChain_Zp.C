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

    float factor = 1.0;
    float lumi = 1.0;
    float xsec = 1.0;
 
    if ( process == "ttbar" ){
         xsec = 87310.0; // fb
    }
    if ( process == "DY" ){
         xsec = 5765400.0; // fb
    }
    if ( process == "WW" ){
         xsec = 115000.0; // fb 
    }
    if ( process == "WZ" ){
	 xsec = 47130.0; // fb
    }
    if ( process == "ZZ" ){
         xsec = 16523.0; // fb
    }    

    
    if ( year == "2018" ){
	 lumi = 62.76; // fb-1
    }
    if ( year == "2017" ){
         lumi = 45.39; // fb-1
    }
    if ( year == "2016" ){
         lumi = 37.40; // fb-1
    }


    factor = xsec*lumi;


    // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
    TFile* f1 = new TFile("output_"+process+"_"+year+".root", "RECREATE");
    H1(cutflow,20,0,20);
    H1(mll_pf,30,0,1000);
    H1(mu1_pt,30,0,1000);
    H1(mu2_pt,30,0,1000);
    H1(nGood_PV_pre,5,0,5);
    H1(nGood_PV_post,5,0,5);
    H1(mu1_pt_pre,30,0,1000);
    H1(mu1_pt_post,30,0,1000);
    H1(mu2_pt_pre,30,0,1000);
    H1(mu2_pt_post,30,0,1000);
    H1(mu1_trkRelIso_pre,10,0,1);
    H1(mu1_trkRelIso_post,10,0,1);
    H1(mu2_trkRelIso_pre,10,0,1);
    H1(mu2_trkRelIso_post,10,0,1);
    H1(mu1_highPtId_pre,50,0,10);
    H1(mu1_highPtId_post,50,0,10);
    H1(mu2_highPtId_pre,50,0,10);
    H1(mu2_highPtId_post,50,0,10);
    H1(nCand_Muons_pre,5,0,5);
    H1(nCand_Muons_post,5,0,5);
    H1(nCand_trigObj_pre,10,0,5);
    H1(nCand_trigObj_post,10,0,5);
    

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
    int nEvents_c11 = 0;
    int nEvents_c12 = 0;
    float sumWeight_c0 = 0.0;
    float sumWeight_c1 = 0.0;
    float sumWeight_c2 = 0.0;
    float sumWeight_c3 = 0.0;
    float sumWeight_c4 = 0.0;
    float sumWeight_c5 = 0.0;
    float sumWeight_c6 = 0.0;
    float sumWeight_c7 = 0.0;
    float sumWeight_c8 = 0.0;
    float sumWeight_c9 = 0.0;
    float sumWeight_c10 = 0.0;
    float sumWeight_c11 = 0.0;
    float sumWeight_c12 = 0.0;
    float sumWeight_total = 0.0;
    
    int nEvents_more_leps = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    float sumOfWeights;

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

            float weight = genWeight();

            // Define vector of muon candidate indices here.....
            std::vector<int> cand_muons_pf;
            //std::vector<int> cand_muons_tunep;

            nEventsTotal++;
            sumWeight_total+=weight;
            bar.progress(nEventsTotal, nEventsChain);

            // HLT selection
            if ( year == "2016" && !( nt.HLT_Mu50() || nt.HLT_TkMu50() ) ) continue;
            if ( (year=="2017" || year=="2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()) ) continue;

            //nEvents_c0++;
            sumWeight_c0+=weight;

            // Number of good primary vertices
            h_nGood_PV_pre->Fill(nt.PV_npvsGood(),weight);
            if ( nt.PV_npvsGood() < 1 ) continue;
            h_nGood_PV_post->Fill(nt.PV_npvsGood(),weight);
            //nEvents_c1++;
            sumWeight_c1+=weight;            


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

            //Fill histograms before and after these requirements!
            h_mu1_pt_pre->Fill(nt.Muon_pt().at(0),weight);
            h_mu2_pt_pre->Fill(nt.Muon_pt().at(1),weight);
            if ( !pt_req ) continue;
            h_mu1_pt_post->Fill(nt.Muon_pt().at(0),weight);
            h_mu2_pt_post->Fill(nt.Muon_pt().at(1),weight);
            //nEvents_c2++;     
	    sumWeight_c2+=weight;       
            h_mu1_trkRelIso_pre->Fill(nt.Muon_tkRelIso().at(0),weight);
            h_mu2_trkRelIso_pre->Fill(nt.Muon_tkRelIso().at(1),weight);
            if ( !(pt_req && iso_req) ) continue;
            h_mu1_trkRelIso_post->Fill(nt.Muon_tkRelIso().at(0),weight);
            h_mu2_trkRelIso_post->Fill(nt.Muon_tkRelIso().at(1),weight);
            //nEvents_c3++;
            sumWeight_c3+=weight;
            if ( !(pt_req && iso_req && trk_req) ) continue;
            //nEvents_c4++;
            sumWeight_c4+=weight;
            h_mu1_highPtId_pre->Fill(nt.Muon_highPtId().at(0),weight);
            h_mu2_highPtId_pre->Fill(nt.Muon_highPtId().at(1),weight);
            if ( !(pt_req && iso_req && trk_req && id_req) ) continue;
            h_mu1_highPtId_post->Fill(nt.Muon_highPtId().at(0),weight);
            h_mu2_highPtId_post->Fill(nt.Muon_highPtId().at(1),weight);
            //nEvents_c5++;
            sumWeight_c5+=weight;
            if ( !two_cand_lep ) continue;
            //nEvents_c6++;
            sumWeight_c6+=weight;           


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

            h_nCand_Muons_pre->Fill(cand_muons_pf.size(),weight);
	    if ( cand_muons_pf.size() < 2 ) continue;
            h_nCand_Muons_post->Fill(cand_muons_pf.size(),weight);
            //nEvents_c7++;
            sumWeight_c7+=weight;
            h_nCand_trigObj_pre->Fill(cand_trigObj.size(),weight);
            if ( cand_trigObj.size() < 1 ) continue;
            h_nCand_trigObj_post->Fill(cand_trigObj.size(),weight);
            //nEvents_c8++;
            sumWeight_c8+=weight;

            bool dimuon_pf = false;        

            // Need to generalize this later for more muons passing selection....
            // Use for loop to construct all possible pairs.....    

	    // If we have 2 candidate muons
	    if ( cand_muons_pf.size() == 2 ){
                 //nEvents_c9++;
                 sumWeight_c9+=weight;
	
                 //Muons should be opposite sign
                 bool opp_sign = ( nt.Muon_pdgId().at(cand_muons_pf[0]) + nt.Muon_pdgId().at(cand_muons_pf[1]) == 0 );

                 TVector3 mu_1(nt.Muon_p4().at(cand_muons_pf[0]).Px(),nt.Muon_p4().at(cand_muons_pf[0]).Py(),nt.Muon_p4().at(cand_muons_pf[0]).Pz());
	         TVector3 mu_2(nt.Muon_p4().at(cand_muons_pf[1]).Px(),nt.Muon_p4().at(cand_muons_pf[1]).Py(),nt.Muon_p4().at(cand_muons_pf[1]).Pz());

                 bool mu_mom_sep = IsSeparated(mu_1,mu_2);

                 bool mu_1_matched = IsMatched(nt.Muon_eta().at(cand_muons_pf[0]),nt.Muon_phi().at(cand_muons_pf[0]),cand_trigObj);
		 bool mu_2_matched = IsMatched(nt.Muon_eta().at(cand_muons_pf[1]),nt.Muon_phi().at(cand_muons_pf[1]),cand_trigObj);

	       
	         if ( opp_sign ){
                      //nEvents_c10++;
                      sumWeight_c10+=weight;
		      if ( mu_mom_sep ){
			   //nEvents_c11++;
			   sumWeight_c11+=weight;
	                   if ( mu_1_matched || mu_2_matched ){
				//nEvents_c12++;
				sumWeight_c12+=weight;
		      		dimuon_pf = true;
			   }
                      }
		 }  	  
		
            }

            // In the case we have more than 2 candidate leptons......	    
            if ( cand_muons_pf.size() > 2 ){
                 nEvents_more_leps++;
            }
            

            //float weight = genWeight();
            //std::cout<<"Generator event weight = "<<weight<<endl;           

 
            // Fill histograms if we have a dimuon pair.....
            if ( dimuon_pf ){
                 float m_ll_pf = (nt.Muon_p4().at(cand_muons_pf[0])+nt.Muon_p4().at(cand_muons_pf[1])).M();
	         h_mll_pf->Fill(m_ll_pf,weight); 	 
                 h_mu1_pt->Fill(nt.Muon_pt().at(cand_muons_pf[0]),weight);
		 h_mu2_pt->Fill(nt.Muon_pt().at(cand_muons_pf[1]),weight);
                 sumOfWeights+=weight;
            }


        } // Event loop

        //std::cout<<"Sum of weights = "<<sumOfWeights<<endl;

        // Fill the cutflow histogram
        /*
        h_cutflow->SetBinContent(1,factor);
        h_cutflow->SetBinContent(2,factor*(sumWeight_c0/sumWeight_total));
        h_cutflow->SetBinContent(3,factor*(sumWeight_c1/sumWeight_total));
        h_cutflow->SetBinContent(4,factor*(sumWeight_c2/sumWeight_total));
        h_cutflow->SetBinContent(5,factor*(sumWeight_c3/sumWeight_total));
        h_cutflow->SetBinContent(6,factor*(sumWeight_c4/sumWeight_total));
        h_cutflow->SetBinContent(7,factor*(sumWeight_c5/sumWeight_total));
        h_cutflow->SetBinContent(8,factor*(sumWeight_c6/sumWeight_total));
        h_cutflow->SetBinContent(9,factor*(sumWeight_c7/sumWeight_total));
        h_cutflow->SetBinContent(10,factor*(sumWeight_c8/sumWeight_total));
        h_cutflow->SetBinContent(11,factor*(sumWeight_c9/sumWeight_total));
        h_cutflow->SetBinContent(12,factor*(sumWeight_c10/sumWeight_total));
        h_cutflow->SetBinContent(13,factor*(sumWeight_c11/sumWeight_total));
        h_cutflow->SetBinContent(14,factor*(sumWeight_c12/sumWeight_total));

        // Perform histogram scaling here to account for xsec, lumi, sum of weights
        h_mll_pf->Scale(factor/sumOfWeights);
        h_mu1_pt->Scale(factor/sumOfWeights);
        h_mu2_pt->Scale(factor/sumOfWeights);
        h_nGood_PV_pre->Scale(factor/sumWeight_c0);
        h_nGood_PV_post->Scale(factor/sumWeight_c1);
        h_mu1_pt_pre->Scale(factor/sumWeight_c1);
        h_mu2_pt_pre->Scale(factor/sumWeight_c1);
        h_mu1_pt_post->Scale(factor/sumWeight_c2);
        h_mu2_pt_post->Scale(factor/sumWeight_c2);
        h_mu1_trkRelIso_pre->Scale(factor/sumWeight_c2);
        h_mu2_trkRelIso_pre->Scale(factor/sumWeight_c2);
        h_mu1_trkRelIso_post->Scale(factor/sumWeight_c3);
        h_mu2_trkRelIso_post->Scale(factor/sumWeight_c3);
        h_mu1_highPtId_pre->Scale(factor/sumWeight_c4);
        h_mu2_highPtId_pre->Scale(factor/sumWeight_c4);
        h_mu1_highPtId_post->Scale(factor/sumWeight_c5);
        h_mu2_highPtId_post->Scale(factor/sumWeight_c5);
        h_nCand_Muons_pre->Scale(factor/sumWeight_c6);
        h_nCand_Muons_post->Scale(factor/sumWeight_c7);
        h_nCand_trigObj_pre->Scale(factor/sumWeight_c7);
        h_nCand_trigObj_post->Scale(factor/sumWeight_c8);
        */
        delete file;


    } // File loop
    bar.finish();

    h_cutflow->SetBinContent(1,factor);
    h_cutflow->SetBinContent(2,factor*(sumWeight_c0/sumWeight_total));
    h_cutflow->SetBinContent(3,factor*(sumWeight_c1/sumWeight_total));
    h_cutflow->SetBinContent(4,factor*(sumWeight_c2/sumWeight_total));
    h_cutflow->SetBinContent(5,factor*(sumWeight_c3/sumWeight_total));
    h_cutflow->SetBinContent(6,factor*(sumWeight_c4/sumWeight_total));
    h_cutflow->SetBinContent(7,factor*(sumWeight_c5/sumWeight_total));
    h_cutflow->SetBinContent(8,factor*(sumWeight_c6/sumWeight_total));
    h_cutflow->SetBinContent(9,factor*(sumWeight_c7/sumWeight_total));
    h_cutflow->SetBinContent(10,factor*(sumWeight_c8/sumWeight_total));
    h_cutflow->SetBinContent(11,factor*(sumWeight_c9/sumWeight_total));
    h_cutflow->SetBinContent(12,factor*(sumWeight_c10/sumWeight_total));
    h_cutflow->SetBinContent(13,factor*(sumWeight_c11/sumWeight_total));
    h_cutflow->SetBinContent(14,factor*(sumWeight_c12/sumWeight_total));    

    h_mll_pf->Scale(factor/sumOfWeights);
    h_mu1_pt->Scale(factor/sumOfWeights);
    h_mu2_pt->Scale(factor/sumOfWeights);
    h_nGood_PV_pre->Scale(factor/sumWeight_c0);
    h_nGood_PV_post->Scale(factor/sumWeight_c1);
    h_mu1_pt_pre->Scale(factor/sumWeight_c1);
    h_mu2_pt_pre->Scale(factor/sumWeight_c1);
    h_mu1_pt_post->Scale(factor/sumWeight_c2);
    h_mu2_pt_post->Scale(factor/sumWeight_c2);
    h_mu1_trkRelIso_pre->Scale(factor/sumWeight_c2);
    h_mu2_trkRelIso_pre->Scale(factor/sumWeight_c2);
    h_mu1_trkRelIso_post->Scale(factor/sumWeight_c3);
    h_mu2_trkRelIso_post->Scale(factor/sumWeight_c3);
    h_mu1_highPtId_pre->Scale(factor/sumWeight_c4);
    h_mu2_highPtId_pre->Scale(factor/sumWeight_c4);
    h_mu1_highPtId_post->Scale(factor/sumWeight_c5);
    h_mu2_highPtId_post->Scale(factor/sumWeight_c5);
    h_nCand_Muons_pre->Scale(factor/sumWeight_c6);
    h_nCand_Muons_post->Scale(factor/sumWeight_c7);
    h_nCand_trigObj_pre->Scale(factor/sumWeight_c7);
    h_nCand_trigObj_post->Scale(factor/sumWeight_c8);


    //std::cout <<  "Mean of h_njets: " << h_njets->GetMean() <<  std::endl;
    f1->Write();
    f1->Close();
    return 0;
}
