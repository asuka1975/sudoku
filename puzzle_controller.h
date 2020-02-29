//
// Created by hungr on 2020/02/27.
//

#ifndef SUDOKU_PUZZLE_CONTROLLER_H
#define SUDOKU_PUZZLE_CONTROLLER_H

#include <utility>
#include "puzzle_view.h"
#include "puzzle_model.h"

class puzzle_controller {
public:
    puzzle_controller();
    puzzle_view& get_view();
    void send_answer(int answer);
    void send_memo(int answer);
    void clear();
    void restart();
    void start();
    void answer();
    void undo();
    void redo();
private:
    int cur_x;
    int cur_y;
    puzzle_view view;
    puzzle_model model;
};


#endif //SUDOKU_PUZZLE_CONTROLLER_H
