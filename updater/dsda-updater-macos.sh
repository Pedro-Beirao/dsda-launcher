#!/bin/bash

REPO="kraflab/dsda-doom"

TEMP=`mktemp -d`
DEST=$1

TAG=$(curl -s https://api.github.com/repos/$REPO/releases/latest | sed -Ene '/^ *"tag_name": *"(v.+)",$/s//\1/p')
VERSION=${TAG:1}

pkg_name="dsda-doom-$VERSION-mac-uni"

CleanUp()
{
  rm -rf $TEMP
}

Download()
{
  if curl -L -o $TEMP/$pkg_name.zip "https://github.com/$REPO/releases/download/$TAG/$pkg_name.zip"
  then
    unzip $TEMP/$pkg_name.zip -d $TEMP
  else
    echo "Error downloading update"
    CleanUp
    exit 1
  fi
}

RemoveOld()
{
  [ -e $DEST/dsda-doom ] && rm -f $DEST/dsda-doom
  [ -e $DEST/dsda-doom.wad ] && rm -f $DEST/dsda-doom.wad
  [ -e $DEST/COPYING.txt ] && rm -f $DEST/COPYING.txt
  [ -e $DEST/libs ] && rm -rf $DEST/libs
  [ -e $DEST/libs_arm64 ] && rm -rf $DEST/libs_arm64
  [ -e $DEST/libs_x86_64 ] && rm -rf $DEST/libs_x86_64
}

CopyUpdate()
{
  cp $TEMP/$pkg_name/dsda-doom $DEST/dsda-doom
  cp $TEMP/$pkg_name/dsda-doom.wad $DEST/dsda-doom.wad
  cp $TEMP/$pkg_name/COPYING.txt $DEST/COPYING.txt
}

if [ $DEST ]
then
    if [ -e $DEST ]
    then
        Download
        RemoveOld
        CopyUpdate
        CleanUp

        echo "\ndsda-doom $VERSION has been installed succesfully!"
        exit
    else
        echo "Destination folder does not exist"
    fi
else
    echo "Error - Missing argument\n\nUsage: sh dsda-update-mac.sh /path/to/destination"
fi
