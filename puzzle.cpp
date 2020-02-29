//
// Created by hungr on 2020/02/29.
//

#include "puzzle.h"

puzzle::puzzle(const puzzle &obj) {
    for(int i = 0; i < 81; i++) {
        answer[i] = obj.answer[i];
        memo[i] = obj.memo[i];
    }
}

void puzzle::operator=(const puzzle &obj) {
    for(int i = 0; i < 81; i++) {
        answer[i] = obj.answer[i];
        memo[i] = obj.memo[i];
    }
}
