#!/usr/bin/env bash

THIS_DIR=$(cd $(dirname $0); pwd)

cd $THIS_DIR/build

python3 -m http.server 8888
