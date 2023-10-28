/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityCar
*/

#include "EntityCar.hpp"

Fuzzy::EntityCar::EntityCar(SDL::Sprite &sprite, SDL::Vector2i position, SDL::Vector2i direction) :
    _sprite(sprite),
    _direction(direction)
{
    _sprite.setPosition(position);
}

void Fuzzy::EntityCar::update()
{
    _sprite.updateTexture(_sprite.getPosition() + _direction);
}

void Fuzzy::EntityCar::render(SDL::Window &window)
{
    _sprite.draw(window);
}