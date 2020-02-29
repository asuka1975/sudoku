//
// Created by hungr on 2020/02/25.
//

#ifndef SUDOKU_MAINWINDOW_VIEW_H
#define SUDOKU_MAINWINDOW_VIEW_H

#include <string>
#include <array>
#include <map>
#include <gtk/gtk.h>
#include "event/event.h"
#include "puzzle_view.h"

class mainwindow_view {
public:
    mainwindow_view(puzzle_view& content);
    event<mainwindow_view*, int> on_numpad_clicked;
    event<GtkWidget*, nullptr_t> on_new_clicked;
    event<GtkWidget*, nullptr_t> on_restart_clicked;
    event<GtkWidget*, nullptr_t> on_memo_clicked;
    event<GtkWidget*, nullptr_t> on_answer_clicked;
    event<GtkWidget*, nullptr_t> on_undo_clicked;
    event<GtkWidget*, nullptr_t> on_redo_clicked;
    event<GtkWidget*, nullptr_t> on_clear_clicked;
    bool is_memo() const noexcept;
private:
    void init_widgets();
    void init_layout();
private:
    GtkWidget* window;
    GtkWidget* numpad;
    GtkWidget* hbox;
    GtkWidget* fixed;
    GtkWidget* content;
    std::array<GtkWidget*, 9> number_buttons;
    std::map<std::string, GtkWidget*> system_buttons;
};

#endif //SUDOKU_MAINWINDOW_VIEW_H
