#!/bin/bash

DESTINATION="/home/kajames/Dropbox/Health Care Parameters/"
for file in configs/*.json
do
    echo bin/healthdp --i $file --o "$DESTINATION"
    bin/healthdp --i $file --o "$DESTINATION"
done
