#!/bin/zsh

# Run this from src/

mkdir build
cd build

/Users/pedro/Qt/6.6.1/macos/bin/qmake .. "CONFIG+=deploy" "CONFIG+=release"
make -j6

rm ./dsda-launcher.app/Contents/Resources/dsda-doom
rm ./dsda-launcher.app/Contents/Resources/dsda-doom.wad

cp ~/Documents/Github/dsda-doom/prboom2/build/dsda-doom ./dsda-launcher.app/Contents/Resources/dsda-doom
cp ~/Documents/Github/dsda-doom/prboom2/build/dsda-doom.wad ./dsda-launcher.app/Contents/Resources/dsda-doom.wad
cp -r ~/Documents/Github/dsda-doom/prboom2/build/libs_arm64 ./dsda-launcher.app/Contents/Resources/
cp -r ~/Documents/Github/dsda-doom/prboom2/build/libs_x64 ./dsda-launcher.app/Contents/Resources/

/Users/pedro/Qt/6.6.1/macos/bin/macdeployqt  ./dsda-launcher.app

create-dmg --app-drop-link 10 10 ./dsda-launcher.dmg ./dsda-launcher.app