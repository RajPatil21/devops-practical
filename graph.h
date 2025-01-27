#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;

class Graph {
private:
    unordered_map<int, list<pair<int, int>>> adjList; // Node -> [(Neighbor, Weight)]

public:
    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);
    void displayGraph();

    vector<int> dijkstra(int source);
    void dfs(int start);
    void bfs(int start);

    void exportToFile(const string &filename);
    void importFromFile(const string &filename);
};

#endif // GRAPH_H
