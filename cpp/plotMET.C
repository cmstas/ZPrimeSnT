void plotMET(){

     //TFile *f1 = new TFile("temp_data/output_Y3_M100_2018.root","READ");
     //TH1D *h1 = (TH1D*)f1->Get("min_mlb");
     //h1->SetLineColor(2);
     //h1->Scale(1/h1->Integral());
     
     TFile *f2 = new TFile("temp_data/output_Y3_M200_2018.root","READ");
     TH1D *h2 = (TH1D*)f2->Get("met_post_mlb_cut"); 
     h2->SetLineColor(kRed);
     h2->Scale(1/h2->Integral());
 
     TFile *f3 = new TFile("temp_data/output_Y3_M400_2018.root","READ");
     TH1D *h3 = (TH1D*)f3->Get("met_post_mlb_cut");
     h3->SetLineColor(kOrange);
     h3->Scale(1/h3->Integral()); 

     TFile *f4 = new TFile("temp_data/output_Y3_M700_2018.root","READ");
     TH1D *h4 = (TH1D*)f4->Get("met_post_mlb_cut");
     h4->SetLineColor(kYellow);
     h4->Scale(1/h4->Integral());

     TFile *f5 = new TFile("temp_data/output_Y3_M1000_2018.root","READ");
     TH1D *h5 = (TH1D*)f5->Get("met_post_mlb_cut");
     h5->SetLineColor(kGreen);
     h5->Scale(1/h5->Integral());

     TFile *f6 = new TFile("temp_data/output_Y3_M1500_2018.root","READ");
     TH1D *h6 = (TH1D*)f6->Get("met_post_mlb_cut");
     h6->SetLineColor(kBlue);
     h6->Scale(1/h6->Integral());

     TFile *f7 = new TFile("temp_data/output_Y3_M2000_2018.root","READ");
     TH1D *h7 = (TH1D*)f7->Get("met_post_mlb_cut");
     h7->SetLineColor(kViolet);
     h7->Scale(1/h7->Integral());

     TFile *f8 = new TFile("temp_data/output_ttbar_2018.root","READ");
     TH1D *h8 = (TH1D*)f8->Get("met_post_mlb_cut");
     h8->SetLineColor(kBlack);
     h8->Scale(1/h8->Integral());

     //Define the legend...
     TLegend* legend = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend->SetBorderSize(0);
     legend->SetTextFont(43);
     legend->SetTextAlign(12);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillColor(0);
     legend->SetFillStyle(0);

     //Add entries to the legend....
     legend->AddEntry(h2,"Y3 M200","f");
     legend->AddEntry(h3,"Y3 M400","f");
     legend->AddEntry(h4,"Y3 M700","f");
     legend->AddEntry(h5,"Y3 M1000","f");
     legend->AddEntry(h6,"Y3 M1500","f");
     legend->AddEntry(h7,"Y3 M2000","f");
     legend->AddEntry(h8,"ttbar","f");
      
     //Draw histograms on same canvas
     //h1->Draw("hist l");
     h2->Draw("hist l");
     h3->Draw("hist l same");
     h4->Draw("hist l same");
     h5->Draw("hist l same");
     h6->Draw("hist l same");
     h7->Draw("hist l same");   
     h8->Draw("hist l same");

     legend->Draw();
    
}
