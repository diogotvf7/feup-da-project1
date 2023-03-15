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

    return 0;
}