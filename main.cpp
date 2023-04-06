#include <iostream>
#include <string>
#include <vector>
#include <csignal>

#include "headers/Menu.h"
#include "headers/Network.h"
#include "headers/NetworkManager.h"
#include "Test.hpp"

using namespace std;

int main () {
    Network *network = NetworkManager::createGraph("dataset/real-dataset/");
    Menu menu(network);
    menu.run();
    return 0;
}