<<<<<<< HEAD
//
// Created by Daniel Rebelo on 05/04/2023.
//

#include "headers/Menu.h"
using namespace std;

int MainMenu(){
    cout << "" << endl;
    return 0;
}
=======
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
        cout << "\n\n" <<  input << "\n\n" << endl;

        cleanTerminal();
    }
}

void Menu::mainMenu() {
    cout << "__________________________________________________________________________________________________________________________________\n"
         << "|                                                           Main menu                                                            |\n"
         << "|                                                  Choose an option to continue                                                  |\n"
         << "|________________________________________________________________________________________________________________________________|\n"
         << "|                                                                                                                                |\n"
         << "|          1. Calculate the maximum number of trains that can travel between two chosen stations. [exercise 2.1.]                |\n"
         << "|          2. Calculate the maximum number of trains that can travel between any two stations. [exercise 2.2.]                   |\n"
         << "|          3. Display top n districts/municipalities according to budget needs. [exercise 2.3.]                                  |\n"
         << "|          4. Calculate the maximum number of trains that can arrive to a chosen station. [exercise 2.4.]                        |\n"
         << "|          5. Calculate the maximum number of trains that can travel between two chosen stations with                            |\n"
         << "|             minimum cost. [exercise 3.1.]                                                                                      |\n"
         << "|          6. Calculate the maximum number of trains that can travel between two chosen stations under                           |\n"
         << "|             under reduced connectivity circumstances. [exercise 4.1.]                                                          |\n"
         << "|          7. Display top n stations affected by the reduced connectivity circumstances. [exercise 4.2.]                         |\n"
         << "|          8. Manage reduced connectivity graphs                                                                                 |\n"
         << "|          9. Run tests                                                                                                          |\n"
         << "|          10. Exit                                                                                                              |\n"
         << "|________________________________________________________________________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> input;
        if (1 <= stoi(input) && stoi(input) <= 10) break;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::exercise_2_1() {

}

void Menu::exercise_2_2() {

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

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


>>>>>>> d6f9b507c0d66ee6bfda5ee33c61eee052614ab6
