#ifndef App_h
#define App_h

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

struct App_info {
    // Window properties
    const int winW, winH;
    const char* winTitle;
    bool fullscreen;
};

class App {
public:
    App(int winW, int winH, const char* winTitle, bool fullscreen);
    ~App();
    void init();
    bool is_running() const;
    void handle_events();
    void update();
    void render();
    void cleanup();

private:
    SDL_Window* window = nullptr;
    SDL_Surface* winSurf = nullptr;
    App_info* appInfo = nullptr;
    bool running = false;
    std::vector<SDL_Surface*> surfaces;

    void update_pixels_on_winSurf(SDL_Surface* winSurf, Uint32 (*updateFunc)(int x, int y, App_info* appInfo));
};

#endif // App_h

// mouser
// jlcpcb