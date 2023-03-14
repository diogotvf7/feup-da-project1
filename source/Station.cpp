//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/Station.h"

Station::Station(std::string name, std::string district, std::string municipality, std::string township, std::string line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

std::string Station::getName() {return name;}

std::string Station::getDistrict() {return district;}

std::string Station::getMunicipality() {return municipality;}

std::string Station::getTownship() {return township;}

std::string Station::getLine() {return line;}

void Station::setName(std::string n) {this->name = n;}

void Station::setDistrict(std::string d) {this->district = d;}

void Station::setMunicipality(std::string m) {this->municipality = m;}

void Station::setTownship(std::string t) {this->township = t;}

void Station::setLine(std::string l) {this->line = l;}