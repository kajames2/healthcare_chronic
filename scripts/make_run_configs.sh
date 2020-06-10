#!/bin/bash

cd configs
python write_configs.py ../"${$1#configs/}"
cd ..
scripts/run_configs.sh
