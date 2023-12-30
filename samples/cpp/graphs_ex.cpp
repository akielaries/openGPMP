#include <iostream>
#include <openGPMP/disct/graphs.hpp>
#include <vector>

int main() {
    gpmp::Graph g(6);
    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 4);
    g.add_edge(1, 3, 3);
    g.add_edge(1, 4, 1);
    g.add_edge(2, 5, 5);

    std::cout << "DFS Traversal starting from vertex 0: ";
    g.dfs(0);
    std::cout << std::endl;

    std::cout << "BFS Traversal starting from vertex 0: ";
    g.bfs(0);
    std::cout << std::endl;

    g.dijkstra(0);

    g.bellman_ford(0);

    std::cout << "Kruskal's Minimum Spanning Tree:\n";
    std::vector<std::pair<int, std::pair<int, int>>> kruskalMST = g.kruskal();
    for (const auto &edge : kruskalMST) {
        std::cout << "Edge: " << edge.second.first << " - "
                  << edge.second.second << " | Weight: " << edge.first << "\n";
    }

    g.floyd_warshall();

    std::cout << "Graph for Topological Sorting:\n";
    gpmp::Graph dag(6);
    dag.add_edge(0, 1, 1);
    dag.add_edge(0, 2, 1);
    dag.add_edge(1, 3, 1);
    dag.add_edge(2, 3, 1);
    dag.add_edge(3, 4, 1);
    dag.add_edge(4, 5, 1);
    dag.topo_sort();

    return 0;
}
