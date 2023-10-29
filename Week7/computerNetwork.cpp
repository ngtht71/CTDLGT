
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, d;
    Edge (int u_, int v_, int d_) {
        u = u_;
        v = v_;
        d = d_;
    }

    bool operator < (const Edge &other) const {
        return d < other.d;
    }

    void print() {
        cout << u << " " << v << " " << d << endl;
    }
};

struct DSU {
    vector<int> parent;

    void init(int n) {
        parent.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        parent[v] = u;
        return true;
    }
} dsu;

int n, m, totalWeight = 0;
vector <Edge> edges;
vector <Edge> spanningTree;

void Kruskal(){
    dsu.init(n);

    sort (edges.begin(), edges.end());

    // Duyệt qua các cạnh theo thứ tự đã sắp xếp
    for (auto e : edges) {
        if (!dsu.join(e.u, e.v)) continue;
        spanningTree.push_back(e);
        totalWeight += e.d;
    }
    cout << totalWeight << endl;
    for (Edge e : spanningTree)
        e.print();
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        edges.push_back({u, v, d});
    }
    Kruskal();
}
