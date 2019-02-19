#!/bin/bash

mkdir -p output
DESTINATION="output/"
for file in configs/*.json
do
    echo bin/healthdp --i $file --o "$DESTINATION"
    bin/healthdp --i $file --o "$DESTINATION"
done
