#ifndef App_h
#define App_h

#include <SDL2/SDL.h>
#include <iostream>

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
    SDL_Renderer* renderer = nullptr;
    App_info* appInfo = nullptr;
    bool running = false;
};

#endif // App_h