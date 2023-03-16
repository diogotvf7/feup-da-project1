//
// Created by Daniel Rebelo on 08/03/2023.
//

#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H

#include <iostream>
#include <vector>
#include <string>

class Segment;

#include "Segment.h"

class Station {
private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    std::vector<Segment*> segments;

public:
    Station(std::string name, std::string district, std::string municipality, std::string township, std::string line);
    std::string getName();
    std::string getDistrict();
    std::string getMunicipality();
    std::string getTownship();
    std::string getLine();
    void setName(const std::string &name);
    void setDistrict(const std::string &district);
    void setMunicipality(const std::string &municipality);
    void setTownship(const std::string &township);
    void setLine(const std::string &line);
    void addSegment(Station *dest, int capacity, const std::string &service);
};


#endif //PROJECT_STATION_H
