#include "App.h"

int main(int argc, char **argv) {
    App::start(argc, argv);
    App::render();
    App::destroy();
    return 0;
}

