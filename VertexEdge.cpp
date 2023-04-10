#include "VertexEdge.h"

#include <utility>

Vertex::Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line) : id(id), Station(std::move(name), std::move(district), std::move(municipality), std::move(township), std::move(line)) {}

Edge * Vertex::addEdge(Vertex *d, double w, std::string s) {
    auto newEdge = new Edge(this, d, w, std::move(s));
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true;
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w, std::string s): orig(orig), dest(dest), capacity(w), service(std::move(s)){
    cost = 0;
    if (service == "STANDARD") cost=2;
    else if (service == "ALFA-PENDULAR") cost=4;
}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getCapacity() const {
    return this->capacity;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

double Edge::getFlow() const {
    return flow;
}

std::string Edge::getService() const {
    return this->service;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

void Edge::setIsReverse(bool c) {
    isreverse=c;
}

int Edge::getCost() const {
    return cost;
}
