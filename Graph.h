//
// Created by 35191 on 09/03/2023.
//
#include <vector>

#ifndef DA2023_PRJ1_G02_2_GRAPH_H
#define DA2023_PRJ1_G02_2_GRAPH_H

#include "VertexEdge.h"

class Graph {
    // ~Graph();

    Vertex *findVertex(const int &id)const;

    bool addVertex(const int &id);

    bool addEdge(const int &sourc, const int &dest, double w);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

protected:
    std::vector<Vertex *> vertexSet;

    int findVertexIdx(const int &id) const;
};
#endif //DA2023_PRJ1_G02_2_GRAPH_H
