cmake_minimum_required(VERSION 3.17)
project(Game_Of_Life)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.1
)

set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(sfml)

include_directories(include)

add_executable(Game_Of_Life
        main.cpp
        src/State.cpp
        src/Rule.cpp
        src/Cell.cpp
        src/Grid.cpp
        src/Interface.cpp
        src/FileManager.cpp
)


target_link_libraries(Game_Of_Life sfml-graphics sfml-window sfml-system)

if(WIN32)
    set_target_properties(Game_Of_Life PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()
