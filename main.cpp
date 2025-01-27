#include "graph.h"

int main() {
    Graph g;

    // Adding edges
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 4, 12);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 5, 2);

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
