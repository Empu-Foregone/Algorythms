#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void dijkstra(vector<vector<pair<int, int>>> &graph, int start, int end) {
    int n = graph.size();
    vector<int> dist(n, INF), parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }

    if (dist[end] == INF) {
        cout << "There is no path from node " << start << " to node " << end << "\n";
    } else {
        cout << "Shortest distance from node " << start << " to node " << end << ": " << dist[end] << "\n";
        
        // Output path
        vector<int> path;
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
}

int main() {
    // Example graph
    vector<vector<pair<int, int>>> graph = {
        {},                                  // Node 0 (unused)
        {{2, 8}, {3, 6}, {4, 5}, {5, 5}},    // Node 1
        {{6, 3}, {7, 4}},                    // Node 2
        {{6, 6}, {7, 4}, {8, 5}},            // Node 3
        {{7, 4}, {8, 5}},                    // Node 4
        {{8, 4}},                            // Node 5
        {{9, 6}, {10, 4}},                   // Node 6
        {{9, 7}, {10, 8}, {11, 9}},          // Node 7
        {{10, 8}, {11, 9}, {12, 9}},         // Node 8
        {{13, 9}, {14, 7}},                  // Node 9
        {{13, 4}, {14, 8}, {15, 9}},         // Node 10
        {{14, 9}, {15, 8}},                  // Node 11
        {{15, 9}},                           // Node 12
        {{16, 4}},                           // Node 13
        {{16, 5}},                           // Node 14
        {{16, 7}},                           // Node 15
        {}                                   // Node 16
    };

    dijkstra(graph, 1, 16);

    return 0;
}
