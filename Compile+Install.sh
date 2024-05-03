#!/bin/bash

# building
	mkdir -p "./src/build"
	cd "./src/build"
	qmake6 ..
	make
	
#installing
	sudo mv ./dsda-launcher /bin
	cd ..
	sudo install -Dm644 ./icons/dsda-launcher.png "${pkgdir}"/usr/share/pixmaps/dsda-launcher.png
	sudo install -Dm644 ./icons/dsda-Launcher.desktop "${pkgdir}"/usr/share/applications/dsda-Launcher.desktop
	
# if you want to vomit from this install script blame this fool: Zse#0330
