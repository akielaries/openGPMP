"""
Main entrypoint for building the openMTPK Python API.
Leverages SWIG, setuptools, and a few other dependencies.
"""

#from setuptools import setup, find_packages
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

# get recent version, bump the version
with urllib.request.urlopen(f"https://pypi.python.org/pypi/openmtpk/json") as url:
    data = json.load(url)
    latest_version = (data['info']['version'])
    bump_version = latest_version
    bump_version = bump_version.split('.')
    bump_version[2] = str(int(bump_version[2]) + 1)
    concat_version = '.'.join(bump_version)
    new_version = concat_version


this_dir = os.path.dirname(os.path.abspath(__file__))


# arithmetic module related information
arithmetic = Extension(
    'openmtpk.arithmetic._arithmetic',
    include_dirs=[os.path.join(this_dir, 'include/arithmetic')],
    sources=[
        'Python/openmtpk/arithmetic/arithmetic.i',
        'modules/arithmetic/arith.cpp'],
    extra_compile_args=['-std=c++2a'],
    swig_opts=['-Wall', '-c++'],
)

# calculus module related information
calculus = Extension(
    'openmtpk.calculus._calculus',
    include_dirs=[os.path.join(this_dir, 'include/calculus')],
    sources=[
        'Python/openmtpk/calculus/calculus.i',
        'modules/calculus/deriv.cpp'],
    extra_compile_args=['-std=c++2a'],
    swig_opts=['-c++'],
)

# machine learning module related information
ml = Extension(
    'openmtpk.ml._ml',
    include_dirs=[os.path.join(this_dir, 'include/ml')],
    sources=[
        'Python/openmtpk/ml/ml.i',
        'modules/ml/linreg.cpp'],
    extra_compile_args=['-std=c++2a'],
    swig_opts=['-c++'],
)

# linear algebra module related information
linalg = Extension(
    'openmtpk.linalg._linalg',
    include_dirs=[os.path.join(this_dir, 'include/linalg')],
    sources=[
        'Python/openmtpk/linalg/linalg.i',
        'modules/linalg/lao.cpp'],
    extra_compile_args=['-std=c++2a'],
    swig_opts=['-c++'],
)

# number_theory module related information
nt = Extension(
    'openmtpk.nt._nt',
    include_dirs=[os.path.join(this_dir, 'include/nt')],
    sources=[
        'Python/openmtpk/nt/nt.i',
        'modules/arithmetic/arith.cpp',
        'modules/nt/primes.cpp',
        'modules/nt/rc4.cpp',
        'modules/nt/cipher.cpp'],
    extra_compile_args=['-std=c++2a'],
    swig_opts=['-c++'],
)

# BINARY DISTRIBUTION (with a Python wrapper)


class BinaryDistribution(dist.Distribution):
    def has_ext_modules(modules):
        return True


# openmtpk Python API modules
modules = [arithmetic, calculus, ml, linalg, nt]

# use the project readme as the description
with open('README.md', 'r', encoding='utf-8') as fh:
    long_description = fh.read()


# def build_pkg():
setuptools.setup(
    name='openmtpk',
    distclass=BinaryDistribution,
    # get version from PyPI package, use bump to increment
    version=new_version,
    author='Akiel Aries',
    author_email='akiel@akiel.org',
    description='openMTPK Python API',
    keywords='openmtpk, example, pypi, package',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/akielaries/openMTPK',
    project_urls={
        'Documentation': 'https://akielaries.github.io/openMTPK/',
        'Bug Reports':
        'https://github.com/akielaries/openMTPK/issues',
        'Source Code': 'https://github.com/akielaries/openMTPK/',
    },
    package_dir={'': 'Python'},
    # packages=setuptools.find_packages(where='Python'),
    #package_data={'openmtpk': ['linalg/*', 'nt/*']},
    # packages=setuptools.find_packages(),
    packages=['openmtpk',
              'openmtpk.arithmetic',
              'openmtpk.calculus',
              'openmtpk.linalg',
              'openmtpk.ml',
              'openmtpk.nt',
              ],
    # packages=setuptools.find_packages(),
    ext_modules=modules,
    include_package_data=True,
    classifiers=[
        # see https://pypi.org/classifiers/
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
        'Programming Language :: OCaml',
        'Operating System :: POSIX',
        'Operating System :: Unix',
        'Operating System :: MacOS',
    ],
    python_requires='>=3.6',
    # install_requires=['Pillow'],
    extras_require={
        'dev': ['check-manifest'],
        # 'test': ['coverage'],
    },
)

#os.system('rm -rf build/')
#os.system('cd Python && rm -rf openmtpk.egg-info && cd openmtpk && make clean')

# if __name__ == '__main__':
#    build_pkg()
