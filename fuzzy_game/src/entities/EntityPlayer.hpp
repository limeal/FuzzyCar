/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityPlayer
*/

#pragma once

#include "EntityCar.hpp"

namespace Fuzzy {
    class EntityPlayer : public EntityCar {
        public:
            EntityPlayer(SDL::Sprite &sprite, SDL::Vector2i position, SDL::Vector2i direction = SDL::Vector2i(0, -1));
            ~EntityPlayer() = default;

            void consume(SDL::Event *event);
    };
}