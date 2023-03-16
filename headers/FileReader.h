#ifndef PROJECT_FILEREADER_H
#define PROJECT_FILEREADER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Graph.h"
#include "Segment.h"
#include "Station.h"

class FileReader {
    std::string path;
    Graph *graph;

public:
    FileReader(const std::string &path, Graph *graph);
    static bool discard(char c) ;
    void readStations();
    [[nodiscard]] std::string strip(const std::string &str) const;
    std::string capitalizeFirstLetter(const std::string& str);
    void readNetworks();
};

#endif //PROJECT_FILEREADER_H

