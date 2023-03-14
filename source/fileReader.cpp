//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/fileReader.h"
using namespace std;

std::vector<Station *> fileReader::readStations(std::istream &stationsFile) {
    stationsFile.ignore(numeric_limits<streamsize>::max(), '\n');
    std::vector<Station*> stations;
    while(stationsFile.good()){
        string sentence, data;
        vector<string> lineVector;
        getline(stationsFile, sentence);

        if(sentence.empty() || sentence == "\r") break;
        stringstream ss(sentence);

        while(getline(ss, data, ',')){
            if(data[0] == '\"'){
                if(data[data.size() - 1] == '\"' || data[data.size() - 1] == '\r'){
                    data = data.erase(0,1);
                    data = data.erase(data.size() - 1);
                }
                else{
                    string temp;
                    getline(ss, temp, '\"');
                    data = data.erase(0,1);
                    data += temp;
                    if (ss.peek() == ',') ss.ignore();
                }
            }
            lineVector.push_back(data);
        }

        string name = lineVector[0],
                district = lineVector[1],
                municipality = lineVector[2],
                township = lineVector[3],
                line = lineVector[4];
        line.erase(line.size() - 1);
        Station* station = new Station(name, district, municipality, township, line);
        stations.push_back(station);
    }

    return stations;
}

void readNetworks(std::string inputFile){

    vector<Segment *> segments;

    std::ifstream networkFile;

    try{
        networkFile.open(inputFile);
    }
    catch (exception e) {
        cout << "Couldn't open network file" << endl;
    }

    networkFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(networkFile.good()) {

        string line, data, src, dest, capacity, service;

        int n;

        getline(networkFile, line);

        if (line.empty() || line == "\r") break;

        stringstream ss(line);

        getline(ss, data, ',');

        src = data;

        getline(ss, data, ',');

        dest = data;

        getline(ss, data, ',');

        capacity = data;

        n = stoi(capacity);

        getline(ss, data, ',');

        service = data;

        Segment *seg = new Segment(src,dest,n,service);

        segments.push_back(seg);
    }

}