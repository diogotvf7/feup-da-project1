#include "headers/NetworkManager.h"

using namespace std;

struct CMP {
    bool operator()(const pair<string, double> &a, const pair<string, double> &b) {
        return a.second < b.second;
    }
};

namespace NetworkManager {
    void reduceConnectivity(Network *network, const tracks_vector &tracks,
                            const vector <string> &stations) {
        for (auto track: tracks)
            network->removeTrack(track.first, track.second);
        for (string station: stations)
            network->removeStation(station);
    }

    Network *createGraph(const string &datasetPath) {
        Network *network = new Network();
        Util::readStations(datasetPath, network);
        Util::readNetwork(datasetPath, network);
        return network;
    }

    int maxFlowBetween(Network *network, Station *source, Station *target) {
        network->edmondsKarp(source, target);
        return target->getFlow();
    }

    void deleteGraph(Network *network) {
        delete network;
    }

    vector<Station *> topAffectedStations(Network *normalNetwork, Network *reducedNetwork, int n) {

        vector<Station *> res;
        unordered_map<string, double> realMaxFlow, reducedMaxFlow, diff;
        vector<Station *> stationSet = normalNetwork->getStationsSet(), reducedStationSet = reducedNetwork->getStationsSet();

        for (int i = 0; i < normalNetwork->getNumStations(); i++) {
            Station *src = stationSet[i];
            for (int j = i; j < normalNetwork->getNumStations(); j++) {
                Station *dest = stationSet[j];
                string revKey =
                        dest->getName() + "/" + src->getName();                             // Check if reverse pair
                // TODO: is Checking reverse pair really needed?
                if (src == dest || realMaxFlow.find(revKey) != realMaxFlow.end()) continue;     //  already exists
                normalNetwork->edmondsKarp(src, dest);
                double flow = dest->getFlow();
                string key = src->getName() + "/" + dest->getName();
                realMaxFlow.emplace(key, flow);

            }
        }

        for (int i = 0; i < reducedNetwork->getNumStations(); i++) {
            Station *src = reducedStationSet[i];
            for (int j = i; j < reducedNetwork->getNumStations(); j++) {
                Station *dest = reducedStationSet[j];
                string revKey =
                        dest->getName() + "/" + src->getName();                             // Check if reverse pair
                        // TODO: is Checking reverse pair really needed?
                if (src == dest || reducedMaxFlow.find(revKey) != reducedMaxFlow.end()) continue;     //  already exists
                reducedNetwork->edmondsKarp(src, dest);
                double flow = dest->getFlow();
                string key = src->getName() + "/" + dest->getName();
                reducedMaxFlow.emplace(key, flow);
            }
        }

        for (auto &[key, maxFlow]: realMaxFlow) {
            string src = Util::split(key, '/')[0], dest = Util::split(key, '/')[1];
            if (reducedNetwork->findStation(src) == nullptr) continue;
            if (reducedNetwork->findStation(dest) == nullptr) continue;
            double maxFlowDifference = abs(maxFlow - reducedMaxFlow[key]);
            diff[src] += maxFlowDifference;
            diff[dest] += maxFlowDifference;
        }

        priority_queue<pair<string, double>, vector<pair<string, double>>, CMP> pq;
        for (auto &[key, value]: diff)
            pq.emplace(key, value);

        while (!pq.empty() && n-- > 0) {
            res.push_back(normalNetwork->findStation(pq.top().first));
            pq.pop();
        }

        return res;
    }
}

