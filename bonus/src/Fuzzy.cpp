/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Fuzzy
*/

#include "Fuzzy.hpp"

#include <iostream>
#include <memory>

#include "Assets.hpp"
/* 
#include "../lib/Ncurses/NCurses.hpp" */

Fuzzy::Fuzzy::Fuzzy(const std::string map, SDL::Vector2i size) :
    _window("FuzzyCar", size, Assets::ICON),
    _level(_window, "assets/background.png", {339, 563, 788}, map, true),
    _player(_window, _level.getRealPosition(_level.getPlayerPosition()))
{

    for (auto &enemyPosition : _level.getEnemiesPositions()) {
        _enemies.push_back(EntityCar(_window, _level.getRealPosition(enemyPosition)));
    }

    _fpsText.load(std::to_string(FPS), Assets::ROBOTO_FONT, { 255, 0, 0 });

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "FuzzyCar" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Project version: " << VERSION << std::endl;
    std::cout << "SDL2 version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Window size: " << size.x << "x" << size.y << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "FPS: " << FPS << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void Fuzzy::Fuzzy::launch()
{
    float elapsedMS = 0.0f;
    Uint64 frameStart = 0;
    Uint64 frameTime = 0;

    //Assets::SOUNDTRACK.play();

    SDL::Vector2i playerPosition = _player.getPosition();
/* 
    SDL_Rect rect = {0, 0, 512, 512};
    SDL_RenderSetClipRect(_window.getRenderer(), &rect); */
    //clock_t start = NCurses::Core::GetClock();

    while (_window.isOpen()) {
        frameStart = SDL::Core::GetTicks();
        
        handleEvents();
        update();
        draw();

        frameTime = SDL::Core::GetTicks() - frameStart;
        int frameDelay = 1000 / FPS;
        if (frameDelay > frameTime)
            SDL::Core::Delay(frameDelay - frameTime);
    }
}

void Fuzzy::Fuzzy::handleEvents()
{
    SDL::Event e;
    SDL_Rect rect;
    while (e.poll() > 0) {
        switch (e->type) {
        case SDL_QUIT:
            _window.close();
            break;
        case SDL_KEYDOWN:
            _player.consume(e);
            switch (e->key.keysym.sym) {
                case SDLK_UP:
                    _level.getRoad().setPosition(SDL::Vector2i(_level.getRoad().getPosition().x, _level.getRoad().getPosition().y - 1));
                    break;
                case SDLK_DOWN:
                    _level.getRoad().setPosition(SDL::Vector2i(_level.getRoad().getPosition().x, _level.getRoad().getPosition().y + 1));
                    break;
                case SDLK_l:
                    Assets::SOUNDTRACK.pause();
                    break;
                case SDLK_m:
                    Assets::SOUNDTRACK.play();
                    break;
            }
            break;
        default:
            break;
        }
    }
}

void Fuzzy::Fuzzy::update()
{
    _level.update();
    _player.update(_level);
}

void Fuzzy::Fuzzy::draw()
{
    _window.clear();
    
    _level.render(_window);
    _player.render(_window);

    for (auto &enemy : _enemies) {
        enemy.render(_window);
    }

    SDL::Sprite texture;
    texture.load(_window, _fpsText, {0, 0, 100, 64});
    texture.setPosition(SDL::Vector2i(10, 10));
    texture.setSize(SDL::Vector2i(80, 80));
    texture.draw();

    _window.display();
}