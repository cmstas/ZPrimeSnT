double btag_yields(TString process, TString year, bool isSignal){
       
       TString dir = "temp_data/";
       TString filestart = "output_";
       TString filetype = ".root";
       
       std::cout << dir+filestart+process+"_"+year+filetype << endl;
       TFile* file = TFile::Open(dir+filestart+process+"_"+year+filetype,"READ");
       
       TTree* tree_in = (TTree*)file->Get("tree");

       bool flag_20T,flag_20M,flag_30T,flag_30M;
       float wgt, m_ll; 

       tree_in->SetBranchAddress("wgt",&wgt);
       //tree_in->SetBranchAddress("m_ll",&m_ll);
       tree_in->SetBranchAddress("flag_20T",&flag_20T);

       double sumWeights;

       // Event loop
       for (Long64_t event = 0; event < tree_in->GetEntries(); ++event){
            tree_in->GetEntry(event);
            if ( flag_20T ){
                 sumWeights += wgt;
            }
       }

       return sumWeights;
}
