#ifndef PROJETO_CONTROLLER_H
#define PROJETO_CONTROLLER_H

#include "Graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class Controller {
public:
    void readStations(const std::string& filename);
    void readNetwork(const std::string& filename);

    void startMenu();
    void mainMenu();
    void maxFlowMenu();
    
private:
    std::unordered_map<std::string, int> stations;
    Graph network;
};


#endif //PROJETO_CONTROLLER_H
