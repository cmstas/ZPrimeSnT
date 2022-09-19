#!/bin/bash

cd ${CMSSW_BASE}/src/
eval `scramv1 runtime -sh`
cd ${CMSSW_BASE}/../cpp

DIR=$1
YEAR=$2 # all, 2018, 2017, 2016APV, 2016nonAPV
DATA=$3 # 0, 1
BKG=$4 # 0, 1
SIG=$5 # 0, 1
BFF=$6 # 0, 1
SAM=$7 # all, data, ttbar, DYbb, ZToMuMu, VV, tW, tZq, TTX, Y3, DY3, DYp3, B3mL2, TTv7, DYv7, BFF
while ! [ -z "$8" ]; do
    FLAGS="$FLAGS, $8"; shift;
done
COMMAND="root -l -b -q 'doAll_Zp.C(\"$DIR\", \"$YEAR\", $DATA, $BKG, $SIG, $BFF, \"$SAM\"$FLAGS)'"

echo ""
echo "Arguments:"
echo "----------"
echo "Directory = "$DIR
echo "Year = "$YEAR
echo "Run data = "$DATA
echo "Run bkg = "$BKG
echo "Run signal = "$SIG
echo "Run BFF = "$BFF
echo "Sample = "$SAM
echo "Variation flags = "${FLAGS#", "}
echo ""

eval $COMMAND
