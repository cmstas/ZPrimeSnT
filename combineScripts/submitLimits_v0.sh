#!/bin/bash

inputDate="Sep-13-2022"
model="Y3"

which=""


if [ $# != 1 ]
then
    echo "Please specify option: shape; count; nomodel"
    return 0
fi

if [ $# > 0 ]
then
    which=$1
fi

if [ ${which} != "shape" ] && [ ${which} != "count" ] && [ ${which} != "nomodel" ]
then
    echo "Available options: shape; count; nomodel"
    return 0
fi

d=`date +%b-%d-%Y`

indir="datacards_all_${inputDate}"
outdir="limits_all_${d}"
if [ ${which} = "count" ]
then
    indir="datacards_all_count_${inputDate}"
    outdir="limits_all_count_${d}"
elif [ ${which} = "nomodel" ]
then
    indir="datacards_all_nomodel_${inputDate}"
    outdir="limits_all_nomodel_${d}"
fi
eval "mkdir -p ${outdir}"

allmasses=(250 400 550 700 850 1000 1250 1500 2000)
options="--cminDefaultMinimizerStrategy 0 --X-rtd MINIMIZER_freezeDisassociatedParams --X-rtd MINIMIZER_multiMin_hideConstants --X-rtd MINIMIZER_multiMin_maskConstraints --X-rtd MINIMIZER_multiMin_maskChannels=1"
for m in ${allmasses[@]}
do
    if [ ${which} != "nomodel" ]
    then
	name="-n _${which}_${model}_M${m}"
	echo "combine -M AsymptoticLimits ${indir}/card_combined_${model}_M${m}_allyears.root ${options} ${name} >& ${outdir}/lim_${which}_${model}_m${m}.txt&"
	eval "combine -M AsymptoticLimits ${indir}/card_combined_${model}_M${m}_allyears.root ${options} ${name} >& ${outdir}/lim_${which}_${model}_m${m}.txt&"
    else
	allf2b=(0 10 25 50 75 90 100)
	for f in ${allf2b[@]}
	do
	    name="-n _${which}_M${m}_f2b${f}"
	    echo "combine -M AsymptoticLimits ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root ${options} ${name} >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt&"
	    eval "combine -M AsymptoticLimits ${indir}/card_f2b${f}_combined_${model}_M${m}_allyears.root ${options} ${name} >& ${outdir}/lim_${which}_f2b${f}_m${m}.txt&"
	done
    fi
done
