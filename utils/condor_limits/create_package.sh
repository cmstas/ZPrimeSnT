#!/bin/bash

INDIR="datacards_all*Oct-*-2022"

# Start from ZPrimeSnT/.
rm tmp_create_package/ -rf
mkdir -p tmp_create_package
cd tmp_create_package

mkdir -p ZPrimeSnT
cp ../HiggsAnalysis/ ZPrimeSnT/. -r # Copy relevant folders
tar -cf - ../combineScripts ../${INDIR} | tar -xf - -C ZPrimeSnT/. # Copy cpp folder without the plot folders

tar -chJf package.tar.gz ZPrimeSnT

mv package.tar.gz ../.
rm -rf tmp_create_package
