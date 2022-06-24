#include <iostream>

using namespace std;

void histoDefinition(map<TString, int> &nbins, map<TString, float> &low, map<TString, float> &high, map<TString, TString> &title) {

  // MET Variables
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

  // Basic muon properties and masses
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

  // Extra lepton properties: Muon
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

  // Extra lepton properties: Electrons
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

  // Extra lepton properties: Isotracks
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

  // Basic btag properties and masses
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

  // Angular variables
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

  nbins.insert({"minDPhi_b_MET", 32});
  low.insert({"minDPhi_b_MET", 0});
  high.insert({"minDPhi_b_MET", 3.2});
  title.insert({"minDPhi_b_MET", "min #Delta#phi(b,MET)"});

  nbins.insert({"maxDPhi_b_MET", 32});
  low.insert({"maxDPhi_b_MET", 0});
  high.insert({"maxDPhi_b_MET", 3.2});
  title.insert({"maxDPhi_b_MET", "max #Delta#phi(b,MET)"});

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

  nbins.insert({"maxDPhi_l_MET", 32});
  low.insert({"maxDPhi_l_MET", 0});
  high.insert({"maxDPhi_l_MET", 3.2});
  title.insert({"maxDPhi_l_MET", "max #Delta#phi(#mu,MET)"});

  nbins.insert({"minDPhi_l_b", 32});
  low.insert({"minDPhi_l_b", 0});
  high.insert({"minDPhi_l_b", 3.2});
  title.insert({"minDPhi_l_b", "min #Delta#phi(#mu, b)"});

  nbins.insert({"dPhi_ll_MET", 32});
  low.insert({"dPhi_ll_MET", 0});
  high.insert({"dPhi_ll_MET", 3.2});
  title.insert({"dPhi_ll_MET", "|#Delta#phi(#mu#mu,MET)|"});
}

void mllbinDefinition(vector<TString> &mllbin, bool doMllBins, map<TString, TString> &mllbinlabel) {
  mllbin.push_back("mllinclusive");
  if ( doMllBins ) {
    mllbin.push_back("mll150to250");
    mllbin.push_back("mll200to600");
    mllbin.push_back("mll500to900");
    mllbin.push_back("mll700to1300");
    mllbin.push_back("mll1100to1900");
    mllbin.push_back("mll1500to2500");
  }

  mllbinlabel["mllinclusive"]="m_{#mu#mu} > 0 GeV";
  mllbinlabel["mll150to250"]="150 < m_{#mu#mu} < 250 GeV";
  mllbinlabel["mll200to600"]="200 < m_{#mu#mu} < 600 GeV";
  mllbinlabel["mll500to900"]="500 < m_{#mu#mu} < 900 GeV";
  mllbinlabel["mll700to1300"]="700 <m_{#mu#mu} < 1300 GeV";
  mllbinlabel["mll1100to1900"]="1.1 < m_{#mu#mu} < 1.9 TeV";
  mllbinlabel["mll1500to2500"]="1.5 < m_{#mu#mu} < 2.5 TeV";
}

void btagbinDefinition(vector<TString> &nbtag, bool doNbTagBins, map<TString, TString> &nbtagbinlabel, bool doDYEnriched) {
  nbtag.push_back("nBTag1p");
  if ( doNbTagBins ) {
    if (doDYEnriched) nbtag.push_back("nBTag0");
    nbtag.push_back("nBTag1");
    nbtag.push_back("nBTag2p");
  }

  nbtagbinlabel["nBTag1p"]="N_{b-tag}#geq 1 (p_{T}>20 GeV, medium WP)";
  if (doDYEnriched) nbtagbinlabel["nBTag0"] = "N_{b-tag}= 0 (p_{T}>20 GeV, medium WP)";
  nbtagbinlabel["nBTag1"]="N_{b-tag}= 1 (p_{T}>20 GeV, medium WP)";
  nbtagbinlabel["nBTag2p"]="N_{b-tag}#geq 2 (p_{T}>20 GeV, medium WP)";
}

void muonregionbinDefinition(vector<TString> &MuDetRegion, bool doMuDetRegionBins, map<TString, TString> &MuDetRegionbinlabel) {
  MuDetRegion.push_back("MuDetAll");
  if (doMuDetRegionBins)
    {
      MuDetRegion.push_back("BB");
      MuDetRegion.push_back("BE");
      MuDetRegion.push_back("EE");
    }

  MuDetRegionbinlabel["BB"] = "2 muons in Barrel";
  MuDetRegionbinlabel["BE"] = "1 muon in Barrel, 1 muon in Endcap)";
  MuDetRegionbinlabel["EE"] = "2 muons in Endcap";
}
