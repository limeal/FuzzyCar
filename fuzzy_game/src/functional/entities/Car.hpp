/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Car
*/

#ifndef CAR_HPP_
#define CAR_HPP_

#include "../../helpers/Vector.hpp"

// English: On a 2D board position is characterized by x and y coordinates
// Korean: 2D 보드의 위치는 x와 y 좌표로 특징지어집니다

namespace Fuzzy
{
    class Car
    {
    public:
        Car(Fuzzy::Vector2d position, float speed = 1.0);
        ~Car();

        bool move(Vector2d max);

        Vector2d getPosition() const
        {
            return _position;
        }

        float getSpeed() const
        {
            return _speed;
        }
    protected:
        Fuzzy::Vector2d _position;

        float _speed;
    };
}

#endif /* !CAR_HPP_ */
