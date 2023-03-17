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

bool Network::addBidirectionalTrack(const string &source,const string &dest, double capacity, const std::string &service) {

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
    return stationsSet.size();
}

vector<Station*> Network::getStationsSet() const {return stationsSet;}

vector<Track*> Network::getTracksSet() const {
    vector<Track*> tracksSet;
    for(Station* station : stationsSet){
        for(Track* track : station->getAdj()){
            tracksSet.push_back(track);
        }
    }
    return tracksSet;
}