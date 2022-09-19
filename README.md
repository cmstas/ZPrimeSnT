### Environment & setup
```bash
git clone git@github.com:cmstas/ZPrimeSnT.git
pushd ZPrimeSnT/
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_2_13
pushd CMSSW_10_2_13/src
cmsenv
git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
pushd HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v8.2.0
scramv1 b clean; scramv1 b # always make a clean build
popd
scram b
popd
pushd NanoCORE
make -j12
popd
```

## Analysis code:

For more dedtails, refer to `cpp/README.md`.

### Example instructions

Edit `cpp/doAll_Zp.C` and/or `cpp/ScanChain_Zp.C` with an appropriate file (or hopefully the default one still exists).

**To run locally:**

```bash
sh cpp/runOutput_Zp.sh DIRECTORY/FOR/OUTPUT/FILES YEAR RUNDATA RUNBKG RUNSIGNAL RUNBFF SAMPLE ADDITIONALBOOLEANFLAGS
```

For example, to run all data, bkg and signal but not the BFF samples, for all years and with all additional flags to their default values, the command to save the files in a folder called "temp_data" would be:

```bash
sh cpp/runOutput_Zp.sh temp_data all 1 1 1 0 all
```

One should check `cpp/doAll_Zp.C` for details on the (additional) arguments and their meaning.

This loops and creates a number of output files of the form `output_"process"_"year".root` containing histograms. 
Optionally, the file also contains a `RooDataSet` to be used as input for fitting (see below).

**To run on condor:**

```bash
voms-proxy-init -voms cms
export X509_USER_PROXY=/ABSOLUTE/PATH/TO/PROXY/LOCATION
sh utils/condor/runOutput_Zp_onCondor.sh FOLDER/FOR/OUTPUT/FILES
```

This script will package the current state of the repository and send it to condor jobs running the `cpp/runOutput_Zp.sh` with the arguments included in the different lines of `utils/condor/runOutput_Zp_onCondor.sub` (please edit this file to control what condor jobs you send). More details on this are included in the description of [PR#57](https://github.com/cmstas/ZPrimeSnT/pull/57).

The output of your jobs will be found under `/ceph/cms/store/user/$USER/ZPrimeSnTOutput/FOLDER/FOR/OUTPUT/FILES` and the plotting logs under `utils/condor/plotting_logs`.

**To produce plots:**
```bash
python python/stack_plots.py
```

**To produce cutflow table:**
```bash
python python/make_cutflow_table.py
```


## Fitting code:

```bash
pushd CMSSW_10_2_13/src/
cmsenv
popd
pushd cpp/
root -b -q -l -n doAll_fitDimuonMass.C
popd
```

This creates a ROOT file with a workspace containing all relevant PDFs, to be used as input to `combine`.
Optionally, fits are drawn and fit results are saved in a dedicated ROOT file.
In order to plot fit results:
```bash
python python/plot_fitResults.py
```


## Pull requests:

When opening a PR against the `main` branch, please make sure your code is up-to-date:
```bash
pushd ZPrimeSnt/
git checkout main
git pull
git checkout -b <branchname>
<Do your developmets and commit>
git push origin <branchname>
```
Then, open a PR against `main` branch and request review.


## NanoCORE synchronization:

The `NanoCORE` subdirectory shall be synchronized often with `git@github.com:cmstas/NanoTools.git`.
For the first time only:
```bash
git clone git@github.com:cmstas/NanoTools.git
```
To pull updates from `NanoTools`:
```bash
pushd NanoTools
git pull
cp NanoCORE/* ../ZPrimeSnT/NanoCORE/
popd
pushd ZPrimeSnT/
git checkout -b <branchname>
git commit -a -m "<description>"
git push origin <branchname>
```
Then, open pull request to `ZPrimeSnT` remote repository.

To push updates to `NanoTools`:
```bash
pushd NanoTools
git pull
git checkout -b <branchname>
cp ../ZPrimeSnT/NanoCORE/* NanoCORE/*
git commit -a -m "<description>"
git push origin <branchname>
```
Then, open pull request to `NanoTools` remote repository.


## Style:

We use `clang-format` based on LLVM style to format our code. To format the `ElectronSelections.cc` file in-place, do
```bash
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4, ColumnLimit: 120, AllowShortIfStatementsOnASingleLine: true, AllowShortBlocksOnASingleLine: true}" -i ElectronSelections.cc
```

If you use ```vim```, add this to the ```~/.vimrc``` (assumes you are working on UAF):
```
autocmd BufNewFile,BufRead *.cc,*.h,*.C,*.cxx set formatprg=clang-format\ -style=\"{BasedOnStyle:\ llvm,\ IndentWidth:\ 4,\ ColumnLimit:\ 100,\ AllowShortIfStatementsOnASingleLine:\ true,\ AllowShortBlocksOnASingleLine:\ false,\ BreakBeforeBraces:\ Allman}\"
```
To format your code in ```vim```, press ```ggvGgq```.
