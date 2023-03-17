#include <string>
#include <iomanip>
#include <map>
#include <set>
#include "iostream"

#include "headers/Network.h"
#include "headers/FileReader.h"

using namespace std;

int main() {

    /*Network *g = new Network();
    string path = "../dataset/test-dataset/";
    FileReader fr = FileReader(path, g);

    fr.readStations();
    fr.readNetworks();

    cout << "Hello World!" << endl;

    for (Station *station : g->getStationsSet()) {
        cout << left << "|--|" << setw(30) << station->getName() << "|--|" << setw(30) << station->getDistrict() << "|--|"
                << setw(30) << station->getMunicipality() << "|--|" << setw(40) << station->getTownship() << "|--|"
                << setw(20) << station->getLine() << "|--|" << endl;
        cout << "----------------------------------------------------------------------------------------------------"
                "-----------------------------------------------------------------------------------" << endl;
    }

    for (Station *station : g->getStationsSet()) {
        break;
    }
    std::string string1 = "Porto Campanhã", string2 = "Pinhal Novo";
    g->edmondsKarp(string1, string2);*/


    Network *g2 = new Network();
    string path2 = "../dataset/real-dataset/";
    FileReader fr2 = FileReader(path2, g2);
    fr2.readStations();
    fr2.readNetworks();
    //std::pair<double,std::vector<std::pair<Station*,Station*>>> tmf = g2->topMaxFlow();
    //for (auto &i : tmf.second) {
    //    std::cout << i.first->getName() << " | " << i.second->getName() << " | " << tmf.first << std::endl;
    //}
    vector<pair<string, double>> test = g2->topTransportationNeeds("district");

    return 0;
}