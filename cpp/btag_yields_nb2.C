vector<double> btag_yields_nb2(TString process, TString year, double mass){
       
       TString dir = "temp_data/";
       TString filestart = "output_";
       TString filetype = ".root";
       
       std::cout << dir+filestart+process+"_"+year+"nb2"+filetype << endl;
       TFile* file = TFile::Open(dir+filestart+process+"_"+year+"nb2"+filetype,"READ");
       
       TTree* tree_in = (TTree*)file->Get("tree");

       bool flag_TT, flag_TT_1b, flag_TM, flag_TM_1b, flag_TL, flag_TL_1b;
       float wgt, m_ll, weighted_evts; 


       std::cout << "1" << endl;
       tree_in->SetBranchAddress("wgt",&wgt);
       tree_in->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_in->SetBranchAddress("m_ll",&m_ll);
       tree_in->SetBranchAddress("flag_TT",&flag_TT);
       tree_in->SetBranchAddress("flag_TT_1b",&flag_TT_1b);
       tree_in->SetBranchAddress("flag_TM",&flag_TM);
       tree_in->SetBranchAddress("flag_TM_1b",&flag_TM_1b);
       tree_in->SetBranchAddress("flag_TL",&flag_TL);
       tree_in->SetBranchAddress("flag_TL_1b",&flag_TL_1b);

       std::cout << "2" << endl;

       double sumW_TT = 0;
       double sumW_TT_1b = 0;
       double sumW_TM = 0;
       double sumW_TM_1b = 0;
       double sumW_TL = 0;
       double sumW_TL_1b = 0;
       double ssW_TT = 0;
       double ssW_TT_1b = 0;
       double ssW_TM = 0;
       double ssW_TM_1b = 0;
       double ssW_TL = 0;
       double ssW_TL_1b = 0; 

       vector<double> yields;

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

       int n_TT = 0;
       int n_TT_1b = 0;
       int n_TM = 0;
       int n_TM_1b = 0;
       int n_TL = 0;
       int n_TL_1b = 0;

       std::cout << "Number of events = " << tree_in->GetEntries() << endl;

       // Event loop for signal sample
       for (Long64_t event = 0; event < tree_in->GetEntries(); ++event){
            
            tree_in->GetEntry(event);
            //if ( weighted_evts < 0.0 ) continue;
            
            if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                 
                 if ( flag_TT ){
                      sumW_TT += weighted_evts;
                      ssW_TT += pow(weighted_evts,2.0);
                      n_TT++;
                 }
                  
                 if ( flag_TT_1b ){
                      sumW_TT_1b += weighted_evts;
                      ssW_TT_1b += pow(weighted_evts,2.0);
                      n_TT_1b++;
                 }
 
                 if ( flag_TM ){
                      sumW_TM += weighted_evts;
                      ssW_TM += pow(weighted_evts,2.0);
                      n_TM++;
                 }

                 if ( flag_TM_1b ){
                      sumW_TM_1b += weighted_evts;
                      ssW_TM_1b += pow(weighted_evts,2.0);
                      n_TM_1b++;
                 }

                 if ( flag_TL ){
                      sumW_TL += weighted_evts;
                      ssW_TL += pow(weighted_evts,2.0);
                      n_TL++;
                 }
        
                 if ( flag_TL_1b ){
                      sumW_TL_1b += weighted_evts;
                      ssW_TL_1b += pow(weighted_evts,2.0);
                      n_TL_1b++;
                 }
 
            }
            
       }

       // Now do the same for DY and ttbar
       TFile* file_DY = TFile::Open("temp_data/output_DrellYan_2018nb2.root","READ");

       TTree* tree_DY = (TTree*)file_DY->Get("tree");

       //bool flag_20T,flag_20M,flag_30T,flag_30M;
       //float wgt, m_ll, weighted_evts;

      
       tree_DY->SetBranchAddress("wgt",&wgt);
       tree_DY->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_DY->SetBranchAddress("m_ll",&m_ll);
       tree_DY->SetBranchAddress("flag_TT",&flag_TT);
       tree_DY->SetBranchAddress("flag_TT_1b",&flag_TT_1b);
       tree_DY->SetBranchAddress("flag_TM",&flag_TM);
       tree_DY->SetBranchAddress("flag_TM_1b",&flag_TM_1b);
       tree_DY->SetBranchAddress("flag_TL",&flag_TL);
       tree_DY->SetBranchAddress("flag_TL_1b",&flag_TL_1b);

       std::cout << "3" << endl;
       
       double sumW_TT_DY = 0;
       double sumW_TT_1b_DY = 0;
       double sumW_TM_DY = 0;
       double sumW_TM_1b_DY = 0;
       double sumW_TL_DY = 0;
       double sumW_TL_1b_DY = 0;
       double ssW_TT_DY = 0;
       double ssW_TT_1b_DY = 0;
       double ssW_TM_DY = 0;
       double ssW_TM_1b_DY = 0;
       double ssW_TL_DY = 0;
       double ssW_TL_1b_DY = 0;       
 
      
       for (Long64_t event = 0; event < tree_DY->GetEntries(); ++event){

            tree_DY->GetEntry(event);
            //if ( weighted_evts < 0.0 ) continue;

            if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                 
                 if ( flag_TT ){
                      sumW_TT_DY += weighted_evts;
                      ssW_TT_DY += pow(weighted_evts,2.0);
                 }

                 if ( flag_TT_1b ){
                      sumW_TT_1b_DY += weighted_evts;
                      ssW_TT_1b_DY += pow(weighted_evts,2.0);
                 }

                 if ( flag_TM ){
                      sumW_TM_DY += weighted_evts;
                      ssW_TM_DY += pow(weighted_evts,2.0);
                 }

                 if ( flag_TM_1b ){
                      sumW_TM_1b_DY += weighted_evts;
                      ssW_TM_1b_DY += pow(weighted_evts,2.0);
                 }

                 if ( flag_TL ){
                      sumW_TL_DY += weighted_evts;
                      ssW_TL_DY += pow(weighted_evts,2.0);
                 }

                 if ( flag_TL_1b ){
                      sumW_TL_1b_DY += weighted_evts;
                      ssW_TL_1b_DY += pow(weighted_evts,2.0);
                 }
          
            }
       }


       // Do the same for ttbar
       TFile* file_tt = TFile::Open("temp_data/output_ttbar_2018nb2.root","READ");

       TTree* tree_tt = (TTree*)file_tt->Get("tree");

       //bool flag_20T,flag_20M,flag_30T,flag_30M;
       //float wgt, m_ll, weighted_evts;

       tree_tt->SetBranchAddress("wgt",&wgt);
       tree_tt->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_tt->SetBranchAddress("m_ll",&m_ll);
       tree_tt->SetBranchAddress("flag_TT",&flag_TT);
       tree_tt->SetBranchAddress("flag_TT_1b",&flag_TT_1b);
       tree_tt->SetBranchAddress("flag_TM",&flag_TM);
       tree_tt->SetBranchAddress("flag_TM_1b",&flag_TM_1b);
       tree_tt->SetBranchAddress("flag_TL",&flag_TL);
       tree_tt->SetBranchAddress("flag_TL_1b",&flag_TL_1b);       
       
       double sumW_TT_tt = 0;
       double sumW_TT_1b_tt = 0;
       double sumW_TM_tt = 0; 
       double sumW_TM_1b_tt = 0; 
       double sumW_TL_tt = 0;
       double sumW_TL_1b_tt = 0;
       double ssW_TT_tt = 0; 
       double ssW_TT_1b_tt = 0; 
       double ssW_TM_tt = 0;
       double ssW_TM_1b_tt = 0;
       double ssW_TL_tt = 0;
       double ssW_TL_1b_tt = 0; 

       for (Long64_t event = 0; event < tree_tt->GetEntries(); ++event){

            tree_tt->GetEntry(event);
            //if ( weighted_evts < 0.0 ) continue;

            if ( m_ll >= lower_bound && m_ll <= upper_bound ){               
                 
                 if ( flag_TT ){
                      sumW_TT_tt += weighted_evts;
                      ssW_TT_tt += pow(weighted_evts,2.0);
                 }

                 if ( flag_TT_1b ){
                      sumW_TT_1b_tt += weighted_evts;
                      ssW_TT_1b_tt += pow(weighted_evts,2.0);
                 }

                 if ( flag_TM ){
                      sumW_TM_tt += weighted_evts;
                      ssW_TM_tt += pow(weighted_evts,2.0);
                 }

                 if ( flag_TM_1b ){
                      sumW_TM_1b_tt += weighted_evts;
                      ssW_TM_1b_tt += pow(weighted_evts,2.0);
                 }

                 if ( flag_TL ){
                      sumW_TL_tt += weighted_evts;
                      ssW_TL_tt += pow(weighted_evts,2.0);
                 }

                 if ( flag_TL_1b ){
                      sumW_TL_1b_tt += weighted_evts;
                      ssW_TL_1b_tt += pow(weighted_evts,2.0);
                 }
                
            }

       }   

       // Calculate the uncertainties associated with each of the yields 
 



       std::cout << "Fraction of TT_2b events = " << sumW_TT/(sumW_TT+sumW_TT_1b) << endl;
       std::cout << "Fraction of TT_1b events = " << sumW_TT_1b/(sumW_TT+sumW_TT_1b) << endl;
       std::cout << "N bkgd events TT 2b = " << sumW_TT_DY + sumW_TT_tt << " +/- " << sqrt(ssW_TT_DY+ssW_TT_tt) << endl;
       std::cout << "N bkgd events TT 1b = " << sumW_TT_1b_DY + sumW_TT_1b_tt << " +/- " << sqrt(ssW_TT_1b_DY+ssW_TT_1b_tt) << endl;    
       std::cout << "Fraction of TM_2b events = " << sumW_TM/(sumW_TM+sumW_TM_1b) << endl;
       std::cout << "Fraction of TM_1b events = " << sumW_TM_1b/(sumW_TM+sumW_TM_1b) << endl;
       std::cout << "N bkgd events TM 2b = " << sumW_TM_DY + sumW_TM_tt << " +/- " << sqrt(ssW_TM_DY+ssW_TM_tt)  << endl;
       std::cout << "N bkgd events TM 1b = " << sumW_TM_1b_DY + sumW_TM_1b_tt << " +/- " << sqrt(ssW_TM_1b_DY+ssW_TM_1b_tt)  << endl;
       std::cout << "Fraction of TL_2b events = " << sumW_TL/(sumW_TL+sumW_TL_1b) << endl;
       std::cout << "Fraction of TL_1b events = " << sumW_TL_1b/(sumW_TL+sumW_TL_1b) << endl;
       std::cout << "N bkgd events TL 2b = " << sumW_TL_DY + sumW_TL_tt << " +/- " << sqrt(ssW_TL_DY+ssW_TL_tt)  << endl;
       std::cout << "N bkgd events TL 1b = " << sumW_TL_1b_DY + sumW_TL_1b_tt << " +/- " << sqrt(ssW_TL_1b_DY+ssW_TL_1b_tt) << endl;

       /*
       std::cout << "N entries signal TT2b = " << n_TT << endl;
       std::cout << "N entries signal TT1b = " << n_TT_1b << endl;
       std::cout << "N entries signal TM2b = " << n_TM << endl;
       std::cout << "N entries signal TM1b = " << n_TM_1b << endl;
       std::cout << "N entries signal TL2b = " << n_TL << endl;
       std::cout << "N entries signal TL1b = " << n_TL_1b << endl;
       */ 
       
       yields = {sumW_TT,sumW_TT_1b,sumW_TM,sumW_TM_1b,sumW_TL,sumW_TL_1b};
      
       return yields;
}
