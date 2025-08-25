#ifndef App_h
#define App_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vectorN.h"
#include "graphics.h"
#include <iostream>
#include <vector>

struct App_info {
    // Window properties
    const int winW, winH;
    const char* winTitle;
    bool fullscreen;

    int index = 0;

    // Surfaces
    std::vector<SDL_Surface*> surfaces; // Store loaded surfaces
    
};

class App {
public:
    App(int winW, int winH, const char* winTitle, bool fullscreen);
    ~App();
    void init();
    bool is_running();
    void handle_events();
    void update();
    void render();
    void cleanup();

private:
    SDL_Window* window = nullptr;
    SDL_Surface* winSurf = nullptr;
    App_info* appInfo = nullptr;
    bool running = false;

    void update_pixels_on_winSurf(Uint32 (*updateFunc)(const VectorN<int, 2>& pos, App_info* appInfo));
    void add_to_surfaces(const char* filepath);
    void remove_from_surfaces(std::size_t index);
};

Uint32 render_test_img(const VectorN<int, 2>& px_pos, App_info* appInfo);

#endif // App_h

// mouser
// jlcpcb