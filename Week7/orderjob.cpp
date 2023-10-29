#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int m, n;
vector <int> graph[100000];
vector <int> path;

// order job
void bfs (int x, vector <int> &priority) {
    queue<int> q;
    int n = priority.size() - 1;

    // cho nhung phan tu khong bi phu thuoc vao trc
    for (int i = 1; i <= n; i++)
        if (priority[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        path.push_back(u);
        for (int v : graph[u]){
            priority[v]--;
            if (priority[v] == 0) q.push(v);
        }
    }
}

void dfs (int x, vector<bool>& visited, vector<int>& res) {
    visited[x] = true;

    for (int i : graph[x])
        if (!visited[i])
            dfs(i, visited, res);
    res.push_back(x);
}

void orderJobBFS(vector<int> &priority) {
    for (int i = 1; i <= n; i++)
        if (priority[i] == 0) {
            bfs(i, priority);
            break;
        }

    if (path.size() == n){
        for (int i = 0; i < path.size(); i++)
            cout << path[i] << " ";
        cout << endl;
    }


    else cout << "Can not order jobs." << endl;
}

void orderJobDFS(){
    vector <bool> visited(n, false);
    vector <int> res;

    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs(i, visited, res);

    reverse(res.begin(), res.end());
    for(int i : res) cout << i << " ";
    cout << endl;
}

int main() {
    cin >> n >> m;
    vector <int> priority (n+1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        priority[v]++;
    }

    cout << "Order jobs by Breath First Search:\n";
    orderJobBFS(priority);

    cout << "Order jobs by Deep First Search:\n";
    orderJobDFS();

    return 0;
}
