#!/bin/bash

# This is a script to run the initial cross section stage in parallel for the different samples.
# Parallellization is needed because running over several hypotheses and mass points can take up to a day otherwise.

nthreads=-1
printhelp=0
outdir=""
mcdir=""
for fargo in "$@";do
  fcnargname=""
  farg="${fargo//\"}"
  fargl="$(echo $farg | awk '{print tolower($0)}')"
  if [[ "$fargl" == "outdir="* ]];then
    fcnargname="$farg"
    fcnargname="${fcnargname#*=}"
    outdir="$fcnargname"
  elif [[ "$fargl" == "mcdir="* ]];then
    fcnargname="$farg"
    fcnargname="${fcnargname#*=}"
    mcdir="$fcnargname"
  elif [[ "$fargl" == "nthreads="* ]];then
    fcnargname="$farg"
    fcnargname="${fcnargname#*=}"
    let nthreads=${fcnargname}
  elif [[ "$fargl" == "help" ]];then
    let printhelp=1
  fi
done

if [[ ${printhelp} -eq 1 ]] || [[ -z "${outdir}" ]] || [[ -z "${mcdir}" ]] || [[ ${nthreads} -le 1 ]] || [[ -z "${STY+x}" ]]; then
  echo "$0 usage:"
  echo " - help: Print this help"
  echo " - outdir: Output directory, '.' for example. Mandatory."
  echo " - mcdir: Directory of (private) MC files, '/ceph/cms/store/user/usarica/Offshell_2L2Nu/PrivateMC/220404' for example. Mandatory."
  echo " - nthreads: Number of threads, has to be greater than 1. Mandatory."
  echo "Note: You must run this script in a screen."
  exit 0
fi

# In case the user gives a relative output path...
outdir=$(readlink -f $outdir)


job_limit(){
  local joblist=( )
  # Test for single positive integer input
  if [[ $# -eq 1 ]] && [[ $1 =~ ^[1-9][0-9]*$ ]]
  then
    # Check number of running jobs
    joblist=( $(jobs -rp) )
    while [[ ${#joblist[*]} -ge $1 ]]; do
      # Wait for any job to finish
      command='wait '${joblist[0]}
      for job in ${joblist[@]:1}; do
        command+=' || wait '$job
      done
      eval ${command}
      joblist=( $(jobs -rp) )
    done
  fi
}


cd $(dirname ${BASH_SOURCE[0]})

eval $(./setupIvy.sh env)

scrlib="loadIvy.C"
scrname="compute_xsec_acceff_params.cc"
fcnname=compute_initial_xsec
# Need triple backslashes because we are letting a python script run the ROOT interpreter, so one pair is lost when passing the --command argument.
STRARGS="\\\"<sample>\\\",\\\"${outdir}\\\",\\\"${mcdir}\\\""
# First, just compile the script without doing anything else.
runGenericROOTCommand.py --loadlib=${scrlib} --script=${scrname} --onlyrecompile
for ss in $(ls ${mcdir}); do
  runGenericROOTCommand.py --loadlib=${scrlib} --script=${scrname} --function=${fcnname} --command="${STRARGS/<sample>/$ss}" &
  job_limit $nthreads
done

wait
