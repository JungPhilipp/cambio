#include <doctest.h>
#include <graph/Graph.h>

#include <graph/breath_first_search.h>

using namespace graph;


TEST_CASE("Graph"){
  auto adj_matrix = AdjazenzMatrix({{1,2,3},{0,3},{0,3},{0,1,2}});
  auto graph = Graph(adj_matrix);

  SUBCASE("neighbors"){
    auto first_node = graph[0];
    auto neighbors = graph.node_neighbors(first_node);
    REQUIRE(neighbors == std::vector<Node>{1,2,3});
    auto second_node = graph[1];
    neighbors = graph.node_neighbors(second_node);
    REQUIRE(neighbors == std::vector<Node>{0u,3u});
  }

  SUBCASE("breath_first_search"){
    auto predicate = [](Node const& node, std::vector<Node> const& neighbors){return neighbors.size() == 1;};
    auto found_nodes = breath_first_search(graph, graph[0], predicate);
    REQUIRE(found_nodes.size() == 0);
    auto predicate1 = [](Node const& node, std::vector<Node> const& neighbors){return neighbors.size() == 2;};
    REQUIRE(found_nodes.size() == 2);
    REQUIRE(found_nodes == std::vector<Node>{1,2});
  }
}