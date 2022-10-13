#include <iostream>
#include <vector>

using namespace std;

void histoDefinition(map<TString, int> &nbins, map<TString, float> &low, map<TString, float> &high, map<TString, vector<float>> &binsx, map<TString, TString> &title) {

  float tbsize = 0.10;
  float tbsizemass = 0.025;
  float tbedge = 0.0;

  // MET Variables
  low.insert({"pfmet_pt", 25.0});
  high.insert({"pfmet_pt", 600.0});
  tbedge = low["pfmet_pt"];
  binsx["pfmet_pt"].push_back(tbedge);
  while ( tbedge < high["pfmet_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["pfmet_pt"].push_back(tbedge);
  }
  nbins.insert({"pfmet_pt", binsx["pfmet_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"pfmet_pt", "PF MET [GeV]"});

  nbins.insert({"pfmet_phi", 65});
  low.insert({"pfmet_phi", -3.25});
  high.insert({"pfmet_phi", 3.25});
  title.insert({"pfmet_phi", "PF MET #phi"});

  low.insert({"puppimet_pt", 25.0});
  high.insert({"puppimet_pt", 600.0});
  tbedge = low["puppimet_pt"];
  binsx["puppimet_pt"].push_back(tbedge);
  while ( tbedge < high["puppimet_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["puppimet_pt"].push_back(tbedge);
  }
  nbins.insert({"puppimet_pt", binsx["puppimet_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"puppimet_pt", "PUPPI MET [GeV]"});

  nbins.insert({"puppimet_phi", 65});
  low.insert({"puppimet_phi", -3.25});
  high.insert({"puppimet_phi", 3.25});
  title.insert({"puppimet_phi", "PUPPI MET #phi"});

  // Basic muon properties and masses
  //nbins.insert({"mmumu", 580}); // for fix 5 GeV binning
  low.insert({"mmumu", 100.0});
  high.insert({"mmumu", 3000.0});
  tbedge = low["mmumu"];
  binsx["mmumu"].push_back(tbedge);
  while ( tbedge < 175.0 ){
    tbedge += 2.5;
    binsx["mmumu"].push_back(tbedge);
  }
  while ( tbedge < high["mmumu"] ) {
    tbedge += tbedge*tbsizemass;
    binsx["mmumu"].push_back(tbedge);
  }
  nbins.insert({"mmumu", binsx["mmumu"].size()-1});
  tbedge = 0.0;
  title.insert({"mmumu", "m_{#mu#mu} [GeV]"});

  //nbins.insert({"mu1_pt", 200}); // for fix 5 GeV binning
  low.insert({"mu1_pt", 10});
  high.insert({"mu1_pt", 1010});
  tbedge = low["mu1_pt"];
  binsx["mu1_pt"].push_back(tbedge);
  while ( tbedge < 100.0 ){
    tbedge += 10.0;
    binsx["mu1_pt"].push_back(tbedge);
  }
  while ( tbedge < high["mu1_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["mu1_pt"].push_back(tbedge);
  }
  nbins.insert({"mu1_pt", binsx["mu1_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"mu1_pt", "p_{T} (leading #mu) [GeV]"});

  //nbins.insert({"mu2_pt", 200}); // for fix 5 GeV binning
  low.insert({"mu2_pt", 10});
  high.insert({"mu2_pt", 1010});
  tbedge = low["mu2_pt"];
  binsx["mu2_pt"].push_back(tbedge);
  while ( tbedge < 100.0 ){
    tbedge += 10.0;
    binsx["mu2_pt"].push_back(tbedge);
  }
  while ( tbedge < high["mu2_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["mu2_pt"].push_back(tbedge);
  }
  nbins.insert({"mu2_pt", binsx["mu2_pt"].size()-1});
  tbedge = 0.0;
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

  nbins.insert({"mu1_dxy", 200});
  low.insert({"mu1_dxy", 0.001});
  high.insert({"mu1_dxy", 0.021});
  title.insert({"mu1_dxy", "|d_{xy}| (leading #mu) [cm]"});

  nbins.insert({"mu2_dxy", 200});
  low.insert({"mu2_dxy", 0.001});
  high.insert({"mu2_dxy", 0.021});
  title.insert({"mu2_dxy", "|d_{xy}| (subleading #mu) [cm]"});

  nbins.insert({"mu1_dz", 100});
  low.insert({"mu1_dz", 0.001});
  high.insert({"mu1_dz", 0.101});
  title.insert({"mu1_dz", "|d_{z}| (leading #mu) [cm]"});

  nbins.insert({"mu2_dz", 100});
  low.insert({"mu2_dz", 0.001});
  high.insert({"mu2_dz", 0.101});
  title.insert({"mu2_dz", "|d_{z}| (subleading #mu) [cm]"});

  nbins.insert({"mu1_relPtErr", 100});
  low.insert({"mu1_relPtErr", 0.001});
  high.insert({"mu1_relPtErr", 1.001});
  title.insert({"mu1_relPtErr", "Relative p_{T} error (leading #mu)"});

  nbins.insert({"mu2_relPtErr", 100});
  low.insert({"mu2_relPtErr", 0.001});
  high.insert({"mu2_relPtErr", 1.001});
  title.insert({"mu2_relPtErr", "Relative p_{T} error (subleading #mu)"});

  nbins.insert({"mu1_tunepRelPt", 100});
  low.insert({"mu1_tunepRelPt", 0.001});
  high.insert({"mu1_tunepRelPt", 2.001});
  title.insert({"mu1_tunepRelPt", "TuneP relative p_{T} (leading #mu)"});

  nbins.insert({"mu2_tunepRelPt", 100});
  low.insert({"mu2_tunepRelPt", 0.001});
  high.insert({"mu2_tunepRelPt", 2.001});
  title.insert({"mu2_tunepRelPt", "TuneP relative p_{T} (subleading #mu)"});

  nbins.insert({"mu1_trkRelIso", 100});
  low.insert({"mu1_trkRelIso", 0.001});
  high.insert({"mu1_trkRelIso", 0.051});
  title.insert({"mu1_trkRelIso", "Track iso./p_{T} (leading #mu)"});

  nbins.insert({"mu2_trkRelIso", 100});
  low.insert({"mu2_trkRelIso", 0.001});
  high.insert({"mu2_trkRelIso", 0.051});
  title.insert({"mu2_trkRelIso", "Track iso./p_{T} (subleading #mu)"});

  nbins.insert({"mu1_trkAbsIso", 100});
  low.insert({"mu1_trkAbsIso", 0.1});
  high.insert({"mu1_trkAbsIso", 5.1});
  title.insert({"mu1_trkAbsIso", "Track iso. (leading #mu)"});

  nbins.insert({"mu2_trkAbsIso", 100});
  low.insert({"mu2_trkAbsIso", 0.1});
  high.insert({"mu2_trkAbsIso", 5.1});
  title.insert({"mu2_trkAbsIso", "Track iso. (subleading #mu)"});

  nbins.insert({"nCand_Muons", 4});
  low.insert({"nCand_Muons", 2});
  high.insert({"nCand_Muons", 6});
  title.insert({"nCand_Muons", "Number of #mu candidates"});

  // Extra lepton properties: Muon
  nbins.insert({"nExtra_muons", 6});
  low.insert({"nExtra_muons", 0});
  high.insert({"nExtra_muons", 6});
  title.insert({"nExtra_muons", "Number of additional #mu's"});

  //nbins.insert({"mu3_pt", 200}); // for fix 5 GeV binning
  low.insert({"mu3_pt", 5});
  high.insert({"mu3_pt", 1005});
  tbedge = low["mu3_pt"];
  binsx["mu3_pt"].push_back(tbedge);
  while ( tbedge < 100.0 ){
    tbedge += 10.0;
    binsx["mu3_pt"].push_back(tbedge);
  }
  while ( tbedge < high["mu3_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["mu3_pt"].push_back(tbedge);
  }
  nbins.insert({"mu3_pt", binsx["mu3_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"mu3_pt", "p_{T} (third #mu) [GeV]"});

  nbins.insert({"mu3_eta", 60});
  low.insert({"mu3_eta", -3});
  high.insert({"mu3_eta", 3});
  title.insert({"mu3_eta", "#eta (third #mu)"});

  nbins.insert({"mu3_trkRelIso", 50});
  low.insert({"mu3_trkRelIso", 0.01});
  high.insert({"mu3_trkRelIso", 0.51});
  title.insert({"mu3_trkRelIso", "Track iso./p_{T} (third #mu)"});

  nbins.insert({"mu3_trkAbsIso", 50});
  low.insert({"mu3_trkAbsIso", 1.0});
  high.insert({"mu3_trkAbsIso", 51});
  title.insert({"mu3_trkAbsIso", "Track iso. (third #mu)"});

  // Extra lepton properties: Electrons
  nbins.insert({"nExtra_electrons", 6});
  low.insert({"nExtra_electrons", 0});
  high.insert({"nExtra_electrons", 6});
  title.insert({"nExtra_electrons", "Number of electrons"});

  //nbins.insert({"ele_extra_pt", 200}); // for fix 5 GeV binning
  low.insert({"ele_extra_pt", 5});
  high.insert({"ele_extra_pt", 1005});
  tbedge = low["ele_extra_pt"];
  binsx["ele_extra_pt"].push_back(tbedge);
  while ( tbedge < 50.0 ){
    tbedge += 5.0;
    binsx["ele_extra_pt"].push_back(tbedge);
  }
  while ( tbedge < high["ele_extra_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["ele_extra_pt"].push_back(tbedge);
  }
  nbins.insert({"ele_extra_pt", binsx["ele_extra_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"ele_extra_pt", "p_{T} (extra electron) [GeV]"});

  nbins.insert({"ele_extra_eta", 60});
  low.insert({"ele_extra_eta", -3});
  high.insert({"ele_extra_eta", 3});
  title.insert({"ele_extra_eta", "#eta (extra electron)"});

  //nbins.insert({"ele_extra_miniPFRelIso", 50});
  //low.insert({"ele_extra_miniPFRelIso", 0.01});
  //high.insert({"ele_extra_miniPFRelIso", 0.51});
  //title.insert({"ele_extra_miniPFRelIso", "PF mini-iso./p_{T} (extra electron)"});

  // Extra lepton properties: Isotracks
  nbins.insert({"nExtra_lepIsoTracks", 6});
  low.insert({"nExtra_lepIsoTracks", 0});
  high.insert({"nExtra_lepIsoTracks", 6});
  title.insert({"nExtra_lepIsoTracks", "Number of (additional) lepton (e/#mu) PF candidates"});

  //nbins.insert({"lepIsoTrack_extra_pt", 200}); // for fix 5 GeV binning
  low.insert({"lepIsoTrack_extra_pt", 5});
  high.insert({"lepIsoTrack_extra_pt", 1005});
  tbedge = low["lepIsoTrack_extra_pt"];
  binsx["lepIsoTrack_extra_pt"].push_back(tbedge);
  while ( tbedge < 50.0 ){
    tbedge += 5.0;
    binsx["lepIsoTrack_extra_pt"].push_back(tbedge);
  }
  while ( tbedge < high["lepIsoTrack_extra_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["lepIsoTrack_extra_pt"].push_back(tbedge);
  }
  nbins.insert({"lepIsoTrack_extra_pt", binsx["lepIsoTrack_extra_pt"].size()-1});
  tbedge = 0.0;
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

  //nbins.insert({"chhIsoTrack_extra_pt", 200}); // for fix 5 GeV binning
  low.insert({"chhIsoTrack_extra_pt", 5});
  high.insert({"chhIsoTrack_extra_pt", 1005});
  tbedge = low["chhIsoTrack_extra_pt"];
  binsx["chhIsoTrack_extra_pt"].push_back(tbedge);
  while ( tbedge < 50.0 ){
    tbedge += 5.0;
    binsx["chhIsoTrack_extra_pt"].push_back(tbedge);
  }
  while ( tbedge < high["chhIsoTrack_extra_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["chhIsoTrack_extra_pt"].push_back(tbedge);
  }
  nbins.insert({"chhIsoTrack_extra_pt", binsx["chhIsoTrack_extra_pt"].size()-1});
  tbedge = 0.0;
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

  nbins.insert({"jet1_pt", 300}); // for fix 5 GeV binning
  low.insert({"jet1_pt", 20});
  high.insert({"jet1_pt", 1520});
  title.insert({"jet1_pt", "p_{T} (leading jet) [GeV]"});

  nbins.insert({"jet1_eta", 60});
  low.insert({"jet1_eta", -3});
  high.insert({"jet1_eta", 3});
  title.insert({"jet1_eta", "#eta (leading jet) [GeV]"});

  nbins.insert({"st_scalar_jet", 300}); // for fix 5 GeV binning
  low.insert({"st_scalar_jet", 20});
  high.insert({"st_scalar_jet", 1520});
  title.insert({"st_scalar_jet", "Scalar sum of MET+#mu_{1}+#mu_{2}+Jet_{1} p_{T} [GeV]"});

  nbins.insert({"st_vector_jet", 300}); // for fix 5 GeV binning
  low.insert({"st_vector_jet", 20});
  high.insert({"st_vector_jet", 1520});
  title.insert({"st_vector_jet", "p_{T} of vector sum of MET+#mu_{1}+#mu_{2}+Jet_{1} [GeV]"});

  //nbins.insert({"bjet1_pt", 300}); // for fix 5 GeV binning
  low.insert({"bjet1_pt", 20});
  high.insert({"bjet1_pt", 1520});
  tbedge = low["bjet1_pt"];
  binsx["bjet1_pt"].push_back(tbedge);
  while ( tbedge < 100.0 ){
    tbedge += 10.0;
    binsx["bjet1_pt"].push_back(tbedge);
  }
  while ( tbedge < high["bjet1_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["bjet1_pt"].push_back(tbedge);
  }
  nbins.insert({"bjet1_pt", binsx["bjet1_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"bjet1_pt", "p_{T} (leading b-tagged jet) [GeV]"});

  nbins.insert({"bjet1_eta", 60});
  low.insert({"bjet1_eta", -3});
  high.insert({"bjet1_eta", 3});
  title.insert({"bjet1_eta", "#eta (leading b-tagged jet) [GeV]"});

  //nbins.insert({"bjet2_pt", 300}); // for fix 5 GeV binning
  low.insert({"bjet2_pt", 20});
  high.insert({"bjet2_pt", 1520});
  tbedge = low["bjet2_pt"];
  binsx["bjet2_pt"].push_back(tbedge);
  while ( tbedge < 100.0 ){
    tbedge += 10.0;
    binsx["bjet2_pt"].push_back(tbedge);
  }
  while ( tbedge < high["bjet2_pt"] ) {
    tbedge += tbedge*tbsize;
    binsx["bjet2_pt"].push_back(tbedge);
  }
  nbins.insert({"bjet2_pt", binsx["bjet2_pt"].size()-1});
  tbedge = 0.0;
  title.insert({"bjet2_pt", "p_{T} (subleading b-tagged jet) [GeV]"});

  nbins.insert({"bjet2_eta", 60});
  low.insert({"bjet2_eta", -3});
  high.insert({"bjet2_eta", 3});
  title.insert({"bjet2_eta", "#eta (subleading b-tagged jet) [GeV]"});

  //nbins.insert({"min_mlb", 300}); // for fix 5 GeV binning
  low.insert({"min_mlb", 5.0});
  high.insert({"min_mlb", 1505.0});
  tbedge = low["min_mlb"];
  binsx["min_mlb"].push_back(tbedge);
  while ( tbedge < 200.0 ){
    tbedge += 5.0;
    binsx["min_mlb"].push_back(tbedge);
  }
  while ( tbedge < high["min_mlb"] ) {
    tbedge += tbedge*tbsizemass;
    binsx["min_mlb"].push_back(tbedge);
  }
  nbins.insert({"min_mlb", binsx["min_mlb"].size()-1});
  tbedge = 0.0;
  title.insert({"min_mlb", "min m_{#mu b} [GeV]"});

  //nbins.insert({"min_mbb", 300}); // for fix 5 GeV binnng
  low.insert({"min_mbb", 5.0});
  high.insert({"min_mbb", 1505.0});
  tbedge = low["min_mbb"];
  binsx["min_mbb"].push_back(tbedge);
  while ( tbedge < 200.0 ){
    tbedge += 5.0;
    binsx["min_mbb"].push_back(tbedge);
  }
  while ( tbedge < high["min_mbb"] ) {
    tbedge += tbedge*tbsizemass;
    binsx["min_mbb"].push_back(tbedge);
  }
  nbins.insert({"min_mbb", binsx["min_mbb"].size()-1});
  tbedge = 0.0;
  title.insert({"min_mbb", "min m_{bb} [GeV]"});

  //nbins.insert({"max_mbb", 300}); // for fix 5 GeV binning
  low.insert({"max_mbb", 1.0});
  high.insert({"max_mbb", 1501.0});
  tbedge = low["max_mbb"];
  binsx["max_mbb"].push_back(tbedge);
  while ( tbedge < 200.0 ){
    tbedge += 5.0;
    binsx["max_mbb"].push_back(tbedge);
  }
  while ( tbedge < high["max_mbb"] ) {
    tbedge += tbedge*tbsizemass;
    binsx["max_mbb"].push_back(tbedge);
  }
  nbins.insert({"max_mbb", binsx["max_mbb"].size()-1});
  tbedge = 0.0;
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

  nbins.insert({"st_scalar_bjet", 300}); // for fix 5 GeV binning
  low.insert({"st_scalar_bjet", 20});
  high.insert({"st_scalar_bjet", 1520});
  title.insert({"st_scalar_bjet", "Scalar sum of MET+#mu_{1}+#mu_{2}+b-jet_{1} p_{T} [GeV]"});

  nbins.insert({"st_vector_bjet", 300}); // for fix 5 GeV binning
  low.insert({"st_vector_bjet", 20});
  high.insert({"st_vector_bjet", 1520});
  title.insert({"st_vector_bjet", "p_{T} of vector sum of MET+#mu_{1}+#mu_{2}+b-jet_{1} [GeV]"});

  nbins.insert({"dPhi_ll_MET", 32});
  low.insert({"dPhi_ll_MET", 0});
  high.insert({"dPhi_ll_MET", 3.2});
  title.insert({"dPhi_ll_MET", "|#Delta#phi(#mu#mu,MET)|"});
}

void histo2DDefinition(map<TString, int> nbins, map<TString, float> low, map<TString, float> high, map<TString, TString> title,
                       map<TString, int> &nbinsX, map<TString, float> &lowX, map<TString, float> &highX, map<TString, TString> &xtitle,
                       map<TString, int> &nbinsY, map<TString, float> &lowY, map<TString, float> &highY, map<TString, TString> &ytitle) {

  nbinsX.insert({"jet1_pt_VS_st_scalar_jet", nbins["jet1_pt"]});
  lowX.insert({"jet1_pt_VS_st_scalar_jet", low["jet1_pt"]});
  highX.insert({"jet1_pt_VS_st_scalar_jet", high["jet1_pt"]});
  xtitle.insert({"jet1_pt_VS_st_scalar_jet", title["jet1_pt"]});
  nbinsY.insert({"jet1_pt_VS_st_scalar_jet", nbins["st_scalar_jet"]});
  lowY.insert({"jet1_pt_VS_st_scalar_jet", low["st_scalar_jet"]});
  highY.insert({"jet1_pt_VS_st_scalar_jet", high["st_scalar_jet"]});
  ytitle.insert({"jet1_pt_VS_st_scalar_jet", title["st_scalar_jet"]});

  nbinsX.insert({"jet1_pt_VS_st_vector_jet", nbins["jet1_pt"]});
  lowX.insert({"jet1_pt_VS_st_vector_jet", low["jet1_pt"]});
  highX.insert({"jet1_pt_VS_st_vector_jet", high["jet1_pt"]});
  xtitle.insert({"jet1_pt_VS_st_vector_jet", title["jet1_pt"]});
  nbinsY.insert({"jet1_pt_VS_st_vector_jet", nbins["st_vector_jet"]});
  lowY.insert({"jet1_pt_VS_st_vector_jet", low["st_vector_jet"]});
  highY.insert({"jet1_pt_VS_st_vector_jet", high["st_vector_jet"]});
  ytitle.insert({"jet1_pt_VS_st_vector_jet", title["st_vector_jet"]});

  nbinsX.insert({"bjet1_pt_VS_st_scalar_bjet", 300/*nbins["bjet1_pt"]*/});
  lowX.insert({"bjet1_pt_VS_st_scalar_bjet", low["bjet1_pt"]});
  highX.insert({"bjet1_pt_VS_st_scalar_bjet", high["bjet1_pt"]});
  xtitle.insert({"bjet1_pt_VS_st_scalar_bjet", title["bjet1_pt"]});
  nbinsY.insert({"bjet1_pt_VS_st_scalar_bjet", nbins["st_scalar_bjet"]});
  lowY.insert({"bjet1_pt_VS_st_scalar_bjet", low["st_scalar_bjet"]});
  highY.insert({"bjet1_pt_VS_st_scalar_bjet", high["st_scalar_bjet"]});
  ytitle.insert({"bjet1_pt_VS_st_scalar_bjet", title["st_scalar_bjet"]});

  nbinsX.insert({"bjet1_pt_VS_st_vector_bjet", 300/*nbins["bjet1_pt"]*/});
  lowX.insert({"bjet1_pt_VS_st_vector_bjet", low["bjet1_pt"]});
  highX.insert({"bjet1_pt_VS_st_vector_bjet", high["bjet1_pt"]});
  xtitle.insert({"bjet1_pt_VS_st_vector_bjet", title["bjet1_pt"]});
  nbinsY.insert({"bjet1_pt_VS_st_vector_bjet", nbins["st_vector_bjet"]});
  lowY.insert({"bjet1_pt_VS_st_vector_bjet", low["st_vector_bjet"]});
  highY.insert({"bjet1_pt_VS_st_vector_bjet", high["st_vector_bjet"]});
  ytitle.insert({"bjet1_pt_VS_st_vector_bjet", title["st_vector_bjet"]});
}

void mllbinDefinitionForBFF(vector<TString> &mllbin, map<TString, TString> &mllbinlabel) {
  mllbin.push_back("mllinclusive");
  mllbin.push_back("mll225to275");
  mllbin.push_back("mll315to385");
  mllbin.push_back("mll360to440");
  mllbin.push_back("mll450to550");
  mllbin.push_back("mll630to770");
  mllbin.push_back("mll900to1100");

  mllbinlabel["mllinclusive"]="m_{#mu#mu} > 0 GeV";
  mllbinlabel["mll225to275"]="225 < m_{#mu#mu} < 275 GeV";
  mllbinlabel["mll315to385"]="315 < m_{#mu#mu} < 385 GeV";
  mllbinlabel["mll360to440"]="360 < m_{#mu#mu} < 440 GeV";
  mllbinlabel["mll450to550"]="450 < m_{#mu#mu} < 550 GeV";
  mllbinlabel["mll630to770"]="630 < m_{#mu#mu} < 770 GeV";
  mllbinlabel["mll900to1100"]="900 < m_{#mu#mu} < 1100 GeV";
}

void mllbinDefinition(vector<TString> &mllbin, bool doMllBins, map<TString, TString> &mllbinlabel) {
  mllbin.push_back("mllinclusive");
  if ( doMllBins ) {
    mllbin.push_back("mll175to300");
    mllbin.push_back("mll300to500");
    mllbin.push_back("mll500to900");
    mllbin.push_back("mll750to1250");
    mllbin.push_back("mll1100to1900");
    mllbin.push_back("mll1500to2500");
  }

  mllbinlabel["mllinclusive"]="m_{#mu#mu} > 0 GeV";
  mllbinlabel["mll175to300"]="175 < m_{#mu#mu} < 300 GeV";
  mllbinlabel["mll300to500"]="300 < m_{#mu#mu} < 500 GeV";
  mllbinlabel["mll500to900"]="500 < m_{#mu#mu} < 900 GeV";
  mllbinlabel["mll750to1250"]="750 <m_{#mu#mu} < 1250 GeV";
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

void prodModeDefinition(vector<TString> &prodMode, bool doProdModeBins, map<TString, TString> &prodModelabel) {
  prodMode.push_back("");
  if ( doProdModeBins ) {
    prodMode.push_back("_ssProdModes");
    prodMode.push_back("_bsProdModes");
    prodMode.push_back("_bbProdModes");
  }

  prodModelabel["all"]="All production modes";
  prodModelabel["ss"]="bs production mode";
  prodModelabel["bs"]="bs production mode";
  prodModelabel["bb"]="bb production mode";
}
