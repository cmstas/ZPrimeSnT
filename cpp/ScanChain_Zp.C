#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TLorentzVector.h"
#include "math.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TRandom3.h"
#include "TString.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooCategory.h"

#include "../NanoCORE/Nano.h"
#include "../NanoCORE/Base.h"
#include "../NanoCORE/tqdm.h"
#include "../NanoCORE/ZPrimeTools.cc"
#include "../NanoCORE/XYMETCorrection_withUL17andUL18andUL16.h"
#include "../NanoCORE/Tools/goodrun.h"
#include "../NanoCORE/Tools/dorky.h"
#include "../NanoCORE/Tools/puWeight.h"
#include "../NanoCORE/Tools/muonRecoSF.h"
#include "../NanoCORE/Tools/muonIDSF.h"
#include "../NanoCORE/Tools/muonIsoSF.h"
#include "../NanoCORE/Tools/muonTriggerSF.h"
#include "../NanoCORE/Tools/GEScaleSyst/GEScaleSyst.h"
#include "../NanoCORE/Tools/bTagEff.h"
#include "../NanoCORE/Tools/btagsf/BTagCalibrationStandalone_v2.h"
#include "../NanoCORE/Tools/jetcorr/JetCorrectionUncertainty.h"
#include "../NanoCORE/Tools/jetcorr/JetResolutionUncertainty.h"
#include "configuration_Zp.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/stat.h>

#define SUM(vec) std::accumulate((vec).begin(), (vec).end(), 0);
#define SUM_GT(vec,num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x,float y) { return ((y > (num)) ? x+y : x); });
#define COUNT_GT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name,nbins,low,high,xtitle) TH1F *h_##name = new TH1F(#name,"",nbins,low,high); h_##name->GetXaxis()->SetTitle(xtitle); h_##name->GetYaxis()->SetTitle("Events");
#define HTemp(name,nbins,low,high,xtitle) TH1F *h_temp = new TH1F(name,"",nbins,low,high); h_temp->GetXaxis()->SetTitle(xtitle); h_temp->GetYaxis()->SetTitle("Events");
#define H2DTemp(name,nbinsX,lowX,highX,xtitle,nbinsY,lowY,highY,ytitle) TH2F *h2D_temp = new TH2F(name,"",nbinsX,lowX,highX,nbinsY,lowY,highY); h2D_temp->GetXaxis()->SetTitle(xtitle); h2D_temp->GetYaxis()->SetTitle(ytitle);
#define HVaryingBinSize(name,nbins,binsx,xtitle) TH1F *h_varyingBinSize = new TH1F(name,"",nbins,(float *)binsx.data()); h_varyingBinSize->GetXaxis()->SetTitle(xtitle); h_varyingBinSize->GetYaxis()->SetTitle("Events");

// #define DEBUG
#define Zmass 91.1876

// For testing purposes only
bool useOnlyRun2018B = false;
bool doPartialUnblinding = false;

// Looper setup flags
int doHistos = 1; // 0: Do not plot histos, 1: Plot only final plots, 2: Plot for every selection
bool muonDebug = false;
bool doMllBins = false;
bool doMllBinsForBFF = false;
bool doNbTagBins = true;
bool doTTEnriched = false;
bool doDYEnriched = false;
bool doOnlyDYEnriched = false; // Turns doDYEnriched on
bool doMuDetRegionBins = false;
bool doProdModeBins = false;

// General flags
bool removeSpikes = true;
bool removeDataDuplicates = true;
bool removeCorrections = false;
bool useTuneP = true;
bool usePuppiMET = true;
bool fillRooDataSet = true;
bool writeOutYields_BeforeSel = false; // Turns doProdModeBins on and DOES NOT RUN THE LOOPER
bool writeOutYields_AfterSel = false; // Turns doProdModeBins on

// HEM15/16 veto
bool doHEMveto = true;
float HEM_region[4] = {-3.2, -1.3, -1.57, -0.87}; // etalow, etahigh, philow, phihigh
unsigned int HEM_startRun = 319077; // affects 38.75 out of 59.83 fb-1 in 2018
unsigned int HEM_fracNum = 1205, HEM_fracDen = 1860; // 38.75/59.83 = 0.648 ~= 1205/1860. Used for figuring out if we should veto MC events
float HEM_frac = 0.648;
bool useHEMjets      = true;
float HEM_jetPtCut = 20.0;  // veto on jets above this threshold
bool useHEMmuons     = false;
bool useHEMelectrons = true;
float HEM_lepPtCut = 10.0;  // veto on leptons above this threshold
bool useHEMisotracks = false;
float HEM_trkPtCut = 10.0;  // veto on iso-tracks above this threshold
//

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
#define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
#define debug(args...)
#endif

using namespace std;
using namespace tas;
using namespace duplicate_removal;
using namespace RooFit;


