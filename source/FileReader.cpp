//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/FileReader.h"

using namespace std;


FileReader::FileReader(const string &path, Graph *graph) {
    this->path = path;
    this->graph = graph;
}

bool FileReader::isAlphabetical(char c) {
    return (65 <= c && c <= 90) || (97 <= c && c <= 122) || ((int) c == 156) || ((int) c == 157) || ((int) c == 158) ||
            (192 <= (int) c && (int) c <= 214) || (216 <= (int) c && (int) c <= 246) ||
           (248 <= (int) c && (int) c <= 255);
}

string FileReader::strip(const string &str) const {
    if (str.empty()) return "";
    string buffer;
    auto lowerBound = str.begin(), upperBound = str.end();
    while (!isAlphabetical(*lowerBound)) lowerBound++;
    while (!isAlphabetical(*upperBound)) upperBound--;
    return {lowerBound, ++upperBound};
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

        graph->addStation(new Station(strip(name), strip(district), strip(municipality), strip(township), strip(line)));
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

        graph->addBidirectionalSegment(strip(src), strip(dest), stoi(capacity), strip(service));
    }
}

