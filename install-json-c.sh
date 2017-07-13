#!/bin/sh
set -ex
git clone https://github.com/json-c/json-c.git
cd json-c
sh autogen.sh
./configure --prefix=/usr && make && sudo make install
