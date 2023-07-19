#ifndef _PROJETIL_
#define _PROJETIL_
#include "GameObject.hpp"

class Projetil : public GameObject
{
public:
    Projetil(Vector2d pos);
    virtual void update();
    // virtual void render();
    virtual SDL_Rect *getRect() { return &rect; }
    bool isOut() { return out; }
    void setOut(bool b) { out = b; }
    virtual bool loadTexture(SDL_Renderer *renderer, std::string filePath);
    virtual void render(SDL_Renderer *renderer);
    virtual void clean();

protected:
    int width;
    int height;
    bool out = false;
    Vector2d pos;
    Vector2d velocidade;
    SDL_Rect rect;
};
#endif