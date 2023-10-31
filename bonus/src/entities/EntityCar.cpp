/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityCar
*/

#include "EntityCar.hpp"

#include "../Fuzzy.hpp"

Fuzzy::EntityCar::EntityCar(SDL::Vector2i position, SDL::Vector2i direction) :
    _direction(direction),
    _currentLane(0),
    _currentStep(0),
    _speed(1.0f)
{
}

Fuzzy::EntityCar::EntityCar(SDL::Window &window, SDL::Vector2i position, SDL::Vector2i direction) :
    _direction(direction),
    _currentLane(0),
    _currentStep(0),
    _speed(1.0f)
{
    // Enemy
    _sprite.load(window, Assets::RED_CAR, {0, 0, 16, 16});
    _sprite.setPosition(position);
    _sprite.setOrigin(SDL::Vector2i(32, 32));
    _sprite.setSize(SDL::Vector2i(64, 64));
}

void Fuzzy::EntityCar::update(Level &level)
{
    //_currentStep += _direction.y;
    
    if (_currentStep < 0) _currentStep = level.getMaxSteps() - 1;

    SDL::Vector2i target = level.getRealPosition(SDL::Vector2i(_currentLane, _currentStep));
    std::cout << "Target: " << target.x << ", " << target.y << std::endl;

    if (target.y < 0) target.y = 0;
    if (target.x < 0) target.x = 0;

    _sprite.setPosition(target);
}

void Fuzzy::EntityCar::render(SDL::Window &window)
{
    _sprite.draw();
}