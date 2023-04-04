#include "Graph.h"
#include "Controller.h"
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
    e1->setIsReverse(false);
    e2->setIsReverse(true);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


void removeWhitespaceAndAccents(std::string& str);


double Graph::edmondsKarp(const int &source, const int &dest) {
    Vertex *s = findVertex(source);
    Vertex *t = findVertex(dest);
    if (s == nullptr || t == nullptr)
        return 0;
    resetFlows();
    double maxFlow = 0;
    while (bfs_edmondsKarp(s, t)) {
        double pathFlow = INF;
        Vertex *v = findVertex(dest);
        while (v->getPath() != nullptr) {
            Edge *e = v->getPath();
            pathFlow = std::min(pathFlow, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        v = findVertex(dest);
        while (v->getPath() != nullptr) {
            Edge *e = v->getPath();
            e->setFlow(e->getFlow() + pathFlow);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - pathFlow);
            v = e->getOrig();
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}


bool Graph::bfs_edmondsKarp(Vertex *s, Vertex *t) {
    for (Vertex *v : vertexSet) {
        v->setVisited(false);
        v->setDist(std::numeric_limits<double>::infinity());
        v->setPath(nullptr);
    }
    s->setVisited(true);
    s->setDist(0);
    std::queue<Vertex*> q;
    q.push(s);
    while (!q.empty()) {
        Vertex* u = q.front();
        q.pop();
        for (Edge* e : u->getAdj()) {
            Vertex* v = e->getDest();
            if (!v->isVisited() && e->getWeight() > e->getFlow()) {
                v->setVisited(true);
                v->setPath(e);
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

void Graph::resetFlows() {
    for (Vertex *v: vertexSet){
        for(Edge *e:v->getAdj()){
            if(e->isReverse()) e->setFlow(e->getWeight());
            else e->setFlow(0);
        }
    }
}



void Graph::maxTrainsNeeded() {
    double maxFlow = 0;
    std::vector<std::pair<std::string, std::string>> maxFlowStations;
    for (Vertex *s : vertexSet) {
        for (Vertex *t : vertexSet) {
            if (s == t) continue;
            double flow = edmondsKarp(s->getId(), t->getId());
            if (flow > maxFlow) {
                maxFlow = flow;
                maxFlowStations.clear();
                maxFlowStations.push_back(std::make_pair(s->getName(), t->getName()));
            } else if (flow == maxFlow) {
                maxFlowStations.push_back(std::make_pair(s->getName(), t->getName()));
            }
        }
    }

    std::cout << "Max flow: " << maxFlow << std::endl;
    std::cout << "Stations with max flow: ";
    for (const auto &p : maxFlowStations) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << std::endl;
}


void Graph::topkTransportNeeds(int k) {
    // Create unordered maps to store the total transportation needs for each district and municipality
    std::unordered_map<std::string, double> districtTransportationNeeds;
    std::unordered_map<std::string, double> municipalityTransportationNeeds;

    // Calculate the total transportation needs for each district and municipality
    for (auto vertex : vertexSet) {
        std::string district = vertex->getDistrict();
        removeWhitespaceAndAccents(district);
        std::string municipality = vertex->getMunicipality();
        removeWhitespaceAndAccents(municipality);
        double weight = 0.0;
        for (auto edge : vertex->getAdj()) {
            weight += edge->getWeight();
        }
        districtTransportationNeeds[district] += weight;
        municipalityTransportationNeeds[municipality] += weight;
    }

    // Sort the maps in descending order of transportation needs
    std::vector<std::pair<std::string, double>> sortedDistricts(districtTransportationNeeds.begin(), districtTransportationNeeds.end());
    std::sort(sortedDistricts.begin(), sortedDistricts.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    std::vector<std::pair<std::string, double>> sortedMunicipalities(municipalityTransportationNeeds.begin(), municipalityTransportationNeeds.end());
    std::sort(sortedMunicipalities.begin(), sortedMunicipalities.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    // Print the top-k districts and municipalities by transportation needs
    std::cout << "Top " << k << " districts by transportation needs:" << std::endl;
    for (int i = 0; i < k && i < sortedDistricts.size(); i++) {
        std::cout << sortedDistricts[i].first << ": " << sortedDistricts[i].second << std::endl;
    }

    std::cout << "Top " << k << " municipalities by transportation needs:" << std::endl;
    for (int i = 0; i < k && i < sortedMunicipalities.size(); i++) {
        std::cout << sortedMunicipalities[i].first << ": " << sortedMunicipalities[i].second << std::endl;
    }
}


void Graph::maxSimultaneousTrains(std::string stationName) {
    int maxTrains = 0;
    for (auto vertex : vertexSet) {
        if (vertex->getName() == stationName) {
            int count = 0;
            for (auto edge : vertex->getAdj()) {
                count += edge->getWeight();
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