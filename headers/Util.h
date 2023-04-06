#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

#include "Network.h"
#include "StationTrack.h"

class Network;

namespace Util {

    bool discard(char c);

    void cleanTerminal();

    std::string repeat(const std::string &str, int times);

    void printLoadingBar(int percentage, const std::string& message);

    std::string normalise(const std::string &s);

    bool isNumerical(const std::string &str);

    bool isAlpha(const std::string &str);

    std::string center(std::string str, int width);

    std::string capitalizeFirstLetter(const std::string &str);

    std::string strip(const std::string &str);

    std::vector<std::string> split(const std::string &str, char delimiter);

    void readStations(const std::string &path, Network *graph);

    void readNetwork(const std::string &path, Network *graph);
}

#endif //FILEREADER_H
