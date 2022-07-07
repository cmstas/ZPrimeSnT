#ifndef MUONISOSF_H
#define MUONISOSF_H

#include <map>
#include <vector>
#include <iostream>
#include <TString.h>

using namespace std;

map<TString,map<TString,map<TString,float>>> isosf = { };
map<TString,map<TString,map<TString,float>>> isosfunc = { };

constexpr int nptbins_iso = 7;
constexpr int netabins_iso = 4;

float *thresholds_pt_iso = new float[nptbins_iso];
TString *ptbins_iso = new TString[nptbins_iso];
inline void set_ptbins_iso() {
	thresholds_pt_iso[0] = 0.0;
	ptbins_iso[0] = "pt0";
	thresholds_pt_iso[1] = 0.9;
	ptbins_iso[1] = "pt1";
	thresholds_pt_iso[2] = 1.2;
	ptbins_iso[2] = "pt2";
	thresholds_pt_iso[3] = 2.1;
	ptbins_iso[3] = "pt3";
	thresholds_pt_iso[4] = 2.4;
	ptbins_iso[4] = "pt4";
	thresholds_pt_iso[5] = 3.0;
	ptbins_iso[5] = "pt5";
	thresholds_pt_iso[6] = 3.6;
	ptbins_iso[6] = "pt6";
}

