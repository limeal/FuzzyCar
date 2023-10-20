/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** PlayerCar
*/

#ifndef PLAYERCAR_HPP_
#define PLAYERCAR_HPP_

#include "Car.hpp"

namespace Fuzzy
{
    class PlayerCar : public Car
    {
    public:
        PlayerCar(Fuzzy::Vector2d position);
        ~PlayerCar();

        bool move(Vector2d max);

        bool turnLeft();
        bool turnRight(Vector2d max);
    };
}

#endif /* !PLAYERCAR_HPP_ */
