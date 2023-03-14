#ifndef PROJECT_FILEREADER_H
#define PROJECT_FILEREADER_H

#include <iostream>
#include "Station.h"
#include <limits>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <fstream>
#include "headers/Segment.h"

class fileReader{

    public:
        std::vector<Station*> readStations(std::istream &stationsFile);
        void readNetworks(std::string inputFile);
};

#endif //PROJECT_FILEREADER_H

