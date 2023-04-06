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
        getline(cin >> ws, input);
        if (Util::isNumerical(input) && 1 <= stoi(input) && stoi(input) <= 10) break;
        else cout << "   - INVALID OPTION" << endl;
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
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: ";
            getline(cin >> ws, input);
            cout << endl;
            if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

void Menu::exercise_2_2() {
    std::pair<int,std::vector<std::pair<std::string,std::string>>> res = network->topMaxFlow();
    int MaxFlow = res.first;
    std::vector<std::pair<std::string,std::string>> v = res.second;
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("Top max flow", 188) << '|' << endl
         << '|' << Util::center("This function calculates the max flow between all pairs of stations and", 188) << '|' << endl
         << '|' << Util::center("returns all the pairs that have the maximum max flow value.", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl
         << Util::center("The calculated result is: " + to_string(MaxFlow), 188) << endl
         << Util::center("The pair(s) of stations that have this max flow are:", 188) << endl;
    for (int i = 1; i <= v.size(); i++)
        cout << Util::center(to_string(i) + ". " + v[i - 1].first + " -> " + v[i-1].second, 190) << endl;
    cout << endl;
    cout << string(190, '_') << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: ";
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }

}

void Menu::exercise_2_3() {

}

void Menu::exercise_2_4() {

}

void Menu::exercise_3_1() {

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
    // Corre os testes em Test.cpp
    // Conseguir escolher que testes correr??
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
            cout << "   - OPTION: ";
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
