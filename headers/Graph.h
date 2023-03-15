//
// Created by diogotvf7 on 14-03-2023.
//

#ifndef FEUP_DA_PROJECT_GRAPH_H
#define FEUP_DA_PROJECT_GRAPH_H

#include <algorithm>
#include <vector>

#include "Segment.h"
#include "Station.h"

class Graph {
    std::vector<Station*> stations;

public:
    Graph();
    [[nodiscard]] Station *findStation(const std::string &name) const;
    void addStation(Station *station);
    void addSegment(const std::string &src, const std::string &dest, int capacity, const std::string &service);
    void addBidirectionalSegment(const std::string &src, const std::string &dest, int capacity, const std::string &service);
    [[nodiscard]] std::vector<Station*> getStationsVector() const;
};


#endif //FEUP_DA_PROJECT_GRAPH_H
