cmake_minimum_required(VERSION 3.29)
project(PEA_Project)

MATH(EXPR stack_size "16 * 1024 * 1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,16777216")

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 20)

add_executable(
        PEA_Project main.cpp
        source/CzytnikGrafow.cpp
        source/Dijkstra.cpp
        source/GeneratorGrafow.cpp
        source/GrafManager.cpp
        source/ListaSasiedztwa.cpp
        source/MacierzIncydencji.cpp
        source/Menu.cpp
        source/Prim.cpp
        header/CzytnikGrafow.h
        header/Dijkstra.h
        header/GeneratorGrafow.h
        header/GrafManager.h
        header/ListaSasiedztwa.h
        header/MacierzIncydencji.h
        header/Menu.h
        header/Prim.h
)
