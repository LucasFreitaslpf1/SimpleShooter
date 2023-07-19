#pragma once
#ifndef _GameObject_
#define _GameObject_
#include "Utils.hpp"
#include "Vector2d.hpp"

class GameObject
{
public:
    virtual bool loadTexture(SDL_Renderer *renderer, std::string filePath) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void clean() = 0;
    virtual SDL_Rect *getRect() = 0;

protected:
    SDL_Texture *texture = nullptr;
    int width;
    int height;
    Vector2d pos;
    Vector2d velocidade;
    SDL_Rect rect;
};

#endif // !GameObject
