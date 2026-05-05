#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
//#include <context/image.h>

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

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE) running = false;
        }

        // Transparent background (alpha = 0)
        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);


        SDL_Texture* texture = IMG_LoadTexture(renderer, "C:\\Users\\temal\\Downloads\\avatar.png");

        // Get image size
        float imgW, imgH;
        SDL_GetTextureSize(texture, &imgW, &imgH);

        // In the render loop, replace the rect drawing with:
        SDL_FRect rect = {
            (bounds.w - imgW) / 2.0f,
            (bounds.h - imgH) / 2.0f,
            imgW,
            imgH
        };
        SDL_RenderTexture(renderer, texture, nullptr, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}