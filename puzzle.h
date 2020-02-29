//
// Created by hungr on 2020/02/29.
//

#ifndef SUDOKU_PUZZLE_H
#define SUDOKU_PUZZLE_H

#include <array>
#include <set>

struct puzzle {
    std::array<int, 9*9> answer;
    std::array<std::set<int>, 9*9> memo;
    puzzle() = default;
    puzzle(const puzzle& obj);
    void operator=(const puzzle& obj);
};

#endif //SUDOKU_PUZZLE_H
