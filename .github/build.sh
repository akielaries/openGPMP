#! /bin/sh
# script to run the vpaSTRM scrip

#./bin/run/convert-001 "$@" | tee logs/STDOUT-001.txt
cd ../ && ./bin/run/vpaSTRM-1x "$@" 

# run bin, display stderr and stdout to seperate files

