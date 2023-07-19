#include "TextHandler.hpp"

bool TextHandler::loadFont()
{
    font = TTF_OpenFont("Arial.ttf", 28);
    if (font == NULL)
    {
        std::cout << "Falha ao inicializar fonte: "
                  << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

bool TextHandler::setText(std::string text, SDL_Renderer *renderer)
{
    SDL_Color txtColor = {255, 255, 255};

    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }

    SDL_Surface *txtSurface =
        TTF_RenderText_Solid(font, text.c_str(), txtColor);

    if (txtSurface == NULL)
    {
        std::cout << "Falhou inicializar superficie de texto"
                  << TTF_GetError() << std::endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, txtSurface);
    if (texture == NULL)
    {
        std::cout << "Falhou criar textura "
                  << TTF_GetError() << std::endl;
        return false;
    }
    width = txtSurface->w;
    height = txtSurface->h;
    SDL_FreeSurface(txtSurface);
    return true;
}

void TextHandler::render(int xpos, int ypos, SDL_Renderer *renderer, SDL_Rect *clip, double angle,
                         SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect rect = {xpos, ypos, width, height};
    if (clip != NULL)
    {
        rect.w = clip->w;
        rect.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
}

void TextHandler::clean()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
    TTF_CloseFont(font);
    font = nullptr;
}