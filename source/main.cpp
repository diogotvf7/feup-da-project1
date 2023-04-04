#include <iostream>
#include <string>
#include <vector>

#include "../headers/Network.h"
#include "../headers/NetworkManager.h"


using namespace std;

int main () {

     /*#############################################*/
    /*          Structures initialization          */

    NetworkManager nm;
    Network *real_network = nm.createGraph("../dataset/real-dataset/");
    Network *test_network = nm.createGraph("../dataset/test-dataset/");

    /*#############################################*/


    /*##############################################*/
    /*              Real Top Max Flow              */

//    std::pair<double,std::vector<std::pair<Station*,Station*>>> tmf = real_network->topMaxFlow();
//    for (auto &i : tmf.second)
//        std::cout << i.first->getName() << " | " << i.second->getName() << " | " << tmf.first << std::endl;

    /*#############################################*/


    /*############################################*/
    /*         Test reduced connectivity         */
    vector<string> reduceStations;
    tracks_vector reduceTracks;

    // Test 1
    Network *test_reduced_network1 = nm.createGraph("../dataset/test-dataset/");
    reduceStations = {"Ermidas-Sado"};
    reduceTracks = {};
    nm.reduceConnectivity(test_reduced_network1, reduceTracks, reduceStations);
    cout << "Max Flow in normal circumstances: " << nm.maxFlowBetween(test_network, "Lisboa Oriente", "Porto Campanhã") << endl;
    cout << "Max Flow in reduced connectivity circumstances: " << nm.maxFlowBetween(test_reduced_network1, "Lisboa Oriente", "Porto Campanhã") << endl;
    nm.deleteGraph(test_reduced_network1);
    cout << endl;

    // Test 2
    Network *test_reduced_network2 = nm.createGraph("../dataset/test-dataset/");
    Network *test_reduced_network3 = nm.createGraph("../dataset/test-dataset/");
    reduceStations = {"Faro", "Porto Campanhã"};
    reduceTracks = {};
    nm.reduceConnectivity(test_reduced_network2, reduceTracks, reduceStations);
    reduceStations = {};
    reduceTracks = {{"Ermidas-Sado", "Faro"}, {"Ermidas-Sado", "Porto Campanhã"}};
    nm.reduceConnectivity(test_reduced_network3, reduceTracks, reduceStations);
    cout << "Max Flow in normal circumstances: " << nm.maxFlowBetween(test_network, "Lisboa Oriente", "Porto Campanhã") << endl;
    cout << "Max Flow in reduced connectivity (cutting stations): " << nm.maxFlowBetween(test_reduced_network2, "Lisboa Oriente", "Ermidas-Sado") << endl;
    cout << "Max Flow in reduced connectivity (cutting tracks): " << nm.maxFlowBetween(test_reduced_network3, "Lisboa Oriente", "Ermidas-Sado") << endl;
    cout << endl;





//    Station* test = g2->getStationsSet()[56];
//    double res = g2->maxTrainsStation(test);
    return 0;
}