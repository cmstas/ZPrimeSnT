#!/bin/bash

SCRAMARCH=slc7_amd64_gcc700
CMSSWVERSION=CMSSW_10_2_13

# Start from ZPrimeSnT/.
rm -rf tmp_test_package/
mkdir -p tmp_test_package/
cd tmp_test_package/

tar xf $1
cd ZPrimeSnT/
export SCRAM_ARCH=${SCRAMARCH} && scramv1 project CMSSW ${CMSSWVERSION}
cd ${CMSSWVERSION}/src
cmsenv
git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
scram b -j

cd ../.. # Get back to ZPrimeSnT/
# Try running a command
cd cpp/
bash runOutput_Zp.sh temp_data_test 2016nonAPV 0 1 0 0 tZq
