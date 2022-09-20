#!/bin/bash

d=`date +%b-%d-%Y`
inputDate="Sep-13-2022"
model="Y3"

indir="datacards_all_${inputDate}"
outdir="limits_all_${d}_checks"
eval "mkdir -p ${outdir}"
eval "cp ./utils/index.php ${outdir}"

allmasses=(250 400 550 700 850 1000 1250 1500 2000)
options="--cminDefaultMinimizerStrategy 0 --X-rtd MINIMIZER_freezeDisassociatedParams --X-rtd MINIMIZER_multiMin_hideConstants --X-rtd MINIMIZER_multiMin_maskConstraints --X-rtd MINIMIZER_multiMin_maskChannels=1 -t -1 --rMin -1 --X-rtd TMCSO_PseudoAsimov=5000"
for m in ${allmasses[@]}
do
    ### Fit diagnostics
    name="-n _${model}_M${m}"
    options="--cminDefaultMinimizerStrategy 0 -t -1 --rMin -1 --toysFrequentist" 
    options=${options}" --X-rtd MINIMIZER_freezeDisassociatedParams --X-rtd TMCSO_PseudoAsimov=5000"
    ### (signal=0)
    eval "combine -M FitDiagnostics ${indir}/card_combined_${model}_M${m}_allyears.root ${options} --expectSignal 0 ${name}_t0 -m ${m} --forceRecreateNLL"
    eval "python ${CMSSW_BASE}/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py -a fitDiagnostics_${model}_M${m}_t0.root -g ${outdir}/plots_${model}_m${m}_t0.root >& ${outdir}/fitResults_${model}_m${m}_t0.txt"
    ### (signal=1)
    eval "combine -M FitDiagnostics ${indir}/card_combined_${model}_M${m}_allyears.root ${options} --expectSignal 1 ${name}_t1 -m ${m} --forceRecreateNLL"
    eval "python ${CMSSW_BASE}/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py -a fitDiagnostics_${model}_M${m}_t1.root -g ${outdir}/plots_${model}_m${m}_t1.root >& ${outdir}/fitResults_${model}_m${m}_t1.txt"
    
    ### Impacts (signal=0)
    name="-n ${model}_M${m}"
    options="--cminDefaultMinimizerStrategy 0 -t -1 --rMin -1 --toysFrequentist"
    options=${options}" --X-rtd TMCSO_PseudoAsimov=5000"
    eval "combineTool.py -M Impacts -d ${indir}/card_combined_${model}_M${m}_allyears.root ${options} --expectSignal 0 ${name}_t0 -m ${m} --doInitialFit"
    eval "combineTool.py -M Impacts -d ${indir}/card_combined_${model}_M${m}_allyears.root -o ${outdir}/impacts_${model}_m${m}_t0.json ${options} --expectSignal 0 ${name}_t0 -m ${m} --doFits --parallel 20 --task-name ${model}_m${m}_t0 >& /dev/null"
    eval "combineTool.py -M Impacts -d ${indir}/card_combined_${model}_M${m}_allyears.root -m ${m} ${name}_t0 -o ${outdir}/impacts_${model}_m${m}_t0.json ${options}"
    eval "plotImpacts.py -i ${outdir}/impacts_${model}_m${m}_t0.json -o ${outdir}/impacts_${model}_m${m}_t0"
    
    ### Impacts (signal=1)
    options="--cminDefaultMinimizerStrategy 0 -t -1 --rMin 0 --toysFrequentist"
    options=${options}" --X-rtd TMCSO_PseudoAsimov=5000"
    eval "combineTool.py -M Impacts -d ${indir}/card_combined_${model}_M${m}_allyears.root ${options} --expectSignal 1 ${name}_t1 -m ${m} --doInitialFit"
    eval "combineTool.py -M Impacts -d ${indir}/card_combined_${model}_M${m}_allyears.root -o ${outdir}/impacts_${model}_m${m}_t1.json ${options} --expectSignal 1 ${name}_t1 -m ${m} --doFits --parallel 20 --task-name ${model}_m${m}_t1 >& /dev/null"
    eval "combineTool.py -M Impacts -d ${indir}/card_combined_${model}_M${m}_allyears.root -m ${m} ${name}_t1 -o ${outdir}/impacts_${model}_m${m}_t1.json ${options}"    
    eval "plotImpacts.py -i ${outdir}/impacts_${model}_m${m}_t1.json -o ${outdir}/impacts_${model}_m${m}_t1"
    
    ### Data-card validation
    eval "ValidateDatacards.py ${indir}/card_combined_${model}_M${m}_allyears.root --jsonFile ${outdir}/validation_${model}_M${m}.json"

    ## Goodness-of-fit test (saturated algorithm)
    eval "combine -M GoodnessOfFit ${indir}/card_combined_${model}_M${m}_allyears.root --algo=saturated -m ${m}"
    eval "combine -M GoodnessOfFit ${indir}/card_combined_${model}_M${m}_allyears.root --algo=saturated -m ${m} --toysFrequentist"
    eval "combine -M GoodnessOfFit ${indir}/card_combined_${model}_M${m}_allyears.root --algo=saturated -t 100 -s ${m} -m ${m} --toysFrequentist"
    eval "combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH${m}.root higgsCombineTest.GoodnessOfFit.mH${m}.${m}.root -o ${outdir}/gof_sb_${model}_M${m}.json -m ${m}"
    eval "plotGof.py ${outdir}/gof_sb_${model}_M${m}.json --statistic saturated -o ${outdir}/gof_plot_sb_${model}_M${m} --m ${m}.0 --title-left='${model}, M=${m} GeV, S+B fit'"

    eval "combine -M GoodnessOfFit ${indir}/card_combined_${model}_M${m}_allyears.root --algo=saturated -m ${m} --fixedSignalStrength=0"
    eval "combine -M GoodnessOfFit ${indir}/card_combined_${model}_M${m}_allyears.root --algo=saturated -m ${m} --toysFrequentist --fixedSignalStrength=0"
    eval "combine -M GoodnessOfFit ${indir}/card_combined_${model}_M${m}_allyears.root --algo=saturated -t 100 -s ${m} -m ${m} --toysFrequentist --fixedSignalStrength=0"
    eval "combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH${m}.root higgsCombineTest.GoodnessOfFit.mH${m}.${m}.root -o ${outdir}/gof_${model}_M${m}.json -m ${m}"
    eval "plotGof.py ${outdir}/gof_${model}_M${m}.json --statistic saturated -o ${outdir}/gof_plot_${model}_M${m} --m ${m}.0 --title-left='${model}, M=${m} GeV, B-only fit'"

done

if [ -d "~/public_html/Zprime/${outdir}" ]
then
    eval "rm ${outdir}/*.png"
    eval "cp ${outdir}/* ~/public_html/Zprime/${outdir}/"
else
    eval "rm ${outdir}/*.png"
    eval "cp -r ${outdir} ~/public_html/Zprime/"
fi

eval "rm higgsCombine*.root"
eval "rm fitDiagnostics*.root"
