#include "../headers/Util.h"

namespace Util {

    bool discard(char c) {
        return c == ' ' || c == '"';
    }

    std::string center(std::string str, int width) {
        int padding = width - str.size();
        int leftPadding = padding / 2;
        int rightPadding = padding - leftPadding;
        return std::string(leftPadding, ' ') + str + std::string(rightPadding, ' ');
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

    std::vector<std::string> split(const std::string &str, char delimiter) {
        std::vector<std::string> res;
        std::string buffer;
        std::stringstream tmp(str);
        while (getline(tmp, buffer, delimiter))
            res.push_back(buffer);
        return res;
    }

    void readStations(const std::string &path, Network *graph) {

        std::vector<int> maxmax(5, 0);

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

            maxmax[0] = maxmax[0] > name.size() ? maxmax[0] : (int) name.size();
            maxmax[1] = maxmax[1] > district.size() ? maxmax[1] : (int) district.size();
            maxmax[2] = maxmax[2] > municipality.size() ? maxmax[2] : (int) municipality.size();
            maxmax[3] = maxmax[3] > township.size() ? maxmax[3] : (int) township.size();
            maxmax[4] = maxmax[4] > line.size() ? maxmax[4] : (int) line.size();

            graph->addStation(new Station(strip(name), capitalizeFirstLetter(strip(district)),
                                          capitalizeFirstLetter(strip(municipality)), strip(township),
                                          capitalizeFirstLetter(strip(line))));
        }

        for (int i = 0; i < 5; i++)
            std::cout << maxmax[i] << " ";
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
