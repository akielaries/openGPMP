#! /bin/sh
# this script acts as the main "runner" for openMTPK demonstrating its
# functionality by running each modules driver file 

# build + run test drivers in Makefile 
make arith
make calculus 
make lin-alg 
make ml_dl
make num-theory 

# delete generated binaries
make clean-mods

