//
// Created by 35191 on 08/03/2023.
//

#include "Controller.h"

using namespace std;

void Controller::startMenu() {
    system("CLS");
    cout << "\t\t**Start Menu**\n\n";
    vector options = {"Read standard files","Read other files"};
    for(int i=1;i<=options.size();i++){
        cout << i << ". " << options[i-1] << "\n";
    }
    cout << "0. Exit\n";
    unsigned int option;
    cin >> option;
    string stations,network,aux;
    switch (option) {
        case 0:
            return;
        case 1:
            system("CLS");
            cout << "\t\t*Start Menu*\n\n";
            cout << "Fetching Data...";
            stations = "stations.csv";
            network = "network.csv";
            //readStations(stations);
            //readNetwork(network);
            mainMenu();
            return;

        case 2:
            system("CLS");
            cout << "\t\t*Start Menu*\n\n";
            cout << "Stations file: ";
            cin >> stations;
            cout << "\nNetwork file: ";
            cin >> network;
            //readStations(stations);
            //readNetwork(network);
            mainMenu();
            return;

        default:
            system("CLS");
            cout << "\t\t**Start Menu**\n\n";
            cout << "ERROR: Invalid option!\n";
            cout << "(Press any key + Enter to continue)\n";
            cin >> aux;
            startMenu();
            return;

    }
}

void Controller::mainMenu(){
    system("CLS");
    cout << "\t\t**Main Menu**\n\n";
    vector<string> options={"OPÇAO NUMERO UM"};
    for(int i=1;i<=options.size();i++){
        cout << i << ". " << options[i-1] << "\n";
    }
    cout << "0. Exit\n";
    unsigned int option;
    cin >> option;
    string aux;
    switch (option) {
        case 0:
            return;
        case 1:
            system("CLS");
            cout<<"\t\tVERY NOICE\n";
            return;
        default:
            system("CLS");
            cout << "\t\t*Start Menu*\n\n";
            cout << "ERROR: Invalid option!\n";
            cout << "(Press any key + Enter to continue)\n";
            cin >> aux;
            mainMenu();
            return;
    }
}
