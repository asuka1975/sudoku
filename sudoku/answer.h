//
// Created by hungr on 2020/03/08.
//

#ifndef SUDOKU_ANSWER_H
#define SUDOKU_ANSWER_H

#include <array>
#include <set>

std::array<int, 81> create_answer();
std::set<int> valid_numbers(std::array<int, 81>& ary, int x, int y);


#endif //SUDOKU_ANSWER_H
