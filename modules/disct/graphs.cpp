/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/*
 * definitions for openGPMP naive implementation of Open Shortest Path First
 * (OSPF)
 */
#include "../../include/disct/graphs.hpp"
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

// gpmp::Graph(int v) : vertices(v), adj_list(v) {
// }

void gpmp::Graph::add_edge(int v, int w, int weight) {
    adj_list[v].emplace_back(w, weight);
    adj_list[w].emplace_back(v, weight); // Uncomment for undirected graph
}

void gpmp::Graph::dfs(int start) {
    std::vector<bool> visited(vertices, false);
    dfs_rec(start, visited);
}

void gpmp::Graph::dfs_rec(int v, std::vector<bool> &visited) {
    visited[v] = true;
    std::cout << v << " ";

    for (const auto &neighbor : adj_list[v]) {
        if (!visited[neighbor.first]) {
            dfs_rec(neighbor.first, visited);
        }
    }
}

void gpmp::Graph::bfs(int start) {
    std::vector<bool> visited(vertices, false);
    std::queue<int> bfsQueue;

    visited[start] = true;
    bfsQueue.push(start);

    while (!bfsQueue.empty()) {
        int v = bfsQueue.front();
        bfsQueue.pop();
        std::cout << v << " ";

        for (const auto &neighbor : adj_list[v]) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                bfsQueue.push(neighbor.first);
            }
        }
    }
}

void gpmp::Graph::dijkstra(int start) {
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    std::vector<int> dist(vertices, std::numeric_limits<int>::max());

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto &neighbor : adj_list[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    std::cout << "Dijkstra's Shortest Paths from vertex " << start << ":\n";
    for (int i = 0; i < vertices; ++i)
        std::cout << "Vertex " << i << ": " << dist[i] << "\n";
}

void gpmp::Graph::bellman_ford(int start) {
    std::vector<int> dist(vertices, std::numeric_limits<int>::max());
    dist[start] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        for (int u = 0; u < vertices; ++u) {
            for (const auto &neighbor : adj_list[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] != std::numeric_limits<int>::max() &&
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    std::cout << "Bellman-Ford Shortest Paths from vertex " << start << ":\n";
    for (int i = 0; i < vertices; ++i)
        std::cout << "Vertex " << i << ": " << dist[i] << "\n";
}

std::vector<std::pair<int, std::pair<int, int>>> gpmp::Graph::kruskal() {
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    for (int u = 0; u < vertices; ++u) {
        for (const auto &neighbor : adj_list[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            edges.emplace_back(weight, std::make_pair(u, v));
        }
    }

    std::sort(edges.begin(), edges.end());

    std::vector<std::pair<int, std::pair<int, int>>> min_span_tree;
    std::vector<int> parent(vertices, -1);

    for (const auto &edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;

        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) {
            min_span_tree.push_back(edge);
            union_sets(parent, setU, setV);
        }
    }

    return min_span_tree;
}

void gpmp::Graph::floyd_warshall() {
    std::vector<std::vector<int>> dist(
        vertices,
        std::vector<int>(vertices, std::numeric_limits<int>::max()));

    for (int i = 0; i < vertices; ++i) {
        dist[i][i] = 0;
        for (const auto &neighbor : adj_list[i]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            dist[i][v] = weight;
        }
    }

    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dist[i][k] != std::numeric_limits<int>::max() &&
                    dist[k][j] != std::numeric_limits<int>::max() &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    std::cout << "Floyd-Warshall Shortest Paths:\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            std::cout << "From " << i << " to " << j << ": ";
            if (dist[i][j] == std::numeric_limits<int>::max())
                std::cout << "INF";
            else
                std::cout << dist[i][j];
            std::cout << "\n";
        }
    }
}

void gpmp::Graph::topo_sort() {
    std::stack<int> topo_stack;
    std::vector<bool> visited(vertices, false);

    for (int i = 0; i < vertices; ++i) {
        if (!visited[i]) {
            topo_sort_util(i, visited, topo_stack);
        }
    }

    std::cout << "Topological Sorting: ";
    while (!topo_stack.empty()) {
        std::cout << topo_stack.top() << " ";
        topo_stack.pop();
    }
    std::cout << std::endl;
}

void gpmp::Graph::topo_sort_util(int v,
                                 std::vector<bool> &visited,
                                 std::stack<int> &topo_stack) {
    visited[v] = true;

    for (const auto &neighbor : adj_list[v]) {
        int u = neighbor.first;
        if (!visited[u]) {
            topo_sort_util(u, visited, topo_stack);
        }
    }

    topo_stack.push(v);
}

int gpmp::Graph::find(std::vector<int> &parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void gpmp::Graph::union_sets(std::vector<int> &parent, int x, int y) {
    int setX = find(parent, x);
    int setY = find(parent, y);
    parent[setX] = setY;
}
