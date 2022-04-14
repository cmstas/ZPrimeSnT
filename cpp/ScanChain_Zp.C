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

#include <iostream>
#include <iomanip>

#define SUM(vec) std::accumulate((vec).begin(), (vec).end(), 0);
#define SUM_GT(vec, num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x, float y) { return ((y > (num)) ? x + y : x); });
#define COUNT_GT(vec, num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec, num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name, nbins, low, high) TH1F *h_##name = new TH1F(#name, #name, nbins, low, high);

// #define DEBUG

struct debugger
{
    template <typename T>
    debugger &operator,(const T &v)
    {
        cerr << v << " ";
        return *this;
    }
} dbg;
#ifdef DEBUG
#define debug(args...)         \
    do                         \
    {                          \
        cerr << #args << ": "; \
        dbg, args;             \
        cerr << endl;          \
    } while (0)
#else
#define debug(args...)
#endif

using namespace std;
using namespace tas;

int ScanChain(TChain *ch, double genEventSumw, TString year, TString process)
{

    float factor = 1.0;
    float lumi = 1.0;
    float xsec = 1.0;

    if (process == "ttbar")
        xsec = 87310.0; // fb
    if (process == "DY")
        xsec = 5765400.0; // fb
    if (process == "WW")
        xsec = 118700.0; // fb
    if (process == "WZ")
        xsec = 47130.0; // fb
    if (process == "ZZ")
        xsec = 16523.0; // fb
    if (process == "tW")
        xsec = 19550; // fb
    if (process == "tbarW")
        xsec = 19550; // fb
    if (process == "TTW")
        xsec = 204.3; // fb
    if (process == "TTZ")
        xsec = 252.9; // fb
    if (process == "TTHToNonbb")
        xsec = 507.5 * (1 - 0.575); // fb
    if (process == "TTHTobb")
        xsec = 507.5 * 0.575; // fb
    if (process == "signal")
        xsec = 0.01597959 * 1000; // fb // M200, Y3, 2018

    if (year == "2018")
        lumi = 59.83; // fb-1
    if (year == "2017")
        lumi = 41.48; // fb-1
    if (year == "2016APV")
        lumi = 19.5; // fb-1
    if (year == "2016")
        lumi = 16.8; // fb-1

    factor = xsec * lumi / genEventSumw;

    // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
    TFile *f1 = new TFile("output_" + process + "_" + year + ".root", "RECREATE");
    H1(cutflow, 20, 0, 20);
    H1(mll_pf, 100, 150, 2000);
    H1(mll_pf_btag, 100, 150, 2000);
    H1(mll_pf_pre, 100, 150, 2000);
    H1(mu1_pt, 50, 50, 800);
    H1(mu2_pt, 50, 50, 800);
    H1(mu1_pt_pre, 30, 0, 1000);
    H1(mu1_pt_post, 30, 0, 1000);
    H1(mu2_pt_pre, 30, 0, 1000);
    H1(mu2_pt_post, 30, 0, 1000);
    H1(mu1_trkRelIso_pre, 50, 0, 0.5);
    H1(mu1_trkRelIso_post, 50, 0, 0.5);
    H1(mu2_trkRelIso_pre, 50, 0, 0.5);
    H1(mu2_trkRelIso_post, 50, 0, 0.5);
    H1(mu1_trkRelIso, 50, 0, 0.1);
    H1(mu2_trkRelIso, 50, 0, 0.1);
    H1(nCand_Muons, 5, 0, 5);
    H1(nbtagDeepFlavB, 5, 0, 5);
    H1(btagDeepFlavB, 50, 0, 1);
    H1(bjet1_pt, 50, 0, 1000);
    H1(bjet2_pt, 50, 0, 1000);
    H1(min_mlb, 50, 50, 250);
    H1(max_mlb, 50, 0, 1000);
    // H1(ll_pt,50,0,1000);
    // H1(ll_eta,50,-5,5);

    int nEventsTotal = 0;
    int nEvents_more_leps = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // set configuration parameters
    // gconf.year = 2017;

    while ((currentFile = (TFile *)fileIter.Next()))
    {
        TFile *file = TFile::Open(currentFile->GetTitle());
        TTree *tree = (TTree *)file->Get("Events");
        TString filename(currentFile->GetTitle());

        tree->SetCacheSize(128 * 1024 * 1024);
        tree->SetCacheLearnEntries(100);

        nt.Init(tree);

        for (unsigned int event = 0; event < tree->GetEntriesFast(); ++event)
        {

            nt.GetEntry(event);
            tree->LoadTree(event);

            float weight = genWeight();

            // Define vector of muon candidate indices here.....
            vector<int> cand_muons_pf;
            // vector<int> cand_muons_tunep;

            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            // Before any cuts
            int icutflow = 0;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            // HLT selection
            if (year == "2016" && !(nt.HLT_Mu50() || nt.HLT_TkMu50()))
                continue;
            if ((year == "2017" || year == "2018") && !(nt.HLT_Mu50() || nt.HLT_OldMu100() || nt.HLT_TkMu100()))
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            // Number of good primary vertices
            if (nt.PV_npvsGood() < 1)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            // Single muon selection loop
            int nEvents_pt = 0;
            int nEvents_iso = 0;
            int nEvents_trk_glb = 0;
            int nEvents_id = 0;
            for (unsigned int mu = 0; mu < nt.nMuon(); mu++)
            {
                bool mu_pt_pf = (nt.Muon_pt().at(mu) > 53);
                bool mu_relIso = (nt.Muon_tkRelIso().at(mu) < 0.1);
                bool mu_trk_and_global = (nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu));
                bool mu_id = (nt.Muon_highPtId().at(mu) == 2);

                if (mu_pt_pf)
                {
                    nEvents_pt++;
                    if (mu_relIso)
                    {
                        nEvents_iso++;
                        if (mu_trk_and_global)
                        {
                            nEvents_trk_glb++;
                            if (mu_id)
                            {
                                nEvents_id++;
                                cand_muons_pf.push_back(mu);
                            }
                        }
                    }
                }
            }

            // Defining booleans for cutflow.....
            bool pt_req = (nEvents_pt > 1);
            bool iso_req = (nEvents_iso > 1);
            bool trk_glob_req = (nEvents_trk_glb > 1);
            bool id_req = (nEvents_id > 1);

            // Fill histograms before and after these requirements!
            h_mu1_pt_pre->Fill(nt.Muon_pt().at(0), weight * factor);
            h_mu2_pt_pre->Fill(nt.Muon_pt().at(1), weight * factor);
            if (!pt_req)
                continue;
            h_mu1_pt_post->Fill(nt.Muon_pt().at(0), weight * factor);
            h_mu2_pt_post->Fill(nt.Muon_pt().at(1), weight * factor);
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            h_mu1_trkRelIso_pre->Fill(nt.Muon_tkRelIso().at(0), weight * factor);
            h_mu2_trkRelIso_pre->Fill(nt.Muon_tkRelIso().at(1), weight * factor);
            if (!iso_req)
                continue;
            h_mu1_trkRelIso_post->Fill(nt.Muon_tkRelIso().at(0), weight * factor);
            h_mu2_trkRelIso_post->Fill(nt.Muon_tkRelIso().at(1), weight * factor);
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            if (!trk_glob_req)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            if (!id_req)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            // Trigger object finding
            bool atLeastSelectedMu_matchedToTrigObj = false;
            vector<bool> muMatchedToTrigObj;
            for (int n = 0; n < nt.nTrigObj(); n++)
            {
                if (abs(nt.TrigObj_id().at(n)) != 13)
                    continue;
                if (!(nt.TrigObj_filterBits().at(n) & 8))
                    continue;
                for (auto i_cand_muons_pf : cand_muons_pf)
                {
                    float deta = nt.TrigObj_eta().at(n) - nt.Muon_eta().at(i_cand_muons_pf);
                    float dphi = TVector2::Phi_mpi_pi(nt.TrigObj_phi().at(n) - nt.Muon_phi().at(i_cand_muons_pf));
                    float dr = TMath::Sqrt(deta * deta + dphi * dphi);
                    if (dr < 0.2)
                    {
                        muMatchedToTrigObj.push_back(true);
                        atLeastSelectedMu_matchedToTrigObj = true;
                    }
                    else
                        muMatchedToTrigObj.push_back(false);
                }
            }
            if (!atLeastSelectedMu_matchedToTrigObj)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            h_nCand_Muons->Fill(cand_muons_pf.size(), weight * factor);

            int leadingMu_idx = -1, subleadingMu_idx = -1;
            float selectedPair_M = -1.0;
            bool Zboson = false;
            for (unsigned int i = 0; i < cand_muons_pf.size(); i++)
            {
                TVector3 mu_1(nt.Muon_p4().at(cand_muons_pf[i]).Px(), nt.Muon_p4().at(cand_muons_pf[i]).Py(), nt.Muon_p4().at(cand_muons_pf[i]).Pz());
                for (unsigned int j = i + 1; j < cand_muons_pf.size(); j++)
                {
                    if (nt.Muon_pdgId().at(cand_muons_pf[i]) + nt.Muon_pdgId().at(cand_muons_pf[j]) != 0)
                        continue; // Opposite sign, same flavor
                    if (!(muMatchedToTrigObj[i] || muMatchedToTrigObj[j]))
                        continue; // At least one muon in pair matched to HLT
                    TVector3 mu_2(nt.Muon_p4().at(cand_muons_pf[j]).Px(), nt.Muon_p4().at(cand_muons_pf[j]).Py(), nt.Muon_p4().at(cand_muons_pf[j]).Pz());
                    if (!(IsSeparated(mu_1, mu_2)))
                        continue; // 3D angle between muons > pi - 0.02
                    float m_ll_pf = (nt.Muon_p4().at(cand_muons_pf[i]) + nt.Muon_p4().at(cand_muons_pf[j])).M();
                    if (m_ll_pf > 70 && m_ll_pf < 110)
                    { // Reject event if it contains dimuon pair compatible with Z mass
                        Zboson = true;
                        continue;
                    }
                    if (selectedPair_M < 0.0)
                    {
                        leadingMu_idx = cand_muons_pf[i];
                        subleadingMu_idx = cand_muons_pf[j];
                        selectedPair_M = m_ll_pf;
                    }
                }
                if (Zboson)
                    break;
            }
            if (selectedPair_M < 0.0)
                continue;
            if (Zboson)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            vector<int> cand_bJets;
            unsigned int nbtagDeepFlavB = 0;
            // bool mu_jet_sep = true;
            for (unsigned int jet = 0; jet < nt.nJet(); jet++)
            {
                float d_eta_1 = nt.Muon_eta().at(leadingMu_idx) - nt.Jet_eta().at(jet);
                float d_eta_2 = nt.Muon_eta().at(subleadingMu_idx) - nt.Jet_eta().at(jet);
                float d_phi_1 = TVector2::Phi_mpi_pi(nt.Muon_phi().at(leadingMu_idx) - nt.Jet_phi().at(jet));
                float d_phi_2 = TVector2::Phi_mpi_pi(nt.Muon_phi().at(subleadingMu_idx) - nt.Jet_phi().at(jet));
                float dr_jmu1 = TMath::Sqrt(d_eta_1 * d_eta_1 + d_phi_1 * d_phi_1);
                float dr_jmu2 = TMath::Sqrt(d_eta_2 * d_eta_2 + d_phi_2 * d_phi_2);
                // Reject jets if they are within dR = 0.4 of the candidate leptons
                if (dr_jmu1 < 0.4 || dr_jmu2 < 0.4)
                    continue;
                if (nt.Jet_pt().at(jet) > 30 && nt.Jet_jetId().at(jet) > 0 && nt.Jet_btagDeepFlavB().at(jet) > 0.2783) // 0.0490 for loose, 0.7100 for tight
                {
                    // nbtagDeepFlavB++; // Medium DeepJet WP
                    cand_bJets.push_back(jet);
                    h_btagDeepFlavB->Fill(nt.Jet_btagDeepFlavB().at(jet), weight * factor);
                }
            }
            h_nbtagDeepFlavB->Fill(cand_bJets.size(), weight * factor);
            h_mll_pf_pre->Fill(selectedPair_M, weight * factor);
            // if ( nbtagDeepFlavB < 1 ) continue;
            if (cand_bJets.size() < 1)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;
            h_mll_pf_btag->Fill(selectedPair_M, weight * factor);
            if (selectedPair_M < 150)
                continue;
            h_cutflow->Fill(icutflow, weight * factor);
            icutflow++;

            // Fill pT distributions for the bjets....
            if (cand_bJets.size() == 1)
            {
                h_bjet1_pt->Fill(nt.Jet_pt().at(cand_bJets[0]), weight * factor);
            }

            if (cand_bJets.size() > 1)
            {
                h_bjet1_pt->Fill(nt.Jet_pt().at(cand_bJets[0]), weight * factor);
                h_bjet2_pt->Fill(nt.Jet_pt().at(cand_bJets[1]), weight * factor);
                if (nt.Jet_pt().at(cand_bJets[0]) < nt.Jet_pt().at(cand_bJets[1]))
                    cout << "Second bjet with higher pT than the first. We need to sort the bjets!\n";
            }

            // Construct mlb pairs from selected muon pair and candidate b jets
            // float m_lb = 0;
            vector<float> m_lb_vec;
            for (int bjet = 0; bjet < cand_bJets.size(); bjet++)
            {
                if (bjet > 2)
                    continue;
                float m_mu1_b = (nt.Muon_p4().at(leadingMu_idx) + nt.Jet_p4().at(cand_bJets[bjet])).M();
                float m_mu2_b = (nt.Muon_p4().at(subleadingMu_idx) + nt.Jet_p4().at(cand_bJets[bjet])).M();
                m_lb_vec.push_back(m_mu1_b);
                m_lb_vec.push_back(m_mu2_b);
            }

            float m_lb = 0;
            for (int i = 0; i < m_lb_vec.size(); i++)
            {
                if (m_lb_vec[i] > m_lb)
                {
                    m_lb = m_lb_vec[i];
                }
            }

            float min_mlb = 10000000000000.;
            for (int k = 0; k < m_lb_vec.size(); k++)
            {
                if (m_lb_vec[k] < min_mlb)
                {
                    min_mlb = m_lb_vec[k];
                }
            }

            h_mu1_trkRelIso->Fill(nt.Muon_tkRelIso().at(leadingMu_idx), weight * factor);
            h_mu2_trkRelIso->Fill(nt.Muon_tkRelIso().at(subleadingMu_idx), weight * factor);
            h_mll_pf->Fill(selectedPair_M, weight * factor);
            h_mu1_pt->Fill(nt.Muon_pt().at(leadingMu_idx), weight * factor);
            h_mu2_pt->Fill(nt.Muon_pt().at(subleadingMu_idx), weight * factor);
            h_max_mlb->Fill(m_lb, weight * factor);
            h_min_mlb->Fill(min_mlb, weight * factor);

        } // Event loop

        delete file;

    } // File loop
    bar.finish();

    f1->Write();
    f1->Close();
    return 0;
}
