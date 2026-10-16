cmake_minimum_required(VERSION 3.20)

project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(Pacman
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
)

target_link_libraries(Pacman PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(Pacman PRIVATE
    include
)