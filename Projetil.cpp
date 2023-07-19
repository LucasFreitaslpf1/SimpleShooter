#include "Projetil.hpp"

Projetil::Projetil(Vector2d mpos)
{
    width = 15;
    height = 15;

    pos = Vector2d(SCREEN_WIDTH / 2 - ((int)width / 2), SCREEN_HEIGHT / 2 - ((int)height / 2));
    velocidade = mpos - pos;
    velocidade.normalize();
    velocidade *= 3;

    rect.h = height;
    rect.w = width;
    rect.x = pos.getX();
    rect.y = pos.getY();
}

void Projetil::render(SDL_Renderer *renderer) {}
void Projetil::clean() {}

void Projetil::update()
{
    pos += velocidade;
    rect.x = pos.getX();
    rect.y = pos.getY();

    if (pos.getX() > SCREEN_WIDTH && pos.getY() > SCREEN_HEIGHT)
    {
        out = true;
    }
}

bool Projetil::loadTexture(SDL_Renderer *renderer, std::string filePath) {}