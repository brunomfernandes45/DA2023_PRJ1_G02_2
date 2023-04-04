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

class Vertex: public Station {
public:
    Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

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
    int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, std::string service);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    std::string getService() const;
    bool isReverse() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setIsReverse(bool c);

protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;
    bool isreverse;
    double flow; // for flow-related problems
    std::string service;
};



#endif //DA2023_PRJ1_G02_2_VERTEXEDGE_H
