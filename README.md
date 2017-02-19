# PANDEMIC - COMP 345 W2017 - Team Elephants

[![Build Status](https://travis-ci.com/jephir/pandemic.svg?token=H5s5urysT233MRnGw5EA&branch=master)](https://travis-ci.com/jephir/pandemic)

Implements the PANDEMIC role playing game.

## Setup

### Visual Studio

1. Run *build.cmd*
2. Open *build/pandemic.sln*

After pulling changes, do these steps again to update the project files.

#### Adding files to the project

1. Open *CMakeLists.txt*
2. Add the file name to `SOURCE_FILES` variable
3. Run *build.cmd* to regenerate the Visual Studio solution

### Linux

```bash
$ mkdir build && cmake .. && make
```

## Design

The *application* object contains the game loop. It reads a command string from standard input and looks it up in the command map. Then, the corresponding *command* object runs with a *context* and arguments.

A *context* is an object that contains references to the game state. Commands call methods on *state* objects to implement their actions.

Game objects are identified using a *handle*; an opaque object that can be compared and printed.

### .panmap.txt file format

Contains a PANDEMIC map in plain text. Each line contains the city *color*, *name*, and one or more *connected cities*, seperated by whitespace. Example:

`blue montreal new_york washington chicago`

## Authors

* Marco Tropiano
* Julian Hoang
* Tom Bach
* Guillaume Giffard
