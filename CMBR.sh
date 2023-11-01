#!/bin/bash

mkdir -p linux-build-debug
cd linux-build-debug

cmake .. -DARGV=$1 

make

./Spectra $@