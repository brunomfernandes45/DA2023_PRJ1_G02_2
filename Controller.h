//
// Created by 35191 on 08/03/2023.
//

#ifndef PROJETO_CONTROLLER_H
#define PROJETO_CONTROLLER_H

#include "Graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class Controller {
public:
    void readStations(std::string filename);
    void readNetwork(std::string filename);

    void startMenu();
    void mainMenu();
    
private:
    std::unordered_map<std::string, int> stations;
    Graph network;
};


#endif //PROJETO_CONTROLLER_H
