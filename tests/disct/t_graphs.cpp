/**
 * Unit tests for Graph related methods
 */
#include "../../include/disct/graphs.hpp"
#include <gtest/gtest.h>
#include <iostream>

namespace {

TEST(GraphTest, AddEdge) {
    gpmp::Graph graph(4);

    graph.add_edge(0, 1, 10);
    graph.add_edge(1, 2, 20);
    graph.add_edge(2, 3, 30);

    // check if the adjacency list has been updated correctly
    ASSERT_EQ(graph.adj_list[0].size(), 1);
    ASSERT_EQ(graph.adj_list[1].size(), 2);
    ASSERT_EQ(graph.adj_list[2].size(), 2);
}
}
