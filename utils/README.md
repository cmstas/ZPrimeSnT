# utilities

## `make_nanoclassfiles.py`
Makes classfiles similar to `CMS3.h`/`CMS3.cc`. 

```bash
python ../utils/make_nanoclassfiles.py [nanoaodfile] --tree Events --looper
```

Note that this `--looper` also creates a looper (`ScanChain.C` + `doAll.C`). 
You can specify `--profiling` to make a beefier class file with more functions to help profile your code. 
The automatic documentation (description of different branches) embedded in nanoAOD files
is converted into comments inside `Nano.h`.


All options and features are visible with `./make_nanoclassfiles.py -h`.

### LorentzVectors
In nanoAOD, there are no branches of LorentzVectors, only things like `Muon_pt`, `Muon_eta`, 
`Muon_phi`, `Muon_mass`. Fear not, since the `Nano.cc`/`Nano.h` class file makes a `tas::Muon_p4()`
collection available (as an `std::vector<LorentzVector>`), which only auto-computes (and caches) the LorentzVectors
if the user has requested them for that event. Bear in mind the non-trivial performance impact from
getting LorentzVectors when you only really need `_pt` and/or `_eta` most of the time.


### Getting branches by strings
Since C++ lacks in terms of code introspection, there are some methods
(`tas::GetVF`, `tas::GetI`, `tas::GetVLV`, `tas::GetF`, `tas::GetB`, `tas::GetVI`, `tas::GetVB`)
that retrieve branches of `std::vector<float>`, `int`, `std::vector<LorentzVector>`, `float`, ... You see the pattern.
Why? You might want to do something as contrived as 
```cpp
for (auto& s : {"MET_pt", "CaloMET_pt", "GenMET_pt", "RawMET_pt", "TkMET_pt"})
    h1->Fill(tas::GetF(s));
```


## `dis_client.py`

Interfaces with [DIS](http://uaf-8.t2.ucsd.edu/~namin/dis2/)

## `parallel`

[GNU parallel](https://www.gnu.org/software/parallel/) -- a handy swiss army knife
for parallelization with bash

## `print_download_commands.sh`

Edit this appropriately with desired datasets. This will query DIS for a filelist
and print out commands to copy the files to your local hadoop area.
Then use `parallel` to download them all.
```
./print_download_commands.sh > commands.txt
./parallel --jobs 10 --bar --joblog joblog.txt < commands.txt
```

