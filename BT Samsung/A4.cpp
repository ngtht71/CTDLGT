#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isBipartite(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> colors(n, 0);  // 0: not colored, 1: color 1, 2: color 2
    queue<int> q;

    colors[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (colors[v] == 0) {
                colors[v] = (colors[u] == 1) ? 2 : 1;
                q.push(v);
            } else if (colors[v] == colors[u]) {
                return false;  // Two adjacent vertices have the same color, not bipartite
            }
        }
    }

    return true;
}

bool isBipartiteGraph(vector<vector<int>>& graph) {
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
        if (!isBipartite(graph, i)) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};  // Example bipartite graph

    if (isBipartiteGraph(graph)) {
        cout << "The graph is bipartite." << endl;
    } else {
        cout << "The graph is not bipartite." << endl;
    }

    return 0;
}

