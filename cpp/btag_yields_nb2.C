#include "Math/DistFunc.h"
#include "Math/DistFuncMathMore.h" 
#include <iostream>
#include <fstream>
using namespace std; 

typedef double(*fcn_chisquared_quantile_t)(double, double);

void getPoissonCountingConfidenceInterval_Frequentist(double sw_total, double swsq_total, double CL, double& vlow, double& vhigh){
    double const quant = (1. - CL) / 2.;
    double const count = (swsq_total<=0. ? (sw_total==0. ? 0. : sw_total) : std::pow(sw_total, 2)/swsq_total);
    //bool const useMathMore = (count<1.);
    constexpr bool useMathMore = false;
    fcn_chisquared_quantile_t fcn_chisquared_quantile = (useMathMore ? ROOT::MathMore::chisquared_quantile : ROOT::Math::chisquared_quantile);
    vlow = (count == 0. ? 0. : fcn_chisquared_quantile(quant, 2. * count) / 2.);
    vhigh = fcn_chisquared_quantile(1.-quant, 2 * (count + 1.)) / 2.;
    if (count>0.){
        vlow *= sw_total/count;
        vhigh *= sw_total/count;
        }
   }


vector<double> btag_yields_nb2(TString process, TString year, double mass, TString btag_comb){
    
       ofstream myfile;
       ofstream yield_file;
       myfile.open (Form("datacards/datacard_%s_%s.txt",process.Data(),btag_comb.Data()));
       yield_file.open (Form("yields/yields_%s_%s.txt",process.Data(),btag_comb.Data()));
   
       TString dir = "temp_data/";
       TString filestart = "output_";
       TString filetype = ".root";
       
       //std::cout << dir+filestart+process+"_"+year+"nb2"+filetype << endl;
       TFile* file = TFile::Open(dir+filestart+process+"_"+year+"nb2"+filetype,"READ");
       
       TTree* tree_in = (TTree*)file->Get("tree");

       bool flag, flag_1b;
       float wgt, m_ll, weighted_evts; 


       //std::cout << "1" << endl;
       tree_in->SetBranchAddress("wgt",&wgt);
       tree_in->SetBranchAddress("weighted_evts",&weighted_evts);
       tree_in->SetBranchAddress("m_ll",&m_ll);
       tree_in->SetBranchAddress("flag_"+btag_comb,&flag);
       tree_in->SetBranchAddress(Form("flag_%s_1b",btag_comb.Data()),&flag_1b);

       //std::cout << "2" << endl;

       double sumW = 0;
       double sumW_1b = 0;
       double ssW = 0;
       double ssW_1b = 0;

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

       int n = 0;
       int n_1b = 0;

       //std::cout << "Number of events = " << tree_in->GetEntries() << endl;

       // Event loop for signal sample
       for (Long64_t event = 0; event < tree_in->GetEntries(); ++event){
            
            tree_in->GetEntry(event);
            //if ( weighted_evts < 0.0 ) continue;
            
            if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                 
                 if ( flag ){
                      sumW += weighted_evts;
                      ssW += pow(weighted_evts,2.0);
                      n++;
                 }
                  
                 if ( flag_1b ){
                      sumW_1b += weighted_evts;
                      ssW_1b += pow(weighted_evts,2.0);
                      n_1b++;
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
       tree_DY->SetBranchAddress("flag_"+btag_comb,&flag);
       tree_DY->SetBranchAddress(Form("flag_%s_1b",btag_comb.Data()),&flag_1b);

       //std::cout << "3" << endl;
       
       double sumW_DY = 0;
       double sumW_1b_DY = 0;
       double ssW_DY = 0;
       double ssW_1b_DY = 0;
 
      
       for (Long64_t event = 0; event < tree_DY->GetEntries(); ++event){

            tree_DY->GetEntry(event);

            if ( m_ll >= lower_bound && m_ll <= upper_bound ){
                 
                 if ( flag ){
                      sumW_DY += weighted_evts;
                      ssW_DY += pow(weighted_evts,2.0);
                 }

                 if ( flag_1b ){
                      sumW_1b_DY += weighted_evts;
                      ssW_1b_DY += pow(weighted_evts,2.0);
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
       tree_tt->SetBranchAddress("flag_"+btag_comb,&flag);
       tree_tt->SetBranchAddress(Form("flag_%s_1b",btag_comb.Data()),&flag_1b);
       
       double sumW_tt = 0;
       double sumW_1b_tt = 0;
       double ssW_tt = 0; 
       double ssW_1b_tt = 0; 

       for (Long64_t event = 0; event < tree_tt->GetEntries(); ++event){

            tree_tt->GetEntry(event);
            //if ( weighted_evts < 0.0 ) continue;

            if ( m_ll >= lower_bound && m_ll <= upper_bound ){               
                 
                 if ( flag ){
                      sumW_tt += weighted_evts;
                      ssW_tt += pow(weighted_evts,2.0);
                 }

                 if ( flag_1b ){
                      sumW_1b_tt += weighted_evts;
                      ssW_1b_tt += pow(weighted_evts,2.0);
                 }
                  
            }

       }   

       // Calculate the uncertainties associated with each of the yields 
       /* 
       double v_low;
       double v_high;
       getPoissonCountingConfidenceInterval_Frequentist(sumW, ssW, 0.684, v_low, v_high);
       std::cout << "Number of TT_2b events = " << sumW << " , frac unc =  " << (v_low-sumW)/sumW << "/" << (v_high-sumW)/sumW << endl;
       getPoissonCountingConfidenceInterval_Frequentist(sumW_1b, ssW_1b, 0.684, v_low, v_high);
       std::cout << "Number of TT_1b events = " << sumW_1b << " , frac unc =  " << (v_low-sumW_1b)/sumW_1b << "/" << (v_high-sumW_1b)/sumW_1b  << endl;
       getPoissonCountingConfidenceInterval_Frequentist(sumW_DY, sumW_DY, 0.684, v_low, v_high);
       std::cout << "N DY events TT 2b = " << sumW_DY << " , frac unc =  " << (v_low-sumW_DY)/sumW_DY << "/" << (v_high-sumW_DY)/sumW_DY  << endl;
       getPoissonCountingConfidenceInterval_Frequentist(sumW_tt, sumW_tt, 0.684, v_low, v_high);
       std::cout << "N ttbar events TT 2b = " << sumW_tt << " , frac unc =  " << (v_low-sumW_tt)/sumW_tt << "/" << (v_high-sumW_tt)/sumW_tt  << endl;
       getPoissonCountingConfidenceInterval_Frequentist(sumW_1b_DY, sumW_1b_DY, 0.684, v_low, v_high);
       std::cout << "N DY events TT 1b = " << sumW_1b_DY << " , frac unc =  " << (v_low-sumW_1b_DY)/sumW_1b_DY << "/" << (v_high-sumW_1b_DY)/sumW_1b_DY  << endl;
       getPoissonCountingConfidenceInterval_Frequentist(sumW_1b_tt, sumW_1b_tt, 0.684, v_low, v_high);
       std::cout << "N ttbar events TT 1b = " << sumW_1b_tt << " , frac unc = " << (v_low-sumW_1b_tt)/sumW_1b_tt << "/" << (v_high-sumW_1b_tt)/sumW_1b_tt  << endl;
       */

       myfile << "imax  * " << endl;
       myfile << "jmax  * " << endl;
       myfile << "kmax  * " << endl;
       myfile << "--------------------------------------" << endl;
       myfile << "--------------------------------------" << endl;             
       myfile << "bin one_b two_b" << endl;
       myfile << "observation " << sumW << " " << sumW_1b << endl;
       myfile << "--------------------------------------" << endl;
       myfile << "bin one_b two_b one_b two_b one_b two_b" << endl;
       myfile << "process ttbar ttbar Drell-Yan Drell-Yan " << process << " " << process << endl;
       myfile << "process 1 1 2 2 -1 -1" << endl;
       myfile << "rate " << sumW_1b_tt << " " << sumW_tt << " " << sumW_1b_DY << " " << sumW_DY << " " << sumW_1b/(sumW_1b+sumW) << " " << sumW/(sumW_1b+sumW) << endl;
       myfile << "--------------------------------------" << endl;
       myfile << "ttbar_Norm_1b gmN " << sumW_1b_tt << " 1 - - - - -" << endl;
       myfile << "ttbar_Norm_2b gmN " << sumW_tt << " - 1 - - - -" << endl;
       myfile << "DY_Norm_1b gmN " << sumW_1b_DY << " - - 1 - - -" << endl;    
       myfile << "DY_Norm_2b gmN " << sumW_DY << " - - - 1 - -" << endl;
       myfile << "signal_Norm_1b gmN " << pow(sumW_1b,2.0)/ssW_1b << " - - - - " << ssW_1b/sumW_1b/(sumW_1b+sumW) << " -"<< endl;
       myfile << "signal_Norm_2b gmN " << pow(sumW,2.0)/ssW << " - - - - - " << ssW/sumW/(sumW_1b+sumW) << endl;
       
       myfile.close();         

       yield_file <<  sumW + sumW_1b << endl;

       yield_file.close();
       
       yields = {sumW,sumW_1b};
      
       return yields;
}
