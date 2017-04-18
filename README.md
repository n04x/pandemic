# PANDEMIC - COMP 345 W2017 - Team Elephants

Implements the PANDEMIC role playing game.

## Setup

### Visual Studio 2015

1. Run *bootstrap.cmd*
2. Open *build/pandemic.sln*

After pulling changes, do these steps again to update the project files.

#### Adding files to the project

1. Open *CMakeLists.txt*
2. Add the file path to `SOURCE_FILES` variable
3. Run *bootstrap.cmd* to regenerate the Visual Studio solution

### clang 3.4 with CMake

```bash
$ mkdir build && cd build
$ cmake ..
$ make
```

## .pandemic.txt file format

Contains commands separated by newlines. Blank lines or lines that start with `#` are ignored by the parser.

Example:

```bash
# this is a comment
add-player red
add-city blue san_francisco chicago los_angeles tokyo manila
load other-script
```

Files can be recursively loaded using the `load` command. This allows command scripts to be split and loaded from multiple files.

## Authors

* Marco Tropiano
* Julian Hoang
* Tom Bach
