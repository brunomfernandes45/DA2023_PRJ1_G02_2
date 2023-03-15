//
// Created by 35191 on 08/03/2023.
//

#include "Controller.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

void Controller::startMenu() {
    std::system("clear");
    std::cout << "\t\t*APP NAME*\n\n";
    std::vector options = {"Read standard files","Read other files"};
    for(int i=1;i<=options.size();i++){
        std::cout << i << ". " << options[i-1] << "\n";
    }
    std::cout << "0. Exit\n";
    unsigned int option;
    std::cout << "Select an option: ";
    std::cin >> option;
    std::string stationsFile, networkFile, aux;
    switch (option) {
        case 0:
            return;

        case 1:
            system("clear");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "Fetching Data...";
            stationsFile = "../stations.csv"; // tem que ser assim
            networkFile = "../network.csv"; // porque o path é em relação ao executável
            readStations(stationsFile); // e o executável está na pasta cmake-build-debug
            //readNetwork(networkFile);
            mainMenu();
            return;

        case 2:
            system("clear");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "Stations file: ";
            std::cin >> stationsFile;
            std::cout << "Network file: ";
            std::cin >> networkFile;
            //readStations(stationsFile);
            //readNetwork(networkFile);
            mainMenu();
            return;

        default:
            system("clear");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            startMenu();
            return;

    }
}


void Controller::mainMenu(){
    std::system("clear");
    std::cout << "\t\t**Main Menu**\n\n";
    std::vector options = {"option"};
    for(int i=1;i<=options.size();i++){
        std::cout << i << ". " << options[i-1] << "\n";
    }
    std::cout << "0. Exit\n";
    unsigned int option;
    std::cout << "Select an option: ";
    std::cin >> option;
    std::string aux;
    switch (option) {
        case 0:
            return;

        case 1:
            system("clear");
            std::cout << "\n\tNoice!";
            return;

        default:
            system("clear");
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            mainMenu();
            return;

    }
}

void Controller::readStations(std::string filename) {
    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }
    int id = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string name, district, municipality, township, stationLine;

        std::getline(iss, name, ',');
        std::getline(iss, district, ',');
        std::getline(iss, municipality, ',');
        std::getline(iss, township, ',');
        std::getline(iss, stationLine);

        if (stations.find(name) == stations.end()) {
            stations.insert(name);
            network.addVertex(id++, name, district, municipality, township, stationLine);
        }
    }

    std::cout << "\nNumber of nodes in the network: " << network.getNumVertex() << std::endl;
}
