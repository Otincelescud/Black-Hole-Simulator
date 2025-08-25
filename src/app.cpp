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
    add_to_surfaces("assets/3.png");
    add_to_surfaces("assets/2.png");
    // Initialize other resources if needed
}

void App::add_to_surfaces(const char* filepath) {
    appInfo->surfaces.push_back(loadImage(filepath));
    if (!appInfo->surfaces.back()) {
        std::cerr << "Failed to load image!" << std::endl;
    }
}

void App::remove_from_surfaces(std::size_t index) {
    if (index < appInfo->surfaces.size()) {
        unloadImage(appInfo->surfaces[index]);
        appInfo->surfaces.erase(appInfo->surfaces.begin() + index);
    }
    else {
        std::cerr << "Index out of bounds when trying to remove surface." << std::endl;
    }
}

void App::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                appInfo->index = (appInfo->index + 1) % appInfo->surfaces.size();
                //std::cout << "Switched to image index: " << appInfo->index << std::endl;
            }
            else if (event.key.keysym.sym == SDLK_LEFT) {
                appInfo->index = (appInfo->index - 1 + appInfo->surfaces.size()) % appInfo->surfaces.size();
                //std::cout << "Switched to image index: " << appInfo->index << std::endl;
            }
        }
        // Handle other events here
    }
}

bool App::is_running() {
    return running;
}

void App::update() {
    // Update application state here
}

void App::cleanup() {
    for (auto surface : appInfo->surfaces) {
        unloadImage(surface);
    }
    appInfo->surfaces.clear();
}

Uint32 render_test_img(const VectorN<int, 2>& px_pos, App_info* appInfo) {
    return getPixel(appInfo->surfaces[appInfo->index], px_pos, false);    
}

void App::render() {
    update_pixels_on_winSurf(render_test_img);
    //SDL_Delay(16); // Simulate frame delay (60 FPS)
    if (!running) {std::cout << "Application is stopping." << std::endl;}  
}

void App::update_pixels_on_winSurf(Uint32 (*updateFunc)(const VectorN<int, 2>& pos, App_info* appInfo)) {
    
    if (!winSurf) {
        std::cerr << "Window surface is null!" << std::endl;
        return;
    }

    if (winSurf->format->BytesPerPixel != 4) {
        std::cerr << " Window Surface must be 32bpp!" << std::endl;
        return;
    }

    // Lock the surface for pixel manipulation
    if (SDL_LockSurface(winSurf) < 0) {
        std::cerr << "Could not lock surface! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    VectorN<int, 2> p{0, 0};
    int& x = p[0];
    int& y = p[1];

    // Update pixels using the provided function
    Uint32* pixels = static_cast<Uint32*>(winSurf->pixels);
    for (y = 0; y < winSurf->h; ++y) {
        for (x = 0; x < winSurf->w; ++x) {
            pixels[y * winSurf->w + x] = updateFunc(p, appInfo);
        }
    }

    // Unlock the surface
    SDL_UnlockSurface(winSurf);

    // Update the window surface
    SDL_UpdateWindowSurface(window);
}

