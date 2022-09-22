#!/bin/bash


# Please run './setupIvy.sh help' for instructions.


(

set -euo pipefail

cd $(dirname ${BASH_SOURCE[0]})

PKGDIR="$(readlink -f ..)"
declare -i doPrintEnv=0
declare -i doPrintEnvInstr=0
declare -i printHelp=0
declare -a setupArgs=()

declare -i nSetupArgs
nSetupArgs=${#setupArgs[@]}

for farg in "$@"; do
  fargl="$(echo $farg | awk '{print tolower($0)}')"
  if [[ "$fargl" == "env" ]]; then
    doPrintEnv=1
  elif [[ "$fargl" == "envinstr" ]]; then
    doPrintEnvInstr=1
  elif [[ "$fargl" == "help" ]]; then
    printHelp=1
  else
    setupArgs+=( "$farg" ) 
  fi
done

if [[ ${printHelp} -eq 1 ]]; then
  echo "setupIvy.sh options:"
  echo
  echo "  help: Prints this message."
  echo "  envinstr: Print on-screen instructions to set environment variables."
  echo "  env: Print commands to set environment variables."
  echo
  echo "  Run ./setupIvy.sh -j [Ncores]' or just './setupIvy.sh' to set up the tools for cross section and acceptance*eff. calculations."
  echo "  Run ./setupIvy.sh clean' to clean up."
  echo
  echo "  At the end of compilation, please follow the on-screen instructions."
  exit 0
fi

if [[ -z "${CMSSW_BASE+x}" ]]; then
  echo "You must have a valid CMSSW_BASE environment variable."
  exit 1
fi


if [[ ! -d ${CMSSW_BASE}/src/IvyFramework/IvyDataTools ]]; then
  cd ${CMSSW_BASE}/src
  git clone git@github.com:IvyFramework/IvyDataTools.git
  costat=$?
  if [[ $costat -ne 0 ]]; then
    echo "Could not checkout IvyFramework/IvyDataTools"
    exit $costat
  fi
  cd ~
fi


printenv() {
  if [[ -d ${CMSSW_BASE}/src/IvyFramework/IvyDataTools ]]; then
    envopts="env standalone"
    ${CMSSW_BASE}/src/IvyFramework/IvyDataTools/setup.sh ${envopts}
    eval $(${CMSSW_BASE}/src/IvyFramework/IvyDataTools/setup.sh ${envopts})
  fi
}
doenv() {
  if [[ -d ${CMSSW_BASE}/src/IvyFramework/IvyDataTools ]]; then
    envopts="env standalone"
    eval $(${CMSSW_BASE}/src/IvyFramework/IvyDataTools/setup.sh ${envopts})
  fi
}
printenvinstr () {
  echo
  echo "to use this repo, you must run:"
  echo
  echo 'eval $(./setupIvy.sh env)'
  echo "or"
  echo 'eval `./setupIvy.sh env`'
  echo
  echo "if you are using a bash-related shell, or you can do"
  echo
  echo './setupIvy.sh env'
  echo
  echo "and change the commands according to your shell in order to do something equivalent to set up the environment variables."
  echo
}

if [[ $doPrintEnv -eq 1 ]]; then
    printenv
    exit
elif [[ $doPrintEnvInstr -eq 1 ]]; then
    printenvinstr
    exit
fi

if [[ $nSetupArgs -eq 0 ]]; then
    setupArgs+=( -j 1 )
    nSetupArgs=2
fi


if [[ "$nSetupArgs" -eq 1 ]] && [[ "${setupArgs[0]}" == *"clean"* ]]; then
    ${CMSSW_BASE}/src/IvyFramework/IvyDataTools/setup.sh standalone clean 1> /dev/null || exit $?

    exit $?
elif [[ "$nSetupArgs" -ge 1 ]] && [[ "$nSetupArgs" -le 2 ]] && [[ "${setupArgs[0]}" == *"-j"* ]]; then
    : ok
else
    echo "Unknown arguments:"
    echo "  ${setupArgs[@]}"
    echo "Should be nothing, env, envinstr, clean, or -j [Ncores]"
    exit 1
fi

doenv

# Compile IvyDataTools
${CMSSW_BASE}/src/IvyFramework/IvyDataTools/setup.sh standalone "${setupArgs[@]}" 1> /dev/null || exit $?

printenvinstr

)
