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

#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"

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

void fitmass(RooDataSet mmumu, TString sample, bool isData, bool isSignal, float mass, TString sigshape="dcbvoigt", const char* outDir = "fitResults")
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

    // Get RooRealVar from RooDataSet
    RooRealVar x = *((RooRealVar*) mmumu.get()->find("mfit"));
    x.setRange(std::max(150.0,mass-10.0*stddev),mass+10.0*stddev);
    int nBins = (mass+10.0*stddev - std::max(150.0,mass-10.0*stddev))/(0.005*mass);
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
      RooRealVar sigma("sigma","Sigma",0.05*mass,0.01*mass,0.25*mass);
      RooGaussian gauss("gauss","gauss",x,mean,sigma);
      RooAddPdf signal("signal", "signal", RooArgList(gauss));
      nFitParams = 2;
      // Fit
      int nFits = 0;
      while ( r->status()!=0 && nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal) ;
      // Import data into the workspace
      wfit->import(mmumu) ;
      // Print workspace contents
      //wfit->Print() ;
    }    
    else if (sigshape=="voigt"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      //RooRealVar width("width","width",gamma,0.5*gamma,2.0*gamma);
      RooRealVar width("width","width",gamma);
      RooRealVar sigma("sigma","Sigma",0.05*mass,0.01*mass,0.25*mass);
      RooVoigtian voigt("voigt","voigt",x,mean,width,sigma);
      RooAddPdf signal("signal", "signal", RooArgList(voigt));
      //nFitParams = 3;
      nFitParams = 2;
      // Fit
      int nFits = 0;
      while ( r->status()!=0 && nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal) ;
      // Import data into the workspace
      wfit->import(mmumu) ;
      // Print workspace contents
      //wfit->Print() ;
    }
    else if (sigshape=="dcb"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      RooRealVar sigma("sigma","Sigma",0.05*mass,0.01*mass,0.25*mass);
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
      while ( r->status()!=0 && nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal) ;
      // Import data into the workspace
      wfit->import(mmumu) ;
      // Print workspace contents
      //wfit->Print() ;
    }
    else if (sigshape=="dcbg"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      RooRealVar sigma("sigma","Sigma",0.05*mass,0.01*mass,0.25*mass);
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
      while ( r->status()!=0 && nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal) ;
      // Import data into the workspace
      wfit->import(mmumu) ;
      // Print workspace contents
      //wfit->Print() ;
    }
    else if (sigshape=="dcbxvoigt"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      //RooRealVar width("width","width",gamma,0.5*gamma,2.0*gamma);
      RooRealVar width("width","width",gamma);
      RooRealVar sigma("sigma","Sigma",0.05*mass,0.01*mass,0.25*mass);
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
      while ( r->status()!=0 && nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal) ;
      // Import data into the workspace
      wfit->import(mmumu) ;
      // Print workspace contents
      //wfit->Print() ;
    }
    else if (sigshape=="dcbvoigt"){
      RooRealVar mean("mean","Mean",mass,0.75*mass,1.25*mass);
      //RooRealVar width("width","width",gamma,0.5*gamma,2.0*gamma);
      RooRealVar width("width","width",gamma);
      RooRealVar sigma("sigma","Sigma",0.05*mass,0.01*mass,0.25*mass);
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
      while ( r->status()!=0 && nFits < nMaxFitAttempts ) {
	r = signal.fitTo(mmumu, Range(std::max(minMforFit,mass-10.0*stddev), mass+10.0*stddev), Save(), Minimizer("Minuit2","minimize"), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));
	++nFits;
      }
      signal.plotOn(frame,Name("signal"));
      // Import model and all its components into the workspace
      wfit->import(signal) ;
      // Import data into the workspace
      wfit->import(mmumu) ;
      // Print workspace contents
      //wfit->Print() ;
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
    Double_t xstart,xstop,y ;
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
      can->Delete();
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
      can->Delete();
    }

    if ( saveFitResult ) {
      // Save RooFitResult into a ROOT file
      TFile ffitresult(Form("%s/%s_fitResult_%s.root",outDir,mmumu.GetName(),sigshape.Data()),"RECREATE") ;
      r->Write("fitResult") ;
      ffitresult.Close() ;
    }

    reset_widths();
  }
  else {
    cout << "Work in progress..." << endl;
    return;
  }

  // Save the workspace into a ROOT file
  wfit->writeToFile(Form("%s/%s_workspace_%s.root",outDir,mmumu.GetName(),sigshape.Data())) ;
  // Workspace will remain in memory after macro finishes
  gDirectory->Add(wfit) ;

}
