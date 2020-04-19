#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <queue>
#include <tuple>

enum Field : unsigned{
  EMPTY,
  RED,
  BLUE
};

using Board = std::array<Field, 12>;
using Index = unsigned int;
using AdjMatrix = std::array<std::vector<Index>, 12>;

struct Move {
    Index source;
    Index destination;
    [[nodiscard]] constexpr bool is_inverse(Move const & other){
        return other.source == destination && other.destination == source;
    }
    void print(){
        std::cout << "Move:" << source << " -> " << destination << std::endl;
    }
};

[[nodiscard]] AdjMatrix get_adj_matrix() noexcept {
    return {std::vector<Index>{1u},
            std::vector<Index>{0u, 2u},
            std::vector<Index>{1u, 3u, 4u},
            std::vector<Index>{2u},
            std::vector<Index>{2u, 5u},
            std::vector<Index>{4u, 6u, 7u},
            std::vector<Index>{5u},
            std::vector<Index>{5u, 8u},
            std::vector<Index>{7u, 9u, 10u},
            std::vector<Index>{8u},
            std::vector<Index>{8u, 11u},
            std::vector<Index>{10u}
    };

}

auto inline adj_matrix = get_adj_matrix();

[[nodiscard]] constexpr Board initial_board() noexcept{

    return {RED, RED, RED, RED,
            EMPTY, EMPTY, EMPTY, EMPTY,
            BLUE, BLUE, BLUE, BLUE};
}



[[nodiscard]] constexpr bool finished_Board(Board const & board) noexcept{
    auto finished = Board {BLUE, BLUE, BLUE, BLUE,
                           EMPTY, EMPTY, EMPTY, EMPTY,
                           RED, RED, RED, RED};
    for(auto i = Index(0); i < board.size(); i++){
        if (board[i] != finished[i])
            return false;
    }
    return true;
}

void print_board(Board const & board) noexcept{
    for(auto field : board){
        std::cout << field << " | " ;
    }
    std::cout << std::endl;
}

[[nodiscard]] constexpr Board do_move(Board board, Move move) noexcept {
    assert (board[move.source] != EMPTY && "Board[source] is an empty field");

    board[move.destination] = board[move.source];
    board[move.source] = EMPTY;
    return board;
}

[[nodiscard]] size_t number_of_empty_neigbors(Board const & board, Index position) noexcept {
    auto num = size_t(0);
    for (auto neighbor : adj_matrix[position]){
        if (board[neighbor] != EMPTY)
            num++;
    }
    return num;
}

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

[[nodiscard]] constexpr bool is_finished(Board const& board, size_t moves, size_t max_moves = 100){
    if (finished_Board(board))
    {
        std::cout << "Found solution in " << moves << " moves " << std::endl;
        return true;
    }
    if (moves >= max_moves)
    {
        std::cout << "Max depth reached " << std::endl;
        return true;
    }
    return false;
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
