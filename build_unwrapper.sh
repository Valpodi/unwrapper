#!/usr/bin/env bash

source scl_source enable devtoolset-9

#build the unwrapper
rm -rf cmake
mkdir -p cmake
pushd cmake
cmake3 -DCMAKE_BUILD_TYPE=Release ..
make
popd
cp cmake/Unwrapper ./unwrapper_linux_x86

