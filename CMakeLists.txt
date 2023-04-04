cmake_minimum_required(VERSION 3.23)
project(feup_da_project)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(.)


add_executable(
        feup_da_project
        source/main.cpp

        dataset/real-dataset/network.csv
        dataset/real-dataset/stations.csv
        headers/FileReader.h
        source/FileReader.cpp
        headers/StationTrack.h
        source/StationTrack.cpp
        headers/Network.h
        source/Network.cpp
)
