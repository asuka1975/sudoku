//
// Created by hungr on 2020/02/28.
//

#ifndef SUDOKU_MAINWINDOW_CONTROLLER_H
#define SUDOKU_MAINWINDOW_CONTROLLER_H

#include "mainwindow_view.h"
#include "puzzle_controller.h"

class mainwindow_controller {
public:
    mainwindow_controller();

private:
    puzzle_controller controller;
    mainwindow_view view;
};


#endif //SUDOKU_MAINWINDOW_CONTROLLER_H
