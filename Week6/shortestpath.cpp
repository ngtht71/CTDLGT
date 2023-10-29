#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void FindShortestPath (vector<vector<pair<int, int>>> graph, int src, int dst) {
    int n = graph.size();
    vector <int> dist (n, INT_MAX);
    vector <bool> visited (n, false);

    dist[src] = 0;      //node goc = 0
    while (true) {
        int min_dist_node = -1;     //node ke min
        for (int i = 0; i < n; i++)     // duyet cac dinh chua di qua gan = min_dist_node
            if (!visited[i] && (min_dist_node == -1 || dist[i] < dist[min_dist_node]))
                min_dist_node = i;

        // neu cac node deu da duyet hoac den dinh can xet r thi break
        if (min_dist_node == -1 || min_dist_node == dst) break;

        visited[min_dist_node] = true;      // set dinh da di qua = true

        // xet cac dinh ke voi dinh min_dist_node - dung dsach ke cac dinh
        for (int i = 0; i < graph[min_dist_node].size(); i++){
            int i_dst = graph[min_dist_node][i].first;      //lay ra 1 dinh ke
            int i_weight = graph[min_dist_node][i].second;  //lay ra weight cua dinh ke do
            int new_dist = dist[min_dist_node] + i_weight;  // xet khoang cach tu src den dinh ke
            dist[i_dst] = min(new_dist, dist[i_dst]);       // cap nhat kc ngan nhat
        }
    }

    cout << dist[dst] << endl;
}

int main(){
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;

    vector<vector<pair<int, int>>> graph (n);
    vector <int> dist(n, INT_MAX);
    vector <int> prev(n, -1);       // -1 indicate undefine

    for (int i = 0; i < m; i++) {
        int x, y, weight;
        cin >> x >> y >> weight;
        graph[x-1].push_back(make_pair(y-1, weight));    // weight = 1
    }

    FindShortestPath(graph, X-1, Y-1);

    return 0;
}
