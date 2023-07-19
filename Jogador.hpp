#ifndef _JOGADOR_
#define _JOGADOR_
#include "GameObject.hpp"

class Jogador : public GameObject
{
public:
    Jogador();
    virtual void update();
    virtual void render(SDL_Renderer *renderer);
    virtual SDL_Rect *getRect() { return &rect; }
    virtual bool loadTexture(SDL_Renderer *renderer, std::string filePath);
    void clean();
    void setMousePos(Vector2d _mousePos) { mousePos = _mousePos; }

protected:
    SDL_Texture *texture = nullptr;
    int width;
    int height;
    Vector2d pos;
    Vector2d velocidade;
    Vector2d mousePos;
    SDL_Rect rect;
    float angle = 0.f;
};
#endif