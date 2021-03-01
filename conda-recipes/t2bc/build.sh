#!/bin/bash

set -x

export PYTHONNOUSERSITE=1
# Enables static linking of stdlibc++
export LLVMLITE_CXX_STATIC_LINK=1

$PYTHON setup.py build --force
$PYTHON setup.py install
