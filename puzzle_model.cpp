//
// Created by hungr on 2020/02/27.
//

#include "puzzle_model.h"

puzzle_model::puzzle_model() {
    start();
}

void puzzle_model::start() {
    question = {
            0, 0, 1, 0, 8, 4, 6, 0, 0,
            0, 4, 0, 2, 0, 0, 0, 3, 0,
            0, 0, 7, 0, 0, 0, 5, 0, 9,
            0, 0, 6, 0, 0, 0, 1, 0, 7,
            0, 0, 0, 0, 0, 0, 3, 0, 6,
            0, 0, 0, 1, 0, 6, 0, 0, 0,
            0, 0, 0, 0, 7, 0, 0, 0, 5,
            0, 8, 0, 0, 0, 0, 0, 0, 0,
            3, 0, 4, 0, 0, 0, 0, 2, 0
    };
    answer = {
            5, 3, 1, 9, 8, 4, 6, 7, 2,
            6, 4, 9, 2, 5, 7, 8, 3, 1,
            8, 2, 7, 6, 1, 3, 5, 4, 9,
            4, 9, 6, 8, 3, 2, 1, 5, 7,
            2, 1, 8, 7, 4, 5, 3, 9, 6,
            7, 5, 3, 1, 9, 6, 2, 8, 4,
            9, 6, 2, 3, 7, 8, 4, 1, 5,
            1, 8, 5, 4, 2, 9, 7, 6, 3,
            3, 7, 4, 5, 6, 1, 9, 2, 8
    };
    for(int i = 0; i < 81; i++) {
        data.answer[i] = question[i];
        data.memo[i].clear();
    }
    hist.push_hist(data);
}

void puzzle_model::set_answer(int x, int y, int answer) {
    if(question[x + y * 9]) return;
    data.memo[x + y * 9].clear();
    data.answer[x + y * 9] = data.answer[x + y * 9] == answer ? 0 : answer;
    for(int i = 0; i < 9; i++) {
        data.memo[i + y * 9].erase(answer);
        data.memo[x + i * 9].erase(answer);
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            data.memo[i + x / 3 * 3 + (j + y / 3 * 3) * 9].erase(answer);
        }
    }
    hist.push_hist(data);
}

void puzzle_model::set_memo(int x, int y, int memo) {
    if(question[x + y * 9]) return;
    data.answer[x + y * 9] = 0;
    if(data.memo[x + y * 9].count(memo))
        data.memo[x + y * 9].erase(memo);
    else
        data.memo[x + y * 9].insert(memo);
    hist.push_hist(data);
}

bool puzzle_model::is_answer(int x, int y) const {
    return data.memo[x + y * 9].empty();
}

int puzzle_model::get_answer(int x, int y) const {
    return data.answer[x + y * 9];
}

std::set<int> puzzle_model::get_memo(int x, int y) const {
    return data.memo[x + y * 9];
}

void puzzle_model::clear(int x, int y) {
    if(question[x + y * 9]) return;
    data.answer[x + y * 9] = 0;
    data.memo[x + y * 9].clear();
}

bool puzzle_model::is_question(int x, int y) const {
    return question[x + y * 9];
}

bool puzzle_model::is_valid(int x, int y) const {
    for(int i = 0; i < 9; i++) {
        if(i != y && data.answer[x + i * 9] == data.answer[x + y * 9]) return false;
        if(i != x && data.answer[i + y * 9] == data.answer[x + y * 9]) return false;
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int _x = i + x / 3 * 3, _y = j + y / 3 * 3;
            if(!(x == _x && y == _y) && data.answer[_x + _y * 9] == data.answer[x + y * 9]) return false;
        }
    }
    return true;
}

void puzzle_model::restart() {
    for(int i = 0; i < 81; i++) {
        data.answer[i] = question[i];
        data.memo[i].clear();
    }
}

void puzzle_model::set_answer() {
    for(int i = 0; i < 81; i++) {
        data.answer[i] = answer[i];
        data.memo[i].clear();
    }
}

void puzzle_model::undo() {
    if(hist.can_undo()) data = hist.undo();
}

void puzzle_model::redo() {
    if(hist.can_redo()) data = hist.redo();
}
