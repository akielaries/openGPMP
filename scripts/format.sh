#!/bin/sh
printf "[+] Formatting C, C++, CUDA files...\n"
cd ../ && find . -regex '.*\.\(c\|cu\|cuh\|cpp\|hpp\|h\|cxx\)' -exec clang-format -style=file -i {} \;

printf "[+] Formatting FORTRAN files...\n"
cd ../ && find . -type f -name "*.f90" -exec fprettify {} --indent 4 \;
