cmake_minimum_required(VERSION 3.2)
project(pandemic)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp model/players_model.h handle.h application.cpp application.h controller/controller.h controller/reference_card.cpp controller/reference_card.h context.h controller/setup.cpp controller/setup.h controller/status.cpp controller/status.h model/decks_model.h model/cities_model.h controller/load.cpp controller/load.h controller/cities.cpp controller/cities.h controller/place_pawn.cpp controller/place_pawn.h controller/save.cpp controller/save.h model/game_model.h controller/editor/add_city.cpp controller/editor/add_city.h)
add_executable(pandemic ${SOURCE_FILES})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT pandemic)
