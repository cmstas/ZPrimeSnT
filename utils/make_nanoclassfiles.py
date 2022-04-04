#!/usr/bin/env python

import ROOT as r
import argparse
import sys
import os
import itertools
import fnmatch

USE_DEFINES_FOR_ARRAY_SIZES = True

PREDEFINED_ARRAY_SIZES = {
        "NSV_MAX" : 24,
        "NSOFTACTIVITYJET_MAX" : 21,
        "NLHESCALEWEIGHT_MAX" : 30,
        "NCORRT1METJET_MAX" : 102,
        "NMUON_MAX" : 90,
        "NGENJET_MAX" : 60,
        "NPSWEIGHT_MAX" : 15,
        "NBOOSTEDTAU_MAX" : 12,
        "NLHEPART_MAX" : 24,
        "NTAU_MAX" : 90,
        "NISOTRACK_MAX" : 33,
        "NLHEPDFWEIGHT_MAX" : 312,
        "NFSRPHOTON_MAX" : 9,
        "NLOWPTELECTRON_MAX" : 18,
        "NOTHERPV_MAX" : 12,
        "NTRIGOBJ_MAX" : 117,
        "NSUBJET_MAX" : 33,
        "NSUBGENJETAK8_MAX" : 42,
        "NGENVISTAU_MAX" : 12,
        "NGENJETAK8_MAX" : 24,
        "NELECTRON_MAX" : 90,
        "NFATJET_MAX" : 18,
        "NJET_MAX" : 250,
        "NGENISOLATEDPHOTON_MAX" : 15,
        "NGENDRESSEDLEPTON_MAX" : 15,
        "NGENPART_MAX" : 402,
        "NPHOTON_MAX" : 27,
        "NLHEREWEIGHTINGWEIGHT_MAX" : 50,
        "NLHEWEIGHT_MAX" : 256,
        }

def get_cc_top(ginfo,binfo):
    yield "#include \"{classname}.h\"".format(**ginfo)
    yield "{classname} {objectname};".format(**ginfo)

def get_cc_init(ginfo,binfo):
    yield "void {classname}::Init(TTree *tree) {{".format(**ginfo)
    for bi in binfo:
        if "LorentzVector" in bi["typename"]: continue
        yield "    b_{name}_ = tree->GetBranch(\"{name}\");".format(**bi)
        yield "    if (b_{name}_) {{ b_{name}_->SetAddress(&{name}_); }}".format(**bi)
    yield "    ParseYear(tree);".format(**bi)
    yield "}"

def get_cc_extra(ginfo,binfo):
    yield """
void {classname}::SetYear(int year) {{
    year_ = year;
}}

void Nano::ParseYear(TTree* tree) {{
    // if (year_ != 0) return; // disabled so that per root file that it reads it will always reset it to the correct year.
    year_ = -999;
    TString full_file_path = TString(((TFile*) tree->GetCurrentFile())->GetName());
    if (full_file_path.Contains("RunIIAutumn18NanoAOD")) year_ = 2018;
    else if (full_file_path.Contains("RunIIFall17NanoAOD")) year_ = 2017;
    else if (full_file_path.Contains("RunIISummer16NanoAOD")) year_ = 2016;
    // Ultra-legacy
    else if (full_file_path.Contains("RunIISummer20UL18")) year_ = 2018;
    else if (full_file_path.Contains("RunIISummer20UL17")) year_ = 2017;
    else if (full_file_path.Contains("RunIISummer20UL16")) year_ = 2016;
    // Ultra-legacy
    else if (full_file_path.Contains("RunIISummer19UL18")) year_ = 2018;
    else if (full_file_path.Contains("RunIISummer19UL17")) year_ = 2017;
    else if (full_file_path.Contains("RunIISummer19UL16")) year_ = 2016;
    // Data
    else if (full_file_path.Contains("Run2018")) year_ = 2018;
    else if (full_file_path.Contains("Run2017")) year_ = 2017;
    else if (full_file_path.Contains("Run2016")) year_ = 2016;
    else throw std::runtime_error("Nano::parseYear():: ERROR - Failed to recognize which year this NanoAOD is !\\nPlease make sure the path has one of the following keywords:\\n  2016: 'Run2016' or 'RunIISummer16NanoAOD' or 'RunIISummer20UL16'\\n  2017: 'Run2017' or 'RunIIFall17NanoAOD' or 'RunIISummer20UL17'\\n  2018: 'Run2018' or 'RunIIAutumn18NanoAOD' or 'RunIISummer20UL18'\\nOR, use Nano::SetYear(int year) before Nano::Init()");
}}


const Int_t &{classname}::year() {{
    return year_;
}}

Bool_t {classname}::isData() {{
    return !((bool)b_GenPart_pt_);
}}

""".format(**ginfo)



