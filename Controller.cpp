#include "Controller.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
}

std::string normalizeCamelCase(const std::string& str) {
    // Create a new string to store the normalized result
    std::string result;

    // Append the first character to the result string
    result += str[0];

    // Iterate through the rest of the string
    for (int i = 1; i < str.length(); i++) {
        // If the current character is uppercase, insert a space before it
        if (std::isupper(str[i])) {
            result += ' '; // Insert a space
        }
        // Append the current character to the result string
        result += str[i];
    }

    // Copy the normalized result back to the original string
    return result;
}


void removeWhitespace(std::string& str) {
    auto it = find_if(str.begin(), str.end(), [](char c) {
        return isspace(c);
    });

    while (it != str.end()) {
        it = str.erase(it);
        it = find_if(it, str.end(), [](char c) {
            return isspace(c);
        });
    }
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
    std::string stationsFile = "../", networkFile = "../", aux, fs, fn;
    switch (option) {
        case 0:
            return;

        case 1:
            clearScreen();
            stationsFile += "stations.csv"; // tem que ser assim
            networkFile += "network.csv"; // porque o path é em relação ao executável
            readStations(stationsFile); // e o executável está na pasta cmake-build-debug
            readNetwork(networkFile);
            mainMenu();
            return;

        case 2:
            clearScreen();
            std::cout << "\t\t**Start Menu**\n\n";
            std::cout << "Stations file: ";
            std::cin >> fs;
            std::cout << "Network file: ";
            std::cin >> fn;
            stationsFile += fs;
            networkFile += fn;
            readStations(stationsFile);
            readNetwork(networkFile);
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
    std::vector options = { "Discover the maximum number of trains that can simultaneously travel between two stations;",
                            "Determine which pairs of stations require the most amount of trains;",
                            "Discover the top-k municipalities and districts regarding their transportation needs;",
                            "Discover the maximum number of trains that can simultaneously arrive at a station;",
                            "Discover the maximum amount of trains that can simultaneously travel between two stations with minimum cost;",
                            "Discover the maximum number of trains that can simultaneously travel between two stations with just 1 type of train;",
                            "Discover the top-k most affected stations for each segment."
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
            maxFlowMenu();
            return;

        case 2:
            clearScreen();
            maxTrainsNeededMenu();
            return;
            
        case 3:
            clearScreen();
            topkTransportNeedsMenu();
            return;
            
        case 4:
            clearScreen();
            maxSimultaneousTrainsMenu();
            return;

        case 5:
            clearScreen();
            maxTrainsMinCostMenu();
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

void Controller::readStations(const std::string& filename) {
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

        removeWhitespace(name);
        removeWhitespace(district);
        removeWhitespace(municipality);
        removeWhitespace(township);
        removeWhitespace(stationLine);

        if (name.empty() && district.empty() && municipality.empty() && township.empty() && stationLine.empty())
            continue;

        if (stations.find(name) == stations.end()) {
            stations.insert({name, id});
            network.addVertex(id++, name, district, municipality, township, stationLine);
        }
    }

}

void Controller::readNetwork(const std::string& filename) {
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

        removeWhitespace(stationA);
        removeWhitespace(stationB);
        removeWhitespace(service);

        if (stationA.empty() || stationB.empty() || capacity.empty() || service.empty() || stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end())
            continue;

        network.addBidirectionalEdge(stations[stationA], stations[stationB], std::stod(capacity), service);
    }
}


void Controller::maxFlowMenu() {
    std::cout << "\t\t**Maximum Amount of Trains Between Two Stations**\n\n";
    std::string stationA, stationB;
    std::cout << "Source station: ";
    std::cin >> stationA;
    std::cout << "Destination station: ";
    std::cin >> stationB;
    clearScreen();
    if (stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end()) {
        std::cout << "ERROR: Invalid station(s)!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        maxFlowMenu();
        return;
    }

    std::cout << "Maximum amount of trains between " << stationA << " and " << stationB << ": " << network.edmondsKarp(stations[stationA], stations[stationB]) << "\n";
    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}


void Controller::maxTrainsNeededMenu(){
    std::cout << "\t\t**Pairs of Stations that Require the Most Amount of Trains**\n\n";
    std::pair<int, std::vector<std::pair<std::string, std::string>>> res = network.maxTrainsNeeded();
    int maxFlow = res.first;
    std::vector<std::pair<std::string, std::string>> maxFlowStations = res.second;
    std::cout << "Max flow: " << maxFlow << std::endl;
    std::cout << maxFlowStations.size() << " stations with max flow:" << std::endl;
    for (const auto &p : maxFlowStations) {
        std::cout << "(" << normalizeCamelCase(p.first) << ", " << normalizeCamelCase(p.second) << ")\n";
    }
    std::cout << std::endl;
    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}


void Controller::topkTransportNeedsMenu(){
    std::cout << "\t\t**Top-k Municipalities and Districts Regarding their Transportation Needs**\n\n";
    int k;
    std::cout << "Enter the value of k: ";
    std::cin >> k;
    network.topkTransportNeeds(k);
    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}


void Controller::maxSimultaneousTrainsMenu() {
    std::cout << "\t\t**Maximum Amount of Trains that can Simultaneously Arrive at a Station**\n\n";
    std::string stationName;
    std::cout << "Enter the name of the station: ";
    std::cin >> stationName;

    if(stations.find(stationName) == stations.end()){
        std::cout << "ERROR: Invalid station(s)!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        maxSimultaneousTrainsMenu();
        return;
    }
    else network.maxSimultaneousTrains(stationName);

    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}


void Controller::maxTrainsMinCostMenu(){
    std::cout << "\t\t**Maximum Amount of Trains that can Simultaneously Travel Between two Stations with Minimum Cost**\n\n";
    std::string stationA, stationB;
    std::cout << "Source station: ";
    std::cin >> stationA;
    std::cout << "Destination station: ";
    std::cin >> stationB;
    clearScreen();
    if (stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end()) {
        std::cout << "ERROR: Invalid station(s)!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        maxTrainsMinCostMenu();
        return;
    }
    network.maxTrainsMinCost(stationA, stationB);
    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}