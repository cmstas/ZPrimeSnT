##this is a very silly script to turn the golden json into the txt format needed by the goodrun.cc tool
import os
import sys
import argparse
import json

parser = argparse.ArgumentParser()
parser.add_argument("--filename", help="filename")
args = parser.parse_args()


with open(args.filename) as f:
    data = json.load(f)
    
    grl = []
    for j in data:
        for jj in data[j]:
            string = str(j) + " " + str(jj[0]) + " " + str(jj[1]) + "\n"
            grl.append(string)
   
    
    print args.filename
    outname = "./"+args.filename.strip(".txt") + "_formatted.txt"
    
    outfile = open(outname, "w")
    for j in grl:
        outfile.write(j)
    

