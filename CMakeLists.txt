cmake_minimum_required(VERSION 3.2)
project(pandemic)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp state/players.h handle.h application.cpp application.h command/command.h command/reference_card.cpp command/reference_card.h context.h command/setup.cpp command/setup.h command/status.cpp command/status.h state/decks.h state/map.h command/load.cpp command/load.h command/cities.cpp command/cities.h command/place_pawn.cpp command/place_pawn.h command/save.cpp command/save.h)
add_executable(pandemic ${SOURCE_FILES})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT pandemic)
