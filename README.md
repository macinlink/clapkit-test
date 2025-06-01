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
cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_LOCAL_CLAPKIT=OFF ..
```

Else:
```
cmake -DCMAKE_BUILD_TYPE=Release -DUSE_LOCAL_CLAPKIT=OFF ..
```

Then finally, make and run:
```
make
LaunchAPPL -e minivmac CKTest.APPL
```
