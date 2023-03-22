//
// Created by 35191 on 08/03/2023.
//

#include "Controller.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}

void Controller::startMenu() {
    clearScreen();
    std::cout << "\t\t*RAILWAY NETWORK*\n\n";
    std::vector options = { "Read standard files", "Read other files" };
    for(int i = 1; i <= options.size(); i++){
        std::cout << i << ". " << options[i - 1] << "\n";
    }
    std::cout << "0. Exit.\n";
    unsigned int option;
    std::cout << "Select an option: ";
    std::cin >> option;
    std::string stationsFile, networkFile, aux;
    switch (option) {
        case 0:
            return;

        case 1:
            clearScreen();
            stationsFile = "../stations.csv"; // tem que ser assim
            networkFile = "../network.csv"; // porque o path é em relação ao executável
            readStations(stationsFile); // e o executável está na pasta cmake-build-debug
            readNetwork(networkFile);
            mainMenu();
            return;

        case 2:
            clearScreen();
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
            clearScreen();
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            startMenu();
            return;

    }
}


void Controller::mainMenu(){
    clearScreen();
    std::cout << "\t\t**Main Menu**\n\n";
    std::vector options = { "Discover maximum number of trains that can simultaneously travel between two stations;",
                            "Determine which pairs of stations require the most amount of trains;",
                            "Discover the top-k municipalities and districts;",
                            "Discover the maximum number of trains that can simultaneously arrive at a station;",
                            "Discover the maximum amount of trains that can simultaneously travel between two stations with minimum cost;"
                            };
    for(int i=1;i<=options.size();i++){
        std::cout << i << ". " << options[i-1] << "\n";
    }
    std::cout << "0. Exit.\n";
    unsigned int option;
    std::cout << "Select an option: ";
    std::cin >> option;
    std::string aux;
    switch (option) {
        case 0:
            return;

        case 1:
            clearScreen();
            std::cout << "\n\tNoice!";
            return;

        default:
            clearScreen();
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

    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string name, district, municipality, township, stationLine;

        std::getline(iss, name, ',');
        std::getline(iss, district, ',');
        std::getline(iss, municipality, ',');
        std::getline(iss, township, ',');
        std::getline(iss, stationLine);

        if (name.empty() && district.empty() && municipality.empty() && township.empty() && stationLine.empty())
            continue;

        if (stations.find(name) == stations.end()) {
            stations.insert({name, id});
            network.addVertex(id++, name, district, municipality, township, stationLine);
        }
    }

}

void Controller::readNetwork(std::string filename) {
    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string stationA, stationB, capacity, service;

        std::getline(iss, stationA, ',');
        std::getline(iss, stationB, ',');
        std::getline(iss, capacity, ',');
        std::getline(iss, service);

        if (stationA.empty() || stationB.empty() || capacity.empty() || service.empty() || stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end())
            continue;

        network.addEdge(stations[stationA], stations[stationB], std::stod(capacity));
    }

    int total = 0;

    for (auto i = 0; i < network.getNumVertex(); i++) {
        std::cout << "\nNumber of edges of vertex " << i << ": " << network.getVertexSet()[i] -> getAdj().size() << std::endl;
        total += network.getVertexSet()[i] -> getAdj().size();
    }
    std::cout << "\n" << total << std::endl;
}

