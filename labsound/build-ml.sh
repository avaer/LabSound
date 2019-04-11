#!/bin/bash

# pushd ..
# npm install native-video-deps
# popd

rm -Rf CMakeCache.txt CMakeFiles
cmake -D CMAKE_TOOLCHAIN_FILE=.\\toolchain -D LUMIN=1 .
# make clean
make -j4
