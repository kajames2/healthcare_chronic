#!/bin/bash

mkdir -p output
SOURCE="configs"
DESTINATION="output"
CURRENT=${pwd}
for file in $SOURCE/*.json
do
    filename="${file#$SOURCE/}"
    filename2="${filename%.*}"
    echo bin/healthdp --i $file --o "$DESTINATION/"
    bin/healthdp --i $file --o "$DESTINATION/"
    python3 "$DESTINATION/output_reader.py" "$DESTINATION/$filename2"
    rm "$DESTINATION/$filename2.csv"
done
