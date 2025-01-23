#!/bin/bash

REPO="kraflab/dsda-doom"

TEMP=`mktemp --directory`
DEST=$1

TAG=$(curl -s https://api.github.com/repos/$REPO/releases/latest | sed -Ene '/^ *"tag_name": *"(v.+)",$/s//\1/p')
VERSION=${TAG:1}

v_arm64="dsda-doom-$VERSION-mac-arm64"
v_x64="dsda-doom-$VERSION-mac-x86_64"

CleanUp()
{
  rm -rf $TEMP
}

Download()
{
  if curl -L -o $TEMP/$v_arm64.zip "https://github.com/$REPO/releases/download/$TAG/$v_arm64.zip"
  then
    unzip $TEMP/$v_arm64.zip -d $TEMP
  else
    echo "Error downloading update"
    CleanUp
    exit 1
  fi


  if curl -L -o $TEMP/$v_x64.zip "https://github.com/$REPO/releases/download/$TAG/$v_x64.zip"
  then
    unzip $TEMP/$v_x64.zip -d $TEMP
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
  lipo -create $TEMP/$v_arm64/dsda-doom $TEMP/$v_x64/dsda-doom -output $DEST/dsda-doom
  cp $TEMP/$v_arm64/dsda-doom.wad $DEST/dsda-doom.wad
  cp $TEMP/$v_arm64/COPYING.txt $DEST/COPYING.txt
  cp -r $TEMP/$v_arm64/libs_arm64 $DEST/libs_arm64
  cp -r $TEMP/$v_x64/libs_x86_64 $DEST/libs_x86_64
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