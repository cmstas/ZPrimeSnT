#!/bin/bash

SCRAMARCH=slc7_amd64_gcc700
CMSSWVERSION=CMSSW_10_2_13

# Start from ZPrimeSnT/.
rm tmp_create_package/ -rf
mkdir -p tmp_create_package
cd tmp_create_package

mkdir -p ZPrimeSnT
cp ../NanoCORE ../data/ ../utils/ ../${CMSSWVERSION}/src/PhysicsTools/ ZPrimeSnT/. -r # Copy relevant folders
tar -cf - --exclude=temp_data* ../cpp | tar -xf - -C ZPrimeSnT/. # Copy cpp folder without the plot folders

cd ZPrimeSnT/NanoCORE
make -j # If there is a need to make clean, do it locally

cd ../.. # Go back to tmp_create_package/
tar -chJf package.tar.gz ZPrimeSnT

mv package.tar.gz ../.
#rm -rf tmp_create_package # Leave the package be to able to easily check what is done
