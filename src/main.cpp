#include <SDL3/SDL.h>

int main() {
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

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE) running = false;
        }

        // Transparent background (alpha = 0)
        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Red square
        SDL_SetRenderDrawColorFloat(renderer, 1.0f, 0.2f, 0.2f, 1.0f);
        SDL_FRect rect = { 100, 100, 100, 100 };
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}