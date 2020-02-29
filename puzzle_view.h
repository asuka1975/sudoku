//
// Created by hungr on 2020/02/25.
//

#ifndef SUDOKU_PUZZLE_VIEW_H
#define SUDOKU_PUZZLE_VIEW_H

#include <array>
#include <gtk/gtk.h>
#include "event/event.h"
#include "puzzle_model.h"

class puzzle_view {
public:
    puzzle_view(const puzzle_model& model);
    void layout_this_to_container(GtkWidget* container);
    void update();
    event<const puzzle_view*, std::pair<int, int>> on_click;
private:
    const puzzle_model& model;
    GtkWidget* puzzle;
    GtkWidget* complete_label;
    std::array<GtkWidget*, 9*9> eventboxes;
    std::array<GtkWidget*, 9*9> cells;
    std::array<GtkWidget*, 9*9> answer_labels;
    std::array<std::array<GtkWidget*, 9>, 9*9> memo_labels;
    std::array<GtkWidget*, 4> vertical_line;
    std::array<GtkWidget*, 4> horizontal_line;
    void set_memo(int x, int y, std::set<int> memo);
    void select(int x, int y);
    void deselect();
    static void on_cell_click(GtkWidget* sender, GdkEventButton *event, gpointer* user_data);
};


#endif //SUDOKU_PUZZLE_VIEW_H
