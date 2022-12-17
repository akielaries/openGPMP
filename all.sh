#! /bin/sh
#                        ___  ______________ _   __
#                        |  \/  |_   _| ___ \ | / /
#   ___  _ __   ___ _ __ | .  . | | | | |_/ / |/ / 
#  / _ \| '_ \ / _ \ '_ \| |\/| | | | |  __/|    \ 
# | (_) | |_) |  __/ | | | |  | | | | | |   | |\  \
#  \___/| .__/ \___|_| |_\_|  |_/ \_/ \_|   \_| \_/
#       | |                                        
#       |_|                                        
#
#
# this script acts as the main "runner" for openMTPK demonstrating its
# functionality by running each modules driver file 

# build + run test drivers in Makefile 
make arith
make calculus
make linalg
make ml_dl
make num-theory

# delete generated binaries
make clean-mods

