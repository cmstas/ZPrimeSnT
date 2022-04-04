## Python loopers

The file `loop_with_core.py` shows how to loop over events and use NanoCORE
This only requires CMSSW. Additional Python usage can be found in the unit tests.

For trendier folk, a conda environment is the recommended way to get the latest/greatest
Python packages.

## Conda environment

You only have to do the initial setup once. Afterwards, 
you only need to activate the environment.

### Initial setup

Install after a fresh login to the computers (to prevent CMSSW interference).
```
# download conda installer
curl -O -L https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
bash Miniconda3-latest-Linux-x86_64.sh -b 

# add conda to the end of ~/.bashrc, so relogin after executing this line
~/miniconda3/bin/conda init

# stop conda from activating the base environment on login
conda config --set auto_activate_base false
conda config --add channels conda-forge

# install package to tarball environments
conda install --name base conda-pack -y

# create environments with as much stuff from anaconda
conda create --name pyrootenv uproot pandas root matplotlib jupyter

# and then any install residual packages with pip
conda run --name pyrootenv pip install yahist
```

### Activate and use

```
conda activate pyrootenv
python read_with_uproot.py
```
