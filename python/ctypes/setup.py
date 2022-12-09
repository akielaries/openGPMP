from setuptools import setup, Extension

# compile into shared lib
setup(
    #...
    ext_modules=[Extension('mysum', ['mysum.cpp'],),],
)

