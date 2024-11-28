# Intructions for compiling dsda-launcher for MacOS


## Qt - https://www.qt.io/download
```
All commits tested using qt6.2.0

You could also install qt using 'brew'
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

// qmake .. "CONFIG+=deploy"
// ^ this will compile for both x64 and arm64 archs
```
4. Run make
```
make
```

## Distributing

For distribution of the binary, you can use `macdeployqt` which patches the final app bundle with everything the users will need to run in the system.
