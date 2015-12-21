#Run this file to generate the Makefiles using Cmake
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-Edison.cmake -DCMAKE_BUILD_TYPE=Debug ..
