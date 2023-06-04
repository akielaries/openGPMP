#!/bin/sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ../tests/openGPMP_tests
