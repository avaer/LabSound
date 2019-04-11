#!/bin/bash

set -e

export MLSDK=${MLSDK:-/mnt/c/Users/avaer/MagicLeap/mlsdk/v0.19.0}

# pushd ..
# npm install native-video-deps
# popd

if [ ! -d magicleap-js ]; then
  git clone https://github.com/webmixedreality/magicleap-js
else
  pushd magicleap-js
  git pull --rebase
  popd
fi

./magicleap-js/hack-toolchain.js

cmake -D CMAKE_TOOLCHAIN_FILE=.\\toolchain -D LUMIN=1 .
make clean
make -j4
