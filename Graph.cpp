//
// Created by 35191 on 09/03/2023.
//

#include "Graph.h"
#include <unordered_map>

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id, std::string name, std::string district, std::string municipality, std::string township, std::string line) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, name, district, municipality, township, line));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &source, const int &dest, double w) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    for (auto edge : v1 -> getAdj()) {
        if (edge -> getDest() -> getId() == v2 -> getId())
            return false;
    }
    v1 -> addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &source, const int &dest, double w) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

int Graph::edmondsKarp(const int &source, const int &dest) {
    auto s = findVertex(source);
    auto t = findVertex(dest);
    if (s == nullptr || t == nullptr)
        return -1;

    int flow = 0;

    while (true) {
        std::queue<Vertex *> q;
        q.push(s);

        std::unordered_map<Vertex *, Edge *> path;
        path[s] = nullptr;

        while (!q.empty()) {
            auto v = q.front();
            q.pop();

            for (auto edge : v -> getAdj()) {
                auto w = edge -> getDest();
                if (path.find(w) == path.end() && edge -> getFlow() < edge -> getWeight()) {
                    path[w] = edge;
                    q.push(w);
                }
            }
        }
        if (!path.count(t))
            break;

        double bottleneck = INT_MAX;

        for (auto v = t; v != s; v = path[v] -> getOrig()) {
            auto edge = path[v];
            bottleneck = std::min(bottleneck, edge -> getWeight() - edge -> getFlow());
        }

        for (auto v = t; v != s; v = path[v] -> getOrig()) {
            auto edge = path[v];
            edge -> setFlow(edge -> getFlow() + bottleneck);
            edge -> getReverse() -> setFlow(edge -> getReverse() -> getFlow() - bottleneck);
        }
        flow += bottleneck;
    }

    return flow;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

/*
Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
