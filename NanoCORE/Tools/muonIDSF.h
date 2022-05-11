#ifndef MUONIDSF_H
#define MUONIDSF_H

#include <map>
#include <vector>
#include <iostream>
#include <TString.h>

using namespace std;

map<TString,map<TString,map<TString,float>>> idsf = { };
map<TString,map<TString,map<TString,float>>> idsfunc = { };

constexpr int nptbins_id = 7;
constexpr int netabins_id = 4;

float *thresholds_pt_id = new float[nptbins_id];
TString *ptbins_id = new TString[nptbins_id];
inline void set_ptbins_id() {
	thresholds_pt_id[0] = 0.0;
	ptbins_id[0] = "pt0";
	thresholds_pt_id[1] = 0.9;
	ptbins_id[1] = "pt1";
	thresholds_pt_id[2] = 1.2;
	ptbins_id[2] = "pt2";
	thresholds_pt_id[3] = 2.1;
	ptbins_id[3] = "pt3";
	thresholds_pt_id[4] = 2.4;
	ptbins_id[4] = "pt4";
	thresholds_pt_id[5] = 3.0;
	ptbins_id[5] = "pt5";
	thresholds_pt_id[6] = 3.6;
	ptbins_id[6] = "pt6";
}

float *thresholds_eta_id = new float[netabins_id];
TString *etabins_id = new TString[netabins_id];
inline void set_etabins_id() {
	thresholds_eta_id[0] = 0.0;
	etabins_id[0] = "eta0";
	thresholds_eta_id[1] = 0.9;
	etabins_id[1] = "eta1";
	thresholds_eta_id[2] = 1.2;
	etabins_id[2] = "eta2";
	thresholds_eta_id[3] = 2.1;
	etabins_id[3] = "eta3";
}

TString get_muonIDSFPtBin(const float pt);

TString get_muonIDSFEtaBin(const float abseta);

float get_muonIDSF( const float pt, const float eta, const TString year, const TString variation="central" );

inline void reset_muonIDSF() {

	idsf.clear();
	idsfunc.clear();

}

