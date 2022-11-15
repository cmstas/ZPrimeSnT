#!/bin/bash

export X509_USER_PROXY=$(voms-proxy-info -path)

usage()
{
    echo "Usage:"
    echo ""
    echo "  sh utils/condor_limits/runLimits_onCondor.sh input_dir output_dir"
    echo ""
    echo "The output_dir will be created in /ceph/cms/store/user/$USER/ZPrimeSnTOutput/"
    echo "Control the jobs to be run by editing runLimits_onCondor.sub"
    echo ""
    exit
}

if [ -z $1 ]; then usage; fi

export ZPRIMESNTINPUTDIRLIM=$1
export ZPRIMESNTOUTPUTDIRLIM=$2
export HOMEDIR=$PWD

mkdir -p utils/condor_limits/plotting_logs
mkdir -p /ceph/cms/store/user/$USER/ZPrimeSnTOutput/$ZPRIMESNTOUTPUTDIRLIM

sh utils/condor_limits/create_package.sh

condor_submit utils/condor_limits/runLimits_onCondor.sub
