//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/FileReader.h"

using namespace std;


FileReader::FileReader(const string &path, Graph *graph) {
    this->path = path;
    this->graph = graph;
}

bool FileReader::discard(char c) {
    return c == ' ' || c == '"';
}

string FileReader::strip(const string &str) const {
    if (str.empty()) return "";
    string buffer;
    auto lowerBound = str.begin(), upperBound = str.end();
    while (discard(*lowerBound)) lowerBound++;
    while (discard(*upperBound)) upperBound--;
    return {lowerBound, upperBound};
}

void FileReader::readStations() {

    ifstream csv("../dataset/stations.csv");
    string buffer;
    getline(csv, buffer, '\n'); // Ignore Header

    while (getline(csv, buffer, '\n')) {
        string name, district, municipality, township, line;
        stringstream tmp(buffer);

        getline(tmp, name, ',');
        getline(tmp, district, ',');
        getline(tmp, municipality, ',');

        if (tmp.peek()  == '"') {
            getline(tmp, township, '"');
            getline(tmp, township, '"');
        }
        else {
            getline(tmp, township, ',');
        }
        getline(tmp, line, ',');
        getline(tmp, line, '\n');

        graph->addStation(new Station(strip(name), capitalizeFirstLetter(strip(district)), capitalizeFirstLetter(strip(municipality)), strip(township),
                                      capitalizeFirstLetter(strip(line))));
    }
}

void FileReader::readNetworks() {

    ifstream csv("../dataset/network.csv");
    string buffer;
    getline(csv, buffer, '\n'); // Ignore Header

    while(getline(csv, buffer)) {

        string src, dest, capacity, service;
        stringstream tmp(buffer);
        getline(tmp, src, ',');
        getline(tmp, dest, ',');
        getline(tmp, capacity, ',');
        getline(tmp, service, '\n');

        graph->addBidirectionalSegment(strip(src), strip(dest), stoi(capacity), capitalizeFirstLetter(strip(service)));
    }
}

std::string FileReader::capitalizeFirstLetter(const std::string& str)
{
    std::string result = str;
    if (!result.empty()) {
        result[0] = std::toupper(result[0]);
        for (std::size_t i = 1; i < result.size(); ++i) {
            result[i] = std::tolower(result[i]);
        }
    }
    return result;
}


