#!/bin/bash

usage()
{
    echo "Usage:"
    echo ""
    echo "  sh utils/condor/runOutput_Zp_onCondor.sh output_dir"
    echo ""
    echo "The output_dir will be created in /ceph/cms/store/user/$USER/ZPrimeSnTOutput/"
    echo "Control the jobs to be run by editing runOutput_Zp_onCondor.sub"
    echo ""
    exit
}

if [ -z $1 ]; then usage; fi

export ZPRIMESNTOUTPUTDIR=$1

mkdir -p utils/condor/plotting_logs
mkdir -p /ceph/cms/store/user/$USER/ZPrimeSnTOutput/$ZPRIMESNTOUTPUTDIR

sh utils/condor/create_package.sh

condor_submit utils/condor/runOutput_Zp_onCondor.sub
