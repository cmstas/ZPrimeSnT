#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooHist.h"
#include "RooCurve.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "RooFFTConvPdf.h"
#include "RooGaussian.h"
#include "RooVoigtian.h"
#include "RooBreitWigner.h"
#include "RooCrystalBall.h"
#include "RooBernstein.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"

#include "Math/ProbFunc.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>

#include "../NanoCORE/Tools/widths.h"

using namespace std;
using namespace RooFit;

bool drawFits = true;
bool saveFitResult = true;
bool drawResidual = false;
bool useFixedSigma = false;

void fitmass(RooDataSet mmumu, TString sample, bool isData, bool isSignal, TString sigmodel, float mass, TString sigshape="dcbvoigt", const char* outDir = "fitResults")
{
  int mdir = mkdir(outDir,0755);

  // Create workspace, import data and model
  RooWorkspace *wfit = new RooWorkspace("wfit","workspace") ;

  if ( isSignal ) {
    set_widths();

    TString model = "";
    if ( sample.Contains("B3mL2") )
      model = "B3mL2";
    else if ( sample.Contains("DYp3") )
      model = "DYp3";
    else if ( sample.Contains("DY3") )
      model = "DY3";
    else if ( sample.Contains("Y3") )
      model = "Y3";
    else {
      cout << "Unknown model. Exit." << endl;
      return;
    }
    double gamma = widths[model][Form("%.0f",mass)];

    // Set starting standard deviation (sigma)
    double stddev = 0.05*mass;
    double minstddev = 0.01*mass;
    double maxstddev = 0.25*mass;
    //
    double p0 = 8.8e-06;
    double p1 = 0.02;
    double p2 = -2.25;
    TF1 *fstddev = new TF1("fstddev","[0]*x*x+[1]*x+[2]",150.0,3000.0);
    fstddev->SetParameter(0, p0);
    fstddev->SetParameter(1, p1);
    fstddev->SetParameter(2, p2);
    if ( !useFixedSigma ) {
      stddev = std::max(0.1, fstddev->Eval(mass));
      minstddev = 0.75*stddev;
      maxstddev = 1.25*stddev;
    }
    double binsize = 0.1*stddev;

    // Get RooRealVar from RooDataSet
    RooRealVar x = *((RooRealVar*) mmumu.get()->find("mfit"));
    x.setRange(std::max(150.0,mass-10.0*stddev),mass+10.0*stddev);
    int nBins = (mass+10.0*stddev - std::max(150.0,mass-10.0*stddev))/binsize;
    x.setBins(nBins);

    RooPlot *frame = x.frame(std::max(150.0,mass-10.0*stddev),mass+10.0*stddev);
    frame->SetTitle("Signal dimuon mass fit");
    // Plot RooDataSet onto frame
    mmumu.plotOn(frame, DataError(RooAbsData::SumW2));

    // Define fit-related variables
    int nMaxFitAttempts = 5;
    double minMforFit = 175.0;
    int nFitParams = 0;
    RooFitResult *r = new RooFitResult();

    if (sigshape=="gaus"){    
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      RooRealVar sigma("sigma","Sigma",stddev,minstddev,maxstddev);
      RooGaussian signal("gauss","gauss",x,mean,sigma);
      nFitParams = 2;
      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal);
      // Import data into the workspace
      wfit->import(mmumu);
      // Print workspace contents
      //wfit->Print();
    }
    else if (sigshape=="voigt"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      //RooRealVar width("width","width",gamma,0.5*gamma,2.0*gamma);
      RooRealVar width("width","width",gamma);
      RooRealVar sigma("sigma","Sigma",stddev,minstddev,maxstddev);
      RooVoigtian signal("voigt","voigt",x,mean,width,sigma);
      //nFitParams = 3;
      nFitParams = 2;
      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal);
      // Import data into the workspace
      wfit->import(mmumu);
      // Print workspace contents
      //wfit->Print();
    }
    else if (sigshape=="dcb"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      RooRealVar sigma("sigma","Sigma",stddev,minstddev,maxstddev);
      RooRealVar alpha_1("alpha_1", "alpha of left CB tail",  1.0, 0.1, 10.0);
      RooRealVar alpha_2("alpha_2", "alpha of 2nd DoubleCB",  -1.0, -10.0, -0.1);
      RooRealVar n_1("n_1", "n of 1st DoubleCB", 2.0, 1.0, 10.0);
      RooRealVar n_2("n_2", "n of 2nd DoubleCB", 2.0, 1.0, 10.0);
      RooCrystalBall cb_1("CrystallBall_1", "CrystallBall_1", x, mean, sigma, alpha_1, n_1);
      RooCrystalBall cb_2("CrystallBall_2", "CrystallBall_2", x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac("mc_frac", "mc_frac", 0.5, 0.0, 1.0);
      RooAddPdf signal("signal", "signal", RooArgList(cb_1,cb_2), RooArgList(mc_frac), true);
      nFitParams = 7;
      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal);
      // Import data into the workspace
      wfit->import(mmumu);
      // Print workspace contents
      //wfit->Print();
    }
    else if (sigshape=="dcbg"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      RooRealVar sigma("sigma","Sigma",stddev,minstddev,maxstddev);
      RooGaussian gaus("Gaus", "Gaus", x, mean, sigma);
      RooRealVar alpha_1("alpha_1", "alpha of left CB tail",  1.0, 0.1, 10.0);
      RooRealVar alpha_2("alpha_2", "alpha of 2nd DoubleCB",  -1.0, -10.0, -0.1);
      RooRealVar n_1("n_1", "n of 1st DoubleCB", 2.0, 1.0, 10.0);
      RooRealVar n_2("n_2", "n of 2nd DoubleCB", 2.0, 1.0, 10.0);
      RooCrystalBall cb_1("CrystallBall_1", "CrystallBall_1", x, mean, sigma, alpha_1, n_1);
      RooCrystalBall cb_2("CrystallBall_2", "CrystallBall_2", x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac_1("mc_frac_1", "mc_frac_1", 1.0/3, 0.0, 1.0);
      RooRealVar mc_frac_2("mc_frac_2", "mc_frac_2", 1.0/3, 0.0, 1.0);
      RooAddPdf signal("signal", "signal", RooArgList(gaus,cb_1,cb_2), RooArgList(mc_frac_1,mc_frac_2), true);
      nFitParams = 8;
      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal);
      // Import data into the workspace
      wfit->import(mmumu);
      // Print workspace contents
      //wfit->Print();
    }
    else if (sigshape=="dcbxvoigt"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      //RooRealVar width("width","width",gamma,0.5*gamma,2.0*gamma);
      RooRealVar width("width","width",gamma);
      RooRealVar sigma("sigma","Sigma",stddev,minstddev,maxstddev);
      RooVoigtian voigt("voigt","voigt",x,mean,width,sigma);
      RooRealVar alpha_1("alpha_1", "alpha of left CB tail",  1.0, 0.1, 10.0);
      RooRealVar alpha_2("alpha_2", "alpha of 2nd DoubleCB",  -1.0, -10.0, -0.1);
      RooRealVar n_1("n_1", "n of 1st DoubleCB", 2.0, 1.0, 10.0);
      RooRealVar n_2("n_2", "n of 2nd DoubleCB", 2.0, 1.0, 10.0);
      RooCrystalBall cb_1("CrystallBall_1", "CrystallBall_1", x, mean, sigma, alpha_1, n_1);
      RooCrystalBall cb_2("CrystallBall_2", "CrystallBall_2", x, mean, sigma, alpha_2, n_2);
      RooFFTConvPdf cb1voigt("cb1voigt", "cb1voigt", x, cb_1, voigt);
      RooFFTConvPdf cb2voigt("cb2voigt", "cb2voigt", x, cb_2, voigt);
      RooRealVar mc_frac("mc_frac", "mc_frac", 0.5, 0.05, 1.0);
      RooAddPdf signal("signal", "signal", RooArgList(cb1voigt,cb2voigt), RooArgList(mc_frac), true);
      //nFitParams = 8;
      nFitParams = 7;
      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal);
      // Import data into the workspace
      wfit->import(mmumu);
      // Print workspace contents
      //wfit->Print();
    }
    else if (sigshape=="dcbvoigt"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      //RooRealVar width("width","width",gamma,0.5*gamma,2.0*gamma);
      RooRealVar width("width","width",gamma);
      RooRealVar sigma("sigma","Sigma",stddev,minstddev,maxstddev);
      RooVoigtian voigt("voigt","voigt",x,mean,width,sigma);
      RooRealVar alpha_1("alpha_1", "alpha of left CB tail",  1.0, 0.1, 10.0);
      RooRealVar alpha_2("alpha_2", "alpha of 2nd DoubleCB",  -1.0, -10.0, -0.1);
      RooRealVar n_1("n_1", "n of 1st DoubleCB", 2.0, 1.0, 10.0);
      RooRealVar n_2("n_2", "n of 2nd DoubleCB", 2.0, 1.0, 10.0);
      RooCrystalBall cb_1("CrystallBall_1", "CrystallBall_1", x, mean, sigma, alpha_1, n_1);
      RooCrystalBall cb_2("CrystallBall_2", "CrystallBall_2", x, mean, sigma, alpha_2, n_2);
      RooRealVar mc_frac_1("mc_frac_1", "mc_frac_1", 1.0/3, 0.0, 1.0);
      RooRealVar mc_frac_2("mc_frac_2", "mc_frac_2", 1.0/3, 0.0, 1.0);
      RooAddPdf signal("signal", "signal", RooArgList(voigt,cb_1,cb_2), RooArgList(mc_frac_1,mc_frac_2), true);
      //nFitParams = 9;
      nFitParams = 8;
      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal);
      // Print workspace contents
      //wfit->Print();
    }
    else{
      cout << "Signal PDF is unknown. Exiting..." << endl;
      return;
    }

    double chi2 = 0.0;
    int nEmptyBins = 0;
    // Construct histograms with residuals and pulls of the data w.r.t. the curve
    RooHist *hresid = frame->residHist();
    RooHist *hpull = frame->pullHist();
    RooCurve *fitcurve = frame->getCurve("signal");
    // Determine range of curve 
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
    // Access fit result information
    //r->Print();
    // Access basic information
    cout << "Status = " << r->status() << endl;
    cout << "EDM = " << r->edm() << endl;
    cout << "-log(L) at minimum = " << r->minNll() << endl;
    // Access list of final fit parameter values
    cout << "Final value of floating parameters:" << endl;
    r->floatParsFinal().Print("s");
    // Evaluate chi-square:
    cout << "chiSquare = " << frame->chiSquare(nFitParams) << endl;
    cout << "chiSquare (from residual histogram) / NDOF = " << chi2 << " / " << nPoints-nEmptyBins-nFitParams << endl; 
    cout << "p-value (chiSquare, NDOF) = " << ROOT::Math::chisquared_cdf_c(chi2, (double)(nPoints-nEmptyBins-nFitParams)) << endl;
    
    if ( drawFits ) {
      // Draw fit
      TCanvas *can = new TCanvas("can","",600,600);
      can->cd();
      frame->SetLabelSize(0.01,"Y");
      frame->SetTitleSize(0.015,"Y");
      frame->SetXTitle("Dimuon mass [GeV]");
      frame->Draw();
      can->SaveAs(Form("%s/%s_fitSignal_%s.png",outDir,mmumu.GetName(),sigshape.Data()));
      can->Update();
      can->Clear();
      can->Close();
    }

    if ( drawResidual ) {
      // Create a dedicated frame to draw the residual distribution and add the distribution to the frame
      RooPlot *frameres = x.frame(Title("Residual Distribution"));
      frameres->addPlotable(hresid, "P");
      frameres->SetXTitle("Dimuon mass [GeV]");
      TCanvas *can = new TCanvas("can","",600,600);
      can->cd();
      frameres->Draw();
      can->SaveAs(Form("%s/%s_fitResidual_%s.png",outDir,mmumu.GetName(),sigshape.Data()));
      can->Update();
      can->Clear();

      // Create a dedicated frame to draw the pull distribution and add the distribution to the frame
      RooPlot *framepull = x.frame(Title("Pull Distribution"));
      framepull->addPlotable(hpull, "P");
      framepull->SetXTitle("Dimuon mass [GeV]");
      can->cd();
      framepull->Draw();
      can->SaveAs(Form("%s/%s_fitPull_%s.png",outDir,mmumu.GetName(),sigshape.Data()));
      can->Update();
      can->Clear();
      can->Close();
    }

    if ( saveFitResult ) {
      // Save RooFitResult into a ROOT file
      TFile ffitresult(Form("%s/%s_fitResult_%s.root",outDir,mmumu.GetName(),sigshape.Data()),"RECREATE");
      r->Write("fitResult");
      ffitresult.Close();
    }

    reset_widths();

    // Save the workspace into a ROOT file
    wfit->writeToFile(Form("%s/%s_workspace.root",outDir,mmumu.GetName())) ;
    // Workspace will remain in memory after macro finishes
    gDirectory->Add(wfit) ;

  }
  else {

    // Set starting standard deviation (sigma)
    double stddev = 0.05*mass;
    double minstddev = 0.01*mass;
    double maxstddev = 0.25*mass;
    //
    double p0 = 8.8e-06;
    double p1 = 0.02;
    double p2 = -2.25;
    TF1 *fstddev = new TF1("fstddev","[0]*x*x+[1]*x+[2]",150.0,3000.0);
    fstddev->SetParameter(0, p0);
    fstddev->SetParameter(1, p1);
    fstddev->SetParameter(2, p2);
    if ( !useFixedSigma ) {
      stddev = std::max(0.1, fstddev->Eval(mass));
      minstddev = 0.75*stddev;
      maxstddev = 1.25*stddev;
    }
    double binsize = 0.1*stddev;

    // Get RooRealVar from RooDataSet
    RooRealVar x = *((RooRealVar*) mmumu.get()->find("mfit"));
    x.setRange(std::max(150.0,mass-10.0*stddev),mass+10.0*stddev);
    int nBins = (mass+10.0*stddev - std::max(150.0,mass-10.0*stddev))/binsize;
    x.setBins(nBins);

    RooPlot *frame = x.frame(std::max(150.0,mass-10.0*stddev),mass+10.0*stddev);
    frame->SetTitle("BG dimuon mass fit");
    // Plot RooDataSet onto frame
    mmumu.plotOn(frame, DataError(RooAbsData::SumW2));

    // Define fit-related variables
    int nMaxFitAttempts = 5;
    double minMforFit = 175.0;
    int nFitParams = 0;
    RooFitResult *r = new RooFitResult();

    TString fitRange = Form("%f < mfit && mfit < %f",std::max(minMforFit,mass-10.0*stddev),mass+10.0*stddev);
    int maxpolyorder = 6;
    int lastnll = 0;
    int bestBernsteinOrder = 0;
    vector<RooArgList> parListBernstein;
    vector<RooBernstein> pdfBernstein;
    vector<double> chi2BernsteinPvalue;
    vector<int> fitStatusBernstein;
    for (int to=0; to<maxpolyorder+1; to++) { 
      RooArgList parList(Form("bernstein_order%d_%s_mass%.0f",to,mmumu.GetName(),mass));
      RooRealVar par0(Form("pbern0_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern0_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
      RooRealVar par1(Form("pbern1_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern1_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
      RooRealVar par2(Form("pbern2_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern2_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
      RooRealVar par3(Form("pbern3_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern3_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
      RooRealVar par4(Form("pbern4_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern4_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
      RooRealVar par5(Form("pbern5_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern5_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
      RooRealVar par6(Form("pbern6_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("pbern6_maxorder%d_%s_mass%.0f",to,mmumu.GetName(),mass),0.0,1.0);
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
      RooBernstein background(Form("background_bernstein_order%d_%s_mass%.0f",to,mmumu.GetName(),mass),Form("background_bernstein_order%d_%s_%.0f",to,mmumu.GetName(),mass),x,parList);

      // Fit
      int nFits = 0;
      while ( nFits < nMaxFitAttempts ) {
	r = background.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
	if ( r->status()==0 )
	  break;
      }
      parListBernstein.push_back(parList);
      pdfBernstein.push_back(background);
      //if ( r->status()!=0 ) continue;
      background.plotOn(frame,Name(Form("background_bernstein_order%d_mass%.0f",to,mass)));

      double chi2 = 0.0;
      int nEmptyBins = 0;
      // Construct histograms with residuals and pulls of the data w.r.t. the curve
      RooHist *hresid = frame->residHist();
      RooHist *hpull = frame->pullHist();
      RooCurve *fitcurve = frame->getCurve(Form("background_bernstein_order%d_mass%.0f",to,mass));
      // Determine range of curve 
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
      // Access fit result information
      //r->Print();
      // Access basic information
      cout << "Status = " << r->status() << endl;
      cout << "EDM = " << r->edm() << endl;
      cout << "-log(L) at minimum = " << r->minNll() << endl;
      // Access list of final fit parameter values
      cout << "Final value of floating parameters:" << endl;
      r->floatParsFinal().Print("s");
      // Evaluate chi-square:
      cout << "chiSquare = " << frame->chiSquare(nFitParams) << endl;
      cout << "chiSquare (from residual histogram) / NDOF = " << chi2 << " / " << nPoints-nEmptyBins-nFitParams << endl; 
      cout << "p-value (chiSquare, NDOF) = " << ROOT::Math::chisquared_cdf_c(chi2, (double)(nPoints-nEmptyBins-nFitParams)) << endl;
      
      if ( saveFitResult ) {
	// Save RooFitResult into a ROOT file
	TFile ffitresult(Form("%s/%s_fitResult_bernstein_order%d_mass%.0f.root",outDir,mmumu.GetName(),to,mass),"RECREATE");
	r->Write("fitResult");
	ffitresult.Close();
      }
      
      // Select PDFs
      // Chi2-based p-value
      fitStatusBernstein.push_back(r->status());
      chi2BernsteinPvalue.push_back(ROOT::Math::chisquared_cdf_c(chi2, (double)(nPoints-nEmptyBins-nFitParams)));
      // Fisher test
      double thisnll = r->minNll();
      double ftestChi2 = 2*(lastnll-thisnll);
      lastnll = thisnll;
      if ( ftestChi2 < 0.0 ) ftestChi2 = 0.0;
      if ( fitStatusBernstein[to]==0 && TMath::Prob(ftestChi2,1) > 0.05 && to > 0 && bestBernsteinOrder <= 0 ) bestBernsteinOrder = to;

      frame->remove(Form("background_bernstein_order%d_mass%.0f",to,mass));

    }
    cout << "Best Bernsteind PDF order = " << bestBernsteinOrder << endl;
    vector<int> bernsteinPDFOrders;
    for ( int to = bestBernsteinOrder-1; to <= bestBernsteinOrder+1; to++) {
      if ( to < 0 ) continue;
      if ( chi2BernsteinPvalue[to] > 0.0 && chi2BernsteinPvalue[to] < 1.0 && fitStatusBernstein[to]==0 )
	bernsteinPDFOrders.push_back(to);
    }
    
    for(const auto& to: bernsteinPDFOrders) {
      pdfBernstein[to].plotOn(frame,Name(Form("background_bernstein_order%d_mass%.0f",to,mass)));
      //// Import model and all its components into the workspace
      //wfit->import(pdfBernstein[to]);

      if ( drawFits ) {
	// Draw fit
	TCanvas *can = new TCanvas("can","",600,600);
	can->cd();
	frame->SetLabelSize(0.01,"Y");
	frame->SetTitleSize(0.015,"Y");
	frame->SetXTitle("Dimuon mass [GeV]");
	frame->Draw();
	can->SaveAs(Form("%s/%s_fitBackground_bernstein_order%d_mass%.0f.png",outDir,mmumu.GetName(),to,mass));
	can->Update();
	can->Clear();
	can->Close();
      }

      if ( drawResidual ) {
	// Create a dedicated frame to draw the residual distribution and add the distribution to the frame
	RooHist *hresid = frame->residHist();
	RooPlot *frameres = x.frame(Title("Residual Distribution"));
	frameres->addPlotable(hresid, "P");
	frameres->SetXTitle("Dimuon mass [GeV]");
	TCanvas *can = new TCanvas("can","",600,600);
	can->cd();
	frameres->Draw();
	can->SaveAs(Form("%s/%s_fitResidual_bernstein_order%d_mass%.0f.png",outDir,mmumu.GetName(),to,mass));
	can->Update();
	can->Clear();
	
	// Create a dedicated frame to draw the pull distribution and add the distribution to the frame
	RooHist *hpull = frame->pullHist();
	RooPlot *framepull = x.frame(Title("Pull Distribution"));
	framepull->addPlotable(hpull, "P");
	framepull->SetXTitle("Dimuon mass [GeV]");
	can->cd();
	framepull->Draw();
	can->SaveAs(Form("%s/%s_fitPull_bernstein_order%d_mass%.0f.png",outDir,mmumu.GetName(),to,mass));
	can->Update();
	can->Clear();
	can->Close();
      }
      
    }
    
    //double bgNormalization = mmumu.sumEntries(fitRange.Data());
    //RooRealVar nBG(Form("bgNormalization_%s_%.0f",mmumu.GetName(),mass),Form("bgNormalization_%s_%.0f",mmumu.GetName(),mass),bgNormalization,0.5*bgNormalization,2.0*bgNormalization);
    //if ( bgNormalization < 1e-3 ) {
    //  nBG.setVal(0.0);
    //  nBG.setRange(0.0,2e-3);
    //}    
    //wfit->import(nBG);
    //// Import data into the workspace
    //wfit->import(mmumu);
    //// Print workspace contents
    ////wfit->Print();

    //// Save the workspace into a ROOT file
    //wfit->writeToFile(Form("%s/%s_workspace.root",outDir,mmumu.GetName())) ;
    //// Workspace will remain in memory after macro finishes
    //gDirectory->Add(wfit) ;

  }

}
