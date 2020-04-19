#pragma once
#include <queue>
#include <vector>
#include <set>

namespace graph {
template <class Predicate>
[[nodiscard]] auto breath_first_search(Graph const &graph,
                                       Node const &start_node,
                                       Predicate predicate) noexcept
    -> std::vector<Node> {
  auto result = std::vector<Node>();
  auto nodes = std::queue<Node>(); // Change to vector?
  auto visited_nodes = std::set<Node>();
  nodes.push(start_node);

  while (not nodes.empty()) {
    auto const node = nodes.front();
    nodes.pop();
    visited_nodes.insert(node);
    auto const neighbors = graph.node_neighbors(node);
    if (predicate(node, neighbors))
      result.push_back(node);
    for (auto const &neighbor : neighbors)
      if (not visited_nodes.contains(neighbor))
        nodes.push(neighbor);
  }
  return result;
}
} // namespace graph