#ifndef PROJETO_CONTROLLER_H
#define PROJETO_CONTROLLER_H

#include "Graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class Controller {
public:

    std::string normalizeCamelCase(const std::string& str);
    void removeWhitespace(std::string& str);
    void replaceWhitespace(std::string& str, char replacement);

    void readStations(const std::string& filename);
    void readNetwork(const std::string& filename);

    void startMenu();
    void mainMenu();

    void maxFlowMenu();
    void maxTrainsNeededMenu();
    void topkTransportNeedsMenu();
    void maxSimultaneousTrainsMenu();
    void maxTrainsMinCostMenu();
    void maxTrainsOneTypeMenu();

private:
    std::unordered_map<std::string, int> stations;
    Graph network;
};


#endif //PROJETO_CONTROLLER_H
