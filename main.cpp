#include "headers/Menu.h"
#include "headers/Network.h"
#include "headers/NetworkManager.h"

using namespace std;

int main () {
    Network *network = NetworkManager::createGraph("../dataset/test-dataset-2/");
    Menu menu(network);
    menu.run();
    return 0;
}