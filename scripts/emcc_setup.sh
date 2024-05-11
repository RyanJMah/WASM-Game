#!/usr/bin/env bash

REPO_DIR=$(cd $(dirname $0); pwd)/..


cd $REPO_DIR
git submodule update --init --recursive


cd $REPO_DIR/emsdk

./emsdk install latest
./emsdk activate latest

source ./emsdk_env.sh

cd $REPO_DIR
