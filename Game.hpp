#pragma once
#ifndef GAME
#define GAME
#include "Utils.hpp"
#include "Jogador.hpp"
#include "Projetil.hpp"
#include "Meteoro.hpp"
#include "TextHandler.hpp"
#include "MenuButton.hpp"

class Game
{
public:
    void init(const char *titulo, const int xpos, const int ypos,
              int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);

    void clean();
    bool isRunning() { return running; }
    void gameLoop();
    void render();
    void handleEvents();
    bool getMouseButtonState(int mouseButton);
    void gameOver();
    void gameOverRender();
    void startMenu();
    void startMenuRender();
    void update();
    void clearMeteoros();

private:
    bool running = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Jogador jogador;
    Vector2d mousePosition;
    std::vector<bool> mouseButtonStates;
    std::vector<Projetil *> projeteis;
    std::vector<Meteoro *> meteoros;
    Uint32 lastAction = 0, currentTime;
    Uint32 delayTime = 350;
    Uint32 meteoroDelay = 1000;
    Uint32 lastMeteor = 0;
    int score;
    std::string scoreText = "Score: ";
    TextHandler textHandler;
    std::vector<bool> gameStates;
    MenuButton startButton;
    MenuButton retryButton;
    enum mouse_buttons
    {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2,
    };

    enum game_state
    {
        PLAY = 0,
        GAMEOVER = 1,
        START = 2,
    };
};

#endif // !GAME