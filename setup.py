"""
Main entrypoint for building the openGPMP Python API.
Leverages SWIG, setuptools, and a few other dependencies.
"""

# from setuptools import setup, find_packages
import setuptools
from setuptools import setup, dist
from setuptools.extension import Extension
from setuptools.command.install import install
from setuptools.command.build_ext import build_ext
import os
import subprocess
import platform
import urllib.request
import json
import versioneer

this_dir = os.path.dirname(os.path.abspath(__file__))

CXX_ARGS = ['-D', 
            '__GPMP_PYTHON_API__',
            '-std=c++20',
            '-Wparentheses',
            '-Wsign-compare',
            '-DNDEBUG',
            '-Wall',
            '-Wextra',
            '-march=native'
            ]

# arithmetic module related information
arithmetic = Extension(
    'pygpmp.arithmetic._arithmetic',
    include_dirs=[os.path.join(this_dir, 'include/arithmetic')],
    sources=[
        'pygpmp/arithmetic/arithmetic.i',
        'modules/arithmetic/arith.cpp'],
    extra_compile_args=['-std=c++20'],
    swig_opts=['-Wall', '-c++'],
)

# calculus module related information
calculus = Extension(
    'pygpmp.calculus._calculus',
    include_dirs=[os.path.join(this_dir, 'include/calculus')],
    sources=[
        'pygpmp/calculus/calculus.i',
        'modules/calculus/differential.cpp'],
    extra_compile_args=CXX_ARGS,
    swig_opts=['-c++'],
)

core = Extension(
    'pygpmp.core._core',
    include_dirs=[os.path.join(this_dir, 'include/core')],
    sources=[
        'pygpmp/core/core.i',
        'modules/core/datatable.cpp',
        'modules/core/utils.cpp',
        ],
    extra_compile_args=CXX_ARGS,
    swig_opts=['-c++'],
)

# machine learning module related information
ml = Extension(
    'pygpmp.ml._ml',
    include_dirs=[os.path.join(this_dir, 'include/ml')],
    sources=[
        'pygpmp/ml/ml.i',
        'modules/ml/linreg.cpp'],
    extra_compile_args=CXX_ARGS,
    swig_opts=['-c++'],
)

# linear algebra module related information
linalg = Extension(
    'pygpmp.linalg._linalg',
    include_dirs=[os.path.join(this_dir, 'include/linalg')],
    sources=[
        'pygpmp/linalg/linalg.i',
        'modules/linalg/mtx.cpp'],
    extra_compile_args=CXX_ARGS,
    swig_opts=['-c++'],
)

# number_theory module related information
nt = Extension(
    'pygpmp.nt._nt',
    include_dirs=[os.path.join(this_dir, 'include/nt')],
    sources=[
        'pygpmp/nt/nt.i',
        'modules/arithmetic/arith.cpp',
        'modules/nt/prime_test.cpp',
        'modules/nt/prime_gen.cpp',
        'modules/nt/logarithms.cpp',
        'modules/nt/factorization.cpp',
        'modules/nt/rc4.cpp',
        'modules/nt/cipher.cpp'],
    extra_compile_args=['-std=c++20'],
    swig_opts=['-c++'],
)

# BINARY DISTRIBUTION(with a Python wrapper)


class BinaryDistribution(dist.Distribution):
    def has_ext_modules(modules):
        return True

def main():
    # main execution for building the dist
    # pygpmp Python API modules
    modules = [arithmetic, calculus, core, ml, linalg, nt]

    # use the project readme as the description
    with open('README.md', 'r', encoding='utf-8') as fh:
        long_description = fh.read()

    # def build_pkg():
    setuptools.setup(
        name='pygpmp',
        distclass=BinaryDistribution,
        # get version from PyPI package, use bump to increment
        version=versioneer.get_version(),
        cmdclass=versioneer.get_cmdclass(),
        author='Akiel Aries',
        author_email='akiel@akiel.org',
        description='openGPMP Python API',
        keywords='pygpmp, example, pypi, package',
        long_description=long_description,
        long_description_content_type='text/markdown',
        url='https://github.com/akielaries/openGPMP',
        project_urls={
            'Documentation': 'https://akielaries.github.io/openGPMP/',
            'Bug Reports':
            'https://github.com/akielaries/openGPMP/issues',
            'Source Code': 'https://github.com/akielaries/openGPMP/',
        },
        package_dir={'': '.'},
        packages=['pygpmp',
                  'pygpmp.arithmetic',
                  'pygpmp.calculus',
                  'pygpmp.core',
                  'pygpmp.linalg',
                  'pygpmp.ml',
                  'pygpmp.nt',
                  ],
        ext_modules=modules,
        include_package_data=True,
        classifiers=[
            # see https: //pypi.org/classifiers/
            'Development Status :: 4 - Beta',
            'Intended Audience :: Science/Research',
            'Intended Audience :: Developers',
            'Intended Audience :: Education',
            'Intended Audience :: Information Technology',
            'Topic :: Scientific/Engineering',
            'Topic :: Scientific/Engineering :: Mathematics',
            'Topic :: Scientific/Engineering :: Artificial Intelligence',
            'Topic :: Software Development',
            'Topic :: Software Development :: Build Tools',
            'Topic :: Software Development :: Libraries',
            'Topic :: Software Development :: Libraries :: Python Modules',
            'Topic :: Utilities',
            'Topic :: Education',
            'Topic :: Education :: Testing',
            'Topic :: Documentation',
            'Programming Language :: C++',
            'Programming Language :: C',
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3.6',
            'Programming Language :: Python :: 3.7',
            'Programming Language :: Python :: 3.8',
            'Programming Language :: Python :: 3.9',
            'Programming Language :: Python :: 3.10',
            'Programming Language :: Python :: 3 :: Only',
            'Programming Language :: Fortran',
            'Programming Language :: R',
            'Operating System :: POSIX',
            'Operating System :: Unix',
            'Operating System :: MacOS',
        ],
        python_requires='>=3.6',
        # install_requires = ['Pillow'],
        extras_require={
            'dev': ['check-manifest'],
            # 'test' : ['coverage'],
        },
    )

if __name__ == '__main__':
    main()
