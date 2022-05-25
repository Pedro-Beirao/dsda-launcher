# Intructions for compiling dsda-launcher for Linux

Tested with Ubuntu LTS 20.04

___

### Tools needed:

## Qt - https://www.qt.io/download
```
Tested with Qt 6.2.2

You can install it with the Qt online installer.
If you instead use your package manager make sure you have version 6.2.2 or above (check using 'qmake -v').


```
<img width="300" alt="Screenshot 2021-06-09 at 12 44 33" src="https://user-images.githubusercontent.com/82064173/121386518-fbd48c00-c941-11eb-8abc-bc2e1e7e5a69.png"><img width="250" alt="Screenshot 2021-06-09 at 12 46 06" src="https://user-images.githubusercontent.com/82064173/121386962-33433880-c942-11eb-9528-a3923dc4ee52.png">
```
When running the installer, I recommend that you install the "Qt for desktop environment".
```
<img width="400" alt="Screenshot 2021-06-09 at 10 56 12" src="https://user-images.githubusercontent.com/82064173/121387513-a351be80-c942-11eb-9962-536a66c03689.png">

## qmake
```
This comes installed with Qt, no need to do anything.
```

## make
```
make is a GNU program, it's usually preinstalled with all GNU/Linux distributions so no need to do anything here.
```
___
## Compiling

1. Download the .zip file from this repository

2. Extract it & open the folder
 
3. Put the **dsda-doom.wad** file (not included in this repo) inside the dsda-launcher folder

      ^^^ Very important
      
   Note: if you built dsda-doom's binaries but didn't install it you will have to symlink it here too.

4. Create a "build" folder
```
mkdir build & cd build
```

Your dsda-launcher folder should look like this: 

![Screenshot 2021-07-07 at 10 22 17](https://user-images.githubusercontent.com/82064173/124734657-40395480-df0d-11eb-81c1-fd19231c5035.jpg)


5. Run qmake from inside of the build folder

If you installed qmake from a package manager run the following and go to step 6:-
```
qmake ..
```

If you installed Qt with the online installer instead do this:-

To make things simple, alias 'qmake' to it's binary's path.
```
alias qmake='[PathToQt]/[version number]/gcc_64/bin/qmake
```
**For example** if you installed Qt 6.2.2 in your home directory the command would be:
```
alias qmake='/home/username/Qt/6.2.2/gcc_64/bin/qmake
```
After that run qmake **inside the build folder**.
```
qmake ..
```

6. Run make
```
make
```

There you go!
You can now use the launcher.