def get_cc_printusage(ginfo,binfo):
    yield "void {classname}::PrintUsage() {{".format(**ginfo)
    for bi in binfo:
        yield "    std::cout << \"{name} (uncached/cached calls): \" << counter_uncached_{name}_ << \" / \" << counter_cached_{name}_ << std::endl;;".format(**bi)
    yield "}"

def get_cc_getentry(ginfo,binfo):
    yield "void {classname}::GetEntry(unsigned int idx) {{".format(**ginfo)
    yield "    index = idx;"
    for bi in binfo:
        yield """    loaded_{name}_ = false;""".format(**bi)
    yield "}"

def get_cc_getfunctions(ginfo,binfo):
    for bi in binfo:
        p = { "name": bi["name"], "type": bi["typename"], "classname": ginfo["classname"] }

        yield "const {type} &{classname}::{name}() {{".format(**p)
        if profiling:
            yield "    if (!loaded_{name}_) counter_uncached_{name}_++;""".format(**bi)
            yield "    else counter_cached_{name}_++;""".format(**bi)
        yield "    if (!loaded_{name}_) {{".format(**p)
        if "LorentzVector" in bi["typename"]:
            if bi["is_array"]:
                yield "        v_{name}_.clear();".format(**p)
                yield "        vector<float> pts = {classname}::{name}();".format(classname=p["classname"],name=p["name"].replace("_p4","_pt"))
                yield "        vector<float> etas = {classname}::{name}();".format(classname=p["classname"],name=p["name"].replace("_p4","_eta"))
                yield "        vector<float> phis = {classname}::{name}();".format(classname=p["classname"],name=p["name"].replace("_p4","_phi"))
                yield "        vector<float> masses = {classname}::{name}();".format(classname=p["classname"],name=p["name"].replace("_p4","_mass"))
                yield "        for (unsigned int i=0; i < pts.size(); i++) {"
                yield "            v_{name}_.push_back(LorentzVector(pts[i],etas[i],phis[i],masses[i]));".format(**p)
                yield "        }"
            else:
                yield "        v_{name}_.clear();".format(**p)
                yield "        v_{name}_ = LorentzVector(*{name_pt}_,*{name_eta}_,*{name_phi}_,*{name_mass}_);".format(
                        name = p["name"],
                        name_pt = p["name"].replace("_p4","_pt"),
                        name_eta = p["name"].replace("_p4","_eta"),
                        name_phi = p["name"].replace("_p4","_phi"),
                        name_mass = p["name"].replace("_p4","_mass"),
                        )
        else:
            yield "        if (!b_{name}_) throw std::runtime_error(\"{name} branch doesn't exist\");".format(**p)
            if bi["is_array"]:
                yield "        int bytes = b_{name}_->GetEntry(index);".format(**p)
                yield "        v_{name}_ = {type}({name}_,{name}_+bytes/sizeof({name}_[0]));".format(**p)
            else:
                yield "        b_{name}_->GetEntry(index);".format(**p)
        yield "        loaded_{name}_ = true;".format(**p)
        yield "    }"
        if bi["is_array"]:
            yield "    return v_{name}_;".format(**p)
        else:
            yield "    return {name}_;".format(**p)
        yield "}"

def get_cc_tas(ginfo,binfo,extra=None):
    yield "namespace {namespace} {{".format(**ginfo)
    for bi in binfo:
        p = { "name": bi["name"], "type": bi["typename"], "objectname": ginfo["objectname"] }
        yield "    const {type} &{name}() {{ return {objectname}.{name}(); }}".format(**p)
    if extra:
        for x in extra(): yield x
    yield "}"

