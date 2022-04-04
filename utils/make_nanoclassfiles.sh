NANOINPUTSDIR=/hadoop/cms/store/group/snt/nanoaod/nanoclassinputs
python make_nanoclassfiles.py -t Events -n tas -c Nano -o nt --profiling $(ls -m ${NANOINPUTSDIR}/*.root | tr -d '\n')
