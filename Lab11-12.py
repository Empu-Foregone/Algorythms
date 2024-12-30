import heapq
import time

def prim_algorithm(graph, start):
    mst = []
    visited = set()
    min_heap = [(0, start, None)]
    total_weight = 0

    while min_heap:
        weight, current_vertex, previous_vertex = heapq.heappop(min_heap)

        if current_vertex in visited:
            continue

        visited.add(current_vertex)
        if previous_vertex is not None:
            mst.append((previous_vertex, current_vertex, weight))
            total_weight += weight

        for neighbor, edge_weight in graph[current_vertex]:
            if neighbor not in visited:
                heapq.heappush(min_heap, (edge_weight, neighbor, current_vertex))

    return mst, total_weight

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)

        if root_u != root_v:
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1

def kruskal_algorithm(graph):
    edges = []
    for u in graph:
        for v, weight in graph[u]:
            edges.append((weight, u, v))
    edges.sort()

    uf = UnionFind(len(graph) + 1)
    mst = []
    total_weight = 0

    for weight, u, v in edges:
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            mst.append((u, v, weight))
            total_weight += weight

    return mst, total_weight

graph = {
    1: [(2, 11), (3, 7)],
    2: [(1, 11), (3, 4), (5, 3)],
    3: [(1, 7), (2, 4), (4, 5), (6, 8)],
    4: [(3, 5), (7, 7)],
    5: [(2, 3), (6, 2), (9, 9)],
    6: [(3, 8), (5, 2), (7, 6), (8, 5)],
    7: [(4, 7), (6, 6), (8, 4)],
    8: [(6, 5), (7, 4), (9, 9), (10, 11)],
    9: [(5, 9), (8, 9), (10, 9)],
    10: [(8, 11), (9, 9)]
}

# Алгоритм Прима
start_time = time.time()
mst_prim, total_weight_prim = prim_algorithm(graph, 1)
end_time = time.time()
prim_duration = end_time - start_time

print("MST Прима:", mst_prim)
print("Загальна вага Прима:", total_weight_prim)
print("Час виконання Прима:", prim_duration)

# Алгоритм Крускала
start_time = time.time()
mst_kruskal, total_weight_kruskal = kruskal_algorithm(graph)
end_time = time.time()
kruskal_duration = end_time - start_time

print("MST Крускала:", mst_kruskal)
print("Загальна вага Крускала:", total_weight_kruskal)
print("Час виконання Крускала:", kruskal_duration)

# Порівняльна таблиця
comparison_table = f"""
| Алгоритм | MST                           | Загальна вага | Час виконання (сек) |
|----------|-------------------------------|---------------|---------------------|
| Прима    | {mst_prim}                    | {total_weight_prim}  | {prim_duration}    |
| Крускала | {mst_kruskal}                 | {total_weight_kruskal} | {kruskal_duration}|
"""

print(comparison_table)
