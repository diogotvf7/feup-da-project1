//
// Created by diogotvf7 on 14-03-2023.
//

#ifndef FEUP_DA_PROJECT_GRAPH_H
#define FEUP_DA_PROJECT_GRAPH_H

#include <vector>

#include "Segment.h"
#include "Station.h"

class Graph {
    std::vector<Station*> stations;
    std::vector<Segment*> segments;

public:
    Graph();
    void addStation(Station *st);
    void addSegment(Segment *s);
};


#endif //FEUP_DA_PROJECT_GRAPH_H
