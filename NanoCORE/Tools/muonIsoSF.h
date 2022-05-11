#ifndef MUONIsoSF_H
#define MUONIsoSF_H

#include <map>
#include <vector>
#include <iostream>
#include <TString.h>

using namespace std;

map<TString,map<TString,map<TString,float>>> isosf = { };
map<TString,map<TString,map<TString,float>>> isosfunc = { };

vector<float> thresholds_pt_iso;
vector<TString> ptbins_iso;
inline void set_ptbins_iso() {
	thresholds_pt_iso.push_back(15.0);
	ptbins_iso.push_back("pt0");
	thresholds_pt_iso.push_back(20.0);
	ptbins_iso.push_back("pt1");
	thresholds_pt_iso.push_back(25.0);
	ptbins_iso.push_back("pt2");
	thresholds_pt_iso.push_back(30.0);
	ptbins_iso.push_back("pt3");
	thresholds_pt_iso.push_back(40.0);
	ptbins_iso.push_back("pt4");
	thresholds_pt_iso.push_back(50.0);
	ptbins_iso.push_back("pt5");
	thresholds_pt_iso.push_back(60.0);
	ptbins_iso.push_back("pt6");
}

vector<float> thresholds_eta_iso;
vector<TString> etabins_iso;
inline void set_etabins_iso() {
	thresholds_eta_iso.push_back(0.0);
	etabins_iso.push_back("eta0");
	thresholds_eta_iso.push_back(0.9);
	etabins_iso.push_back("eta1");
	thresholds_eta_iso.push_back(1.2);
	etabins_iso.push_back("eta2");
	thresholds_eta_iso.push_back(2.1);
	etabins_iso.push_back("eta3");
}

TString get_muonIsoSFPtBin(const float pt);

TString get_muonIsoSFEtaBin(const float abseta);

float get_muonIsoSF( const float pt, const float eta, const TString year, const TString variation="central" );

inline void reset_muonIsoSF() {

	isosf.clear();
	isosfunc.clear();

}

