import os

os.system('cd Python/openmtpk &&\
        make run-swig &&\
        python3 setup.py build_ext --inplace')

