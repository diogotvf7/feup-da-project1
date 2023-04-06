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
    Network *test_network_2 = nm.createGraph("../dataset/test-dataset-2/");
    Network *test_simple_network = nm.createGraph("../dataset/test-simple-dataset/");
    /*#############################################*/


    /*##############################################*/
    /*            Test Edmonds Karp Cost           */

    pair<int,int> p = real_network->edmondsKarpCost("Porto Campanhã","Lisboa Oriente");
    cout << "Flow is " << p.first << " cost is " << p.second << endl;
    cout << endl;

    /*##############################################*/


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
    Network *test_network_reduced01 = nm.createGraph("../dataset/test-dataset/");
    reduceStations = {"Ermidas-Sado"};
    reduceTracks = {};
    nm.reduceConnectivity(test_network_reduced01, reduceTracks, reduceStations);
    cout << "Max Flow in normal circumstances: " << nm.maxFlowBetween(test_network, "Lisboa Oriente", "Porto Campanhã") << endl;
    cout << "Max Flow in reduced connectivity circumstances: " << nm.maxFlowBetween(test_network_reduced01, "Lisboa Oriente", "Porto Campanhã") << endl;
    nm.deleteGraph(test_network_reduced01);
    cout << endl;

    // Test 2
    Network *test_network_reduced02 = nm.createGraph("../dataset/test-dataset/");
    Network *test_network_reduced03 = nm.createGraph("../dataset/test-dataset/");
    reduceStations = {"Faro", "Porto Campanhã"};
    reduceTracks = {};
    nm.reduceConnectivity(test_network_reduced02, reduceTracks, reduceStations);
    reduceStations = {};
    reduceTracks = {{"Ermidas-Sado", "Faro"}, {"Ermidas-Sado", "Porto Campanhã"}};
    nm.reduceConnectivity(test_network_reduced03, reduceTracks, reduceStations);
    cout << "Max Flow in normal circumstances: " << nm.maxFlowBetween(test_network, "Lisboa Oriente", "Porto Campanhã") << endl;
    cout << "Max Flow in reduced connectivity (cutting stations): " << nm.maxFlowBetween(test_network_reduced02, "Lisboa Oriente", "Ermidas-Sado") << endl;
    cout << "Max Flow in reduced connectivity (cutting tracks): " << nm.maxFlowBetween(test_network_reduced03, "Lisboa Oriente", "Ermidas-Sado") << endl;
    nm.deleteGraph(test_network_reduced02);
    nm.deleteGraph(test_network_reduced03);
    cout << endl;

    /*#############################################*/


    /*############################################*/
    /*           Test maxTrainsStation           */

    Station *puortoooo = test_network->findStation("Porto Campanhã");
    cout << "Max trains arriving at Porto Campanhã: " << test_network->maxTrainsStation(puortoooo) << endl;
    Station *faroooooo = test_network->findStation("Faro");
    cout << "Max trains arriving at Faro: " << test_network->maxTrainsStation(faroooooo) << endl;
    Station *fds = test_network->findStation("Ermidas-Sado");
    cout << "Max trains arriving at Ermidas-Sado: " << test_network->maxTrainsStation(fds) << endl;
    cout << endl;

    /*#############################################*/

    /*############################################*/
    /*           Test topAffectedStations        */
    vector<Station*> topAffectedStations;

    Network *test_network_2_reduced01 = nm.createGraph("../dataset/test-dataset-2/");
    reduceStations = {"ST10"};
    reduceTracks = {};
    nm.reduceConnectivity(test_network_2, reduceTracks, reduceStations);
    topAffectedStations = nm.topAffectedStations(test_network_2, test_network_2_reduced01, 3);
    for (int i = 0; i < topAffectedStations.size(); i++)
        cout << "Top " << i+1 << " affected station: " << topAffectedStations[i]->getName() << endl;

    cout << endl;

    Network *test_simple_network_reduced = nm.createGraph("../dataset/test-simple-dataset/");
    reduceStations = {"ST02"};
    reduceTracks = {};
    nm.reduceConnectivity(test_simple_network_reduced, reduceTracks, reduceStations);
    topAffectedStations = nm.topAffectedStations(test_simple_network, test_simple_network_reduced, 3);
    for (int i = 0; i < topAffectedStations.size(); i++)
        cout << "Top " << i+1 << " affected station: " << topAffectedStations[i]->getName() << endl;

    cout << endl;

    Network *real_network_reduced = nm.createGraph("../dataset/real-dataset/");
    reduceStations = {"Porto Campanhã", "Lisboa Oriente", "Aveiro - Vouga", "Coimbra B", "Coimbra", "Faro", "Ermidas-Sado"};
    reduceTracks = {{"São Romão - A","São Romão"}, {"Pala","Mosteirô"}, {"Loulé","Almancil"}};
    nm.reduceConnectivity(real_network_reduced, reduceTracks, reduceStations);
    topAffectedStations = nm.topAffectedStations(real_network, real_network_reduced, 10);
    for (int i = 0; i < topAffectedStations.size(); i++)
        cout << "Top " << i+1 << " affected station: " << topAffectedStations[i]->getName() << endl;

    /*#############################################*/

    return 0;
}