#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class img {
private:
    std::string url;
    SDL_Texture* texture;
    SDL_FRect rect;
    float drag_offset_x = 0.0f;
    float drag_offset_y = 0.0f;
public:
    img(SDL_Renderer* renderer, std::string url);
    ~img();

    void zoomin();
    void zoomout();
    void zoomin(const float& speed);
    void zoomout(const float& speed);

    void begin_drag(const float& mx, const float& my);
    void place_to(const float& x, const float& y);
    void put_image(SDL_Renderer* renderer);

    bool in_image_box(const float& x, const float& y);
private:
    bool is_avaliable_size(const float& size);
};