inline void set_muonIsoSF() {
	set_ptbins_iso();
	set_etabins_iso();

	isosf.insert({"2016nonAPV", { }});
	isosfunc.insert({"2016nonAPV", { }});
	isosf["2016nonAPV"].insert({"eta0", { }});
	isosfunc["2016nonAPV"].insert({"eta0", { }});
	isosf["2016nonAPV"]["eta0"].insert({"pt0", 0.990140080452});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt0", 0.00287416647205});
	isosf["2016nonAPV"]["eta0"].insert({"pt1", 0.991725862026});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt1", 0.00272561956354});
	isosf["2016nonAPV"]["eta0"].insert({"pt2", 0.994013905525});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt2", 0.000753144667515});
	isosf["2016nonAPV"]["eta0"].insert({"pt3", 0.996264159679});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt3", 0.000206172169736});
	isosf["2016nonAPV"]["eta0"].insert({"pt4", 0.997684001923});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt4", 0.000106266615369});
	isosf["2016nonAPV"]["eta0"].insert({"pt5", 0.998000741005});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt5", 0.000309368729198});
	isosf["2016nonAPV"]["eta0"].insert({"pt6", 0.999144136906});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt6", 0.000219307711241});
	isosf["2016nonAPV"].insert({"eta1", { }});
	isosfunc["2016nonAPV"].insert({"eta1", { }});
	isosf["2016nonAPV"]["eta1"].insert({"pt0", 0.989233970642});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt0", 0.0032408578289});
	isosf["2016nonAPV"]["eta1"].insert({"pt1", 0.994826376438});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt1", 0.00225845529404});
	isosf["2016nonAPV"]["eta1"].insert({"pt2", 0.998054146767});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt2", 0.000923894357299});
	isosf["2016nonAPV"]["eta1"].insert({"pt3", 0.998584389687});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt3", 0.000337761794938});
	isosf["2016nonAPV"]["eta1"].insert({"pt4", 0.998453140259});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt4", 0.000216948842523});
	isosf["2016nonAPV"]["eta1"].insert({"pt5", 0.998618960381});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt5", 0.00031078853685});
	isosf["2016nonAPV"]["eta1"].insert({"pt6", 0.998576998711});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt6", 0.000404284841101});
	isosf["2016nonAPV"].insert({"eta2", { }});
	isosfunc["2016nonAPV"].insert({"eta2", { }});
	isosf["2016nonAPV"]["eta2"].insert({"pt0", 1.00105547905});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt0", 0.00206842164999});
	isosf["2016nonAPV"]["eta2"].insert({"pt1", 0.998185396194});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt1", 0.0010816174664});
	isosf["2016nonAPV"]["eta2"].insert({"pt2", 1.00072443485});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt2", 0.000631496953608});
	isosf["2016nonAPV"]["eta2"].insert({"pt3", 0.999783992767});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt3", 0.000203676394609});
	isosf["2016nonAPV"]["eta2"].insert({"pt4", 0.999232470989});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt4", 0.000265926080424});
	isosf["2016nonAPV"]["eta2"].insert({"pt5", 0.999476969242});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt5", 0.00035784794407});
	isosf["2016nonAPV"]["eta2"].insert({"pt6", 0.999585449696});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt6", 0.000234810733644});
	isosf["2016nonAPV"].insert({"eta3", { }});
	isosfunc["2016nonAPV"].insert({"eta3", { }});
	isosf["2016nonAPV"]["eta3"].insert({"pt0", 1.00662636757});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt0", 0.00236181666594});
	isosf["2016nonAPV"]["eta3"].insert({"pt1", 1.00329697132});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt1", 0.00156713497517});
	isosf["2016nonAPV"]["eta3"].insert({"pt2", 1.00272333622});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt2", 0.000913828818985});
	isosf["2016nonAPV"]["eta3"].insert({"pt3", 1.00088989735});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt3", 0.000363516423391});
	isosf["2016nonAPV"]["eta3"].insert({"pt4", 1.00013995171});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt4", 0.000209543464489});
	isosf["2016nonAPV"]["eta3"].insert({"pt5", 0.999682843685});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt5", 0.000548091778785});
	isosf["2016nonAPV"]["eta3"].insert({"pt6", 1.00004780293});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt6", 0.000545471047169});

	isosf.insert({"2016APV", { }});
	isosfunc.insert({"2016APV", { }});
	isosf["2016APV"].insert({"eta0", { }});
	isosfunc["2016APV"].insert({"eta0", { }});
	isosf["2016APV"]["eta0"].insert({"pt0", 0.983842253685});
	isosfunc["2016APV"]["eta0"].insert({"pt0", 0.00238012223524});
	isosf["2016APV"]["eta0"].insert({"pt1", 0.991503715515});
	isosfunc["2016APV"]["eta0"].insert({"pt1", 0.00139130587552});
	isosf["2016APV"]["eta0"].insert({"pt2", 0.992633640766});
	isosfunc["2016APV"]["eta0"].insert({"pt2", 0.000668991381706});
	isosf["2016APV"]["eta0"].insert({"pt3", 0.994851052761});
	isosfunc["2016APV"]["eta0"].insert({"pt3", 0.00023461621473});
	isosf["2016APV"]["eta0"].insert({"pt4", 0.99636477232});
	isosfunc["2016APV"]["eta0"].insert({"pt4", 0.000148985173975});
	isosf["2016APV"]["eta0"].insert({"pt5", 0.996927559376});
	isosfunc["2016APV"]["eta0"].insert({"pt5", 0.000280831215868});
	isosf["2016APV"]["eta0"].insert({"pt6", 0.998375535011});
	isosfunc["2016APV"]["eta0"].insert({"pt6", 0.000304209193408});
	isosf["2016APV"].insert({"eta1", { }});
	isosfunc["2016APV"].insert({"eta1", { }});
	isosf["2016APV"]["eta1"].insert({"pt0", 0.995001077652});
	isosfunc["2016APV"]["eta1"].insert({"pt0", 0.00306058228498});
	isosf["2016APV"]["eta1"].insert({"pt1", 0.992413640022});
	isosfunc["2016APV"]["eta1"].insert({"pt1", 0.00185363387563});
	isosf["2016APV"]["eta1"].insert({"pt2", 0.997791349888});
	isosfunc["2016APV"]["eta1"].insert({"pt2", 0.00111346654255});
	isosf["2016APV"]["eta1"].insert({"pt3", 0.998060941696});
	isosfunc["2016APV"]["eta1"].insert({"pt3", 0.000368462914917});
	isosf["2016APV"]["eta1"].insert({"pt4", 0.998582780361});
	isosfunc["2016APV"]["eta1"].insert({"pt4", 0.000240098509119});
	isosf["2016APV"]["eta1"].insert({"pt5", 0.998677909374});
	isosfunc["2016APV"]["eta1"].insert({"pt5", 0.000421441873243});
	isosf["2016APV"]["eta1"].insert({"pt6", 0.999225497246});
	isosfunc["2016APV"]["eta1"].insert({"pt6", 0.00045544889171});
	isosf["2016APV"].insert({"eta2", { }});
	isosfunc["2016APV"].insert({"eta2", { }});
	isosf["2016APV"]["eta2"].insert({"pt0", 0.996481716633});
	isosfunc["2016APV"]["eta2"].insert({"pt0", 0.0021550042964});
	isosf["2016APV"]["eta2"].insert({"pt1", 1.00086116791});
	isosfunc["2016APV"]["eta2"].insert({"pt1", 0.00125293515061});
	isosf["2016APV"]["eta2"].insert({"pt2", 1.00040149689});
	isosfunc["2016APV"]["eta2"].insert({"pt2", 0.000656460283005});
	isosf["2016APV"]["eta2"].insert({"pt3", 0.999966800213});
	isosfunc["2016APV"]["eta2"].insert({"pt3", 0.000250387193306});
	isosf["2016APV"]["eta2"].insert({"pt4", 0.999351799488});
	isosfunc["2016APV"]["eta2"].insert({"pt4", 0.000122227696015});
	isosf["2016APV"]["eta2"].insert({"pt5", 0.999325215816});
	isosfunc["2016APV"]["eta2"].insert({"pt5", 0.000264581502767});
	isosf["2016APV"]["eta2"].insert({"pt6", 0.999282121658});
	isosfunc["2016APV"]["eta2"].insert({"pt6", 0.000318038289794});
	isosf["2016APV"].insert({"eta3", { }});
	isosfunc["2016APV"].insert({"eta3", { }});
	isosf["2016APV"]["eta3"].insert({"pt0", 1.00399982929});
	isosfunc["2016APV"]["eta3"].insert({"pt0", 0.00307355386531});
	isosf["2016APV"]["eta3"].insert({"pt1", 1.00485503674});
	isosfunc["2016APV"]["eta3"].insert({"pt1", 0.00160114014494});
	isosf["2016APV"]["eta3"].insert({"pt2", 1.00185382366});
	isosfunc["2016APV"]["eta3"].insert({"pt2", 0.00118939341456});
	isosf["2016APV"]["eta3"].insert({"pt3", 1.00140476227});
	isosfunc["2016APV"]["eta3"].insert({"pt3", 0.000370872216909});
	isosf["2016APV"]["eta3"].insert({"pt4", 1.00013613701});
	isosfunc["2016APV"]["eta3"].insert({"pt4", 0.000224009547816});
	isosf["2016APV"]["eta3"].insert({"pt5", 1.00035858154});
	isosfunc["2016APV"]["eta3"].insert({"pt5", 0.00051553361991});
	isosf["2016APV"]["eta3"].insert({"pt6", 1.00051212311});
	isosfunc["2016APV"]["eta3"].insert({"pt6", 0.000626761362416});

	isosf.insert({"2017", { }});
	isosfunc.insert({"2017", { }});
	isosf["2017"].insert({"eta0", { }});
	isosfunc["2017"].insert({"eta0", { }});
	isosf["2017"]["eta0"].insert({"pt0", 0.995146751404});
	isosfunc["2017"]["eta0"].insert({"pt0", 0.00223920444837});
	isosf["2017"]["eta0"].insert({"pt1", 0.998417556286});
	isosfunc["2017"]["eta0"].insert({"pt1", 0.00223833987983});
	isosf["2017"]["eta0"].insert({"pt2", 0.997822284698});
	isosfunc["2017"]["eta0"].insert({"pt2", 0.00184833828904});
	isosf["2017"]["eta0"].insert({"pt3", 0.998113811016});
	isosfunc["2017"]["eta0"].insert({"pt3", 0.000156223673428});
	isosf["2017"]["eta0"].insert({"pt4", 0.999082148075});
	isosfunc["2017"]["eta0"].insert({"pt4", 8.90500168054e-05});
	isosf["2017"]["eta0"].insert({"pt5", 0.99880194664});
	isosfunc["2017"]["eta0"].insert({"pt5", 0.000241531869366});
	isosf["2017"]["eta0"].insert({"pt6", 0.999478876591});
	isosfunc["2017"]["eta0"].insert({"pt6", 0.00024455981242});
	isosf["2017"].insert({"eta1", { }});
	isosfunc["2017"].insert({"eta1", { }});
	isosf["2017"]["eta1"].insert({"pt0", 0.992159426212});
	isosfunc["2017"]["eta1"].insert({"pt0", 0.00434278374033});
	isosf["2017"]["eta1"].insert({"pt1", 0.998758494854});
	isosfunc["2017"]["eta1"].insert({"pt1", 0.00186111408497});
	isosf["2017"]["eta1"].insert({"pt2", 1.00143003464});
	isosfunc["2017"]["eta1"].insert({"pt2", 0.0010109340613});
	isosf["2017"]["eta1"].insert({"pt3", 0.999055683613});
	isosfunc["2017"]["eta1"].insert({"pt3", 0.000260169700975});
	isosf["2017"]["eta1"].insert({"pt4", 0.999677121639});
	isosfunc["2017"]["eta1"].insert({"pt4", 0.000162791939648});
	isosf["2017"]["eta1"].insert({"pt5", 0.9991081357});
	isosfunc["2017"]["eta1"].insert({"pt5", 0.000323168839649});
	isosf["2017"]["eta1"].insert({"pt6", 0.999700903893});
	isosfunc["2017"]["eta1"].insert({"pt6", 0.000393990616123});
	isosf["2017"].insert({"eta2", { }});
	isosfunc["2017"].insert({"eta2", { }});
	isosf["2017"]["eta2"].insert({"pt0", 1.00952279568});
	isosfunc["2017"]["eta2"].insert({"pt0", 0.0018457533936});
	isosf["2017"]["eta2"].insert({"pt1", 1.00525331497});
	isosfunc["2017"]["eta2"].insert({"pt1", 0.00151470065368});
	isosf["2017"]["eta2"].insert({"pt2", 1.00320005417});
	isosfunc["2017"]["eta2"].insert({"pt2", 0.000784624110302});
	isosf["2017"]["eta2"].insert({"pt3", 1.00066125393});
	isosfunc["2017"]["eta2"].insert({"pt3", 0.000218975851797});
	isosf["2017"]["eta2"].insert({"pt4", 1.00034630299});
	isosfunc["2017"]["eta2"].insert({"pt4", 0.000109780985095});
	isosf["2017"]["eta2"].insert({"pt5", 0.999647736549});
	isosfunc["2017"]["eta2"].insert({"pt5", 0.000371327764035});
	isosf["2017"]["eta2"].insert({"pt6", 0.999895989895});
	isosfunc["2017"]["eta2"].insert({"pt6", 0.000272540446277});
	isosf["2017"].insert({"eta3", { }});
	isosfunc["2017"].insert({"eta3", { }});
	isosf["2017"]["eta3"].insert({"pt0", 1.01087701321});
	isosfunc["2017"]["eta3"].insert({"pt0", 0.00333415718503});
	isosf["2017"]["eta3"].insert({"pt1", 1.01155138016});
	isosfunc["2017"]["eta3"].insert({"pt1", 0.00173857129073});
	isosf["2017"]["eta3"].insert({"pt2", 1.0077354908});
	isosfunc["2017"]["eta3"].insert({"pt2", 0.00110772995423});
	isosf["2017"]["eta3"].insert({"pt3", 1.00220131874});
	isosfunc["2017"]["eta3"].insert({"pt3", 0.000361765506532});
	isosf["2017"]["eta3"].insert({"pt4", 1.0007083416});
	isosfunc["2017"]["eta3"].insert({"pt4", 0.000222357993968});
	isosf["2017"]["eta3"].insert({"pt5", 0.999516844749});
	isosfunc["2017"]["eta3"].insert({"pt5", 0.000577940823688});
	isosf["2017"]["eta3"].insert({"pt6", 1.00080287457});
	isosfunc["2017"]["eta3"].insert({"pt6", 0.000672517383493});

	isosf.insert({"2018", { }});
	isosfunc.insert({"2018", { }});
	isosf["2018"].insert({"eta0", { }});
	isosfunc["2018"].insert({"eta0", { }});
	isosf["2018"]["eta0"].insert({"pt0", 0.989093780518});
	isosfunc["2018"]["eta0"].insert({"pt0", 0.00231180896676});
	isosf["2018"]["eta0"].insert({"pt1", 0.99634885788});
	isosfunc["2018"]["eta0"].insert({"pt1", 0.00128780411572});
	isosf["2018"]["eta0"].insert({"pt2", 0.996420264244});
	isosfunc["2018"]["eta0"].insert({"pt2", 0.000447301088994});
	isosf["2018"]["eta0"].insert({"pt3", 0.998218417168});
	isosfunc["2018"]["eta0"].insert({"pt3", 0.000139197698533});
	isosf["2018"]["eta0"].insert({"pt4", 0.998921096325});
	isosfunc["2018"]["eta0"].insert({"pt4", 7.70899629009e-05});
	isosf["2018"]["eta0"].insert({"pt5", 0.998930513859});
	isosfunc["2018"]["eta0"].insert({"pt5", 0.000223530819835});
	isosf["2018"]["eta0"].insert({"pt6", 0.999252140522});
	isosfunc["2018"]["eta0"].insert({"pt6", 0.000182141174168});
	isosf["2018"].insert({"eta1", { }});
	isosfunc["2018"].insert({"eta1", { }});
	isosf["2018"]["eta1"].insert({"pt0", 0.993837416172});
	isosfunc["2018"]["eta1"].insert({"pt0", 0.00264630715178});
	isosf["2018"]["eta1"].insert({"pt1", 0.997611582279});
	isosfunc["2018"]["eta1"].insert({"pt1", 0.00145079776177});
	isosf["2018"]["eta1"].insert({"pt2", 0.997916042805});
	isosfunc["2018"]["eta1"].insert({"pt2", 0.000805323719773});
	isosf["2018"]["eta1"].insert({"pt3", 0.999454975128});
	isosfunc["2018"]["eta1"].insert({"pt3", 0.000236890886391});
	isosf["2018"]["eta1"].insert({"pt4", 0.999244391918});
	isosfunc["2018"]["eta1"].insert({"pt4", 0.000137760042292});
	isosf["2018"]["eta1"].insert({"pt5", 0.999533176422});
	isosfunc["2018"]["eta1"].insert({"pt5", 0.000338364968797});
	isosf["2018"]["eta1"].insert({"pt6", 0.999792933464});
	isosfunc["2018"]["eta1"].insert({"pt6", 0.000345436022362});
	isosf["2018"].insert({"eta2", { }});
	isosfunc["2018"].insert({"eta2", { }});
	isosf["2018"]["eta2"].insert({"pt0", 1.0038921833});
	isosfunc["2018"]["eta2"].insert({"pt0", 0.00180883085141});
	isosf["2018"]["eta2"].insert({"pt1", 1.00119960308});
	isosfunc["2018"]["eta2"].insert({"pt1", 0.00141148698075});
	isosf["2018"]["eta2"].insert({"pt2", 1.00093531609});
	isosfunc["2018"]["eta2"].insert({"pt2", 0.00043141380454});
	isosf["2018"]["eta2"].insert({"pt3", 1.00021481514});
	isosfunc["2018"]["eta2"].insert({"pt3", 0.000188491806568});
	isosf["2018"]["eta2"].insert({"pt4", 0.999975860119});
	isosfunc["2018"]["eta2"].insert({"pt4", 9.38010485698e-05});
	isosf["2018"]["eta2"].insert({"pt5", 0.999340474606});
	isosfunc["2018"]["eta2"].insert({"pt5", 0.000221703025434});
	isosf["2018"]["eta2"].insert({"pt6", 0.999692797661});
	isosfunc["2018"]["eta2"].insert({"pt6", 0.000250031143996});
	isosf["2018"].insert({"eta3", { }});
	isosfunc["2018"].insert({"eta3", { }});
	isosf["2018"]["eta3"].insert({"pt0", 1.00590264797});
	isosfunc["2018"]["eta3"].insert({"pt0", 0.0021858056562});
	isosf["2018"]["eta3"].insert({"pt1", 1.00421690941});
	isosfunc["2018"]["eta3"].insert({"pt1", 0.00130076407827});
	isosf["2018"]["eta3"].insert({"pt2", 1.00212740898});
	isosfunc["2018"]["eta3"].insert({"pt2", 0.000952734411174});
	isosf["2018"]["eta3"].insert({"pt3", 1.00130021572});
	isosfunc["2018"]["eta3"].insert({"pt3", 0.000298067408362});
	isosf["2018"]["eta3"].insert({"pt4", 1.00007641315});
	isosfunc["2018"]["eta3"].insert({"pt4", 0.000235851162887});
	isosf["2018"]["eta3"].insert({"pt5", 1.00023853779});
	isosfunc["2018"]["eta3"].insert({"pt5", 0.000395691970579});
	isosf["2018"]["eta3"].insert({"pt6", 0.999996483326});
	isosfunc["2018"]["eta3"].insert({"pt6", 0.00050112049578});

}

#endif
