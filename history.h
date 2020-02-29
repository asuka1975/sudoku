//
// Created by hungr on 2020/02/27.
//

#ifndef SUDOKU_HISTORY_H
#define SUDOKU_HISTORY_H

#include <vector>
#include <tuple>
#include "puzzle.h"


class history {
public:
    history() = default;
    [[nodiscard]] bool can_undo() const noexcept;
    [[nodiscard]] bool can_redo() const noexcept;
    puzzle undo();
    puzzle redo();
    void push_hist(puzzle pzl);
private:
    std::vector<puzzle> hist;
    int current;
};


#endif //SUDOKU_HISTORY_H
