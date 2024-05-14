#!/bin/bash

 export CC=/usr/bin/gcc-10
 export CXX=/usr/bin/g++-10
 export CUDA_ROOT=/usr/local/cuda
 ln -s /usr/bin/gcc-10 $CUDA_ROOT/bin/gcc
 ln -s /usr/bin/g++-10 $CUDA_ROOT/bin/g++