#include <map>
#include "headers/Network.h"
using namespace std;

Station* Network::findStation(string stationName) const {
    for(Station* station : stationsSet){
        if(station->getName() == stationName){
            return station;
        }
    }
    return nullptr;
}

bool Network::addStation(Station* station) {
    if(findStation(station->getName()) == nullptr){
        stationsSet.push_back(station);
        return true;
    }
    return false;
}

bool Network::addTrack(const string &sourc, const string &dest, double capacity, const string &service) {
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addTrack(v2, capacity, service);
    return true;
}

bool Network::addBidirectionalTrack(const string &source,const string &dest, double capacity, const string &service) {

    Station* s1 = findStation(source);
    Station* s2 = findStation(dest);
    if(s1 == nullptr || s2 == nullptr){
        return false;
    }
    Track* t1 = s1->addTrack(s2, capacity, service);
    Track* t2 = s2->addTrack(s1, capacity, service);
    t1->setReverse(t2);
    t2->setReverse(t1);
    return true;
}

int Network::getNumStations()  const {
    return (int) stationsSet.size();
}

vector<Station*> Network::getStationsSet() const {
    return stationsSet;
}

vector<Track*> Network::getTracksSet() const {
    vector<Track*> tracksSet;
    for(Station* station : stationsSet){
        for(Track* track : station->getAdj()){
            tracksSet.push_back(track);
        }
    }
    return tracksSet;
}

void Network::testAndVisit(queue<Station *> &q, Track *t, Station *s, double residual) {
    if(!s->isVisited() && residual > 0){
        s->setVisited(true);
        s->setPath(t);
        q.push(s);
    }
}

bool Network::findAugmentingPath(Station *source, Station *dest) {
    for(Station* station : stationsSet){
        if(station->getName() != source->getName())
            station->setVisited(false);
        else
            station->setVisited(true);
    }

    queue<Station*> q;
    q.push(source);

    while(!q.empty() && !(dest->isVisited())){
        Station* v = q.front();
        q.pop();
        for(Track* t : v->getAdj()){
            testAndVisit(q, t, t->getDestination(),  t->getCapacity() - t->getFlow());
        }

        for(Track* t : v->getIncoming()){
            testAndVisit(q, t, t->getSource(), t->getFlow());
        }
    }
    return dest->isVisited();
}

double Network::findMinResidualAlongPath(Station *source, Station *dest) {
    double f = INT16_MAX;
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
    }
    return f;
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

void Network::edmondsKarp(const string &source, const string &dest) {

    Station *stationSource = findStation(source);
    Station *stationDest = findStation(dest);

    if (stationSource == nullptr || stationDest == nullptr || stationSource == stationDest) {
        throw logic_error("Invalid source and/or target vertex");
    }

    for (Station *station: stationsSet) {
        for (Track *track: station->getAdj()) {
            track->setFlow(0);
        }
    }

    while (findAugmentingPath(stationSource, stationDest)) {
        double f = findMinResidualAlongPath(stationSource, stationDest);
        augmentFlowAlongPath(stationSource, stationDest, f);
    }
}

void Network::edmondsKarp2(const string &source, const string &dest) {

    Station *stationSource = findStation(source);
    Station *stationDest = findStation(dest);

    double cost = 0;

    if (stationSource == nullptr || stationDest == nullptr || stationSource == stationDest) {
        throw logic_error("Invalid source and/or target vertex");
    }

    for (Station *station: stationsSet) {
        for (Track *track: station->getAdj()) {
            track->setFlow(0);
        }
    }

    while (findAugmentingPath(stationSource, stationDest)) {
        double f = findMinResidualAlongPath(stationSource, stationDest);
        augmentFlowAlongPath(stationSource, stationDest, f);

    }

 }


pair<double,vector<pair<Station*,Station*>>> Network::topMaxFlow() {
    vector<pair<Station*,Station*>> ans;
    double maxFlow = 0;

    for (Station *src : stationsSet) {
        for (Station *dest : stationsSet) {
            if (src == dest) continue;
            edmondsKarp(src->getName(), dest->getName());
            double flow = dest->getFlow();
            if (flow < maxFlow) continue;
            if (flow > maxFlow) {
                maxFlow = flow;
                ans.clear();
            }
            ans.emplace_back(src, dest);
        }
    }
    return {maxFlow, ans};
}

struct{
        bool operator() (const pair<string, double>& pair1, const pair<string, double>& pair2){
            return (pair1.second > pair2.second);
        }
}customComparator;

vector<pair<string, double>> Network::topTransportationNeeds(string location){

    vector<pair<string, double>> res;

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
        auto itr = std::find_if(res.begin(), res.end(), [&](const auto& p) {
            return p.first == locStr;
        });

        if ((itr == res.end() ) && !locStr.empty()) {
            res.push_back(make_pair(locStr, 0));
        }
    }

    for (Station* src : stationsSet) {
        string srcLocStr = getLocationString(src);
        for (Station* dest : stationsSet) {
            if (src == dest) continue;
            edmondsKarp(src->getName(), dest->getName());
            double flow = dest->getFlow();

            auto itrSource = std::find_if(res.begin(), res.end(), [&](const auto& p) {
                return p.first == srcLocStr;
            });
            itrSource->second += flow;

            string destLocStr = getLocationString(dest);
            auto itrDest = std::find_if(res.begin(), res.end(), [&](const auto& p) {
                return p.first == destLocStr;
            });
            itrDest->second += flow;
        }
    }

    sort(res.begin(), res.end(), customComparator);
    return res;
}

double Network::maxTrainsStation(Station* dest) {

    Station* superSource = new Station("test", "test", "test", "test", "test");

    for(Station* station : stationsSet){
        if(station != dest){
            superSource->addTrack(station, INT16_MAX, "STANDARD");
        }
    }
    addStation(superSource);

    edmondsKarp(superSource->getName(), dest->getName());
    return dest->getFlow();

}


