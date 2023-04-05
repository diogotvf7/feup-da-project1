#include "headers/NetworkManager.h"

using namespace std;

void NetworkManager::reduceConnectivity(Network *network, const tracks_vector &tracks,
                                                    const vector<string> &stations) {
    for (auto track : tracks)
        network->removeTrack(track.first, track.second);
    for (string station : stations)
        network->removeStation(station);
}

Network *NetworkManager::createGraph(const string &datasetPath) {
    Network *network = new Network();
    FileReader::readStations(datasetPath, network);
    FileReader::readNetwork(datasetPath, network);
    return network;
}

double NetworkManager::maxFlowBetween(Network *network, const string &source, const string &target) {
    network->edmondsKarp(source, target);
    Station *station = network->findStation(target);
    return station->getFlow();
}

void NetworkManager::deleteGraph(Network *network) {
    delete network;
}


