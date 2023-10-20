/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** PlayerCar
*/

#include "PlayerCar.hpp"

namespace Fuzzy {
    PlayerCar::PlayerCar(Fuzzy::Vector2d position) :
        Car(position)
    {
    }

    PlayerCar::~PlayerCar()
    {
    }

    bool PlayerCar::move(Vector2d max)
    {
        if (_position.y == 0)
            return false;
        _position.y -= 1;
        return true;
    }

    bool PlayerCar::turnLeft()
    {
        if (_position.x == 0)
            return false;
        _position.x -= 1;
        return true;
    }

    bool PlayerCar::turnRight(Vector2d max)
    {
        if (_position.x == (max.x - 1))
            return false;
        _position.x += 1;
        return true;
    }
}
