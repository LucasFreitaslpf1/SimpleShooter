#pragma once
#ifndef _TEXTHANDLER_
#define _TEXTHANDLER_
#include "Utils.hpp"

class TextHandler
{
public:
    bool loadFont();
    void clean();
    void render(int xpos, int ypos, SDL_Renderer *renderer, SDL_Rect *clip = NULL, double angle = 0.0,
                SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    bool setText(std::string text, SDL_Renderer *renderer);

private:
    SDL_Texture *texture = nullptr;
    int width;
    int height;
    TTF_Font *font = nullptr;
};

#endif