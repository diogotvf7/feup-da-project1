#include <string>
#include <iomanip>
#include "iostream"

#include "headers/Graph.h"
#include "headers/FileReader.h"

using namespace std;

int main() {
    Graph *g = new Graph();
    string path = "dataset/";
    FileReader fr = FileReader(path, g);

    fr.readStations();
    fr.readNetworks();

    cout << "Hello World!" << endl;

    for (Station *station : g->getStationsVector()) {
        cout << left << "|--|" << setw(30) << station->getName() << "|--|" << setw(30) << station->getDistrict() << "|--|"
                << setw(30) << station->getMunicipality() << "|--|" << setw(40) << station->getTownship() << "|--|"
                << setw(20) << station->getLine() << "|--|" << endl;
        cout << "----------------------------------------------------------------------------------------------------"
                "-----------------------------------------------------------------------------------" << endl;
    }

    for (Station *station : g->getStationsVector()) {
        break;
    }

    return 0;
}