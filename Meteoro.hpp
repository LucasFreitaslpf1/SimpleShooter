#ifndef _METEORO_
#define _METEORO_
#include "GameObject.hpp"
#define MAXSIZE 100

class Meteoro : public GameObject
{
public:
    Meteoro();
    ~Meteoro() {}
    virtual void update();
    // virtual void render();
    virtual SDL_Rect *getRect() { return &rect; }
    bool collision(GameObject *gameObject);
    int getId() { return id; }
    bool isOut() { return out; }
    void setOut(bool b) { out = b; }
    virtual void render(SDL_Renderer *renderer);
    virtual bool loadTexture(SDL_Renderer *renderer, std::string filePath);
    virtual void clean();
    void setTexture(SDL_Texture *_texture) { texture = _texture; }
    static SDL_Texture *getTexture(SDL_Renderer *renderer, std::string filePath);

protected:
    int id;
    int width;
    int height;
    bool out;
    Vector2d pos;
    Vector2d velocidade;
    SDL_Rect rect;
    static SDL_Texture *staticTexture;
};
#endif