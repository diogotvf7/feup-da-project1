#ifndef FEUP_DA_PROJECT_MENU_H
#define FEUP_DA_PROJECT_MENU_H

#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "NetworkManager.h"
#include "Network.h"
#include "Util.h"

class Menu {
    Network *network;
    std::unordered_map<std::string, Network*> reducedNetworks;
    std::string input;
public:
    Menu(Network *network);
    void run();
    void mainMenu();
    void exercise_2_1();
    void exercise_2_2();
    void exercise_2_3();
    void exercise_2_4();
    void exercise_3_1();
    void exercise_4_1();
    void exercise_4_2();
    void manageReducedNetworks();
    void listReducedNetworks();
    bool createReducedNetwork();
    bool deleteReducedNetwork();
    bool renameReducedNetwork();
    void runTests();
    Station *listStations(Network *nw, const std::string &message, Station *ignore = nullptr);

    bool seeReducedNetworks();
};


#endif //FEUP_DA_PROJECT_MENU_H
