/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityCar
*/

#pragma once

#include "../../lib/SDL/SDL.hpp"
#include "../levels/Level.hpp"

namespace Fuzzy {
    class EntityCar {
        public:
            EntityCar(SDL::Vector2i position, SDL::Vector2i direction = SDL::Vector2i(0, 1));
            EntityCar(SDL::Window &window, SDL::Vector2i position, SDL::Vector2i direction = SDL::Vector2i(0, 1));
            ~EntityCar() = default;

            void update(Level &level);
            void render(SDL::Window &window);

            void setLane(int lane) { _currentLane = lane; }
            int getCurrentLane() { return _currentLane; }
            int getCurrentStep() { return _currentStep; }

            SDL::Vector2i getPosition() { return _sprite.getPosition(); }

        protected:
            SDL::Sprite _sprite;
            SDL::Vector2i _direction;
            float _speed;

            int _currentLane;
            int _currentStep;
    };
}