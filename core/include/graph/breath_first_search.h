#pragma once
#include <queue>
#include <vector>
#include <set>

namespace graph {
template <class Predicate>
[[nodiscard]] auto breath_first_search(Graph const &graph,
                                       size_t start_index,
                                       size_t end_index,
                                       Predicate predicate) noexcept
    -> bool {
  auto nodes = std::queue<Node>(); // Change to vector?
  auto visited_nodes = std::set<Node>();
  nodes.push(graph[start_index]);

  while (not nodes.empty()) {
    auto const node = nodes.front();
    if (node.index == end_index)
      return true;
    nodes.pop();
    visited_nodes.insert(node);
    auto const neighbors = graph.node_neighbors(node);
    for (auto const &neighbor : neighbors)
      if (not visited_nodes.contains(neighbor) and predicate(neighbor))
        nodes.push(neighbor);
  }
  return false;
}
} // namespace graph