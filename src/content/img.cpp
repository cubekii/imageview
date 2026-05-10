#include "img.h"

void img::render(SDL_Renderer* renderer, std::string url) {
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

img::img(SDL_Renderer *renderer, std::string url) {
    render(renderer, url);
}

bool img::is_avaliable_size(const float& factor) {
    return (rect.w / factor) > 10.0f && (rect.h / factor) > 10.0f;
}

void img::zoomin() {
    rect.x -= 5.0f;
    rect.y -= 5.0f;
    rect.w += 10.0f;
    rect.h += 10.0f;
}

void img::zoomout() {
    if (!is_avaliable_size(10.0f))
        return;
    rect.x += 5.0f;
    rect.y += 5.0f;
    rect.w -= 10.0f;
    rect.h -= 10.0f;
}

void img::zoomin(const float& speed) {
    float aspect = rect.w / rect.h;
    float dh = speed;
    float dw = speed * aspect;

    rect.x -= dw / 2.0f;
    rect.y -= dh / 2.0f;
    rect.w += dw;
    rect.h += dh;
}

void img::zoomout(const float& speed) {
    if (!is_avaliable_size(10.0f))
        return;

    float aspect = rect.w / rect.h;
    float dh = speed;
    float dw = speed * aspect;

    rect.x += dw / 2.0f;
    rect.y += dh / 2.0f;
    rect.w -= dw;
    rect.h -= dh;
}

void img::begin_drag(const float& mx, const float& my) {
    drag_offset_x = mx - rect.x;
    drag_offset_y = my - rect.y;
}

void img::place_to(const float& x, const float& y) {
    rect.x = x - drag_offset_x;
    rect.y = y - drag_offset_y;
}

bool img::in_image_box(const float& x, const float& y) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

img::~img() {
    SDL_DestroyTexture(texture);
}

void img::put_image(SDL_Renderer* renderer) {
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}