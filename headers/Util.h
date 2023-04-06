#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>
#include <sstream>

#include "Network.h"
#include "StationTrack.h"

namespace Util {

    bool discard(char c);

    std::string center(std::string str, int width);

    std::string capitalizeFirstLetter(const std::string &str);

    std::string strip(const std::string &str);

    std::vector<std::string> split(const std::string &str, char delimiter);

    void readStations(const std::string &path, Network *graph);

    void readNetwork(const std::string &path, Network *graph);
}

#endif //FILEREADER_H
