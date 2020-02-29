//
// Created by hungr on 2020/02/27.
//

#ifndef SUDOKU_HISTORY_H
#define SUDOKU_HISTORY_H

#include <vector>
#include <tuple>

struct command {
public:
    int x;
    int y;
    bool is_memo;
    std::vector<int> memo;
    int answer;
    command(int x, int y, std::vector<int> memo);
    command(int x, int y, int answer);
};

class history {
public:
    history() = default;
    [[nodiscard]] bool can_undo() const noexcept;
    [[nodiscard]] bool can_redo() const noexcept;
    command undo();
    command redo();
    void push_hist(command cmd);
private:
    std::vector<command> hist;
    int current;
};


#endif //SUDOKU_HISTORY_H
