#include <vector>

#ifndef DA2023_PRJ1_G02_2_GRAPH_H
#define DA2023_PRJ1_G02_2_GRAPH_H

#include "VertexEdge.h"

class Graph {
public:
    // ~Graph();

    ///@brief Returns the number of vertices in the graph.
    ///@return An integer representing the number of vertices in the graph.
    ///@note Time complexity: O(1)
    int getNumVertex() const;

    ///@brief Returns the vector of vertices in the graph.
    ///@return The vector of vertices in the graph.
    ///@note Time complexity: O(1)
    std::vector<Vertex *> getVertexSet() const;

    ///@brief Finds a vertex in the graph with a given ID.
    ///@param id The ID of the vertex to find
    ///@return A pointer to the vertex with the given ID, or nullptr if not found.
    ///@note Time complexity: O(n), where n is the number of vertices in the graph
    Vertex *findVertex(const int &id)const;

    ///@brief Adds a vertex with the given information to the graph.
    ///@param id The id of the station to be added
    ///@param name The name of the station to be added
    ///@param district The district of the station to be added
    ///@param municipality The municipality of the station to be added
    ///@param township The township of the station to be added
    ///@param line The line of the station to be added
    ///@return True if the vertex was successfully added, false otherwise
    ///@note Time complexity: O(1)
    bool addVertex(const int &id, std::string name, std::string district, std::string municipality, std::string township, std::string line);

    bool addEdge(const int &source, const int &dest, double w, std::string s);

    ///@brief Adds a bidirectional edge between two vertices with the given weight and label.
    ///@param source The ID of the source vertex
    ///@param dest The ID of the destination vertex
    ///@param w The weight of the edge
    ///@param s The label (service) of the edge
    ///@return True if the edge was added successfully, false otherwise
    ///@note Time complexity: O(1)
    bool addBidirectionalEdge(const int &source, const int &dest, double w, std::string s);


    ///@brief Implementation of the Edmonds-Karp algorithm to find the maximum flow in a network flow graph.
    ///@param source The ID of the source vertex
    ///@param dest The ID of the destination vertex
    ///@return The maximum flow from the source to the destination.
    ///@note Time complexity: O(V * E^2), where V is the number of vertices and E is the number of edges in the graph
    double edmondsKarp(const int &source, const int &dest);

    ///@brief Breadth-first search algorithm to find a path between two vertices for the Edmonds-Karp algorithm.
    ///@param s The source vertex
    ///@param t The destination vertex
    ///@return True if a path between s and t was found, false otherwise.
    ///@note Time complexity: O(V+E), where V is the number of vertices and E is the number of edges in the graph
    bool bfs_edmondsKarp(Vertex& s, Vertex& t);

    ///@brief Resets the flow of all edges in the graph to zero.
    ///@note Time complexity: O(V+E), where n is the number of vertices and m is the number of edges in the graph
    void resetFlows();

    ///@brief Computes the maximum number of trains needed to transport passengers from any station to any other station.
    ///@return A pair containing the maximum number of trains needed and a vector with pairs of station names.
    ///@note Time complexity: O(V^3 (V + E)), where V is the number of vertices and E is the number of edges in the graph
    std::pair<int, std::vector<std::pair<std::string, std::string>>> maxTrainsNeeded();


    ///@brief Computes and displays the top-k districts and municipalities by transportation needs.
    ///@param k The number of districts and municipalities to display
    ///@note Time complexity: O(VlogV + E), where V is the number of vertices and E is the number of edges in the graph
    void topkTransportNeeds(int k);


    ///@brief Applies Dijkstra's algorithm to find the shortest path between two vertices in the graph.
    ///@param origin The ID of the origin vertex
    ///@param dest The ID of the destination vertex
    ///@return A vector of pointers to the vertices in the shortest path from origin to dest.
    ///@note Time complexity: O((V+E)logV), where V is the number of vertices and E is the number of edges in the graph
    std::vector<Vertex*> dijkstra(const int &origin, const int &dest);

    ///@brief Removes a vertex with the specified ID from the graph, as well as all edges connected to it.
    ///@param id The ID of the vertex to be removed
    ///@return true if a vertex with the specified ID was found and removed, false otherwise.
    ///@note Time complexity: O(V+E), where V is the number of vertices and E is the number of edges in the graph
    bool removeVertex(const int &id);

    ///@brief Calculates the maximum number of trains that can simultaneously arrive at a given station.
    ///@param stationName The name of the target station
    ///@note Time complexity: O(V * E * logV), where V is the number of vertices and E is the number of edges in the graph
    void maxSimultaneousTrains(std::string stationName);


    ///@brief Finds a vertex in the graph given its name.
    ///@param name The name of the vertex to be found
    ///@return A pointer to the vertex if found, or nullptr if not found.
    ///@note Time complexity: O(V), where V is the number of vertices in the graph
    Vertex* findVertexByName(const std::string& name) const;

    ///@brief Computes the maximum number of trains that can travel simultaneously between two given stations with minimum cost.
    ///@param srcName The name of the source station
    ///@param destName The name of the destination station
    ///@return A pair containing the maximum number of trains that can travel simultaneously and the path followed by the trains.
    ///@note Time complexity: O(E log V), where V is the number of vertices and E is the number of edges in the graph.
    void maxTrainsMinCost(const std::string& srcName, const std::string& destName);


    ///@brief Calculates the maximum flow that can be achieved for a specific service between two vertices using the Edmonds-Karp algorithm.
    ///@param source The ID of the source vertex
    ///@param dest The ID of the destination vertex
    ///@param service The service for which the maximum flow will be calculated
    ///@return The maximum flow that can be achieved for the given service between the source and destination vertices.
    ///@note Time complexity: O(E^2 * V), where E is the number of edges and V is the number of vertices in the graph
    double edmondsKarpService(const int &source, const int &dest, std::string service);

    ///@brief Breadth-first search algorithm to find a path between two vertices that satisfies a certain service condition.
    ///@param source The source vertex
    ///@param dest The destination vertex
    ///@param service The service condition that the path must satisfy
    ///@return True if a path between s and t was found that satisfies the service condition, false otherwise.
    ///@note Time complexity: O(V+E), where V is the number of vertices and E is the number of edges in the graph
    bool bfs_service(Vertex& source, Vertex& dest, std::string service);

    void topkAffectedStations(int k);

protected:
    ///@brief A vector of pointers to the vertices of the graph. Each Vertex object represents a station in the railway network.
    std::vector<Vertex *> vertexSet;
    int findVertexIdx(const int &id) const;
};
#endif //DA2023_PRJ1_G02_2_GRAPH_H
