#include"Graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

void BFS(Graph g, int start) {
    vector<bool> visited(g.getNumVertices(), false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        cout << cur << " ";

        for (int i = 0; i < g.getNumVertices(); i++) {
            if (g.getWeight(cur, i) && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void DFS(Graph g, int start) {
    vector<bool> visited(g.getNumVertices(), false);
    stack<int> s;

    visited[start] = true;
    s.push(start);

    while (!s.empty()) {
        int cur = s.top();
        s.pop();

        cout << cur << " ";

        for (int i = 0; i < g.getNumVertices(); i++) {
            if (g.getWeight(cur, i) && !visited[i]) {
                visited[i] = true;
                s.push(i);
            }
        }
    }
}
