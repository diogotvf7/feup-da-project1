#ifndef FEUP_DA_PROJECT_NETWORKMANAGER_H
#define FEUP_DA_PROJECT_NETWORKMANAGER_H

#include <vector>
#include <string>
#include <utility>

#include "Network.h"
#include "StationTrack.h"
#include "FileReader.h"

#define tracks_vector std::vector<std::pair<std::string,std::string>>

class NetworkManager {
public:
    void reduceConnectivity(Network *network, const tracks_vector &tracks, const std::vector<std::string> &stations);
    Network *createGraph(const std::string &datasetPath);
    double maxFlowBetween(Network *network, const std::string &source, const std::string &target);
    void deleteGraph(Network *network);
};


#endif //FEUP_DA_PROJECT_NETWORKMANAGER_H
