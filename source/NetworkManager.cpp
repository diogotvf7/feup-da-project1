#include "headers/NetworkManager.h"

using namespace std;

struct CMP {
    bool operator()(const pair<string, double> &a, const pair<string, double> &b) {
        return a.second < b.second;
    }
};

void NetworkManager::reduceConnectivity(Network *network, const tracks_vector &tracks,
                                                    const vector<string> &stations) {
    for (auto track : tracks)
        network->removeTrack(track.first, track.second);
    for (string station : stations)
        network->removeStation(station);
}

Network *NetworkManager::createGraph(const string &datasetPath) {
    Network *network = new Network();
    Util::readStations(datasetPath, network);
    Util::readNetwork(datasetPath, network);
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

vector<Station*> NetworkManager::topAffectedStations(Network *normalNetwork, Network *reducedNetwork, int n) {

    vector<Station*> res;
    unordered_map<string,double> realMaxFlow, reducedMaxFlow, diff;

    for (Station *src : normalNetwork->getStationsSet()) {
        for (Station *dest: normalNetwork->getStationsSet()) {
            string revKey = dest->getName() + "/" + src->getName();                             // Check if reverse pair
            if (src == dest || realMaxFlow.find(revKey) != realMaxFlow.end()) continue;     //  already exists
            normalNetwork->edmondsKarp(src->getName(), dest->getName());
            double flow = dest->getFlow();
            string key = src->getName() + "/" + dest->getName();
            realMaxFlow.emplace(key, flow);
        }
    }

    for (Station *src : reducedNetwork->getStationsSet()) {
        for (Station *dest: reducedNetwork->getStationsSet()) {
            string revKey = dest->getName() + "/" + src->getName();                             // Check if reverse pair
            if (src == dest || reducedMaxFlow.find(revKey) != reducedMaxFlow.end()) continue;     //  already exists
            reducedNetwork->edmondsKarp(src->getName(), dest->getName());
            double flow = dest->getFlow();
            string key = src->getName() + "/" + dest->getName();
            reducedMaxFlow.emplace(key, flow);
        }
    }

    for (auto &[key, maxFlow] : realMaxFlow) {
        double aux = 0;
        string src = Util::split(key, '/')[0], dest = Util::split(key, '/')[1];
        string revKey = key.substr(key.find('/') + 1) + "/" + key.substr(0, key.find('/'));
        if (reducedMaxFlow.find(key) != reducedMaxFlow.end())
            aux = reducedMaxFlow[key];
        else if (reducedMaxFlow.find(revKey) != reducedMaxFlow.end())
            aux = reducedMaxFlow[revKey];
        else
            aux = 0;
        double maxFlowDifference = abs(maxFlow - aux);
        if (maxFlowDifference == 0) continue;
        diff[src] += maxFlowDifference;
        diff[dest] += maxFlowDifference;
    }

    priority_queue<pair<string,double>, vector<pair<string,double>>, CMP> pq;
    for (auto &[key, value] : diff)
        pq.emplace(key, value);

    for (int i = 0; i < n; i++) {
        if (pq.empty()) break;
        res.push_back(normalNetwork->findStation(pq.top().first));
        pq.pop();
    }
    return res;
}


