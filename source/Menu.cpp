#include "headers/Menu.h"

using namespace std;

Menu::Menu(Network *network) {
    this->network = network;
    this->input = "0";
    cleanTerminal();
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
        // cout << "\n\n" <<  input << "\n\n" << endl;
        cout << "\n\n" << endl;

        cleanTerminal();
    }
}

void Menu::mainMenu() {
    cout << "______________________________________________________________________________________________________________________________________________________________________________________________\n"
         << "|                                                           Main menu                                                            |\n"
         << "|                                                  Choose an option to continue                                                  |\n"
         << "|____________________________________________________________________________________________________________________________________________________________________________________________|\n"
         << "|" << Util::center("", 188) << "|\n"
         << "|" << Util::center("1. Calculate the maximum number of trains that can travel between two chosen stations. [exercise 2.1.]", 188) << "|\n"
         << "|" << Util::center("2. Calculate the maximum number of trains that can travel between any two stations. [exercise 2.2.]", 188) << "|\n"
         << "|" << Util::center("3. Display top n districts/municipalities according to budget needs. [exercise 2.3.]", 188) << "|\n"
         << "|" << Util::center("4. Calculate the maximum number of trains that can arrive to a chosen station. [exercise 2.4.]", 188) << "|\n"
         << "|" << Util::center("5. Calculate the maximum number of trains that can travel between two chosen stations with minimum cost. [exercise 3.1.]", 188) << "|\n"
         << "|" << Util::center("6. Calculate the maximum number of trains that can travel between two chosen stations under reduced connectivity circumstances. [exercise 4.1.]", 188) << "|\n"
         << "|" << Util::center("7. Display top n stations affected by the reduced connectivity circumstances. [exercise 4.2.]", 188) << "|\n"
         << "|" << Util::center("8. Manage reduced connectivity graphs", 188) << "|\n"
         << "|" << Util::center("9. Run tests", 188) << "|\n"
         << "|" << Util::center("10. Exit", 188) << "|\n"
         << "|____________________________________________________________________________________________________________________________________________________________________________________________|\n\n";

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

}

void Menu::exercise_2_2() {
    std::pair<double,std::vector<std::pair<std::string,std::string>>> res = network->topMaxFlow();
    double MaxFlow = res.first;
    std::vector<std::pair<std::string,std::string>> v = res.second;
    cout << "When taking into consideration the full network capacity, the most amount of trains required by a pair of stations is: " << MaxFlow << " " << endl;
    cout << "The pair(s) of stations that require this amount is/are: "<< endl;
    int i = 1;
    for (auto p : v){
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

Station *listStations(Network *nw, string message) {
    int page = 0;
    bool alive = true;
    vector<Station *> stations = nw->getStationsSet();
    while (alive) {
        cout
                << "______________________________________________________________________________________________________________________________________________________________________________________________\n"
                << "|" << Util::center("STATIONS", 188) << "|\n"
                << "|" << Util::center(message, 188) << "|\n"
                << "|____________________________________________________________________________________________________________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) stations.size()); i++) {
            cout << right << setw(5) << to_string(i + 1) + ".   " << left
                 << setw(40) << stations[i]->getName()
                 << setw(20) << stations[i]->getDistrict()
                 << setw(30) << stations[i]->getMunicipality()
                 << setw(60) << stations[i]->getTownship()
                 << setw(30) << stations[i]->getLine() << endl;
        }
        cout
                << "____________________________________________________________________________________________________________________________________________________________________________________________\n"
                << "|" << Util::center("WRITE A NUMBER TO SELECT A STATIONS", 188) << "|\n"
                << "|" << Util::center("WRITE AN AIRPORT CODE TO SELECT AN AIRPORT", 188) << "|\n"
                << "|" << Util::center("WRITE W TO MOVE UP", 188) << "|\n"
                << "|" << Util::center("WRITE S TO MOVE DOWN", 188) << "|\n"
                << "|" << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << "|\n"
                << "|____________________________________________________________________________________________________________________________________________________________________________________________|\n\n";

        /*while (true) {
            cout << "   - OPTION: "; cin >> input;
            string tmp = input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) airport.size())) {
                while (true) {
                    cout << "   - 1. Display airport info" << endl
                         << "   - 2. Display possible targets" << endl;
                    cin >> input;
                    if (input == "1")
                        alive = airportInfo(airportsCache[stoi(tmp) - 1]);
                    else if (input == "2")
                        alive = reachableAirports(airportsCache[stoi(tmp) - 1]);
                    else cout << "   - INVALID OPTION" << endl;
                    break;
                }
                break;
            } else if (isAlpha(input) && input.size() == 3) {
                if (dm->getAirports().find(input) == dm->getAirports().end()) cout << "   - WRONG CODE\n";
                else {
                    while (true) {
                        cout << "   - 1. Display airport info" << endl
                             << "   - 2. Display possible targets" << endl;
                        cin >> input;
                        if (input == "1")
                            alive = airportInfo(dm->getAirports()[tmp]);
                        else if (input == "2")
                            alive = reachableAirports(dm->getAirports()[tmp]);
                        else cout << "   - INVALID OPTION" << endl;
                        break;
                    }
                    break;
                }
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) airport.size()) {
                page++;
                break;
            } else if (normalise(input) == "menu" || normalise(input) == "back")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }*/
    }
}


void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