def get_h_top(ginfo,binfo):
    yield "// -*- C++ -*-"
    yield "// Generated with args: {args}".format(**ginfo)
    yield "#ifndef {classname}_H".format(**ginfo)
    yield "#define {classname}_H".format(**ginfo)
    for include in [
            "Math/LorentzVector.h",
            "Math/GenVector/PtEtaPhiM4D.h",
            "Math/Point3D.h",
            "TMath.h",
            "TBranch.h",
            "TTree.h",
            "TH1F.h",
            "TFile.h",
            "TBits.h",
            "vector",
            "unistd.h",
            "chrono",
            "ctime",
            "numeric",
            "TTreeReader.h",
            "TTreeReaderValue.h",
            "TTreeReaderArray.h",
            ]:
        yield "#include \"{}\"".format(include)
    yield ""
    yield "typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > LorentzVector;"
    yield "#define makeP4(Collection, idx) LorentzVector(Collection##_pt[idx],Collection##_eta[idx],Collection##_phi[idx],Collection##_mass[idx]);"
    yield "#define RANGE(a, b) unsigned a=0; a<b; a++"
    yield ""
    if USE_DEFINES_FOR_ARRAY_SIZES:
        defines = {}
        for b in binfo:
            if not b["ndatamacroname"]: continue
            if b["ndatamacroname"] in defines: continue
            multiplier = 3
            defines[b["ndatamacroname"]] = dict(ndatamacroname=b["ndatamacroname"], collectionname=b["collectionname"], ndata=int(multiplier*b["ndata"]))
            if b["ndatamacroname"] in PREDEFINED_ARRAY_SIZES.keys():
                defines[b["ndatamacroname"]]["ndata"] = PREDEFINED_ARRAY_SIZES[b["ndatamacroname"]]
        for v in defines.values():
            yield "#define {ndatamacroname} {ndata} // for {collectionname}_* collection".format(**v)
    yield ""
    yield "using namespace std;"

def get_h_class(ginfo,binfo):
    yield "class {classname} {{".format(**ginfo)
    yield "private:"
    yield "protected:"
    yield "    unsigned int index;"
    for bi in binfo:
        if bi["is_array"]:
            if "LorentzVector" not in bi["typename"]:
                if USE_DEFINES_FOR_ARRAY_SIZES:
                    yield """    {typename_novec} {name}_[{ndatamacroname}];""".format(**bi)
                else:
                    yield """    {typename_novec} {name}_[{ndata}];""".format(**bi)
            yield """    {typename} v_{name}_;""".format(**bi)
        else:
            yield """    {typename} {name}_;""".format(**bi)
        yield """    TBranch *b_{name}_;""".format(**bi)
        yield """    bool loaded_{name}_;""".format(**bi)
        if profiling:
            yield """    unsigned int counter_cached_{name}_;""".format(**bi)
            yield """    unsigned int counter_uncached_{name}_;""".format(**bi)
    yield """    Int_t year_;"""
    yield "public:"
    yield "    void Init(TTree *tree);"
    yield "    void SetYear(int year);"
    yield "    void ParseYear(TTree *tree);"
    yield "    void PrintUsage();"
    yield "    void GetEntry(unsigned int idx);"
    for bi in binfo:
        yield "    const {typename} &{name}();".format(**bi)
    yield "    Bool_t isData();"
    yield "    const Int_t &year();"
    yield "};"
    yield ""
    yield "#ifndef __CINT__"
    yield "extern {classname} {objectname};".format(**ginfo)
    yield "#endif"

def get_h_tas(ginfo,binfo,extra=None):
    yield "namespace {namespace} {{".format(**ginfo)
    for bi in binfo:
        yield "    const {typename} &{name}(); // {desc}".format(**bi)
    if extra:
        for x in extra(): yield x
    yield "}"
    yield "#endif"

def get_looper_ScanChain(ginfo):
    yield """#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "{classname}.h"
#include "tqdm.h"

using namespace std;

int ScanChain(TChain *ch) {{

    TH1F * h1 = new TH1F("met", "met", 50, 0, 300);

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    while ( (currentFile = (TFile*)fileIter.Next()) ) {{
        TFile *file = TFile::Open( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("{treename}");
        TString filename(currentFile->GetTitle());
        tree->SetCacheSize(128*1024*1024);
        tree->SetCacheLearnEntries(10);
        {objectname}.Init(tree);

        // Can also make custom formulas to eval (but dunno how slow this is)
        TTreeFormula formula("f1", "MET_pt>50", tree);

        for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {{
            {objectname}.GetEntry(event);
            tree->LoadTree(event);
            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            // Analysis code

            // auto jets = {namespace}::GetVLV("Jet_p4"); if (jets.size() > 0) h1->Fill(jets[0].pt());
            // auto jets = {namespace}::Jet_p4(); if (jets.size() > 0) h1->Fill(jets[0].pt());
            // auto jetpts = {namespace}::Jet_pt(); if (jetpts.size() > 0) h1->Fill(jetpts[0]);
            // for (auto& s : {{"MET_pt", "CaloMET_pt", "GenMET_pt", "RawMET_pt", "TkMET_pt"}}) h1->Fill({namespace}::GetF(s));
            // bool highmet = formula.EvalInstance();
            h1->Fill({namespace}::MET_pt());

        }} // Event loop
        delete file;
    }} // File loop
    bar.finish();

    TFile* f1 = new TFile("output.root", "RECREATE");
    std::cout <<  "Mean of h1: " << h1->GetMean() <<  std::endl;
    h1->Write();
    f1->Write();
    f1->Close();
    return 0;
}}
""".format(**ginfo)


