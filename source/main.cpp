#include <string>
#include <iomanip>
#include "iostream"

#include "headers/Network.h"
#include "headers/FileReader.h"

using namespace std;

int main() {
    Network *g = new Network();
    string path = "dataset/";
    FileReader fr = FileReader(path, g);

    fr.readStations();
    fr.readNetworks();

    cout << "Hello World!" << endl;

    /*
    for (StationTrack *station : g->getStationsVector()) {
        cout << left << "|--|" << setw(30) << station->getName() << "|--|" << setw(30) << station->getDistrict() << "|--|"
                << setw(30) << station->getMunicipality() << "|--|" << setw(40) << station->getTownship() << "|--|"
                << setw(20) << station->getLine() << "|--|" << endl;
        cout << "----------------------------------------------------------------------------------------------------"
                "-----------------------------------------------------------------------------------" << endl;
    }

    for (StationTrack *station : g->getStationsVector()) {
        break;
    }
     */
     
    g->edmondsKarp("Porto Campanhã", "Pinhal Novo");
    
    return 0;
}