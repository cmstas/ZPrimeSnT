void plotDY_bjets(){

     TCanvas *c = new TCanvas("c","Number of pF bjets",10,10,700,700);
     TCanvas *c1 = new TCanvas("c1","Number of hF bjets",10,10,700,700);
     TCanvas *c2 = new TCanvas("c2","Number of pF+hF bjets",10,10,700,700);
     TCanvas *c3 = new TCanvas("c3","Number of non-bjets",10,10,700,700);
     TCanvas *c4 = new TCanvas("c4","p_{T} of pF bjets [GeV]",10,10,700,700);
     TCanvas *c5 = new TCanvas("c5","p_{T} of hF bjets [GeV]",10,10,700,700);
     TCanvas *c6 = new TCanvas("c6","p_{T} of pF+hF bjets [GeV]",10,10,700,700);
     TCanvas *c7 = new TCanvas("c7","p_{T} of leading pF+hF bjet [GeV]",10,10,700,700);
     TCanvas *c8 = new TCanvas("c8","p_{T} of subleading pF+hF bjet [GeV]",10,10,700,700);

     
     TFile *f2 = new TFile("temp_data/output_DrellYan_2018.root","READ");
     TH1D *h2 = (TH1D*)f2->Get("n_bjets_pF_sel6"); 
     TH1D *h2_1 = (TH1D*)f2->Get("n_bjets_hF_sel6");
     TH1D *h2_2 = (TH1D*)f2->Get("n_bjets_both_sel6");
     TH1D *h2_3 = (TH1D*)f2->Get("n_non_bjets_sel6");
     TH1D *h2_4 = (TH1D*)f2->Get("pt_bjets_pF_sel6");
     TH1D *h2_5 = (TH1D*)f2->Get("pt_bjets_hF_sel6");
     TH1D *h2_6 = (TH1D*)f2->Get("pt_bjets_both_sel6");
     TH1D *h2_7 = (TH1D*)f2->Get("pt_leading_bjet_pFhF_sel6");
     TH1D *h2_8 = (TH1D*)f2->Get("pt_second_bjet_pFhF_sel6");
     h2->SetLineColor(kBlue);
     h2_1->SetLineColor(kBlue);
     h2_2->SetLineColor(kBlue);
     h2_3->SetLineColor(kBlue);
     h2_4->SetLineColor(kBlue);
     h2_5->SetLineColor(kBlue);
     h2_6->SetLineColor(kBlue);
     h2_7->SetLineColor(kBlue);
     h2_8->SetLineColor(kBlue);


     c->cd();
     h2->Draw("hist");
     c1->cd();
     h2_1->Draw("hist");
     c2->cd();
     h2_2->Draw("hist");
     c3->cd();
     h2_3->Draw("hist");
     c4->cd();
     h2_4->Draw("hist");
     c5->cd();
     h2_5->Draw("hist");
     c6->cd();
     h2_6->Draw("hist");
     c7->cd();
     h2_7->Draw("hist");
     c8->cd();
     h2_8->Draw("hist");      
}
