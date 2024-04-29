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
 * LICENSE file.
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

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// Constants
const int INF = std::numeric_limits<int>::max();

// Data structure to represent edges
struct Edge {
    int to;
    int weight;
};

// Dijkstra's algorithm implementation
void dijkstra(const std::vector<std::vector<Edge>> &graph,
              int source,
              std::vector<int> &distances,
              std::vector<int> &parents) {
    int n = graph.size();
    distances.assign(n, INF);
    parents.assign(n, -1);

    distances[source] = 0;
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    pq.push(std::make_pair(0, source));

    while (!pq.empty()) {
        int current = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        if (distance > distances[current])
            continue;

        for (const Edge &edge : graph[current]) {
            int neighbor = edge.to;
            int new_distance = distance + edge.weight;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                parents[neighbor] = current;
                pq.push(std::make_pair(new_distance, neighbor));
            }
        }
    }
}

int main() {
    int n = 4; // Number of nodes
    std::vector<std::vector<Edge>> graph(n);

    graph[0].push_back({1, 2});
    graph[0].push_back({2, 5});
    graph[1].push_back({2, 1});
    graph[1].push_back({3, 3});
    graph[2].push_back({3, 1});

    int source = 0;
    std::vector<int> distances, parents;
    dijkstra(graph, source, distances, parents);

    int destination = 3;
    std::cout << "Shortest distance from " << source << " to " << destination
              << ": " << distances[destination] << std::endl;
    std::cout << "Shortest path: ";
    for (int node = destination; node != -1; node = parents[node])
        std::cout << node << " ";
    std::cout << std::endl;

    return 0;
}
