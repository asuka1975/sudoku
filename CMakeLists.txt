cmake_minimum_required(VERSION 3.15)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)
set(GTK_INCLUDE_PATHS /usr/include/gtk-3.0 /usr/include/at-spi2-atk/2.0 /usr/include/at-spi-2.0 /usr/include/dbus-1.0 /usr/lib/x86_64-linux-gnu/dbus-1.0/include /usr/include/gtk-3.0 /usr/include/gio-unix-2.0/ /usr/include/cairo /usr/include/pango-1.0 /usr/include/harfbuzz /usr/include/pango-1.0 /usr/include/atk-1.0 /usr/include/cairo /usr/include/pixman-1 /usr/include/freetype2 /usr/include/libpng16 /usr/include/freetype2 /usr/include/libpng16 /usr/include/gdk-pixbuf-2.0 /usr/include/libpng16 /usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include)

include_directories(${GTK_INCLUDE_PATHS} include)

add_executable(sudoku main.cpp app.cpp app.h styles/styles.h styles/styles.cpp mainwindow_view.h mainwindow_view.cpp puzzle_view.cpp puzzle_view.h puzzle_controller.cpp puzzle_controller.h puzzle_model.cpp puzzle_model.h history.cpp history.h mainwindow_controller.cpp mainwindow_controller.h puzzle.cpp puzzle.h)

target_link_libraries(sudoku -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0)