#!/bin/bash

mkdir -p "output/"
SOURCE="configs"
DESTINATION="output"
CURRENT=${pwd}
for dir in $SOURCE/*/
do
    shortdir="${dir#$SOURCE/}"
    destdir="$DESTINATION/$shortdir"
    mkdir "$destdir"
    for file in $dir/*.json
    do
	echo "$file"
	filename="${file#$dir/}"
	filename2="${filename%.*}"
	echo bin/healthdp --i $file --o "$destdir/"
	bin/healthdp --i $file --o "$destdir/"
	mv "$file" "$destdir/"
	python3 "$DESTINATION/output_reader.py" "$destdir/$filename2"
	rm "$destdir/$filename2.csv"
    done
    rmdir "$dir"
    cd "$DESTINATION"
    python3 "plot_maker.py" "$shortdir"
    cd "$CURRENT"

done
