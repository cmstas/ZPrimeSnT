## C++ based looper

In this folder, there is a "standard" C++ looper that is hooked up to NanoCORE already.

### Example instructions

Edit `doAll_ss.C` with an appropriate file (or hopefully the default one still exists).

```bash
root -b -q -l -n doAll_ss.C
```

This loops and creates `output.root`, which contains a handful of histograms.

### Making a standalone executable

Sometimes it is handy to make a standalone executable from an unnamed macro (e.g., `root -b -q -l -n doAll_jec.C` -> `./main.exe`).
To do this, first make a macro that is not unnamed (valid C++) usually by wrapping the unnamed function with a few lines to get
```cpp
#include "TROOT.h"
#include "ScanChain_jec.C"
int main() {
    TChain *ch = new TChain("Events");
    ch->Add("root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv6/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano25Oct2019_102X_mc2017_realistic_v7-v1/260000/E5F07826-B7B2-0C48-850C-63F68B5C9B99.root");
    ScanChain(ch);
}
```
Assuming this main function is in `main.cc`, execute
```bash
g++ main.cc -o main.exe `root-config --cflags --glibs` ../NanoCORE/NANO_CORE.so
```
to compile and link against CORE functions. Simply run with `./main.exe`.

### CPU profiling a standalone executable

To do CPU profiling of a standalone executable, we make use of `igprof`. Make sure NanoCORE and the executable
were compiled with debug symbols enabled (`-g`). Run the program
```bash
igprof -d -pp -z -o igprof.pp.gz ./main.exe >& log.txt &
```
Then convert this profiling output file into a format to be used with a cgi script. For some reason, this only
works with an older $SCRAM_ARCH, so we switch to an older one temporarily in order to execute `igprof-analyse`. (Commands
in bash which are enclosed in `(`,`)` are executed in a sandboxed subshell, so this is why we don't need to reset the
CMSSW environment again. Handy.)
```bash
(
    cd /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw-patch/CMSSW_7_4_7_patch1;
    cmsenv;
    cd -;
    igprof-analyse --sqlite -d -v -g igprof.pp.gz | sqlite3 igreport_perf.sql3 >& /dev/null
)
```
This sqlite file can be viewed with a cgi script. Set it up with
```bash
mkdir -p ~/public_html/cgi-bin/data
curl -o ~/public_html/cgi-bin/igprof-navigator.py https://raw.githubusercontent.com/cmstas/NtupleMaker/combined/test/profiling/igprof-navigator.py
chmod 755 -R ~/public_html/cgi-bin
```
Also ensure that your `~/public_html/.htaccess` file contains
```
AddHandler cgi-script .cgi .py
Options +ExecCGI
```
Next, copy over the sqlite file and visit the link.
```bash
cp igreport_perf.sql3 ~/public_html/cgi-bin/data/
echo "Navigate to http://uaf-10.t2.ucsd.edu/~${USER}/cgi-bin/igprof-navigator.py/igreport_perf/"
```
If you see issues with the web site, try making the permissions on the data files within `data/` 644. 
Permissions for cgi scripts and folders they reside in are very annoying to get right. 
