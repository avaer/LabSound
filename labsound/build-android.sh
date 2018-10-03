#!/bin/bash

./android-config.sh
make clean
cmake -D ANDROID=1 .
make -j4
