#include "app.h"

int main(int argc, char** argv)
{
    app::init(&argc, &argv);
    app::run();

    return 0;
}