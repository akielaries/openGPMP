compile:
	gfortran -g -fPIE -c mtx.f90 -o mtx.o -lgfortran
	g++ -g -fPIE -c mtx.cpp -o mtx_cpp.o -lgfortran

link:
	g++ -g mtx_cpp.o mtx.o -lgfortran


comp:
	gfortran -g -fPIE -c mtx.f90 -o mtx.o -lgfortran
	g++ -g -fPIE -c mtx2.cpp -o mtx_cpp.o -lgfortran
	g++ -g mtx_cpp.o mtx.o -lgfortran


clean:
	rm *.o
	rm a.out
	rm *.so
