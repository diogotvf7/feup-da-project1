#include "../headers/FileReader.h"

namespace FileReader {

    bool discard(char c) {
        return c == ' ' || c == '"';
    }

    std::string capitalizeFirstLetter(const std::string &str) {
        std::string res = str;
        for (size_t i = 0; i < res.size(); i++)
            res[i] = i ? std::tolower(res[i]) : std::toupper(res[i]);
        return res;
    }

    std::string strip(const std::string &str) {
        if (str.empty()) return "";
        std::string buffer;
        auto lowerBound = str.begin(), upperBound = str.end();
        while (discard(*lowerBound)) lowerBound++;
        while (discard(*upperBound)) upperBound--;
        return {lowerBound, upperBound};
    }

    void readStations(const std::string &path, Network *graph) {

        std::ifstream csv(path + "stations.csv");
        std::string buffer;
        getline(csv, buffer, '\n'); // Ignore Header

        while (getline(csv, buffer, '\n')) {
            std::string name, district, municipality, township, line;
            std::stringstream tmp(buffer);

            getline(tmp, name, ',');
            getline(tmp, district, ',');
            getline(tmp, municipality, ',');

            if (tmp.peek() == '"') {
                getline(tmp, township, '"');
                getline(tmp, township, '"');
            } else {
                getline(tmp, township, ',');
            }
            getline(tmp, line, ',');
            getline(tmp, line, '\n');

            graph->addStation(new Station(strip(name), capitalizeFirstLetter(strip(district)),
                                          capitalizeFirstLetter(strip(municipality)), strip(township),
                                          capitalizeFirstLetter(strip(line))));
        }
    }

    void readNetwork(const std::string &path, Network *graph) {

        std::ifstream csv(path + "network.csv");
        std::string buffer;
        getline(csv, buffer, '\n'); // Ignore Header

        while (getline(csv, buffer)) {

            std::string src, dest, capacity, service;
            std::stringstream tmp(buffer);
            getline(tmp, src, ',');
            getline(tmp, dest, ',');
            getline(tmp, capacity, ',');
            getline(tmp, service, '\n');

            graph->addBidirectionalTrack(strip(src), strip(dest), stoi(capacity),
                                         capitalizeFirstLetter(strip(service)));
        }
    }
}

