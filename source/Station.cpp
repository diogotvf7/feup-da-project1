//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/Station.h"

using namespace std;

Station::Station(string name, string district, string municipality, string township, string line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

string Station::getName() {
    return name;
}

string Station::getDistrict() {
    return district;
}

string Station::getMunicipality() {
    return municipality;
}

string Station::getTownship() {
    return township;
}

string Station::getLine() {
    return line;
}

void Station::setName(const string &name) {
    this->name = name;
}

void Station::setDistrict(const string &district) {
    this->district = district;
}

void Station::setMunicipality(const string &municipality) {
    this->municipality = municipality;
}

void Station::setTownship(const string &township) {
    this->township = township;
}

void Station::setLine(const string &line) {
    this->line = line;
}

void Station::addSegment(Station *dest, int capacity, const string &service) {
    segments.push_back(new Segment(this, dest, capacity, service));
}
