//
// Created by hungr on 2020/02/28.
//

#include "mainwindow_controller.h"

mainwindow_controller::mainwindow_controller() : controller(), view(controller.get_view()){
    view.on_numpad_clicked += [this](mainwindow_view* sender, int num) -> void {
        if(sender->is_memo())
            this->controller.send_memo(num);
        else
            this->controller.send_answer(num);
    };
    view.on_clear_clicked += [this](GtkWidget* sender, nullptr_t null) -> void { this->controller.clear(); };
    view.on_restart_clicked += [this](GtkWidget* sender, nullptr_t null) -> void { this->controller.restart(); };
    view.on_new_clicked += [this](GtkWidget* sender, nullptr_t null) -> void { this->controller.start(); };
    view.on_answer_clicked += [this](GtkWidget* sender, nullptr_t null) -> void { this->controller.answer(); };
    view.on_undo_clicked += [this](GtkWidget* sender, nullptr_t null) -> void { this->controller.undo(); };
    view.on_redo_clicked += [this](GtkWidget* sender, nullptr_t null) -> void { this->controller.redo(); };
}
