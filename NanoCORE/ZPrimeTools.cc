#include "Config.h"
#include "TLorentzVector.h"
#include "Nano.h"
#include "math.h"
#include "TVector3.h"

using namespace tas;

bool IsMatched(float lep_eta, float lep_phi, std::vector<int> trigObj){
     float dRmin = 0.2;
     bool match = false;
     for ( int i = 0; i < trigObj.size(); i++){
	   float d_eta = lep_eta - nt.TrigObj_eta().at(i);
           float d_phi = lep_phi - nt.TrigObj_phi().at(i);
           float dR = sqrt(pow(d_eta,2)+pow(d_phi,2));
	   if ( dR < dRmin ) match = true;
     }
     return match;
}

bool IsSeparated(TVector3 mu_1, TVector3 mu_2){
     double angle = M_PI - 0.2000;
     bool separated = false;
     double vec_sep = mu_1.Angle(mu_2);
     if ( abs(vec_sep) < angle ) separated = true;

     return separated; 

} 
