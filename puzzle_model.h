//
// Created by hungr on 2020/02/27.
//

#ifndef SUDOKU_PUZZLE_MODEL_H
#define SUDOKU_PUZZLE_MODEL_H

#include <array>
#include <set>
#include "history.h"
#include "puzzle.h"

class puzzle_model {
public:
    puzzle_model();
    void start();
    void set_answer(int x, int y, int answer);
    int get_answer(int x, int y) const;
    void set_memo(int x, int y, int memo);
    std::set<int> get_memo(int x, int y) const;
    bool is_answer(int x, int y) const;
    void clear(int x, int y);
    void restart();
    void set_answer();
    void undo();
    void redo();
    bool is_question(int x, int y) const;
    bool is_valid(int x, int y) const;
    std::array<bool, 9> get_complete() const;
private:
    puzzle data;
    std::array<int, 9*9> question;
    std::array<int, 9*9> answer;
    history hist;
};


#endif //SUDOKU_PUZZLE_MODEL_H
