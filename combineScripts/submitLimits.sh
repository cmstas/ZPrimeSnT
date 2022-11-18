#!/bin/bash

ulimit -s unlimited
export useSignalMC=0

indir=$1
outdir=$2
model=$3
which=$4

mF=350
mL=2000
if [ $# -lt 5 ]
then
    mF=350
    mL=2000
elif [ $# -lt 6 ]
then
    mF=$5
    mL=0
else
    mF=$5
    mL=$6
fi

allf2b=()
if [ $# -gt 6 ]
then
    if [ $7 -lt 101 ]
    then
	allf2b=($7)
    fi
else
    allf2b=(0 1 5 10 25 50 75 90 95 99 100)
fi

if [ $# -lt 4 ]
then
    echo "Usage: sh submitLimits.sh <indir> <outdir> <model> <which>"
    return 0
fi

allmasses=()
if [ ${useSignalMC} == 0 ]
then
    allmasses=(${allmasses} ${mF})
    tm=${mF}
    until [ ${tm} -gt ${mL} ]
    do
      if [ ${tm} -lt 400 ]; then
	  tm=$((${tm} + 5))
      elif [ ${tm} -lt 700 ]; then
	  tm=$((${tm} + 10))
      elif [ ${tm} -lt 1000 ]; then
	  tm=$((${tm} + 15))
      elif [ ${tm} -lt 1500 ]; then
	  tm=$((${tm} + 25))
      else
	  tm=$((${tm} + 50))
      fi
      allmasses=(${allmasses[@]} ${tm})
    done
else
    allmasses=(400 550 700 850 1000 1250 1500 2000)
fi

#options="--cminDefaultMinimizerStrategy 0 --X-rtd MINIMIZER_freezeDisassociatedParams --X-rtd MINIMIZER_multiMin_hideConstants --X-rtd MINIMIZER_multiMin_maskConstraints --X-rtd MINIMIZER_multiMin_maskChannels=1"
options="--cminDefaultMinimizerStrategy 0 -v 0"
for m in ${allmasses[@]}
do
    if [ ${model} != "nomodel" ]
    then
	name="-n _${which}_${model}_M${m}"
	if [ ${which} == "asymptotic" ]
	then
	    eval "combine -M AsymptoticLimits ${indir}/card_combined_${model}_M${m}_allyears.root ${options} ${name} -m ${m} >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "toysObs" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "toysExp" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.5 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "toysEm1" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.16 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "toysEp1" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.84 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "toysEm2" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.025 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "toysEp2" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.975 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "sigExp" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M Significance ${options} ${name} -m ${m} --uncapped=1 --rMin=-5 --rMax=5 -t -1 --expectSignal=1 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	elif [ ${which} == "sigObs" ]
	then
	    eval "combine ${indir}/card_combined_${model}_M${m}_allyears.root -M Significance ${options} ${name} -m ${m} --uncapped=1 --rMin=-5 --rMax=5 >& ${outdir}/lim_${which}_${model}_m${m}.txt"
	fi
	rm higgsCombine*_${which}_${model}_M${m}*.root
    else
	for f in ${allf2b[@]}
	do
	    name="-n _${which}_M${m}_f2b${f}"
	    if [ ${which} == "asymptotic" ]
	    then
		echo "combine -M AsymptoticLimits ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root ${options} ${name} -m ${m} >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine -M AsymptoticLimits ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root ${options} ${name} -m ${m} >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "toysObs" ]
	    then
		echo "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "toysExp" ]
	    then
		echo "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.5 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.5 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "toysEm1" ]
	    then
		echo "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.16 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.16 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "toysEp1" ]
	    then
		echo "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.84 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.84 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "toysEm2" ]
	    then
		echo "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.025 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.025 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "toysEp2" ]
	    then
		echo "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.975 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M HybridNew --LHCmode LHC-limits -T 500 -i 2 --rAbsAcc=0.01 --rRelAcc=0.025 ${options} ${name} -m ${m} --expectedFromGrid=0.975 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "sigExp" ]
	    then
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M Significance ${options} ${name} -m ${m} --uncapped=1 --rMin=-5 --rMax=5 -t -1 --expectSignal=1 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    elif [ ${which} == "sigObs" ]
	    then
		eval "combine ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root -M Significance ${options} ${name} -m ${m} --uncapped=1 --rMin=-5 --rMax=5 >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt"
	    fi
	    rm higgsCombine*_${which}_M${m}_f2b${f}*.root
	done
    fi
done
