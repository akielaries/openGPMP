# Execution of CPP->Python wrapping with Swig
import os
from distutils.core import setup, Extension

src_files = Extension('_openmtpk',
                      sources=['openmtpk/openmtpk_wrap.cxx',
                               '../modules/arithmetic/arith.cpp',
                               '../modules/number_theory/primes.cpp',
                               '../modules/number_theory/rc4.cpp',
                               '../modules/number_theory/cipher.cpp'],
                      extra_compile_args=['-std=c++17'],
                      )

setup(name='openmtpk',
      version='0.0.1',
      author='Akiel Aries',
      description='openMTPK Python API with SWIG',
      ext_modules = [src_files],
      py_modules = ['openmtpk'],
    )

os.system('mv *.so openmtpk/')

