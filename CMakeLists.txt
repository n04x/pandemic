cmake_minimum_required(VERSION 3.2)
project(pandemic)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp players.cpp players.h handle.h application.cpp application.h command/command.h command/reference_card.cpp command/reference_card.h command/context.h command/setup.cpp command/setup.h command/status.cpp command/status.h)
add_executable(pandemic ${SOURCE_FILES})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT pandemic)
