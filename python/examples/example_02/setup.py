# automates the API binding process

from distutils.core import setup, Extension

# module name
module = "test_module"
version = "0.0.1"

# specifying name of extension and src files
ext_modules = Extension(name='_test_module', 
                        sources=["test_module_wrap.cxx", "test_module.cpp"])
setup(name=module,
      version=version,
      ext_modules=[ext_modules])

