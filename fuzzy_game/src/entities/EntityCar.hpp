/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityCar
*/

#pragma once

#include "../../lib/SDL/SDL.hpp"

namespace Fuzzy {
    class EntityCar {
        public:
            EntityCar(SDL::Sprite &sprite, SDL::Vector2i position, SDL::Vector2i direction = SDL::Vector2i(0, 1));
            ~EntityCar() = default;

            void update();
            void render(SDL::Window &window);

        protected:
            SDL::Sprite &_sprite;
            SDL::Vector2i _direction;
    };
}