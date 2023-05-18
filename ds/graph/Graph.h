#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjacencyMatrix;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int source, int target, int weight) {
        adjacencyMatrix[source][target] = weight;
        adjacencyMatrix[target][source] = weight;
    }

    int getWeight(int source, int target) {
        return adjacencyMatrix[source][target];
    }

    int getNumVertices() {
        return numVertices;
    }
};
