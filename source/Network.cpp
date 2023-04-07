#include "headers/Network.h"

using namespace std;

Station* Network::findStation(const string &stationName) const {
    for (Station* station : stationsSet)
        if (station->getName() == stationName)
            return station;
    return nullptr;
}

bool Network::addStation(Station* station) {
    if (findStation(station->getName()) == nullptr) {
        stationsSet.push_back(station);
        return true;
    }
    return false;
}

bool Network::addTrack(const string &source, const string &dest, double capacity, const string &service) {
    auto v1 = findStation(source);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addTrack(v2, capacity, service);
    return true;
}

bool Network::addBidirectionalTrack(const string &source, const string &dest, int capacity, const string &service) {

    Station* s1 = findStation(source);
    Station* s2 = findStation(dest);
    if (s1 == nullptr || s2 == nullptr) return false;
    Track* t1 = s1->addTrack(s2, capacity, service);
    Track* t2 = s2->addTrack(s1, capacity, service);
    t1->setReverse(t2);
    t2->setReverse(t1);
    return true;
}

void Network::removeTrack(const std::string src, const std::string dest) {
    auto srcItr = stationsSet.begin(), destItr = stationsSet.begin();
    while (srcItr != stationsSet.end() && (*srcItr)->getName() != src) srcItr++;     // Find source station
    while (destItr != stationsSet.end() && (*destItr)->getName() != dest) destItr++;     // Find source station
    if (srcItr == stationsSet.end() || destItr == stationsSet.end()) return;                                 // Source or destination station not found
    Station *srcStation = *srcItr;
    Station *destStation = *destItr;
    srcStation->removeOutgoingTrack(dest);
    destStation->removeIncomingTrack(src);
}

void Network::removeStation(const string &name) {
    auto itr = stationsSet.begin();
    while (itr != stationsSet.end() && (*itr)->getName() != name) itr++;    // Find station
    if (itr == stationsSet.end()) return;                                   // Station not found
    (*itr)->removeIncomingTracks();
    (*itr)->removeOutgoingTracks();
    stationsSet.erase(itr);                                         // Remove station from set
}


int Network::getNumStations()  const {
    return (int) stationsSet.size();
}

vector<Station*> Network::getStationsSet() const {
    return stationsSet;
}

vector<Track*> Network::getTracksSet() const {
    vector<Track*> tracksSet;
    for(Station* station : stationsSet) {
        for(Track* track : station->getAdj()) {
            tracksSet.push_back(track);
        }
    }
    return tracksSet;
}

void Network::testAndVisit(queue<Station *> &q, Track *t, Station *s, double residual) {
    if(!s->isVisited() && residual > 0) {
        s->setVisited(true);
        s->setPath(t);
        q.push(s);
    }
}

bool Network::findAugmentingPath(Station *source, Station *dest) {
    for(Station* station : stationsSet) {
        if (station->getName() != source->getName())
            station->setVisited(false);
        else
            station->setVisited(true);
    }

    queue<Station*> q;
    q.push(source);

    while(!q.empty() && !(dest->isVisited())) {
        Station* v = q.front();
        q.pop();
        for(Track* t : v->getAdj()) {
            testAndVisit(q, t, t->getDestination(),  t->getCapacity() - t->getFlow());
        }

        for(Track* t : v->getIncoming()) {
            testAndVisit(q, t, t->getSource(), t->getFlow());
        }
    }
    return dest->isVisited();
}

int Network::findMinResidualAlongPath(Station *source, Station *dest) {
    int f = INT16_MAX;
    int cost = 0;
    for (auto v = dest; v != source; ) {
        auto e = v->getPath();
        if (e->getDestination() == v) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getSource();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDestination();
        }
        cost += e->getService() == "STANDARD" ? 4 : 2;
    }
    return f;
}

pair<int,int> Network::edmondsKarpCost(Station *stationSource, Station *stationDest) {

    vector<pair<int,int>> all_flowCosts;

    if (stationSource == nullptr || stationDest == nullptr || stationSource == stationDest) {
        throw logic_error("Invalid source and/or target vertex");
    }

    for (Station *station: stationsSet) {
        for (Track *track: station->getAdj()) {
            track->setFlow(0);
        }
    }

    while (findAugmentingPath(stationSource, stationDest)) {
        pair<int,int> flowCost = findMinResidualCostAlongPath(stationSource, stationDest);
        all_flowCosts.push_back(flowCost);
        augmentFlowAlongPath(stationSource, stationDest, flowCost.first);
    }

    std::sort(all_flowCosts.begin(), all_flowCosts.end(),
              [](pair<int,int> p1,pair<int,int> p2){if (p1.first == p2.first) return p1.second < p2.second; return p1.first > p2.first; });
    return all_flowCosts.at(0);
}

std::pair<int,int> Network::findMinResidualCostAlongPath(Station *source, Station *dest) {
    int f = INT16_MAX;
    int cost = 0;
    for (auto v = dest; v != source; ) {
        auto e = v->getPath();
        if (e->getDestination() == v) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getSource();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDestination();
        }
        cost += e->getService() == "STANDARD" ? 4 : 2;
    }
    return {f,cost};
}



