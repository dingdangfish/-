#include"../../graph/BFS DFS.h"
int main() {
    Graph g(6);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 1);

    cout << "BFS: ";
    BFS(g, 0);
    cout << endl;

    cout << "DFS: ";
    DFS(g, 0);
    cout << endl;

    return 0;
}