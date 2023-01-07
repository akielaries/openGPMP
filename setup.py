#from setuptools import setup, find_packages
import setuptools
from setuptools import setup, dist
from setuptools.extension import Extension
from setuptools.command.install import install

import os
import subprocess
import platform

import urllib.request
import json

# get recent version, use pip bump to bump the version
req = urllib.request.Request(f'https://pypi.python.org/pypi/openmtpk/json')
r = urllib.request.urlopen(req)

if r.code == 200:
    t = json.loads(r.read())
    releases = t.get('releases', [])
    if releases:
        new_version = sorted(releases)[-1]

this_dir = os.path.dirname(os.path.abspath(__file__))

# execute swig wrapping and respective setup.py
os.system('cd Python/openmtpk &&\
        make run-swig')

# openMTPK source files for SWIG interfacing
foo = Extension(
        'openmtpk._openmtpk',
        include_dirs=[os.path.join(this_dir, 'include')],
        sources=['Python/openmtpk/openmtpk_wrap.cxx',
             'modules/arithmetic/arith.cpp',
             'modules/number_theory/primes.cpp',
             'modules/number_theory/rc4.cpp',
             'modules/number_theory/cipher.cpp'],
        extra_compile_args=['-std=c++17']     
)

# BINARY DISTRIBUTION (with a Python wrapper)
class BinaryDistribution(dist.Distribution):
    def has_ext_modules(foo):
        return True

with open('README.md', 'r', encoding='utf-8') as fh:
    long_description = fh.read()


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
    packages=setuptools.find_packages(where='Python', 
                                      exclude=['*.cxx']),
    # shared object is dependent on operating system
    include_package_data=True,
    classifiers=[
        # see https://pypi.org/classifiers/
        'Development Status :: 5 - Production/Stable',

        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',

        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Programming Language :: Python :: 3 :: Only',
        'Operating System :: OS Independent',
    ],
    ext_modules=[foo],
    python_requires='>=3.6',
    # install_requires=['Pillow'],
    extras_require={
        'dev': ['check-manifest'],
        # 'test': ['coverage'],
    },
)

os.system('rm -rf build/')

