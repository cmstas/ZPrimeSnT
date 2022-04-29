#include "Config.h"
#include "TLorentzVector.h"
#include "Nano.h"
#include "math.h"
#include "TVector3.h"

using namespace tas;

bool IsMatched(float lep_eta, float lep_phi, std::vector<int> trigObj, float dRmin=0.02){
     bool match = false;
     for ( unsigned int i = 0; i < trigObj.size(); i++){
	   float d_eta = lep_eta - nt.TrigObj_eta().at(i);
           float d_phi = TVector2::Phi_mpi_pi(nt.TrigObj_phi().at(i) - lep_phi);
           float dR = sqrt(pow(d_eta,2)+pow(d_phi,2));
	   if ( dR < dRmin ) {
	     match = true;
	     break;
	   }
     }
     return match;
}

bool IsMatched(float lep_eta, float lep_phi, float trigObj_eta, float trigObj_phi, float dRmin=0.02){
     bool match = false;
     float d_eta = lep_eta - trigObj_eta;
     float d_phi = TVector2::Phi_mpi_pi(trigObj_phi - lep_phi);
     float dR = sqrt(pow(d_eta,2)+pow(d_phi,2));
     if ( dR < dRmin ) match = true;
     return match;
}

bool IsSeparated(TVector3 mu_1, TVector3 mu_2, double delta=0.02){
     double angle = M_PI - delta;
     bool separated = false;
     double vec_sep = mu_1.Angle(mu_2);
     if ( abs(vec_sep) < angle ) separated = true;

     return separated; 

} 
