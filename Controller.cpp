//
// Created by 35191 on 08/03/2023.
//

#include "Controller.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void Controller::startMenu() {
    std::system("clear");
    std::cout << "\t\t*APP NAME*\n\n";
    std::vector options = {"Read standard files","Read other files"};
    for(int i=1;i<=options.size();i++){
        std::cout << i << ". " << options[i-1] << "\n";
    }
    std::cout << "0. Exit\n";
    unsigned int option;
    std::cin >> option;
    std::string stations,network,aux;
    switch (option) {
        case 0:
            return;

        case 1:
            system("CLS");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "Fetching Data...";
            stations = "stations.csv";
            network = "network.csv";
            //readStations(stations);
            //readNetwork(network);
            mainMenu();
            return;

        case 2:
            system("CLS");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "Stations file: ";
            std::cin >> stations;
            std::cout << "Network file: ";
            std::cin >> network;
            //readStations(stations);
            //readNetwork(network);
            mainMenu();
            return;

        default:
            system("CLS");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            startMenu();
            return;

    }
}


void Controller::mainMenu(){
    std::system("CLS");
    std::cout << "\t\t**Main Menu**\n\n";
    std::vector options = {"option"};
    for(int i=1;i<=options.size();i++){
        std::cout << i << ". " << options[i-1] << "\n";
    }
    std::cout << "0. Exit\n";
    unsigned int option;
    std::cin >> option;
    std::string aux;
    switch (option) {
        case 0:
            return;

        case 1:
            system("CLS");
            std::cout << "\n\tNoice!";
            return;

        default:
            system("CLS");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            mainMenu();
            return;

    }
}

void Controller::readStations(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, district, municipality, township, stationLine;

        std::getline(iss, name, ',');
        std::getline(iss, district, ',');
        std::getline(iss, municipality, ',');
        std::getline(iss, township, ',');
        std::getline(iss, stationLine);

        if (stations.find(name) == stations.end()) {
            stations.insert(name);
            // create Vertex and add it to Graph
        }
    }
}
