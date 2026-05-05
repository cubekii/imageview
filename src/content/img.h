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
    ~img();
    void put_image(SDL_Renderer* renderer);
};

