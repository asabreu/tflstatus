#!/bin/sh
set -ex
git clone https://github.com/json-c/json-c.git
cd json-c
mkdir build
cd build
../cmake-configure --prefix=/usr && make && sudo make install
