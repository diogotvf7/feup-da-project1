//
// Created by Daniel Rebelo on 08/03/2023.
//

#ifndef PROJECT_SEGMENT_H
#define PROJECT_SEGMENT_H

#include <iostream>
#include <string>

class Station;

#include "Station.h"

class Segment {
    Station *src;
    Station *dest;
    int capacity;
    std::string service;
public:
    Segment(Station *src, Station *dest, int capacity, const std::string &service);
    [[nodiscard]] Station *getSource() const;
    [[nodiscard]] Station *getDestination() const;
    [[nodiscard]] int getCapacity() const;

    [[nodiscard]] std::string getService() const;
    void setSource(Station *source);
    void setDestination(Station *destination);
    void setCapacity(int capacity);

    void setService(const std::string &service);
};


#endif //PROJECT_SEGMENT_H
