//
// Created by Daniel Rebelo on 08/03/2023.
//

#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H

#include <iostream>
#include <string>

class Station {
private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
public:
    Station(std::string name, std::string district, std::string municipality, std::string township, std::string line);
    std::string getName();
    std::string getDistrict();
    std::string getMunicipality();
    std::string getTownship();
    std::string getLine();
    void setName(std::string n);
    void setDistrict(std::string d);
    void setMunicipality(std::string m);
    void setTownship(std::string t);
    void setLine(std::string l);
};


#endif //PROJECT_STATION_H
