#ifndef PROJETO_CONTROLLER_H
#define PROJETO_CONTROLLER_H

#include "Graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class Controller {
public:
    ///@brief This function normalizes a string in camel case by inserting spaces before each uppercase letter, except for the first letter.
    ///@param str The camel case string to normalize
    ///@return The normalized string with spaces between words.
    ///@note Time complexity: O(n), where n is the length of the input string.
    static std::string normalizeCamelCase(const std::string& str);

    ///@brief Removes whitespace and accents from a string
    ///@param str The string to modify
    ///@note Time complexity: O(n), where n is the length of the input string
    static void removeWhitespaceAndAccents(std::string& str);

    ///@brief Replaces all whitespace characters in a string with a given character.
    ///@param str The input string to modify
    ///@param replacement The replacement character to use
    ///@note Time complexity: O(n), where n is the length of the input string
    static void replaceWhitespace(std::string& str, char replacement);


    ///@brief This function reads a CSV file with information about railway stations and populates the 'stations' and 'network' data structures.
    ///@param filename The name of the CSV file to read
    ///@note Time complexity: O(n), where n is the number of stations in the input file
    void readStations(const std::string& filename);

    ///@brief This function reads a CSV file with information about railway connections between stations and populates the 'network' data structure.
    ///@param filename The name of the CSV file to read
    ///@note Time complexity: O(n), where n is the number of lines in the input file
    void readNetwork(const std::string& filename);


    ///@brief Displays the start menu and allows the user to select an option to read files (either read the standard files, other files or the demo files).
    void startMenu();

    ///@brief Displays the main menu of the program and allows the user to select an option to execute a specific functionality.
    void mainMenu();


    ///@brief Displays the name, district and line of all the stations in the network.
    ///@note Time complexity: O(V), where V is the number of vertices (stations) in the network
    void displayAllStationsMenu();

    ///@brief Asks the user to input the name of a station and checks if it is a valid station in the network.
    /// If the station is not valid, prints an error message and returns to the browse station menu.
    /// If the station is valid, calls browseSpecificStationMenu function with the station name as a parameter.
    ///@note Time complexity: O(V), where V is the number of vertices in the network
    void browseStationMenu();

    ///@brief Displays the name, municipality, district, township, and line o a specific station in the network.
    ///@param stationName The name of the station to browse
    ///@note Time complexity: O(V + E), where V is the number of vertices in the network and E is the number of edges in the network
    void browseSpecificStationMenu(const std::string& stationName);

    ///@brief Prompts the user for two station names and calculates the maximum amount of trains that can travel between them using the Edmonds-Karp algorithm.
    ///@note Time complexity: O(V * E^2), where E is the number of edges and V is the number of vertices in the network
    void maxFlowMenu();

    ///@brief Displays the pairs of stations that require the most amount of trains to be scheduled between them
    ///@note Time complexity: O(V^3 (V + E)), where V is the number of vertices and E is the number of edges in the graph
    void maxTrainsNeededMenu();

    ///@brief Displays the top-k municipalities and districts with the highest transportation needs in the network
    ///@note Time complexity: O(VlogV + E), where V is the number of vertices and E is the number of edges in the graph
    void topkTransportNeedsMenu();

    ///@brief Prompts the user to enter the name of a railway station and calculates the maximum number of trains that can simultaneously arrive at that station.
    ///@note Time complexity: O(V * E * logV), where V is the number of vertices and E is the number of edges in the graph
    void maxSimultaneousTrainsMenu();

    ///@brief Prompts the user to input the source and destination stations for finding the maximum amount of trains that can simultaneously travel between the two with minimum cost.
    ///@note Time complexity: O(E log V), where V is the number of vertices and E is the number of edges in the graph
    void maxTrainsMinCostMenu();

    ///@brief Prompts the user to input the source and destination stations and a service type, and finds the maximum amount of trains that can simultaneously travel between the two stations with only the specified service type.
    ///@note Time complexity: O(E^2 * V), where E is the number of edges and V is the number of vertices in the graph
    void maxTrainsOneTypeMenu();

    ///@brief Displays the top-k most affected stations for a segment defined by two stations.
    ///@note Time complexity: O(V^2 * E^2), where V is the number of vertices and E is the number of edges in the graph
    void topkAffectedStationsMenu();

private:
    ///@brief Unordered map that stores the stations' names and their corresponding indices.
    std::unordered_map<std::string, int> stations;
    ///@brief The graph object that stores all the data regarding the transportation network.
    Graph network;
};


#endif //PROJETO_CONTROLLER_H
