#!/bin/bash

rm -r apps

mkdir data 2> /dev/null
mkdir apps 2> /dev/null
mkdir graphs 2> /dev/null
mkdir data_preproc 2> /dev/null
mkdir tables_data 2> /dev/null

./build_apps.sh
./update_data.sh 1
python3 make_preproc.py
python3 tables_data.py
./make_postproc.sh
