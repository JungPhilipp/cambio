//
// Created by philipp on 4/25/20.
//
#pragma once
#include <ostream>
#include <cstddef>

namespace move {
struct Move {
  size_t source;
  size_t destination;
  [[nodiscard]] constexpr auto is_inverse(Move const &other) const noexcept
      -> bool {
    return other.source == destination && other.destination == source;
  }
  [[nodiscard]] constexpr auto operator==(Move const &other) const noexcept -> bool{
    return source == other.source && destination == other.destination;
  }
  [[nodiscard]] constexpr auto operator!=(Move const &other) const noexcept -> bool{
    return not operator==(other);
  }
};

std::ostream & operator << (std::ostream &out, Move const& move)
{
    out << "Move:" << move.source << " -> " << move.destination;
  return out;
}
}
