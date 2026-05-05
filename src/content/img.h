#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class img {
private:
    std::string url;
    SDL_Texture* texture;
    SDL_FRect rect;
public:
    img(SDL_Renderer* renderer,std::string url);

    void zoomin();
    void zoomout();
    void zoomin(const float& speed);
    void zoomout(const float& speed);

    void place_to(const int& x, const int& y);
    ~img();
    void put_image(SDL_Renderer* renderer);
private:
    bool is_avaliable_size(const float& size);
};

