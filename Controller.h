//
// Created by 35191 on 08/03/2023.
//

#ifndef PROJETO_CONTROLLER_H
#define PROJETO_CONTROLLER_H

#include <vector>
#include <unordered_set>
#include <string>

class Controller {
public:

    //readers
    void readStations(std::string filename);
    //void readNetwork(std::string filename);

    //Menus
    void startMenu();
    //void mainMenu();
private:
    std::unordered_set<std::string> stations;
};


#endif //PROJETO_CONTROLLER_H
