#!/bin/bash

rm -r apps

mkdir data 2> /dev/null
mkdir apps 2> /dev/null
mkdir results 2> /dev/null

./build_apps.sh
./update_data.sh 15