# Intructions for compiling dsda-launcher for Windows


## Qt - https://www.qt.io/download
```
All commits tested using the latest qt5 version available

If you want to build statically, I reccoment using msys2 and the mingw-w64-x86_64-qt5-static package
Take a look at .github/workflows/main.yml in this repo
```

## Compiling

1. Clone this repo
```
git clone https://github.com/Pedro-Beirao/dsda-launcher.git
```

2. Create a "build" folder inside src/
```
cd dsda-launcher
cd src

mkdir build
cd build
```
3. Run qmake from the build folder
```
qmake ..
```
4. Run make
```
make
```
Now copy the launcher to the same folder as dsda-doom

## Distributing

For distribution of the binary, you should use a static build of qt, in order to remove the need to ship so many dll files. This way all you end up with is the launcher executable.

Anyway, for a dynamic build, you would get all the needed dll files using `windeployqt` and ship it all.
