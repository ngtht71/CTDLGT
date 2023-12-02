#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    bool isEulerianCycle() {
        for (int i = 0; i < V; i++)
            if (adj[i].size() % 2 != 0)
                return false;
        return true;
    }

    bool isConnected() {
        vector<bool> visited(V, false);

        // Find a vertex with non-zero degree
        int i;
        for (i = 0; i < V; i++)
            if (adj[i].size() != 0)
                break;

        // If there are no edges in the graph, it's connected.
        if (i == V)
            return true;

        // Start DFS traversal from a vertex with non-zero degree
        DFSUtil(i, visited);

        // Check if all non-zero degree vertices are visited
        for (i = 0; i < V; i++)
            if (!visited[i] && adj[i].size() > 0)
                return false;

        return true;
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;

        for (int i : adj[v])
            if (!visited[i])
                DFSUtil(i, visited);
    }

    bool isHamiltonianCycle() {
        vector<int> path(V, -1);

        // Start from the first vertex
        path[0] = 0;

        if (!isHamiltonianUtil(path, 1))
            return false;

        return true;
    }

    bool isHamiltonianUtil(vector<int>& path, int pos) {
        if (pos == V) {
            // Check if the last vertex is connected to the first vertex
            if (find(adj[path[pos - 1]].begin(), adj[path[pos - 1]].end(), path[0]) != adj[path[pos - 1]].end())
                return true;
            else
                return false;
        }

        for (int v = 1; v < V; v++) {
            if (isSafe(v, pos, path)) {
                path[pos] = v;

                if (isHamiltonianUtil(path, pos + 1))
                    return true;

                path[pos] = -1;
            }
        }

        return false;
    }

    bool isSafe(int v, int pos, const vector<int>& path) {
        // Check if this vertex is an adjacent vertex of the previously added vertex
        if (find(adj[path[pos - 1]].begin(), adj[path[pos - 1]].end(), v) == adj[path[pos - 1]].end())
            return false;

        // Check if the vertex has already been included
        if (find(path.begin(), path.end(), v) != path.end())
            return false;

        return true;
    }
};

int main() {
    // Example 1
    Graph g1(10);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(0, 3);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 5);
    g1.addEdge(2, 9);
    g1.addEdge(3, 6);
    g1.addEdge(4, 7);
    g1.addEdge(4, 8);
    g1.addEdge(5, 8);
    g1.addEdge(5, 9);
    g1.addEdge(6, 7);
    g1.addEdge(6, 9);
    g1.addEdge(7, 8);

    if (g1.isEulerianCycle())
        cout << "Graph 1 has an Eulerian cycle." << endl;
    else
        cout << "Graph 1 does not have an Eulerian cycle." << endl;

    if (g1.isHamiltonianCycle())
        cout << "Graph 1 has a Hamiltonian cycle." << endl;
    else
        cout << "Graph 1 does not have a Hamiltonian cycle." << endl;

    // Example 2
    Graph g2(10);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 3);
    g2.addEdge(0, 3);
    g2.addEdge(2, 5);
    g2.addEdge(5, 6);
    g2.addEdge(3, 6);
    g2.addEdge(4, 7);
    g2.addEdge(4, 8);
    g2.addEdge(5, 8);
    g2.addEdge(5, 9);
    g2.addEdge(6, 7);
    g2.addEdge(6, 9);
    g2.addEdge(8, 8);

    if (g2.isEulerianCycle())
        cout << "Graph 2 has an Eulerian cycle." << endl;
    else
        cout << "Graph 2 does not have an Eulerian cycle." << endl;

    if (g2.isHamiltonianCycle())
        cout << "Graph 2 has a Hamiltonian cycle." << endl;
    else
        cout << "Graph 2 does not have a Hamiltonian cycle." << endl;

    // Example 3
    Graph g3(10);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(1, 3);
    g3.addEdge(0, 3);
    g3.addEdge(0, 4);
    g3.addEdge(2, 5);
    g3.addEdge(2, 9);
    g3.addEdge(3, 6);
    g3.addEdge(4, 7);
    g3.addEdge(4, 8);
    g3.addEdge(5, 8);
    g3.addEdge(5, 9);
    g3.addEdge(6, 7);
    g3.addEdge(6, 9);
    g3.addEdge(7, 8);

    if (g3.isEulerianCycle())
        cout << "Graph 3 has an Eulerian cycle." << endl;
    else
        cout << "Graph 3 does not have an Eulerian cycle." << endl;

    if (g3.isHamiltonianCycle())
        cout << "Graph 3 has a Hamiltonian cycle." << endl;
    else
        cout << "Graph 3 does not have a Hamiltonian cycle." << endl;

    // Example 4
    Graph g4(10);
    g4.addEdge(4, 1);
    g4.addEdge(7, 9);
    g4.addEdge(6, 2);
    g4.addEdge(7, 3);
    g4.addEdge(5, 0);
    g4.addEdge(0, 2);
    g4.addEdge(0, 8);
    g4.addEdge(1, 6);
    g4.addEdge(3, 9);
    g4.addEdge(6, 3);
    g4.addEdge(2, 8);
    g4.addEdge(1, 5);
    g4.addEdge(9, 8);
    g4.addEdge(4, 5);
    g4.addEdge(4, 7);

    if (g4.isEulerianCycle())
        cout << "Graph 4 has an Eulerian cycle." << endl;
    else
        cout << "Graph 4 does not have an Eulerian cycle." << endl;

    if (g4.isHamiltonianCycle())
        cout << "Graph 4 has a Hamiltonian cycle." << endl;
    else
        cout << "Graph 4 does not have a Hamiltonian cycle." << endl;

    return 0;
}

