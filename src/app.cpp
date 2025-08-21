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
    // Create Winsurface
    winSurf = SDL_GetWindowSurface(window);
    if (!winSurf) {
        std::cerr << "Could not get window surface! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    running = true;
}

App::~App() {
    delete appInfo;
    if (winSurf) {
        SDL_FreeSurface(winSurf);
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
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
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

void App::render() {
    update_pixels_on_winSurf(winSurf, [](int x, int y, App_info* appInfo) -> Uint32 {return 0x000000AA;}); // Example update function that fills the surface with black color
    SDL_UpdateWindowSurface(window);
    SDL_Delay(16); // Simulate frame delay (60 FPS)
    if (!running) {std::cout << "Application is stopping." << std::endl;}  
}

void App::update_pixels_on_winSurf(SDL_Surface* winSurf, Uint32 (*updateFunc)(int x, int y, App_info* appInfo)) {
    if (!winSurf) {
        std::cerr << "Window surface is null!" << std::endl;
        return;
    }

    // Lock the surface for pixel manipulation
    if (SDL_LockSurface(winSurf) < 0) {
        std::cerr << "Could not lock surface! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Update pixels using the provided function
    Uint32* pixels = static_cast<Uint32*>(winSurf->pixels);
    for (int y = 0; y < winSurf->h; ++y) {
        for (int x = 0; x < winSurf->w; ++x) {
            pixels[y * winSurf->w + x] = updateFunc(x, y, appInfo);
        }
    }

    // Unlock the surface
    SDL_UnlockSurface(winSurf);

    // Update the window surface
    SDL_UpdateWindowSurface(window);
}

