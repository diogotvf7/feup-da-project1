//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/Segment.h"

Segment::Segment(Station *src, Station *dest, int capacity, const std::string &service) {
    this->src = src;
    this->dest = dest;
    this->capacity = capacity;
    this->service = service;
}

Station *Segment::getSource() const {
    return src;
}

void Segment::setSource(Station *source) {
    this->src = source;
}

Station *Segment::getDestination() const {
    return dest;
}

void Segment::setDestination(Station *destination) {
    this->dest = destination;
}

int Segment::getCapacity() const {
    return capacity;
}

void Segment::setCapacity(int c) {
    this->capacity = c;
}

void Segment::setReverse(Segment *reverse) {
    this->reverse = reverse;
}

std::string Segment::getService() const {
    return service;
}

void Segment::setService(const std::string &service) {
    this->service = service;
}

