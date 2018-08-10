 #!/bin/bash

cmake . -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DCMAKE_SYSTEM_NAME="Android" -DANDROID_NDK=$ANDROID_NDK -DANDROID_TOOLCHAIN=clang -DANDROID_PLATFORM=android-27 -DANDROID_ABI="arm64-v8a" -DANDROID_STL=c++_shared
