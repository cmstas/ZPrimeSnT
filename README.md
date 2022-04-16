### Environment & setup
```bash
git clone git@github.com:cmstas/ZPrimeSnT.git
pushd ZPrimeSnT/
pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_2_9/
cmsenv
popd
pushd NanoCORE
make -j12
popd
```

### Analysis codee:

Please, refer to `cpp/README.md`.

### NanoCORE synchronization:

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


### Style:

We use `clang-format` based on LLVM style to format our code. To format the `ElectronSelections.cc` file in-place, do
```bash
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4, ColumnLimit: 120, AllowShortIfStatementsOnASingleLine: true, AllowShortBlocksOnASingleLine: true}" -i ElectronSelections.cc
```

If you use ```vim```, add this to the ```~/.vimrc``` (assumes you are working on UAF):
```
autocmd BufNewFile,BufRead *.cc,*.h,*.C,*.cxx set formatprg=clang-format\ -style=\"{BasedOnStyle:\ llvm,\ IndentWidth:\ 4,\ ColumnLimit:\ 100,\ AllowShortIfStatementsOnASingleLine:\ true,\ AllowShortBlocksOnASingleLine:\ false,\ BreakBeforeBraces:\ Allman}\"
```
To format your code in ```vim```, press ```ggvGgq```.