void Network::augmentFlowAlongPath(Station *source, Station *dest, double f) {
    for (auto v = dest; v != source; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDestination() == v) {
            e->setFlow(flow + f);
            v = e->getSource();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDestination();
        }
    }
}

void Network::edmondsKarp(Station *source, Station *dest) {
    if (source == nullptr || dest == nullptr || source == dest)
        throw logic_error("Invalid source and/or target vertex");

    for (Station *station: stationsSet)
        for (Track *track: station->getAdj())
            track->setFlow(0);

    while (findAugmentingPath(source, dest)) {
        double f = findMinResidualAlongPath(source, dest);
        augmentFlowAlongPath(source, dest, f);
    }
}



pair<double,vector<pair<string,string>>> Network::topMaxFlow() {
    vector<pair<string,string>> ans;
    vector<pair<string,string>> analysedCases;
    double maxFlow = 0;
    double cases = (double) (stationsSet.size()*(stationsSet.size() - 1))/2;
    double calculatedCases = 0;
    int percentage = 0;
    for (size_t i = 0; i != stationsSet.size(); i++) {
        for (size_t j = i; j != stationsSet.size(); j++) {
            Station* src = stationsSet[i];
            Station* dest = stationsSet[j];
            if (src == dest) continue;
            edmondsKarp(src, dest);
            calculatedCases++;
            if (percentage < round(((calculatedCases/cases) * 100))){
                percentage = (int) round(((calculatedCases/cases) * 100));
                Util::cleanTerminal();
                Util::printLoadingBar(percentage);
            }
            double flow = dest->getFlow();
            if (flow < maxFlow) continue;
            if (flow > maxFlow) {
                maxFlow = flow;
                ans.clear();
            }
            ans.emplace_back(src->getName(), dest->getName());
        }
    }
    return {maxFlow, ans};
}

struct{
        bool operator() (const pair<string, double>& pair1, const pair<string, double>& pair2) {
            return (pair1.second > pair2.second);
        }
}customComparator;

vector<pair<string, double>> Network::topTransportationNeeds(string location) {

    vector<pair<string, double>> res;

    auto cases = (double) ((stationsSet.size() * (stationsSet.size() - 1))/2);
    double calculatedCases = 0;
    int percentage = 0;
    auto getLocationString = [&](Station* station) {
        if (location == "district") {
            return station->getDistrict();
        } else if (location == "municipality") {
            return station->getMunicipality();
        }
        return string("");
    };
    for (Station* station : stationsSet) {
        string locStr = getLocationString(station);
        auto itr = find_if(res.begin(), res.end(), [&](const auto& p) {
            return p.first == locStr;
        });
        if ((itr == res.end() ) && !locStr.empty()) {
            res.emplace_back(locStr, 0);
        }
        if ((itr == res.end() || res.empty()) && !locStr.empty())
            res.emplace_back(locStr, 0);
    }
    for (int i = 0; i < getNumStations(); i++) {
        Station* src = stationsSet[i];
        string srcLocStr = getLocationString(src);
        for (int j = i; j < getNumStations(); j++) {
            Station* dest = stationsSet[j];
            if (src == dest) continue;

            edmondsKarp(src, dest);
            double flow = dest->getFlow();

            auto itrSource = find_if(res.begin(), res.end(), [&](const auto& p) {
                return p.first == srcLocStr;
            });
            itrSource->second += flow;

            string destLocStr = getLocationString(dest);
            auto itrDest = find_if(res.begin(), res.end(), [&](const auto& p) {
                return p.first == destLocStr;
            });
            itrDest->second += flow;
            calculatedCases++;
            if (percentage < round(((calculatedCases/cases) * 100))){
                percentage = (int) round(((calculatedCases/cases) * 100));
                Util::cleanTerminal();
                Util::printLoadingBar(percentage);
            }
        }
    }
    sort(res.begin(), res.end(), customComparator);
    return res;
}

void Network::DFS(vector<Station *> &endStations, Station *srcStation) {

    srcStation->setVisited(true);
    bool unvisitedNeighbours = false;
    for(Track* track : srcStation->getIncoming()){
        if(!track->getSource()->isVisited()){
            unvisitedNeighbours = true;
            DFS(endStations, track->getSource());
        }
    }
    if(!unvisitedNeighbours)
        endStations.push_back(srcStation);
}

double Network::maxTrainsStation(Station* dest) {

    vector<Station*> endStations;
    for (Station* station : stationsSet)
        station->setVisited(false);
    DFS(endStations, dest);

    Station* superSource = new Station("test", "test", "test", "test", "test");

    for (Station* station : endStations)
        superSource->addTrack(station, INT16_MAX, "REGULAR");
    addStation(superSource);
    edmondsKarp(superSource, dest);
    removeStation(superSource->getName());

    return dest->getFlow();
}


