//
// Created by hungr on 2020/02/27.
//

#include <functional>
#include "puzzle_controller.h"

puzzle_controller::puzzle_controller() : model(), view(model) {
    view.on_click += [this](const puzzle_view *sender, std::pair<int, int> e) -> void {
        this->cur_x=e.first, this->cur_y=e.second;
    };
    view.update();
}

puzzle_view &puzzle_controller::get_view() {
    return view;
}

void puzzle_controller::send_answer(int answer) {
    model.set_answer(cur_x, cur_y, answer);
    view.update();
}

void puzzle_controller::send_memo(int memo) {
    model.set_memo(cur_x, cur_y, memo);
    view.update();
}

void puzzle_controller::clear() {
    model.clear(cur_x, cur_y);
    view.update();
}

void puzzle_controller::restart() {
    model.restart();
    view.update();
}

void puzzle_controller::start() {
    model.start();
    view.update();
}

void puzzle_controller::answer() {
    model.set_answer();
    view.update();
}


