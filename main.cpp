#include "graph.h"

int main() {
    Graph g;

    // Adding edges with different weights
    g.addEdge(1, 2, 7);
    g.addEdge(1, 3, 9);
    g.addEdge(1, 6, 14);
    g.addEdge(2, 3, 10);
    g.addEdge(2, 4, 15);
    g.addEdge(3, 4, 11);
    g.addEdge(3, 6, 2);
    g.addEdge(4, 5, 6);
    g.addEdge(5, 6, 9);

    cout << "Graph Representation:" << endl;
    g.displayGraph();

    cout << "\nDFS starting from node 1:" << endl;
    g.dfs(1);

    cout << "\nBFS starting from node 1:" << endl;
    g.bfs(1);

    cout << "\nShortest distances from node 1 (Dijkstra):" << endl;
    vector<int> distances = g.dijkstra(1);
    for (size_t i = 0; i < distances.size(); i++) {
        cout << "Node " << i + 1 << ": " << distances[i] << endl;
    }

    // Export and Import functionality
    g.exportToFile("graph.txt");
    g.importFromFile("graph.txt");

    return 0;
}
