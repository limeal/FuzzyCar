/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Car
*/

#include "Car.hpp"
#include "../Game.hpp"

namespace Fuzzy
{
    Car::Car(Fuzzy::Vector2d position, float speed) :
        _position(position),
        _speed(speed)
    {
    }

    Car::~Car()
    {
    }

    bool Car::move(Vector2d max)
    {
        if (_position.y >= (max.y - 1))
            return false;
        _position.y += 1;
        return true;
        // TODO: Move the position of the car in y coordinate by increasing it by 1
        // Position is store in the _position variable

        // TODO: 카인 좌표 위치를 1씩 높여 이동합니다
        // 위치가 _position 변수에 저장됩니다
        
    }
}