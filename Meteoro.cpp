#include "Meteoro.hpp"
#include <random>

SDL_Texture *Meteoro::staticTexture = nullptr;

Meteoro::Meteoro()
{
    unsigned int seed = (unsigned)SDL_GetTicks();
    std::random_device rd;
    std::mt19937 gen(seed);
    int direction = (int)SDL_GetTicks() % 4;
    std::uniform_int_distribution<> dis(1, SCREEN_HEIGHT);

    switch (direction)
    {
    case 0: // ESQUERDA
        pos.setX(0);
        dis.param(std::uniform_int_distribution<>::param_type(1, SCREEN_HEIGHT));
        pos.setY(dis(gen));
        break;
    case 1: // DIREITA
        pos.setX(SCREEN_WIDTH);
        dis.param(std::uniform_int_distribution<>::param_type(1, SCREEN_HEIGHT));
        pos.setY(dis(gen));
        break;
    case 2: // CIMA
        pos.setY(0);
        dis.param(std::uniform_int_distribution<>::param_type(1, SCREEN_WIDTH));
        pos.setX(dis(gen));
        break;
    case 3: // BAIXO
        pos.setY(SCREEN_HEIGHT);
        dis.param(std::uniform_int_distribution<>::param_type(1, SCREEN_WIDTH));
        pos.setX(dis(gen));
        break;
    }

    dis.param(std::uniform_int_distribution<>::param_type(10, MAXSIZE));
    width = height = dis(gen);

    rect.w = width;
    rect.h = height;
    rect.x = pos.getX();
    rect.y = pos.getY();
    Vector2d centro(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    velocidade = centro - pos;
    velocidade.normalize();
    velocidade *= 3;
}

bool Meteoro::collision(GameObject *gameObject)
{
    // cima = y
    // baixo = y + height
    // esquerda = x
    // direita = x + width
    SDL_Rect *alvo = gameObject->getRect();
    if (alvo->x <= (rect.x + width) &&   // Alvo esquerda <> Meteoro direita
        (alvo->x + alvo->w) >= rect.x && // Alvo direita <> Meteoro esquerda
        alvo->y <= (rect.y + height) &&  // Alvo cima <> Meteoro baixo
        (alvo->y + alvo->h) >= rect.y)   // Alvo baixo <> Meteoro cima
    {
        out = true;
        return true;
    }
    return false;
}

void Meteoro::render(SDL_Renderer *renderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = MAXSIZE;
    srcRect.h = MAXSIZE;
    destRect.w = width;
    destRect.h = height;
    destRect.x = pos.getX();
    destRect.y = pos.getY();

    SDL_Point center;
    center.x = pos.getX();
    center.y = pos.getY();

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Meteoro::clean()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void Meteoro::update()
{
    pos += velocidade;
    rect.x = pos.getX();
    rect.y = pos.getY();
}

bool Meteoro::loadTexture(SDL_Renderer *renderer, std::string filePath)
{
}

SDL_Texture *Meteoro::getTexture(SDL_Renderer *renderer, std::string filePath)
{
    if (staticTexture != nullptr)
    {
        return staticTexture;
    }

    SDL_Surface *tempSurface = IMG_Load(filePath.c_str());
    if (tempSurface == NULL)
    {
        std::cout << "Error loading surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    staticTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    tempSurface = nullptr;

    return staticTexture;
}