#include "headers/Menu.h"

using namespace std;

Menu::Menu(Network *network) {
    this->network = network;
    this->input = "0";
    Util::cleanTerminal();
}

void Menu::run() {

    bool alive = true;
    while (alive) {
        switch (stoi(input)) {
            case 0: mainMenu(); break;
            case 1: exercise_2_1(); input = "0"; break;
            case 2: exercise_2_2(); input = "0"; break;
            case 3: exercise_2_3(); input = "0"; break;
            case 4: exercise_2_4(); input = "0"; break;
            case 5: exercise_3_1(); input = "0"; break;
            case 6: exercise_4_1(); input = "0"; break;
            case 7: exercise_4_2(); input = "0"; break;
            case 8: manageNetworks(); input = "0"; break;
            case 9: runTests(); input = "0"; break;
            case 10: cout << "hello"; alive = false; break;
        }
        Util::cleanTerminal();
    }
}

void Menu::mainMenu() {
    cout << string(190, '_') << endl
         << '|' << Util::center("Main menu", 188) << '|' << endl
         << '|' << Util::center("Choose an option to continue", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << '|' << Util::center("", 188) << '|' << endl
         << '|' << Util::center("1. Calculate the maximum number of trains that can travel between two chosen stations. [exercise 2.1.]", 188) << '|' << endl
         << '|' << Util::center("2. Calculate the maximum number of trains that can travel between any two stations. [exercise 2.2.]", 188) << '|' << endl
         << '|' << Util::center("3. Display top n districts/municipalities according to budget needs. [exercise 2.3.]", 188) << '|' << endl
         << '|' << Util::center("4. Calculate the maximum number of trains that can arrive to a chosen station. [exercise 2.4.]", 188) << '|' << endl
         << '|' << Util::center("5. Calculate the maximum number of trains that can travel between two chosen stations with minimum cost. [exercise 3.1.]", 188) << '|' << endl
         << '|' << Util::center("6. Calculate the maximum number of trains that can travel between two chosen stations under reduced connectivity circumstances. [exercise 4.1.]", 188) << '|' << endl
         << '|' << Util::center("7. Display top n stations affected by the reduced connectivity circumstances. [exercise 4.2.]", 188) << '|' << endl
         << '|' << Util::center("8. Manage reduced connectivity graphs", 188) << '|' << endl
         << '|' << Util::center("9. Run tests", 188) << '|' << endl
         << '|' << Util::center("10. Exit", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl;

    while (true) {
        cout << "   - OPTION: ";
        cin >> input;
        try {
            int inputNum = stoi(input);
            if (1 <= inputNum && inputNum <= 10) {
                // Valid input
                break;
            } else {
                cout << "   - INVALID OPTION" << endl;
            }
        } catch (const std::invalid_argument&) {
            cout << "   - INVALID OPTION" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Menu::exercise_2_1() {
    Station *choice1 = listStations(network, "Choose the first station: ");
    if (choice1 == nullptr) return;
    Station *choice2 = listStations(network, "Choose the second station: ", choice1);
    if (choice2 == nullptr) return;
    Util::cleanTerminal();
    string message = "From: " + choice1->getName() + " ---> To: " + choice2->getName();
    int result = NetworkManager::maxFlowBetween(network, choice1, choice2);
    while (true) {
        cout << string(190, '_') << endl
             << '|' << Util::center("Max flow", 188) << '|' << endl
             << '|' << Util::center(message, 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl
             << Util::center("The calculated result is: " + to_string(result), 188) << endl
             << Util::center("This means that between the two stations there can be a maximum number of " + to_string(result) + " trains.", 188)
             << endl
             << string(190, '_') << endl
             << '|' << Util::center("TYPE 0 TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "Type 0: ";
            cin >> input;
            try {
                int inputNum = stoi(input);
                if (inputNum == 0) {
                    // Valid input
                    break;
                } else {
                    cout << "   - INVALID OPTION" << endl;
                }
            } catch (const std::invalid_argument&) {
                cout << "   - INVALID OPTION" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

void Menu::exercise_2_2() {
    std::pair<double,std::vector<std::pair<std::string,std::string>>> res = network->topMaxFlow();
    double MaxFlow = res.first;
    std::vector<std::pair<std::string,std::string>> v = res.second;
    cout << "When taking into consideration the full network capacity, the most amount of trains required by a pair of stations is: " << MaxFlow << " " << endl;
    cout << "The pair(s) of stations that require this amount is/are: "<< endl;
    int i = 1;
    for (const auto &p : v) {
        cout << i++ << ". " << p.first << "->" << p.second << endl;
    }
    while (true) {
        cout << "\n\n" << "Want to go back to the menu? Type 0: ";
        cin >> input;
        try {
            int inputNum = stoi(input);
            if (inputNum == 0) {
                // Valid input
                break;
            } else {
                cout << "   - INVALID OPTION" << endl;
            }
        } catch (const std::invalid_argument&) {
            cout << "   - INVALID OPTION" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }


}

void Menu::exercise_2_3() {
    int inputNum;
    while (true) {
        cout << "\n\n" << "Select option:" << endl;
        cout << "1. District" << endl;
        cout << "2. Municipality" << endl;
        cout << "0. Return to menu" << endl;
        cin >> input;
        try {
            inputNum = stoi(input);
            if (inputNum == 0 || inputNum == 1 || inputNum == 2) {
                // Valid input
                break;
            } else {
                cout << "   - INVALID OPTION" << endl;
            }
        } catch (const std::invalid_argument&) {
            cout << "   - INVALID OPTION" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    //string location = inputNum == 1 ? "district" : "municipality" ;
    string location = "district";
    std::vector<std::pair<std::string, double>> res = network->topTransportationNeeds(location);
    if (location == "district") cout << "The municipalities with the most needs are: " << endl;
    else cout << "The districts with the most needs are: " << endl;
    for (auto e : res){
        cout << std::left << std::setw(20) << std::setfill(' ') << e.first << setw(12) << e.second << endl;    }
    while (true) {
        cout << "\n\n" << "Type 0 to return to menu: ";
        cin >> input;
        try {
            inputNum = stoi(input);
            if (inputNum == 0) {
                // Valid input
                break;
            } else {
                cout << "   - INVALID OPTION" << endl;
            }
        } catch (const std::invalid_argument&) {
            cout << "   - INVALID OPTION" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Menu::exercise_2_4() {
    Station *st = listStations(network, "Choose the first station: ");
    if (st == nullptr) return;
    double maxFlow = network->maxTrainsStation(st);
    cout << "The maximum number of trains that can simultaneously arrive at " << st->getName() << " train station is " << maxFlow << endl;
    int inputNum;
    while (true) {
        cout << "\n\n" << "Type 0 to return to menu: ";
        cin >> input;
        try {
            inputNum = stoi(input);
            if (inputNum == 0) {
                // Valid input
                break;
            } else {
                cout << "   - INVALID OPTION" << endl;
            }
        } catch (const std::invalid_argument&) {
            cout << "   - INVALID OPTION" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}

void Menu::exercise_3_1() {
    Station *stationSource = listStations(network, "Choose the first station: ");
    if (stationSource == nullptr) return;
    Station *stationDest = listStations(network, "Choose the first station: ");
    if (stationDest == nullptr) return;
    pair<int,int> p = network->edmondsKarpCost(stationSource,stationDest);
    cout << "The maximum amount of trains that can simultaneously travel between two specific stations with minimum costs for the company"
            " is: " << endl;
    cout << "Amount: " << p.first << " | " << "Cost: " << p.second << endl;
    int inputNum;
    while (true) {
        cout << "\n\n" << "Type 0 to return to menu: ";
        cin >> input;
        try {
            inputNum = stoi(input);
            if (inputNum == 0) {
                // Valid input
                break;
            } else {
                cout << "   - INVALID OPTION" << endl;
            }
        } catch (const std::invalid_argument&) {
            cout << "   - INVALID OPTION" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}

void Menu::exercise_4_1() {

}

void Menu::exercise_4_2() {

}

void Menu::manageNetworks() {
    // TODO
    // See network
    // Create, remove, rename, see reduced networks
}

void Menu::runTests() {
    // TODO

}

Station *Menu::listStations(Network *nw, const string &message, Station *ignoreStation) {
    Util::cleanTerminal();
    int page = 0;
    vector<Station*> stations = nw->getStationsSet();
    if (ignoreStation) {
        for (auto itr = stations.begin(); itr != stations.end(); itr++) {
            if (*itr == ignoreStation) {
                stations.erase(itr);
                break;
            }
        }
    }
    while (true) {
        cout    << string(190, '_') << endl
                << '|' << Util::center("STATIONS", 188) << '|' << endl
                << '|' << Util::center(message, 188) << '|' << endl
                << '|' << string(188, '_') << '|' << endl;
        for (int i = page * 20; i < min(page * 20 + 20, (int) stations.size()); i++) {
            cout << right << setw(5) << to_string(i + 1) + ".   " << left
                 << setw(40) << stations[i]->getName()
                 << setw(20) << stations[i]->getDistrict()
                 << setw(30) << stations[i]->getMunicipality()
                 << setw(60) << stations[i]->getTownship()
                 << setw(30) << stations[i]->getLine() << endl;
        }
        cout << string(190, '_') << endl
             << '|' << Util::center("WRITE A NUMBER OR A STATION NAME TO SELECT A STATION", 188) << '|' << endl
             << '|' << Util::center("WRITE W TO MOVE UP", 188) << '|' << endl
             << '|' << Util::center("WRITE S TO MOVE DOWN", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;

        while (true) {
            cout << "   - OPTION: " << std::flush;;
            getline(cin >> ws, input);
            cout << endl;
            string tmp = input;
            if (Util::isNumerical(input) && page * 20 + 1 <= stoi(input) &&
                stoi(input) <= min(page * 20 + 20, (int) stations.size())) {
                return stations[stoi(input) - 1];
            } else if (Util::normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (Util::normalise(input) == "s" && page * 20 + 20 < (int) stations.size()) {
                page++;
                break;
            } else if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") {
                return nullptr;
            } else if (Util::isAlpha(input)) {
                Station *station = network->findStation(input);
                if (station == nullptr) cout << "   - COULDN'T FIND STATION NAME\n";
                else return station;
            }
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}
