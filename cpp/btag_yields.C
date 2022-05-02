vector<double> btag_yields(TString process, TString year, double mass){
       
       TString dir = "temp_data/";
       TString filestart = "output_";
       TString filetype = ".root";
       
       std::cout << dir+filestart+process+"_"+year+filetype << endl;
       TFile* file = TFile::Open(dir+filestart+process+"_"+year+filetype,"READ");
       
       TTree* tree_in = (TTree*)file->Get("tree");

       bool flag_20T,flag_20M,flag_30T,flag_30M;
       float wgt, m_ll, weighted_evts; 

       tree_in->SetBranchAddress("wgt",&wgt);
       tree_in->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_in->SetBranchAddress("m_ll",&m_ll);
       tree_in->SetBranchAddress("flag_20T",&flag_20T);
       tree_in->SetBranchAddress("flag_20M",&flag_20M);
       tree_in->SetBranchAddress("flag_30T",&flag_30T);
       tree_in->SetBranchAddress("flag_30M",&flag_30M);

       double sumWeights_20T, sumWeights_20T_MW;
       double sumWeights_20M, sumWeights_20M_MW;
       double sumWeights_30T, sumWeights_30T_MW;
       double sumWeights_30M, sumWeights_30M_MW;

       vector<double> FOMs;

       double window;

       if ( mass == 200.0 ){
            window = 40.0;
       }
       
       if ( mass == 400.0 ){
            window = 80.0;
       }

       if ( mass == 700.0 ){
            window = 140.0;
       }

       if ( mass == 1000.0 ){
            window = 200.0;
       }

       if ( mass == 1500.0 ){
            window = 300.0;
       }

       if ( mass == 2000.0 ){
            window = 400.0;
       }

       double upper_bound = mass+window;
       double lower_bound = mass-window;

       std::cout << "Number of events = " << tree_in->GetEntries() << endl;

       // Event loop for signal sample
       for (Long64_t event = 0; event < tree_in->GetEntries(); ++event){
            
            tree_in->GetEntry(event);
            if ( weighted_evts < 0.0 ) continue;
            
            if ( flag_20T ){
 
                 sumWeights_20T += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_20T_MW += weighted_evts;
                 }

            }
            
            if ( flag_20M ){
                 
                 sumWeights_20M += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_20M_MW += weighted_evts;
                 }                 

            }

            if ( flag_30T ){

                 sumWeights_30T += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_30T_MW += weighted_evts;
                 }

	    }

            if ( flag_30M ){

                 sumWeights_30M += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_30M_MW += weighted_evts;
                 }
            }

       }

       // Now do the same for DY and ttbar
       TFile* file_DY = TFile::Open("temp_data/output_DrellYan_2018.root","READ");

       TTree* tree_DY = (TTree*)file_DY->Get("tree");

       //bool flag_20T,flag_20M,flag_30T,flag_30M;
       //float wgt, m_ll, weighted_evts;

       tree_DY->SetBranchAddress("wgt",&wgt);
       tree_DY->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_DY->SetBranchAddress("m_ll",&m_ll);
       tree_DY->SetBranchAddress("flag_20T",&flag_20T);
       tree_DY->SetBranchAddress("flag_20M",&flag_20M);
       tree_DY->SetBranchAddress("flag_30T",&flag_30T);
       tree_DY->SetBranchAddress("flag_30M",&flag_30M);

       double sumWeights_20T_DY, sumWeights_20T_MW_DY;
       double sumWeights_20M_DY, sumWeights_20M_MW_DY;
       double sumWeights_30T_DY, sumWeights_30T_MW_DY;
       double sumWeights_30M_DY, sumWeights_30M_MW_DY;
 
      
       for (Long64_t event = 0; event < tree_DY->GetEntries(); ++event){

            tree_DY->GetEntry(event);
            if ( weighted_evts < 0.0 ) continue;

            if ( flag_20T ){

                 sumWeights_20T_DY += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_20T_MW_DY += weighted_evts;
                 }

            }

            if ( flag_20M ){

                 sumWeights_20M_DY += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_20M_MW_DY += weighted_evts;
                 }

            }

            if ( flag_30T ){

                 sumWeights_30T_DY += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_30T_MW_DY += weighted_evts;
                 }

            }

            if ( flag_30M ){

                 sumWeights_30M_DY += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_30M_MW_DY += weighted_evts;
                 }
            }

       }


       // Do the same for ttbar
       TFile* file_tt = TFile::Open("temp_data/output_ttbar_2018.root","READ");

       TTree* tree_tt = (TTree*)file_tt->Get("tree");

       //bool flag_20T,flag_20M,flag_30T,flag_30M;
       //float wgt, m_ll, weighted_evts;

       tree_tt->SetBranchAddress("wgt",&wgt);
       tree_tt->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_tt->SetBranchAddress("m_ll",&m_ll);
       tree_tt->SetBranchAddress("flag_20T",&flag_20T);
       tree_tt->SetBranchAddress("flag_20M",&flag_20M);
       tree_tt->SetBranchAddress("flag_30T",&flag_30T);
       tree_tt->SetBranchAddress("flag_30M",&flag_30M);

       double sumWeights_20T_tt, sumWeights_20T_MW_tt;
       double sumWeights_20M_tt, sumWeights_20M_MW_tt;
       double sumWeights_30T_tt, sumWeights_30T_MW_tt;
       double sumWeights_30M_tt, sumWeights_30M_MW_tt;


       for (Long64_t event = 0; event < tree_tt->GetEntries(); ++event){

            tree_tt->GetEntry(event);
            if ( weighted_evts < 0.0 ) continue;

            if ( flag_20T ){

                 sumWeights_20T_tt += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_20T_MW_tt += weighted_evts;
                 }

            }

            if ( flag_20M ){

                 sumWeights_20M_tt += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_20M_MW_tt += weighted_evts;
                 }

            }

            if ( flag_30T ){

                 sumWeights_30T_tt += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_30T_MW_tt += weighted_evts;
                 }

            }

            if ( flag_30M ){

                 sumWeights_30M_tt += weighted_evts;
                 if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                      sumWeights_30M_MW_tt += weighted_evts;
                 }
            }

       }   


       double FOM_20M = sumWeights_20M_MW / sqrt(sumWeights_20M_MW_DY+sumWeights_20M_MW_tt);
       double FOM_30M = sumWeights_30M_MW / sqrt(sumWeights_30M_MW_DY+sumWeights_30M_MW_tt);
       double FOM_20T = sumWeights_20T_MW / sqrt(sumWeights_20T_MW_DY+sumWeights_20T_MW_tt);
       double FOM_30T = sumWeights_30T_MW / sqrt(sumWeights_30T_MW_DY+sumWeights_30T_MW_tt); 

       std::cout << "Event yield 20M (signal) = " << sumWeights_20M << endl;
       std::cout << "Event yield 20M (DY) = " << sumWeights_20M_DY << endl; 
       std::cout << "Event yield 20M (ttbar) = " << sumWeights_20M_tt << endl;
       std::cout << "Event yield 20T (signal) = " << sumWeights_20T << endl;
       std::cout << "Event yield 20T (DY) = " << sumWeights_20T_DY << endl;
       std::cout << "Event yield 20T (ttbar) = " << sumWeights_20T_tt << endl;
       std::cout << "Event yield 30M (signal) = " << sumWeights_30M << endl;
       std::cout << "Event yield 30M (DY) = " << sumWeights_30M_DY << endl;
       std::cout << "Event yield 30M (ttbar) = " << sumWeights_30M_tt << endl;
       std::cout << "Event yield 30T (signal) = " << sumWeights_30T << endl;
       std::cout << "Event yield 30T (DY) = " << sumWeights_30T_DY << endl;
       std::cout << "Event yield 30T (ttbar) = " << sumWeights_30T_tt << endl;

       std::cout << "T/M Ratio, 20 GeV, signal = " << sumWeights_20T/sumWeights_20M << endl;
       std::cout << "T/M Ratio, 30 GeV, signal = " << sumWeights_30T/sumWeights_30M << endl;
       std::cout << "30/20 Ratio, Medium, signal = " << sumWeights_30M/sumWeights_20M << endl;
       std::cout << "30/20 Ratio, Tight, signal = " << sumWeights_30T/sumWeights_20T << endl; 

       FOMs = {FOM_20M,FOM_20T,FOM_30M,FOM_30T};
      

       return FOMs;
}