float *thresholds_eta_iso = new float[netabins_iso];
TString *etabins_iso = new TString[netabins_iso];
inline void set_etabins_iso() {
	thresholds_eta_iso[0] = 0.0;
	etabins_iso[0] = "eta0";
	thresholds_eta_iso[1] = 0.9;
	etabins_iso[1] = "eta1";
	thresholds_eta_iso[2] = 1.2;
	etabins_iso[2] = "eta2";
	thresholds_eta_iso[3] = 2.1;
	etabins_iso[3] = "eta3";
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
	isosf["2016nonAPV"]["eta0"].insert({"pt0", 0.984367311001});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt0", 0.0031420653216});
	isosf["2016nonAPV"]["eta0"].insert({"pt1", 0.983549058437});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt1", 0.00181042279059});
	isosf["2016nonAPV"]["eta0"].insert({"pt2", 0.984287679195});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt2", 0.000945127829835});
	isosf["2016nonAPV"]["eta0"].insert({"pt3", 0.98774266243});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt3", 0.000487131071878});
	isosf["2016nonAPV"]["eta0"].insert({"pt4", 0.991430222988});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt4", 0.000280016664204});
	isosf["2016nonAPV"]["eta0"].insert({"pt5", 0.992886841297});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt5", 0.000447732046048});
	isosf["2016nonAPV"]["eta0"].insert({"pt6", 0.995608091354});
	isosfunc["2016nonAPV"]["eta0"].insert({"pt6", 0.00048740534787});
	isosf["2016nonAPV"].insert({"eta1", { }});
	isosfunc["2016nonAPV"].insert({"eta1", { }});
	isosf["2016nonAPV"]["eta1"].insert({"pt0", 0.975333333015});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt0", 0.00410702306524});
	isosf["2016nonAPV"]["eta1"].insert({"pt1", 0.988472342491});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt1", 0.00266833471289});
	isosf["2016nonAPV"]["eta1"].insert({"pt2", 0.991665661335});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt2", 0.00612591971023});
	isosf["2016nonAPV"]["eta1"].insert({"pt3", 0.993330419064});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt3", 0.00112554825936});
	isosf["2016nonAPV"]["eta1"].insert({"pt4", 0.994531929493});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt4", 0.000413101380715});
	isosf["2016nonAPV"]["eta1"].insert({"pt5", 0.994804263115});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt5", 0.000761984885477});
	isosf["2016nonAPV"]["eta1"].insert({"pt6", 0.999102830887});
	isosfunc["2016nonAPV"]["eta1"].insert({"pt6", 0.000870551825055});
	isosf["2016nonAPV"].insert({"eta2", { }});
	isosfunc["2016nonAPV"].insert({"eta2", { }});
	isosf["2016nonAPV"]["eta2"].insert({"pt0", 1.00067782402});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt0", 0.00344075893386});
	isosf["2016nonAPV"]["eta2"].insert({"pt1", 0.995697438717});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt1", 0.00166442992344});
	isosf["2016nonAPV"]["eta2"].insert({"pt2", 0.998406350613});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt2", 0.00125588050245});
	isosf["2016nonAPV"]["eta2"].insert({"pt3", 0.998373389244});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt3", 0.000483884341527});
	isosf["2016nonAPV"]["eta2"].insert({"pt4", 0.99857956171});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt4", 0.000254581530101});
	isosf["2016nonAPV"]["eta2"].insert({"pt5", 0.998342216015});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt5", 0.00103850345404});
	isosf["2016nonAPV"]["eta2"].insert({"pt6", 0.998328506947});
	isosfunc["2016nonAPV"]["eta2"].insert({"pt6", 0.000916279030583});
	isosf["2016nonAPV"].insert({"eta3", { }});
	isosfunc["2016nonAPV"].insert({"eta3", { }});
	isosf["2016nonAPV"]["eta3"].insert({"pt0", 1.00559854507});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt0", 0.00358972905376});
	isosf["2016nonAPV"]["eta3"].insert({"pt1", 1.00345349312});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt1", 0.00268651120757});
	isosf["2016nonAPV"]["eta3"].insert({"pt2", 1.00366210938});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt2", 0.00200228520741});
	isosf["2016nonAPV"]["eta3"].insert({"pt3", 1.00262272358});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt3", 0.000808433342336});
	isosf["2016nonAPV"]["eta3"].insert({"pt4", 1.00109648705});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt4", 0.000495129422598});
	isosf["2016nonAPV"]["eta3"].insert({"pt5", 1.00063073635});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt5", 0.00111970135347});
	isosf["2016nonAPV"]["eta3"].insert({"pt6", 1.00123393536});
	isosfunc["2016nonAPV"]["eta3"].insert({"pt6", 0.00112402601285});

	isosf.insert({"2016APV", { }});
	isosfunc.insert({"2016APV", { }});
	isosf["2016APV"].insert({"eta0", { }});
	isosfunc["2016APV"].insert({"eta0", { }});
	isosf["2016APV"]["eta0"].insert({"pt0", 0.980290830135});
	isosfunc["2016APV"]["eta0"].insert({"pt0", 0.00298950055863});
	isosf["2016APV"]["eta0"].insert({"pt1", 0.98554700613});
	isosfunc["2016APV"]["eta0"].insert({"pt1", 0.00204995214472});
	isosf["2016APV"]["eta0"].insert({"pt2", 0.986100077629});
	isosfunc["2016APV"]["eta0"].insert({"pt2", 0.00387534635297});
	isosf["2016APV"]["eta0"].insert({"pt3", 0.987081289291});
	isosfunc["2016APV"]["eta0"].insert({"pt3", 0.000435923421848});
	isosf["2016APV"]["eta0"].insert({"pt4", 0.989958703518});
	isosfunc["2016APV"]["eta0"].insert({"pt4", 0.00045539316073});
	isosf["2016APV"]["eta0"].insert({"pt5", 0.992043435574});
	isosfunc["2016APV"]["eta0"].insert({"pt5", 0.000671402137131});
	isosf["2016APV"]["eta0"].insert({"pt6", 0.995402693748});
	isosfunc["2016APV"]["eta0"].insert({"pt6", 0.000659784434982});
	isosf["2016APV"].insert({"eta1", { }});
	isosfunc["2016APV"].insert({"eta1", { }});
	isosf["2016APV"]["eta1"].insert({"pt0", 0.996034562588});
	isosfunc["2016APV"]["eta1"].insert({"pt0", 0.00474915475335});
	isosf["2016APV"]["eta1"].insert({"pt1", 0.992690086365});
	isosfunc["2016APV"]["eta1"].insert({"pt1", 0.00305252510345});
	isosf["2016APV"]["eta1"].insert({"pt2", 0.993187010288});
	isosfunc["2016APV"]["eta1"].insert({"pt2", 0.00209348786322});
	isosf["2016APV"]["eta1"].insert({"pt3", 0.993661999702});
	isosfunc["2016APV"]["eta1"].insert({"pt3", 0.00132229441654});
	isosf["2016APV"]["eta1"].insert({"pt4", 0.99515080452});
	isosfunc["2016APV"]["eta1"].insert({"pt4", 0.000422522153009});
	isosf["2016APV"]["eta1"].insert({"pt5", 0.995418727398});
	isosfunc["2016APV"]["eta1"].insert({"pt5", 0.00105459530777});
	isosf["2016APV"]["eta1"].insert({"pt6", 0.99754434824});
	isosfunc["2016APV"]["eta1"].insert({"pt6", 0.000959887039847});
	isosf["2016APV"].insert({"eta2", { }});
	isosfunc["2016APV"].insert({"eta2", { }});
	isosf["2016APV"]["eta2"].insert({"pt0", 0.996525347233});
	isosfunc["2016APV"]["eta2"].insert({"pt0", 0.00296189337347});
	isosf["2016APV"]["eta2"].insert({"pt1", 1.00235497952});
	isosfunc["2016APV"]["eta2"].insert({"pt1", 0.00196285984221});
	isosf["2016APV"]["eta2"].insert({"pt2", 0.999375939369});
	isosfunc["2016APV"]["eta2"].insert({"pt2", 0.00105649180287});
	isosf["2016APV"]["eta2"].insert({"pt3", 0.999540150166});
	isosfunc["2016APV"]["eta2"].insert({"pt3", 0.000495222336414});
	isosf["2016APV"]["eta2"].insert({"pt4", 0.999448120594});
	isosfunc["2016APV"]["eta2"].insert({"pt4", 0.000309233563229});
	isosf["2016APV"]["eta2"].insert({"pt5", 0.99864512682});
	isosfunc["2016APV"]["eta2"].insert({"pt5", 0.000634381053764});
	isosf["2016APV"]["eta2"].insert({"pt6", 0.998654782772});
	isosfunc["2016APV"]["eta2"].insert({"pt6", 0.00076971131254});
	isosf["2016APV"].insert({"eta3", { }});
	isosfunc["2016APV"].insert({"eta3", { }});
	isosf["2016APV"]["eta3"].insert({"pt0", 1.01043188572});
	isosfunc["2016APV"]["eta3"].insert({"pt0", 0.00420126002203});
	isosf["2016APV"]["eta3"].insert({"pt1", 1.00543451309});
	isosfunc["2016APV"]["eta3"].insert({"pt1", 0.00259293662984});
	isosf["2016APV"]["eta3"].insert({"pt2", 1.00377643108});
	isosfunc["2016APV"]["eta3"].insert({"pt2", 0.00191086271435});
	isosf["2016APV"]["eta3"].insert({"pt3", 1.00364625454});
	isosfunc["2016APV"]["eta3"].insert({"pt3", 0.00148736024467});
	isosf["2016APV"]["eta3"].insert({"pt4", 1.00186264515});
	isosfunc["2016APV"]["eta3"].insert({"pt4", 0.000569969650978});
	isosf["2016APV"]["eta3"].insert({"pt5", 1.00235652924});
	isosfunc["2016APV"]["eta3"].insert({"pt5", 0.000969037955112});
	isosf["2016APV"]["eta3"].insert({"pt6", 1.00095427036});
	isosfunc["2016APV"]["eta3"].insert({"pt6", 0.00133801091249});

	isosf.insert({"2017", { }});
	isosfunc.insert({"2017", { }});
	isosf["2017"].insert({"eta0", { }});
	isosfunc["2017"].insert({"eta0", { }});
	isosf["2017"]["eta0"].insert({"pt0", 0.992873489857});
	isosfunc["2017"]["eta0"].insert({"pt0", 0.00364661735268});
	isosf["2017"]["eta0"].insert({"pt1", 0.995457649231});
	isosfunc["2017"]["eta0"].insert({"pt1", 0.00693407540584});
	isosf["2017"]["eta0"].insert({"pt2", 0.99394518137});
	isosfunc["2017"]["eta0"].insert({"pt2", 0.000922419533169});
	isosf["2017"]["eta0"].insert({"pt3", 0.995125114918});
	isosfunc["2017"]["eta0"].insert({"pt3", 0.000283106090965});
	isosf["2017"]["eta0"].insert({"pt4", 0.996479451656});
	isosfunc["2017"]["eta0"].insert({"pt4", 0.00048457598255});
	isosf["2017"]["eta0"].insert({"pt5", 0.99670869112});
	isosfunc["2017"]["eta0"].insert({"pt5", 0.000850826630478});
	isosf["2017"]["eta0"].insert({"pt6", 0.997578084469});
	isosfunc["2017"]["eta0"].insert({"pt6", 0.000488098969651});
	isosf["2017"].insert({"eta1", { }});
	isosfunc["2017"].insert({"eta1", { }});
	isosf["2017"]["eta1"].insert({"pt0", 0.993837952614});
	isosfunc["2017"]["eta1"].insert({"pt0", 0.00569461013843});
	isosf["2017"]["eta1"].insert({"pt1", 1.00335657597});
	isosfunc["2017"]["eta1"].insert({"pt1", 0.00292755849735});
	isosf["2017"]["eta1"].insert({"pt2", 1.00339829922});
	isosfunc["2017"]["eta1"].insert({"pt2", 0.00172499620722});
	isosf["2017"]["eta1"].insert({"pt3", 0.998559296131});
	isosfunc["2017"]["eta1"].insert({"pt3", 0.00058221285261});
	isosf["2017"]["eta1"].insert({"pt4", 0.999120414257});
	isosfunc["2017"]["eta1"].insert({"pt4", 0.000359467672961});
	isosf["2017"]["eta1"].insert({"pt5", 0.998489677906});
	isosfunc["2017"]["eta1"].insert({"pt5", 0.000753405831828});
	isosf["2017"]["eta1"].insert({"pt6", 0.999163508415});
	isosfunc["2017"]["eta1"].insert({"pt6", 0.00163018895837});
	isosf["2017"].insert({"eta2", { }});
	isosfunc["2017"].insert({"eta2", { }});
	isosf["2017"]["eta2"].insert({"pt0", 1.0195325613});
	isosfunc["2017"]["eta2"].insert({"pt0", 0.00273337095737});
	isosf["2017"]["eta2"].insert({"pt1", 1.01262366772});
	isosfunc["2017"]["eta2"].insert({"pt1", 0.00171383351897});
	isosf["2017"]["eta2"].insert({"pt2", 1.00903499126});
	isosfunc["2017"]["eta2"].insert({"pt2", 0.00102561298737});
	isosf["2017"]["eta2"].insert({"pt3", 1.00457465649});
	isosfunc["2017"]["eta2"].insert({"pt3", 0.000354347983728});
	isosf["2017"]["eta2"].insert({"pt4", 1.00293004513});
	isosfunc["2017"]["eta2"].insert({"pt4", 0.000255410015541});
	isosf["2017"]["eta2"].insert({"pt5", 1.00065231323});
	isosfunc["2017"]["eta2"].insert({"pt5", 0.000896270591016});
	isosf["2017"]["eta2"].insert({"pt6", 0.999813556671});
	isosfunc["2017"]["eta2"].insert({"pt6", 0.000610674443232});
	isosf["2017"].insert({"eta3", { }});
	isosfunc["2017"].insert({"eta3", { }});
	isosf["2017"]["eta3"].insert({"pt0", 1.03066253662});
	isosfunc["2017"]["eta3"].insert({"pt0", 0.00449433527165});
	isosf["2017"]["eta3"].insert({"pt1", 1.02898108959});
	isosfunc["2017"]["eta3"].insert({"pt1", 0.00297047340911});
	isosf["2017"]["eta3"].insert({"pt2", 1.01824748516});
	isosfunc["2017"]["eta3"].insert({"pt2", 0.00213608260007});
	isosf["2017"]["eta3"].insert({"pt3", 1.01109707355});
	isosfunc["2017"]["eta3"].insert({"pt3", 0.000891080601124});
	isosf["2017"]["eta3"].insert({"pt4", 1.00717175007});
	isosfunc["2017"]["eta3"].insert({"pt4", 0.000613495997105});
	isosf["2017"]["eta3"].insert({"pt5", 1.00434195995});
	isosfunc["2017"]["eta3"].insert({"pt5", 0.00170759840523});
	isosf["2017"]["eta3"].insert({"pt6", 1.00598561764});
	isosfunc["2017"]["eta3"].insert({"pt6", 0.00160558937026});

	isosf.insert({"2018", { }});
	isosfunc.insert({"2018", { }});
	isosf["2018"].insert({"eta0", { }});
	isosfunc["2018"].insert({"eta0", { }});
	isosf["2018"]["eta0"].insert({"pt0", 0.98772841692});
	isosfunc["2018"]["eta0"].insert({"pt0", 0.00267612769335});
	isosf["2018"]["eta0"].insert({"pt1", 0.994106054306});
	isosfunc["2018"]["eta0"].insert({"pt1", 0.00174957633666});
	isosf["2018"]["eta0"].insert({"pt2", 0.990476369858});
	isosfunc["2018"]["eta0"].insert({"pt2", 0.000897548635207});
	isosf["2018"]["eta0"].insert({"pt3", 0.994292616844});
	isosfunc["2018"]["eta0"].insert({"pt3", 0.000328527741342});
	isosf["2018"]["eta0"].insert({"pt4", 0.99594014883});
	isosfunc["2018"]["eta0"].insert({"pt4", 0.000180548433383});
	isosf["2018"]["eta0"].insert({"pt5", 0.995983541012});
	isosfunc["2018"]["eta0"].insert({"pt5", 0.000721119881357});
	isosf["2018"]["eta0"].insert({"pt6", 0.997251689434});
	isosfunc["2018"]["eta0"].insert({"pt6", 0.000464922075528});
	isosf["2018"].insert({"eta1", { }});
	isosfunc["2018"].insert({"eta1", { }});
	isosf["2018"]["eta1"].insert({"pt0", 0.995734572411});
	isosfunc["2018"]["eta1"].insert({"pt0", 0.00451470407422});
	isosf["2018"]["eta1"].insert({"pt1", 0.999952435493});
	isosfunc["2018"]["eta1"].insert({"pt1", 0.00344268073099});
	isosf["2018"]["eta1"].insert({"pt2", 0.994749605656});
	isosfunc["2018"]["eta1"].insert({"pt2", 0.00121291666229});
	isosf["2018"]["eta1"].insert({"pt3", 0.997374176979});
	isosfunc["2018"]["eta1"].insert({"pt3", 0.000493558263891});
	isosf["2018"]["eta1"].insert({"pt4", 0.997357130051});
	isosfunc["2018"]["eta1"].insert({"pt4", 0.000353874788895});
	isosf["2018"]["eta1"].insert({"pt5", 0.998803734779});
	isosfunc["2018"]["eta1"].insert({"pt5", 0.000779018188443});
	isosf["2018"]["eta1"].insert({"pt6", 0.999072432518});
	isosfunc["2018"]["eta1"].insert({"pt6", 0.000761099328931});
	isosf["2018"].insert({"eta2", { }});
	isosfunc["2018"].insert({"eta2", { }});
	isosf["2018"]["eta2"].insert({"pt0", 1.00893306732});
	isosfunc["2018"]["eta2"].insert({"pt0", 0.00215371702571});
	isosf["2018"]["eta2"].insert({"pt1", 1.00585222244});
	isosfunc["2018"]["eta2"].insert({"pt1", 0.00162257203645});
	isosf["2018"]["eta2"].insert({"pt2", 1.00421142578});
	isosfunc["2018"]["eta2"].insert({"pt2", 0.000773090970702});
	isosf["2018"]["eta2"].insert({"pt3", 1.00273871422});
	isosfunc["2018"]["eta2"].insert({"pt3", 0.000432292968291});
	isosf["2018"]["eta2"].insert({"pt4", 1.00222158432});
	isosfunc["2018"]["eta2"].insert({"pt4", 0.000329537765905});
	isosf["2018"]["eta2"].insert({"pt5", 1.0002669096});
	isosfunc["2018"]["eta2"].insert({"pt5", 0.000637904452355});
	isosf["2018"]["eta2"].insert({"pt6", 0.999244749546});
	isosfunc["2018"]["eta2"].insert({"pt6", 0.000475989494865});
	isosf["2018"].insert({"eta3", { }});
	isosfunc["2018"].insert({"eta3", { }});
	isosf["2018"]["eta3"].insert({"pt0", 1.01315510273});
	isosfunc["2018"]["eta3"].insert({"pt0", 0.00358788386401});
	isosf["2018"]["eta3"].insert({"pt1", 1.01465427876});
	isosfunc["2018"]["eta3"].insert({"pt1", 0.00230760746493});
	isosf["2018"]["eta3"].insert({"pt2", 1.00774550438});
	isosfunc["2018"]["eta3"].insert({"pt2", 0.00526526609003});
	isosf["2018"]["eta3"].insert({"pt3", 1.00828564167});
	isosfunc["2018"]["eta3"].insert({"pt3", 0.000660269843038});
	isosf["2018"]["eta3"].insert({"pt4", 1.00419199467});
	isosfunc["2018"]["eta3"].insert({"pt4", 0.000765544838018});
	isosf["2018"]["eta3"].insert({"pt5", 1.00220608711});
	isosfunc["2018"]["eta3"].insert({"pt5", 0.00132121170101});
	isosf["2018"]["eta3"].insert({"pt6", 1.00301527977});
	isosfunc["2018"]["eta3"].insert({"pt6", 0.0011208950482});

}

#endif
