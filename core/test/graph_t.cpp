#include <doctest.h>
#include <graph/Graph.h>
#include <graph/move.h>

#include <graph/breath_first_search.h>

using namespace graph;
using namespace move;


TEST_CASE("Graph"){
  auto adj_matrix = AdjazenzMatrix({{1,2,3},{0,3},{0,3},{0,1,2}});
  auto graph = Graph(adj_matrix);

  SUBCASE("neighbors"){
    auto first_node = graph[0];
    auto neighbors = graph.node_neighbors(first_node);
    REQUIRE(neighbors == std::vector{Node{1},Node{2},Node{3}});
    auto second_node = graph[1];
    neighbors = graph.node_neighbors(second_node);
    REQUIRE(neighbors == std::vector{Node{0},Node{3}});
  }

  SUBCASE("breath_first_search"){
    auto predicate = [](Node const& node, std::vector<Node> const& neighbors){return neighbors.size() == 1;};
    auto found_nodes = breath_first_search(graph, graph[0], predicate);
    REQUIRE(found_nodes.size() == 0);
    auto predicate1 = [](Node const& node, std::vector<Node> const& neighbors){return neighbors.size() == 2;};
    found_nodes = breath_first_search(graph, graph[0], predicate1);
    REQUIRE(found_nodes.size() == 2);
    REQUIRE(found_nodes == std::vector{Node{1},Node{2}});
  }
}

TEST_CASE("Print"){
  auto adj_matrix = example_01::adj_matrix();
  auto graph = Graph(adj_matrix);
  graph.print();
}

TEST_CASE("Move"){
  auto adj_matrix = example_01::adj_matrix();
  auto initial_positions_red = example_01::initial_positions_red();
  auto initial_positions_blue = example_01::initial_positions_blue();
  auto graph = Graph(adj_matrix, initial_positions_red, initial_positions_blue);
  graph.print();

  SUBCASE("Move is_inverse"){
    static_assert(Move{10,10}.is_inverse({10,10}));
    static_assert(Move{10,20}.is_inverse({20,10}));
    static_assert(Move{20,10}.is_inverse({10,20}));
    static_assert(not Move{20,10}.is_inverse({30,20}));
  }
  SUBCASE("Move equality") {
    static_assert(Move{10, 10} == Move{10, 10});
    static_assert(Move{1, 10} != Move{10, 10});
  }
}