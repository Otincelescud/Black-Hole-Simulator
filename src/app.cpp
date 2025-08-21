#include "app.h"

App::App(int winW, int winH, const char* winTitle, bool fullscreen)
    : appInfo(new App_info{winW, winH, winTitle, fullscreen}) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    // Create window
    Uint32 flags = SDL_WINDOW_SHOWN;
    if (appInfo->fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    window = SDL_CreateWindow(appInfo->winTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, appInfo->winW, appInfo->winH, flags);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    running = true;
}

App::~App() {
    delete appInfo;
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void App::init() {
    // init stuff if needed
}

void App::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        // Handle other events here
    }
}

bool App::is_running() const {
    return running;
}

void App::update() {
    // Update application state here
}

void App::cleanup() {
    // Cleanup resources if needed
}

void App::render() {}