#include "Controller.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>


void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        // Assume POSIX
        std::system("clear");
    #endif
}


std::string Controller::normalizeCamelCase(const std::string& str) {
    std::string result;
    result += str[0];

    for (int i = 1; i < str.length(); i++) {
        if (std::isupper(str[i])) result += ' ';
        result += str[i];
    }

    return result;
}

void Controller::removeWhitespaceAndAccents(std::string& str) {
    static const std::unordered_map<std::string, std::string> accents = {
            {"À", "A"}, {"Á", "A"}, {"Â", "A"}, {"Ã", "A"}, {"Ç", "C"}, {"È", "E"},
            {"É", "E"}, {"Ê", "E"}, {"Ì", "I"}, {"Í", "I"}, {"Î", "I"}, {"Ò", "O"},
            {"Ó", "O"}, {"Ô", "O"}, {"Õ", "O"}, {"Ù", "U"}, {"Ú", "U"}, {"à", "a"},
            {"á", "a"}, {"â", "a"}, {"ã", "a"}, {"ç", "c"}, {"è", "e"}, {"é", "e"},
            {"ê", "e"}, {"ì", "i"}, {"í", "i"}, {"î", "i"}, {"ò", "o"}, {"ó", "o"},
            {"ô", "o"}, {"õ", "o"}, {"ù", "u"}, {"ú", "u"}
    };

    auto it = str.begin();
    while (it != str.end()) {
        if (isspace(*it) && (it == str.begin() || isspace(*(it - 1)))) {
            it = str.erase(it);
            it--;
        } else {
            std::string c;
            c += *it;
            auto pos = accents.find(c);
            if (pos != accents.end()) {
                str.replace(it, it + 1, pos->second);
                it += pos->second.length();
            } else ++it;
        }
    }
}

void Controller::replaceWhitespace(std::string& str, char replacement) {
    auto it = find_if(str.begin(), str.end(), [](char c) {
        return isspace(c);
    });

    while (it != str.end()) {
        *it = replacement;
        it = find_if(it, str.end(), [](char c) {
            return isspace(c);
        });
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

        removeWhitespaceAndAccents(name);
        removeWhitespaceAndAccents(district);
        removeWhitespaceAndAccents(municipality);
        removeWhitespaceAndAccents(township);
        removeWhitespaceAndAccents(stationLine);

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

        removeWhitespaceAndAccents(stationA);
        removeWhitespaceAndAccents(stationB);
        replaceWhitespace(service,'-');

        if (stationA.empty() || stationB.empty() || capacity.empty() || service.empty() || stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end())
            continue;

        network.addBidirectionalEdge(stations[stationA], stations[stationB], std::stod(capacity), service);
    }
}


