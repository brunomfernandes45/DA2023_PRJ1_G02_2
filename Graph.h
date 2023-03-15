//
// Created by 35191 on 09/03/2023.
//

#ifndef DA2023_PRJ1_G02_2_GRAPH_H
#define DA2023_PRJ1_G02_2_GRAPH_H
#include <vector>
class Edge{

private:
unsigned int origin;
unsigned int target;
unsigned int weight;
unsigned int flow;
};


class Vertex{

private:
    unsigned int id;
    std::vector<Edge> adj;
};

class Graph {

private:
    std::vector<Vertex> vertexSet;

};
#endif //DA2023_PRJ1_G02_2_GRAPH_H
