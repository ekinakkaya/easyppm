#!/bin/bash
# https://stackoverflow.com/a/67426191
mkdir images
for i in *.ppm;
    do name=`echo "$i" | cut -d'.' -f1`;
    echo "$name"

    ffmpeg -i "$i" "images/${name}.png"
    mv $i images/$i
done


