#!/bin/bash

SCRAMARCH=slc7_amd64_gcc700
CMSSWVERSION=CMSSW_10_2_13

DIR=$1
YEAR=$2 # all, 2018, 2017, 2016APV, 2016nonAPV
DATA=$3 # 0, 1
BKG=$4 # 0, 1
SIG=$5 # 0, 1
BFF=$6 # 0, 1
SAM=$7 # all, data, ttbar, DYbb, ZToMuMu, VV, tW, tZq, TTX, Y3, DY3, DYp3, B3mL2, TTv7, DYv7, BFF
while ! [ -z "$8" ]; do
    FLAGS="$FLAGS $8"; shift;
done

function stageout {
    COPY_SRC=$1
    COPY_DEST=$2
    retries=0
    COPY_STATUS=1
    until [ $retries -ge 10 ]
    do
        echo "Stageout attempt $((retries+1)): env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-copy -p -f -t 7200 --verbose --checksum ADLER32 ${COPY_SRC} ${COPY_DEST}"
        env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-copy -p -f -t 7200 --verbose --checksum ADLER32 ${COPY_SRC} ${COPY_DEST}
        COPY_STATUS=$?
        if [ $COPY_STATUS -ne 0 ]; then
            echo "Failed stageout attempt $((retries+1))"
        else
            echo "Successful stageout with $retries retries"
            break
        fi
        retries=$[$retries+1]
        echo "Sleeping for 5m"
        sleep 5m
    done
    if [ $COPY_STATUS -ne 0 ]; then
        echo "Removing output file because gfal-copy crashed with code $COPY_STATUS"
        env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-rm --verbose ${COPY_DEST}
        REMOVE_STATUS=$?
        if [ $REMOVE_STATUS -ne 0 ]; then
            echo "Uhh, gfal-copy crashed and then the gfal-rm also crashed with code $REMOVE_STATUS"
            echo "You probably have a corrupt file sitting on hadoop now."
            exit 1
        fi
    fi
}

source /cvmfs/cms.cern.ch/cmsset_default.sh

tar xvf package.tar.gz
cd ZPrimeSnT/
export SCRAM_ARCH=${SCRAMARCH} && scramv1 project CMSSW ${CMSSWVERSION}
cd ${CMSSWVERSION}/src
cmsenv
mv ../../PhysicsTools/ .
scram b -j

cd ../.. # Get back to ZPrimeSnT/
cd cpp/
bash runOutput_Zp.sh $DIR $YEAR $DATA $BKG $SIG $BFF $SAM $FLAGS

for FILE in $(ls $DIR);
do
  echo "File $FILE to be copied..."
  echo ""
  COPY_SRC="file://`pwd`/$DIR/$FILE"
  COPY_DEST="davs://redirector.t2.ucsd.edu:1095/store/user/$USER/ZPrimeSnTOutput/$DIR/$FILE"
  stageout $COPY_SRC $COPY_DEST
done;
