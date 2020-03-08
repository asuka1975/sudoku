//
// Created by hungr on 2020/02/25.
//

#include <gdk/gdk.h>

#include "puzzle_view.h"

puzzle_view::puzzle_view(const puzzle_model& model) : model(model) {
    GtkStyleContext *context;
    puzzle = gtk_fixed_new();
    context = gtk_widget_get_style_context(puzzle);
    gtk_style_context_add_class(context,"puzzle-border");
    gtk_widget_set_size_request(puzzle, 486, 486);
    for(int i = 0; i < 81; i++) {
        eventboxes[i] = gtk_event_box_new();
        gtk_widget_set_size_request(eventboxes[i], 54, 54);
        gtk_widget_set_name(eventboxes[i], std::to_string(i).data());
        g_signal_connect(eventboxes[i], "button_press_event", G_CALLBACK(puzzle_view::on_cell_click), this);
        cells[i] = gtk_fixed_new();
        gtk_widget_set_size_request(cells[i], 54, 54);

        answer_labels[i] = gtk_label_new("");
        gtk_widget_set_size_request(answer_labels[i], 54, 54);
        context = gtk_widget_get_style_context(answer_labels[i]);
        gtk_style_context_add_class(context,"answer-style");

        for(int j = 0; j < 9; j++) {
            memo_labels[i][j] = gtk_label_new("");
            gtk_widget_set_size_request(memo_labels[i][j], 18, 18);
            context = gtk_widget_get_style_context(memo_labels[i][j]);
            gtk_style_context_add_class(context, "memo-font");
            gtk_label_set_label(GTK_LABEL(memo_labels[i][j]), "");
        }
    }

    complete_label = gtk_label_new("");
    gtk_widget_set_size_request(complete_label, 486, 16);

    for(int i = 0; i < 4; i++) {
        vertical_line[i] = gtk_label_new("");
        gtk_widget_set_size_request(vertical_line[i], 2, 488);
        context = gtk_widget_get_style_context(vertical_line[i]);
        gtk_style_context_add_class(context, "line-style");
        horizontal_line[i] = gtk_label_new("");
        gtk_widget_set_size_request(horizontal_line[i], 488, 2);
        context = gtk_widget_get_style_context(horizontal_line[i]);
        gtk_style_context_add_class(context, "line-style");
    }
}

void puzzle_view::layout_this_to_container(GtkWidget *container) {
    for(int i = 0; i < 81; i++) {
        gtk_fixed_put(GTK_FIXED(puzzle), eventboxes[i], i % 9 * 54, i / 9 * 54);
        gtk_container_add(GTK_CONTAINER(eventboxes[i]), cells[i]);
        gtk_fixed_put(GTK_FIXED(cells[i]), answer_labels[i], 0, 0);
        for(int j = 0; j < 9; j++) {
            gtk_fixed_put(GTK_FIXED(cells[i]), memo_labels[i][j], (j % 3) * 18, (j / 3) * 18);
        }
    }
    gtk_box_pack_start(GTK_BOX(container), puzzle, 0, 1, 0);
    gtk_box_pack_start(GTK_BOX(container), complete_label, 0, 1, 0);

    for(int i = 0; i < 4; i++) {
        gtk_fixed_put(GTK_FIXED(puzzle), vertical_line[i], i*54*3, 0);
        gtk_fixed_put(GTK_FIXED(puzzle), horizontal_line[i], 0, i*54*3);
    }
}

void puzzle_view::update() {
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (int answer = model.get_answer(i, j); model.get_answer(i, j))
                gtk_label_set_label(GTK_LABEL(answer_labels[i + j * 9]), std::to_string(answer).data());
            else
                gtk_label_set_label(GTK_LABEL(answer_labels[i + j * 9]), "");
            set_memo(i, j, model.get_memo(i, j));
            GtkStyleContext* context = gtk_widget_get_style_context(answer_labels[i + j * 9]);
            if(!model.is_valid(i, j)) {
                gtk_style_context_remove_class(context, "question-number");
                gtk_style_context_remove_class(context, "valid-number");
                gtk_style_context_add_class(context, "invalid-number");
            } else {
                if(model.is_question(i, j)) {
                    gtk_style_context_remove_class(context, "invalid-number");
                    gtk_style_context_remove_class(context, "valid-number");
                    gtk_style_context_add_class(context, "question-number");
                } else {
                    gtk_style_context_remove_class(context, "invalid-number");
                    gtk_style_context_remove_class(context, "question-number");
                    gtk_style_context_add_class(context, "valid-number");
                }
            }
        }
    }
    auto complete = model.get_complete();
    std::string label = "";
    for(int i = 0; i < 9; i++) label += (complete[i] ? std::to_string(i + 1) : " ") + " ";
    gtk_label_set_label(GTK_LABEL(complete_label), label.data());
}

void puzzle_view::on_cell_click(GtkWidget* sender, GdkEventButton *event, gpointer* user_data) {
    puzzle_view* view = (puzzle_view*)user_data;
    int index = std::atoi(gtk_widget_get_name(sender));
    view->deselect();
    view->select(index % 9, index / 9);
    view->on_click(view, std::pair<int, int>(index % 9, index / 9));
}

void puzzle_view::select(int x, int y) {
    GtkStyleContext* context;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            context = gtk_widget_get_style_context(answer_labels[(x / 3) * 3 + i + ((y / 3) * 3 + j) * 9]);
            gtk_style_context_add_class(context, "neighbor-style");
        }
    }
    for(int i = 0; i < 9; i++) {
        context = gtk_widget_get_style_context(answer_labels[x + i * 9]);
        gtk_style_context_add_class(context, "neighbor-style");
        context = gtk_widget_get_style_context(answer_labels[i + y * 9]);
        gtk_style_context_add_class(context, "neighbor-style");
    }
    context = gtk_widget_get_style_context(answer_labels[x + y * 9]);
    gtk_style_context_remove_class(context, "neighbor-style");
    gtk_style_context_add_class(context, "selection-style");
    int label = std::atoi(gtk_label_get_label(GTK_LABEL(answer_labels[x + y * 9])));
    if(label == 0) return;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(!(x == i && y == j) && label == std::atoi(gtk_label_get_label(GTK_LABEL(answer_labels[i + j * 9])))) {
                context = gtk_widget_get_style_context(answer_labels[i + j * 9]);
                gtk_style_context_remove_class(context, "neighbor-style");
                gtk_style_context_add_class(context, "same-style");
            }
        }
    }
}

void puzzle_view::deselect() {
    GtkStyleContext* context;
    for(int i = 0; i < 81; i++) {
        context = gtk_widget_get_style_context(answer_labels[i]);
        gtk_style_context_remove_class(context, "neighbor-style");
        gtk_style_context_remove_class(context, "selection-style");
        gtk_style_context_remove_class(context, "same-style");
    }
}

void puzzle_view::set_memo(int x, int y, std::set<int> memo) {
    for(int i = 0; i < 9; i++) gtk_label_set_label(GTK_LABEL(memo_labels[x + y * 9][i]), "");
    for(int m : memo) {
        gtk_label_set_label(GTK_LABEL(memo_labels[x + y * 9][m - 1]), std::to_string(m).data());
    }
}
