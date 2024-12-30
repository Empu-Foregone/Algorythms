#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

const int INF = 1e9;

// Реалізація алгоритму Пріма
void prim(vector<vector<pair<int, int>>> &graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF), parent(n, -1);
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && dist[v] > weight) {
                dist[v] = weight;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Prim's MST:\n";
    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1)
            cout << parent[i] << " - " << i << "\n";
    }
}

// Структура для ребра графа
struct Edge {
    int u, v, weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

// Алгоритм Крускала
int find_set(int v, vector<int> &parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_sets(int a, int b, vector<int> &parent, vector<int> &rank) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

void kruskal(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());
    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    cout << "Kruskal's MST:\n";
    for (auto &edge : edges) {
        if (find_set(edge.u, parent) != find_set(edge.v, parent)) {
            cout << edge.u << " - " << edge.v << "\n";
            union_sets(edge.u, edge.v, parent, rank);
        }
    }
}

// Основна функція
int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 11}, {2, 7}, {3, 8}},          // Вершина 0
        {{0, 11}, {2, 4}, {4, 3}},          // Вершина 1
        {{0, 7}, {1, 4}, {3, 5}, {5, 8}},   // Вершина 2
        {{0, 8}, {2, 5}, {6, 4}},           // Вершина 3
        {{1, 3}, {5, 2}},                   // Вершина 4
        {{2, 8}, {4, 2}, {6, 9}},           // Вершина 5
        {{3, 4}, {5, 9}, {7, 5}},           // Вершина 6
        {{6, 5}}                            // Вершина 7
    };

    vector<Edge> edges = {
        {0, 1, 11}, {0, 2, 7}, {0, 3, 8}, {1, 2, 4},
        {1, 4, 3}, {2, 3, 5}, {2, 5, 8}, {3, 6, 4},
        {4, 5, 2}, {5, 6, 9}, {6, 7, 5}
    };

    auto start = high_resolution_clock::now();
    prim(graph, 0);
    auto end = high_resolution_clock::now();
    cout << "Time taken by Prim: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    kruskal(graph.size(), edges);
    end = high_resolution_clock::now();
    cout << "Time taken by Kruskal: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";

    return 0;
}
