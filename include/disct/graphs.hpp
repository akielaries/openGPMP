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

#ifndef __GRAPHS_HPP__
#define __GCDS_HPP__

#include <limits>
#include <stack>
#include <vector>

namespace gpmp {

/*
 * @class Graph
 * @brief Graph class containing several utility methods and algorithms
 */
class Graph {
  public:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adj_list;

    /**
     * @brief Constructor for the Graph class
     * @param v Number of vertices in the graph
     */
    Graph(int v) : vertices(v), adj_list(v) {
    }

    /**
     * @brief Adds an edge between two vertices with a specified weight
     * @param v The first vertex
     * @param w The second vertex
     * @param weight The weight of the edge
     */
    void add_edge(int v, int w, int weight);

    /**
     * @brief Performs Depth-First Search (DFS) traversal starting from a given
     * vertex
     * @param start The starting vertex for DFS traversal
     */
    void dfs(int start);

    /**
     * @brief Helper function for recursive Depth-First Search (DFS) traversal
     * @param v The current vertex
     * @param visited A vector indicating whether each vertex has been visited
     */
    void dfs_rec(int v, std::vector<bool> &visited);

    /**
     * @brief Performs Breadth-First Search (BFS) traversal starting from a
     * given vertex
     * @param start The starting vertex for BFS traversal
     */
    void bfs(int start);

    /**
     * @brief Applies Dijkstra's algorithm to find the single-source shortest
     * paths in the graph
     * @param start The starting vertex for Dijkstra's algorithm
     */
    void dijkstra(int start);

    /**
     * @brief Applies Bellman-Ford algorithm to find the single-source shortest
     * paths in the graph, handling negative weights
     * @param start The starting vertex for Bellman-Ford algorithm
     */
    void bellman_ford(int start);

    /**
     * @brief Applies Kruskal's algorithm to find the minimum spanning tree of
     * the graph
     * @return Vector of edges forming the minimum spanning tree
     */
    std::vector<std::pair<int, std::pair<int, int>>> kruskal();

    /**
     * @brief Applies Floyd-Warshall algorithm to find all-pairs shortest paths
     * in the graph
     */
    void floyd_warshall();

    /**
     * @brief Performs topological sorting on a Directed Acyclic Graph (DAG)
     */
    void topo_sort();

  private:
    /**
     * @brief Helper function for topological sorting
     * @param v The current vertex
     * @param visited A vector indicating whether each vertex has been visited
     * @param topo_stack The stack used for topological sorting
     */
    void topo_sort_util(int v,
                        std::vector<bool> &visited,
                        std::stack<int> &topo_stack);

    /**
     * @brief Finds the representative element of the set that contains the
     * given element
     * @param parent The parent vector representing disjoint sets
     * @param i The element to find
     * @return The representative element of the set containing 'i'
     */
    int find(std::vector<int> &parent, int i);

    /**
     * @brief Unions two sets by rank in the disjoint set data structure
     * @param parent The parent vector representing disjoint sets
     * @param x The representative element of the first set
     * @param y The representative element of the second set
     */
    void union_sets(std::vector<int> &parent, int x, int y);
};

} // namespace gpmp

#endif
