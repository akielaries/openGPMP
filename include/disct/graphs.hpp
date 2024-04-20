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
#define __GRAPHS_HPP__

#include <cstdint>
// #include <limits>
#include <set>
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

    /**
     * @brief Finds connected components in an undirected graph using
     * Depth-First Search (DFS)
     * @return Vector of vectors representing the connected components
     */
    std::vector<std::vector<int>> connected_components();

    /**
     * @brief Determines if a given graph is bipartite using BFS (Breadth First
     * Search)
     * @note A bipartite graph is a graph where the vertices can be divided into
     * two disjoint sets such that all edges connect a vertex in one set to a
     * vertex in another set
     */
    bool is_bipartite();

    /**
     * @brief Calculates betweenness centrality for each vertex in the graph
     * @return Vector of doubles representing the betweenness centrality of
     * each vertex
     */
    std::vector<double> betweenness_centrality();

    /**
     * @brief Checks if the graph contains a Hamiltonian circuit.
     * @return True if the graph contains a Hamiltonian circuit, false otherwise
     */
    bool has_hamiltonian_circuit();

    /**
     * @brief Checks if the graph contains an Eulerian path
     * @return True if the graph contains an Eulerian path, false otherwise
     */
    bool has_eulerian_path();

    /**
     * @brief Calculates the eccentricity of a specified vertex in the graph
     * @param vertex The vertex for which eccentricity is calculated
     * @return The eccentricity of the specified vertex
     */
    int eccentricity(int vertex);

    /**
     * @brief Calculates the radius of the graph
     * @return The radius of the graph
     */
    int radius();

    /**
     * @brief Performs graph coloring using the greedy algorithm
     * @return Vector of integers representing the color assigned to each vertex
     */
    std::vector<int> greedy_coloring();

    /**
     * @brief Calculates the chromatic number of the graph
     * @return The chromatic number of the graph
     */
    int chromatic_number();

    /**
     * @brief Finds a maximum cardinality matching in the graph using a greedy
     * algorithm
     * @return Vector of pairs representing the edges in the maximum cardinality
     * matching
     */
    std::vector<std::pair<int, int>> match_cardinality();

    /**
     * @brief Finds a maximum weight matching in the graph using a greedy
     * algorithm
     * @return Vector of pairs representing the edges in the maximum weight
     * matching
     */
    std::vector<std::pair<int, int>> match_wt();

    /**
     * @brief Checks if the graph is planar using Kuratowski's theorem
     * @return True if the graph is planar, false otherwise
     */
    bool is_planar();

    /**
     * @brief Generates a random planar graph using the random geometric graph
     * model
     * @param num_vertices The number of vertices in the generated graph
     * @param radius The radius parameter for the random geometric graph model
     */
    void planar_gen(int num_vertices, double radius);

    /**
     * @brief Checks if the graph contains a subgraph that is a subdivision of
     * K5
     * @return True if the graph contains a subgraph that is a subdivision of
     * K5, false otherwise
     */
    bool has_k5();

    /**
     * @brief Checks if the graph contains a subgraph that is a subdivision of
     * K3,3
     * @return True if the graph contains a subgraph that is a subdivision of
     * K3,3, false otherwise
     */
    bool has_k33();

    /**
     * @brief Checks if a set of vertices forms a subgraph that is a subdivision
     * of K3,3
     * @param vertices The set of vertices to be checked
     * @return True if the set of vertices forms a subgraph that is a
     * subdivision of K3,3, false otherwise
     */
    bool is_k33(const std::set<int> &k_vertices);

    /**
     * @brief Calculates the Euclidean distance between two 2D points
     * @param point1 The first 2D point
     * @param point2 The second 2D point
     * @return The Euclidean distance between the two points
     */
    double euclid_dist(const std::pair<double, double> &point1,
                       const std::pair<double, double> &point2);

    /**
     * @brief Compresses the graph using Elias Gamma encoding
     * @return Vector of uint64_t representing the compressed graph
     */
    std::vector<uint64_t> compress();

    /**
     * @brief Decompresses a compressed graph using Elias Gamma encoding
     * @param compressed Vector of uint64_t representing the compressed graph
     */
    void decompress(const std::vector<uint64_t> &compressed);

  private:
    std::vector<bool> is_matched;
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

    /**
     * @brief Performs Depth-First Search (DFS) traversal to find connected
     * components in an undirected graph
     *
     * This method is a helper function used by the connected_components method
     *
     * @param v The current vertex during DFS traversal
     * @param visited A vector indicating whether each vertex has been visited
     * @param component The connected component being formed during the
     * traversal
     */
    void dfs_connected_components(int v,
                                  std::vector<bool> &visited,
                                  std::vector<int> &component);

    /**
     * @brief Chooses a random neighbor of a given vertex
     * @param vertex The vertex for which a random neighbor is chosen
     * @return The index of the randomly chosen neighbor in the adjacency list
     */
    int choose_random_neighbor(int vertex);

    /**
     * @brief Utility function for finding a Hamiltonian circuit
     * @param v The current vertex in the exploration
     * @param visited Vector indicating whether each vertex has been visited
     * @param path Vector representing the current path in the exploration
     * @param count The count of vertices visited so far
     * @return True if a Hamiltonian circuit is found, false otherwise
     */
    bool hamiltonian_circuit_util(int v,
                                  std::vector<bool> &visited,
                                  std::vector<int> &path,
                                  int count);
};

} // namespace gpmp

#endif
