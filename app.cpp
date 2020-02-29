//
// Created by hungr on 2020/02/23.
//

#include <cstring>
#include <memory>
#include <gtk/gtk.h>
#include "app.h"
#include "mainwindow_controller.h"
#include "styles/styles.h"

static void load_css();

std::vector<std::string> app::args;
static std::unique_ptr<mainwindow_controller> mainwindow;

void app::init(int *argc, char ***argv) {
    gtk_init(argc, argv);

    load_css();
    mainwindow = std::make_unique<mainwindow_controller>();
    for(int i = 0; i < *argc; i++) args.emplace_back((*argv)[i]);
}

void app::run() {
    gtk_main();
}

void load_css() {
    GtkCssProvider* provider = gtk_css_provider_new();
    GError* error;
    gtk_css_provider_load_from_data(provider, style_css, std::strlen(style_css), &error);
    if( error != nullptr ){
        g_print("can't read stylesheets.");
        return;
    }

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}