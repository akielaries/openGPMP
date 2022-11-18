#! /bin/sh

#   ____   __  __                _          
#  |  _ \ |  \/  |        _ __  | | __ __ _ 
#  | |_) || |\/| | _____ | '_ \ | |/ // _` |
#  |  _ < | |  | ||_____|| |_) ||   <| (_| |
#  |_| \_\|_|  |_|       | .__/ |_|\_\\__, |
#                        | |           __| |
#                        |_|          |___/ 
# this script acts as the main "runner" for RM-pkg demonstrating its
# functionality by running each modules driver file 

# build + run tests in the makefile 
make arith
make lin-reg
# delete generated binaries
make clean

