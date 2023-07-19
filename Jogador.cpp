#include "Jogador.hpp"
#include <cmath>
Jogador::Jogador()
{
    width = 30;
    height = 30;

    pos = Vector2d(SCREEN_WIDTH / 2 - ((int)width / 2), SCREEN_HEIGHT / 2 - ((int)height / 2));
    velocidade = Vector2d(0, 0);

    rect.h = height;
    rect.w = width;
    rect.x = pos.getX();
    rect.y = pos.getY();
}

void Jogador::update()
{
    Vector2d aux = mousePos - pos;
    float angleAux = -90 + std::atan2(aux.getY(), aux.getX()) * (180 / M_PI);
    angle = angleAux; // >= 0 ? angle : 360 + angleAux;
}

bool Jogador::loadTexture(SDL_Renderer *renderer, std::string filePath)
{
    SDL_Surface *tempSurface = IMG_Load(filePath.c_str());
    if (tempSurface == NULL)
    {
        std::cout << "Error loading surface: " << SDL_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    tempSurface = nullptr;

    return true;
}

void Jogador::render(SDL_Renderer *renderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = pos.getX();
    destRect.y = pos.getY();

    SDL_Point center;
    center.x = pos.getX();
    center.y = pos.getY();

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, SDL_FLIP_NONE);
}

void Jogador::clean()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}
