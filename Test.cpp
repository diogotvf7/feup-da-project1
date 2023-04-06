#include <iostream>

#include "headers/Network.h"
#include "headers/NetworkManager.h"

using namespace std;

void edmondsKarpCostTest() {
    Network *real_network = NetworkManager::createGraph("../dataset/real-dataset/");

    cout << "Edmonds Karp Cost Test" << endl;
    pair<int,int> p = real_network->edmondsKarpCost("Porto Campanhã","Lisboa Oriente");
    cout << "[Porto Campanhã -> Lisboa Oriente]" << endl;
    cout << "Flow: " << p.first << endl;
    cout << "Cost: " << p.second << endl;
    cout << endl;

    NetworkManager::deleteGraph(real_network);
}

void realTopMaxFlow() {
    Network *real_network = NetworkManager::createGraph("../dataset/real-dataset/");

    cout << "Real Top Max Flow" << endl;
    pair<double,vector<pair<string,string>>> tmf = real_network->topMaxFlow();
    for (auto &i : tmf.second)
        cout << i.first << " | " << i.second << " | " << tmf.first << endl;
    cout << endl;

    NetworkManager::deleteGraph(real_network);
}

void testReducedConnectivity01() {
    Network *test_network = NetworkManager::createGraph("../dataset/test-dataset/");
    Network *test_network_reduced = NetworkManager::createGraph("../dataset/test-dataset/");
    vector<string> reduceStations = {"Ermidas-Sado"};
    tracks_vector reduceTracks = {};
    NetworkManager::reduceConnectivity(test_network_reduced, reduceTracks, reduceStations);

    cout << "Test reduced connectivity 01" << endl;
    cout << "[Lisboa Oriente -> Porto Campanhã]" << endl;
    cout << "Max Flow under normal circumstances: "
         << NetworkManager::maxFlowBetween(test_network, test_network->findStation("Lisboa Oriente"), test_network->findStation("Porto Campanhã")) << endl;
    cout << "Max Flow in reduced connectivity circumstances: "
         << NetworkManager::maxFlowBetween(test_network_reduced, test_network_reduced->findStation("Lisboa Oriente"), test_network_reduced->findStation("Porto Campanhã")) << endl;
    cout << endl;

    NetworkManager::deleteGraph(test_network_reduced);
}

void testReducedConnectivity02() {
    Network *test_network = NetworkManager::createGraph("../dataset/test-dataset/");
    Network *test_network_reduced = NetworkManager::createGraph("../dataset/test-dataset/");
    vector<string> reduceStations = {"Faro", "Porto Campanhã"};
    tracks_vector reduceTracks = {};
    NetworkManager::reduceConnectivity(test_network_reduced, reduceTracks, reduceStations);

    cout << "Test reduced connectivity 02 (Cutting stations)" << endl;
    cout << "[Lisboa Oriente -> Porto Campanhã]" << endl;
    NetworkManager::reduceConnectivity(test_network_reduced, reduceTracks, reduceStations);
    cout << "Max Flow in normal circumstances: " << NetworkManager::maxFlowBetween(test_network, test_network->findStation("Lisboa Oriente"), test_network->findStation("Porto Campanhã")) << endl;
    cout << "Max Flow in reduced connectivity: " << NetworkManager::maxFlowBetween(test_network_reduced, test_network_reduced->findStation("Lisboa Oriente"), test_network_reduced->findStation("Ermidas-Sado")) << endl;
    cout << endl;

    NetworkManager::deleteGraph(test_network);
    NetworkManager::deleteGraph(test_network_reduced);
}

void testReducedConnectivity03() {
    Network *test_network = NetworkManager::createGraph("../dataset/test-dataset/");
    Network *test_network_reduced = NetworkManager::createGraph("../dataset/test-dataset/");
    vector<string> reduceStations = {};
    tracks_vector reduceTracks = {{"Ermidas-Sado", "Faro"}, {"Ermidas-Sado", "Porto Campanhã"}};
    NetworkManager::reduceConnectivity(test_network_reduced, reduceTracks, reduceStations);


    cout << "Test reduced connectivity 03 (Cutting tracks)" << endl;

    NetworkManager::reduceConnectivity(test_network_reduced, reduceTracks, reduceStations);
    cout << "Max Flow in normal circumstances: " << NetworkManager::maxFlowBetween(test_network, test_network->findStation("Lisboa Oriente"), test_network->findStation("Porto Campanhã")) << endl;
    cout << "Max Flow in reduced connectivity (cutting tracks): " << NetworkManager::maxFlowBetween(test_network_reduced, test_network_reduced->findStation("Lisboa Oriente"), test_network_reduced->findStation("Ermidas-Sado")) << endl;
    cout << endl;

    NetworkManager::deleteGraph(test_network);
    NetworkManager::deleteGraph(test_network_reduced);
}

