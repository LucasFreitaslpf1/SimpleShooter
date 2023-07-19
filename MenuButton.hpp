#pragma once
#ifndef _MENUBUTTON_
#define _MENUBUTTON_
#include "GameObject.hpp"

class MenuButton : public GameObject
{
public:
    MenuButton();
    virtual bool loadTexture(SDL_Renderer *renderer, std::string filePath);
    virtual void update();
    virtual void render(SDL_Renderer *renderer);
    virtual void clean();
    bool isHover(Vector2d &mousePos);
    SDL_Rect *getRect() { return &rect; }
    void setCallBack(void (*_callback)()) { callback = _callback; }

protected:
    SDL_Texture *texture = nullptr;
    int width;
    int height;
    Vector2d pos;
    SDL_Rect rect;
    void (*callback)();
};

#endif