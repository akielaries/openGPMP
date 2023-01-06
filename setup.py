#from setuptools import setup, find_packages
import setuptools
import subprocess
import platform

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
    version='0.4.1',
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
    packages=setuptools.find_packages(where='Python'),
    # shared object is dependent on operating system
    package_data=pkg_data,
    include_package_data=True,
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




