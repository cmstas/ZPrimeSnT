## Various jupyter notebooks

To set up a python-friendly conda environment for analysis, see the instructions in
[https://github.com/aminnj/daskucsd](https://github.com/aminnj/daskucsd).

### Deprecated instructions below

#### Setup
```bash
# edit the port and add additional packages into `setup_container.sh`
# start a jupyter notebook
./start_server.sh

# on your local computer, forward the port before you can visit the url. e.g.,
ssh -N -f -L localhost:8893:localhost:8893 uaf-10.t2.ucsd.edu
```

#### Notebooks

* `fourmu.ipynb` uses `coffea` tools to look at H to ZZ to 4mu in Run2 DoubleMuon datasets
* `trijet.ipynb` uses `coffea` to store invariant masses of 2,3,4,5 jets with Run2 JetHT datasets
* `convert.ipynb` converts NanoAOD datasets into columnar format (each column is a separate gzipped `.npz` file)
