//
// Created by hungr on 2020/02/27.
//

#include "history.h"

command::command(int x, int y, std::vector<int> memo) : x(x), y(y), memo(memo), is_memo(true) { }

command::command(int x, int y, int answer) : x(x), y(y), answer(answer), is_memo(false) { }

bool history::can_undo() const noexcept {
    return current > 0;
}

bool history::can_redo() const noexcept {
    return current < hist.size() - 1;
}

command history::undo() {
    return can_undo() ? hist[--current] : hist[current];
}

command history::redo() {
    return can_redo() ? hist[++current] : hist[current];
}

void history::push_hist(command cmd) {
    while(hist.size() - current > 1) hist.pop_back();
    hist.push_back(cmd);
    current++;
}
