/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Fuzzy
*/

#include "Fuzzy.hpp"

#include <iostream>
#include <memory>

Fuzzy::Fuzzy::Fuzzy(SDL::Vector2i size) :
    _window("FuzzyCar", size)
    /* ,
    _player("assets/cars/blue.png", {10, 10, 16, 16}, SDL::Vector2i(64, 64), true) */
{
    // Background
    _background.load(_window, Assets::BACKGROUND);
    _background.setPosition(SDL::Vector2i(0, 0));
    _background.setSize(size);

    // Player
    _player.load(_window, Assets::BLUE_CAR, {0, 0, 16, 16});
    _player.setPosition(SDL::Vector2i(size.x / 4, size.y - 64));
    _player.setSize(SDL::Vector2i(64, 64));

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

    Assets::SOUNDTRACK.play();
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
    while (e.poll() > 0) {
        switch (e->type) {
        case SDL_QUIT:
            _window.close();
            break;
        case SDL_KEYDOWN:
            switch (e->key.keysym.sym) {
                case SDLK_LEFT:
                    _player.setPosition(_player.getPosition() - SDL::Vector2i(5, 0));
                    break;
                case SDLK_RIGHT:
                    _player.setPosition(_player.getPosition() + SDL::Vector2i(5, 0));
                    break;
                case SDLK_UP:
                    FPS += 10;
                    _fpsText.setText(std::to_string(FPS));
                    break;
                case SDLK_DOWN:
                    if (FPS <= 10) break;
                    FPS -= 10;
                    _fpsText.setText(std::to_string(FPS));
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
    if (_player.getPosition().y > -20)
        _player.setPosition(_player.getPosition() - SDL::Vector2i(0, 1));
    else
        _player.setPosition(SDL::Vector2i(_player.getPosition().x, _window.getSize().y));
}

void Fuzzy::Fuzzy::draw()
{
    _window.clear();
    
    _background.draw(_window);
    _player.draw(_window);

    SDL::Sprite texture;
    texture.load(_window, _fpsText, {0, 0, 100, 64});
    texture.setPosition(SDL::Vector2i(10, 10));
    texture.setSize(SDL::Vector2i(80, 80));
    texture.draw(_window);

    _window.display();
}