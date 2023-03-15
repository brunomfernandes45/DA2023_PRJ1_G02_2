//
// Created by 35191 on 08/03/2023.
//

#include "Controller.h"

void Controller::startMenu() {
    std::system("clear");
    std::cout << "\t\t*APP NAME*\n\n";
    std::vector options = {"Read standard files","Read other files"};
    for(int i=1;i<=options.size();i++){
        std::cout << i << ". " << options[i-1] << "\n";
    }
    std::cout << "0. Exit";
    unsigned int option;
    std::cin >> option;
    std::string stations,network,aux;
    switch (option) {
        case 0:
            return;

        case 1:
            system("clear");
            std::cout << "Fetching Data...";
            stations = "stations.csv";
            network = "network.csv";
            //readStations(stations);
            //readNetwork(network);
            //mainMenu();
            return;

        case 2:
            system("clear");
            std::cout << "\t\t*APP NAME*\n\n";
            std::cout << "Stations file: ";
            std::cin >> stations;
            std::cout << "Network file: ";
            std::cin >> network;
            //readStations(stations);
            //readNetwork(network);
            //mainMenu();
            return;

        default:
            system("clear");
            std::cout << "\t\t*APP NAME*\n\n";
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            startMenu();
            return;

    }
}
