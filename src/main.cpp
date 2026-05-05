#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <content/img.h>

int main(int argv, char** argc) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WindowFlags flags =
        SDL_WINDOW_BORDERLESS    |
        SDL_WINDOW_ALWAYS_ON_TOP |
        SDL_WINDOW_TRANSPARENT;

    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    SDL_Rect bounds;
    SDL_GetDisplayBounds(display, &bounds);

    SDL_Window* window = SDL_CreateWindow("", bounds.w, bounds.h, flags);

    SDL_SetWindowPosition(window, 0, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    //SDL_SetRenderVSync(renderer, 1);

    bool running = true;
    SDL_Event event;

    auto content = img(renderer,"C:\\Users\\temal\\Downloads\\avatar.png");
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE) running = false;
            if (event.type == SDL_EVENT_MOUSE_WHEEL && event.wheel.y > 0)
                content.zoomin();
            if (event.type == SDL_EVENT_MOUSE_WHEEL && event.wheel.y < 0)
                content.zoomout();

        }

        // Transparent background (alpha = 0)
        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        content.put_image(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}