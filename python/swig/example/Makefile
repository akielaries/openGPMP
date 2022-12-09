

swig_files		= test_module.i

pypath			= -I/usr/include/python3.10

run-swig:
	swig -c++ -python ${swig_files}

compile-source:
	g++ -O2 -fPIC -c test_module.cpp

compile-wrapper:
	g++ -O2 -fPIC -c test_module_wrap.cxx ${pypath}

compile-lib:
	g++ -shared test_module.o test_module_wrap.o -o _test_module.so