void Controller::startMenu() {
    clearScreen();
    std::cout << "\t\t*RAILWAY NETWORK*\n\n";

    std::vector options = { "Read standard files", "Read other files", "Read demo files" };
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
            stationsFile += "stations.csv";
            networkFile += "network.csv";
            readStations(stationsFile);
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

        case 3:
            clearScreen();
            stationsFile += "demoStations.csv";
            networkFile += "demoNetwork.csv";
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

    std::vector options = { "Display all stations;",
                            "Browse a specific station;",
                            "Discover the maximum number of trains that can simultaneously travel between two stations;",
                            "Determine which pairs of stations require the most amount of trains;",
                            "Discover the top-k municipalities and districts regarding their transportation needs;",
                            "Discover the maximum number of trains that can simultaneously arrive at a station;",
                            "Discover the maximum amount of trains that can simultaneously travel between two stations with minimum cost;",
                            "Discover the maximum number of trains that can simultaneously travel between two stations with just 1 type of service;",
                            "Discover the top-k most affected stations for each segment;"
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
            displayAllStationsMenu();
            return;

        case 2:
            clearScreen();
            browseStationMenu();
            return;

        case 3:
            clearScreen();
            maxFlowMenu();
            return;

        case 4:
            clearScreen();
            maxTrainsNeededMenu();
            return;
            
        case 5:
            clearScreen();
            topkTransportNeedsMenu();
            return;
            
        case 6:
            clearScreen();
            maxSimultaneousTrainsMenu();
            return;

        case 7:
            clearScreen();
            maxTrainsMinCostMenu();
            return;

        case 8:
            clearScreen();
            maxTrainsOneTypeMenu();
            return;

        case 9:
            clearScreen();
            topkAffectedStationsMenu();
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


void Controller::displayAllStationsMenu() {
    std::cout << "\t\t**Display All Stations**\n\n";
    std::cout << "Name, District, Line\n";

    for (const auto &s : network.getVertexSet()) {
        std::cout << s->getName() << ", " << s->getDistrict() << ", " << s->getLine() << "\n";
    }
    std::cout << std::endl;

    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

void Controller::browseStationMenu() {
    std::cout << "\t\t**Browse Station**\n\n";
    std::string stationName;
    std::cout << "Enter the name of the station: ";
    std::cin >> stationName;

    if(stations.find(stationName) == stations.end()){
        std::cout << "ERROR: Invalid station(s)!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        browseStationMenu();
        return;
    }
    else {
        browseSpecificStationMenu(stationName);
        return;
    }
}

void Controller::browseSpecificStationMenu(const std::string& stationName) {
    auto stationId = stations[stationName];
    auto station = network.findVertex(stationId);

    std::cout << "\t\t**Station**\n\n";
    std::cout << "Name: " << station->getName() << "\n";
    std::cout << "Municipality: " << station->getMunicipality() << "\n";
    std::cout << "District: " << station->getDistrict() << "\n";
    std::cout << "Township: " << station->getTownship() << "\n";
    std::cout << "Line: " << station->getLine() << "\n";

    std::cout << "\n1. Display Connections;\n";
    std::cout << "0. Exit.\n";
    unsigned int option;
    std::cout << "Select an option: ";
    std::cin >> option;
    std::string aux;

    switch (option) {
        case 1:
            clearScreen();
            std::cout << "\t\t**" << station->getName() << "' Connections**\n\n";
            for(auto e: station->getAdj()){
                std::cout << e->getDest()->getName() << " (" << e->getCapacity() << " Trains, " << e->getService() << ")\n";
            }
            std::cout << "\n(Press any key + Enter to continue)\n";
            std::cin >> aux;
            browseSpecificStationMenu(stationName);
            return;

        case 0:
            mainMenu();
            return;

        default:
            std::cout << "ERROR: Invalid option!\n";
            std::cout << "(Press any key + Enter to continue)\n";
            std::cin >> aux;
            browseSpecificStationMenu(stationName);
            return;
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

    double mf = network.edmondsKarp(stations[stationA], stations[stationB]);
    if ( mf == 0 ) std::cout << "There is no path between " << stationA << " and " << stationB << "!\n";
    else std::cout << "Maximum amount of trains between " << stationA << " and " << stationB << ": " << mf << "\n";

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
    std::cout << "Enter the number of stations to display: ";
    std::cin >> k;

    if (std::cin.fail() || k < 0 || k > stations.size()) {
        std::cout << "ERROR: Invalid value for k!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, aux);
        topkTransportNeedsMenu();
        return;
    }

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

void Controller::maxTrainsOneTypeMenu() {
    std::cout << "\t\t**Maximum Amount of Trains that can Simultaneously Travel Between two Stations with Only One Type of Service**\n\n";
    std::string stationA, stationB, service;
    std::cout << "Source station: ";
    std::cin >> stationA;
    std::cout << "Destination station: ";
    std::cin >> stationB;
    std::cout << "Service: ";
    std::cin >> service;
    clearScreen();

    if (stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end()) {
        std::cout << "ERROR: Invalid station(s)!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        maxTrainsOneTypeMenu();
        return;
    }

    if (service!="STANDARD" && service!="ALFA-PENDULAR"){
        std::cout << "ERROR: Invalid service!\n";
        std::cout << "The service must be either STANDARD or ALFA-PENDULAR.\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        maxTrainsOneTypeMenu();
        return;
    }

    double mf = network.edmondsKarpService(stations[stationA], stations[stationB], service);

    if ( mf == 0 )
        std::cout << "There is no path between " << stationA << " and " << stationB << " using only the " << service << " service.\n";
    else
        std::cout << "Maximum amount of trains between " << stationA << " and " << stationB << " using only the " << service << " service: "  << mf << "\n";

    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

void Controller::topkAffectedStationsMenu() {
    std::cout << "\t\t**Top k Affected Stations**\n\n";

    unsigned int k;
    std::cout << "Enter the number of stations to display: ";
    std::cin >> k;

    if (std::cin.fail() || k < 0 || k > stations.size()) {
        std::cout << "ERROR: Invalid value for k!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, aux);
        topkAffectedStationsMenu();
        return;
    }

    std::cout << "\nWhich connection do you want to remove?\n";
    std::string stationA, stationB;
    std::cout << "Station A: ";
    std::cin >> stationA;
    std::cout << "Station B: ";
    std::cin >> stationB;
    clearScreen();

    if (stations.find(stationA) == stations.end() || stations.find(stationB) == stations.end()) {
        std::cout << "ERROR: Invalid station(s)!\n";
        std::cout << "(Press any key + Enter to continue)\n";
        std::string aux;
        std::cin >> aux;
        topkAffectedStationsMenu();
        return;
    }

    std::cout << "\t\t**Top " << k << " Affected Stations**\n\n";
    network.topkAffectedStations(k, stations[stationA], stations[stationB]);

    std::cout << "(Press any key + Enter to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}


