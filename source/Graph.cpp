//
// Created by diogotvf7 on 14-03-2023.
//

#include "headers/Graph.h"

Graph::Graph() {
}

void Graph::addStation(Station *station) {
    stations.push_back(station);
}

void Graph::addSegment(const std::string &src, const std::string &dest, int capacity, const std::string &service) {
    Station *srcStation = findStation(src);
    Station *destStation = findStation(dest);
    srcStation->addSegment(destStation, capacity, service);
}

void Graph::addBidirectionalSegment(const std::string &src, const std::string &dest, int capacity, const std::string &service) {
    addSegment(src, dest, capacity, service);
    addSegment(dest, src, capacity, service);
}

Station *Graph::findStation(const std::string &name) const {
    return *std::find_if(stations.begin(), stations.end(), [&name](Station *station) {
        return station->getName() == name;
    });
}

std::vector<Station *> Graph::getStationsVector() const {
    return stations;
}


