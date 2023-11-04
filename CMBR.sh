#!/bin/bash

mkdir -p linux-build-debug
cd linux-build-debug
rm Spectra

cmake .. -DARGV=$1 

make

./Spectra $@