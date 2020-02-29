//
// Created by hungr on 2020/02/27.
//

#include "history.h"

bool history::can_undo() const noexcept {
    return current > 0;
}

bool history::can_redo() const noexcept {
    return current < hist.size() - 1;
}

puzzle history::undo() {
    return can_undo() ? hist[--current] : hist[current];
}

puzzle history::redo() {
    return can_redo() ? hist[++current] : hist[current];
}

void history::push_hist(puzzle pzl) {
    while(hist.size() - current > 1) hist.pop_back();
    hist.push_back(pzl);
    current++;
}