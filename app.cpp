//
// Created by hungr on 2020/02/23.
//

#include <gtk/gtk.h>
#include "app.h"

static GtkWidget* window;

std::vector<std::string> args;

void app::init(int *argc, char ***argv) {
    gtk_init(argc, argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 800, 600);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    for(int i = 0; i < *argc; i++) args.emplace_back((*argv)[i]);
}

void app::run() {
    gtk_main();
}
