#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <queue>
#include <tuple>

[[nodiscard]] std::vector<Move> get_possible_moves(Board const & board, Move last_move) noexcept{
    auto moves = std::vector<Move>{};
    for(auto position = Index(0); position < board.size(); position++){
        if (board[position] == EMPTY)
            continue;
        if (number_of_empty_neigbors(board, position) == 0)
            continue;
        for (auto destination = Index(0); destination < board.size(); destination++){
            auto move = Move{position, destination};
            if (destination == position || move.is_inverse(last_move))
                continue;
            if (number_of_empty_neigbors(board, destination) == 1){ // TODO add search for these moves
                moves.push_back(move);
                move.print();
            }
        }
    }
    return moves;
}


[[nodiscard]] bool play(Board const& initial_board) noexcept {
    auto boards = std::queue<std::tuple<Board,size_t,Move>>();
    boards.emplace(initial_board, 0, Move{0,0});
    while (not boards.empty()){
        auto [current_board, current_move, last_move] = boards.front();
        boards.pop();
        if (is_finished(current_board, current_move))
        {}
        std::cout << "Current Move: " << current_move << std::endl;
        auto possible_moves = get_possible_moves(current_board, last_move);
        for(auto move: possible_moves){
            boards.emplace(do_move(current_board, move), current_move + 1, move);
        }
    }
    return false;
}


int main()
{
    auto found = play(initial_board());
    std::cout << "Found at least 1 soluton: " << found << std::endl;
    return 0;
}
