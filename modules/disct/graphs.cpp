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
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <stack>
#include <vector>

void gpmp::Graph::add_edge(int v, int w, int weight) {
    adj_list[v].emplace_back(w, weight);
    adj_list[w].emplace_back(v, weight); // uncomment for undirected graph
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
    std::queue<int> bfs_queue;

    visited[start] = true;
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        int v = bfs_queue.front();
        bfs_queue.pop();
        std::cout << v << " ";

        for (const auto &neighbor : adj_list[v]) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                bfs_queue.push(neighbor.first);
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

std::vector<std::vector<int>> gpmp::Graph::connected_components() {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(vertices, false);

    for (int v = 0; v < vertices; ++v) {
        if (!visited[v]) {
            std::vector<int> component;
            dfs_connected_components(v, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

bool gpmp::Graph::is_bipartite() {
    std::vector<int> color(vertices, -1);
    std::queue<int> bfs_queue;

    for (int start = 0; start < vertices; ++start) {
        if (color[start] == -1) {
            color[start] = 0;
            bfs_queue.push(start);

            while (!bfs_queue.empty()) {
                int v = bfs_queue.front();
                bfs_queue.pop();

                for (const auto &neighbor : adj_list[v]) {
                    int u = neighbor.first;
                    if (color[u] == -1) {
                        color[u] = 1 - color[v];
                        bfs_queue.push(u);
                    } else if (color[u] == color[v]) {
                        return false; // Not bipartite
                    }
                }
            }
        }
    }

    return true; // Bipartite
}

std::vector<double> gpmp::Graph::betweenness_centrality() {
    std::vector<double> centrality(vertices, 0.0);

    for (int s = 0; s < vertices; ++s) {
        std::vector<int> predecessors(vertices, -1);
        std::vector<int> distance(vertices, -1);
        std::vector<int> num_shortest_paths(vertices, 0);
        std::stack<int> stack;
        std::queue<int> bfs_queue;

        distance[s] = 0;
        num_shortest_paths[s] = 1;
        bfs_queue.push(s);

        while (!bfs_queue.empty()) {
            int v = bfs_queue.front();
            bfs_queue.pop();
            stack.push(v);

            for (const auto &neighbor : adj_list[v]) {
                int w = neighbor.first;
                if (distance[w] == -1) {
                    distance[w] = distance[v] + 1;
                    bfs_queue.push(w);
                }

                if (distance[w] == distance[v] + 1) {
                    num_shortest_paths[w] += num_shortest_paths[v];
                    predecessors[w] = v;
                }
            }
        }

        std::vector<double> dependency(vertices, 0.0);

        while (!stack.empty()) {
            int w = stack.top();
            stack.pop();

            for (const auto &predecessor : adj_list[w]) {
                int v = predecessor.first;
                dependency[v] += (static_cast<double>(num_shortest_paths[v]) /
                                  num_shortest_paths[w]) *
                                 (1 + dependency[w]);
            }

            if (w != s) {
                centrality[w] += dependency[w];
            }
        }
    }

    return centrality;
}

void gpmp::Graph::dfs_connected_components(int v,
                                           std::vector<bool> &visited,
                                           std::vector<int> &component) {
    visited[v] = true;
    component.push_back(v);

    for (const auto &neighbor : adj_list[v]) {
        int u = neighbor.first;
        if (!visited[u]) {
            dfs_connected_components(u, visited, component);
        }
    }
}

bool gpmp::Graph::has_hamiltonian_circuit() {
    std::vector<int> path;
    std::vector<bool> visited(vertices, false);

    for (int v = 0; v < vertices; ++v) {
        path.clear();
        if (hamiltonian_circuit_util(v, visited, path, 1)) {
            return true;
        }
    }

    return false;
}

bool gpmp::Graph::has_eulerian_path() {
    // A connected graph has an Eulerian path if and only if it has exactly 0 or
    // 2 vertices with an odd degree.
    int odd_degrees = 0;

    for (int v = 0; v < vertices; ++v) {
        if (adj_list[v].size() % 2 != 0) {
            ++odd_degrees;
        }
    }

    return odd_degrees == 0 || odd_degrees == 2;
}

bool gpmp::Graph::hamiltonian_circuit_util(int v,
                                           std::vector<bool> &visited,
                                           std::vector<int> &path,
                                           int count) {
    visited[v] = true;
    path.push_back(v);

    if (count == vertices) {
        // all vertices are visited; check if there is an edge from the last
        // added vertex to the starting vertex
        for (const auto &neighbor : adj_list[v]) {
            if (neighbor.first == path[0]) {
                return true; // Hamiltonian circuit found
            }
        }
    } else {
        // recursive step to try all vertices as the next one in the Hamiltonian
        // circuit
        for (const auto &neighbor : adj_list[v]) {
            if (!visited[neighbor.first]) {
                if (hamiltonian_circuit_util(neighbor.first,
                                             visited,
                                             path,
                                             count + 1)) {
                    return true;
                }
            }
        }
    }

    // backtrack
    visited[v] = false;
    path.pop_back();
    return false;
}

int gpmp::Graph::eccentricity(int vertex) {
    std::vector<int> distance(vertices, std::numeric_limits<int>::max());
    distance[vertex] = 0;

    std::queue<int> bfs_queue;
    bfs_queue.push(vertex);

    while (!bfs_queue.empty()) {
        int v = bfs_queue.front();
        bfs_queue.pop();

        for (const auto &neighbor : adj_list[v]) {
            int u = neighbor.first;
            if (distance[u] == std::numeric_limits<int>::max()) {
                distance[u] = distance[v] + 1;
                bfs_queue.push(u);
            }
        }
    }

    // the eccentricity is the maximum distance from the given vertex
    return *std::max_element(distance.begin(), distance.end());
}

// method to calculate the radius of the graph
int gpmp::Graph::radius() {
    int min_ecntrc = std::numeric_limits<int>::max();

    for (int v = 0; v < vertices; ++v) {
        int vEccentricity = eccentricity(v);
        min_ecntrc = std::min(min_ecntrc, vEccentricity);
    }

    return min_ecntrc;
}

int gpmp::Graph::chromatic_number() {
    std::vector<int> result(vertices, -1);

    // assign the first color to the first vertex
    result[0] = 0;

    // initialize available colors. For each vertex, remove colors used by its
    // neighbors.
    std::vector<bool> available(vertices, false);
    for (const auto &neighbor : adj_list[0]) {
        int v = neighbor.first;
        if (result[v] != -1) {
            available[result[v]] = true;
        }
    }

    // assign colors to the remaining vertices
    for (int v = 1; v < vertices; ++v) {
        for (int c = 0; c < vertices; ++c) {
            if (!available[c]) {
                result[v] = c;
                break;
            }
        }

        // reset available colors for the next vertex
        std::fill(available.begin(), available.end(), false);

        // update available colors for neighbors
        for (const auto &neighbor : adj_list[v]) {
            int u = neighbor.first;
            if (result[u] != -1) {
                available[result[u]] = true;
            }
        }
    }

    // find the maximum color assigned, which represents the chromatic number
    int chrom_num = *std::max_element(result.begin(), result.end()) + 1;

    return chrom_num;
}

// method to perform graph coloring using the greedy algorithm
std::vector<int> gpmp::Graph::greedy_coloring() {
    std::vector<int> result(vertices, -1);

    // assign colors to vertices
    for (int v = 0; v < vertices; ++v) {
        std::vector<bool> available(vertices, false);
        for (const auto &neighbor : adj_list[v]) {
            int u = neighbor.first;
            if (result[u] != -1) {
                available[result[u]] = true;
            }
        }

        for (int c = 0; c < vertices; ++c) {
            if (!available[c]) {
                result[v] = c;
                break;
            }
        }
    }

    return result;
}

std::vector<std::pair<int, int>> gpmp::Graph::match_cardinality() {
    std::vector<std::pair<int, int>> matching;

    // iterate through each vertex and find unmatched neighbors
    for (int v = 0; v < vertices; ++v) {
        if (!is_matched[v]) {
            for (const auto &neighbor : adj_list[v]) {
                int u = neighbor.first;
                if (!is_matched[u]) {
                    matching.push_back({v, u});
                    is_matched[v] = true;
                    is_matched[u] = true;
                    break;
                }
            }
        }
    }

    return matching;
}

// method to find a maximum weight matching in the graph using greedy algorithm
std::vector<std::pair<int, int>> gpmp::Graph::match_wt() {
    std::vector<std::pair<int, int>> matching;

    // sort edges in descending order based on weights
    std::vector<std::pair<std::pair<int, int>, int>> wt_edges;
    for (int v = 0; v < vertices; ++v) {
        for (const auto &neighbor : adj_list[v]) {
            int u = neighbor.first;
            int weight = neighbor.second;
            wt_edges.push_back({{v, u}, weight});
        }
    }

    std::sort(wt_edges.rbegin(),
              wt_edges.rend(),
              [](const auto &a, const auto &b) { return a.second < b.second; });

    // iterate through sorted edges and add to matching if both vertices are
    // unmatched
    for (const auto &edge : wt_edges) {
        int v = edge.first.first;
        int u = edge.first.second;
        if (!is_matched[v] && !is_matched[u]) {
            matching.push_back({v, u});
            is_matched[v] = true;
            is_matched[u] = true;
        }
    }

    return matching;
}

bool gpmp::Graph::is_planar() {
    // planar graphs satisfy Kuratowski's theorem: they do not contain a
    // subgraph that is a subdivision of K5 or K3,3.
    return !has_k5() && !has_k33();
}

// method to generate a random planar graph using the random geometric graph
// model
void gpmp::Graph::planar_gen(int num_vertices, double radius) {
    vertices = num_vertices;
    adj_list.resize(vertices);

    // generate random points in a 2D plane
    std::vector<std::pair<double, double>> points;
    for (int v = 0; v < vertices; ++v) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;
        points.push_back({x, y});
    }

    // connect vertices if their Euclidean distance is less than the specified
    // radius
    for (int v = 0; v < vertices; ++v) {
        for (int u = v + 1; u < vertices; ++u) {
            double distance = euclid_dist(points[v], points[u]);
            if (distance < radius) {
                // TODO the weight of the generated edges should probably be
                // determined algorithmically
                add_edge(v, u, 0);
            }
        }
    }
}

// method to check if the graph contains a subgraph that is a subdivision of K5
bool gpmp::Graph::has_k5() {
    for (int v = 0; v < vertices; ++v) {
        if (adj_list[v].size() >= 5) {
            std::set<int> neighbors;
            for (const auto &neighbor : adj_list[v]) {
                neighbors.insert(neighbor.first);
            }

            for (const auto &u : neighbors) {
                std::set<int> common_neighbors;
                for (const auto &neighbor : adj_list[u]) {
                    if (neighbors.find(neighbor.first) != neighbors.end()) {
                        common_neighbors.insert(neighbor.first);
                    }
                }

                for (const auto &w : common_neighbors) {
                    if (neighbors.find(w) != neighbors.end()) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// method to check if the graph contains a subgraph that is a subdivision of
// K3,3
bool gpmp::Graph::has_k33() {
    for (int v = 0; v < vertices; ++v) {
        if (adj_list[v].size() >= 3) {
            std::set<int> neighbors;
            for (const auto &neighbor : adj_list[v]) {
                neighbors.insert(neighbor.first);
            }

            if (is_k33(neighbors)) {
                return true;
            }
        }
    }

    return false;
}

// helper method to check if a set of vertices forms a K3,3 subgraph
bool gpmp::Graph::is_k33(const std::set<int> &vertices) {
    if (vertices.size() == 6) {
        int degree_sum = 0;
        for (int v : vertices) {
            degree_sum += adj_list[v].size();
        }

        // Cast vertices.size() to int to avoid the comparison warning
        return degree_sum == 2 * static_cast<int>(vertices.size());
    }
    return false;
}

// helper method to calculate the Euclidean distance between two points
double gpmp::Graph::euclid_dist(const std::pair<double, double> &point1,
                                const std::pair<double, double> &point2) {
    double dx = point1.first - point2.first;
    double dy = point1.second - point2.second;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<uint64_t> gpmp::Graph::compress() {
    std::vector<uint64_t> compressed;
    compressed.push_back(vertices);

    for (int v = 0; v < vertices; ++v) {
        // encode the number of neighbors using Elias Gamma encoding
        std::bitset<64> binary_representation(adj_list[v].size() + 1);
        int length = log2(adj_list[v].size() + 1) + 1;

        // store the length of the encoded number
        compressed.push_back(length);

        // store the encoded number
        compressed.push_back(
            std::stoull(binary_representation.to_string(), 0, 2));

        // store the neighbors
        for (const auto &neighbor : adj_list[v]) {
            compressed.push_back(neighbor.first);
        }
    }

    return compressed;
}

// method to decompress a compressed graph using the Elias Gamma encoding
void gpmp::Graph::decompress(const std::vector<uint64_t> &compressed) {
    int index = 0;
    vertices = compressed[index++];

    adj_list.resize(vertices);

    for (int v = 0; v < vertices; ++v) {
        int length = compressed[index++];
        uint64_t encoded_neighbors = compressed[index++];
        std::bitset<64> binary_representation(encoded_neighbors);

        // decode the number of neighbors
        int num_neighbors =
            std::stoi(binary_representation.to_string().substr(64 - length),
                      nullptr,
                      2) -
            1;

        // decode and add neighbors
        for (int i = 0; i < num_neighbors; ++i) {
            adj_list[v].emplace_back(compressed[index++],
                                     0); // TODO assuming unweighted graph
        }
    }
}
