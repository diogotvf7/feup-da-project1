#ifndef NETWORK_H
#define NETWORK_H

#include <algorithm>
#include <vector>

#include "StationTrack.h"

class Network {
    std::vector<Station*> stationsSet;
public:
    Station* findStation(std::string stationName) const;
    bool addStation(Station* station);
    //bool addTrack(const int &sourc, const int &dest, double w);
    bool addBidirectionalTrack(const std::string &source,const std::string &dest, double capacity, const std::string &service);
    int getNumStations() const;
    std::vector<Track*> getTracksSet() const;
    std::vector<Station*> getStationsSet() const;

};


#endif //NETWORK_H
