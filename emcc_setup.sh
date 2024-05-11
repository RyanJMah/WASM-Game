#!/usr/bin/env bash

THIS_DIR=$(cd $(dirname $0); pwd)

cd $THIS_DIR
git submodule update --init --recursive


cd $THIS_DIR/emsdk

./emsdk install latest
./emsdk activate latest

source ./emsdk_env.sh

cd $THIS_DIR
