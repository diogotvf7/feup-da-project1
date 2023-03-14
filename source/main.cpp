#include <fstream>
#include "iostream"
#include "headers/fileReader.h"

#include <string>
#include "headers/fileReader.h"

int main(){
    std::ifstream stationsFile;
    stationsFile.open("dataset/stations.csv");
    fileReader fileReader;
    std::vector<Station*> test = fileReader.readStations(stationsFile);
    std::string inputFile = "dataset/network.csv";
    readNetworks(inputFile);

}