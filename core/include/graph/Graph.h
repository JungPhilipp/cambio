#pragma once
#include <cassert>
#include <type_traits>
#include <vector>

#include <graph/Node.h>

namespace graph {

using AdjazenzMatrix = std::vector<std::vector<size_t>>;

class Graph {
public:
  explicit Graph(AdjazenzMatrix adjazenzMatrix) noexcept
      : adj_matrix(std::move(adjazenzMatrix)) {}

  [[nodiscard]] auto size() const noexcept -> size_t {
    return adj_matrix.size();
  }

  [[nodiscard]] auto operator[](size_t node_index) const noexcept -> Node {
    return Node(node_index);
  }

  [[nodiscard]] auto node_neighbors(Node const &node) const noexcept
      -> std::vector<Node> {
    auto result = std::vector<Node>();
    assert(node.index >= 0 && node.index < adj_matrix.size() &&
           "Node index is out of range");
    result.reserve(adj_matrix[node.index].size());
    auto const &neighbor_indices = adj_matrix[node.index];
    std::transform(begin(neighbor_indices), end(neighbor_indices),
                   std::back_inserter(result),
                   [](auto node_index) { return Node(node_index); });
    return result;
  }

private:
  AdjazenzMatrix adj_matrix;
};
} // namespace graph