#include "headers/Menu.h"
#include "headers/Network.h"
#include "headers/NetworkManager.h"

using namespace std;

int main () {
    string folder, path;
    cout << "Write the name of the folder with your dataset (it must be inside the dataset folder): "; cin >> folder;
    path = "../dataset/" + folder + "/";
    Network *network = NetworkManager::createGraph(path);
    Menu menu(network, path);
    menu.run();
    return 0;
}