def get_looper_doAll(ginfo):
    yield "{"
    yield "    gROOT->ProcessLine(\".L {classname}.cc+\");".format(**ginfo)
    yield "    gROOT->ProcessLine(\".L ScanChain.C+\");".format(**ginfo)
    yield "    TChain *ch = new TChain(\"{treename}\");".format(**ginfo)
    yield "    ch->Add(\"{filename}\");".format(**ginfo)
    yield "    ScanChain(ch);"
    yield "}"

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="filename(s) to make classfile on, separated by comman")
    parser.add_argument("-t", "--tree", help="treename (default: Events)", default="Events")
    parser.add_argument("-n", "--namespace", help="namespace (default: tas)", default="tas")
    parser.add_argument("-o", "--objectname", help="objectname (default: nt)", default="nt")
    parser.add_argument("-c", "--classname", help="classname (default: Nano)", default="Nano")
    parser.add_argument("-l", "--looper", help="make a looper as well", default=False, action="store_true")
    parser.add_argument("-p", "--profiling", help="make extra functions to help performance profiling", default=False, action="store_true")
    parser.add_argument("-b", "--branches", help="use only these specified (comma separated) branches", default="")
    parser.add_argument("-e", "--exclude", help="exclude branches matching patterns separated by , (e.g., \"HLT_*,*_pt\")", default="")
    args = parser.parse_args()

    flist = [os.path.abspath(f) for f in args.filename.strip().split(',')]
    treename = args.tree
    classname = args.classname
    objectname = args.objectname
    namespace = args.namespace
    make_looper = args.looper
    profiling = args.profiling
    excludes = args.exclude
    filter_branches = args.branches.strip().split(",") if args.branches.strip() else []
    exclude_patterns = args.exclude.strip().split(",") if args.exclude.strip() else []

    download_cpptqdm = True

    # filter_branches = ["Muon_pt","MET_pt","Muon_phi","Muon_eta","Muon_mass"]

    ginfo = {
            "treename": treename,
            "classname": classname,
            "namespace": namespace,
            "objectname": objectname,
            "filename": ','.join(flist),
            "args": " ".join(sys.argv[1:]).replace(args.filename.strip(),','.join(flist)),
            }

    d_branch_info = {}
    s_brnames = set()

    for fname in flist:
        f = r.TFile(fname)
        t = f.Get(treename)

        branches = list(t.GetListOfBranches())

        for branch in branches:
            title = branch.GetTitle()
            name = branch.GetName()

            # If title has "newline" character we replace them
            title = title.replace("\n","  ")

            if name in s_brnames: continue
            s_brnames.add(name)

            if filter_branches and name not in filter_branches: continue
            if exclude_patterns:
                if any(fnmatch.fnmatch(name,patt) for patt in exclude_patterns): continue

            leaf = branch.GetLeaf(branch.GetName())
            leaf_title = leaf.GetTitle()
            is_array = "[" in leaf_title
            # DECLARING ARRAY WITH TOO LITTLE SPACE WILL SEGFAULT SO NEED TO BE REALLY CAREFUL
            # FIXME figure out better way. tripling is not a solution
            # ndata = 3*leaf.GetNdata()
            # sys.exit("DECLARING ARRAY WITH TOO LITTLE SPACE WILL SEGFAULT SO NEED TO BE REALLY CAREFUL\nIF ONE REPLACES THE NanoCORE/Nano.h/cc USING THIS OTHER USERS WORK ON THE SETTING WILL GET OVERWRITTEN\nIF YOU HAVE ANY QUESTIONS PLEASE CONTACT PHILIP CHANG <philip@ucsd.edu>\n")
            ndata = leaf.GetNdata()
            collectionname = None
            ndatamacroname = None
            if is_array:
                collectionname = leaf_title.split("_",1)[0].split("[",1)[0]
                ndatamacroname = "N{}_MAX".format(collectionname.upper())

            typename = leaf.GetTypeName()
            tmap = {
                    "Float_t": "float",
                    "Int_t": "int",
                    "Bool_t": "bool",
                    }
            typename = tmap.get(typename,typename)
            typename_novec = typename[:]
            if is_array:
                leaf_title = "{}[{}]".format(leaf_title.split("[")[0],ndata)
                typename = "vector<{}>".format(typename)

            d_branch_info[name] = {
                    "desc": title,
                    "name": name,
                    "is_array": is_array,
                    "typename": typename,
                    "typename_novec": typename_novec,
                    "ndata": ndata,
                    "leaf_title": leaf_title,
                    "collectionname": collectionname,
                    "ndatamacroname": ndatamacroname,
                    }

    names = d_branch_info.keys()
    for_p4s = []
    for prefix,sub in itertools.groupby(sorted(names), key=lambda x:x.split("_")[0]):
        if len(set([prefix+y for y in ["_pt", "_eta", "_phi", "_mass"]]) & set(sub)) == 4:
            bi = dict(d_branch_info[prefix+"_pt"])
            bi["typename"] = bi["typename"].replace("float","LorentzVector")
            bi["typename_novec"] = bi["typename_novec"].replace("float","LorentzVector")
            bi["name"] = bi["name"].replace("_pt","_p4")
            bi["leaf_title"] = bi["leaf_title"].replace("_pt","_p4")
            bi["desc"] = "from {}_pt,eta,phi,mass".format(prefix)
            for_p4s.append(bi)

    vals = d_branch_info.values() + for_p4s
    binfo = sorted(vals, key=lambda x: x["name"])

    types = set(b["typename"] for b in binfo if "U" not in b["typename"])  # drop things like Uints
    short_map = {
            "vector<float>": "VF",
            "vector<int>": "VI",
            "vector<LorentzVector>": "VLV",
            "vector<bool>": "VB",
            "float": "F",
            "int": "I",
            "LorentzVector": "LV",
            "bool": "B",
            }

    def extra_h_tas():
        yield "    Bool_t isData();"
        yield "    const Int_t &year();"
        for t in types:
            yield "    {typename} Get{shortname}(const string &name);".format(typename=t, shortname=short_map[t])

    def extra_cc_tas():
        yield """    const Int_t &year() {{ return {objectname}.year(); }}""".format(**ginfo)
        yield """    Bool_t isData() {{ return {objectname}.isData(); }}""".format(**ginfo)
        for t in types:
            yield """    {t} Get{short}(const string &name) {{""".format(t=t,short=short_map[t])
            bsame = [x for x in binfo if x["typename"] == t]
            for ibi,bi in enumerate(bsame):
                p = { "name": bi["name"], "type": bi["typename"], "objectname": ginfo["objectname"] }
                if ibi == 0:
                    yield "        if (name == \"{name}\") return {objectname}.{name}();".format(**p)
                elif ibi == len(bsame)-1:
                    yield "        return {t}();".format(t=t)
                else:
                    yield "        else if (name == \"{name}\") return {objectname}.{name}();".format(**p)
            if len(bsame) < 2:
                yield "        return {t}();".format(t=t)
            yield "    }"

    with open("{}.cc".format(ginfo["classname"]), "w") as fhout:
        fhout.write("\n".join(get_cc_top(ginfo,binfo)))
        fhout.write("\n\n")
        fhout.write("\n".join(get_cc_init(ginfo,binfo)))
        fhout.write("\n".join(get_cc_extra(ginfo,binfo)))
        fhout.write("\n\n")
        if profiling:
            fhout.write("\n".join(get_cc_printusage(ginfo,binfo)))
            fhout.write("\n\n")
        fhout.write("\n".join(get_cc_getentry(ginfo,binfo)))
        fhout.write("\n\n")
        fhout.write("\n".join(get_cc_getfunctions(ginfo,binfo)))
        fhout.write("\n\n")
        fhout.write("\n".join(get_cc_tas(ginfo,binfo,extra=extra_cc_tas)))

    with open("{}.h".format(ginfo["classname"]), "w") as fhout:
        fhout.write("\n".join(get_h_top(ginfo,binfo)))
        fhout.write("\n\n")
        fhout.write("\n".join(get_h_class(ginfo,binfo)))
        fhout.write("\n\n")
        fhout.write("\n".join(get_h_tas(ginfo,binfo,extra=extra_h_tas)))

    if os.path.isfile("ScanChain.C") or os.path.isfile("doAll.C"):
        print(">>> Hey, you already have a looper here! Not overwriting the looper. Delete to regenerate.")
        make_looper = False

    if make_looper:

        with open("ScanChain.C", "w") as fhout:
            fhout.write("\n".join(get_looper_ScanChain(ginfo)))

        with open("doAll.C", "w") as fhout:
            fhout.write("\n".join(get_looper_doAll(ginfo)))

    if download_cpptqdm:

        if not os.path.exists("tqdm.h"):
            os.system("curl -O https://raw.githubusercontent.com/aminnj/cpptqdm/master/tqdm.h >& /dev/null")

