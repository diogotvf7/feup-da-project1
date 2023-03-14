cmake_minimum_required(VERSION 3.24)
project(feup_da_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(feup_da_project
        dataset/network.csv
        dataset/stations.csv
        headers/fileReader.h
        headers/Segment.h
        headers/Station.h
        source/fileReader.cpp
        source/Segment.cpp
        source/main.cpp
        source/Station.cpp
        )
