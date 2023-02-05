"""
openMTPK
========
Python API for C++ based Mathematics Package. See the following links for
details and documentation:
    SOURCE CODE : https://github.com/akielaries/openMTPK/
    DOCS        : https://akielaries.github.io/openMTPK/
    PyPI        : https://pypi.org/project/openmtpk/

"""

__all__: list[str]
__path__: list[str]


from . import _version
__version__ = _version.get_versions()['version']
