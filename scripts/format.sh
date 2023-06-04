#!/bin/sh
find ../ -regex '.*\.\(c\|cu\|cuh\|cpp\|hpp\|h\|cxx\)' -exec clang-format -style=file -i {} \;
