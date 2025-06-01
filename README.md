# CKTest

A simple example app for [Clapkit](https://github.com/macinlink/clapkit).

![Screenshot](https://raw.githubusercontent.com/macinlink/clapkit-test/refs/heads/main/Clapkit-Test-App.png)

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

**Note:** You'll need to have Macsbug installed for debug mode, or the application will crash on start. Debug mode also keeps track of memory usage and leaks.

Else:
```
cmake -DCMAKE_BUILD_TYPE=Release -DUSE_LOCAL_CLAPKIT=OFF ..
```

Then finally, make and run:
```
make
LaunchAPPL -e minivmac CKTest.APPL
```
