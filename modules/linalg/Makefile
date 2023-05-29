compile:
	gfortran -g -fPIE -c mtx.f90 -o mtx.o -lgfortran
	g++ -g -fPIE -c mtx2.cpp -o mtx_cpp.o -lgfortran

link:
	g++ -g mtx_cpp.o mtx.o -lgfortran


clean:
	rm *.o
	rm a.out
