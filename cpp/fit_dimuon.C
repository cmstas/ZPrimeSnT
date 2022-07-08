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

bool drawFits = true;
bool drawResidual = false;
bool useFixedSigma = false;
bool saveFitResult = false;
bool addBernsteinOrders = true;

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
    //x.setBins(nBins);
    RooBinning binningPlot(nBinsPlot,std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);

    RooPlot *frame = x.frame(std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    frame->SetTitle("Signal dimuon mass fit");
    frame->SetMinimum(0.0);
    //////Plot RooDataSet onto frame
    //(*mmumu).plotOn(frame/*, DataError(RooAbsData::SumW2)*/);
    (*mmumu).plotOn(frame, DataError(RooAbsData::SumW2), Binning(binningPlot));

    //////Define fit-related variables
    int nMaxFitAttempts = 5;
    int nFitParams = 0;
    RooFitResult *r = new RooFitResult();

    wfit.import(*(mmumu));
    double sigNormalization = (*mmumu).sumEntries(fitRange.Data());
    RooRealVar nSig(Form("sigNormalization_%s",(*mmumu).GetName()),Form("sigNormalization_%s",(*mmumu).GetName()),sigNormalization);
    wfit.import(nSig);

    if (sigshape=="gaus"){
      RooRealVar mean(Form("mean_%s",(*mmumu).GetName()),Form("mean_%s",(*mmumu).GetName()),mass,mass-stddev,mass+stddev);
      RooRealVar sigma(Form("sigma_%s",(*mmumu).GetName()),Form("sigma_%s",(*mmumu).GetName()),stddev,minstddev,maxstddev);
      RooGaussian signal(Form("signal_%s",(*mmumu).GetName()),Form("signal_%s",(*mmumu).GetName()),x,mean,sigma);
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
      wfit.import(signal);
    }
    else if (sigshape=="voigt"){
      RooRealVar mean(Form("mean_%s",(*mmumu).GetName()),Form("mean_%s",(*mmumu).GetName()),mass,mass-stddev,mass+stddev);
      //RooRealVar width(Form("width_%s",(*mmumu).GetName()),Form("width_%s",(*mmumu).GetName()),gamma,0.75*gamma,1.25*gamma);
      RooRealVar width(Form("width_%s",(*mmumu).GetName()),Form("width_%s",(*mmumu).GetName()),gamma);
      RooRealVar sigma(Form("sigma_%s",(*mmumu).GetName()),Form("sigma_%s",(*mmumu).GetName()),stddev,minstddev,maxstddev);
      RooVoigtian signal(Form("signal_%s",(*mmumu).GetName()),Form("signal_%s",(*mmumu).GetName()),x,mean,width,sigma);
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
      wfit.import(signal);
    }
    else if (sigshape=="dcb"){
      RooRealVar mean(Form("mean_%s",(*mmumu).GetName()),Form("mean_%s",(*mmumu).GetName()),mass,mass-stddev,mass+stddev);
      RooRealVar sigma(Form("sigma_%s",(*mmumu).GetName()),Form("sigma_%s",(*mmumu).GetName()),stddev,minstddev,maxstddev);
      RooRealVar alpha_1(Form("alphaR_%s",(*mmumu).GetName()),Form("alphaR_%s",(*mmumu).GetName()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL_%s",(*mmumu).GetName()),Form("alphaL_%s",(*mmumu).GetName()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR_%s",(*mmumu).GetName()),Form("nR_%s",(*mmumu).GetName()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL_%s",(*mmumu).GetName()),Form("nL_%s",(*mmumu).GetName()), nL, minnL, maxnL);
      //RooCrystalBall cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      //RooCrystalBall cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooCBShape cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac(Form("mcfrac_%s",(*mmumu).GetName()),Form("mcfrac_%s",(*mmumu).GetName()), 0.5, 0.0, 1.0);
      RooAddPdf signal(Form("signal_%s",(*mmumu).GetName()),Form("signal_%s",(*mmumu).GetName()), RooArgList(cb_1,cb_2), RooArgList(mc_frac), true);
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
      wfit.import(signal);
    }
    else if (sigshape=="dcbg"){
      RooRealVar mean(Form("mean_%s",(*mmumu).GetName()),Form("mean_%s",(*mmumu).GetName()),mass,mass-stddev,mass+stddev);
      RooRealVar sigma(Form("sigma_%s",(*mmumu).GetName()),Form("sigma_%s",(*mmumu).GetName()),stddev,minstddev,maxstddev);
      RooGaussian gaus(Form("gauss_%s",(*mmumu).GetName()),Form("gauss_%s",(*mmumu).GetName()),x,mean,sigma);
      RooRealVar alpha_1(Form("alphaR_%s",(*mmumu).GetName()),Form("alphaR_%s",(*mmumu).GetName()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL_%s",(*mmumu).GetName()),Form("alphaL_%s",(*mmumu).GetName()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR_%s",(*mmumu).GetName()),Form("nR_%s",(*mmumu).GetName()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL_%s",(*mmumu).GetName()),Form("nL_%s",(*mmumu).GetName()), nL, minnL, maxnL);
      //RooCrystalBall cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      //RooCrystalBall cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooCBShape cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac_1(Form("mcfracR_%s",(*mmumu).GetName()),Form("mcfracR_%s",(*mmumu).GetName()), fracR, minfracR, maxfracR);
      RooRealVar mc_frac_2(Form("mcfracL_%s",(*mmumu).GetName()),Form("mcfracL_%s",(*mmumu).GetName()), fracL, minfracL, maxfracL);
      RooAddPdf signal(Form("signal_%s",(*mmumu).GetName()),Form("signal_%s",(*mmumu).GetName()), RooArgList(gaus,cb_1,cb_2), RooArgList(mc_frac_1,mc_frac_2), true);
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
      wfit.import(signal);
    }
    else if (sigshape=="dcbxvoigt"){
      RooRealVar mean(Form("mean_%s",(*mmumu).GetName()),Form("mean_%s",(*mmumu).GetName()),mass,mass-stddev,mass+stddev);
      //RooRealVar width(Form("width_%s",(*mmumu).GetName()),Form("width_%s",(*mmumu).GetName()),gamma,0.75*gamma,1.25*gamma);
      RooRealVar width(Form("width_%s",(*mmumu).GetName()),Form("width_%s",(*mmumu).GetName()),gamma);
      RooRealVar sigma(Form("sigma_%s",(*mmumu).GetName()),Form("sigma_%s",(*mmumu).GetName()),stddev,minstddev,maxstddev);
      RooVoigtian voigt(Form("voigt_%s",(*mmumu).GetName()),Form("voigt_%s",(*mmumu).GetName()),x,mean,width,sigma);
      RooRealVar alpha_1(Form("alphaR_%s",(*mmumu).GetName()),Form("alphaR_%s",(*mmumu).GetName()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL_%s",(*mmumu).GetName()),Form("alphaL_%s",(*mmumu).GetName()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR_%s",(*mmumu).GetName()),Form("nR_%s",(*mmumu).GetName()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL_%s",(*mmumu).GetName()),Form("nL_%s",(*mmumu).GetName()), nL, minnL, maxnL);
      //RooCrystalBall cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      //RooCrystalBall cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooCBShape cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooFFTConvPdf cb1voigt(Form("CBRVoigt_%s",(*mmumu).GetName()),Form("CBRVoigt_%s",(*mmumu).GetName()), x, cb_1, voigt);
      RooFFTConvPdf cb2voigt(Form("CBLVoigt_%s",(*mmumu).GetName()),Form("CBLVoigt_%s",(*mmumu).GetName()), x, cb_2, voigt);
      RooRealVar mc_frac(Form("mcfrac_%s",(*mmumu).GetName()),Form("mcfrac_%s",(*mmumu).GetName()), 0.5, 0.0, 1.0);
      RooAddPdf signal(Form("signal_%s",(*mmumu).GetName()),Form("signal_%s",(*mmumu).GetName()), RooArgList(cb1voigt,cb2voigt), RooArgList(mc_frac), true);
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
      wfit.import(signal);
    }
    else if (sigshape=="dcbvoigt"){
      RooRealVar mean(Form("mean_%s",(*mmumu).GetName()),Form("mean_%s",(*mmumu).GetName()),mass,mass-stddev,mass+stddev);
      //RooRealVar width(Form("width_%s",(*mmumu).GetName()),Form("width_%s",(*mmumu).GetName()),gamma,0.75*gamma,1.25*gamma);
      RooRealVar width(Form("width_%s",(*mmumu).GetName()),Form("width_%s",(*mmumu).GetName()),gamma);
      RooRealVar sigma(Form("sigma_%s",(*mmumu).GetName()),Form("sigma_%s",(*mmumu).GetName()),stddev,minstddev,maxstddev);
      RooVoigtian voigt(Form("voigt_%s",(*mmumu).GetName()),Form("voigt_%s",(*mmumu).GetName()),x,mean,width,sigma);
      RooRealVar alpha_1(Form("alphaR_%s",(*mmumu).GetName()),Form("alphaR_%s",(*mmumu).GetName()),alphaR, minalphaR, maxalphaR);
      RooRealVar alpha_2(Form("alphaL_%s",(*mmumu).GetName()),Form("alphaL_%s",(*mmumu).GetName()),alphaL, minalphaL, maxalphaL);
      RooRealVar n_1(Form("nR_%s",(*mmumu).GetName()),Form("nR_%s",(*mmumu).GetName()), nR, minnR, maxnR);
      RooRealVar n_2(Form("nL_%s",(*mmumu).GetName()),Form("nL_%s",(*mmumu).GetName()), nL, minnL, maxnL);
      //RooCrystalBall cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      //RooCrystalBall cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooCBShape cb_1(Form("CBR_%s",(*mmumu).GetName()),Form("CBR_%s",(*mmumu).GetName()), x, mean, sigma, alpha_1, n_1);
      RooCBShape cb_2(Form("CBL_%s",(*mmumu).GetName()),Form("CBL_%s",(*mmumu).GetName()), x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac_1(Form("mcfracR_%s",(*mmumu).GetName()),Form("mcfracR_%s",(*mmumu).GetName()), fracR, minfracR, maxfracR);
      RooRealVar mc_frac_2(Form("mcfracL_%s",(*mmumu).GetName()),Form("mcfracL_%s",(*mmumu).GetName()), fracL, minfracL, maxfracL);
      RooAddPdf signal(Form("signal_%s",(*mmumu).GetName()),Form("signal_%s",(*mmumu).GetName()), RooArgList(voigt,cb_1,cb_2), RooArgList(mc_frac_1,mc_frac_2), true);
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
    //x.setBins(nBins);
    RooBinning binningPlot(nBinsPlot,std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);

    RooDataSet *mmumuFit;
    double bgNormalizationForToy = (*mmumu).sumEntries(fitRange.Data());
    RooRealVar nBGForToy(Form("bgNormalizationForToy_%s_%.0f",(*mmumu).GetName(),mass),Form("bgNormalizationForToy_%s_%.0f",(*mmumu).GetName(),mass),bgNormalizationForToy);
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
    frame->SetTitle("BG dimuon mass fit");
    frame->SetMinimum(0.0);

    //////Plot RooDataSet onto frame
    (*mmumuFit).plotOn(frame/*, DataError(RooAbsData::SumW2)*/, Binning(binningPlot));

    //////Define RooMultiPDF
    //////Make a RooCategory object. This will control which of the PDFs is "active"
    RooCategory cat(Form("pdf_index_%s",(*mmumuFit).GetName()),"Index of active PDF");
    RooArgList bgPDFs;
    //RooArgSet *bgPDFs;

    //////Define fit-related variables
    int nMaxFitAttempts = 5;
    int nFitParams = 0;
    RooFitResult *r = new RooFitResult();

    (*mmumuFit).Print();
    wfit.import(*(mmumuFit));

    double bgNormalization = (*mmumuFit).sumEntries(fitRange.Data());
    RooRealVar nBG(Form("roomultipdf_%s_norm",(*mmumuFit).GetName()),Form("roomultipdf_%s_norm",(*mmumuFit).GetName()),bgNormalization,0.0,10.0*bgNormalization);
    if ( bgNormalization < 0.001 ) {
      nBG.setVal(0.0001);
      nBG.setRange(0.0,0.001);
    }
    wfit.import(nBG);

    //////Exponential PDF
    RooRealVar expo_slope(Form("expo_slope_%s_mass%.0f",(*mmumuFit).GetName(),mass),Form("expo_slope_%s_mass%.0f",(*mmumuFit).GetName(),mass),-0.02,-0.1,-0.0001);
    RooExponential exponential(Form("background_exponential_%s_mass%.0f",(*mmumuFit).GetName(),mass),Form("background_exponential_%s_mass%.0f",(*mmumuFit).GetName(),mass),x,expo_slope);
    //////Fit
    int nFits = 0;
    while ( nFits < nMaxFitAttempts ) {
      r = exponential.fitTo((*mmumuFit), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"),/*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
      ++nFits;
      if ( r->status()==0 )
	break;
    }
    exponential.plotOn(frame,Name(Form("background_exponential_mass%.0f",mass)),Range("fitRange"),RooFit::NormRange("fitRange"));

    double chi2 = 0.0;
    int nEmptyBins = 0;
    //////Construct histograms with residuals and pulls of the data w.r.t. the curve
    RooHist *hresid = frame->residHist();
    RooHist *hpull = frame->pullHist();
    RooCurve *fitcurve = frame->getCurve(Form("background_exponential_mass%.0f",mass));
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

    //////Select PDFs
    //////Chi2-based p-value
    int fitStatusExponential = r->status();
    double chi2ExponentialPvalue = ROOT::Math::chisquared_cdf_c(chi2, (double)(std::max(nFitParams,nPoints-nEmptyBins-nFitParams)));

    frame->remove(Form("background_exponential_mass%.0f",mass));

    if ( chi2ExponentialPvalue > 0.05 &&
	 chi2ExponentialPvalue < 0.95 &&
	 fitStatusExponential==0 ) {
      bgPDFs.add(exponential);

      exponential.plotOn(frame,Name(Form("background_exponential_mass%.0f",mass)),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kRed));
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
      frame->remove(Form("background_exponential_mass%.0f",mass));
    }

    //////Power-law PDF
    RooRealVar plaw_power(Form("plaw_power_%s_mass%.0f",(*mmumuFit).GetName(),mass),Form("plaw_power_%s_mass%.0f",(*mmumuFit).GetName(),mass),-3.0,-6.0,-0.0001);
    RooGenericPdf powerlaw(Form("background_powerlaw_%s_mass%.0f",(*mmumuFit).GetName(),mass),"TMath::Power(@0,@1)",RooArgList(x,plaw_power));
    //////Fit
    nFits = 0;
    while ( nFits < nMaxFitAttempts ) {
      r = powerlaw.fitTo((*mmumuFit), Range("fitRange"), Save(), Minimizer("Minuit2","minimize"),/*SumW2Error(kTRUE), */PrintLevel(-1), PrintEvalErrors(-1));
      ++nFits;
      if ( r->status()==0 )
	break;
    }
    powerlaw.plotOn(frame,Name(Form("background_powerlaw_mass%.0f",mass)),Range("fitRange"),RooFit::NormRange("fitRange"));

    chi2 = 0.0;
    nEmptyBins = 0;
    //////Construct histograms with residuals and pulls of the data w.r.t. the curve
    hresid = frame->residHist();
    hpull = frame->pullHist();
    fitcurve = frame->getCurve(Form("background_powerlaw_mass%.0f",mass));
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

    frame->remove(Form("background_powerlaw_mass%.0f",mass));

    if ( chi2PowerlawPvalue > 0.05 &&
	 chi2PowerlawPvalue < 0.95 &&
	 fitStatusPowerlaw==0 ) {
      bgPDFs.add(powerlaw);

      powerlaw.plotOn(frame,Name(Form("background_powerlaw_mass%.0f",mass)),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kRed));
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
      frame->remove(Form("background_powerlaw_mass%.0f",mass));
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
      RooArgList parList(Form("bernstein_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass));
      RooRealVar par0(Form("pbern0_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern0_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
      RooRealVar par1(Form("pbern1_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern1_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
      RooRealVar par2(Form("pbern2_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern2_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
      RooRealVar par3(Form("pbern3_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern3_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
      RooRealVar par4(Form("pbern4_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern4_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
      RooRealVar par5(Form("pbern5_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern5_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
      RooRealVar par6(Form("pbern6_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("pbern6_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),0.0,1.0);
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
      RooBernstein background(Form("background_bernstein_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),Form("background_bernstein_order%d_%s_mass%.0f",to,(*mmumuFit).GetName(),mass),x,parList);

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
      background.plotOn(frame,Name(Form("background_bernstein_order%d_mass%.0f",to,mass)),Range("fitRange"),RooFit::NormRange("fitRange"));

      chi2 = 0.0;
      nEmptyBins = 0;
      //////Construct histograms with residuals and pulls of the data w.r.t. the curve
      RooHist *hresid = frame->residHist();
      RooHist *hpull = frame->pullHist();
      RooCurve *fitcurve = frame->getCurve(Form("background_bernstein_order%d_mass%.0f",to,mass));
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
      if ( bestBernsteinOrder < 0 && fitStatusBernstein[to]==0 && TMath::Prob(ftestChi2,1) > 0.05 && to >= 0 ) bestBernsteinOrder = to;
      if ( nBG.getVal() < 1e-3 ) bestBernsteinOrder=0;

      frame->remove(Form("background_bernstein_order%d_mass%.0f",to,mass));

      if ( (bestBernsteinOrder >= 0 && to > bestBernsteinOrder) || to >= maxpolyorder ) {

	vector<int> bernsteinPDFOrders;
	int minBernsteinOrder = (addBernsteinOrders) ?bestBernsteinOrder-1 : bestBernsteinOrder;
	int maxBernsteinOrder = (addBernsteinOrders) ?bestBernsteinOrder+1 : bestBernsteinOrder;
	for ( int tto = minBernsteinOrder; tto <= maxBernsteinOrder; tto++) {
	  if ( tto < 0 ) continue;
	  if ( nBG.getVal() < 1e-3 && tto > 0 ) continue;
	  if ( ( chi2BernsteinPvalue[tto] > 0.05 && chi2BernsteinPvalue[tto] < 0.95 && fitStatusBernstein[tto]==0 ) || nBG.getVal() < 1e-3 ) {
	    bernsteinPDFOrders.push_back(tto);
	    //parListBernstein[tto].Print("v");
	    RooBernstein background(Form("background_bernstein_order%d_%s_mass%.0f",tto,(*mmumuFit).GetName(),mass),Form("background_bernstein_order%d_%s_mass%.0f",tto,(*mmumuFit).GetName(),mass),x,parListBernstein[tto]);
	    RooArgList tbgBernsteinPDFs;
	    tbgBernsteinPDFs.add(background);

	    if (tto == bestBernsteinOrder) {
	      background.plotOn(frame,Name(Form("background_bernstein_order%d_mass%.0f",tto,mass)),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kRed));
	    }
	    else {
	      background.plotOn(frame,Name(Form("background_bernstein_order%d_mass%.0f",tto,mass)),Range("fitRange"),RooFit::NormRange("fitRange"),LineColor(kOrange));
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
	    frame->remove(Form("background_bernstein_order%d_mass%.0f",tto,mass));
	    //bgPDFs.add(background);
	    //bgPDFs.add(*((RooArgSet*) tbgBernsteinPDFs.snapshot(kTRUE)));
	    bgPDFs.add(*((RooArgSet*) tbgBernsteinPDFs.snapshot(kFALSE)));
	  }
	}
	break;
      }
    }
    RooMultiPdf multipdf(Form("roomultipdf_%s",(*mmumuFit).GetName()),Form("roomultipdf_%s",(*mmumuFit).GetName()),cat,bgPDFs);
    wfit.import(multipdf);
  }
}
