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
    _window("FuzzyCar", size),
    _level(_window, Assets::BACKGROUND, {339, 563, 788}, 10, 10),
    _player(nullptr)
{

    _player = std::make_unique<EntityPlayer>(_window, _level.getRealPosition(0, _level.getMaxSteps() - 1));

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

    SDL::Vector2i playerPosition = _player->getPosition();

    SDL_Rect rect = {0, playerPosition.y - (_window.getSize().y / 2), _window.getSize().x, _window.getSize().y};
    _window.setViewport(&rect);
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
            _player->consume(e);
            switch (e->key.keysym.sym) {
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
    _player->update(_level);
}

void Fuzzy::Fuzzy::draw()
{
    _window.clear();
    
    _level.render(_window);
    _player->render(_window);

    SDL::Sprite texture;
    texture.load(_window, _fpsText, {0, 0, 100, 64});
    texture.setPosition(SDL::Vector2i(10, 10));
    texture.setSize(SDL::Vector2i(80, 80));
    texture.draw(_window);

    _window.display();
}