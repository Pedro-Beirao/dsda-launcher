#!/usr/bin/env sh

export PROJECT=dsda-launcher
export ICONDIR=$PROJECT.iconset
export PNGICON=$PROJECT.png

mkdir -p $ICONDIR

# Normal screen icons
for SIZE in 16 32 64 128 256 512; do
sips -z $SIZE $SIZE $PNGICON --out $ICONDIR/icon_${SIZE}x${SIZE}.png ;
done

# Retina display icons
for SIZE in 32 64 256 512; do
sips -z $SIZE $SIZE $PNGGICON --out \
	$ICONDIR/icon_$(expr $SIZE / 2)x$(expr $SIZE / 2)x2.png ;
done

# Make a multi-resolution Icon
iconutil -c icns -o $PROJECT.icns $ICONDIR
rm -rf $ICONDIR #it is useless now