void testMaxTrainStations01() {
    Network *test_network = NetworkManager::createGraph("../dataset/test-dataset/");

    cout << "Test max trains arriving at station 01" << endl;
    Station *porto = test_network->findStation("Porto Campanhã");
    cout << "Max trains arriving at Porto Campanhã: " << test_network->maxTrainsStation(porto) << endl;
    Station *faro = test_network->findStation("Faro");
    cout << "Max trains arriving at Faro: " << test_network->maxTrainsStation(faro) << endl;
    Station *ermidas_sado = test_network->findStation("Ermidas-Sado");
    cout << "Max trains arriving at Ermidas-Sado: " << test_network->maxTrainsStation(ermidas_sado) << endl;
    cout << endl;

    NetworkManager::deleteGraph(test_network);
}

void testMaxTrainStations02() {
    Network *real_network = NetworkManager::createGraph("../dataset/real-dataset/");

    cout << "Test max trains arriving at station 02" << endl;
    Station *porto = real_network->findStation("Porto Campanhã");
    cout << "Max trains arriving at Porto Campanhã: " << real_network->maxTrainsStation(porto) << endl;
    Station *faro = real_network->findStation("Faro");
    cout << "Max trains arriving at Faro: " << real_network->maxTrainsStation(faro) << endl;
    Station *ermidas_sado = real_network->findStation("Ermidas-Sado");
    cout << "Max trains arriving at Ermidas-Sado: " << real_network->maxTrainsStation(ermidas_sado) << endl;
    cout << endl;

    NetworkManager::deleteGraph(real_network);
}

void testTopAffectedStations01() {
    Network *network = NetworkManager::createGraph("../dataset/test-dataset-2/");
    Network *network_reduced = NetworkManager::createGraph("../dataset/test-dataset-2/");
    vector<Station*> topAffectedStations;
    vector<string> reduceStations = {"ST10"};
    tracks_vector reduceTracks = {};
    NetworkManager::reduceConnectivity(network_reduced, reduceTracks, reduceStations);

    cout << "Test top affected stations 01" << endl;
    topAffectedStations = NetworkManager::topAffectedStations(network, network_reduced, 3);
    for (int i = 0; i < topAffectedStations.size(); i++)
        cout << "Top " << i+1 << " affected station: " << topAffectedStations[i]->getName() << endl;
    cout << endl;

    NetworkManager::deleteGraph(network);
    NetworkManager::deleteGraph(network_reduced);
}

void testTopAffectedStations02() {
    Network *network = NetworkManager::createGraph("../dataset/test-simple-dataset/");
    Network *network_reduced = NetworkManager::createGraph("../dataset/test-simple-dataset/");
    vector<Station*> topAffectedStations;
    vector<string> reduceStations = {"ST02"};
    tracks_vector reduceTracks = {};
    NetworkManager::reduceConnectivity(network_reduced, reduceTracks, reduceStations);

    cout << "Test top affected stations 02" << endl;
    topAffectedStations = NetworkManager::topAffectedStations(network, network_reduced, 3);
    for (int i = 0; i < topAffectedStations.size(); i++)
        cout << "Top " << i+1 << " affected station: " << topAffectedStations[i]->getName() << endl;
    cout << endl;

    NetworkManager::deleteGraph(network);
    NetworkManager::deleteGraph(network_reduced);
}

void testTopAffectedStations03() {
    Network *network = NetworkManager::createGraph("../dataset/real-dataset/");
    Network *network_reduced = NetworkManager::createGraph("../dataset/real-dataset/");
    vector<Station*> topAffectedStations;
    vector<string> reduceStations = {"Porto Campanhã", "Lisboa Oriente", "Aveiro - Vouga", "Coimbra B", "Coimbra", "Faro", "Ermidas-Sado"};
    tracks_vector reduceTracks = {{"São Romão - A","São Romão"}, {"Pala","Mosteirô"}, {"Loulé","Almancil"}};
    NetworkManager::reduceConnectivity(network_reduced, reduceTracks, reduceStations);

    cout << "Test top affected stations 03" << endl;
    topAffectedStations = NetworkManager::topAffectedStations(network, network_reduced, 10);
    for (int i = 0; i < topAffectedStations.size(); i++)
        cout << "Top " << i+1 << " affected station: " << topAffectedStations[i]->getName() << endl;
    cout << endl;

    NetworkManager::deleteGraph(network);
    NetworkManager::deleteGraph(network_reduced);
}

void run() {
    edmondsKarpCostTest();
    realTopMaxFlow();
    testReducedConnectivity01();
    testReducedConnectivity02();
    testReducedConnectivity03();
    testMaxTrainStations01();
    testMaxTrainStations02();
    testTopAffectedStations01();
    testTopAffectedStations02();
    testTopAffectedStations03();
}