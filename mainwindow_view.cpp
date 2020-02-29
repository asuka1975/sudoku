//
// Created by hungr on 2020/02/25.
//

#include <cstring>
#include <iostream>
#include <string>
#include <gdk/gdk.h>
#include "mainwindow_view.h"
#include "mainwindow_view.h"

struct Initializer {
    const char* name;
    const char* label;
    const char* style;
    bool has_size;
    int width;
    int height;
    void(*callback)(GtkWidget*, gpointer*);
    Initializer(const char* name, const char* label, const char* style, void(*callback)(GtkWidget*, gpointer*), bool has_size, int width = 0, int height = 0) :
        name(name), label(label), style(style), callback(callback), has_size(has_size), width(width), height(height) {}
};

static void on_numpad_clicked(GtkWidget* sender, gpointer* user_data);
static void on_new_clicked(GtkWidget* sender, gpointer* user_data);
static void on_restart_clicked(GtkWidget* sender, gpointer* user_data);
static void on_memo_clicked(GtkWidget* sender, gpointer* user_data);
static void on_answer_clicked(GtkWidget* sender, gpointer* user_data);
static void on_undo_clicked(GtkWidget* sender, gpointer* user_data);
static void on_redo_clicked(GtkWidget* sender, gpointer* user_data);
static void on_clear_clicked(GtkWidget* sender, gpointer* user_data);

Initializer initializers[7] = {
        Initializer("new", "new", "sys-button", on_new_clicked,  false),
        Initializer("restart", "restart", "sys-button", on_restart_clicked, false),
        Initializer("memo", "memo:OFF", "sys-button", on_memo_clicked, false),
        Initializer("answer", "answer", "sys-button", on_answer_clicked, false),
        Initializer("undo", "⟲", "sys-button", on_undo_clicked, false),
        Initializer("redo", "⟳", "sys-button", on_redo_clicked, false),
        Initializer("clear", "Clear", "num-button", on_clear_clicked, true, 180, 60)
};

mainwindow_view::mainwindow_view(puzzle_view& content) : on_numpad_clicked() {
    init_widgets();
    init_layout();
    content.layout_this_to_container(this->content);
    gtk_widget_show_all(window);
}

void mainwindow_view::init_widgets() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    fixed = gtk_fixed_new();
    gtk_widget_set_size_request(window, 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    for(int i = 0; i < number_buttons.size(); i++) {
        number_buttons[i] = gtk_button_new_with_label(std::to_string(i+1).data());
        gtk_widget_set_size_request(number_buttons[i], 60, 60);
        GtkStyleContext *context = gtk_widget_get_style_context(number_buttons[i]);
        gtk_style_context_add_class(context,"num-button");
        g_signal_connect(number_buttons[i], "clicked", G_CALLBACK(::on_numpad_clicked), this);
    }
    for(auto initializer : initializers) {
        system_buttons[initializer.name] = gtk_button_new_with_label(initializer.label);
        GtkStyleContext *context = gtk_widget_get_style_context(system_buttons[initializer.name]);
        gtk_style_context_add_class(context,initializer.style);
        g_signal_connect(system_buttons[initializer.name], "clicked", G_CALLBACK(initializer.callback), this);
        if(initializer.has_size)
            gtk_widget_set_size_request(system_buttons[initializer.name], initializer.width, initializer.height);
    }

    numpad = gtk_grid_new();
    content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
}

void mainwindow_view::init_layout() {
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_fixed_put(GTK_FIXED(fixed), hbox, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), system_buttons["new"], 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), system_buttons["restart"], 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), system_buttons["memo"], 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), system_buttons["answer"], 0, 0, 0);

    gtk_fixed_put(GTK_FIXED(fixed), numpad, 580, 150);
    gtk_grid_set_row_spacing(GTK_GRID(numpad), 1);
    gtk_grid_set_column_spacing(GTK_GRID(numpad), 1);
    for (int i = 0; i < number_buttons.size(); i++)
        gtk_grid_attach(GTK_GRID(numpad), number_buttons[i], i % 3, i / 3, 1, 1);
    gtk_grid_attach(GTK_GRID(numpad), system_buttons["clear"], 0, 3, 3, 1);
    gtk_grid_attach(GTK_GRID(numpad), system_buttons["undo"], 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(numpad), system_buttons["redo"], 2, 4, 1, 1);

    gtk_fixed_put(GTK_FIXED(fixed), content, 40, 40);
}

bool mainwindow_view::is_memo() const noexcept {
    std::string label = gtk_button_get_label(GTK_BUTTON(system_buttons.at("memo")));
    return label == "memo:ON";
}

static void on_numpad_clicked(GtkWidget* sender, gpointer* user_data) {
    auto* view = (mainwindow_view*)user_data;
    int label = std::stoi(gtk_button_get_label(GTK_BUTTON(sender)));
    view->on_numpad_clicked(view, label);
}

void on_new_clicked(GtkWidget *sender, gpointer *user_data) {
    auto* view = (mainwindow_view*)user_data;
    view->on_new_clicked(sender, nullptr);
}

void on_restart_clicked(GtkWidget *sender, gpointer *user_data) {
    auto* view = (mainwindow_view*)user_data;
    view->on_restart_clicked(sender, nullptr);
}

void on_memo_clicked(GtkWidget *sender, gpointer *user_data) {
    if(!std::strcmp(gtk_button_get_label(GTK_BUTTON(sender)), "memo:OFF")) gtk_button_set_label(GTK_BUTTON(sender), "memo:ON");
    else gtk_button_set_label(GTK_BUTTON(sender), "memo:OFF");
    auto* view = (mainwindow_view*)user_data;
    view->on_memo_clicked(sender, nullptr);
}

void on_answer_clicked(GtkWidget *sender, gpointer *user_data) {
    auto* view = (mainwindow_view*)user_data;
    view->on_answer_clicked(sender, nullptr);
}

void on_undo_clicked(GtkWidget *sender, gpointer *user_data) {
    auto* view = (mainwindow_view*)user_data;
    view->on_undo_clicked(sender, nullptr);
}

void on_redo_clicked(GtkWidget *sender, gpointer *user_data) {
    auto* view = (mainwindow_view*)user_data;
    view->on_redo_clicked(sender, nullptr);
}

static void on_clear_clicked(GtkWidget* sender, gpointer* user_data) {
    auto* view = (mainwindow_view*)user_data;
    view->on_clear_clicked(sender, nullptr);
}

