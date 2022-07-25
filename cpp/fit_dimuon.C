#include "../CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
#include "RooCategory.h"
#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooHist.h"
#include "RooCurve.h"
#include "RooPlot.h"
#include "RooBinning.h"
#include "RooAddPdf.h"
#include "RooFFTConvPdf.h"
#include "RooGaussian.h"
#include "RooVoigtian.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooBernstein.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
#include "RooExtendPdf.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include "TSystem.h"

#include "Math/ProbFunc.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>

#include "../NanoCORE/Tools/widths.h"

using namespace std;
using namespace RooFit;

bool doBinnedFit = false;
bool categorizeSignal = false;
bool categorizeBackground = true;
bool useFixedSigma = false;
bool addBernsteinOrders = true;
bool saveFitResult = false;
bool drawFits = true;
bool drawResidual = false;

void fitmass(RooDataSet mmumuAll, TString sample, bool isData, bool isSignal, TString sigmodel, float mass, RooWorkspace &wfit, TString sigshape="dcbvoigt", const char* outDir = "fitResults")
{

  int mdir = mkdir(outDir,0755);

  double minmass = 175.0;
  double maxmass = 6500.0;
  double minMforFit = minmass;

  if ( isSignal ) {
    set_widths();

    double gamma = 0.001*mass;
    if ( widths[sigmodel].find(Form("%.0f",mass)) != widths[sigmodel].end() )
      gamma = widths[sigmodel][Form("%.0f",mass)];

    //////Set starting standard deviation (sigma)
    double stddev = 0.05*mass;
    double minstddev = 0.01*mass;
    double maxstddev = 0.25*mass;
    //
    double p0 = 8.53e-06;
    double p1 = 2.27e-02;
    double p2 = -2.22;
    TF1 *fstddev = new TF1("fstddev","[0]*x*x+[1]*x+[2]",minmass,maxmass);
    fstddev->SetParameter(0, p0);
    fstddev->SetParameter(1, p1);
    fstddev->SetParameter(2, p2);
    if ( !useFixedSigma ) {
      stddev = std::max(0.1, fstddev->Eval(mass));
      minstddev = 0.75*stddev;
      maxstddev = 1.25*stddev;
    }
    double binsize = 0.1*stddev;
    double binsizePlot = 1.0*stddev;

    //////Set starting alphaR
    double alphaR = 1.0;
    double minalphaR = 0.1;
    double maxalphaR = 10.0;
    //
    p0 = 2.58e-04;
    p1 = 6.89e-01;
    TF1 *falphaR = new TF1("falphaR","[0]*x+[1]",minmass,maxmass);
    falphaR->SetParameter(0, p0);
    falphaR->SetParameter(1, p1);
    if ( !useFixedSigma ) {
      alphaR = std::max(1.0e-3, falphaR->Eval(mass));
      minalphaR = 0.75*alphaR;
      maxalphaR = 1.25*alphaR;
    }
    //////Set starting alphaL
    double alphaL = -1.0;
    double minalphaL = -10.0;
    double maxalphaL = -0.1;
    //
    p0 = -6.42e-05;
    p1 = -1.20;
    TF1 *falphaL = new TF1("falphaL","[0]*x+[1]",minmass,maxmass);
    falphaL->SetParameter(0, p0);
    falphaL->SetParameter(1, p1);
    if ( !useFixedSigma ) {
      alphaL = std::min(-1.0e-3, falphaL->Eval(mass));
      minalphaL = 1.25*alphaL;
      maxalphaL = 0.75*alphaL;
    }

    //////Set starting nR
    double nR = 2.0;
    double minnR = 1.0;
    double maxnR = 5.0;
    //
    p0 = -8.94e-04;
    p1 = 3.21;
    TF1 *fnR = new TF1("fnR","[0]*x+[1]",minmass,maxmass);
    fnR->SetParameter(0, p0);
    fnR->SetParameter(1, p1);
    if ( !useFixedSigma ) {
      nR = std::max(1.0, fnR->Eval(mass));
      minnR = 0.75*nR;
      maxnR = 1.25*nR;
    }
    //////Set starting nL
    double nL = 6.0;
    double minnL = 1.0;
    double maxnL = 15.0;
    //
    p0 = 2.33e-03;
    p1 = 6.13;
    TF1 *fnL = new TF1("fnL","[0]*x+[1]",minmass,maxmass);
    fnL->SetParameter(0, p0);
    fnL->SetParameter(1, p1);
    if ( !useFixedSigma ) {
      nL = std::max(1.0, fnL->Eval(mass));
      minnL = 0.75*nL;
      maxnL = 1.25*nL;
    }

    //////Set starting fracR
    double fracR = 1.0/3;
    double minfracR = 0.0;
    double maxfracR = 1.0;
    //
    p0 = -9.54e-05;
    p1 = 2.19e-01;
    TF1 *ffracR = new TF1("ffracR","[0]*x+[1]",minmass,maxmass);
    ffracR->SetParameter(0, p0);
    ffracR->SetParameter(1, p1);
    if ( !useFixedSigma ) {
      fracR = std::max(1.0e-03, ffracR->Eval(mass));
      minfracR = 0.75*fracR;
      maxfracR = 1.25*fracR;
    }
    //////Set starting fracL
    double fracL = 6.0;
    double minfracL = 1.0;
    double maxfracL = 15.0;
    //
    p0 = 4.12e-05;
    p1 = 5.44e-01;
    TF1 *ffracL = new TF1("ffracL","[0]*x+[1]",minmass,maxmass);
    ffracL->SetParameter(0, p0);
    ffracL->SetParameter(1, p1);
    if ( !useFixedSigma ) {
      fracL = std::max(1.0e-03, ffracL->Eval(mass));
      minfracL = 0.75*fracL;
      maxfracL = 1.25*fracL;
    }

    TString fitRange = Form("%f < mfit && mfit < %f",std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);

    //////Get RooRealVar from RooDataSet
    RooRealVar mfit("mfit", "mfit", std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    std::unique_ptr<RooDataSet> mmumu{static_cast<RooDataSet*>(mmumuAll.reduce(RooArgSet(mfit),fitRange))};
    (*mmumu).Print();
    RooRealVar x = *((RooRealVar*) (*mmumu).get()->find("mfit"));
    x.Print();
    x.setRange("fitRange",std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    int nBins = (mass+10.0*stddev - std::max(minMforFit,mass-10.0*stddev))/binsize;
    int nBinsPlot = (mass+10.0*stddev - std::max(minMforFit,mass-10.0*stddev))/(0.5*binsizePlot);
    if ( doBinnedFit )
      x.setBins(nBins);
    RooBinning binningPlot(nBinsPlot,std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);

    RooPlot *frame = x.frame(std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    frame->SetTitle("");//Signal dimuon mass fit");
    frame->SetMinimum(0.0);
    //////Plot RooDataSet onto frame
    //(*mmumu).plotOn(frame/*, DataError(RooAbsData::SumW2)*/);
    (*mmumu).plotOn(frame, DataError(RooAbsData::SumW2), Binning(binningPlot));

    //////Define fit-related variables
    int nMaxFitAttempts = 5;
    int nFitParams = 0;
    RooFitResult *r = new RooFitResult();

    //////Define index over event categories
    ////// binidx=0: nB>0
    ////// binidx=1: nB=1
    ////// binidx=2: nB>1    
    int binidx=-1;
    TString datasetname((*mmumu).GetName());
    if ( datasetname.Contains("nBTag1p") ) binidx=0;
    else if ( datasetname.Contains("nBTag1") ) binidx=1;
    else if ( datasetname.Contains("nBTag2p") ) binidx=2;
    TString catExt = "";
    if ( categorizeSignal ) 
      catExt = Form("_ch%d",binidx);
    mmumu->SetName(Form("signalRooDataSet%s",catExt.Data()));
    wfit.import(*(mmumu));
    double sigNormalization = (*mmumu).sumEntries(fitRange.Data());
    RooRealVar nSig(Form("signalNorm%s",catExt.Data()),Form("signalNorm%s",catExt.Data()),sigNormalization);
    wfit.import(nSig);

    if (sigshape=="gaus"){
      RooRealVar mean(Form("mean%s",catExt.Data()),Form("mean%s",catExt.Data()),mass,mass-stddev,mass+stddev);
      RooRealVar sigma(Form("sigma%s",catExt.Data()),Form("sigma%s",catExt.Data()),stddev,minstddev,maxstddev);
      RooGaussian signal(Form("signal%s",catExt.Data()),Form("signal%s",catExt.Data()),x,mean,sigma);
      nFitParams = 2;
      //////Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	//r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), /*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"),Range("fitRange"),RooFit::NormRange("fitRange"));
      //////Import model and all its components into the workspace      
      mean.removeError();
      sigma.removeError();
      wfit.import(signal);
    }
    else if (sigshape=="voigt"){
      RooRealVar mean(Form("mean%s",catExt.Data()),Form("mean%s",catExt.Data()),mass,mass-stddev,mass+stddev);
      //RooRealVar width(Form("width%s",catExt.Data()),Form("width%s",catExt.Data()),gamma,0.75*gamma,1.25*gamma);
      RooRealVar width(Form("width%s",catExt.Data()),Form("width%s",catExt.Data()),gamma);
      RooRealVar sigma(Form("sigma%s",catExt.Data()),Form("sigma%s",catExt.Data()),stddev,minstddev,maxstddev);
      RooVoigtian signal(Form("signal%s",catExt.Data()),Form("signal%s",catExt.Data()),x,mean,width,sigma);
      //nFitParams = 3;
      nFitParams = 2;
      //////Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	//r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), /*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"),Range("fitRange"),RooFit::NormRange("fitRange"));
      //////Import model and all its components into the workspace
      mean.removeError();
      width.removeError();
      sigma.removeError();
      wfit.import(signal);
    }
    else if (sigshape=="dcb"){
      RooRealVar mean(Form("mean%s",catExt.Data()),Form("mean%s",catExt.Data()),mass,mass-stddev,mass+stddev);
      RooRealVar sigma(Form("sigma%s",catExt.Data()),Form("sigma%s",catExt.Data()),stddev,minstddev,maxstddev);
      RooRealVar alpha_1(Form("alphaR%s",catExt.Data()),Form("alphaR%s",catExt.Data()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL%s",catExt.Data()),Form("alphaL%s",catExt.Data()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR%s",catExt.Data()),Form("nR%s",catExt.Data()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL%s",catExt.Data()),Form("nL%s",catExt.Data()), nL, minnL, maxnL);
      RooCBShape cb_1(Form("CBR%s",catExt.Data()),Form("CBR%s",catExt.Data()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL%s",catExt.Data()),Form("CBL%s",catExt.Data()), x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac(Form("mcfrac%s",catExt.Data()),Form("mcfrac%s",catExt.Data()), 0.5, 0.0, 1.0);
      RooAddPdf signal(Form("signal%s",catExt.Data()),Form("signal%s",catExt.Data()), RooArgList(cb_1,cb_2), RooArgList(mc_frac), true);
      nFitParams = 7;
      //////Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	//r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), /*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"),Range("fitRange"),RooFit::NormRange("fitRange"));
      //////Import model and all its components into the workspace
      mean.removeError();
      sigma.removeError();
      alpha_1.removeError();
      alpha_2.removeError();
      n_1.removeError();
      n_2.removeError();
      mc_frac.removeError();
      wfit.import(signal);
    }
    else if (sigshape=="dcbg"){
      RooRealVar mean(Form("mean%s",catExt.Data()),Form("mean%s",catExt.Data()),mass,mass-stddev,mass+stddev);
      RooRealVar sigma(Form("sigma%s",catExt.Data()),Form("sigma%s",catExt.Data()),stddev,minstddev,maxstddev);
      RooGaussian gaus(Form("gauss%s",catExt.Data()),Form("gauss%s",catExt.Data()),x,mean,sigma);
      RooRealVar alpha_1(Form("alphaR%s",catExt.Data()),Form("alphaR%s",catExt.Data()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL%s",catExt.Data()),Form("alphaL%s",catExt.Data()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR%s",catExt.Data()),Form("nR%s",catExt.Data()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL%s",catExt.Data()),Form("nL%s",catExt.Data()), nL, minnL, maxnL);
      //RooCrystalBall cb_1(Form("CBR%s",catExt.Data()),Form("CBR%s",catExt.Data()), x, mean, sigma, alpha_1, n_1);
      //RooCrystalBall cb_2(Form("CBL%s",catExt.Data()),Form("CBL%s",catExt.Data()), x, mean, sigma, alpha_2, n_2);
      RooCBShape cb_1(Form("CBR%s",catExt.Data()),Form("CBR%s",catExt.Data()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL%s",catExt.Data()),Form("CBL%s",catExt.Data()), x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac_1(Form("mcfracR%s",catExt.Data()),Form("mcfracR%s",catExt.Data()), fracR, minfracR, maxfracR);
      RooRealVar mc_frac_2(Form("mcfracL%s",catExt.Data()),Form("mcfracL%s",catExt.Data()), fracL, minfracL, maxfracL);
      RooAddPdf signal(Form("signal%s",catExt.Data()),Form("signal%s",catExt.Data()), RooArgList(gaus,cb_1,cb_2), RooArgList(mc_frac_1,mc_frac_2), true);
      nFitParams = 8;
      //////Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	//r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), /*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"),Range("fitRange"),RooFit::NormRange("fitRange"));
      //////Import model and all its components into the workspace
      mean.removeError();
      sigma.removeError();
      alpha_1.removeError();
      alpha_2.removeError();
      n_1.removeError();
      n_2.removeError();
      mc_frac_1.removeError();
      mc_frac_2.removeError();
      wfit.import(signal);
    }
    else if (sigshape=="dcbxvoigt"){
      RooRealVar mean(Form("mean%s",catExt.Data()),Form("mean%s",catExt.Data()),mass,mass-stddev,mass+stddev);
      //RooRealVar width(Form("width%s",catExt.Data()),Form("width%s",catExt.Data()),gamma,0.75*gamma,1.25*gamma);
      RooRealVar width(Form("width%s",catExt.Data()),Form("width%s",catExt.Data()),gamma);
      RooRealVar sigma(Form("sigma%s",catExt.Data()),Form("sigma%s",catExt.Data()),stddev,minstddev,maxstddev);
      RooVoigtian voigt(Form("voigt%s",catExt.Data()),Form("voigt%s",catExt.Data()),x,mean,width,sigma);
      RooRealVar alpha_1(Form("alphaR%s",catExt.Data()),Form("alphaR%s",catExt.Data()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL%s",catExt.Data()),Form("alphaL%s",catExt.Data()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR%s",catExt.Data()),Form("nR%s",catExt.Data()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL%s",catExt.Data()),Form("nL%s",catExt.Data()), nL, minnL, maxnL);
      RooCBShape cb_1(Form("CBR%s",catExt.Data()),Form("CBR%s",catExt.Data()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL%s",catExt.Data()),Form("CBL%s",catExt.Data()), x, mean, sigma, alpha_2, n_2);
      RooFFTConvPdf cb1voigt(Form("CBRVoigt%s",catExt.Data()),Form("CBRVoigt%s",catExt.Data()), x, cb_1, voigt);
      RooFFTConvPdf cb2voigt(Form("CBLVoigt%s",catExt.Data()),Form("CBLVoigt%s",catExt.Data()), x, cb_2, voigt);
      RooRealVar mc_frac(Form("mcfrac%s",catExt.Data()),Form("mcfrac%s",catExt.Data()), 0.5, 0.0, 1.0);
      RooAddPdf signal(Form("signal%s",catExt.Data()),Form("signal%s",catExt.Data()), RooArgList(cb1voigt,cb2voigt), RooArgList(mc_frac), true);
      //nFitParams = 8;
      nFitParams = 7;
      //////Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	//r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), /*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"),Range("fitRange"),RooFit::NormRange("fitRange"));
      //////Import model and all its components into the workspace
      mean.removeError();
      width.removeError();
      sigma.removeError();
      alpha_1.removeError();
      alpha_2.removeError();
      n_1.removeError();
      n_2.removeError();
      mc_frac.removeError();
      wfit.import(signal);
    }
    else if (sigshape=="dcbvoigt"){
      RooRealVar mean(Form("mean%s",catExt.Data()),Form("mean%s",catExt.Data()),mass,mass-stddev,mass+stddev);
      //RooRealVar width(Form("width%s",catExt.Data()),Form("width%s",catExt.Data()),gamma,0.75*gamma,1.25*gamma);
      RooRealVar width(Form("width%s",catExt.Data()),Form("width%s",catExt.Data()),gamma);
      RooRealVar sigma(Form("sigma%s",catExt.Data()),Form("sigma%s",catExt.Data()),stddev,minstddev,maxstddev);
      RooVoigtian voigt(Form("voigt%s",catExt.Data()),Form("voigt%s",catExt.Data()),x,mean,width,sigma);
      RooRealVar alpha_1(Form("alphaR%s",catExt.Data()),Form("alphaR%s",catExt.Data()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL%s",catExt.Data()),Form("alphaL%s",catExt.Data()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR%s",catExt.Data()),Form("nR%s",catExt.Data()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL%s",catExt.Data()),Form("nL%s",catExt.Data()), nL, minnL, maxnL);
      RooCBShape cb_1(Form("CBR%s",catExt.Data()),Form("CBR%s",catExt.Data()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL%s",catExt.Data()),Form("CBL%s",catExt.Data()), x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac_1(Form("mcfracR%s",catExt.Data()),Form("mcfracR%s",catExt.Data()), fracR, minfracR, maxfracR);
      RooRealVar mc_frac_2(Form("mcfracL%s",catExt.Data()),Form("mcfracL%s",catExt.Data()), fracL, minfracL, maxfracL);
      RooAddPdf signal(Form("signal%s",catExt.Data()),Form("signal%s",catExt.Data()), RooArgList(voigt,cb_1,cb_2), RooArgList(mc_frac_1,mc_frac_2), true);
      //nFitParams = 9;
      nFitParams = 8;
      //////Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	//r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), /*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	r = signal.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"),Range("fitRange"),RooFit::NormRange("fitRange"));
      //////Import model and all its components into the workspace
      mean.removeError();
      width.removeError();
      sigma.removeError();
      alpha_1.removeError();
      alpha_2.removeError();
      n_1.removeError();
      n_2.removeError();
      mc_frac_1.removeError();
      mc_frac_2.removeError();
      wfit.import(signal);
    }
    else{
      cout << "Signal PDF is unknown. Exiting..." << endl;
      return;
    }

    double chi2 = 0.0;
    int nEmptyBins = 0;
    //////Construct histograms with residuals and pulls of the data w.r.t. the curve
    RooHist *hresid = frame->residHist();
    RooHist *hpull = frame->pullHist();
    RooCurve *fitcurve = frame->getCurve("signal");
    //////Determine range of curve 
    Double_t xstart,xstop,y;
    fitcurve->GetPoint(0,xstart,y);
    fitcurve->GetPoint(fitcurve->GetN()-1,xstop,y);
    int nPoints = hresid->GetN();
    for (int i = 0; i < nPoints; i++) {
      double b, point;
      hpull->GetPoint(i,b,point);
      if (b<xstart || b>xstop) continue;
      if (point==0) {
	++nEmptyBins;
      }
      else {
	hresid->GetPoint(i,b,point);
	chi2 += point*point / (fitcurve->interpolate(b));
      }
    }
    //////Access fit result information
    //r->Print();
    //////Access basic information
    cout << "Status = " << r->status() << endl;
    cout << "EDM = " << r->edm() << endl;
    cout << "-log(L) at minimum = " << r->minNll() << endl;
    //////Access list of final fit parameter values
    cout << "Final value of floating parameters:" << endl;
    r->floatParsFinal().Print("s");
    //////Evaluate chi-square:
    cout << "chiSquare = " << frame->chiSquare(nFitParams) << endl;
    cout << "chiSquare (from residual histogram) / NDOF = " << chi2 << " / " << std::max(nFitParams,nPoints-nEmptyBins-nFitParams) << endl;
    cout << "p-value (chiSquare, NDOF) = " << ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams))) << endl;

    if ( drawFits ) {
      //////Draw fit
      TCanvas *can = new TCanvas("can","",600,600);
      can->cd();
      frame->SetMinimum(0.0);
      frame->SetLabelSize(0.02,"Y");
      frame->SetTitleSize(0.025,"Y");
      frame->SetXTitle("Dimuon mass [GeV]");
      frame->Draw();
      can->SaveAs(Form("%s/%s_fitSignal_%s.png",outDir,(*mmumu).GetName(),sigshape.Data()));
      can->Update();
      can->Clear();
      can->Close();
    }

    if ( drawResidual ) {
      //Create a dedicated frame to draw the residual distribution and add the distribution to the frame
      RooPlot *frameres = x.frame(Title("Residual Distribution"));
      frameres->addPlotable(hresid, "P");
      frameres->SetXTitle("Dimuon mass [GeV]");
      TCanvas *can = new TCanvas("can","",600,600);
      can->cd();
      frameres->Draw();
      can->SaveAs(Form("%s/%s_fitResidual_%s.png",outDir,(*mmumu).GetName(),sigshape.Data()));
      can->Update();
      can->Clear();

      //Create a dedicated frame to draw the pull distribution and add the distribution to the frame
      RooPlot *framepull = x.frame(Title("Pull Distribution"));
      framepull->addPlotable(hpull, "P");
      framepull->SetXTitle("Dimuon mass [GeV]");
      can->cd();
      framepull->Draw();
      can->SaveAs(Form("%s/%s_fitPull_%s.png",outDir,(*mmumu).GetName(),sigshape.Data()));
      can->Update();
      can->Clear();
      can->Close();
    }

    if ( saveFitResult ) {
      //////Save RooFitResult into a ROOT file
      TFile ffitresult(Form("%s/%s_fitResult_%s.root",outDir,(*mmumu).GetName(),sigshape.Data()),"RECREATE");
      r->Write("fitResult");
      ffitresult.Close();
    }

    reset_widths();

  }
  else {

    //////Set starting standard deviation (sigma)
    double stddev = 0.05*mass;
    double minstddev = 0.01*mass;
    double maxstddev = 0.25*mass;
    //
    double p0 = 8.53e-06;
    double p1 = 2.27e-02;
    double p2 = -2.22;
    TF1 *fstddev = new TF1("fstddev","[0]*x*x+[1]*x+[2]",minmass,maxmass);
    fstddev->SetParameter(0, p0);
    fstddev->SetParameter(1, p1);
    fstddev->SetParameter(2, p2);
    if ( !useFixedSigma ) {
      stddev = std::max(0.1, fstddev->Eval(mass));
      minstddev = 0.75*stddev;
      maxstddev = 1.25*stddev;
    }
    double binsize = 0.1*stddev;
    double binsizePlot = 1.0*stddev;

    //////Get RooRealVar from RooDataSet
    TString fitRange = Form("%f < mfit && mfit < %f",std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    //////Get RooRealVar from RooDataSet
    RooRealVar mfit("mfit", "mfit", std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    RooRealVar roow("roow", "roow", 0.0, 100.0);
    std::unique_ptr<RooDataSet> mmumu{static_cast<RooDataSet*>(mmumuAll.reduce(RooArgSet(mfit,roow),fitRange))};
    RooRealVar x = *((RooRealVar*) (*mmumu).get()->find("mfit"));
    x.setRange("fitRange",std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    int nBins = (mass+10.0*stddev - std::max(minMforFit,mass-10.0*stddev))/binsize;
    int nBinsPlot = (mass+10.0*stddev - std::max(minMforFit,mass-10.0*stddev))/binsizePlot;
    if ( doBinnedFit )
      x.setBins(nBins);
    RooBinning binningPlot(nBinsPlot,std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);

    RooDataSet *mmumuFit;
    double bgNormalizationForToy = (*mmumu).sumEntries(fitRange.Data());
    RooRealVar nBGForToy(Form("bgNormalizationForToy_%s_%.0f",(*mmumu).GetName(),mass),Form("bgNormalizationForToy_%s_%.0f",(*mmumu).GetName(),mass),bgNormalizationForToy);
    //////If using MC, fit RooDataSet with exponential PDF, then build MC toy dataset
    if ( !isData ) {
      //////Exponential PDF
      RooRealVar expo_slope_forToy(Form("expo_slope_forToy_%s_mass%.0f",(*mmumu).GetName(),mass),Form("expo_slope_forToy_%s_mass%.0f",(*mmumu).GetName(),mass),-0.02,-0.1,-0.0001);
      RooExponential exponential_forToy(Form("background_exponential_forToy_%s_mass%.0f",(*mmumu).GetName(),mass),Form("background_exponential_forToy_%s_mass%.0f",(*mmumu).GetName(),mass),x,expo_slope_forToy);
      RooExtendPdf exponential_toyMC(Form("background_exponential_forToy_%s_mass%.0f",(*mmumu).GetName(),mass),Form("background_exponential_forToy_%s_mass%.0f",(*mmumu).GetName(),mass),exponential_forToy,nBGForToy,fitRange.Data());
      RooFitResult* r_forToy = exponential_toyMC.fitTo((*mmumu), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
      TString thisname = (*mmumu).GetName();
      RooDataSet mmumuTOY = *(exponential_toyMC.generate(RooArgSet(x)));
      mmumuFit = (RooDataSet*) mmumuTOY.Clone((*mmumu).GetName());
    }
    else {
      mmumuFit = (RooDataSet*) (*mmumu).Clone((*mmumu).GetName());
    }

    RooPlot *frame = x.frame(std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    frame->SetTitle("");//BG dimuon mass fit");
    frame->SetMinimum(0.0);

    //////Plot RooDataSet onto frame
    (*mmumuFit).plotOn(frame/*, DataError(RooAbsData::SumW2)*/, Binning(binningPlot));

    //////Define index over event categories
    ////// binidx=0: nB>0
    ////// binidx=1: nB=1
    ////// binidx=2: nB>1    
    int binidx=-1;
    TString datasetname((*mmumuFit).GetName());
    if ( datasetname.Contains("nBTag1p") ) binidx=0;
    else if ( datasetname.Contains("nBTag1") ) binidx=1;
    else if ( datasetname.Contains("nBTag2p") ) binidx=2;
    TString catExt = "";
    if ( categorizeBackground ) 
      catExt = Form("_ch%d",binidx);

    //////Define fit-related variables
    int nMaxFitAttempts = 5;
    int nFitParams = 0;
    RooFitResult *r = new RooFitResult();

    (*mmumuFit).Print();
    mmumuFit->SetName(Form("data_obs%s",catExt.Data()));
    wfit.import(*(mmumuFit));

    double bgNormalization = (*mmumuFit).sumEntries(fitRange.Data());
    RooRealVar nBG(Form("roomultipdf%s_norm",catExt.Data()),Form("roomultipdf%s_norm",catExt.Data()),bgNormalization,0.0,10.0*bgNormalization);
    if ( bgNormalization < 0.001 ) {
      nBG.setVal(0.0001);
      nBG.setRange(0.0,0.001);
    }
    wfit.import(nBG);

    //////Exponential PDF
    RooRealVar expo_slope(Form("expo_slope%s",catExt.Data()),Form("expo_slope%s",catExt.Data()),-0.02,-0.1,-0.0001);
    RooExponential exponential(Form("background_exponential%s",catExt.Data()),Form("background_exponential%s",catExt.Data()),x,expo_slope);
    //////Fit
    int nFits = 0;
    while ( nFits < nMaxFitAttempts ) {
      r = exponential.fitTo((*mmumuFit), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"),/*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
      ++nFits;
      if ( r->status()==0 )
	break;
    }
    exponential.plotOn(frame,Name("background_exponential"),Range("fitRange"),RooFit::NormRange("fitRange"));

    double chi2 = 0.0;
    int nEmptyBins = 0;
    //////Construct histograms with residuals and pulls of the data w.r.t. the curve
    RooHist *hresid = frame->residHist();
    RooHist *hpull = frame->pullHist();
    RooCurve *fitcurve = frame->getCurve("background_exponential");
    //////Determine range of curve 
    Double_t xstart,xstop,y;
    fitcurve->GetPoint(0,xstart,y);
    fitcurve->GetPoint(fitcurve->GetN()-1,xstop,y);
    int nPoints = hresid->GetN();
    for (int i = 0; i < nPoints; i++) {
      double b, point;
      hpull->GetPoint(i,b,point);
      if (b<xstart || b>xstop) continue;
      if (point==0) {
	++nEmptyBins;
      }
      else {
	hresid->GetPoint(i,b,point);
	chi2 += point*point / (fitcurve->interpolate(b));
      }
    }
    //////Access fit result information
    //r->Print();
    //////Access basic information
    cout << "Status = " << r->status() << endl;
    cout << "EDM = " << r->edm() << endl;
    cout << "-log(L) at minimum = " << r->minNll() << endl;
    //////Access list of final fit parameter values
    cout << "Final value of floating parameters:" << endl;
    r->floatParsFinal().Print("s");
    //////Evaluate chi-square:
    cout << "chiSquare = " << frame->chiSquare(nFitParams) << endl;
    cout << "chiSquare (from residual histogram) / NDOF = " << chi2 << " / " << std::max(nFitParams,nPoints-nEmptyBins-nFitParams) << endl;
    cout << "p-value (chiSquare, NDOF) = " << ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams))) << endl;

    if ( saveFitResult ) {
      //////Save RooFitResult into a ROOT file
      TFile ffitresult(Form("%s/%s_fitResult_exponential_mass%.0f.root",outDir,(*mmumuFit).GetName(),mass),"RECREATE");
      r->Write("fitResult");
      ffitresult.Close();
    }

    RooCategory cat(Form("pdf_index%s",catExt.Data()),Form("pdf_index%s",catExt.Data()));
    wfit.import(cat);
    RooArgList bgPDFs;

    //////Select PDFs
    //////Chi2-based p-value
    int fitStatusExponential = r->status();
    double chi2ExponentialPvalue = ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams)));

    frame->remove("background_exponential");

    if ( chi2ExponentialPvalue > 0.01 &&
	 //chi2ExponentialPvalue < 0.99 &&
	 fitStatusExponential==0 ) {
      bgPDFs.add(exponential);

      exponential.plotOn(frame,Name("background_exponential"),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kRed));
      if ( drawFits ) {
	//////Draw fit
	TCanvas *can = new TCanvas("can","",600,600);
	can->cd();
	frame->SetMinimum(0.0);
	frame->SetLabelSize(0.02,"Y");
	frame->SetTitleSize(0.025,"Y");
	frame->SetXTitle("Dimuon mass [GeV]");
	frame->Draw();
	can->SaveAs(Form("%s/%s_fitBackground_exponential_mass%.0f.png",outDir,(*mmumuFit).GetName(),mass));
	can->Update();
	can->Clear();
	can->Close();
      }
      if ( drawResidual ) {
	//Create a dedicated frame to draw the residual distribution and add the distribution to the frame
	RooHist *hresid = frame->residHist();
	RooPlot *frameres = x.frame(Title("Residual Distribution"));
	frameres->addPlotable(hresid, "P");
	frameres->SetXTitle("Dimuon mass [GeV]");
	TCanvas *can = new TCanvas("can","",600,600);
	can->cd();
	frameres->Draw();
	can->SaveAs(Form("%s/%s_fitResidual_exponential_mass%.0f.png",outDir,(*mmumuFit).GetName(),mass));
	can->Update();
	can->Clear();
	
	//Create a dedicated frame to draw the pull distribution and add the distribution to the frame
	RooHist *hpull = frame->pullHist();
	RooPlot *framepull = x.frame(Title("Pull Distribution"));
	framepull->addPlotable(hpull, "P");
	framepull->SetXTitle("Dimuon mass [GeV]");
	can->cd();
	framepull->Draw();
	can->SaveAs(Form("%s/%s_fitPull_exponential_mass%.0f.png",outDir,(*mmumuFit).GetName(),mass));
	can->Update();
	can->Clear();
	can->Close();
      }
      frame->remove("background_exponential");
    }

    //////Power-law PDF
    RooRealVar plaw_power(Form("plaw_power%s",catExt.Data()),Form("plaw_power%s",catExt.Data()),-3.0,-6.0,-0.0001);
    RooGenericPdf powerlaw(Form("background_powerlaw%s",catExt.Data()),"TMath::Power(@0,@1)",RooArgList(x,plaw_power));
    //////Fit
    nFits = 0;
    while ( nFits < nMaxFitAttempts ) {
      r = powerlaw.fitTo((*mmumuFit), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"),/*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
      ++nFits;
      if ( r->status()==0 )
	break;
    }
    powerlaw.plotOn(frame,Name("background_powerlaw"),Range("fitRange"),RooFit::NormRange("fitRange"));

    chi2 = 0.0;
    nEmptyBins = 0;
    //////Construct histograms with residuals and pulls of the data w.r.t. the curve
    hresid = frame->residHist();
    hpull = frame->pullHist();
    fitcurve = frame->getCurve("background_powerlaw");
    //////Determine range of curve 
    fitcurve->GetPoint(0,xstart,y);
    fitcurve->GetPoint(fitcurve->GetN()-1,xstop,y);
    nPoints = hresid->GetN();
    for (int i = 0; i < nPoints; i++) {
      double b, point;
      hpull->GetPoint(i,b,point);
      if (b<xstart || b>xstop) continue;
      if (point==0) {
	++nEmptyBins;
      }
      else {
	hresid->GetPoint(i,b,point);
	chi2 += point*point / (fitcurve->interpolate(b));
      }
    }
    //////Access fit result information
    //r->Print();
    //////Access basic information
    cout << "Status = " << r->status() << endl;
    cout << "EDM = " << r->edm() << endl;
    cout << "-log(L) at minimum = " << r->minNll() << endl;
    //////Access list of final fit parameter values
    cout << "Final value of floating parameters:" << endl;
    r->floatParsFinal().Print("s");
    //////Evaluate chi-square:
    cout << "chiSquare = " << frame->chiSquare(nFitParams) << endl;
    cout << "chiSquare (from residual histogram) / NDOF = " << chi2 << " / " << std::max(nFitParams,nPoints-nEmptyBins-nFitParams) << endl;
    cout << "p-value (chiSquare, NDOF) = " << ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams))) << endl;

    if ( saveFitResult ) {
      //////Save RooFitResult into a ROOT file
      TFile ffitresult(Form("%s/%s_fitResult_powerlaw_mass%.0f.root",outDir,(*mmumuFit).GetName(),mass),"RECREATE");
      r->Write("fitResult");
      ffitresult.Close();
    }

    //////Select PDFs
    //////Chi2-based p-value
    int fitStatusPowerlaw = r->status();
    double chi2PowerlawPvalue = ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams)));

    frame->remove("background_powerlaw");

    if ( chi2PowerlawPvalue > 0.01 &&
	 //chi2PowerlawPvalue < 0.99 &&
	 fitStatusPowerlaw==0 ) {
      bgPDFs.add(powerlaw);

      powerlaw.plotOn(frame,Name("background_powerlaw"),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kRed));
      if ( drawFits ) {
	//////Draw fit
	TCanvas *can = new TCanvas("can","",600,600);
	can->cd();
	frame->SetMinimum(0.0);
	frame->SetLabelSize(0.02,"Y");
	frame->SetTitleSize(0.025,"Y");
	frame->SetXTitle("Dimuon mass [GeV]");
	frame->Draw();
	can->SaveAs(Form("%s/%s_fitBackground_powerlaw_mass%.0f.png",outDir,(*mmumuFit).GetName(),mass));
	can->Update();
	can->Clear();
	can->Close();
      }
      if ( drawResidual ) {
	//Create a dedicated frame to draw the residual distribution and add the distribution to the frame
	RooHist *hresid = frame->residHist();
	RooPlot *frameres = x.frame(Title("Residual Distribution"));
	frameres->addPlotable(hresid, "P");
	frameres->SetXTitle("Dimuon mass [GeV]");
	TCanvas *can = new TCanvas("can","",600,600);
	can->cd();
	frameres->Draw();
	can->SaveAs(Form("%s/%s_fitResidual_powerlaw_mass%.0f.png",outDir,(*mmumuFit).GetName(),mass));
	can->Update();
	can->Clear();
	
	//Create a dedicated frame to draw the pull distribution and add the distribution to the frame
	RooHist *hpull = frame->pullHist();
	RooPlot *framepull = x.frame(Title("Pull Distribution"));
	framepull->addPlotable(hpull, "P");
	framepull->SetXTitle("Dimuon mass [GeV]");
	can->cd();
	framepull->Draw();
	can->SaveAs(Form("%s/%s_fitPull_powerlaw_mass%.0f.png",outDir,(*mmumuFit).GetName(),mass));
	can->Update();
	can->Clear();
	can->Close();
      }
      frame->remove("background_powerlaw");
    }

    //////Bernstein polynomials
    int maxpolyorder = 6;
    int lastnll = 0;
    int bestBernsteinOrder = -1;
    vector<RooArgList> parListBernstein;
    RooArgList bgBernsteinPDFs;
    vector<double> chi2BernsteinPvalue;
    vector<RooFitResult> fitResultBernstein;
    vector<int> fitStatusBernstein;
    for (int to=0; to<maxpolyorder+1; to++) { 
      RooArgList parList(Form("bernstein_order%d%s",to,catExt.Data()));
      RooRealVar par0(Form("pbern0_order%d%s",to,catExt.Data()),Form("pbern0_order%d%s",to,catExt.Data()),0.0,1.0);
      RooRealVar par1(Form("pbern1_order%d%s",to,catExt.Data()),Form("pbern1_order%d%s",to,catExt.Data()),0.0,1.0);
      RooRealVar par2(Form("pbern2_order%d%s",to,catExt.Data()),Form("pbern2_order%d%s",to,catExt.Data()),0.0,1.0);
      RooRealVar par3(Form("pbern3_order%d%s",to,catExt.Data()),Form("pbern3_order%d%s",to,catExt.Data()),0.0,1.0);
      RooRealVar par4(Form("pbern4_order%d%s",to,catExt.Data()),Form("pbern4_order%d%s",to,catExt.Data()),0.0,1.0);
      RooRealVar par5(Form("pbern5_order%d%s",to,catExt.Data()),Form("pbern5_order%d%s",to,catExt.Data()),0.0,1.0);
      RooRealVar par6(Form("pbern6_order%d%s",to,catExt.Data()),Form("pbern6_order%d%s",to,catExt.Data()),0.0,1.0);
      if ( to<=0 ) {
	parList.add(par0);
      }
      else if ( to<=1 ) {
	parList.add(par0);
	parList.add(par1);
      }
      else if ( to<=2 ) {
	parList.add(par0);
	parList.add(par1);
	parList.add(par2);
      }
      else if ( to<=3 ) {
	parList.add(par0);
	parList.add(par1);
	parList.add(par2);
	parList.add(par3);
      }
      else if ( to<=4 ) {
	parList.add(par0);
	parList.add(par1);
	parList.add(par2);
	parList.add(par3);
	parList.add(par4);
      }
      else if ( to<=5 ) {
	parList.add(par0);
	parList.add(par1);
	parList.add(par2);
	parList.add(par3);
	parList.add(par4);
	parList.add(par5);
      }
      else if ( to<=6 ) {
	parList.add(par0);
	parList.add(par1);
	parList.add(par2);
	parList.add(par3);
	parList.add(par4);
	parList.add(par5);
	parList.add(par6);
      }
      else { 
	cout << "Bernsteain polynomials are only defined for order [0,6]; exiting." << endl;
	return;
      }
      nFitParams = to+1;
      RooBernstein background(Form("background_bernstein_order%d%s",to,catExt.Data()),Form("background_bernstein_order%d%s",to,catExt.Data()),x,parList);

      //////Fit
      nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = background.fitTo((*mmumuFit), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"),/*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      parListBernstein.push_back(*((RooArgSet*) parList.snapshot(kTRUE)));
      //if ( r->status()!=0 ) continue;
      background.plotOn(frame,Name(Form("background_bernstein_order%d",to)),Range("fitRange"),RooFit::NormRange("fitRange"));

      chi2 = 0.0;
      nEmptyBins = 0;
      //////Construct histograms with residuals and pulls of the data w.r.t. the curve
      RooHist *hresid = frame->residHist();
      RooHist *hpull = frame->pullHist();
      RooCurve *fitcurve = frame->getCurve(Form("background_bernstein_order%d",to));
      //////Determine range of curve 
      Double_t xstart,xstop,y;
      fitcurve->GetPoint(0,xstart,y);
      fitcurve->GetPoint(fitcurve->GetN()-1,xstop,y);
      int nPoints = hresid->GetN();
      for (int i = 0; i < nPoints; i++) {
	double b, point;
	hpull->GetPoint(i,b,point);
	if (b<xstart || b>xstop) continue;
	if (point==0) {
	  ++nEmptyBins;
	}
	else {
	  hresid->GetPoint(i,b,point);
	  chi2 += point*point / (fitcurve->interpolate(b));
	}
      }
      //////Access fit result information
      //r->Print();
      //////Access basic information
      cout << "Status = " << r->status() << endl;
      cout << "EDM = " << r->edm() << endl;
      cout << "-log(L) at minimum = " << r->minNll() << endl;
      //////Access list of final fit parameter values
      cout << "Final value of floating parameters:" << endl;
      r->floatParsFinal().Print("s");
      //////Evaluate chi-square:
      cout << "chiSquare = " << frame->chiSquare(nFitParams) << endl;
      cout << "chiSquare (from residual histogram) / NDOF = " << chi2 << " / " << std::max(nFitParams,nPoints-nEmptyBins-nFitParams) << endl;
      cout << "p-value (chiSquare, NDOF) = " << ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams))) << endl;

      if ( saveFitResult ) {
	//////Save RooFitResult into a ROOT file
	TFile ffitresult(Form("%s/%s_fitResult_bernstein_order%d_mass%.0f.root",outDir,(*mmumuFit).GetName(),to,mass),"RECREATE");
	r->Write("fitResult");
	ffitresult.Close();
      }

      //////Select PDFs
      //////Chi2-based p-value
      fitResultBernstein.push_back(*r);
      fitStatusBernstein.push_back(r->status());
      chi2BernsteinPvalue.push_back(ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams))));
      //////Fisher test
      double thisnll = r->minNll();
      double ftestChi2 = 2*(lastnll-thisnll);
      lastnll = thisnll;
      if ( ftestChi2 < 0.0 ) ftestChi2 = 0.0;
      if ( bestBernsteinOrder < 0 && fitStatusBernstein[to]==0 && TMath::Prob(ftestChi2,1) > 0.05 && to-1 >= 0 ) bestBernsteinOrder = to-1;
      if ( nBG.getVal() < 1e-3 ) bestBernsteinOrder=0;

      frame->remove(Form("background_bernstein_order%d",to));

      if ( (bestBernsteinOrder >= 0 && to > bestBernsteinOrder) || to >= maxpolyorder ) {

	vector<int> bernsteinPDFOrders;
	int minBernsteinOrder = (addBernsteinOrders) ? bestBernsteinOrder-1 : bestBernsteinOrder;
	int maxBernsteinOrder = (addBernsteinOrders) ? bestBernsteinOrder+1 : bestBernsteinOrder;
	for ( int tto = minBernsteinOrder; tto <= maxBernsteinOrder; tto++) {
	  if ( tto < 0 ) continue;
	  if ( nBG.getVal() < 1e-3 && tto > 0 ) continue;
	  if ( ( chi2BernsteinPvalue[tto] > 0.01 &&
		 //chi2BernsteinPvalue[tto] < 0.99 &&
		 fitStatusBernstein[tto]==0 )
	       || nBG.getVal() < 1e-3 ) {
	    bernsteinPDFOrders.push_back(tto);
	    RooBernstein bernstein(Form("background_bernstein_order%d%s",tto,catExt.Data()),Form("background_bernstein_order%d%s",tto,catExt.Data()),x,parListBernstein[tto]);
	    RooArgList tbgBernsteinPDFs;
	    tbgBernsteinPDFs.add(bernstein);

	    if (tto == bestBernsteinOrder) {
	      bernstein.plotOn(frame,Name(Form("background_bernstein_order%d",tto)),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kRed));
	    }
	    else {
	      bernstein.plotOn(frame,Name(Form("background_bernstein_order%d",tto)),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kOrange));
	    }

	    if ( drawFits ) {
	      //////Draw fit
	      TCanvas *can = new TCanvas("can","",600,600);
	      can->cd();
	      frame->SetMinimum(0.0);
	      frame->SetLabelSize(0.02,"Y");
	      frame->SetTitleSize(0.025,"Y");
	      frame->SetXTitle("Dimuon mass [GeV]");
	      frame->Draw();
	      can->SaveAs(Form("%s/%s_fitBackground_bernstein_order%d_mass%.0f.png",outDir,(*mmumuFit).GetName(),tto,mass));
	      can->Update();
	      can->Clear();
	      can->Close();
	    }

	    if ( drawResidual ) {
	      //Create a dedicated frame to draw the residual distribution and add the distribution to the frame
	      RooHist *hresid = frame->residHist();
	      RooPlot *frameres = x.frame(Title("Residual Distribution"));
	      frameres->addPlotable(hresid, "P");
	      frameres->SetXTitle("Dimuon mass [GeV]");
	      TCanvas *can = new TCanvas("can","",600,600);
	      can->cd();
	      frameres->Draw();
	      can->SaveAs(Form("%s/%s_fitResidual_bernstein_order%d_mass%.0f.png",outDir,(*mmumuFit).GetName(),tto,mass));
	      can->Update();
	      can->Clear();

	      //Create a dedicated frame to draw the pull distribution and add the distribution to the frame
	      RooHist *hpull = frame->pullHist();
	      RooPlot *framepull = x.frame(Title("Pull Distribution"));
	      framepull->addPlotable(hpull, "P");
	      framepull->SetXTitle("Dimuon mass [GeV]");
	      can->cd();
	      framepull->Draw();
	      can->SaveAs(Form("%s/%s_fitPull_bernstein_order%d_mass%.0f.png",outDir,(*mmumuFit).GetName(),tto,mass));
	      can->Update();
	      can->Clear();
	      can->Close();
	    }
	    frame->remove(Form("background_bernstein_order%d",tto));
	    bgPDFs.add(*((RooArgSet*) tbgBernsteinPDFs.snapshot(kFALSE)));
	  }
	}
	break;
      }
    }
    RooMultiPdf multipdf(Form("roomultipdf%s",catExt.Data()),Form("roomultipdf%s",catExt.Data()),cat,bgPDFs);
    wfit.import(multipdf);
  }
}
