#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

#include "../NanoCORE/Nano.h"
#include "../NanoCORE/Base.h"
#include "../NanoCORE/SSSelections.cc"
#include "../NanoCORE/MetSelections.cc"
#include "../NanoCORE/tqdm.h"

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

int ScanChain(TChain *ch) {

    TFile* f1 = new TFile("output.root", "RECREATE");
    H1(mll,30,0,-1);
    H1(type,4,0,4);
    H1(hyp_class,6,0.5,6.5);
    H1(filt,2,0,2);
    H1(met,50,0,-1);
    H1(njets,15,0,15);
    H1(nbtags,8,0,8);
    H1(ht,50,0,-1);
    H1(nleps,6,-0.5,5.5);
    H1(weight,300,0,-1);

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // set configuration parameters
    gconf.year = 2017;

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


            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            // if (event > 50000) break;

            auto leps = getLeptons();
            auto result = getBestHyp(leps, false);
            int hyp_class = result.first;
            if (hyp_class < 0) continue;
            auto best_hyp = result.second;

            Lepton lep1 = result.second.first;
            Lepton lep2 = result.second.second;
            if (lep1.pt() < 25 || lep2.pt() < 20) continue;

            int njets, nbtags;
            float ht;
            std::tie(njets,nbtags,ht) = getJetInfo(leps);

            float mll = (lep1.p4()+lep2.p4()).M();
            int type = lep1.is_el() + lep2.is_el(); // mm, em, ee
            float met = MET_pt();
            bool passfilt = passesMETfilters(false);

            debug(passfilt,nbtags,met,njets,nleps);

            if (lep1.is_el() && lep1.idlevel() < SS::IDfakable) continue;
            if (lep2.is_el() && lep2.idlevel() < SS::IDfakable) continue;

            // if (hyp_class != 3 && hyp_class != 4) continue;

            float weight = genWeight();

            h_type->Fill(type);
            h_mll->Fill(mll);
            h_hyp_class->Fill(hyp_class);
            h_filt->Fill(passfilt);
            h_nbtags->Fill(nbtags);
            h_met->Fill(met);
            h_njets->Fill(njets);
            h_ht->Fill(ht);
            h_nleps->Fill(leps.size());
            h_weight->Fill(weight);


        } // Event loop

        delete file;


    } // File loop
    bar.finish();

    std::cout <<  "Mean of h_njets: " << h_njets->GetMean() <<  std::endl;
    f1->Write();
    f1->Close();
    return 0;
}
