# Rifts: Promise of Power

A toolchain designed to build a DRM-free version of Rifts: Promise of
Power for the Nokia N-Gage.

## How-to

First clone the repository:
```bash
git clone git@github.com:mupfelofen-de/Rifts.git
```

Unpack the complete source code of Rifts in the root directory. This
should now be in the `Rifts` subdirectory.

In order to build the sources without the proprietary Nokia N-Gage SDK,
the network and Bluetooth functionality must be disabled in the source
code. There is a patch for this in the root directory.

However, please make sure that the files to be patched are writable,
because in the original archive, all files are marked as read-only by
default.

To apply the patch just use the standard GNU patch tool as follows:
```bash
patch -s -p0 < source.diff
```

The GCC compiler for Symbian S60 is based on Cygwin. For it to work, its
path `[Project_Dir]\Symbian\6.1\Shared\EPOC32\gcc\bin` should be
included in your `$PATH` environment variable, otherwise it will not be
able to find the file `cygwin1.dll`.

Once you have done this, simply launch Visual Studio 2019 with [C++
CMake tools for
Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#installation)
installed and open the project directory.

Wait until Visual Studio has generated the CMake Cache and then simply
click Build All or press F7.

The patched source code has a few optional features that I would like to
extend over time. These can be set directly in Visual Studio under
`Project CMake → Settings`.
