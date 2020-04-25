#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <queue>
#include <tuple>
#include <graph/Graph.h>

using namespace graph;
using namespace move;

[[nodiscard]] bool play(Graph const& initial_board, Graph const& finish_board) noexcept {
    auto boards = std::queue<std::tuple<Graph,size_t,Move>>();
    boards.emplace(initial_board, 0, Move{0,0});
    while (not boards.empty()){
        auto [current_board, current_move, last_move] = boards.front();
        boards.pop();
        if (current_board == finish_board){
          current_board.print();
          return true;
        }
        std::cout << "Current Move: " << current_move << std::endl;
        auto possible_moves = current_board.possible_moves();
        for(auto move: possible_moves){
            if (move.is_inverse(last_move))
              continue;
            auto copy_board = current_board;
            copy_board.do_move(move);
            boards.emplace(copy_board, current_move + 1, move);
        }
    }
    return false;
}


int main()
{
    auto adj_matrix = graph::example_01::adj_matrix();
    auto pos_red = graph::example_01::initial_positions_red();
    auto pos_blue = graph::example_01::initial_positions_blue();
    auto intial_board = graph::Graph(adj_matrix, pos_red, pos_blue);
    auto finished_board = graph::Graph(adj_matrix, pos_blue, pos_red);
    auto found = play(intial_board, finished_board);
    std::cout << "Found at least 1 soluton: " << found << std::endl;
    return 0;
}
