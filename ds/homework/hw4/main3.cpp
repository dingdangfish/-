#include <iostream>
#include <queue>
#include <vector>
#include"../../graph/Graph.h"
#include "main2.cpp"
using namespace std;

class Node {
public:
    int vertex;
    int distance;

    Node(int vertex, int distance) {
        this->vertex = vertex;
        this->distance = distance;
    }

    bool operator<(const Node& node) const {
        return distance > node.distance;
    }
};

void dijkstra(Graph g, int start, vector<int>& distances) {
    vector<bool> visited(g.getNumVertices(), false);
    distances.resize(g.getNumVertices());
    fill(distances.begin(), distances.end(), numeric_limits<int>::max());
    distances[start] = 0;

    priority_queue<Node> pq;
    pq.push(Node(start, 0));

    while (!pq.empty()) {
        int cur = pq.top().vertex;
        pq.pop();

        if (!visited[cur]) {
            visited[cur] = true;

            for (int i = 0; i < g.getNumVertices(); i++) {
                if (g.getWeight(cur, i) && !visited[i]) {
                    int distance = distances[cur] + g.getWeight(cur, i);
                    if (distance < distances[i]) {
                        distances[i] = distance;
                        pq.push(Node(i, distance));
                    }
                }
            }
        }
    }
}