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
popd; popd
pushd NanoCORE
make -j12
popd
```

## Analysis code:

For more dedtails, refer to `cpp/README.md`.

### Example instructions

Edit `cpp/doAll_Zp.C` with an appropriate file (or hopefully the default one still exists).

```bash
pushd cpp/
root -b -q -l -n doAll_Zp.C
popd
```

This loops and creates a number of output files of the form `output_"process"_"year".root` containing histograms. 
Optionally, the file also contains a `RooDataSet` to be used as input for fitting (see below).

To produce plots:
```bash
python python/stack_plots.py
```

To produce cutflow table:
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
