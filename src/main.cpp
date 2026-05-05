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
    bool dragging = false;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE) running = false;
            // zooming
            if (event.type == SDL_EVENT_MOUSE_WHEEL && event.wheel.y > 0)
                content.zoomin(50);
            if (event.type == SDL_EVENT_MOUSE_WHEEL && event.wheel.y < 0)
                content.zoomout(50);
            // moving
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                dragging = true;
                SDL_HideCursor();
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
                dragging = false;
                SDL_ShowCursor();
            }

            if (dragging) {
                float x, y;
                SDL_GetMouseState(&x, &y);
                content.place_to(x, y);
            }
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