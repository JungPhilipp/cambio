#pragma once
#include <cstddef>
#include <ostream>
#include <string>

namespace graph {
enum class Field : unsigned { EMPTY, RED, BLUE };

struct Node {
  explicit Node(size_t index, Field field = Field::EMPTY)
      : index(index), field(field) {}
  size_t index;
  Field field;
  [[nodiscard]] auto operator<(Node const &other) const noexcept -> bool {
    return index < other.index;
  }
  [[nodiscard]] auto operator==(Node const &other) const noexcept -> bool {
    return index == other.index;
  }
};
namespace {
  [[nodiscard]] auto red() noexcept -> std::string{
    return std::string ("\033[1;31mo\033[0m");
  }
  [[nodiscard]] auto blue() noexcept -> std::string{
    return std::string ("\034[1;31mo\034[0m");
  }
  [[nodiscard]] auto white() noexcept -> std::string{
    return std::string ("o");
  }
}

std::ostream & operator << (std::ostream &out, Node const& node)
{
  switch(node.field){
  case Field::BLUE:
    out << blue(); break;
  case Field::RED:
    out << red(); break;
  case Field::EMPTY:
  default:
    out << white();
  }
  return out;
}
} // namespace graph