inline void set_muonIDSF() {
	set_ptbins_id();
	set_etabins_id();

	idsf.insert({"2016nonAPV", { }});
	idsfunc.insert({"2016nonAPV", { }});
	idsf["2016nonAPV"].insert({"eta0", { }});
	idsfunc["2016nonAPV"].insert({"eta0", { }});
	idsf["2016nonAPV"]["eta0"].insert({"pt0", 0.991038560867});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt0", 0.000876227787464});
	idsf["2016nonAPV"]["eta0"].insert({"pt1", 0.992986261845});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt1", 0.00133268566747});
	idsf["2016nonAPV"]["eta0"].insert({"pt2", 0.992404043674});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt2", 0.00392846242623});
	idsf["2016nonAPV"]["eta0"].insert({"pt3", 0.991533696651});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt3", 0.00542837279187});
	idsf["2016nonAPV"]["eta0"].insert({"pt4", 0.991862118244});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt4", 0.00646077834312});
	idsf["2016nonAPV"]["eta0"].insert({"pt5", 0.991828501225});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt5", 0.00199408358129});
	idsf["2016nonAPV"]["eta0"].insert({"pt6", 0.991244375706});
	idsfunc["2016nonAPV"]["eta0"].insert({"pt6", 0.000416199042094});
	idsf["2016nonAPV"].insert({"eta1", { }});
	idsfunc["2016nonAPV"].insert({"eta1", { }});
	idsf["2016nonAPV"]["eta1"].insert({"pt0", 0.987932682037});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt0", 0.00153395646921});
	idsf["2016nonAPV"]["eta1"].insert({"pt1", 0.989819824696});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt1", 0.00163602981987});
	idsf["2016nonAPV"]["eta1"].insert({"pt2", 0.988136649132});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt2", 0.00425996224505});
	idsf["2016nonAPV"]["eta1"].insert({"pt3", 0.988563835621});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt3", 0.00556104974982});
	idsf["2016nonAPV"]["eta1"].insert({"pt4", 0.988140761852});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt4", 0.00680464890373});
	idsf["2016nonAPV"]["eta1"].insert({"pt5", 0.988110303879});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt5", 0.00194400573907});
	idsf["2016nonAPV"]["eta1"].insert({"pt6", 0.987487256527});
	idsfunc["2016nonAPV"]["eta1"].insert({"pt6", 0.00130636718855});
	idsf["2016nonAPV"].insert({"eta2", { }});
	idsfunc["2016nonAPV"].insert({"eta2", { }});
	idsf["2016nonAPV"]["eta2"].insert({"pt0", 0.991685211658});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt0", 0.00147217382008});
	idsf["2016nonAPV"]["eta2"].insert({"pt1", 0.992401540279});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt1", 0.00108106738331});
	idsf["2016nonAPV"]["eta2"].insert({"pt2", 0.992007315159});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt2", 0.0040949107983});
	idsf["2016nonAPV"]["eta2"].insert({"pt3", 0.99262547493});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt3", 0.00518933467439});
	idsf["2016nonAPV"]["eta2"].insert({"pt4", 0.993185758591});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt4", 0.00776456166615});
	idsf["2016nonAPV"]["eta2"].insert({"pt5", 0.992389142513});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt5", 0.00309801289369});
	idsf["2016nonAPV"]["eta2"].insert({"pt6", 0.992024183273});
	idsfunc["2016nonAPV"]["eta2"].insert({"pt6", 0.000853879143311});
	idsf["2016nonAPV"].insert({"eta3", { }});
	idsfunc["2016nonAPV"].insert({"eta3", { }});
	idsf["2016nonAPV"]["eta3"].insert({"pt0", 0.976856410503});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt0", 0.004659745917});
	idsf["2016nonAPV"]["eta3"].insert({"pt1", 0.978182375431});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt1", 0.00323781735501});
	idsf["2016nonAPV"]["eta3"].insert({"pt2", 0.978543758392});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt2", 0.00548236844843});
	idsf["2016nonAPV"]["eta3"].insert({"pt3", 0.979182958603});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt3", 0.00586582453171});
	idsf["2016nonAPV"]["eta3"].insert({"pt4", 0.977279543877});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt4", 0.00886291710952});
	idsf["2016nonAPV"]["eta3"].insert({"pt5", 0.979782283306});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt5", 0.00321782593576});
	idsf["2016nonAPV"]["eta3"].insert({"pt6", 0.971952974796});
	idsfunc["2016nonAPV"]["eta3"].insert({"pt6", 0.0106368082175});

	idsf.insert({"2016APV", { }});
	idsfunc.insert({"2016APV", { }});
	idsf["2016APV"].insert({"eta0", { }});
	idsfunc["2016APV"].insert({"eta0", { }});
	idsf["2016APV"]["eta0"].insert({"pt0", 0.99323618412});
	idsfunc["2016APV"]["eta0"].insert({"pt0", 0.00523757331371});
	idsf["2016APV"]["eta0"].insert({"pt1", 0.991814374924});
	idsfunc["2016APV"]["eta0"].insert({"pt1", 0.00297190008441});
	idsf["2016APV"]["eta0"].insert({"pt2", 0.991392016411});
	idsfunc["2016APV"]["eta0"].insert({"pt2", 0.0031169849337});
	idsf["2016APV"]["eta0"].insert({"pt3", 0.991049051285});
	idsfunc["2016APV"]["eta0"].insert({"pt3", 0.00317356580391});
	idsf["2016APV"]["eta0"].insert({"pt4", 0.991102278233});
	idsfunc["2016APV"]["eta0"].insert({"pt4", 0.00307726308104});
	idsf["2016APV"]["eta0"].insert({"pt5", 0.990075111389});
	idsfunc["2016APV"]["eta0"].insert({"pt5", 0.00317885873845});
	idsf["2016APV"]["eta0"].insert({"pt6", 0.989865601063});
	idsfunc["2016APV"]["eta0"].insert({"pt6", 0.00251860182041});
	idsf["2016APV"].insert({"eta1", { }});
	idsfunc["2016APV"].insert({"eta1", { }});
	idsf["2016APV"]["eta1"].insert({"pt0", 0.986753344536});
	idsfunc["2016APV"]["eta1"].insert({"pt0", 0.00497346834219});
	idsf["2016APV"]["eta1"].insert({"pt1", 0.986781358719});
	idsfunc["2016APV"]["eta1"].insert({"pt1", 0.00563626570347});
	idsf["2016APV"]["eta1"].insert({"pt2", 0.98886680603});
	idsfunc["2016APV"]["eta1"].insert({"pt2", 0.00450308069316});
	idsf["2016APV"]["eta1"].insert({"pt3", 0.987104654312});
	idsfunc["2016APV"]["eta1"].insert({"pt3", 0.00355957243079});
	idsf["2016APV"]["eta1"].insert({"pt4", 0.987630009651});
	idsfunc["2016APV"]["eta1"].insert({"pt4", 0.00323340826528});
	idsf["2016APV"]["eta1"].insert({"pt5", 0.987451732159});
	idsfunc["2016APV"]["eta1"].insert({"pt5", 0.00354912867816});
	idsf["2016APV"]["eta1"].insert({"pt6", 0.987442731857});
	idsfunc["2016APV"]["eta1"].insert({"pt6", 0.00197732256698});
	idsf["2016APV"].insert({"eta2", { }});
	idsfunc["2016APV"].insert({"eta2", { }});
	idsf["2016APV"]["eta2"].insert({"pt0", 0.99221688509});
	idsfunc["2016APV"]["eta2"].insert({"pt0", 0.00535803908269});
	idsf["2016APV"]["eta2"].insert({"pt1", 0.991337001324});
	idsfunc["2016APV"]["eta2"].insert({"pt1", 0.00389220863963});
	idsf["2016APV"]["eta2"].insert({"pt2", 0.992746889591});
	idsfunc["2016APV"]["eta2"].insert({"pt2", 0.00428991458998});
	idsf["2016APV"]["eta2"].insert({"pt3", 0.992579340935});
	idsfunc["2016APV"]["eta2"].insert({"pt3", 0.00390404935544});
	idsf["2016APV"]["eta2"].insert({"pt4", 0.993557870388});
	idsfunc["2016APV"]["eta2"].insert({"pt4", 0.00300619400311});
	idsf["2016APV"]["eta2"].insert({"pt5", 0.993085861206});
	idsfunc["2016APV"]["eta2"].insert({"pt5", 0.00306027784154});
	idsf["2016APV"]["eta2"].insert({"pt6", 0.993122160435});
	idsfunc["2016APV"]["eta2"].insert({"pt6", 0.00212453535598});
	idsf["2016APV"].insert({"eta3", { }});
	idsfunc["2016APV"].insert({"eta3", { }});
	idsf["2016APV"]["eta3"].insert({"pt0", 0.979364693165});
	idsfunc["2016APV"]["eta3"].insert({"pt0", 0.00650743728347});
	idsf["2016APV"]["eta3"].insert({"pt1", 0.980486035347});
	idsfunc["2016APV"]["eta3"].insert({"pt1", 0.00585269871322});
	idsf["2016APV"]["eta3"].insert({"pt2", 0.97898209095});
	idsfunc["2016APV"]["eta3"].insert({"pt2", 0.00573547543032});
	idsf["2016APV"]["eta3"].insert({"pt3", 0.979619204998});
	idsfunc["2016APV"]["eta3"].insert({"pt3", 0.00488846515633});
	idsf["2016APV"]["eta3"].insert({"pt4", 0.979634344578});
	idsfunc["2016APV"]["eta3"].insert({"pt4", 0.00400282620132});
	idsf["2016APV"]["eta3"].insert({"pt5", 0.977748394012});
	idsfunc["2016APV"]["eta3"].insert({"pt5", 0.00658766479752});
	idsf["2016APV"]["eta3"].insert({"pt6", 0.975579380989});
	idsfunc["2016APV"]["eta3"].insert({"pt6", 0.0127653994876});

	idsf.insert({"2017", { }});
	idsfunc.insert({"2017", { }});
	idsf["2017"].insert({"eta0", { }});
	idsfunc["2017"].insert({"eta0", { }});
	idsf["2017"]["eta0"].insert({"pt0", 0.993292212486});
	idsfunc["2017"]["eta0"].insert({"pt0", 0.00103022484464});
	idsf["2017"]["eta0"].insert({"pt1", 0.993729114532});
	idsfunc["2017"]["eta0"].insert({"pt1", 0.000983211725641});
	idsf["2017"]["eta0"].insert({"pt2", 0.993467926979});
	idsfunc["2017"]["eta0"].insert({"pt2", 0.000456888425726});
	idsf["2017"]["eta0"].insert({"pt3", 0.993498384953});
	idsfunc["2017"]["eta0"].insert({"pt3", 0.000185734651229});
	idsf["2017"]["eta0"].insert({"pt4", 0.993319988251});
	idsfunc["2017"]["eta0"].insert({"pt4", 0.00016510022011});
	idsf["2017"]["eta0"].insert({"pt5", 0.993298172951});
	idsfunc["2017"]["eta0"].insert({"pt5", 0.000533167419907});
	idsf["2017"]["eta0"].insert({"pt6", 0.992960393429});
	idsfunc["2017"]["eta0"].insert({"pt6", 0.000396837595549});
	idsf["2017"].insert({"eta1", { }});
	idsfunc["2017"].insert({"eta1", { }});
	idsf["2017"]["eta1"].insert({"pt0", 0.988870561123});
	idsfunc["2017"]["eta1"].insert({"pt0", 0.00165788173531});
	idsf["2017"]["eta1"].insert({"pt1", 0.987534582615});
	idsfunc["2017"]["eta1"].insert({"pt1", 0.00219957822368});
	idsf["2017"]["eta1"].insert({"pt2", 0.987384021282});
	idsfunc["2017"]["eta1"].insert({"pt2", 0.000767340376295});
	idsf["2017"]["eta1"].insert({"pt3", 0.987892389297});
	idsfunc["2017"]["eta1"].insert({"pt3", 0.000606517542363});
	idsf["2017"]["eta1"].insert({"pt4", 0.988415122032});
	idsfunc["2017"]["eta1"].insert({"pt4", 0.000187080015012});
	idsf["2017"]["eta1"].insert({"pt5", 0.988063514233});
	idsfunc["2017"]["eta1"].insert({"pt5", 0.000876313921205});
	idsf["2017"]["eta1"].insert({"pt6", 0.987942695618});
	idsfunc["2017"]["eta1"].insert({"pt6", 0.0015575336797});
	idsf["2017"].insert({"eta2", { }});
	idsfunc["2017"].insert({"eta2", { }});
	idsf["2017"]["eta2"].insert({"pt0", 0.991098046303});
	idsfunc["2017"]["eta2"].insert({"pt0", 0.00202973203677});
	idsf["2017"]["eta2"].insert({"pt1", 0.992057025433});
	idsfunc["2017"]["eta2"].insert({"pt1", 0.000979023462587});
	idsf["2017"]["eta2"].insert({"pt2", 0.993266999722});
	idsfunc["2017"]["eta2"].insert({"pt2", 0.000456540078192});
	idsf["2017"]["eta2"].insert({"pt3", 0.993120729923});
	idsfunc["2017"]["eta2"].insert({"pt3", 0.000207565074889});
	idsf["2017"]["eta2"].insert({"pt4", 0.993321239948});
	idsfunc["2017"]["eta2"].insert({"pt4", 0.000161218914901});
	idsf["2017"]["eta2"].insert({"pt5", 0.992929697037});
	idsfunc["2017"]["eta2"].insert({"pt5", 0.000672900541347});
	idsf["2017"]["eta2"].insert({"pt6", 0.992357969284});
	idsfunc["2017"]["eta2"].insert({"pt6", 0.000656943570696});
	idsf["2017"].insert({"eta3", { }});
	idsfunc["2017"].insert({"eta3", { }});
	idsf["2017"]["eta3"].insert({"pt0", 0.976562261581});
	idsfunc["2017"]["eta3"].insert({"pt0", 0.00164965696326});
	idsf["2017"]["eta3"].insert({"pt1", 0.976100623608});
	idsfunc["2017"]["eta3"].insert({"pt1", 0.00145025066942});
	idsf["2017"]["eta3"].insert({"pt2", 0.979540169239});
	idsfunc["2017"]["eta3"].insert({"pt2", 0.000823419309638});
	idsf["2017"]["eta3"].insert({"pt3", 0.978517413139});
	idsfunc["2017"]["eta3"].insert({"pt3", 0.000454191284109});
	idsf["2017"]["eta3"].insert({"pt4", 0.978434562683});
	idsfunc["2017"]["eta3"].insert({"pt4", 0.000738808933199});
	idsf["2017"]["eta3"].insert({"pt5", 0.97441726923});
	idsfunc["2017"]["eta3"].insert({"pt5", 0.00328619348094});
	idsf["2017"]["eta3"].insert({"pt6", 0.973654270172});
	idsfunc["2017"]["eta3"].insert({"pt6", 0.00333441789571});

	idsf.insert({"2018", { }});
	idsfunc.insert({"2018", { }});
	idsf["2018"].insert({"eta0", { }});
	idsfunc["2018"].insert({"eta0", { }});
	idsf["2018"]["eta0"].insert({"pt0", 0.993878245354});
	idsfunc["2018"]["eta0"].insert({"pt0", 0.000838440184193});
	idsf["2018"]["eta0"].insert({"pt1", 0.994140386581});
	idsfunc["2018"]["eta0"].insert({"pt1", 0.000713029707145});
	idsf["2018"]["eta0"].insert({"pt2", 0.994721829891});
	idsfunc["2018"]["eta0"].insert({"pt2", 0.000285320391641});
	idsf["2018"]["eta0"].insert({"pt3", 0.994594156742});
	idsfunc["2018"]["eta0"].insert({"pt3", 0.000166717936352});
	idsf["2018"]["eta0"].insert({"pt4", 0.994418621063});
	idsfunc["2018"]["eta0"].insert({"pt4", 0.00028882851274});
	idsf["2018"]["eta0"].insert({"pt5", 0.994318127632});
	idsfunc["2018"]["eta0"].insert({"pt5", 0.000635315289907});
	idsf["2018"]["eta0"].insert({"pt6", 0.993905723095});
	idsfunc["2018"]["eta0"].insert({"pt6", 0.000443436013649});
	idsf["2018"].insert({"eta1", { }});
	idsfunc["2018"].insert({"eta1", { }});
	idsf["2018"]["eta1"].insert({"pt0", 0.986443519592});
	idsfunc["2018"]["eta1"].insert({"pt0", 0.00131468901143});
	idsf["2018"]["eta1"].insert({"pt1", 0.987626731396});
	idsfunc["2018"]["eta1"].insert({"pt1", 0.00108472584514});
	idsf["2018"]["eta1"].insert({"pt2", 0.987349331379});
	idsfunc["2018"]["eta1"].insert({"pt2", 0.00101481128677});
	idsf["2018"]["eta1"].insert({"pt3", 0.988283097744});
	idsfunc["2018"]["eta1"].insert({"pt3", 0.000260799064315});
	idsf["2018"]["eta1"].insert({"pt4", 0.988070547581});
	idsfunc["2018"]["eta1"].insert({"pt4", 0.000362999356048});
	idsf["2018"]["eta1"].insert({"pt5", 0.987424373627});
	idsfunc["2018"]["eta1"].insert({"pt5", 0.000540563981322});
	idsf["2018"]["eta1"].insert({"pt6", 0.987330198288});
	idsfunc["2018"]["eta1"].insert({"pt6", 0.000601002582889});
	idsf["2018"].insert({"eta2", { }});
	idsfunc["2018"].insert({"eta2", { }});
	idsf["2018"]["eta2"].insert({"pt0", 0.991889894009});
	idsfunc["2018"]["eta2"].insert({"pt0", 0.0010028125155});
	idsf["2018"]["eta2"].insert({"pt1", 0.992112994194});
	idsfunc["2018"]["eta2"].insert({"pt1", 0.000703558015106});
	idsf["2018"]["eta2"].insert({"pt2", 0.99226385355});
	idsfunc["2018"]["eta2"].insert({"pt2", 0.00045316061672});
	idsf["2018"]["eta2"].insert({"pt3", 0.99264985323});
	idsfunc["2018"]["eta2"].insert({"pt3", 0.000242822950825});
	idsf["2018"]["eta2"].insert({"pt4", 0.992835938931});
	idsfunc["2018"]["eta2"].insert({"pt4", 0.000308681271917});
	idsf["2018"]["eta2"].insert({"pt5", 0.992779612541});
	idsfunc["2018"]["eta2"].insert({"pt5", 0.000483613839285});
	idsf["2018"]["eta2"].insert({"pt6", 0.992042064667});
	idsfunc["2018"]["eta2"].insert({"pt6", 0.000481554225938});
	idsf["2018"].insert({"eta3", { }});
	idsfunc["2018"].insert({"eta3", { }});
	idsf["2018"]["eta3"].insert({"pt0", 0.977586686611});
	idsfunc["2018"]["eta3"].insert({"pt0", 0.00278172261662});
	idsf["2018"]["eta3"].insert({"pt1", 0.975184082985});
	idsfunc["2018"]["eta3"].insert({"pt1", 0.0018822902053});
	idsf["2018"]["eta3"].insert({"pt2", 0.977163910866});
	idsfunc["2018"]["eta3"].insert({"pt2", 0.000624391180165});
	idsf["2018"]["eta3"].insert({"pt3", 0.976459085941});
	idsfunc["2018"]["eta3"].insert({"pt3", 0.000502845836415});
	idsf["2018"]["eta3"].insert({"pt4", 0.97682005167});
	idsfunc["2018"]["eta3"].insert({"pt4", 0.000732165319971});
	idsf["2018"]["eta3"].insert({"pt5", 0.973384737968});
	idsfunc["2018"]["eta3"].insert({"pt5", 0.00359534430636});
	idsf["2018"]["eta3"].insert({"pt6", 0.970276236534});
	idsfunc["2018"]["eta3"].insert({"pt6", 0.00508650574916});

}

#endif
