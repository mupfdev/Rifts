# Rifts: Promise of Power

A toolchain designed to build a DRM- and copy-protection-free version of
Rifts: Promise of Power for the Nokia N-Gage.

## Status

The project has not yet been completed.  At the moment it is not yet
possible to compile a working version of Rifts.

## Compiling

First clone the repository:
```bash
git clone git@github.com:mupfelofen-de/Rifts.git
```

The GCC compiler for Symbian S60 is based on Cygwin. For it to work, its
path (`Symbian\6.1\Shared\EPOC32\gcc\bin`)should be entered in your
`$PATH` environment variable, otherwise it will not be able to find the
`cygwin1.dll` file.

Once you have done this, simply launch Visual Studio 2019 with [C++
CMake tools for
Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#installation)
installed and open the project directory. Everything else is set up
automatically.
