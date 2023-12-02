#include <iostream>
#include <vector>
#include <set>

using namespace std;

int countParallelEdges(const vector<pair<int, int>>& edges) {
    set<pair<int, int>> edgeSet;
    int parallelEdge = 0;

    for (const auto& edge : edges) {
        // Sort the pair of vertices to handle both (u, v) and (v, u)
        pair<int, int> sortedEdge = (edge.first < edge.second) ? edge : make_pair(edge.second, edge.first);

        if (edgeSet.find(sortedEdge) != edgeSet.end()) {
            ++parallelEdge;
        } else {
            // Add the edge to the set
            edgeSet.insert(sortedEdge);
        }
    }

    return parallelEdge;
}

int main() {
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 0}, {2, 0}, {2, 3}};

    int parallelEdge = countParallelEdges(edges);

    cout << "Number of parallel edges: " << parallelEdge << endl;

    return 0;
}
