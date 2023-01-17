# openMTPK Python API

> **Warning**
> Do not edit the source `.py` files. 

The Python API leverages SWIG for generating each modules wrapper 
and corresponding shared object file. Edits to the Python API are done through :

1.  `setup.py` file seen in the root directory of this project. This file takes 
care of the SWIG process and creating a PyPI wheel.

2. Each modules SWIG interface file (`.i`) contains the information needed to 
compile and generate the necessary files for the module.

3. Each modules `__init__.py` file that contains the import information for each module. 

