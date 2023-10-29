/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityPlayer
*/

#include "EntityPlayer.hpp"

#include "../Fuzzy.hpp"

#include <iostream>

Fuzzy::EntityPlayer::EntityPlayer(SDL::Window &window, SDL::Vector2i position, SDL::Vector2i direction) :
    EntityCar(position, direction)
{
    std::cout << "Position: " << position.x << ", " << position.y << std::endl;
    // Player
    _sprite.load(window, Assets::BLUE_CAR, {0, 0, 16, 16});
    _sprite.setPosition(position);
    _sprite.setOrigin(SDL::Vector2i(32, 32));
    _sprite.setSize(SDL::Vector2i(64, 64));
}

void Fuzzy::EntityPlayer::consume(SDL::Event &event)
{
    switch (event->key.keysym.sym)
    {
    case SDLK_LEFT:
        if (_currentLane == 0)
            break;
        _currentLane--;
        break;
    case SDLK_RIGHT:
        if (_currentLane == 2)
            break;
        _currentLane++;
        break;
    }
}