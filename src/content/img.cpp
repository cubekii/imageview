#include "img.h"

img::img(SDL_Renderer* renderer, std::string url) {

    texture = IMG_LoadTexture(renderer, url.c_str());

    float imgW, imgH;
    SDL_GetTextureSize(texture, &imgW, &imgH);

    int rendW, rendH;
    SDL_GetRenderOutputSize(renderer, &rendW, &rendH);

    rect = {
        (rendW - imgW) / 2.0f,
        (rendH - imgH) / 2.0f,
        imgW,
        imgH
    };
}

void img::zoomin() {
    rect.w+=10.0f;
    rect.h+=10.0f;
}

void img::zoomout() {
    rect.w-=10.0f;
    rect.h-=10.0f;
}

img::~img() {
    SDL_DestroyTexture(texture);
}

void img::put_image(SDL_Renderer *renderer) {
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
