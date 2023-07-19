#include "MenuButton.hpp"

MenuButton::MenuButton()
{
    width = 200;
    height = 100;

    pos = Vector2d(SCREEN_WIDTH / 2 - ((int)width / 2), (SCREEN_HEIGHT)*0.75);

    rect.h = height;
    rect.w = width;
    rect.x = pos.getX();
    rect.y = pos.getY();
}

bool MenuButton::isHover(Vector2d &mousePos)
{
    if (mousePos.getX() >= pos.getX() &&
        mousePos.getX() <= (pos.getX() + width) &&
        mousePos.getY() >= pos.getY() &&
        mousePos.getY() <= pos.getY() + height)
    {
        return true;
    }
    return false;
}

void MenuButton::update()
{
}

void MenuButton::render(SDL_Renderer *renderer)
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

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void MenuButton::clean()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

bool MenuButton::loadTexture(SDL_Renderer *renderer, std::string filePath)
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
