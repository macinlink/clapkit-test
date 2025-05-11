# CKTest

A simple example app for Clapkit.

## Usage

Make a build folder, switch to it.
```
mkdir build
cd build
```

If you want debug logs,
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

Else:
```
cmake -DCMAKE_BUILD_TYPE=Release ..
```

Then finally, make and run:
```
make
LaunchAPPL -e minivmac CKTest.APPL
```
