#!/bin/sh
set -ex
git clone https://github.com/json-c/json-c.git
mkdir json-c-build
cd json-c-build
cmake -DCMAKE_INSTALL_PREFIX=/usr ../json-c
make
make test
make install
