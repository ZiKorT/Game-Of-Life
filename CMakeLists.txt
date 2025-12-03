cmake_minimum_required(VERSION 3.17)
project(Game_Of_Life)

set(CMAKE_CXX_STANDARD 20)

# --- 1. TÉLÉCHARGEMENT SFML ---
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

# --- 2. EXÉCUTABLE DU JEU ---
add_executable(Game_Of_Life
        main.cpp
        src/State.cpp
        src/Rule.cpp
        src/Cell.cpp
        src/Grid.cpp
        src/Interface.cpp
        src/FileManager.cpp
)

# Liaison avec la SFML (Uniquement pour le jeu)
target_link_libraries(Game_Of_Life sfml-graphics sfml-window sfml-system)

# Options pour rendre le .exe portable (tout inclus dedans)
target_link_options(Game_Of_Life PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
)

# --- 3. EXÉCUTABLE DES TESTS ---
add_executable(RunTests
        tests.cpp            # <--- C'est ici que ça change (plus de src/)
        src/State.cpp
        src/Cell.cpp
        src/Grid.cpp
        src/FileManager.cpp
        src/Rule.cpp
)

# Options pour rendre le .exe de test portable aussi
target_link_options(RunTests PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
)

# --- 4. CONFIG WINDOWS (Pour trouver les fichiers input.txt etc) ---
if(WIN32)
    set_target_properties(Game_Of_Life PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    set_target_properties(RunTests PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()