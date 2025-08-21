#include <SDL2/SDL.h>
#include <iostream>
#include "app.h"

int main(int argc, char* argv[]) {

    App* app = new App(800, 800, "Black Hole Simulator", false);
    app->init();

    while (app->is_running()) {
        app->handle_events();
        app->update();
        app->render();
    }

    app->cleanup();
    delete app;

    return 0;
}