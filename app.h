//
// Created by hungr on 2020/02/23.
//

#ifndef SUDOKU_APP_H
#define SUDOKU_APP_H

#include <string>
#include <vector>

namespace app {
    extern std::vector<std::string> args;

    void init(int* argc, char*** argv);
    void run();
}

#endif //SUDOKU_APP_H
