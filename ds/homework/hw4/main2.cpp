#include <iostream>
#include <limits>
#include <vector>
#include"../../graph/Graph.h"
using namespace std;

int findMinVertex(vector<int> distances, vector<bool> visited) {
    int minVertex = -1;
    for (int i = 0; i < distances.size(); i++) {
        if (!visited[i] && (minVertex == -1 || distances[i] < distances[minVertex])) {
            minVertex = i;
        }
    }
    return minVertex;
}

void dijkstra(Graph g, int start, vector<int>& distances) {
    vector<bool> visited(g.getNumVertices(), false);
    distances.resize(g.getNumVertices());
    fill(distances.begin(), distances.end(), numeric_limits<int>::max());
    distances[start] = 0;

    for (int i = 0; i < g.getNumVertices() - 1; i++) {
        int cur = findMinVertex(distances, visited);
        visited[cur] = true;

        for (int j = 0; j < g.getNumVertices(); j++) {
            if (g.getWeight(cur, j) && !visited[j]) {
                int distance = distances[cur] + g.getWeight(cur, j);
                if (distance < distances[j]) {
                    distances[j] = distance;
                }
            }
        }
    }
}

int findMinEdge(vector<int> distances, vector<bool> visited) {
    int minEdge = -1;
    for (int i = 0; i < distances.size(); i++) {
        if (!visited[i] && (minEdge == -1 || distances[i] < distances[minEdge])) {
            minEdge = i;
        }
    }
    return minEdge;
}

void prim(Graph g, int start, vector<int>& parent) {
    vector<bool> visited(g.getNumVertices(), false);
    vector<int> distances(g.getNumVertices());
    parent.resize(g.getNumVertices());

    fill(distances.begin(), distances.end(), numeric_limits<int>::max());

    distances[start] = 0;
    parent[start] = -1;

    for (int i = 0; i < g.getNumVertices() - 1; i++) {
        int cur = findMinEdge(distances, visited);
        visited[cur] = true;

        for (int j = 0; j < g.getNumVertices(); j++) {
            if (g.getWeight(cur, j) && !visited[j] && g.getWeight(cur, j) < distances[j]) {
                distances[j] = g.getWeight(cur, j);
                parent[j] = cur;
            }
        }
    }
}
int main() {
    Graph g(6);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 3);

    cout << "Dijkstra's 算法:" << endl;
    vector<int> distances;
    dijkstra(g, 0, distances);
    for (int i = 0; i < distances.size(); i++) {
        cout << "从0--" << i << "的最短距离是：" << distances[i] << endl;
    }
    cout << endl;

    cout << "Prim's 算法:" << endl;
    vector<int> parent;
    prim(g, 0, parent);
    for (int i = 1; i < g.getNumVertices(); i++) {
        cout << parent[i] << " - " << i << endl;
    }

    return 0;
}