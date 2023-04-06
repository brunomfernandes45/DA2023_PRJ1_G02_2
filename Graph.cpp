#include "Graph.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <cmath>

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
 * destination vertices and the edge capacity (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &source, const int &dest, double w, std::string s) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    for (auto edge : v1 -> getAdj()) {
        if (edge -> getDest() -> getId() == v2 -> getId())
            return false;
    }
    v1 -> addEdge(v2, w, s);
    return true;
}

bool Graph::addBidirectionalEdge(const int &source, const int &dest, double w, std::string s) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, s);
    auto e2 = v2->addEdge(v1, w, s);
    e1->setIsReverse(false);
    e2->setIsReverse(true);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

double Graph::edmondsKarp(const int& source, const int& dest) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(dest);
    if (s == nullptr || t == nullptr)
        return 0;
    resetFlows();
    double maxFlow = 0;
    while (bfs_edmondsKarp(*s, *t)) {
        double pathFlow = INF;
        Vertex* v = t;
        while (v->getPath() != nullptr) {
            Edge* e = v->getPath();
            pathFlow = std::min(pathFlow, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        v = t;
        while (v->getPath() != nullptr) {
            Edge* e = v->getPath();
            e->setFlow(e->getFlow() + pathFlow);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - pathFlow);
            v = e->getOrig();
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

bool Graph::bfs_edmondsKarp(Vertex& s, Vertex& t) {
    for (Vertex* v : vertexSet) {
        v->setVisited(false);
        v->setDist(std::numeric_limits<double>::infinity());
        v->setPath(nullptr);
    }
    s.setVisited(true);
    s.setDist(0);
    std::deque<Vertex *> q;
    q.push_back(&s);
    while (!q.empty()) {
        Vertex *u = q.front();
        q.pop_front();
        for (Edge *e: u->getAdj()) {
            Vertex *v = e->getDest();
            if (!v->isVisited() && e->getCapacity() > e->getFlow()) {
                v->setVisited(true);
                v->setPath(e);
                if (v == &t) return true;
                q.push_back(v);
            }
        }
    }
    return false;
}

void Graph::resetFlows() {
    for (Vertex *v: vertexSet) {
        for(Edge *e:v->getAdj()) {
            e->setFlow(0);
        }
    }
}



std::pair<int, std::vector<std::pair<std::string, std::string>>> Graph::maxTrainsNeeded() {
    double maxFlow = 0;
    std::unordered_set<int> checkedStations;

    std::vector<std::pair<std::string, std::string>> maxFlowStations;
    for (Vertex *s : vertexSet) {
        for (Vertex *t : vertexSet) {
            if (s == t || checkedStations.find(t -> getId()) != checkedStations.end()) continue;
            double flow = edmondsKarp(s->getId(), t->getId());
            if (flow > maxFlow) {
                maxFlow = flow;
                maxFlowStations.clear();
                maxFlowStations.emplace_back(s->getName(), t->getName());
            } else if (flow == maxFlow) {
                maxFlowStations.emplace_back(s->getName(), t->getName());
            }
        }
        checkedStations.insert(s -> getId());
    }
    return {maxFlow, maxFlowStations};
}


void Graph::topkTransportNeeds(int k) {

    std::unordered_map<std::string, double> districtTransportationNeeds;
    std::unordered_map<std::string, double> municipalityTransportationNeeds;

    for (auto vertex : vertexSet) {
        std::string district = vertex->getDistrict();
        std::string municipality = vertex->getMunicipality();
        double amount = 0.0;
        for (auto edge : vertex->getAdj()) {
            amount += edge->getCost() * edge->getCapacity();
        }
        districtTransportationNeeds[district] += amount;
        municipalityTransportationNeeds[municipality] += amount;
    }

    std::vector<std::pair<std::string, double>> sortedDistricts(districtTransportationNeeds.begin(), districtTransportationNeeds.end());
    std::sort(sortedDistricts.begin(), sortedDistricts.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    std::vector<std::pair<std::string, double>> sortedMunicipalities(municipalityTransportationNeeds.begin(), municipalityTransportationNeeds.end());
    std::sort(sortedMunicipalities.begin(), sortedMunicipalities.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    std::cout << "Top " << k << " districts by transportation needs:" << std::endl;
    for (int i = 0; i < k && i < sortedDistricts.size(); i++) {
        std::cout << sortedDistricts[i].first << ": " << sortedDistricts[i].second << std::endl;
    }

    std::cout << "Top " << k << " municipalities by transportation needs:" << std::endl;
    for (int i = 0; i < k && i < sortedMunicipalities.size(); i++) {
        std::cout << sortedMunicipalities[i].first << ": " << sortedMunicipalities[i].second << std::endl;
    }
}

std::vector<Vertex *> Graph::dijkstra(const int &origin, const int &dest) {
    std::vector<Vertex *> res;
    Vertex *s = findVertex(origin);
    Vertex *t = findVertex(dest);
    if (s == nullptr || t == nullptr)
        return res;
    MutablePriorityQueue<Vertex> q;
    for (Vertex *v : vertexSet) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    s->setDist(0);
    q.insert(s);
    while (!q.empty()) {
        Vertex *v = q.extractMin();
        if (v == t) break;
        for (Edge *e : v->getAdj()) {
            double newDist = v->getDist() + e->getCost();
            if (newDist < e->getDest()->getDist()) {
                e->getDest()->setDist(newDist);
                e->getDest()->setPath(e);
                if (q.inQueue(e->getDest()))
                    q.decreaseKey(e->getDest());
                else
                    q.insert(e->getDest());
            }
        }
    }
    if (t->getPath() == nullptr) return res; // t is not reachable from s
    for (Vertex *v = t; v->getPath() != nullptr; v = v->getPath()->getOrig()) {
        res.push_back(v);
    }
    std::reverse(res.begin(), res.end());
    return res;
}

void Graph::maxSimultaneousTrains(std::string stationName) {
    int maxTrains = 0;
    for (auto vertex : vertexSet) {
        if (vertex->getName() == stationName) {
            int count = 0;
            for (auto edge : vertex->getAdj()) {
                count += edge->getCapacity();
            }
            if (count > maxTrains) {
                maxTrains = count;
            }
        }
    }
    if (maxTrains > 0) {
        std::cout << "Maximum number of trains that can simultaneously arrive at station " << stationName << ": " << maxTrains << std::endl;
    } else {
        std::cout << "Station " << stationName << " does not exist in the railway grid." << std::endl;
    }
}


Vertex* Graph::findVertexByName(const std::string& name) const {
    for (Vertex* v : vertexSet) {
        if (v->getName() == name) {
            return v;
        }
    }
    return nullptr;
}


void Graph::maxTrainsMinCost(const std::string& srcName, const std::string& destName) {
    // Find the source and destination vertices
    Vertex* s = findVertexByName(srcName);
    Vertex* t = findVertexByName(destName);
    if (s == nullptr || t == nullptr) {
        std::cout << "Invalid source or destination station\n";
        return;
    }

    std::vector<Vertex*> path = dijkstra(s -> getId(), t -> getId());
    if (path.empty()) {
        std::cout << "No path found between source and destination stations\n";
        return;
    }

    int max_trains = std::numeric_limits<int>::max();
    double cost = 0;
    for (auto v : path) {
        Edge* e = v->getPath();
        if (e == nullptr) {
            std::cout << "No path found between source and destination stations\n";
            return;
        }
        cost += e->getCost();
        if(e->getCapacity()<max_trains){
            max_trains = e->getCapacity();
        }
    }

    std::cout << "The maximum number of trains that can travel simultaneously between " << srcName << " and " << destName << " is: " << max_trains << std::endl;
    std::cout << "The path is: " << std::endl;
    std::cout << srcName << " -> " << (*path.begin())->getName() << std::endl;
    for(auto it = path.begin(); it != path.end() - 1; it++){
        std::cout << (*it)->getName() << " -> " << (*(it+1))->getName() << std::endl;
    }

    std::cout << "The minimum cost for the company while maintaining the same level of service is: " << (cost*max_trains) << " euros.\n";
}

bool Graph::removeVertex(const int &id) {
    for(std::vector<Vertex*>::iterator v = vertexSet.begin(); v != vertexSet.end(); ++v){
        if((*v)->getId() == id){
            for(Edge *e: (*v)->getAdj()){
                (*v)->removeEdge(e->getDest()->getId());
                e->getDest()->removeEdge((*v)->getId());
            }
            vertexSet.erase(v);
            return true;
        }
    }
    return false;
}

bool Graph::bfs_service(Vertex &s, Vertex &t, std::string service) {
    for (Vertex* v : vertexSet) {
        v->setVisited(false);
        v->setDist(std::numeric_limits<double>::infinity());
        v->setPath(nullptr);
    }
    s.setVisited(true);
    s.setDist(0);
    std::deque<Vertex *> q;
    q.push_back(&s);
    while (!q.empty()) {
        Vertex *u = q.front();
        q.pop_front();
        for (Edge *e: u->getAdj()) {
            Vertex *v = e->getDest();
            if (!v->isVisited() && e->getCapacity() > e->getFlow() && e->getService() == service) {
                v->setVisited(true);
                v->setPath(e);
                if (v == &t) return true;
                q.push_back(v);
            }
        }
    }
    return false;
}

double Graph::edmondsKarpService(const int &source, const int &dest, std::string service) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(dest);
    if (s == nullptr || t == nullptr)
        return 0;
    resetFlows();
    double maxFlow = 0;
    while (bfs_service(*s, *t,service)) {
        double pathFlow = INF;
        Vertex* v = t;
        while (v->getPath() != nullptr) {
            Edge* e = v->getPath();
            pathFlow = std::min(pathFlow, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        v = t;
        while (v->getPath() != nullptr) {
            Edge* e = v->getPath();
            e->setFlow(e->getFlow() + pathFlow);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - pathFlow);
            v = e->getOrig();
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
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
*/