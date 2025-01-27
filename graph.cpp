#include "graph.h"

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight}); // Uncomment for undirected graphs
}

void Graph::removeEdge(int u, int v) {
    adjList[u].remove_if([v](pair<int, int> edge) { return edge.first == v; });
    adjList[v].remove_if([u](pair<int, int> edge) { return edge.first == u; }); // Uncomment for undirected graphs
}

void Graph::displayGraph() {
    for (auto node : adjList) {
        cout << "Node " << node.first << " -> ";
        for (auto neighbor : node.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

vector<int> Graph::dijkstra(int source) {
    unordered_map<int, int> dist;
    for (auto node : adjList) dist[node.first] = numeric_limits<int>::max();

    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // (Distance, Node)
    pq.push({0, source});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int currNode = pq.top().second;
        pq.pop();

        for (auto neighbor : adjList[currNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;

            if (currDist + weight < dist[nextNode]) {
                dist[nextNode] = currDist + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    vector<int> distances;
    for (auto node : dist) {
        distances.push_back(node.second);
    }
    return distances;
}

void Graph::dfs(int start) {
    unordered_map<int, bool> visited;
    stack<int> s;
    s.push(start);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            for (auto neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    s.push(neighbor.first);
                }
            }
        }
    }
    cout << endl;
}

void Graph::bfs(int start) {
    unordered_map<int, bool> visited;
    queue<int> q;
    q.push(start);

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            for (auto neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    q.push(neighbor.first);
                }
            }
        }
    }
    cout << endl;
}

void Graph::exportToFile(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing!" << endl;
        return;
    }

    for (auto node : adjList) {
        file << node.first << ": ";
        for (auto neighbor : node.second) {
            file << "(" << neighbor.first << "," << neighbor.second << ") ";
        }
        file << endl;
    }

    file.close();
    cout << "Graph exported to " << filename << endl;
}

void Graph::importFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading!" << endl;
        return;
    }

    adjList.clear();
    string line;
    while (getline(file, line)) {
        int node;
        size_t colonPos = line.find(':');
        node = stoi(line.substr(0, colonPos));
        string neighbors = line.substr(colonPos + 1);

        size_t start = 0, end = 0;
        while ((end = neighbors.find('(', start)) != string::npos) {
            size_t comma = neighbors.find(',', end);
            size_t close = neighbors.find(')', comma);

            int neighbor = stoi(neighbors.substr(end + 1, comma - end - 1));
            int weight = stoi(neighbors.substr(comma + 1, close - comma - 1));
            adjList[node].push_back({neighbor, weight});

            start = close + 1;
        }
    }

    file.close();
    cout << "Graph imported from " << filename << endl;
}

bool Graph::isCyclicUtil(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &recStack) {
    visited[node] = true;
    recStack[node] = true;

    for (auto neighbor : adjList[node]) {
        if (!visited[neighbor.first] && isCyclicUtil(neighbor.first, visited, recStack)) {
            return true;
        } else if (recStack[neighbor.first]) {
            return true;
        }
    }

    recStack[node] = false;
    return false;
}

bool Graph::isCyclic() {
    unordered_map<int, bool> visited, recStack;

    for (auto node : adjList) {
        if (!visited[node.first]) {
            if (isCyclicUtil(node.first, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::isCyclicUndirectedUtil(int node, unordered_map<int, bool> &visited, int parent) {
    visited[node] = true;

    for (auto neighbor : adjList[node]) {
        if (!visited[neighbor.first]) {
            if (isCyclicUndirectedUtil(neighbor.first, visited, node)) {
                return true;
            }
        } else if (neighbor.first != parent) { // Back edge detected
            return true;
        }
    }

    return false;
}

bool Graph::isCyclicUndirected() {
    unordered_map<int, bool> visited;

    for (auto node : adjList) {
        if (!visited[node.first]) {
            if (isCyclicUndirectedUtil(node.first, visited, -1)) {
                return true;
            }
        }
    }
    return false;
}

