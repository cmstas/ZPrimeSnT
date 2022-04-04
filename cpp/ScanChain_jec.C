#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

#include "../NanoCORE/Nano.h"
#include "../NanoCORE/MetSelections.h"
#include "../NanoCORE/Tools/JetCorrector.h"
#include "../NanoCORE/tqdm.h"

#include <iostream>
#include <iomanip>

#define DEBUG

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
    #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
    #define debug(args...)
#endif

using namespace std;
using namespace tas;

int ScanChain(TChain *ch, int nevents_to_process=-1) {

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // std::string jecEraMC = "Fall17_17Nov2017_V32_MC";
    std::string jecEraMC = "Autumn18_V19_MC";
    debug(jecEraMC);
    FactorizedJetCorrector* jetCorr = makeJetCorrector({
            "../NanoCORE/Tools/jetcorr/data/"+jecEraMC+"/"+jecEraMC+"_L1FastJet_AK4PFchs.txt",
            "../NanoCORE/Tools/jetcorr/data/"+jecEraMC+"/"+jecEraMC+"_L2Relative_AK4PFchs.txt",
            "../NanoCORE/Tools/jetcorr/data/"+jecEraMC+"/"+jecEraMC+"_L3Absolute_AK4PFchs.txt",
            });

    while ( (currentFile = (TFile*)fileIter.Next()) ) {
        TFile *file = TFile::Open( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        TString filename(currentFile->GetTitle());

        tree->SetCacheSize(32*1024*1024);
        tree->SetCacheLearnEntries(100);

        nt.Init(tree);

        for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

            nt.GetEntry(event);
            tree->LoadTree(event);

            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            int njets = Jet_pt().size();
            debug(njets);
            for (int i = 0; i < njets; i++) {
                // Get corrected jet pT from nanoAOD and undo the correction
                float pt = Jet_pt()[i];
                float rawpt = pt*(1.-Jet_rawFactor()[i]);
                // Now compute the JEC again from text files
                jetCorr->setJetPtEtaARho(rawpt, Jet_eta()[i], Jet_area()[i], fixedGridRhoFastjetAll());
                // Which is shorthand for
                //     jetCorr->setJetEta(Jet_eta()[i]);
                //     jetCorr->setJetPt(rawpt);
                //     jetCorr->setJetA(Jet_area()[i]);
                //     jetCorr->setRho(fixedGridRhoFastjetAll());
                float JEC = jetCorr->getCorrection();
                float newpt = rawpt*JEC;
                // Do they match?
                debug(i, rawpt, pt, newpt);
            }

            float rawmet = RawMET_pt();
            float nanomet = MET_pt();
            float recalct1met = getT1CHSMET(jetCorr).first;
            debug(rawmet, nanomet, recalct1met);

            if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;
        }
        if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;

        delete file;


    }
    bar.finish();

    return 0;
}
