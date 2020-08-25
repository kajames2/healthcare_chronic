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
    for file in $dir/*_conf.json
    do
	      echo "$file"
	      filename="${file#$dir/}"
	      filename2="${filename%.*}"
	      echo bin/healthdp --i $file --o "$destdir/"
	      bin/healthdp --i $file --o "$destdir/"
	      mv "$file" "$destdir/"
	      python3 "$DESTINATION/payout_table_maker.py" "$destdir/$filename2" "$destdir/$filename"
	      python3 "$DESTINATION/output_reader.py" "$destdir/$filename2"
	      rm "$destdir/$filename2.csv"
    done
    for file in $dir/*.json
    do
        mv "$file" "$destdir/"
    done
    rmdir "$dir"
    cd "$DESTINATION"
    python3 "plot_maker.py" "$shortdir"
    cd ..
done
