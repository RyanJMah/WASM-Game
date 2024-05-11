#!/bin/bash

trap 'exit' INT TERM QUIT

REPO_DIR=$(cd $(dirname $0); pwd)/..

cd $REPO_DIR/build

# Loop until keyboard interrupt
while true;
do
    find . -name '*.html' | entr -r python3 $REPO_DIR/scripts/http_server.py
    sleep 1
done
