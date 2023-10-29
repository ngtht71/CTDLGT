#include <iostream>
#include <vector>

using namespace std;

void dfs (vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    for (int i : graph[node]) {
        if (!visited[i]) dfs(graph, i, visited);
    }
}

int countConnectedComponent (vector<vector<int>>& graph) {
    int n = graph.size();
    vector <bool> visited(n, false);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited);
            count++;
        }
    }
    return count;
}

int main (){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);   // dsach ke
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x-1].push_back(y-1);
        graph[y-1].push_back(x-1);
    }

    cout << countConnectedComponent(graph);
    return 0;
}
