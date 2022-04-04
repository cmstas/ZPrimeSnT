#!/usr/bin/env python

from __future__ import print_function

import json
try:
    from urllib2 import urlopen
    from urllib import urlencode
except:
    # python3 compatibility
    from urllib.request import urlopen
    from urllib.parse import urlencode
import sys
import argparse
import socket
import time
import glob

"""
examples:
       dis_client.py -t snt "*,cms3tag=CMS3_V08-00-01 | grep dataset_name,nevents_in, nevents_out"
           - this searches for all samples with the above tag in all Twikis and only prints out dataset_name, nevents_out

       dis_client.py /GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM
           - prints out basic information (nevents, file size, number of files, number of lumi blocks) for this dataset

       dis_client.py -t files /GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM
           - prints out filesize, nevents, location for a handful of files for this dataset

       dis_client.py -t files -d /GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM
           - prints out above information for ALL files

Or you can import dis_client and make a query using online syntax and get a json via:
       dis_client.query(q="..." [, typ="basic"] [, detail=False])
"""

BASEURL = "http://uaf-7.t2.ucsd.edu:50010/dis/serve"

def query(q, typ="basic", detail=False, timeout=999):
    query_dict = {"query": q, "type": typ, "short": "" if detail else "short"}
    url = '%s?%s' % (BASEURL, urlencode(query_dict))

    data = {}

    try:
        content =  urlopen(url,timeout=timeout).read()
        data = json.loads(content)
    except: 
        print("Failed to perform URL fetching and decoding!")

    return data

def listofdicts_to_table(lod): # pragma: no cover
    colnames = list(set(sum([thing.keys() for thing in lod],[])))

    # key is col name and value is maximum length of any entry in that column
    d_colsize = {}
    for thing in lod:
        for colname in colnames:
            val = str(thing.get(colname,""))
            if colname not in d_colsize: d_colsize[colname] = len(colname)+1
            d_colsize[colname] = max(len(val)+1, d_colsize[colname])

    # sort colnames from longest string lengths to shortest
    colnames = sorted(colnames, key=d_colsize.get, reverse=True)

    try:
        from pytable import Table
        if not sys.stdout.isatty():
            raise Exception

        tab = Table()
        tab.set_column_names(colnames)

        for row in lod:
            tab.add_row([row.get(colname) for colname in colnames])
        tab.sort(column=colnames[0], descending=False)

        return "".join(tab.get_table_string())

    except:
        buff = ""
        header = ""
        for icol,colname in enumerate(colnames):
            header += ("%%%s%is" % ("-" if icol==0 else "", d_colsize[colname])) % colname
        buff += header + "\n"
        for thing in lod:
            line = ""
            for icol,colname in enumerate(colnames):
                tmp = "%%%s%is" % ("-" if icol==0 else "", d_colsize[colname])
                tmp = tmp % str(thing.get(colname,""))
                line += tmp
            buff += line + "\n"

        return buff


def get_output_string(q, typ="basic", detail=False, show_json=False, pretty_table=False, one=False): # pragma:no cover
    buff = ""
    data = query(q, typ, detail)

    if not data:
        return "URL fetch/decode failure"

    if data["status"] != "success":
        return "DIS failure: %s" % data["payload"]["failure_reason"]

    data = data["payload"]

    if show_json:
        return json.dumps(data, indent=4)


    if type(data) == dict:
        if "files" in data: data = data["files"]


    if type(data) == list:

        if pretty_table:
            buff += listofdicts_to_table(data)
        else:
            for elem in data:
                if type(elem) == dict:
                    for key in elem:
                        buff += "%s:%s\n" % (key, elem[key])
                else:
                    buff += str(elem)
                buff += "\n"

    elif type(data) == dict:
        for ikey,key in enumerate(data):
            buff += "%s: %s\n\n" % (key, data[key])

    if typ=="snt" and len(data) and one:
        onefile = glob.glob("{}/*.root".format(data[0]["location"]))[0]
        return onefile

    # ignore whitespace at end
    buff = buff.rstrip()
    return buff

def test(): # pragma: no cover

    queries = [

            {"type": "snt", "query": "/DY*/*MiniAOD*/MINIAODSIM | grep nevents_out | sort", "short":"short"},
            {"type": "snt", "query": "/G* | grep cms3tag"},
            {"type": "snt", "query": "/SingleElectron/Run2016*-PromptReco-v*/MINIAOD | grep nevents_in | stats", "short":"short"},
            {"type": "snt", "query": "/WJetsToLNu_TuneCUETP8M1_13TeV-madgr*"},
            {"type": "update_snt", "query": "dataset_name=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM,cms3tag=v2,sample_type=CMS3", "short": "short"},
            {"type": "delete_snt", "query": "dataset_name=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM,cms3tag=v2,sample_type=CMS3", "short": "short"},
            {"type": "basic", "query": "/*/Run2016*-17Jul2018-v1/MINIAOD", "short":"short"},
            {"type": "basic", "query": "/DoubleMuon/Run2016*-17Jul2018-v1/MINIAOD"},
            {"type": "dbs", "query": "https://cmsweb.cern.ch/dbs/prod/global/DBSReader/files?dataset=/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM&detail=1"},
            {"type": "chain", "query": "/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"},
            {"type": "files", "query": "/SinglePhoton/Run2016E-PromptReco-v2/MINIAOD", "short":"short"},
            {"type": "mcm", "query": "/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM | grep cross_section", "short":"short"},
            {"type": "parents", "query": "/SMS-T1tttt_mGluino-1500_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v1/MINIAODSIM"},
            {"type": "runs", "query": "/SinglePhoton/Run2016E-PromptReco-v2/MINIAOD"},
            {"type": "sites", "query": "/ZeroBias/Run2016F-17Jul2018-v1/MINIAOD", "short":"short"},
            {"type": "sites", "query": "/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"},

            ]
    green = '\033[92m'
    red = '\033[91m'
    clear = '\033[0m'
    import os
    columns = int(os.popen('stty size', 'r').read().split()[1])-20

    print(">>> Testing queries")
    for q_params in queries:
        detail = q_params.get("short","") != "short"
        to_print = "{0}: {1}{2}".format(q_params["type"], q_params["query"], " (detailed)" if detail else "")
        if len(to_print) > columns:
            to_print = to_print[:columns-3] + "..."
        t0 = time.time()
        data = query(q=q_params["query"],
                typ=q_params["type"],
                detail=detail,
                timeout=30)
        t1 = time.time()
        status = data["status"]
        startcolor = green if status == "success" else red
        print("[{0}{1}{2} ({3:.2f}s)] {4}".format(startcolor,status,clear,t1-t0,to_print))
        if status != "success":
            print(data["payload"]["failure_reason"])

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("query", help="query")
    parser.add_argument("-t", "--type", help="type of query")
    parser.add_argument("-d", "--detail", help="show more detailed information", action="store_true")
    parser.add_argument("-j", "--json", help="show output as full json", action="store_true")
    parser.add_argument("-p", "--table", help="show output as pretty table", action="store_true")
    parser.add_argument("-v", "--dev", help="use developer instance", action="store_true")
    parser.add_argument("-e", "--test", help="perform query tests", action="store_true")
    parser.add_argument("-o", "--one", help="get one file from SNT sample", action="store_true")
    args = parser.parse_args()

    if not args.type: args.type = "basic"

    if args.test:
        test()
    else:
        print(get_output_string(args.query, typ=args.type, detail=args.detail, show_json=args.json, pretty_table=args.table, one=args.one))

