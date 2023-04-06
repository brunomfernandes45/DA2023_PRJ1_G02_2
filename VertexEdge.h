#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

#ifndef DA2023_PRJ1_G02_2_VERTEXEDGE_H
#define DA2023_PRJ1_G02_2_VERTEXEDGE_H

#include "Station.h"
#define INF std::numeric_limits<double>::max()

class Edge;

class Vertex: public Station{
public:
    ///@brief A station in the network.
    ///@param id The id of the station
    ///@param name The name of the station
    ///@param district The district of the station
    ///@param municipality The municipality of the station
    ///@param township The township of the station
    ///@param line The line of the station
    Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line);
    bool operator<(Vertex & vertex) const;

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);

    Edge * addEdge(Vertex *dest, double w, std::string s);
    bool removeEdge(int destID);

    friend class MutablePriorityQueue<Vertex>;

protected:
    int id;
    std::vector<Edge *> adj;
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Edge *path = nullptr;
    std::vector<Edge *> incoming;
    int queueIndex = 0;

};

/********************** Edge  ****************************/

class Edge {
public:
    ///@brief Line between two stations.
    ///@param orig The station of the origin
    ///@param dest The station of destination
    ///@param w The capacity (weight) of the edge
    ///@param service The service type of the line
    Edge(Vertex *orig, Vertex *dest, double w, std::string service);

    Vertex * getDest() const;
    double getCapacity() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    std::string getService() const;
    bool isReverse() const;
    int getCost() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setIsReverse(bool c);

protected:
    Vertex * dest;
    double capacity;
    bool selected = false;
    Vertex *orig;
    Edge *reverse = nullptr;
    bool isreverse;
    double flow;
    std::string service;
    int cost;
};


#endif //DA2023_PRJ1_G02_2_VERTEXEDGE_H
