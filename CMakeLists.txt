cmake_minimum_required(VERSION 3.24)
project(feup_da_project)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(.)


add_executable(
        feup_da_project
        source/main.cpp

        dataset/network.csv
        dataset/stations.csv
        headers/FileReader.h
        source/FileReader.cpp
        headers/Segment.h
        source/Segment.cpp
        headers/Station.h
        source/Station.cpp
        headers/Graph.h
        source/Graph.cpp)
