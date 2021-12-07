# Rifts: Promise of Power

A toolchain to build a DRM- and copy-protection-free version of Rifts:
Promise of Power for the Nokia N-Gage.

## Status

The project  has not  yet been completed.  At the moment  it is  not yet
possible to compile a working version of Rifts.

## Compiling

First clone the repository:
```bash
git clone git@github.com:mupfelofen-de/Rifts.git
```

The easiest way to compile the project is Visual Studio 2019 with [C++
CMake tools for
Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#installation)
installed. Just open the project inside the IDE and everything else is
set up automatically.

Alternatively just use [MSYS2](https://www.msys2.org/) and compile it using CMake:
```bash
mkdir build
cd build
cmake ..
make
```
