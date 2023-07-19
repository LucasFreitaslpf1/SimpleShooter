#include "Game.hpp"

void Game::init(const char *titulo, const int xpos, const int ypos,
                int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Falhou em inicializar o SDL: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(titulo, xpos,
                              ypos, width, height, 0);
    if (window == NULL)
    {
        std::cout << "Falhou criar a janela: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        std::cout << "Falhou criar o renderer: " << SDL_GetError() << std::endl;
        return;
    }

    int flag = IMG_INIT_PNG;
    if (!(IMG_Init(flag) & flag))
    {
        std::cout << "Falhou inicializar SDL Image: " << IMG_GetError() << std::endl;
        return;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "Falha ao inicializar SDL TTF: " << TTF_GetError() << std::endl;
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        mouseButtonStates.push_back(false);
    }

    if (textHandler.loadFont())
    {
        std::cout << "FONTE CARREGADA\n";
    }
    jogador.loadTexture(renderer, "img/player.png");
    startButton.loadTexture(renderer, "img/start.png");
    retryButton.loadTexture(renderer, "img/retry.png");

    for (int i = 0; i < 3; i++)
    {
        gameStates.push_back(false);
    }
    running = true;
    gameStates[START] = true;
    score = 0;
}

void Game::gameOver()
{
    if (retryButton.isHover(mousePosition) &&
        mouseButtonStates[LEFT])
    {
        score = 0;
        gameStates[GAMEOVER] = false;
        gameStates[PLAY] = true;
        lastAction = SDL_GetTicks();
    }
}

void Game::gameOverRender()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    textHandler.setText("Voce perdeu! Pontuacao: " + std::to_string(score), renderer);
    textHandler.render(SCREEN_WIDTH / 2 - 100, 100, renderer);
    retryButton.render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::startMenu()
{
    if (startButton.isHover(mousePosition) &&
        mouseButtonStates[LEFT])
    {
        gameStates[START] = false;
        gameStates[PLAY] = true;
        lastAction = SDL_GetTicks();
    }
}

void Game::startMenuRender()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    textHandler.setText("Pressione Start!", renderer);
    textHandler.render(SCREEN_WIDTH / 2 - 100, 100, renderer);
    startButton.render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::update()
{
    if (gameStates[PLAY])
    {
        gameLoop();
        render();
    }

    if (gameStates[GAMEOVER])
    {
        gameOver();
        gameOverRender();
    }

    if (gameStates[START])
    {
        startMenu();
        startMenuRender();
    }
}

void Game::gameLoop()
{
    currentTime = SDL_GetTicks();
    jogador.setMousePos(mousePosition);
    jogador.update();

    if (getMouseButtonState(LEFT) &&
        (currentTime - lastAction >= delayTime))
    {
        lastAction = SDL_GetTicks();
        Vector2d target = mousePosition;
        projeteis.push_back(new Projetil(target));
    }

    for (int i = 0; i < projeteis.size(); i++)
    {
        projeteis[i]->update();
    }

    for (int i = 0; i < meteoros.size(); i++)
    {
        if (!(meteoros[i]->isOut()) &&
            meteoros[i]->collision(&jogador))
        {
            meteoroDelay = 1000;
            gameStates[PLAY] = false;
            gameStates[GAMEOVER] = true;
            clearMeteoros();
        }
        meteoros[i]->update();
    }

    if (currentTime - lastMeteor >= meteoroDelay)
    {
        lastMeteor = SDL_GetTicks();
        Meteoro *m = new Meteoro();
        m->setTexture(Meteoro::getTexture(renderer, "img/meteor.png"));
        meteoros.push_back(m);
    }

    for (int i = 0; i < projeteis.size(); i++)
    {
        if (!projeteis[i]->isOut())
            for (int j = 0; j < meteoros.size(); j++)
            {
                if (!meteoros[j]->isOut())
                {
                    if (meteoros[j]->collision(projeteis[i]))
                    {
                        projeteis[i]->setOut(true);
                        score += 1;
                    }
                }
            }
    }

    if (score >= 20 && score < 50)
    {
        meteoroDelay = 700;
    }

    if (score >= 50 && score < 70)
    {
        meteoroDelay = 600;
    }
    if (score >= 70 && score < 90)
    {
        meteoroDelay = 500;
    }
    if (score >= 90)
    {
        meteoroDelay = 400;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // RENDER JOGADOR
    jogador.render(renderer);

    // RENDER PROJETEIS
    SDL_SetRenderDrawColor(renderer, 200, 150, 80, 100);
    for (int i = 0; i < projeteis.size(); i++)
    {
        if (!projeteis[i]->isOut())
            SDL_RenderFillRect(renderer, projeteis[i]->getRect());
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < meteoros.size(); i++)
    {
        if (!meteoros[i]->isOut())
            // SDL_RenderFillRect(renderer, meteoros[i]->getRect());
            meteoros[i]->render(renderer);
    }
    textHandler.setText(scoreText + std::to_string(score), renderer);
    textHandler.render(600, 100, renderer);

    SDL_RenderPresent(renderer);
}

bool Game::getMouseButtonState(int mouseButton)
{
    return mouseButtonStates[mouseButton];
}

void Game::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseButtonStates[LEFT] = true;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE)
            {
                mouseButtonStates[MIDDLE] = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                mouseButtonStates[RIGHT] = true;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseButtonStates[LEFT] = false;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE)
            {
                mouseButtonStates[MIDDLE] = false;
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                mouseButtonStates[RIGHT] = false;
            }
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            mousePosition.setX(event.motion.x);
            mousePosition.setY(event.motion.y);
        }
    }
}

void Game::clearMeteoros()
{
    for (int i = 0; i < meteoros.size(); i++)
    {
        meteoros[i]->setOut(true);
    }
    for (int i = 0; i < projeteis.size(); i++)
    {
        projeteis[i]->setOut(true);
    }
}

void Game::clean()
{
    for (int i = 0; i < projeteis.size(); i++)
    {
        Projetil *p = projeteis[i];
        p->clean();
        delete p;
        p = nullptr;
    }

    for (int i = 0; i < meteoros.size(); i++)
    {
        Meteoro *m = meteoros[i];
        m->clean();
        delete m;
        m = nullptr;
    }

    retryButton.clean();
    startButton.clean();
    meteoros.clear();
    projeteis.clear();
    jogador.clean();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;
    textHandler.clean();
    SDL_Quit();
}