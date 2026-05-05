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

bool img::is_avaliable_size(const float &size) {
    return rect.h-size > 0.0f || rect.w-size > 0.0f;
}

void img::zoomin() {
    rect.x-=5.0f;
    rect.y-=5.0f;
    rect.w+=10.0f;
    rect.h+=10.0f;
}

void img::zoomout() {
    if (!img::is_avaliable_size(10.0f))
        return;
    rect.x+=5.0f;
    rect.y+=5.0f;
    rect.w-=10.0f;
    rect.h-=10.0f;
}

void img::zoomin(const float& speed) {
    rect.x-=speed/2.0f;
    rect.y-=speed/2.0f;
    rect.w+=speed;
    rect.h+=speed;
}
void img::zoomout(const float& speed) {
    if (!is_avaliable_size(10.0f))
        return;
    rect.x+=speed/2.0f;
    rect.y+=speed/2.0f;
    rect.w-=speed;
    rect.h-=speed;
}

void img::place_to(const int& x, const int& y, const int& rel_x, const int& rel_y) {
    if (!in_image_box(x,y))
        return;
    rect.x = x - rel_x;
    rect.y = y - rel_y;
}

bool img::in_image_box(const int&x, const int&y) {
    float imgW, imgH;
    SDL_GetTextureSize(texture, &imgW, &imgH);
    return ((rect.x <= x && rect.x + rect.w >= x) && (rect.y <= y && rect.y + rect.h >= y));
}

img::~img() {
    SDL_DestroyTexture(texture);
}

void img::put_image(SDL_Renderer *renderer) {
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
