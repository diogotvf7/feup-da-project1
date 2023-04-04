#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>
#include <sstream>

#include "Network.h"
#include "StationTrack.h"

namespace FileReader {

    bool discard(char c);

    std::string capitalizeFirstLetter(const std::string &str);

    std::string strip(const std::string &str);

    void readStations(const std::string &path, Network *graph);

    void readNetwork(const std::string &path, Network *graph);
}

#endif //FILEREADER_H
