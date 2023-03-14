//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/Segment.h"

Segment::Segment(std::string src, std::string dest, int capacity, std::string service) {
    this->src = src;
    this->dest = dest;
    this->capacity = capacity;
    this->service = service;
}

std::string Segment::getSource() const {
    return src;
}

void Segment::setSource(const std::string &source) {
    this->src = source;
}

std::string Segment::getDestination() const {
    return dest;
}

void Segment::setDestination(const std::string &destination) {
    this->dest = destination;
}

int Segment::getCapacity() const {
    return capacity;
}

void Segment::setCapacity(int c) {
    this->capacity = c;
}

std::string Segment::getService() const {
    return service;
}

void Segment::setService(const std::string &s) {
    this->service = s;
}
