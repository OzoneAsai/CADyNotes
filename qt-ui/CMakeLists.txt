cmake_minimum_required(VERSION 3.16)
project(CADyNotesQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(CADyNotesQt
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
)

target_link_libraries(CADyNotesQt PRIVATE Qt6::Widgets)