int ScanChain(TChain *ch, double genEventSumw, TString year, TString process, int prefireWeight=1, int topPtWeight=1, int PUWeight=1, int muonRecoSF=1, int muonIdSF=1, int muonIsoSF=1, int muonScaleUnc=0, int muonResUnc=0, int triggerSF=1, int bTagSF=1, int JECUnc=0, int JERUnc=0, int UnclEnUnc=0, int runBFFSync=0, const char* outdir="temp_data") {
// Event weights / scale factors:
//  0: Do not apply
//  1: Apply central value
// +2: Apply positive variation
// -2: Apply negative variation
  
  if ( runBFFSync ) {
    removeCorrections = true;
    doMllBinsForBFF = true;
  }
  if ( removeCorrections ) {
    prefireWeight = 0;
    topPtWeight = 0;
    PUWeight = 0;
    muonRecoSF = 0;
    muonIdSF = 0;
    muonIsoSF = 0;
    muonScaleUnc=0;
    muonResUnc=0;
    triggerSF = 0;
    bTagSF = 0;
    JECUnc = 0;
    JERUnc = 0;
    UnclEnUnc = 0;
  }

  int mdir = mkdir(outdir,0755);
  TString oDir(outdir);

  float factor = 1.0;
  float lumi = 1.0;
  float xsec = 1.0;
  bool isMC = true;

  if ( process.Contains("data") ) {
    isMC = false;
  }
  // SM processes and cross-sections:
  else if ( process == "TTv7" )               xsec = 76700.0; // fb
  else if ( process == "DYv7" )               xsec = 5929000.0; // fb
  else if ( process == "ttbar_2L2Nu" )        xsec = 831.76*1000*(3*0.108)*(3*0.108); // fb
  else if ( process == "ttbar_SemiLeptonic" ) xsec = 831.76*1000*2*(1-3*0.108)*(3*0.108); // fb
  else if ( process == "ttbar_Hadronic" )     xsec = 831.76*1000*(1-3*0.108)*(1-3*0.108); // fb
  else if ( process == "DY" )                 xsec = 5765400.0; // fb
  else if ( process == "DYbb" )               xsec = 14670.0; // fb
  else if ( process == "ZToMuMu_50_120" )     xsec = 2112904.0; // fb
  else if ( process == "ZToMuMu_120_200" )    xsec = 20553.0; // fb
  else if ( process == "ZToMuMu_200_400" )    xsec = 2886.0; // fb
  else if ( process == "ZToMuMu_400_800" )    xsec = 251.7; // fb
  else if ( process == "ZToMuMu_800_1400" )   xsec = 17.07; // fb
  else if ( process == "ZToMuMu_1400_2300" )  xsec = 1.366; // fb
  else if ( process == "ZToMuMu_2300_3500" )  xsec = 0.08178; // fb
  else if ( process == "ZToMuMu_3500_4500" )  xsec = 0.003191; // fb
  else if ( process == "ZToMuMu_4500_6000" )  xsec = 0.0002787; // fb
  else if ( process == "ZToMuMu_6000_Inf" )   xsec = 0.000009569; // fb
  else if ( process == "WW" )                 xsec = 118700.0; // fb 
  else if ( process == "WWTo1L1Nu2Q" )        xsec = 50667.5; // fb 
  else if ( process == "WWTo2L2Nu" )          xsec = 11090.000; // fb 
  else if ( process == "WWTo4Q" )             xsec = 51627.500; // fb 
  else if ( process == "WZ" )                 xsec = 47130.0; // fb
  else if ( process == "WZTo1L1Nu2Q" )        xsec = 9156.5; // fb
  else if ( process == "WZTo1L3Nu" )          xsec = 3408.25; // fb
  else if ( process == "WZTo2Q2L" )           xsec = 6417.75; // fb
  else if ( process == "WZTo3LNu" )           xsec = 5231.0; // fb
  else if ( process == "ZZ" )                 xsec = 16523.0; // fb
  else if ( process == "ZZTo2L2Nu" )          xsec = 973.8; // fb
  else if ( process == "ZZTo2Nu2Q" )          xsec = 4552.0; // fb
  else if ( process == "ZZTo2Q2L" )           xsec = 3683.5; // fb
  else if ( process == "ZZTo4L" )             xsec = 1325.0; // fb
  else if ( process == "ZZTo4Q" )             xsec = 3286.0; // fb
  else if ( process == "tW" )                 xsec = 19550; // fb
  else if ( process == "tbarW" )              xsec = 19550; // fb
  else if ( process == "tZq" )                xsec = 75.8; // fb
  else if ( process == "TTW" )                xsec = 204.3; // fb
  else if ( process == "TTZ" )                xsec = 252.9; // fb
  else if ( process == "TTHToNonbb" )         xsec = 507.5*(1-0.575); // fb
  else if ( process == "TTHTobb" )            xsec = 507.5*0.575; // fb
  // Signal processes and cross-sections:
  else if ( process == "Y3_M100"  )    xsec = 0.0211372800*1000; // fb
  else if ( process == "Y3_M200"  )    xsec = 0.0159797150*1000; // fb
  else if ( process == "Y3_M250"  )    xsec = (runBFFSync==1) ? 0.1*1000 : 0.010116452*1000; // fb
  else if ( process == "Y3_M400"  )    xsec = (runBFFSync==1) ? 0.1*1000 : 0.0029093405*1000; // fb
  else if ( process == "Y3_M550"  )    xsec = 0.00122483125*1000; // fb
  else if ( process == "Y3_M700"  )    xsec = (runBFFSync==1) ? 0.1*1000 : 0.0006143530*1000; // fb
  else if ( process == "Y3_M850"  )    xsec = 0.0003349177*1000; // fb
  else if ( process == "Y3_M1000" )    xsec = (runBFFSync==1) ? 0.1*1000 : 0.0001919544*1000; // fb
  else if ( process == "Y3_M1250" )    xsec = 0.00008172256*1000; // fb
  else if ( process == "Y3_M1500" )    xsec = 0.0000363696*1000; // fb
  else if ( process == "Y3_M2000" )    xsec = 0.0000082510*1000; // fb

  else if ( process == "DY3_M100"  )   xsec = 0.0337049425*1000; // fb
  else if ( process == "DY3_M200"  )   xsec = 0.0127905600*1000; // fb
  else if ( process == "DY3_M250"  )   xsec = 0.00953640075*1000; // fb
  else if ( process == "DY3_M400"  )   xsec = 0.0038605973*1000; // fb
  else if ( process == "DY3_M550"  )   xsec = 0.00180864725*1000; // fb
  else if ( process == "DY3_M700"  )   xsec = 0.0009411330*1000; // fb
  else if ( process == "DY3_M850"  )   xsec = 0.0005227909*1000; // fb
  else if ( process == "DY3_M1000" )   xsec = 0.0003003987*1000; // fb
  else if ( process == "DY3_M1250" )   xsec = 0.00013043808*1000; // fb
  else if ( process == "DY3_M1500" )   xsec = 0.0000595791*1000; // fb
  else if ( process == "DY3_M2000" )   xsec = 0.0000154994*1000; // fb

  else if ( process == "DYp3_M100"  )  xsec = 0.0313425200*1000; // fb
  else if ( process == "DYp3_M200"  )  xsec = 0.0091705403*1000; // fb
  else if ( process == "DYp3_M250"  )  xsec = 0.00657672*1000; // fb
  else if ( process == "DYp3_M400"  )  xsec = 0.0025317413*1000; // fb
  else if ( process == "DYp3_M550"  )  xsec = 0.001172149*1000; // fb
  else if ( process == "DYp3_M700"  )  xsec = 0.0006051238*1000; // fb
  else if ( process == "DYp3_M850"  )  xsec = 0.0003346604*1000; // fb
  else if ( process == "DYp3_M1000" )  xsec = 0.0001939990*1000; // fb
  else if ( process == "DYp3_M1250" )  xsec = 0.00008302484*1000; // fb
  else if ( process == "DYp3_M1500" )  xsec = 0.0000367774*1000; // fb
  else if ( process == "DYp3_M2000" )  xsec = 0.0000082788*1000; // fb

  else if ( process == "B3mL2_M100"  ) xsec = 0.2895163696*1000; // fb
  else if ( process == "B3mL2_M200"  ) xsec = 0.1236243250*1000; // fb
  else if ( process == "B3mL2_M250"  ) xsec = 0.08624186*1000; // fb
  else if ( process == "B3mL2_M400"  ) xsec = 0.0307822425*1000; // fb
  else if ( process == "B3mL2_M550"  ) xsec = 0.01395786*1000; // fb
  else if ( process == "B3mL2_M700"  ) xsec = 0.0071884160*1000; // fb
  else if ( process == "B3mL2_M850"  ) xsec = 0.0039685095*1000; // fb
  else if ( process == "B3mL2_M1000" ) xsec = 0.0022984062*1000; // fb
  else if ( process == "B3mL2_M1250" ) xsec = 0.000981572*1000; // fb
  else if ( process == "B3mL2_M1500" ) xsec = 0.0004383351*1000; // fb
  else if ( process == "B3mL2_M2000" ) xsec = 0.0001029249*1000; // fb

  else if ( process == "BFF_M250" )        xsec = 0.1*1000; // fb
  else if ( process == "BFF_M350" )        xsec = 0.1*1000; // fb
  else if ( process == "BFFdbs1p0_M350" )  xsec = 0.1*1000; // fb
  else if ( process == "BFF_M500" )        xsec = 0.1*1000; // fb
  else
    {
      cout<<"Non-valid process: Exiting!"<<endl;
      return 1;
    }

  // Configuration setup: NanoCORE/Config.{h,cc}
  gconf.nanoAOD_ver = 9;
  gconf.isAPV = (year=="2016APV") ? 1 : 0;
  gconf.GetConfigs(year.Atoi());
  lumi = gconf.lumi;

  if ( runBFFSync ) {
    lumi = 137.61;
    if ( process.Contains("BFF") || process=="TTv7" || process=="DYv7" ) {
      gconf.WP_DeepFlav_tight = 0.7221;
      gconf.WP_DeepFlav_medium = 0.3093;
    }
  }

  // Golden JSON files
  if ( !isMC ) {
    if ( year == "2016APV" )
      set_goodrun_file_json("../utils/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt");
    if ( year == "2016nonAPV" )
      set_goodrun_file_json("../utils/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt");
    if ( year == "2017" )
      set_goodrun_file_json("../utils/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt");
    if ( year == "2018" )
      set_goodrun_file_json("../utils/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt");
  }

  if (doOnlyDYEnriched) doDYEnriched = true;
  if ( writeOutYields_BeforeSel || writeOutYields_AfterSel ) doProdModeBins = true;

  if ( isMC )
    factor = xsec*lumi/genEventSumw;


  // Output yield file and relevant variables
  if ( ( writeOutYields_BeforeSel || writeOutYields_AfterSel ) && ( !process.Contains("Y3") && !process.Contains("DY3") && !process.Contains("DYp3") && !process.Contains("B3mL2") ) ) {
    writeOutYields_BeforeSel = false; // Write yields out only for signal
    writeOutYields_AfterSel = false; // Write yields out only for signal
  }

  ifstream ifile_BeforeSel, ifile_AfterSel;
  TString fn_before = Form("%s/yieldFile_BeforeSel.txt",oDir.Data());
  TString fn_after  = Form("%s/yieldFile_AfterSel.txt" ,oDir.Data());
  if ( writeOutYields_BeforeSel ) ifile_BeforeSel.open(fn_before); // Check file existence
  if ( writeOutYields_AfterSel ) ifile_AfterSel.open(fn_after); // Check file existence

  ofstream yieldFile_BeforeSel, yieldFile_AfterSel;
  if ( writeOutYields_BeforeSel ) {
    yieldFile_BeforeSel.open(fn_before,ios::app); // Append in existing file or create the file, if it is missing
    if (!ifile_BeforeSel) yieldFile_BeforeSel<<"year,model,M,NbbZ_w,NbsZ_w,NssZ_w,NbbZbb_w NbsZbs_w NssZss_w,NbbZ_r,NbsZ_r,NssZ_r,NbbZbb_r NbsZbs_r NssZss_r" << endl;
  }
  if ( writeOutYields_AfterSel ) {
    yieldFile_AfterSel.open(fn_after,ios::app); // Append in existing file or create the file, if it is missing
    if (!ifile_AfterSel) yieldFile_AfterSel<<"year,model,x,t23,M,N_w,f_w,N1_w,N2_w,N1bb_w,N2bb_w,N1bs_w,N2bs_w,N1ss_w,N2ss_w,N_r,f_r,N1_r,N2_r,N1bb_r,N2bb_r,N1bs_r,N2bs_r,N1ss_r,N2ss_r" << endl;
  }

  float NbbZ=0, NbsZ=0, NssZ=0, NbbZbb=0, NbsZbs=0, NssZss=0;
  int yNbbZ=0, yNbsZ=0, yNssZ=0, yNbbZbb=0, yNbsZbs=0, yNssZss=0;
  float N1=0, N2=0, N1bb=0, N2bb=0, N1bs=0, N2bs=0, N1ss=0, N2ss=0;
  int yN1=0, yN2=0, yN1bb=0, yN2bb=0, yN1bs=0, yN2bs=0, yN1ss=0, yN2ss=0;


  // Modify the name of the output file to include arguments of ScanChain function (i.e. process, year, etc.)
  TFile* fout = new TFile(oDir+"/output_"+process+"_"+year+".root", "RECREATE");

  // Define histo info maps
  map<TString, int> nbins { };
  map<TString, float> low { };
  map<TString, float> high { };
  map<TString, vector<float>> binsx { };
  map<TString, TString> title { };

  // Define 2D histo info maps
  map<TString, int> nbinsX { };
  map<TString, float> lowX { };
  map<TString, float> highX { };
  map<TString, TString> xtitle { };
  map<TString, int> nbinsY { };
  map<TString, float> lowY { };
  map<TString, float> highY { };
  map<TString, TString> ytitle { };

  // Define histos
  H1(cutflow,20,0,20,"");
  if (doHistos)
    histoDefinition(nbins, low, high, binsx, title);
    histo2DDefinition(nbins, low, high, title, nbinsX, lowX, highX, xtitle, nbinsY, lowY, highY, ytitle);

  // Define (overlapping) mll bins
  vector<TString> mllbin = { };
  map<TString, TString> mllbinlabel;
  if (doMllBinsForBFF)
    mllbinDefinitionForBFF(mllbin, mllbinlabel);
  else
    mllbinDefinition(mllbin, doMllBins, mllbinlabel);
  const int nMllBins = mllbin.size();
  bool mllbinsel[nMllBins];

  // Define number of b-tag bins
  vector<TString> nbtag = { };
  map<TString, TString> nbtagbinlabel;
  btagbinDefinition(nbtag, doNbTagBins, nbtagbinlabel, doDYEnriched);
  const int nBTagBins = nbtag.size();
  bool nbtagsel[nBTagBins];

  // Define muon detector region bins
  vector<TString> MuDetRegion = {};
  map<TString, TString> MuDetRegionbinlabel;
  muonregionbinDefinition(MuDetRegion, doMuDetRegionBins, MuDetRegionbinlabel);
  const int MuDetRegionBins = MuDetRegion.size();
  bool MuDetRegionSel[MuDetRegionBins];

  // Define production mode
  vector<TString> prodMode = { };
  map<TString, TString> prodModelabel;
  prodModeDefinition(prodMode, doProdModeBins, prodModelabel);
  const int nProdModeBins = prodMode.size();
  bool prodModesel[nProdModeBins];

  // Define RooDataSet's for fit
  RooRealVar mfit("mfit", "mfit", 175.0, 6500.0);
  RooRealVar roow("roow", "roow", -10000.0, 10000.0);
  map<TString, RooDataSet> roods;
  for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
    for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
      for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
        for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
          TString dname = TString("d_") + mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
          TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
          if ( fillRooDataSet )
            roods.insert({slice, RooDataSet(dname,dname,RooArgSet(mfit,roow),WeightVar("roow"))});
        }
      }
    }
  }

  // Define cutflow histograms in bins of mll and number of b-tags
  map<TString, TH1F*> slicedcutflows;
  for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
    for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
      for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++){
        for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
          TString plot_name = TString("cutflow_") + mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
          TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
          HTemp(plot_name,20,0,20,"");
          slicedcutflows[slice] = h_temp;
        }
      }
    }
  }

  // Define selection
  vector<TString> selection = { };
  if (doHistos) {
    if (doHistos==2) {
      selection.push_back("sel0"); // Skimming + HLT + Good PV
      selection.push_back("sel1"); // 2 high-pT ID muons with |dxy|<0.02 cm && |dz|<0.1 cm
      selection.push_back("sel2"); // pT > 53 GeV && |eta| < 2.4 muons
      selection.push_back("sel3"); // Relative track isolation < 0.05 && absolute track isolation < 5 GeV
      selection.push_back("sel4"); // Selected muon matched to HLT > 1 (DeltaR < 0.02)
      selection.push_back("sel5"); // At least one OS dimuon pair, not from Z
      selection.push_back("sel6"); // Mmumu > 175 GeV
      selection.push_back("sel7"); // No extra lepton / isoTrack
      selection.push_back("sel8"); // NbTag >= 1 (medium WP)
      selection.push_back("sel9"); // MET<250 GeV, if (anti-)aligned to muons and/or b-tags
    }
    selection.push_back("sel10"); // minMlb > 175 GeV
    if (doTTEnriched) selection.push_back("antisel10"); // minMlb < 175 GeV, used for ttbar bkg reduction
  }

  vector<TString> plot_names = { };
  vector<TString> plot_names_b = { };
  vector<TString> plot_names_2b = { };
  map<TString, TH1F*> histos;
  vector<TString> plot2D_names = { };
  vector<TString> plot2D_names_b = { };
  vector<TString> plot2D_names_2b = { };
  map<TString, TH2F*> histos2D;
  int nExtraHistos = 0;
  if (doHistos) {
    if (doHistos==2) {
      plot_names.push_back("pfmet_pt");
      plot_names.push_back("pfmet_phi");
      plot_names.push_back("puppimet_pt");
      plot_names.push_back("puppimet_phi");
      if ( muonDebug ) {
        plot_names.push_back("mu1_pt");
        plot_names.push_back("mu2_pt");
        plot_names.push_back("mu1_eta");
        plot_names.push_back("mu2_eta");
        plot_names.push_back("mu1_phi");
        plot_names.push_back("mu2_phi");
        plot_names.push_back("mu1_dxy");
        plot_names.push_back("mu2_dxy");
        plot_names.push_back("mu1_dz");
        plot_names.push_back("mu2_dz");
        plot_names.push_back("mu1_relPtErr");
        plot_names.push_back("mu2_relPtErr");
        plot_names.push_back("mu1_tunepRelPt");
        plot_names.push_back("mu2_tunepRelPt");
        plot_names.push_back("mu1_trkRelIso");
        plot_names.push_back("mu1_trkAbsIso");
        plot_names.push_back("mu2_trkRelIso");
        plot_names.push_back("mu2_trkAbsIso");
        plot_names.push_back("nCand_Muons");
      }
      for ( unsigned int isel=0; isel < selection.size(); isel++ ) {
        if (isel==5) {
          plot_names.push_back("mmumu");
          if ( !muonDebug ) {
            plot_names.push_back("mu1_pt");
            plot_names.push_back("mu2_pt");
            plot_names.push_back("mu1_eta");
            plot_names.push_back("mu2_eta");
            plot_names.push_back("mu1_phi");
            plot_names.push_back("mu2_phi");
            plot_names.push_back("mu1_dxy");
            plot_names.push_back("mu2_dxy");
            plot_names.push_back("mu1_dz");
            plot_names.push_back("mu2_dz");
            plot_names.push_back("mu1_relPtErr");
            plot_names.push_back("mu2_relPtErr");
            plot_names.push_back("mu1_tunepRelPt");
            plot_names.push_back("mu2_tunepRelPt");
            plot_names.push_back("mu1_trkRelIso");
            plot_names.push_back("mu1_trkAbsIso");       
            plot_names.push_back("mu2_trkRelIso");       
            plot_names.push_back("mu2_trkAbsIso");
            plot_names.push_back("nCand_Muons");
          }
          plot_names.push_back("dPhi_ll");
          plot_names.push_back("dEta_ll");
          plot_names.push_back("dEta_dPhi_ratio_ll");
          plot_names.push_back("dPhi_ll_MET");
          plot_names.push_back("minDPhi_l_MET");
          plot_names.push_back("maxDPhi_l_MET");
        }
        // Add also extra plots before third lepton/isotrack veto
        if (isel==6) {
          plot_names.push_back("nExtra_muons"); ++nExtraHistos;
          plot_names.push_back("nExtra_electrons"); ++nExtraHistos;
          plot_names.push_back("nExtra_lepIsoTracks"); ++nExtraHistos;
          plot_names.push_back("nExtra_chhIsoTracks"); ++nExtraHistos;
          plot_names.push_back("mu3_pt"); ++nExtraHistos;
          plot_names.push_back("mu3_eta"); ++nExtraHistos;
          plot_names.push_back("mu3_trkRelIso"); ++nExtraHistos;
          plot_names.push_back("mu3_trkAbsIso"); ++nExtraHistos;
          plot_names.push_back("ele_extra_pt"); ++nExtraHistos;
          plot_names.push_back("ele_extra_eta"); ++nExtraHistos;
          //plot_names.push_back("ele_extra_miniPFRelIso"); ++nExtraHistos;
          plot_names.push_back("lepIsoTrack_extra_pt"); ++nExtraHistos;
          plot_names.push_back("lepIsoTrack_extra_eta"); ++nExtraHistos;
          plot_names.push_back("lepIsoTrack_extra_PFRelIsoChg"); ++nExtraHistos;
          plot_names.push_back("chhIsoTrack_extra_pt"); ++nExtraHistos;
          plot_names.push_back("chhIsoTrack_extra_eta"); ++nExtraHistos;
          plot_names.push_back("chhIsoTrack_extra_PFRelIsoChg"); ++nExtraHistos;
        }

        // Third lepton/isotrack veto
        if (isel==7) {
          // Remove plots added for thid lepton/isotrack veto
          for (int e=0; e<nExtraHistos; ++e)
      plot_names.pop_back();
        }
        if (isel==8) {
          plot_names.push_back("nbtagDeepFlavB");
          plot_names.push_back("jet1_pt");
          plot_names.push_back("jet1_eta");
          plot_names.push_back("bjet1_pt");
          plot_names.push_back("bjet1_eta");
          plot_names.push_back("bjet2_pt");
          plot_names.push_back("bjet2_eta");
          plot_names.push_back("min_mlb");
          plot_names.push_back("min_mbb");
          plot_names.push_back("max_mbb");
          plot_names.push_back("minDPhi_b_MET");
          plot_names.push_back("maxDPhi_b_MET");
          plot_names.push_back("minDPhi_lb_MET");
          plot_names.push_back("minDPhi_llb_MET");
          plot_names.push_back("minDPhi_l_b");
          plot_names.push_back("st_scalar_jet");
          plot_names.push_back("st_vector_jet");
          plot_names.push_back("st_scalar_bjet");
          plot_names.push_back("st_vector_bjet");
          plot2D_names.push_back("jet1_pt_VS_st_scalar_jet");
          plot2D_names.push_back("jet1_pt_VS_st_vector_jet");
          plot2D_names.push_back("bjet1_pt_VS_st_scalar_bjet");
          plot2D_names.push_back("bjet1_pt_VS_st_vector_bjet");
          //
          plot_names_b.push_back("bjet1_pt");
          plot_names_b.push_back("bjet1_eta");
          plot_names_b.push_back("min_mlb");
          plot_names_b.push_back("minDPhi_b_MET");
          plot_names_b.push_back("maxDPhi_b_MET");
          plot_names_b.push_back("minDPhi_lb_MET");
          plot_names_b.push_back("minDPhi_llb_MET");
          plot_names_b.push_back("minDPhi_l_b");
          plot_names_b.push_back("st_scalar_bjet");
          plot_names_b.push_back("st_vector_bjet");
          plot2D_names_b.push_back("bjet1_pt_VS_st_scalar_bjet");
          plot2D_names_b.push_back("bjet1_pt_VS_st_vector_bjet");
          //
          plot_names_2b.push_back("bjet2_pt");
          plot_names_2b.push_back("bjet2_eta");
          plot_names_2b.push_back("min_mbb");
          plot_names_2b.push_back("max_mbb");
        }
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          if(isel<5) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString plot_name = plot_names[iplot];
              TString name = plot_name+"_"+selection[isel]+"_"+mllbin[0] + prodMode[iprodMode];
              if ( binsx[plot_name].size()==0 ) {
                HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
                histos[name] = h_temp;
              }
              else {
                HVaryingBinSize(name,nbins[plot_name],binsx[plot_name],title[plot_name]);
                histos[name] = h_varyingBinSize;
              }
            }
          }
          else if(isel>=5 && isel<8) {
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString plot_name = plot_names[iplot];
                  TString name = plot_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if ( binsx[plot_name].size()==0 ) {
                    HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
                    histos[name] = h_temp;
                  }
                  else {
                    HVaryingBinSize(name,nbins[plot_name],binsx[plot_name],title[plot_name]);
                    histos[name] = h_varyingBinSize;
                  }
                }
              }
            }
          }
          else if(isel>=8) {
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
                for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                  for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                    TString plot_name = plot_names[iplot];
                    if ( std::find(plot_names_b.begin(), plot_names_b.end(), plot_name) != plot_names_b.end() && nbtag[inb]=="nBTag0" )
                      continue;
                    if ( std::find(plot_names_2b.begin(), plot_names_2b.end(), plot_name) != plot_names_2b.end() && ( nbtag[inb]=="nBTag1" || nbtag[inb]=="nBTag0" ) )
                      continue;
                    TString name = plot_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                    if ( binsx[plot_name].size()==0 ) {
                      HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
                      histos[name] = h_temp;
                    }
                    else {
                      HVaryingBinSize(name,nbins[plot_name],binsx[plot_name],title[plot_name]);
                      histos[name] = h_varyingBinSize;
                    }
                  }
                }
              }
            }
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          if(isel<5) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString plot2D_name = plot2D_names[iplot];
              TString name = plot2D_name+"_"+selection[isel]+"_"+mllbin[0] + prodMode[iprodMode];
              H2DTemp(name,nbinsX[plot2D_name],lowX[plot2D_name],highX[plot2D_name],xtitle[plot2D_name],nbinsY[plot2D_name],lowY[plot2D_name],highY[plot2D_name],ytitle[plot2D_name]);
              histos2D[name] = h2D_temp;
            }
          }
          else if(isel>=5 && isel<8) {
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString plot2D_name = plot2D_names[iplot];
                  TString name = plot2D_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  H2DTemp(name,nbinsX[plot2D_name],lowX[plot2D_name],highX[plot2D_name],xtitle[plot2D_name],nbinsY[plot2D_name],lowY[plot2D_name],highY[plot2D_name],ytitle[plot2D_name]);
                  histos2D[name] = h2D_temp;
                }
              }
            }
          }
          else if(isel>=8) {
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
                for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                  for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                    TString plot2D_name = plot2D_names[iplot];
                    if ( std::find(plot2D_names_b.begin(), plot2D_names_b.end(), plot2D_name) != plot2D_names_b.end() && nbtag[inb]=="nBTag0" )
                      continue;
                    if ( std::find(plot2D_names_2b.begin(), plot2D_names_2b.end(), plot2D_name) != plot2D_names_2b.end() && ( nbtag[inb]=="nBTag1" || nbtag[inb]=="nBTag0" ) )
                      continue;
                    TString name = plot2D_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                    H2DTemp(name,nbinsX[plot2D_name],lowX[plot2D_name],highX[plot2D_name],xtitle[plot2D_name],nbinsY[plot2D_name],lowY[plot2D_name],highY[plot2D_name],ytitle[plot2D_name]);
                    histos2D[name] = h2D_temp;
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      plot_names.push_back("pfmet_pt");
      plot_names.push_back("pfmet_phi");
      plot_names.push_back("puppimet_pt");
      plot_names.push_back("puppimet_phi");
      plot_names.push_back("mmumu");
      plot_names.push_back("mu1_pt");
      plot_names.push_back("mu2_pt");
      plot_names.push_back("mu1_eta");
      plot_names.push_back("mu2_eta");
      plot_names.push_back("mu1_phi");
      plot_names.push_back("mu2_phi");
      plot_names.push_back("mu1_dxy");
      plot_names.push_back("mu2_dxy");
      plot_names.push_back("mu1_dz");
      plot_names.push_back("mu2_dz");
      plot_names.push_back("mu1_relPtErr");
      plot_names.push_back("mu2_relPtErr");
      plot_names.push_back("mu1_tunepRelPt");
      plot_names.push_back("mu2_tunepRelPt");
      plot_names.push_back("mu1_trkRelIso");
      plot_names.push_back("mu1_trkAbsIso");       
      plot_names.push_back("mu2_trkRelIso");       
      plot_names.push_back("mu2_trkAbsIso");
      plot_names.push_back("nCand_Muons");
      plot_names.push_back("dPhi_ll");
      plot_names.push_back("dEta_ll");
      plot_names.push_back("dEta_dPhi_ratio_ll");
      plot_names.push_back("dPhi_ll_MET");
      plot_names.push_back("minDPhi_l_MET");
      plot_names.push_back("maxDPhi_l_MET");
      plot_names.push_back("nbtagDeepFlavB");
      plot_names.push_back("jet1_pt");
      plot_names.push_back("jet1_eta");
      plot_names.push_back("bjet1_pt");
      plot_names.push_back("bjet1_eta");
      plot_names.push_back("bjet2_pt");
      plot_names.push_back("bjet2_eta");
      plot_names.push_back("min_mlb");
      plot_names.push_back("min_mbb");
      plot_names.push_back("max_mbb");
      plot_names.push_back("minDPhi_b_MET");
      plot_names.push_back("maxDPhi_b_MET");
      plot_names.push_back("minDPhi_lb_MET");
      plot_names.push_back("minDPhi_llb_MET");
      plot_names.push_back("minDPhi_l_b");
      plot_names.push_back("st_scalar_jet");
      plot_names.push_back("st_vector_jet");
      plot_names.push_back("st_scalar_bjet");
      plot_names.push_back("st_vector_bjet");
      plot2D_names.push_back("jet1_pt_VS_st_scalar_jet");
      plot2D_names.push_back("jet1_pt_VS_st_vector_jet");
      plot2D_names.push_back("bjet1_pt_VS_st_scalar_bjet");
      plot2D_names.push_back("bjet1_pt_VS_st_vector_bjet");
      //
      plot_names_b.push_back("bjet1_pt");
      plot_names_b.push_back("bjet1_eta");
      plot_names_b.push_back("min_mlb");
      plot_names_b.push_back("minDPhi_b_MET");
      plot_names_b.push_back("maxDPhi_b_MET");
      plot_names_b.push_back("minDPhi_lb_MET");
      plot_names_b.push_back("minDPhi_llb_MET");
      plot_names_b.push_back("minDPhi_l_b");
      plot_names_b.push_back("st_scalar_bjet");
      plot_names_b.push_back("st_vector_bjet");
      plot2D_names_b.push_back("bjet1_pt_VS_st_scalar_bjet");
      plot2D_names_b.push_back("bjet1_pt_VS_st_vector_bjet");
      //
      plot_names_2b.push_back("bjet2_pt");
      plot_names_2b.push_back("bjet2_eta");
      plot_names_2b.push_back("min_mbb");
      plot_names_2b.push_back("max_mbb");
      for ( unsigned int isel=0; isel < selection.size(); isel++ ) {
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString plot_name = plot_names[iplot];
                  if ( std::find(plot_names_b.begin(), plot_names_b.end(), plot_name) != plot_names_b.end() && nbtag[inb]=="nBTag0" )
                    continue;
                  if ( std::find(plot_names_2b.begin(), plot_names_2b.end(), plot_name) != plot_names_2b.end() && ( nbtag[inb]=="nBTag1" || nbtag[inb]=="nBTag0" ) )
                    continue;
                  TString name = plot_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if ( binsx[plot_name].size()==0 ) {
                    HTemp(name,nbins[plot_name],low[plot_name],high[plot_name],title[plot_name]);
                    histos[name] = h_temp;
                  }
                  else {
                    HVaryingBinSize(name,nbins[plot_name],binsx[plot_name],title[plot_name]);
                    histos[name] = h_varyingBinSize;
                  }
                }
              }
            }
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString plot2D_name = plot2D_names[iplot];
                  if ( std::find(plot2D_names_b.begin(), plot2D_names_b.end(), plot2D_name) != plot2D_names_b.end() && nbtag[inb]=="nBTag0" )
                    continue;
                  if ( std::find(plot2D_names_2b.begin(), plot2D_names_2b.end(), plot2D_name) != plot2D_names_2b.end() && ( nbtag[inb]=="nBTag1" || nbtag[inb]=="nBTag0" ) )
                    continue;
                  TString name = plot2D_name + "_" + selection[isel] + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  H2DTemp(name,nbinsX[plot2D_name],lowX[plot2D_name],highX[plot2D_name],xtitle[plot2D_name],nbinsY[plot2D_name],lowY[plot2D_name],highY[plot2D_name],ytitle[plot2D_name]);
                  histos2D[name] = h2D_temp;
                }
              }
            }
          }
        }
      }
    }
  }

  if ( PUWeight!=0 ) set_puWeights();
  if ( muonRecoSF!=0 ) {
    // If muon p>100 GeV or (p>50 GeV and |eta|<1.6), high-pT RECO SF are applied as a function of muon p and |eta|
    // (central high-pT RECO SFs equal zero elsewhere)
    // Else medium-pT RECO SF are applied as a function of muon pT and |eta|, to avoid zero SFs
    set_muonRecoSF();
  }
  if ( muonIdSF!=0 ) set_muonIDSF();
  if ( muonIsoSF!=0) set_muonIsoSF();
  if ( triggerSF!=0 ) set_triggerSF();
  if ( bTagSF!=0 ) set_allbTagEff();

  // Setting up muon momentum scale
  std::string muonScaleEra = (year+"_UL").Data();
  GEScaleSyst GE(muonScaleEra); // Only available for 2017!
  GE.SetVerbose(0);

  // Setting up muon momentum resolution
  TRandom3 rnd_muonMomRes(12345);

  // Setting up btagging scale factors
  BTagCalibration_v2* btagCalib;
  BTagCalibrationReader_v2* btagReaderTight = new BTagCalibrationReader_v2(BTagEntry_v2::OP_TIGHT, "central", {"up", "down"});
  BTagCalibrationReader_v2* btagReaderMedium = new BTagCalibrationReader_v2(BTagEntry_v2::OP_MEDIUM, "central", {"up", "down"});
  BTagCalibrationReader_v2* btagReaderLoose = new BTagCalibrationReader_v2(BTagEntry_v2::OP_LOOSE, "central", {"up", "down"});
  if ( isMC && bTagSF!=0 ) {
    if (year == "2016APV") {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL16preVFP_v2.csv");
    }
    else if (year == "2016nonAPV") {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL16postVFP_v3.csv");
    }
    else if (year == "2017") {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL17_v3.csv");
    }
    else if (year == "2018") {
      btagCalib = new BTagCalibration_v2("DeepJet", "../data/wp_deepJet_106XUL18_v2.csv");
    }
    else {
      cout<<"Non-valid year for setting bTag SFs: Exiting!"<<endl;
      return 1;
    }

    btagReaderTight->load(*btagCalib, BTagEntry_v2::FLAV_B, "comb");
    btagReaderTight->load(*btagCalib, BTagEntry_v2::FLAV_C, "comb");
    btagReaderTight->load(*btagCalib, BTagEntry_v2::FLAV_UDSG, "incl");
    btagReaderMedium->load(*btagCalib, BTagEntry_v2::FLAV_B, "comb");
    btagReaderMedium->load(*btagCalib, BTagEntry_v2::FLAV_C, "comb");
    btagReaderMedium->load(*btagCalib, BTagEntry_v2::FLAV_UDSG, "incl");
    btagReaderLoose->load(*btagCalib, BTagEntry_v2::FLAV_B, "comb");
    btagReaderLoose->load(*btagCalib, BTagEntry_v2::FLAV_C, "comb");
    btagReaderLoose->load(*btagCalib, BTagEntry_v2::FLAV_UDSG, "incl");
  }

  // Setting up JEC uncertainties
  JetCorrectionUncertainty* jec_unc = new JetCorrectionUncertainty(
    "../NanoCORE/Tools/jetcorr/data/"
    + gconf.jecEraMC 
    + "/"
    + gconf.jecEraMC
    + "_Uncertainty_AK4PFchs.txt"
  );

  // Setting up JER uncertainties
  TRandom3 rnd(12345);
  JetResolutionUncertainty* jer_unc = new JetResolutionUncertainty(
    "../NanoCORE/Tools/jetcorr/data/"+gconf.jerEra+"/"+gconf.jerEra+"_PtResolution_AK4PFchs.txt",
    "../NanoCORE/Tools/jetcorr/data/"+gconf.jerEra+"/"+gconf.jerEra+"_SF_AK4PFchs.txt"
  );

  // Setting up partial unblinding
  TRandom3 rnd_data(12345);

  int nEventsTotal = 0;
  int nDuplicates = 0;
  int nEventsChain = ch->GetEntries();
  TFile *currentFile = 0;
  TObjArray *listOfFiles = ch->GetListOfFiles();
  TIter fileIter(listOfFiles);
  tqdm bar;

  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    TFile *file = TFile::Open( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    TString filename(currentFile->GetTitle());

    tree->SetCacheSize(128*1024*1024);
    tree->SetCacheLearnEntries(100);

    nt.Init(tree);

    // Before any cuts
    int icutflow = 0;
    TString label = "Total";
    TString slicedlabel = label;
    if ( isMC ) {
      if ( process!="DYbb") {
        h_cutflow->Fill(icutflow,xsec*lumi);
      }
      else {
        h_cutflow->Fill(icutflow,2./3.*xsec*lumi);
      }
    }
    h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
    for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
      for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
        for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
            if ( isMC )
              slicedcutflows[slice]->Fill(icutflow,xsec*lumi);
            slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
          }
        }
      }
    }

    for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

      nt.GetEntry(event);
      tree->LoadTree(event);

      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);

      float weight = 1.0;
      if ( isMC ) 
        weight = nt.genWeight();

      bool Z2q = false; // Two quarks in final state?
      prodModesel[0] = true;
      if ( doProdModeBins ) {
        if ( process.Contains("Y3") || process.Contains("DY3") || process.Contains("DYp3") || process.Contains("B3mL2") ) {
          int s = 0; // How many s quarks?
          if (nt.nLHEPart()==6) Z2q=true;
          for ( unsigned int LHEPart = 0; LHEPart < nt.nLHEPart(); LHEPart++) {
            if (abs(nt.LHEPart_pdgId().at(LHEPart)) == 3) s++;
          }
          if (s==2) {
            prodModesel[1] = true;
            prodModesel[2] = false;
            prodModesel[3] = false;
          }
          else if (s==1) {
            prodModesel[1] = false;
            prodModesel[2] = true;
            prodModesel[3] = false;
          }
          else {
            prodModesel[1] = false;
            prodModesel[2] = false;
            prodModesel[3] = true;
          }
        }
        else {
          prodModesel[1] = true;
          prodModesel[2] = true;
          prodModesel[3] = true;
        }
      }

      if ( writeOutYields_BeforeSel ) {
        if ( Z2q ) {
          if ( prodModesel[1] ) {
            NssZss += weight * factor;
            yNssZss++;
          }
          else if ( prodModesel[2] ) {
            NbsZbs += weight * factor;
            yNbsZbs++;
          }
          else {
            NbbZbb += weight * factor;
            yNbbZbb++;
          }
        }
        else {
          if ( prodModesel[1] ) {
            NssZ += weight * factor;
            yNssZ++;
          }
          else if ( prodModesel[2] ) {
            NbsZ += weight * factor;
            yNbsZ++;
          }
          else {
            NbbZ += weight * factor;
            yNbbZ++;
          }
        }
        continue;
      }


      if ( isMC ) {
	if(removeSpikes && fabs(weight*factor)>1e2) continue;
	if (process=="DYbb") {
	  int nGluons = 0;
	  for ( unsigned int p=0; p<nt.nLHEPart(); p++ ) {
	    if ( nt.LHEPart_pdgId().at(p)==21 && nt.LHEPart_status().at(p)==-1 ) nGluons+=1;
	  }
	  if ( nGluons != 2 )
	    continue;
	}

	// Apply L1 muon pre-firing weight (available in nanoAODv9):
	// https://twiki.cern.ch/twiki/bin/view/CMS/L1PrefiringWeightRecipe
        if ( prefireWeight!=0 && ( process!="DYbb" && process!="DYv7" && process!="TTv7" && !process.Contains("BFF") ) ) {
          if ( prefireWeight==1 ) weight *= nt.L1PreFiringWeight_Muon_Nom();
          if ( prefireWeight==2 ) weight *= nt.L1PreFiringWeight_Muon_SystUp(); // Syst unc. up --> Possibly merge with Stat up?
          if ( prefireWeight==3 ) weight *= nt.L1PreFiringWeight_Muon_StatUp(); // Stat unc. up --> Possibly merge with Syst up?
          if ( prefireWeight==-2 ) weight *= nt.L1PreFiringWeight_Muon_SystDn(); // Syst unc. dn --> Possibly merge with Stat dn?
          if ( prefireWeight==-3 ) weight *= nt.L1PreFiringWeight_Muon_StatDn(); // Stat unc. dn --> Possibly merge with Syst dn?
        }

	// Apply PU reweight
	if ( PUWeight!=0 ) {
	  unsigned int nTrueInt = nt.Pileup_nTrueInt();
	  TString whichPUWeight = "central";
	  if ( PUWeight==2 ) whichPUWeight = "up";
	  else if ( PUWeight==-2 ) whichPUWeight = "down";
	  TString puyear = year;
	  if ( useOnlyRun2018B ) puyear = "2018B";
	  weight *= get_puWeight(nTrueInt, puyear, whichPUWeight);
	}

	// Apply top pT weight:
	// https://twiki.cern.ch/twiki/bin/view/CMS/TopPtReweighting#TOP_PAG_corrections_based_on_dat
	if ( topPtWeight!=0 && process == "ttbar" ) {
	  float exp_p0 =  0.0615;
	  float exp_p1 = -0.0005;
	  float topweight = 1.0;
	  float maxtoppt = 500.0;
	  int ntop = 0;
	  for ( unsigned int t=0; t<nt.nGenPart(); t++ ) {
	    if ( ntop >=2 ) break;
	    if ( abs(nt.GenPart_pdgId().at(t))!=6 or nt.GenPart_status().at(t)!=62 ) continue;
	    if ( abs(nt.GenPart_pdgId().at(t))==6 ) {
	      float tpt = std::min(nt.GenPart_pt().at(t), maxtoppt);
	      topweight *= TMath::Exp( exp_p0 + exp_p1*tpt );
	      ++ntop;
	    }
	  }
	  weight *= TMath::Sqrt(topweight);
	}
      }

      unsigned int runnb = nt.run();
      unsigned int lumiblock = nt.luminosityBlock();
      unsigned long int evtnb = nt.event();
      int npv = nt.PV_npvs();

      // Setting random number generator seed
      int seed = 1 + ( runnb << 20 ) + ( lumiblock << 10 ) + evtnb + ( nt.nJet() > 0 ? nt.Jet_eta().at(0) / 0.01 : 0 );
      rnd.SetSeed(seed);

      // Apply Golden JSON
      if ( !isMC ) {
	if ( !(goodrun(runnb, lumiblock)) )
	  continue;
	if ( removeDataDuplicates ) {
	  DorkyEventIdentifier id(runnb, evtnb, lumiblock);
	  if ( is_duplicate(id) ){
	    ++nDuplicates;
	    continue;
	  }
	}
	// Unblind only 10% of data set

	if ( doPartialUnblinding && !doOnlyDYEnriched ) {
	  if ( rnd_data.Rndm() > 0.1 )
	    continue;
	}
      }

      // MET xy correction: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections#xy_Shift_Correction_MET_phi_modu
      // METXYCorr_Met_MetPhi(double uncormet, double uncormet_phi, int runnb, TString year, bool isMC, int npv, bool isUL =false,bool ispuppi=false)

      // Before MET xy correction, apply check for inf and nans:
      if ( !usePuppiMET ) {
	if( isinf(nt.MET_pt()) || isnan(nt.MET_pt()) )
	  continue;
	if( isinf(nt.MET_phi()) || isnan(nt.MET_phi()) )
	  continue;
      }
      else {
	// Central value
	if ( isinf(nt.PuppiMET_pt()) || isnan(nt.PuppiMET_pt()) )
	  continue;
	if ( isinf(nt.PuppiMET_phi()) || isnan(nt.PuppiMET_phi()) )
	  continue;
	if ( isMC && ( process!="DYbb" && process!="DYv7" && process!="TTv7" && !process.Contains("BFF") ) ) {
	  // JES up
	  if ( isinf(nt.PuppiMET_ptJESUp()) || isnan(nt.PuppiMET_ptJESUp()) )
	    continue;
	  if ( isinf(nt.PuppiMET_phiJESUp()) || isnan(nt.PuppiMET_phiJESUp()) )
	    continue;
	  // JES down
	  if ( isinf(nt.PuppiMET_ptJESDown()) || isnan(nt.PuppiMET_ptJESDown()) )
	    continue;
	  if ( isinf(nt.PuppiMET_phiJESDown()) || isnan(nt.PuppiMET_phiJESDown()) )
	    continue;
	  // JER up
	  if ( isinf(nt.PuppiMET_ptJERUp()) || isnan(nt.PuppiMET_ptJERUp()) )
	    continue;
	  if ( isinf(nt.PuppiMET_phiJERUp()) || isnan(nt.PuppiMET_phiJERUp()) )
	    continue;
	  // JER down
	  if ( isinf(nt.PuppiMET_ptJERDown()) || isnan(nt.PuppiMET_ptJERDown()) )
	    continue;
	  if ( isinf(nt.PuppiMET_phiJERDown()) || isnan(nt.PuppiMET_phiJERDown()) )
	    continue;
	  // Unclustered up
	  if ( isinf(nt.PuppiMET_ptUnclusteredUp()) || isnan(nt.PuppiMET_ptUnclusteredUp()) )
	    continue;
	  if ( isinf(nt.PuppiMET_phiUnclusteredUp()) || isnan(nt.PuppiMET_phiUnclusteredUp()) )
	    continue;
	  // Unclustered down
	  if ( isinf(nt.PuppiMET_ptUnclusteredDown()) || isnan(nt.PuppiMET_ptUnclusteredDown()) )
	    continue;
	  if ( isinf(nt.PuppiMET_phiUnclusteredDown()) || isnan(nt.PuppiMET_phiUnclusteredDown()) )
	    continue;
	}
      }

      double pfmet_pt  = nt.MET_pt();
      double pfmet_phi = nt.MET_phi();
      double puppimet_pt = nt.PuppiMET_pt();
      double puppimet_phi = nt.PuppiMET_phi();
      if ( isMC && ( process!="DYbb" && process!="DYv7" && process!="TTv7" && !process.Contains("BFF") ) ) {
        // JEC uncertainties on PUPPI MET
        if ( JECUnc==2 ) {
          puppimet_pt = nt.PuppiMET_ptJESUp();
          puppimet_phi = nt.PuppiMET_phiJESUp();
        }
        if ( JECUnc==-2 ) {
          puppimet_pt = nt.PuppiMET_ptJESDown();
          puppimet_phi = nt.PuppiMET_phiJESDown();
        }
        // JER uncertainties on PUPPI MET
        if ( JERUnc==2 ) {
          puppimet_pt = nt.PuppiMET_ptJERUp();
          puppimet_phi = nt.PuppiMET_phiJERUp();
        }
        if ( JERUnc==-2 ) {
          puppimet_pt = nt.PuppiMET_ptJERDown();
          puppimet_phi = nt.PuppiMET_phiJERDown();
        }
        if ( UnclEnUnc==2 ) {
          puppimet_pt = nt.PuppiMET_ptUnclusteredUp();
          puppimet_phi = nt.PuppiMET_phiUnclusteredUp();
        }
        if ( UnclEnUnc==-2 ) {
          puppimet_pt = nt.PuppiMET_ptUnclusteredDown();
          puppimet_phi = nt.PuppiMET_phiUnclusteredDown();
        }
      }

      if ( !removeCorrections ) {
        std::pair<double,double> pfmet = METXYCorr_Met_MetPhi(pfmet_pt, pfmet_phi, runnb, year, isMC, npv, true, false);
        pfmet_pt  = pfmet.first;
        pfmet_phi = pfmet.second;
        std::pair<double,double> puppimet = METXYCorr_Met_MetPhi(puppimet_pt, puppimet_phi, runnb, year, isMC, npv, true, true);
        puppimet_pt  = puppimet.first;
        puppimet_phi = puppimet.second;
      }

      // Account for tunepRelPt if useTuneP
      vector<LorentzVector> Muon_p4 = {};
      vector<double> Muon_pt = {};
      vector<double> Muon_tkRelIso = {};
      TVector2 pfmet_temp;
      pfmet_temp.SetMagPhi(pfmet_pt,pfmet_phi);
      TVector2 puppimet_temp;
      puppimet_temp.SetMagPhi(puppimet_pt,puppimet_phi);
      // Muon selection loop
      int nMu_id = 0;
      vector<int> cand_muons_id;
      int nMu_pt = 0;
      vector<int> cand_muons_id_pteta;
      int nMu_iso = 0;
      vector<int> cand_muons;
      //
      float triggerWeight = -1.0;
      //
      for ( unsigned int mu = 0; mu < nt.nMuon(); mu++ ) {
	Muon_p4.push_back(LorentzVector(nt.Muon_pt().at(mu),nt.Muon_eta().at(mu),nt.Muon_phi().at(mu),nt.Muon_mass().at(mu)));
        if ( isMC && muonResUnc != 0 ) { // 2 means that variation are to be applied
          // https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2018#Momentum_Resolution
          // https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2017#Momentum_Resolution
          // https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2016#Momentum_Resolution
          float a, b, c;
          if ( fabs(Muon_p4[mu].Eta()) < 1.2 ) {
            a = ( year == "2018" ?  0.0141926   : ( year == "2017" ?  0.0145351   :  0.0146577   ) );
            b = ( year == "2018" ?  4.23456e-05 : ( year == "2017" ?  4.24022e-05 :  4.48517e-05 ) );
            c = ( year == "2018" ? -9.91644e-09 : ( year == "2017" ? -1.01461e-08 : -9.87206e-09 ) );
          }
          else {
            a = ( year == "2018" ?  0.016883    : ( year == "2017" ?  0.0168087   :  0.0155794   ) );
            b = ( year == "2018" ?  6.21438e-05 : ( year == "2017" ?  5.57382e-05 :  7.22117e-05 ) );
            c = ( year == "2018" ? -9.79418e-09 : ( year == "2017" ? -8.89713e-09 : -1.27255e-08 ) );
          }
          float muonP = Muon_p4[mu].P();
          float muonResSmearParam = a + b * muonP + c * muonP * muonP;
          double muonResSmearFactor = rnd_muonMomRes.Gaus(0,muonResSmearParam*0.46);
          Muon_p4[mu].SetPt( Muon_p4[mu].Pt()*(1 + 0.5*muonResUnc*muonResSmearFactor) ); // 0.5*muonResUnc = sign of variation
        }
        if ( isMC && muonScaleUnc != 0 ) { // 2 means that variation are to be applied
          // https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2016#Momentum_Scale
          // https://gitlab.cern.ch/cms-muonPOG/GeneralizedEndpoint/GEScaleSyst
          if ( year=="2017" ) { // Only available for 2017!
            float muonScaleCorrPt = GE.GEScaleCorrPt(Muon_p4[mu].Pt(), Muon_p4[mu].Eta(), Muon_p4[mu].Phi(), nt.Muon_pdgId().at(mu)/abs(nt.Muon_pdgId().at(mu)), 0, 0);
            if ( muonScaleCorrPt < -1e8 ) muonScaleCorrPt = Muon_p4[mu].Pt(); // Do not assign the crazy -1e9 value to muons out of the range of their correction tables => Fall back to the non-corrected value.
            Muon_p4[mu].SetPt( muonScaleCorrPt );
          }
        }
	Muon_pt.push_back(Muon_p4[mu].Pt());
	Muon_tkRelIso.push_back(nt.Muon_tkRelIso().at(mu)); // We don't change the relative isolation based on the muon momentum resolution, as this seems to be out of the scope of this uncertainty
	//
        bool mu_trk_and_global = ( nt.Muon_isGlobal().at(mu) && nt.Muon_isTracker().at(mu) );
        bool mu_id = ( nt.Muon_highPtId().at(mu) >= 2 );
	bool mu_pt = false;
	bool mu_iso = false;
        if ( mu_trk_and_global && mu_id && fabs(nt.Muon_dxy().at(mu))<0.02 && fabs(nt.Muon_dz().at(mu))<0.1 ) {
          nMu_id++;
          cand_muons_id.push_back(mu);
	  if ( useTuneP ) {
	    TVector2 muon_temp;
	    TVector2 muon_temp_tunep;
	    muon_temp.SetMagPhi(Muon_pt[mu],nt.Muon_phi().at(mu));
	    Muon_pt[mu] *= nt.Muon_tunepRelPt().at(mu);
	    Muon_p4[mu] = LorentzVector(Muon_pt[mu],nt.Muon_eta().at(mu),nt.Muon_phi().at(mu),nt.Muon_mass().at(mu));
	    muon_temp_tunep.SetMagPhi(Muon_pt[mu],nt.Muon_phi().at(mu));
	    // Correct MET for highPtId muon candidates
	    pfmet_temp+=muon_temp;
	    pfmet_temp-=muon_temp_tunep;
	    puppimet_temp+=muon_temp;
	    puppimet_temp-=muon_temp_tunep;
	  }
	  else {
	    Muon_tkRelIso[mu] *= nt.Muon_tunepRelPt().at(mu);
	  }
	  mu_pt = ( Muon_pt.at(mu) > 53 && fabs(nt.Muon_eta().at(mu)) < 2.4 );
	  mu_iso = ( Muon_tkRelIso.at(mu) < 0.05 && (Muon_tkRelIso.at(mu)) * (Muon_pt.at(mu)) < 5.0 );
          if ( mu_pt ) {
            nMu_pt++;
            cand_muons_id_pteta.push_back(mu);
            if ( mu_iso ) {
              nMu_iso++;
              cand_muons.push_back(mu);
            }
          }
        }
	if ( isMC ) {
	  // 2016: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2016
	  // 2017: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2017
	  // 2018: https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2018
	  // Apply muon (RECO, ID, ISO) SFs
	  if ( muonRecoSF!=0 ) {
	    TString tvariation = "central";
	    if ( muonRecoSF==2 ) tvariation = "up";
	    else if ( muonRecoSF==-2 ) tvariation = "down";
	    // If muon p>100 GeV or (p>50 GeV and |eta|<1.6), high-pT RECO SF are applied as a function of muon p and |eta|
	    // (central high-pT RECO SFs equal zero elsewhere)
	    // Else medium-pT RECO SF are applied as a function of muon pT and |eta|, to avoid zero SFs
	    weight *= get_muonRecoSF(Muon_p4.at(mu).P(), Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	  }
	  if ( muonIdSF!=0 && mu_id ) {
	    TString tvariation = "central";
	    if ( muonIdSF==2 ) tvariation = "up";
	    else if ( muonIdSF==-2 ) tvariation = "down";
	    weight *= get_muonIDSF(Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	  }
	  if ( muonIsoSF!=0 && mu_iso ) {
	    TString tvariation = "central";
	    if ( muonIsoSF==2 ) tvariation = "up";
	    else if ( muonIsoSF==-2 ) tvariation = "down";
	    weight *= get_muonIsoSF(Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
	  }
	  // Apply trigger SF
	  if ( triggerSF!=0 && !(triggerWeight > 0.0) ) {
	    TString tvariation = "central";
	    if ( triggerSF==2 ) tvariation = "up";
	    else if ( triggerSF==-2 ) tvariation = "down";
	    float minPt  = 52.0;
	    float maxEta = 2.4; 
	    for ( int n = 0; n < nt.nTrigObj(); n++ ) {
	      if ( abs(nt.TrigObj_id().at(n)) != 13 ) continue;
	      if ( !(nt.TrigObj_filterBits().at(n) & 8) ) continue;
	      if ( IsMatched( nt.Muon_eta().at(mu), nt.Muon_phi().at(mu), nt.TrigObj_eta().at(n), nt.TrigObj_phi().at(n), 0.02 ) ) {
		if ( Muon_pt.at(mu) < minPt ) {
		  triggerWeight = 0.0;
		}
		else if ( fabs(nt.Muon_eta().at(mu) ) < maxEta && mu_id ) {
		  triggerWeight = get_triggerSF(Muon_pt.at(mu), nt.Muon_eta().at(mu), year, tvariation);
		}
		else continue;
	      }
	    }
	  }
	}
      }

      pfmet_pt  = pfmet_temp.Mod();
      pfmet_phi = TVector2::Phi_mpi_pi(pfmet_temp.Phi());
      puppimet_pt  = puppimet_temp.Mod();
      puppimet_phi = TVector2::Phi_mpi_pi(puppimet_temp.Phi());

      icutflow=0;
      // For data, fill "total" in cutflow after golden JSON
      if ( !isMC ) {
        h_cutflow->Fill(icutflow,weight*factor);
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (prodModesel[iprodMode])
                  slicedcutflows[slice]->Fill(icutflow,weight*factor);
              }
            }
          }
        }
      }
      icutflow++;

      // Define histo names and variables
      plot_names = { };
      map<TString, float> variable { };

      // Define histo2D names and variables
      plot2D_names = { };
      map<TString, float> variableX { };
      map<TString, float> variableY { };

      // Define extra histo names and variables (for third lepton/isotrack veto variables)
      vector<TString> extra_plot_names = { };
      map<TString, float> extra_variable { };

      // Book histo names and variables
      if (doHistos) {
        plot_names.push_back("pfmet_pt");
        variable.insert({"pfmet_pt", pfmet_pt});

        plot_names.push_back("pfmet_phi");
        variable.insert({"pfmet_phi", pfmet_phi});

        plot_names.push_back("puppimet_pt");
        variable.insert({"puppimet_pt", puppimet_pt});

        plot_names.push_back("puppimet_phi");
        variable.insert({"puppimet_phi", puppimet_phi});

        if ( muonDebug ) {
          plot_names.push_back("mu1_pt");
          variable.insert({"mu1_pt", Muon_pt.at(0)});

          plot_names.push_back("mu2_pt");
          variable.insert({"mu2_pt", Muon_pt.at(1)});

          plot_names.push_back("mu1_eta");
          variable.insert({"mu1_eta", nt.Muon_eta().at(0)});

          plot_names.push_back("mu2_eta");
          variable.insert({"mu2_eta", nt.Muon_eta().at(1)});

          plot_names.push_back("mu1_phi");
          variable.insert({"mu1_phi", nt.Muon_phi().at(0)});

          plot_names.push_back("mu2_phi");
          variable.insert({"mu2_phi", nt.Muon_phi().at(1)});

          plot_names.push_back("mu1_dxy");
          variable.insert({"mu1_dxy", fabs(nt.Muon_dxy().at(0))});

          plot_names.push_back("mu2_dxy");
          variable.insert({"mu2_dxy", fabs(nt.Muon_dxy().at(1))});

          plot_names.push_back("mu1_dz");
          variable.insert({"mu1_dz", fabs(nt.Muon_dz().at(0))});

          plot_names.push_back("mu2_dz");
          variable.insert({"mu2_dz", fabs(nt.Muon_dz().at(1))});

          plot_names.push_back("mu1_relPtErr");
          variable.insert({"mu1_relPtErr", nt.Muon_ptErr().at(0) / Muon_pt.at(0)});

          plot_names.push_back("mu2_relPtErr");
          variable.insert({"mu2_relPtErr", nt.Muon_ptErr().at(1) / Muon_pt.at(1)});

          plot_names.push_back("mu1_tunepRelPt");
          variable.insert({"mu1_tunepRelPt", nt.Muon_tunepRelPt().at(0)});

          plot_names.push_back("mu2_tunepRelPt");
          variable.insert({"mu2_tunepRelPt", nt.Muon_tunepRelPt().at(1)});

          plot_names.push_back("mu1_trkRelIso");
          variable.insert({"mu1_trkRelIso", Muon_tkRelIso.at(0)});

          plot_names.push_back("mu1_trkAbsIso");
          variable.insert({"mu1_trkAbsIso", Muon_tkRelIso.at(0) *  Muon_pt.at(0)});

          plot_names.push_back("mu2_trkRelIso");
          variable.insert({"mu2_trkRelIso", Muon_tkRelIso.at(1)});

          plot_names.push_back("mu2_trkAbsIso");
          variable.insert({"mu2_trkAbsIso", Muon_tkRelIso.at(1) *  Muon_pt.at(1)});

          plot_names.push_back("nCand_Muons");
          variable.insert({"nCand_Muons", nt.nMuon()});
        }
      }


      // After skim
      label = "After skim";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }
      icutflow++;

      // HLT selection
      if ( (year=="2016nonAPV" || year=="2016APV") &&
             !( (tree->GetBranch("HLT_Mu50") ? nt.HLT_Mu50() : 0)
               || (tree->GetBranch("HLT_TkMu50") ? nt.HLT_TkMu50() : 0) ) ) continue;
      if ( (year=="2017" || year=="2018") &&
              !( (tree->GetBranch("HLT_Mu50") ? nt.HLT_Mu50() : 0)
                || (tree->GetBranch("HLT_OldMu100") ? nt.HLT_OldMu100() : 0)
                || (tree->GetBranch("HLT_TkMu100") ? nt.HLT_TkMu100() : 0) ) ) continue;

      // Apply trigger SF:
      if ( isMC && triggerSF!=0 )  {
        if ( triggerWeight < 0.0 )
 	  weight *= 0.0;
 	else
 	  weight *= triggerWeight;
      }

      label = "HLT";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }
      icutflow++;

      // Number of good primary vertices
      if ( nt.PV_npvsGood() < 1 ) continue;
      // MET filters: https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2#UL_data
      if ( process!="DYbb" && process!="DYv7" && process!="TTv7" && !process.Contains("BFF") ) { //v9
	if ( // process.Contains("data") &&
	    !( nt.Flag_goodVertices()>=1 &&
	       nt.Flag_globalSuperTightHalo2016Filter()>=1 &&
	       nt.Flag_HBHENoiseFilter()>=1 &&
	       nt.Flag_HBHENoiseIsoFilter()>=1 &&
	       nt.Flag_EcalDeadCellTriggerPrimitiveFilter()>=1 &&
	       nt.Flag_BadPFMuonFilter()>=1 &&
	       nt.Flag_BadPFMuonDzFilter()>=1 &&
	       nt.Flag_eeBadScFilter()>=1 &&
	       ( year.Contains("2016") ? 1 : nt.Flag_ecalBadCalibFilter()>=1 ) &&
	       ( year.Contains("2016") ? 1 : nt.Flag_hfNoisyHitsFilter()>=1 ) )
	     ) continue;
      }
      else {
	if ( // process.Contains("data") &&
	    !( nt.Flag_goodVertices()>=1 &&
	       nt.Flag_globalSuperTightHalo2016Filter()>=1 &&
	       nt.Flag_HBHENoiseFilter()>=1 &&
	       nt.Flag_HBHENoiseIsoFilter()>=1 &&
	       nt.Flag_EcalDeadCellTriggerPrimitiveFilter()>=1 &&
	       nt.Flag_BadPFMuonFilter()>=1 &&
	       nt.Flag_eeBadScFilter()>=1 &&
	       ( year.Contains("2016") ? 1 : nt.Flag_ecalBadCalibFilter()>=1 ) )
	     ) continue;
      }

      // Apply extra noise cleaning
      if ( !usePuppiMET ) {
	if( isinf(pfmet_pt) || isnan(pfmet_pt) )
	  continue;
      }
      else {
	if ( isinf(puppimet_pt) || isnan(puppimet_pt) )
	  continue;
      }
      if ( nt.nJet()>0 && nt.Jet_pt().at(0)>13000.0 )
	continue;
      if ( nt.nMuon()>0 && Muon_pt.at(0)>13000.0 )
	continue;

      // Application of JEC/JER uncertainties
      vector<LorentzVector> Jet_p4 = {};
      for ( unsigned int ijet=0; ijet < nt.nJet(); ijet++ ) {
        LorentzVector jet_p4 = nt.Jet_p4()[ijet];

        // JECs
        if ( abs(JECUnc)==2 && isMC ) { // 2 means that variation are to be applied
          jec_unc->setJetEta(jet_p4.eta());
          jec_unc->setJetPt(jet_p4.pt());
          jet_p4 *= ( 1. + 0.5*JECUnc*(jec_unc->getUncertainty(true)) );
        }

        // JERs
        if ( isMC ) { // JERUnc == 1 means the nominal value is applied, +/-2 means a variation is applied, anything else means JERs are not applied.
          jer_unc->setJetEta(jet_p4.eta());
          jer_unc->setJetPt(jet_p4.pt());
          jer_unc->setRho(nt.fixedGridRhoFastjetAll());
          jer_unc->applyJER(jet_p4, JERUnc, nt.GenJet_p4(), rnd);
        }
        
        Jet_p4.push_back(jet_p4);
      }

      // For test: use Run2018B, with exclusion of HEM15/16 affcted runs:
      if ( !isMC ) {
	if ( !doHEMveto && useOnlyRun2018B && runnb >= HEM_startRun )
	  continue;
      }
      // HEM15/16 veto
      if ( doHEMveto && year == "2018" ) {
	if ( ( !isMC && runnb >= HEM_startRun ) || ( isMC /*&& ( evtnb % HEM_fracDen < HEM_fracNum )*/ ) ) {
	  // Jets
	  bool hasHEMjet = false;
	  if ( useHEMjets )
	    for ( unsigned int i=0; i < nt.nJet(); i++ ) {
	      if ( Jet_p4.at(i).Pt() < HEM_jetPtCut )
		break;
	      // For jets, increase affected area by half of jet cone (i.e., by 0.2)
	      if ( nt.Jet_jetId().at(i) > 1 &&
		   Jet_p4.at(i).eta() > HEM_region[0]-0.2 && Jet_p4.at(i).eta() < HEM_region[1]+0.2 &&
		   Jet_p4.at(i).phi() > HEM_region[2]-0.2 && Jet_p4.at(i).phi() < HEM_region[3]+0.2 ) {
		hasHEMjet = true;
		break;
	      }
	    }
	  // Muons (using same ID as for analysis)
	  bool hasHEMmuon = false;
	  if ( useHEMmuons )
	    for ( unsigned int i = 0; i < nt.nMuon(); i++ ) {
	      if ( Muon_pt.at(i) < HEM_lepPtCut )
		break;
	      if ( nt.Muon_isGlobal().at(i) && nt.Muon_isTracker().at(i) &&
		   nt.Muon_highPtId().at(i) >= 2 &&
		   fabs(nt.Muon_dxy().at(i)) < 0.02 && fabs(nt.Muon_dz().at(i)) < 0.1 &&
		   Muon_tkRelIso.at(i) < 0.05 && (Muon_tkRelIso.at(i)) * (Muon_pt.at(i)) < 5.0 &&
		   nt.Muon_eta().at(i) > HEM_region[0] && nt.Muon_eta().at(i) < HEM_region[1] &&
		   nt.Muon_phi().at(i) > HEM_region[2] && nt.Muon_phi().at(i) < HEM_region[3] ) {
		hasHEMmuon = true;
		break;
	      }
	    }
	  // Electrons
	  bool hasHEMelectron = false;
	  if ( useHEMelectrons )
	    for ( unsigned int i = 0; i < nt.nElectron(); i++ ) {
	      if ( nt.Electron_pt().at(i) < HEM_lepPtCut )
		break;
	      if ( nt.Electron_cutBased().at(i) > 0 &&
		   fabs(nt.Electron_dxy().at(i)) < 0.2 &&
		   fabs(nt.Electron_dz().at(i)) < 0.5 &&
		   nt.Electron_eta().at(i) > HEM_region[0] && nt.Electron_eta().at(i) < HEM_region[1] &&
		   nt.Electron_phi().at(i) > HEM_region[2] && nt.Electron_phi().at(i) < HEM_region[3] ) {
		hasHEMelectron = true;
		break;
	      }
	    }
	  // IsoTracks (using both PF candidates and highPurity lost tracks)
	  bool hasHEMisotrack = false;
	  if ( useHEMisotracks )
	    for ( unsigned int i = 0; i < nt.nIsoTrack(); i++ ) {
	      if ( nt.IsoTrack_pt().at(i) < HEM_trkPtCut )
		break;
	      if ( (nt.IsoTrack_isPFcand().at(i) || nt.IsoTrack_isHighPurityTrack().at(i)) &&
		   (abs(nt.IsoTrack_pdgId().at(i))==11 || abs(nt.IsoTrack_pdgId().at(i))==13 || abs(nt.IsoTrack_pdgId().at(i))==211) &&
		   fabs(nt.IsoTrack_dxy().at(i)) < 0.2 &&
		   fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
		   (((abs(nt.IsoTrack_pdgId().at(i))==11 || abs(nt.IsoTrack_pdgId().at(i))==13) && nt.IsoTrack_pfRelIso03_chg().at(i) < 0.2) ||
		    (abs(nt.IsoTrack_pdgId().at(i))==211 && nt.IsoTrack_pfRelIso03_chg().at(i) < 0.1)) &&
		   nt.IsoTrack_eta().at(i) > HEM_region[0] && nt.IsoTrack_eta().at(i) < HEM_region[1] &&
		   nt.IsoTrack_phi().at(i) > HEM_region[2] && nt.IsoTrack_phi().at(i) < HEM_region[3] ) {
		hasHEMisotrack = true;
		break;
	      }
	    }
	  // Apply HEM veto
	  if( hasHEMjet || hasHEMmuon || hasHEMelectron || hasHEMisotrack ) {
	    if ( !isMC ) 
	      continue;
	    else
	      weight *= (1.0 - HEM_frac);
	  }
	}
      }

      // Fill histos: sel0
      label = ">0 good PVs & MET Filters";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }
      icutflow++;
      TString sel;
      if (doHistos==2) {
        sel = "sel0";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot2D_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
          }
        }
      }

      // Defining booleans for cutflow
      bool id_req = ( nMu_id > 1 );
      bool pt_req = ( nMu_pt > 1 );
      bool iso_req = ( nMu_iso > 1);

      if ( !id_req ) continue;
      // Fill histos: sel1
      label = ">1 #mu w/ highPt ID, |dxy|<0.02 cm & |dz|<0.1 cm";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }
      icutflow++;
      if (doHistos==2) {
        sel = "sel1";
        if ( muonDebug ) {
          variable["mu1_pt"] = Muon_pt.at(cand_muons_id[0]);
          variable["mu2_pt"] = Muon_pt.at(cand_muons_id[1]);
          variable["mu1_eta"] = nt.Muon_eta().at(cand_muons_id[0]);
          variable["mu2_eta"] = nt.Muon_eta().at(cand_muons_id[1]);
          variable["mu1_phi"] = nt.Muon_phi().at(cand_muons_id[0]);
          variable["mu2_phi"] = nt.Muon_phi().at(cand_muons_id[1]);
          variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id[0]));
          variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id[1]));
          variable["mu1_dz"] = fabs(nt.Muon_dz().at(cand_muons_id[0]));
          variable["mu2_dz"] = fabs(nt.Muon_dz().at(cand_muons_id[1]));
          variable["mu1_relPtErr"] = nt.Muon_ptErr().at(cand_muons_id[0]) / Muon_pt.at(cand_muons_id[0]);
          variable["mu2_relPtErr"] = nt.Muon_ptErr().at(cand_muons_id[1]) / Muon_pt.at(cand_muons_id[1]);
          variable["mu1_tunepRelPt"] = nt.Muon_tunepRelPt().at(cand_muons_id[0]);
          variable["mu2_tunepRelPt"] = nt.Muon_tunepRelPt().at(cand_muons_id[1]);
          variable["mu1_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id[0]);
          variable["mu1_trkAbsIso"] = Muon_tkRelIso.at(cand_muons_id[0]) * Muon_pt.at(cand_muons_id[0]);
          variable["mu2_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id[1]);
          variable["mu2_trkAbsIso"] = Muon_tkRelIso.at(cand_muons_id[1]) * Muon_pt.at(cand_muons_id[1]);
          variable["nCand_Muons"] = cand_muons.size();
        }
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot2D_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
          }
        }
      }

      if ( !pt_req ) continue;
      // Fill histos: sel2
      label = ">1 #mu w/ pT>53 GeV & |eta|<2.4";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }
      icutflow++;
      if (doHistos==2) {
        sel = "sel2";
        if ( muonDebug ) {
          variable["mu1_pt"] = Muon_pt.at(cand_muons_id_pteta[0]);
          variable["mu2_pt"] = Muon_pt.at(cand_muons_id_pteta[1]);
          variable["mu1_eta"] = nt.Muon_eta().at(cand_muons_id_pteta[0]);
          variable["mu2_eta"] = nt.Muon_eta().at(cand_muons_id_pteta[1]);
          variable["mu1_phi"] = nt.Muon_phi().at(cand_muons_id_pteta[0]);
          variable["mu2_phi"] = nt.Muon_phi().at(cand_muons_id_pteta[1]);
          variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id_pteta[0]));
          variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(cand_muons_id_pteta[1]));
          variable["mu1_dz"] = fabs(nt.Muon_dz().at(cand_muons_id_pteta[0]));
          variable["mu2_dz"] = fabs(nt.Muon_dz().at(cand_muons_id_pteta[1]));
          variable["mu1_relPtErr"] = nt.Muon_ptErr().at(cand_muons_id_pteta[0]) / Muon_pt.at(cand_muons_id_pteta[0]);
          variable["mu2_relPtErr"] = nt.Muon_ptErr().at(cand_muons_id_pteta[1]) / Muon_pt.at(cand_muons_id_pteta[1]);
          variable["mu1_tunepRelPt"] = nt.Muon_tunepRelPt().at(cand_muons_id_pteta[0]);
          variable["mu2_tunepRelPt"] = nt.Muon_tunepRelPt().at(cand_muons_id_pteta[1]);
          variable["mu1_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id_pteta[0]);
          variable["mu1_trkAbsIso"] = Muon_tkRelIso.at(cand_muons_id_pteta[0]) * Muon_pt.at(cand_muons_id_pteta[0]);
          variable["mu2_trkRelIso"] = Muon_tkRelIso.at(cand_muons_id_pteta[1]);
          variable["mu2_trkAbsIso"] = Muon_tkRelIso.at(cand_muons_id_pteta[1]) * Muon_pt.at(cand_muons_id_pteta[1]);
          variable["nCand_Muons"] = cand_muons.size();
        }
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot2D_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
          }
        }
      }

      if ( !iso_req ) continue;
      // Fill histos: sel3
      label = ">1 #mu w/ track iso./pT<0.05 & track iso.<5 GeV";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }

      icutflow++;
      if (doHistos==2) {
        sel = "sel3";
        if ( muonDebug ) {
          variable["mu1_pt"] = Muon_pt.at(cand_muons[0]);
          variable["mu2_pt"] = Muon_pt.at(cand_muons[1]);
          variable["mu1_eta"] = nt.Muon_eta().at(cand_muons[0]);
          variable["mu2_eta"] = nt.Muon_eta().at(cand_muons[1]);
          variable["mu1_phi"] = nt.Muon_phi().at(cand_muons[0]);
          variable["mu2_phi"] = nt.Muon_phi().at(cand_muons[1]);
          variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(cand_muons[0]));
          variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(cand_muons[1]));
          variable["mu1_dz"] = fabs(nt.Muon_dz().at(cand_muons[0]));
          variable["mu2_dz"] = fabs(nt.Muon_dz().at(cand_muons[1]));
          variable["mu1_relPtErr"] = nt.Muon_ptErr().at(cand_muons[0]) / Muon_pt.at(cand_muons[0]);
          variable["mu2_relPtErr"] = nt.Muon_ptErr().at(cand_muons[1]) / Muon_pt.at(cand_muons[1]);
          variable["mu1_tunepRelPt"] = nt.Muon_tunepRelPt().at(cand_muons[0]);
          variable["mu2_tunepRelPt"] = nt.Muon_tunepRelPt().at(cand_muons[1]);
          variable["mu1_trkRelIso"] = Muon_tkRelIso.at(cand_muons[0]);
          variable["mu1_trkAbsIso"] = Muon_tkRelIso.at(cand_muons[0]) * Muon_pt.at(cand_muons[0]);
          variable["mu2_trkRelIso"] = Muon_tkRelIso.at(cand_muons[1]);
          variable["mu2_trkAbsIso"] = Muon_tkRelIso.at(cand_muons[1]) * Muon_pt.at(cand_muons[1]);
          variable["nCand_Muons"] = cand_muons.size();
        }
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot2D_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
          }
        }
      }

      // Trigger object finding (match: dR<0.02)
      bool atLeastSelectedMu_matchedToTrigObj = false;
      vector<bool> muMatchedToTrigObj;
      for ( auto i_cand_muons : cand_muons ) {
	if ( muMatchedToTrigObj.size() > i_cand_muons && muMatchedToTrigObj.at(i_cand_muons)==true ) continue;
	for ( int n = 0; n < nt.nTrigObj(); n++ ) {
	  if ( abs(nt.TrigObj_id().at(n)) != 13 ) continue;
	  if ( !(nt.TrigObj_filterBits().at(n) & 8) ) continue;
	  if ( IsMatched( nt.Muon_eta().at(i_cand_muons), nt.Muon_phi().at(i_cand_muons), nt.TrigObj_eta().at(n), nt.TrigObj_phi().at(n), 0.02 ) ) {
            muMatchedToTrigObj.push_back(true);
            atLeastSelectedMu_matchedToTrigObj = true;
	    break;
          }
        }
	if ( muMatchedToTrigObj.size() <= i_cand_muons ) 
	  muMatchedToTrigObj.push_back(false);
      }
      if ( !atLeastSelectedMu_matchedToTrigObj ) continue;
      // Fill histos: sel4
      label = ">0 HLT match (dR<0.02)";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow,weight*factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow+1,slicedlabel);
            }
          }
        }
      }
      icutflow++;
      if (doHistos==2) {
        sel = "sel4";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos[name]->Fill(variable[plot_name], weight * factor);
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
            TString name = plot2D_name+"_"+sel+"_"+mllbin[0] + prodMode[iprodMode];
            if (prodModesel[iprodMode])
              histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
          }
        }
      }

      int leadingMu_idx = -1, subleadingMu_idx = -1;
      float selectedPair_M = -1.0;
      bool Zboson = false;
      for ( unsigned int i=0; i<cand_muons.size(); i++ ) {
        TVector3 mu_1(Muon_p4.at(cand_muons[i]).Px(),Muon_p4.at(cand_muons[i]).Py(),Muon_p4.at(cand_muons[i]).Pz());
        for ( unsigned int j=i+1; j<cand_muons.size(); j++ ) {
          if ( nt.Muon_pdgId().at(cand_muons[i]) + nt.Muon_pdgId().at(cand_muons[j]) != 0 ) continue; // Opposite sign, same flavor
          if ( !(muMatchedToTrigObj[i] || muMatchedToTrigObj[j]) ) continue; // At least one muon in pair matched to HLT
          TVector3 mu_2(Muon_p4.at(cand_muons[j]).Px(),Muon_p4.at(cand_muons[j]).Py(),Muon_p4.at(cand_muons[j]).Pz());
          if ( !(IsSeparated( mu_1, mu_2, 0.02 ) ) ) continue; // 3D angle between muons > pi - 0.02
          float m_ll = (Muon_p4.at(cand_muons[i])+Muon_p4.at(cand_muons[j])).M();
          if ( fabs(m_ll - Zmass)<20.0 ) { // Reject event if it contains dimuon pair compatible with Z mass (within 20 GeV)
            Zboson = true;
            continue;
          }
          if ( selectedPair_M < 0.0 ) {
            leadingMu_idx = cand_muons[i];
            subleadingMu_idx = cand_muons[j];
            selectedPair_M = m_ll;
          }
        }
        if ( Zboson ) break;
      }
      if ( selectedPair_M < 0.0 || Zboson ) continue;

      auto leadingMu_p4 = Muon_p4.at(leadingMu_idx);
      auto subleadingMu_p4 = Muon_p4.at(subleadingMu_idx);
      auto selectedPair_p4 = leadingMu_p4 + subleadingMu_p4;
      float dPhi_ll_MET = fabs(TVector2::Phi_mpi_pi(selectedPair_p4.Phi() - puppimet_phi));
      if ( !(usePuppiMET) )
	dPhi_ll_MET = fabs(TVector2::Phi_mpi_pi(selectedPair_p4.Phi() - pfmet_phi));

      float minDPhi_l_MET = 1e9;
      float maxDPhi_l_MET = -1e9;
      float dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(leadingMu_p4.Phi() - puppimet_phi));
      if ( !(usePuppiMET) )
	dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(leadingMu_p4.Phi() - pfmet_phi));
      if ( dPhi_l_MET < minDPhi_l_MET ) minDPhi_l_MET = dPhi_l_MET;
      if ( dPhi_l_MET > maxDPhi_l_MET ) maxDPhi_l_MET = dPhi_l_MET;
      dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(subleadingMu_p4.Phi() - puppimet_phi));
      if ( !(usePuppiMET) )
	dPhi_l_MET = fabs(TVector2::Phi_mpi_pi(subleadingMu_p4.Phi() - pfmet_phi));
      if ( dPhi_l_MET < minDPhi_l_MET ) minDPhi_l_MET = dPhi_l_MET;
      if ( dPhi_l_MET > maxDPhi_l_MET ) maxDPhi_l_MET = dPhi_l_MET;

      mllbinsel[0] = true;
      if (doMllBins) {
        if ( selectedPair_M > 175. && selectedPair_M < 300.)
          mllbinsel[1] = true;
        else mllbinsel[1] = false;
        if ( selectedPair_M > 300. && selectedPair_M < 500.)
          mllbinsel[2] = true;
        else mllbinsel[2] = false;
        if ( selectedPair_M > 500. && selectedPair_M < 900.)
          mllbinsel[3] = true;
        else mllbinsel[3] = false;
        if ( selectedPair_M > 750. && selectedPair_M < 1250.)
          mllbinsel[4] = true;
        else mllbinsel[4] = false;
        if ( selectedPair_M > 1100. && selectedPair_M < 1900.)
          mllbinsel[5] = true;
        else mllbinsel[5] = false;
        if ( selectedPair_M > 1500. && selectedPair_M < 2500.)
          mllbinsel[6] = true;
        else mllbinsel[6] = false;
      }
      else if (doMllBinsForBFF) {
        if ( selectedPair_M > 225. && selectedPair_M < 275.)
          mllbinsel[1] = true;
        else mllbinsel[1] = false;
        if ( selectedPair_M > 315. && selectedPair_M < 385.)
          mllbinsel[2] = true;
        else mllbinsel[2] = false;
        if ( selectedPair_M > 360. && selectedPair_M < 440.)
          mllbinsel[3] = true;
        else mllbinsel[3] = false;
        if ( selectedPair_M > 450. && selectedPair_M < 550.)
          mllbinsel[4] = true;
        else mllbinsel[4] = false;
        if ( selectedPair_M > 630. && selectedPair_M < 770.)
          mllbinsel[5] = true;
        else mllbinsel[5] = false;
        if ( selectedPair_M > 900. && selectedPair_M < 1100.)
          mllbinsel[6] = true;
        else mllbinsel[6] = false;
      }

      MuDetRegionSel[0] = true;
      if (doMuDetRegionBins) {
        if (fabs(nt.Muon_eta().at(leadingMu_idx)) < 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) < 1.2)
          MuDetRegionSel[1] = true;
        else
          MuDetRegionSel[1] = false;
        if ((fabs(nt.Muon_eta().at(leadingMu_idx)) < 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) > 1.2) || (fabs(nt.Muon_eta().at(leadingMu_idx)) > 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) < 1.2))
          MuDetRegionSel[2] = true;
        else
          MuDetRegionSel[2] = false;
        if (fabs(nt.Muon_eta().at(leadingMu_idx)) > 1.2 && fabs(nt.Muon_eta().at(subleadingMu_idx)) > 1.2)
          MuDetRegionSel[3] = true;
        else
          MuDetRegionSel[3] = false;
      }
      
      // Add histos: sel5
      if (doHistos) {
        plot_names.push_back("mmumu");
        variable.insert({"mmumu", selectedPair_M});

        if ( muonDebug ) {
          variable["mu1_pt"] = Muon_pt.at(leadingMu_idx);
          variable["mu2_pt"] = Muon_pt.at(subleadingMu_idx);
          variable["mu1_eta"] = nt.Muon_eta().at(leadingMu_idx);
          variable["mu2_eta"] = nt.Muon_eta().at(subleadingMu_idx);
          variable["mu1_phi"] = nt.Muon_phi().at(leadingMu_idx);
          variable["mu2_phi"] = nt.Muon_phi().at(subleadingMu_idx);
          variable["mu1_dxy"] = fabs(nt.Muon_dxy().at(leadingMu_idx));
          variable["mu2_dxy"] = fabs(nt.Muon_dxy().at(subleadingMu_idx));
          variable["mu1_dz"] = fabs(nt.Muon_dz().at(leadingMu_idx));
          variable["mu2_dz"] = fabs(nt.Muon_dz().at(subleadingMu_idx));
          variable["mu1_relPtErr"] = nt.Muon_ptErr().at(leadingMu_idx) / Muon_pt.at(leadingMu_idx);
          variable["mu2_relPtErr"] = nt.Muon_ptErr().at(subleadingMu_idx) / Muon_pt.at(subleadingMu_idx);
          variable["mu1_tunepRelPt"] = nt.Muon_tunepRelPt().at(leadingMu_idx);
          variable["mu2_tunepRelPt"] = nt.Muon_tunepRelPt().at(subleadingMu_idx);
          variable["mu1_trkRelIso"] = Muon_tkRelIso.at(leadingMu_idx);
          variable["mu1_trkAbsIso"] = Muon_tkRelIso.at(leadingMu_idx) * Muon_pt.at(leadingMu_idx);
          variable["mu2_trkRelIso"] = Muon_tkRelIso.at(subleadingMu_idx);
          variable["mu2_trkAbsIso"] = Muon_tkRelIso.at(subleadingMu_idx) * Muon_pt.at(subleadingMu_idx);
          variable["nCand_Muons"] = cand_muons.size();
        }
        else {
          plot_names.push_back("mu1_pt");
          variable.insert({"mu1_pt", Muon_pt.at(leadingMu_idx)});

          plot_names.push_back("mu2_pt");
          variable.insert({"mu2_pt", Muon_pt.at(subleadingMu_idx)});

          plot_names.push_back("mu1_eta");
          variable.insert({"mu1_eta", nt.Muon_eta().at(leadingMu_idx)});

          plot_names.push_back("mu2_eta");
          variable.insert({"mu2_eta", nt.Muon_eta().at(subleadingMu_idx)});

          plot_names.push_back("mu1_phi");
          variable.insert({"mu1_phi", nt.Muon_phi().at(leadingMu_idx)});

          plot_names.push_back("mu2_phi");
          variable.insert({"mu2_phi", nt.Muon_phi().at(subleadingMu_idx)});

          plot_names.push_back("mu1_dxy");
          variable.insert({"mu1_dxy", fabs(nt.Muon_dxy().at(leadingMu_idx))});

          plot_names.push_back("mu2_dxy");
          variable.insert({"mu2_dxy", fabs(nt.Muon_dxy().at(subleadingMu_idx))});

          plot_names.push_back("mu1_dz");
          variable.insert({"mu1_dz", fabs(nt.Muon_dz().at(leadingMu_idx))});

          plot_names.push_back("mu2_dz");
          variable.insert({"mu2_dz", fabs(nt.Muon_dz().at(subleadingMu_idx))});

          plot_names.push_back("mu1_relPtErr");
          variable.insert({"mu1_relPtErr", nt.Muon_ptErr().at(leadingMu_idx) / Muon_pt.at(leadingMu_idx)});

          plot_names.push_back("mu2_relPtErr");
          variable.insert({"mu2_relPtErr", nt.Muon_ptErr().at(subleadingMu_idx) / Muon_pt.at(subleadingMu_idx)});

          plot_names.push_back("mu1_tunepRelPt");
          variable.insert({"mu1_tunepRelPt", nt.Muon_tunepRelPt().at(leadingMu_idx)});

          plot_names.push_back("mu2_tunepRelPt");
          variable.insert({"mu2_tunepRelPt", nt.Muon_tunepRelPt().at(subleadingMu_idx)});

          plot_names.push_back("mu1_trkRelIso");
          variable.insert({"mu1_trkRelIso", Muon_tkRelIso.at(leadingMu_idx)});

          plot_names.push_back("mu1_trkAbsIso");
          variable.insert({"mu1_trkAbsIso", Muon_tkRelIso.at(leadingMu_idx) * Muon_pt.at(leadingMu_idx)});

          plot_names.push_back("mu2_trkRelIso");
          variable.insert({"mu2_trkRelIso", Muon_tkRelIso.at(subleadingMu_idx)});

          plot_names.push_back("mu2_trkAbsIso");
          variable.insert({"mu2_trkAbsIso", Muon_tkRelIso.at(subleadingMu_idx) * Muon_pt.at(subleadingMu_idx)});

          plot_names.push_back("nCand_Muons");
          variable.insert({"nCand_Muons", cand_muons.size()});
        }

        plot_names.push_back("dPhi_ll");
        variable.insert({"dPhi_ll", fabs( TVector2::Phi_mpi_pi( nt.Muon_phi().at(leadingMu_idx) - nt.Muon_phi().at(subleadingMu_idx) ) )});

        plot_names.push_back("dEta_ll");
        variable.insert({"dEta_ll", fabs( nt.Muon_eta().at(leadingMu_idx) - nt.Muon_eta().at(subleadingMu_idx) )});

        plot_names.push_back("dEta_dPhi_ratio_ll");
        variable.insert({"dEta_dPhi_ratio_ll", TMath::Log10( fabs( nt.Muon_eta().at(leadingMu_idx) - nt.Muon_eta().at(subleadingMu_idx) ) / fabs( TVector2::Phi_mpi_pi( nt.Muon_phi().at(leadingMu_idx) - nt.Muon_phi().at(subleadingMu_idx) ) ) )});

        plot_names.push_back("dPhi_ll_MET");
        variable.insert({"dPhi_ll_MET", dPhi_ll_MET});

        plot_names.push_back("minDPhi_l_MET");
        variable.insert({"minDPhi_l_MET", minDPhi_l_MET});

        plot_names.push_back("maxDPhi_l_MET");
        variable.insert({"maxDPhi_l_MET", maxDPhi_l_MET});
      }

      // Fill histos: sel5
      label = "Muon pair (OS, !Z)";
      slicedlabel = "Muon pair (OS), ";
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              TString tlabel = slicedlabel + mllbinlabel[mllbin[imll]] + MuDetRegionbinlabel[MuDetRegion[iMuDet]] + prodModelabel[iprodMode];
              if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow, weight * factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, tlabel);
            }
          }
        }
      }

      icutflow++;
      if (doHistos==2) {
        sel = "sel5";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos[name]->Fill(variable[plot_name], weight * factor);
              }
            }
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
              }
            }
          }
        }
      }

      if ( selectedPair_M < 175 ) continue;
      // Fill histos: sel6
      label = "m_{#mu#mu}>175 GeV";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
        for (unsigned int inb = 0; inb < nbtag.size(); inb++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow, weight * factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
            }
          }
        }
      }
      icutflow++;

      // Look for a third isolated lepton and then veto the event if it is found
      // Muons (using same ID and isolation as for selected muons, to avoid scale factor combinatorics)
      vector<int> extra_muons;
      for ( int i = 0; i < nt.nMuon(); i++ ) {
        if ( Muon_pt.at(i) > 10. &&
	     fabs(nt.Muon_eta().at(i)) < 2.4 &&
	     nt.Muon_isGlobal().at(i) && nt.Muon_isTracker().at(i) &&
	     nt.Muon_highPtId().at(i) >= 2 &&
	     fabs(nt.Muon_dxy().at(i)) < 0.02 && fabs(nt.Muon_dz().at(i)) < 0.1 &&
	     Muon_tkRelIso.at(i) < 0.05 && (Muon_tkRelIso.at(i)) * (Muon_pt.at(i)) < 5.0 &&
	     !( i == leadingMu_idx || i == subleadingMu_idx)) {
          extra_muons.push_back(i);
        }
      }

      // Electrons
      vector<int> extra_electrons;
      for ( int i = 0; i < nt.nElectron(); i++ ) {
        if ( nt.Electron_pt().at(i) > 10. &&
	     fabs(nt.Electron_eta().at(i)) < 2.5 &&
	     nt.Electron_cutBased().at(i) > 0 &&
	     fabs(nt.Electron_dxy().at(i)) < 0.2 &&
	     fabs(nt.Electron_dz().at(i)) < 0.5 ) {
          extra_electrons.push_back(i);
        }
      }

      // IsoTracks
      vector<int> extra_isotracks_lep;
      for ( int i = 0; i < nt.nIsoTrack(); i++ ) {
        if ( nt.IsoTrack_isPFcand().at(i) &&
	     (abs(nt.IsoTrack_pdgId().at(i))==11 || (abs(nt.IsoTrack_pdgId().at(i))==13)) &&
	     nt.IsoTrack_pt().at(i) > 5. && 
	     fabs(nt.IsoTrack_eta().at(i)) < 2.5 &&
	     fabs(nt.IsoTrack_dxy().at(i)) < 0.2 &&
	     fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
	     nt.IsoTrack_pfRelIso03_chg().at(i) < 0.2) {
          float mindr=1e9;
          for ( auto i_cand_muons : cand_muons ) {
            if (i_cand_muons!=leadingMu_idx && i_cand_muons!=subleadingMu_idx) continue;
            float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons);
            float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons));
            float dr = TMath::Sqrt( deta*deta+dphi*dphi );
            if ( dr < mindr ) {
              mindr = dr;
            }
          }
	  // Avoid overlap with muon isolation cone: otherwise, muons and isotracks are anyways likely to fail isolation requirement
          if ( mindr > 0.3 )
            extra_isotracks_lep.push_back(i);
        }
      }

      vector<int> extra_isotracks_chh;
      for ( int i = 0; i < nt.nIsoTrack(); i++ ) {
        if ( nt.IsoTrack_isPFcand().at(i) &&
	     abs(nt.IsoTrack_pdgId().at(i))==211 &&
	     nt.IsoTrack_pt().at(i) > 10. &&
	     fabs(nt.IsoTrack_eta().at(i)) < 2.5 &&
	     fabs(nt.IsoTrack_dxy().at(i)) < 0.2 &&
	     fabs(nt.IsoTrack_dz().at(i)) < 0.1 &&
	     nt.IsoTrack_pfRelIso03_chg().at(i) < 0.1) {
          float mindr=1e9;
          for ( auto i_cand_muons : cand_muons ) {
            if (i_cand_muons!=leadingMu_idx && i_cand_muons!=subleadingMu_idx) continue;
            float deta = nt.IsoTrack_eta().at(i) - nt.Muon_eta().at(i_cand_muons);
            float dphi = TVector2::Phi_mpi_pi(nt.IsoTrack_phi().at(i) - nt.Muon_phi().at(i_cand_muons));
            float dr = TMath::Sqrt( deta*deta+dphi*dphi );
            if ( dr < mindr ) {
              mindr = dr;
            }
          }
	  // Avoid overlap with muon isolation cone: otherwise, muons and isotracks are anyways likely to fail isolation requirement
          if ( mindr > 0.3 )
            extra_isotracks_chh.push_back(i);
        }
      }

      // Add extra histos: before sel6 (third lepton/isotrack veto)
      if (doHistos==2) {
        extra_plot_names.push_back("nExtra_muons");
        extra_variable.insert({"nExtra_muons", extra_muons.size()});

        extra_plot_names.push_back("nExtra_electrons");
        extra_variable.insert({"nExtra_electrons",extra_electrons.size()});

        extra_plot_names.push_back("nExtra_lepIsoTracks");
        extra_variable.insert({"nExtra_lepIsoTracks",extra_isotracks_lep.size()});

        extra_plot_names.push_back("nExtra_chhIsoTracks");
        extra_variable.insert({"nExtra_chhIsoTracks",extra_isotracks_chh.size()});

        if ( extra_muons.size() > 0 ) {
          extra_plot_names.push_back("mu3_pt");
          extra_variable.insert({"mu3_pt", Muon_pt.at(extra_muons[0])});
          extra_plot_names.push_back("mu3_eta");
          extra_variable.insert({"mu3_eta", nt.Muon_eta().at(extra_muons[0])});
          
          extra_plot_names.push_back("mu3_trkRelIso");
          extra_variable.insert({"mu3_trkRelIso", Muon_tkRelIso.at(extra_muons[0])});
          extra_plot_names.push_back("mu3_trkAbsIso");
          extra_variable.insert({"mu3_trkAbsIso", Muon_tkRelIso.at(extra_muons[0]) * Muon_pt.at(extra_muons[0])});
        }

        if ( extra_electrons.size() > 0 ) {
          extra_plot_names.push_back("ele_extra_pt");
          extra_variable.insert({"ele_extra_pt", nt.Electron_pt().at(extra_electrons[0])});

          extra_plot_names.push_back("ele_extra_eta");
          extra_variable.insert({"ele_extra_eta", nt.Electron_eta().at(extra_electrons[0])});

          //extra_plot_names.push_back("ele_extra_miniPFRelIso");
          //extra_variable.insert({"ele_extra_miniPFRelIso", nt.Electron_miniPFRelIso_all().at(extra_electrons[0])});
        }

        if ( extra_isotracks_lep.size() > 0 ) {
          extra_plot_names.push_back("lepIsoTrack_extra_pt");
          extra_variable.insert({"lepIsoTrack_extra_pt", nt.IsoTrack_pt().at(extra_isotracks_lep[0])});

          extra_plot_names.push_back("lepIsoTrack_extra_eta");
          extra_variable.insert({"lepIsoTrack_extra_eta", nt.IsoTrack_eta().at(extra_isotracks_lep[0])});

          extra_plot_names.push_back("lepIsoTrack_extra_PFRelIsoChg");
          extra_variable.insert({"lepIsoTrack_extra_PFRelIsoChg", nt.IsoTrack_pfRelIso03_chg().at(extra_isotracks_lep[0])});
        }

        if ( extra_isotracks_chh.size() > 0 ) {
          extra_plot_names.push_back("chhIsoTrack_extra_pt");
          extra_variable.insert({"chhIsoTrack_extra_pt", nt.IsoTrack_pt().at(extra_isotracks_chh[0])});

          extra_plot_names.push_back("chhIsoTrack_extra_eta");
          extra_variable.insert({"chhIsoTrack_extra_eta", nt.IsoTrack_eta().at(extra_isotracks_chh[0])});

          extra_plot_names.push_back("chhIsoTrack_extra_PFRelIsoChg");
          extra_variable.insert({"chhIsoTrack_extra_PFRelIsoChg", nt.IsoTrack_pfRelIso03_chg().at(extra_isotracks_chh[0])});
        }
      }

      // Fill standard histos for sel6
      if (doHistos==2) {
        sel = "sel6";
        for (unsigned int iplot = 0; iplot < plot_names.size(); iplot++) {
          TString plot_name = plot_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos[name]->Fill(variable[plot_name], weight * factor);
              }
            }
          }
        }
        for (unsigned int iplot = 0; iplot < plot2D_names.size(); iplot++) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
              }
            }
          }
        }
        // Now fill extra histos for sel6 (before third lepton/isotrack veto)
        for ( unsigned int iplot=0; iplot < extra_plot_names.size(); iplot++ ) {
          TString plot_name = extra_plot_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos[name]->Fill(variable[plot_name], weight * factor);
              }
            }
          }
        }
      }

      if ( extra_muons.size() > 0 || extra_electrons.size() > 0 ) continue;
      label = "Third lepton veto";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
        for (unsigned int inb = 0; inb < nbtag.size(); inb++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow, weight * factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
            }
          }
        }
      }
      icutflow++;

      if ( extra_isotracks_lep.size() > 0 || extra_isotracks_chh.size() > 0 ) continue;
      label = "Iso. track veto";
      slicedlabel = label;
      h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
        for (unsigned int inb = 0; inb < nbtag.size(); inb++) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow, weight * factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
            }
          }
        }
      }
      icutflow++;

      // Fill histos: sel7
      if (doHistos==2) {
        sel = "sel7";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos[name]->Fill(variable[plot_name], weight * factor);
              }
            }
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for (unsigned int imll = 0; imll < mllbin.size(); imll++) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
              }
            }
          }
        }
      }

      float btag_prob_DATA=1.0, btag_up_prob_DATA=1.0, btag_dn_prob_DATA=1.0, btag_prob_MC=1.0;
      vector<int> cand_jets, cand_bJets_tight, cand_bJets;
      unsigned int nbtagDeepFlavB = 0;
      for ( unsigned int jet = 0; jet < nt.nJet(); jet++ ) {
        float d_eta_1 = nt.Muon_eta().at(leadingMu_idx) - Jet_p4.at(jet).eta();
        float d_eta_2 = nt.Muon_eta().at(subleadingMu_idx) - Jet_p4.at(jet).eta();
        float d_phi_1 = TVector2::Phi_mpi_pi(nt.Muon_phi().at(leadingMu_idx) - Jet_p4.at(jet).phi());
        float d_phi_2 = TVector2::Phi_mpi_pi(nt.Muon_phi().at(subleadingMu_idx) - Jet_p4.at(jet).phi());
        float dr_jmu1 = TMath::Sqrt( d_eta_1*d_eta_1+d_phi_1*d_phi_1 );
        float dr_jmu2 = TMath::Sqrt( d_eta_2*d_eta_2+d_phi_2*d_phi_2 );
        // Reject jets if they are within dR = 0.4 of the candidate leptons
        if ( dr_jmu1 < 0.4 || dr_jmu2 < 0.4 ) continue;
        if ( Jet_p4.at(jet).Pt() > 20 &&
             fabs(Jet_p4.at(jet).eta()) < 2.5 &&
             nt.Jet_jetId().at(jet) > 1 ) {
          cand_jets.push_back(jet);

          bool isBTagMedium = false, isBTagTight = false;
          if ( nt.Jet_btagDeepFlavB().at(jet) > gconf.WP_DeepFlav_medium ) {
            isBTagMedium = true;
            cand_bJets.push_back(jet);
          }
          if ( nt.Jet_btagDeepFlavB().at(jet) > gconf.WP_DeepFlav_tight ) {
            isBTagTight = true;
            cand_bJets_tight.push_back(jet);
          }

          // https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#1a_Event_reweighting_using_scale
          if ( isMC && bTagSF!=0 ) {
            float pt = Jet_p4.at(jet).Pt();
            float eta = Jet_p4.at(jet).eta();
            int flavor = nt.Jet_hadronFlavour().at(jet);

            float eff_tight = get_bTagEff(pt, eta, year, "tight", flavor, "central");
            float eff_med = get_bTagEff(pt, eta, year, "med", flavor, "central");

            float sf_tight =
	      flavor == 4 ? btagReaderTight->eval_auto_bounds("central", BTagEntry_v2::FLAV_C, eta, pt) : 
	      ( flavor == 5 ? btagReaderTight->eval_auto_bounds("central", BTagEntry_v2::FLAV_B, eta, pt) : btagReaderTight->eval_auto_bounds("central", BTagEntry_v2::FLAV_UDSG, eta, pt) );
            float sf_up_tight =
	      flavor == 4 ? btagReaderTight->eval_auto_bounds("up", BTagEntry_v2::FLAV_C, eta, pt) : 
	      ( flavor == 5 ? btagReaderTight->eval_auto_bounds("up", BTagEntry_v2::FLAV_B, eta, pt) : btagReaderTight->eval_auto_bounds("up", BTagEntry_v2::FLAV_UDSG, eta, pt) );
            float sf_dn_tight =
	      flavor == 4 ? btagReaderTight->eval_auto_bounds("down", BTagEntry_v2::FLAV_C, eta, pt) : 
	      ( flavor == 5 ? btagReaderTight->eval_auto_bounds("down", BTagEntry_v2::FLAV_B, eta, pt) : btagReaderTight->eval_auto_bounds("down", BTagEntry_v2::FLAV_UDSG, eta, pt) );
            float sf_med =
	      flavor == 4 ? btagReaderMedium->eval_auto_bounds("central", BTagEntry_v2::FLAV_C, eta, pt) : 
	      ( flavor == 5 ? btagReaderMedium->eval_auto_bounds("central", BTagEntry_v2::FLAV_B, eta, pt) : btagReaderMedium->eval_auto_bounds("central", BTagEntry_v2::FLAV_UDSG, eta, pt) );
            float sf_up_med =
	      flavor == 4 ? btagReaderMedium->eval_auto_bounds("up", BTagEntry_v2::FLAV_C, eta, pt) : 
	      ( flavor == 5 ? btagReaderMedium->eval_auto_bounds("up", BTagEntry_v2::FLAV_B, eta, pt) : btagReaderMedium->eval_auto_bounds("up", BTagEntry_v2::FLAV_UDSG, eta, pt) );
            float sf_dn_med =
	      flavor == 4 ? btagReaderMedium->eval_auto_bounds("down", BTagEntry_v2::FLAV_C, eta, pt) : 
	      ( flavor == 5 ? btagReaderMedium->eval_auto_bounds("down", BTagEntry_v2::FLAV_B, eta, pt) : btagReaderMedium->eval_auto_bounds("down", BTagEntry_v2::FLAV_UDSG, eta, pt) );

            if ( isBTagTight ) {
              btag_prob_MC *= eff_tight;
              if ( bTagSF==2 )
                btag_up_prob_DATA *= sf_up_tight * eff_tight;
              else if ( bTagSF==-2 )
                btag_dn_prob_DATA *= sf_dn_tight * eff_tight;
              else
                btag_prob_DATA *= sf_tight * eff_tight;
            }
            else if ( isBTagMedium ) {
              btag_prob_MC *= (eff_med - eff_tight);
              if ( bTagSF==2 )
                btag_up_prob_DATA *= (sf_up_med * eff_med - sf_up_tight * eff_tight);
              else if ( bTagSF==-2 )
                btag_dn_prob_DATA *= (sf_dn_med * eff_med - sf_dn_tight * eff_tight);
              else
                btag_prob_DATA *= (sf_med * eff_med - sf_tight * eff_tight);
            }
            else {
              btag_prob_MC *= (1 - eff_med);
              if ( bTagSF==2 )
                btag_up_prob_DATA *= (1 - sf_up_med * eff_med);
              else if ( bTagSF==-2 )
                btag_dn_prob_DATA *= (1 - sf_dn_med * eff_med);
              else
                btag_prob_DATA *= (1 - sf_med * eff_med);
            }
          }
        }
      }

      if (cand_bJets_tight.size()>=1) nbtagsel[0] = true;
      else nbtagsel[0] = false;
      if (doNbTagBins) {
        if ( doDYEnriched ) {
          if (cand_bJets.size() == 0) nbtagsel[1] = true;
          else nbtagsel[1] = false;
          if (cand_bJets_tight.size() == 1 && cand_bJets.size() == 1) nbtagsel[2] = true;
          else nbtagsel[2] = false;
          if (cand_bJets_tight.size() >= 1 && cand_bJets.size() >= 2) nbtagsel[3] = true;
          else nbtagsel[3] = false;
        }
        else {
          if (cand_bJets_tight.size() == 1 && cand_bJets.size() == 1) nbtagsel[1] = true;
          else nbtagsel[1] = false;
          if (cand_bJets_tight.size() >= 1 && cand_bJets.size() >= 2) nbtagsel[2] = true;
          else nbtagsel[2] = false;
        }
      }

      if ( doDYEnriched && cand_bJets.size()==0 ) {
          if (doHistos==2) {
          sel = "sel8";
          for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
            TString plot_name = plot_names[iplot];
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              unsigned int inb=1;
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                    histos[name]->Fill(variable[plot_name], weight * factor);
                }
              }
            }
          }
          for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
            TString plot2D_name = plot2D_names[iplot];
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              unsigned int inb=1;
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if (mllbinsel[imll] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                    histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
                }
              }
            }
          }
        }
      }

      if ( cand_bJets_tight.size() < 1 && !doDYEnriched ) continue;
      if ( cand_bJets_tight.size() > 0 && doOnlyDYEnriched ) continue;

      if ( isMC && bTagSF!=0 ) {
        if ( bTagSF==2 )
          weight *= ( btag_up_prob_DATA ==0 || btag_prob_MC == 0 ) ? 1.0 : btag_up_prob_DATA / btag_prob_MC;
        else if ( bTagSF==-2 )
          weight *= ( btag_dn_prob_DATA ==0 || btag_prob_MC == 0 ) ? 1.0 : btag_dn_prob_DATA / btag_prob_MC;
        else
          weight *= ( btag_prob_DATA ==0 || btag_prob_MC == 0 ) ? 1.0 : btag_prob_DATA / btag_prob_MC;
      }

      LorentzVector puppimet_p4 = LorentzVector(puppimet_pt,0.0,puppimet_phi,0.0);

      float jet1_pt = (cand_jets.size() > 0 ? Jet_p4.at(cand_jets[0]).Pt() : -1.0);
      float jet1_eta = (cand_bJets.size() > 0 ? Jet_p4.at(cand_jets[0]).eta() : -999.0);

      float st_scalar = (cand_jets.size() > 0 ? puppimet_pt + Muon_pt.at(cand_muons[0]) + Muon_pt.at(cand_muons[1]) + jet1_pt :
                                                puppimet_pt + Muon_pt.at(cand_muons[0]) + Muon_pt.at(cand_muons[1]));
      float st_scalar_jet = (cand_jets.size() > 0 ? puppimet_pt + Muon_pt.at(cand_muons[0]) + Muon_pt.at(cand_muons[1]) + jet1_pt : -1.0);
      float st_vector = (cand_jets.size() > 0 ? (puppimet_p4 + Muon_p4.at(cand_muons[0]) + Muon_p4.at(cand_muons[1]) + Jet_p4.at(cand_jets[0])).Pt() :
                                                (puppimet_p4 + Muon_p4.at(cand_muons[0]) + Muon_p4.at(cand_muons[1])).Pt());
      float st_vector_jet = (cand_jets.size() > 0 ? (puppimet_p4 + Muon_p4.at(cand_muons[0]) + Muon_p4.at(cand_muons[1]) + Jet_p4.at(cand_jets[0])).Pt() : -1.0);

      float bjet1_pt = (cand_bJets.size() > 0 ? Jet_p4.at(cand_bJets[0]).Pt() : -1.0);
      float bjet2_pt = (cand_bJets.size() > 1 ? Jet_p4.at(cand_bJets[1]).Pt() : -1.0);
      float bjet1_eta = (cand_bJets.size() > 0 ? Jet_p4.at(cand_bJets[0]).eta() : -999.0);
      float bjet2_eta = (cand_bJets.size() > 1 ? Jet_p4.at(cand_bJets[1]).eta() : -999.0);

      float st_scalar_bjet = (cand_bJets.size() > 0 ? puppimet_pt + Muon_pt.at(cand_muons[0]) + Muon_pt.at(cand_muons[1]) + bjet1_pt : -1.0);
      float st_vector_bjet = (cand_bJets.size() > 0 ? (puppimet_p4 + Muon_p4.at(cand_muons[0]) + Muon_p4.at(cand_muons[1]) + Jet_p4.at(cand_bJets[0])).Pt() : -1.0);

      // Construct mlb pairs from selected muon pair and candidate b jets
      float minDPhi_b_MET = 1e9, minDPhi_lb_MET = 1e9, minDPhi_llb_MET = 1e9, minDPhi_l_b = 1e9;
      float maxDPhi_b_MET = -1e9;
      float min_mlb = 1e9;
      float min_mbb = 1e9, max_mbb = -1e9;
      for ( int bjet = 0; bjet < cand_bJets.size(); bjet++ ) {
        auto bjet_p4 = Jet_p4.at(cand_bJets[bjet]);
        float m_mu1_b = (leadingMu_p4+bjet_p4).M();
        if ( m_mu1_b < min_mlb ) {
          min_mlb = m_mu1_b;
        }
        float m_mu2_b = (subleadingMu_p4+bjet_p4).M();
        if ( m_mu2_b < min_mlb ) {
          min_mlb = m_mu2_b;
        }

        float dPhi_b_MET = fabs(TVector2::Phi_mpi_pi(bjet_p4.Phi() - puppimet_phi));
        if ( !(usePuppiMET) )
	  dPhi_b_MET = fabs(TVector2::Phi_mpi_pi(bjet_p4.Phi() - pfmet_phi));
        if ( dPhi_b_MET < minDPhi_b_MET ) minDPhi_b_MET = dPhi_b_MET;
        if ( dPhi_b_MET > maxDPhi_b_MET ) maxDPhi_b_MET = dPhi_b_MET;

        float dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((leadingMu_p4 + bjet_p4).Phi() - puppimet_phi));
        if ( !(usePuppiMET) )
	  dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((leadingMu_p4 + bjet_p4).Phi() - pfmet_phi));
        if ( dPhi_lb_MET < minDPhi_lb_MET ) minDPhi_lb_MET = dPhi_lb_MET;
        dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((subleadingMu_p4 + bjet_p4).Phi() - puppimet_phi));
	if ( !(usePuppiMET) )
	  dPhi_lb_MET = fabs(TVector2::Phi_mpi_pi((subleadingMu_p4 + bjet_p4).Phi() - pfmet_phi));
        if ( dPhi_lb_MET < minDPhi_lb_MET ) minDPhi_lb_MET = dPhi_lb_MET;

        float dPhi_llb_MET = fabs(TVector2::Phi_mpi_pi((selectedPair_p4 + bjet_p4).Phi() - puppimet_phi));
	if ( !(usePuppiMET) )
	  dPhi_llb_MET = fabs(TVector2::Phi_mpi_pi((selectedPair_p4 + bjet_p4).Phi() - pfmet_phi));
        if ( dPhi_llb_MET < minDPhi_llb_MET ) minDPhi_llb_MET = dPhi_llb_MET;

        float dPhi_l_b = fabs(TVector2::Phi_mpi_pi(leadingMu_p4.Phi() - bjet_p4.Phi()));
        if ( dPhi_l_b < minDPhi_l_b ) minDPhi_l_b = dPhi_l_b;
        dPhi_l_b = fabs(TVector2::Phi_mpi_pi(subleadingMu_p4.Phi() - bjet_p4.Phi()));
        if ( dPhi_l_b < minDPhi_l_b ) minDPhi_l_b = dPhi_l_b;

	for ( int bbjet = bjet+1; bbjet < cand_bJets.size(); bbjet++) {
	  auto bbjet_p4 = Jet_p4.at(cand_bJets[bbjet]);
	  float mbb = (bjet_p4+bbjet_p4).M();
	  if ( mbb < min_mbb ) {
	    min_mbb = mbb;
	  }
	  if ( mbb > max_mbb ) {
	    max_mbb = mbb;
	  }
	}
      }

      // Add histos: sel8
      if (doHistos) {
        plot_names.push_back("nbtagDeepFlavB");
        variable.insert({"nbtagDeepFlavB", cand_bJets.size()});

        plot_names.push_back("jet1_pt");
        variable.insert({"jet1_pt", jet1_pt});

        plot_names.push_back("jet1_eta");
        variable.insert({"jet1_eta", jet1_eta});

        plot_names.push_back("st_scalar_jet");
        variable.insert({"st_scalar_jet", st_scalar_jet});

        plot_names.push_back("st_vector_jet");
        variable.insert({"st_vector_jet", st_vector_jet});

        plot2D_names.push_back("jet1_pt_VS_st_scalar_jet");
        variableX.insert({"jet1_pt_VS_st_scalar_jet", variable["jet1_pt"]});
        variableY.insert({"jet1_pt_VS_st_scalar_jet", st_scalar});

        plot2D_names.push_back("jet1_pt_VS_st_vector_jet");
        variableX.insert({"jet1_pt_VS_st_vector_jet", variable["jet1_pt"]});
        variableY.insert({"jet1_pt_VS_st_vector_jet", st_vector});

        if ( cand_bJets_tight.size() >= 1 ) {

          plot_names.push_back("bjet1_pt");
          variable.insert({"bjet1_pt", bjet1_pt});

          plot_names.push_back("bjet1_eta");
          variable.insert({"bjet1_eta", bjet1_eta});

          plot_names.push_back("min_mlb");
          variable.insert({"min_mlb", min_mlb});

          plot_names.push_back("minDPhi_b_MET");
          variable.insert({"minDPhi_b_MET", minDPhi_b_MET});

          plot_names.push_back("maxDPhi_b_MET");
          variable.insert({"maxDPhi_b_MET", maxDPhi_b_MET});

          plot_names.push_back("minDPhi_lb_MET");
          variable.insert({"minDPhi_lb_MET", minDPhi_lb_MET});

          plot_names.push_back("minDPhi_llb_MET");
          variable.insert({"minDPhi_llb_MET", minDPhi_llb_MET});

          plot_names.push_back("minDPhi_l_b");
          variable.insert({"minDPhi_l_b", minDPhi_l_b});

          plot_names.push_back("st_scalar_bjet");
          variable.insert({"st_scalar_bjet", st_scalar_bjet});

          plot_names.push_back("st_vector_bjet");
          variable.insert({"st_vector_bjet", st_vector_bjet});

          plot2D_names.push_back("bjet1_pt_VS_st_scalar_bjet");
          variableX.insert({"bjet1_pt_VS_st_scalar_bjet", variable["bjet1_pt"]});
          variableY.insert({"bjet1_pt_VS_st_scalar_bjet", variable["st_scalar_bjet"]});

          plot2D_names.push_back("bjet1_pt_VS_st_vector_bjet");
          variableX.insert({"bjet1_pt_VS_st_vector_bjet", variable["bjet1_pt"]});
          variableY.insert({"bjet1_pt_VS_st_vector_bjet", variable["st_vector_bjet"]});

          if ( cand_bJets.size() > 1 ) {

            plot_names.push_back("bjet2_pt");
            variable.insert({"bjet2_pt", bjet2_pt});

            plot_names.push_back("bjet2_eta");
            variable.insert({"bjet2_eta", bjet2_eta});

            plot_names.push_back("min_mbb");
            variable.insert({"min_mbb", min_mbb});

            plot_names.push_back("max_mbb");
            variable.insert({"max_mbb", max_mbb});
          }
        }
      }

      // Fill histos: sel8
      label = ">0 b-tag (Tight+Mediums WP)";
      slicedlabel = "";
      if ( cand_bJets_tight.size() >= 1 )
        h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              TString tlabel = slicedlabel + nbtagbinlabel[nbtag[inb]] + prodModelabel[iprodMode];
              if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow, weight * factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, tlabel);
            }
          }
        }
      }
      icutflow++;

      if (doHistos==2) {
        sel = "sel8";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                    histos[name]->Fill(variable[plot_name], weight * factor);
                }
              }
            }
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                    histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
                }
              }
            }
          }
        }
      }

      double met_pt = puppimet_pt;
      if ( !(usePuppiMET) ) met_pt = pfmet_pt;
      double maxdphiobjmet = 0.3;
      if ( met_pt > 250.0 &&
      	   ( (minDPhi_l_MET < maxdphiobjmet) ||
      	     (minDPhi_b_MET < maxdphiobjmet) ||
      	     (maxDPhi_l_MET > TMath::Pi()-maxdphiobjmet) ||
      	     (maxDPhi_b_MET > TMath::Pi()-maxdphiobjmet) ) ) continue;
      // Fill histos: sel9
      label = "E_{T}^{miss}<250 GeV (if aligned)";
      slicedlabel = label;
      if ( cand_bJets_tight.size() >= 1 )
        h_cutflow->Fill(icutflow,weight*factor);
      h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
      for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
        for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
          for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
            for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
              TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
              if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                slicedcutflows[slice]->Fill(icutflow, weight * factor);
              slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
            }
          }
        }
      }
      icutflow++;
      
      if (doHistos==2) {
        sel = "sel9";
        for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
          TString plot_name = plot_names[iplot];
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                    histos[name]->Fill(variable[plot_name], weight * factor);
                }
              }
            }
          }
        }
        for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
          TString plot2D_name = plot2D_names[iplot];
          for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
            for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
              for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                  TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                  if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                    histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
                }
              }
            }
          }
        }
      }

      if (min_mlb > 175.0) {
        // Fill histos: sel10
        label = "min m_{#mu b}>175 GeV";
        slicedlabel = label;
        if ( cand_bJets_tight.size() >= 1 )
          h_cutflow->Fill(icutflow,weight*factor);
        h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode]) {
                  slicedcutflows[slice]->Fill(icutflow, weight * factor);
                  if ( fillRooDataSet ) {
                    mfit.setVal(selectedPair_M);
                    roow.setVal(weight*factor);
                    roods[slice].add(RooArgSet(mfit,roow),roow.getVal());
                  }
                }
                slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
              }
            }
          }
        }
        icutflow++;

        if (doHistos) {
          sel = "sel10";
          for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
            TString plot_name = plot_names[iplot];
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
                for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                  for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                    TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                    if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                      histos[name]->Fill(variable[plot_name], weight * factor);
                  }
                }
              }
            }
          }
          for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
            TString plot2D_name = plot2D_names[iplot];
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
                for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                  for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                    TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                    if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                      histos2D[name]->Fill(variableX[plot2D_name],variableY[plot2D_name], weight * factor);
                  }
                }
              }
            }
          }
        }
      }
      if (min_mlb < 175.0 && doTTEnriched) {
        // Fill histos: antisel10
        label = "min m_{#mu b}<175 GeV";
        slicedlabel = label;
        if ( cand_bJets_tight.size() >= 1 )
          h_cutflow->Fill(icutflow,weight*factor);
        h_cutflow->GetXaxis()->SetBinLabel(icutflow+1,label);
        for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
          for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
            for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
              for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                TString slice = mllbin[imll] + TString("_") + nbtag[inb] + TString("_") + MuDetRegion[iMuDet] + prodMode[iprodMode];
                if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                  slicedcutflows[slice]->Fill(icutflow, weight * factor);
                slicedcutflows[slice]->GetXaxis()->SetBinLabel(icutflow + 1, slicedlabel);
              }
            }
          }
        }
        icutflow++;

        if (doHistos) {
          sel = "antisel10";
          for ( unsigned int iplot=0; iplot < plot_names.size(); iplot++ ) {
            TString plot_name = plot_names[iplot];
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
                for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                  for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                    TString name = plot_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                    if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                      histos[name]->Fill(variable[plot_name], weight * factor);
                  }
                }
              }
            }
          }
          for ( unsigned int iplot=0; iplot < plot2D_names.size(); iplot++ ) {
            TString plot2D_name = plot2D_names[iplot];
            for ( unsigned int imll=0; imll < mllbin.size(); imll++ ) {
              for ( unsigned int inb=0; inb < nbtag.size(); inb++ ) {
                for (unsigned int iMuDet = 0; iMuDet < MuDetRegion.size(); iMuDet++) {
                  for (unsigned int iprodMode = 0; iprodMode < prodMode.size(); iprodMode++) {
                    TString name = plot2D_name + "_" + sel + "_" + mllbin[imll] + "_" + nbtag[inb] + "_" + MuDetRegion[iMuDet] + prodMode[iprodMode];
                    if (mllbinsel[imll] && nbtagsel[inb] && MuDetRegionSel[iMuDet] && prodModesel[iprodMode])
                      histos2D[name]->Fill(variableX[plot2D_name], variableY[plot2D_name], weight * factor);
                  }
                }
              }
            }
          }
        }
      }

      if ( writeOutYields_AfterSel && min_mlb > 175.0 ) {
        if ( nbtagsel[1] ) {
          N1 += weight * factor;
          yN1++;
          if ( prodModesel[1] ) {
            N1ss += weight * factor;
            yN1ss++;
          }
          else if ( prodModesel[2] ) {
            N1bs += weight * factor;
            yN1bs++;
          }
          else {
            N1bb += weight * factor;
            yN1bb++;
          }
        }
        if ( nbtagsel[2] ) {
          N2 += weight * factor;
          yN2++;
          if ( prodModesel[1] ) {
            N2ss += weight * factor;
            yN2ss++;
          }
          else if ( prodModesel[2] ) {
            N2bs += weight * factor;
            yN2bs++;
          }
          else {
            N2bb += weight * factor;
            yN2bb++;
          }
        }
      }

    } // Event loop

    delete file;

  } // File loop
  bar.finish();

  if ( muonRecoSF!=0 ) reset_muonRecoSF();
  if ( muonIdSF!=0 ) reset_muonIDSF();
  if ( muonIsoSF!=0 ) reset_muonIsoSF();
  if ( triggerSF!=0 ) reset_triggerSF();
  if ( bTagSF!=0 ) reset_bTagEff();

  if ( removeDataDuplicates && !(isMC) )
    cout << "Number of duplicates found: " << nDuplicates << endl;

  //// Avoid histograms with unphysical negative bin content (due to negative GEN weights)
  //map<TString, TH1F*>::iterator it;
  //for ( it = histos.begin(); it != histos.end(); it++ ) {
  //  for ( unsigned int b=1; b<(it->second)->GetNbinsX()+1; b++ ) {
  //    if ( (it->second)->GetBinContent(b)<0.0) {
  //	(it->second)->SetBinContent(b,0.0);
  //	(it->second)->SetBinError(b,0.0);
  //    }
  //  }
  //}

  if ( writeOutYields_BeforeSel ) {
    TString model = ((TObjString *)process.Tokenize("_")->At(0))->String();
    yieldFile_BeforeSel << year;
    yieldFile_BeforeSel << "," << model;
    yieldFile_BeforeSel << "," << ((TObjString *)process.Tokenize("_")->At(1))->String().Strip(TString::kLeading,'M'); // M
    // Weighted yields
    yieldFile_BeforeSel << "," << to_string(NbbZ);
    yieldFile_BeforeSel << "," << to_string(NbsZ);
    yieldFile_BeforeSel << "," << to_string(NssZ);
    yieldFile_BeforeSel << "," << to_string(NbbZbb);
    yieldFile_BeforeSel << "," << to_string(NbsZbs);
    yieldFile_BeforeSel << "," << to_string(NssZss);
    // Raw yields
    yieldFile_BeforeSel << "," << to_string(yNbbZ);
    yieldFile_BeforeSel << "," << to_string(yNbsZ);
    yieldFile_BeforeSel << "," << to_string(yNssZ);
    yieldFile_BeforeSel << "," << to_string(yNbbZbb);
    yieldFile_BeforeSel << "," << to_string(yNbsZbs);
    yieldFile_BeforeSel << "," << to_string(yNssZss)<<endl;
    yieldFile_BeforeSel.close();
  }

  if ( writeOutYields_AfterSel ) {
    TString model = ((TObjString *)process.Tokenize("_")->At(0))->String();
    yieldFile_AfterSel << year;
    yieldFile_AfterSel << "," << model;
    yieldFile_AfterSel << "," << ( (model=="Y3" || model=="DY3") ? "0.14" : ( model=="DYp3" ? "0.08" : /*B3mL2*/ "0.05" ) ); // x = g/M
    yieldFile_AfterSel << "," << ( model=="Y3" ? "-0.15" : ( model=="DY3" ? "0.13" : ( model=="DYp3" ? "-0.18" : /*B3mL2*/ "0.1" ) ) ); // theta23
    yieldFile_AfterSel << "," << ((TObjString *)process.Tokenize("_")->At(1))->String().Strip(TString::kLeading,'M'); // M
    // Weighted yields
    yieldFile_AfterSel << "," << to_string(N1+N2); // N
    yieldFile_AfterSel << "," << to_string(N2/(N1+N2)); // f
    yieldFile_AfterSel << "," << to_string(N1);
    yieldFile_AfterSel << "," << to_string(N2);
    yieldFile_AfterSel << "," << to_string(N1bb);
    yieldFile_AfterSel << "," << to_string(N2bb);
    yieldFile_AfterSel << "," << to_string(N1bs);
    yieldFile_AfterSel << "," << to_string(N2bs);
    yieldFile_AfterSel << "," << to_string(N1ss);
    yieldFile_AfterSel << "," << to_string(N2ss);
    // Raw yields
    yieldFile_AfterSel << "," << to_string(yN1+yN2); // N
    yieldFile_AfterSel << "," << to_string(float(yN2)/(float(yN1)+float(yN2))); // f
    yieldFile_AfterSel << "," << to_string(yN1);
    yieldFile_AfterSel << "," << to_string(yN2);
    yieldFile_AfterSel << "," << to_string(yN1bb);
    yieldFile_AfterSel << "," << to_string(yN2bb);
    yieldFile_AfterSel << "," << to_string(yN1bs);
    yieldFile_AfterSel << "," << to_string(yN2bs);
    yieldFile_AfterSel << "," << to_string(yN1ss);
    yieldFile_AfterSel << "," << to_string(yN2ss)<<endl;
    yieldFile_AfterSel.close();
  }

  fout->Write();
  if ( fillRooDataSet ) {
    fout->cd();
    for (const auto& d : roods )
      d.second.Write();
  }
  fout->Close();

  return 0;
}
