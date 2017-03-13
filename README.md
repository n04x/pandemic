# PANDEMIC - COMP 345 W2017 - Team Elephants

[![Build Status](https://travis-ci.com/jephir/pandemic.svg?token=H5s5urysT233MRnGw5EA&branch=master)](https://travis-ci.com/jephir/pandemic)

Implements the PANDEMIC role playing game.

## Setup

### Visual Studio

1. Run *bootstrap.cmd*
2. Open *build/pandemic.sln*

After pulling changes, do these steps again to update the project files.

#### Adding files to the project

1. Open *CMakeLists.txt*
2. Add the file path to `SOURCE_FILES` variable
3. Run *bootstrap.cmd* to regenerate the Visual Studio solution

### Linux

```bash
$ mkdir build && cd build
$ cmake ..
$ make
```

## Design

The *application* class contains the game loop. It reads a command string from standard input and looks it up in the controller map. Then, the corresponding *controller* runs with a *context*, arguments, and output stream.

The *context* contains the entire game state. Each state is encapsulated in a *model* class. Controllers implement their actions by calling methods on the model.

Game objects are identified using a *handle* - an opaque object that can be compared and printed. By using handles, all dynamic memory allocations for game objects are contained to the model classes. This ensures that there are no memory leaks or dangling references, as the game objects are not exposed to the controllers.

After every successful command, the command is saved to a buffer. This buffer can be written to a file using the `save` command. It can then be loaded by using the `load` command. This allows for saving of the entire game state by replaying the command history to regenerate the runtime game objects.

### .pandemic.txt file format

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
