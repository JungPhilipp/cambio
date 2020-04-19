#pragma once
#include <cstddef>
enum Field : unsigned{
  EMPTY,
  RED,
  BLUE
};

struct Node{
  explicit Node(size_t index, Field field = EMPTY): index(index), field(field){}
  size_t index;
  Field field;
  [[nodiscard]] auto operator<(Node const& other) const noexcept -> bool{
    return index < other.index;
  }
  [[nodiscard]] auto operator==(Node const& other) const noexcept -> bool{
    return index == other.index;
  }
};