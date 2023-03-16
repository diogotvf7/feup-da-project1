#ifndef PROJECT_FILEREADER_H
#define PROJECT_FILEREADER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Network.h"
#include "StationTrack.h"

class FileReader {
    std::string path;
    Network *graph;

public:
    FileReader(const std::string &path, Network *graph);
    static bool discard(char c) ;
    void readStations();
    [[nodiscard]] std::string strip(const std::string &str) const;
    std::string capitalizeFirstLetter(const std::string& str);
    void readNetworks();
};

#endif //PROJECT_FILEREADER_H

