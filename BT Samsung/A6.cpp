#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;
public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void findAndPrintBridges() {
        set<pair<int, int>> bridges;

        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                if (u < v && isBridge(u, v, bridges)) {
                    cout << "Bridge Edge: " << u << " - " << v << endl;
                }
            }
        }
    }

    bool isBridge(int u, int v, set<pair<int, int>>& bridges) {
        removeEdge(u, v);
        vector<bool> visited(V, false);

        int startVertex = 0;
        dfs(startVertex, visited);

        addEdge(u, v);
        for (bool status : visited)
            if (!status)
                return bridges.insert(make_pair(u, v)).second;


        return false; // Cạnh (u, v) không là cầu
    }

    void dfs(int u, vector<bool>& visited) {
        visited[u] = true;

        for (int v : adjList[u]) {
            if (!visited[v]) {
                dfs(v, visited);
            }
        }
    }

    void removeEdge(int u, int v) {
        auto it = find(adjList[u].begin(), adjList[u].end(), v);
        if (it != adjList[u].end()) {
            adjList[u].erase(it);
        }

        it = find(adjList[v].begin(), adjList[v].end(), u);
        if (it != adjList[v].end()) {
            adjList[v].erase(it);
        }
    }
};

int main() {
    Graph graph(5);

    // Thêm cạnh vào đồ thị
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Kiểm tra và in cầu
    graph.findAndPrintBridges();

    return 0;
}
