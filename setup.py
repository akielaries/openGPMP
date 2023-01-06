#from setuptools import setup, find_packages
import setuptools
from setuptools import setup, dist
from setuptools.command.install import install
import os
import subprocess
import platform

# execute swig wrapping and respective setup.py
os.system('cd Python/openmtpk &&\
        make run-swig &&\
        cd ../ &&\
        python3 setup.py build_ext --inplace &&\
        make clean')

# BINARY DISTRIBUTION (with a Python wrapper)
class BinaryDistribution(dist.Distribution):
    def has_ext_modules(foo):
        return True

if platform.system() == 'Darwin':
    pkg_data = {'': ['Python/openmtpk/*.so']}
else:
    pkg_data = {'': ['Python/openmtpk/_openmtpk.so']}

with open('README.md', 'r', encoding='utf-8') as fh:
    long_description = fh.read()

#subprocess.call(['make compile compile-wrapper compile-lib clean', 
#                 '-C',
#                 'Python/openmtpk'])



setuptools.setup(
    name='openmtpk',
    distclass=BinaryDistribution,
    version='0.4.96',
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
    #packages=[''],
    package_dir={'': 'Python'},
    packages=setuptools.find_packages(where='Python', 
                                      exclude=['openmtpk/setup.py']),
    # shared object is dependent on operating system
    package_data=pkg_data,
    include_package_data=True,
    #exclude_package_data={'': 'Python/openmtpk/setup.py'},
    classifiers=[
        # see https://pypi.org/classifiers/
        'Development Status :: 4 - Beta',

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
    python_requires='>=3.6',
    # install_requires=['Pillow'],
    extras_require={
        'dev': ['check-manifest'],
        # 'test': ['coverage'],
    },
    # entry_points={
    #     'console_scripts': [  # This can provide executable scripts
    #         'run=examplepy:main',
    # You can execute `run` in bash to run `main()` in src/examplepy/__init__.py
    #     ],
    # },
)

os.system('cd Python/openmtpk &&\
        make clean')

