#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <content/img.h>
#include <content/listdir.h>

int main(int argc, char* argv[]) {
    if (argc<2) {
        SDL_Log("No arguments provided");
        return 0;
    }
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WindowFlags flags =
        SDL_WINDOW_BORDERLESS    |
        SDL_WINDOW_TRANSPARENT;

    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    SDL_Rect bounds;
    SDL_GetDisplayBounds(display, &bounds);

    SDL_Window* window = SDL_CreateWindow("", bounds.w, bounds.h, flags);
    SDL_SetWindowPosition(window, 0, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    bool running = true;
    SDL_Event event;

    auto current_dir = listdir(argv[1]);
    auto content = img(renderer, current_dir.get_current_file());
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
            //scroll content
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_L)
                content.render(renderer, current_dir.scroll_up());

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_H)
                content.render(renderer, current_dir.scroll_down());

            // moving
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
                event.button.button == SDL_BUTTON_LEFT && !dragging) {
                float mx, my;
                SDL_GetMouseState(&mx, &my);
                if (content.in_image_box(mx, my)) {
                    SDL_HideCursor();
                    dragging = true;
                    content.begin_drag(mx, my);
                }
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP &&
                event.button.button == SDL_BUTTON_LEFT && dragging) {
                dragging = false;
                SDL_ShowCursor();
            }

            if (dragging) {
                float x, y;
                SDL_GetMouseState(&x, &y);
                content.place_to(x, y);
            }
        }

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