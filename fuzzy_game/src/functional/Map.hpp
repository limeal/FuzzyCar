/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "../helpers/Vector.hpp"

namespace Fuzzy
{
    class Map
    {
    public:
        enum ElementType
        {
            CAR,
            PCAR
        };

        Map(std::string filename, char picon = 'P', char cicon = 'O');

        std::vector<Vector2d> getEnemies()
        {
            std::vector<Vector2d> enemies;
            for (auto &element : _elements)
            {
                if (element.first == Map::ElementType::CAR)
                    enemies.push_back(element.second);
            }
            return enemies;
        }

        Vector2d getPlayer()
        {
            for (auto &element : _elements)
            {
                if (element.first == Map::ElementType::PCAR)
                    return element.second;
            }
            return Vector2d(0, 0);
        }

        Vector2d getSize() const
        {
            return _size;
        }

        void print()
        {
            for (auto &element : _elements)
            {
                if (element.first == Fuzzy::Map::ElementType::CAR)
                    std::cout << "Car: ";
                else if (element.first == Fuzzy::Map::ElementType::PCAR)
                    std::cout << "Player: ";
                std::cout << element.second.x << "," << element.second.y << std::endl;
            }
        }

    protected:
    private:
        std::vector<std::pair<ElementType, Vector2d>> _elements;
        Vector2d _size;

        char _picon, _cicon;
    };
}

#endif /* !MAP_HPP_ */
