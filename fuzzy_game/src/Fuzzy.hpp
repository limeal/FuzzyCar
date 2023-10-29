/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Fuzzy
*/

#pragma once

#include <vector>
#include <memory>

#include "../lib/SDL/SDL.hpp"
#include "Assets.hpp"

#include "levels/Level.hpp"

// Entities
#include "entities/EntityPlayer.hpp"

namespace Fuzzy {
    class Fuzzy {
        public:
            Fuzzy(SDL::Vector2i size);

            void launch();
        private:
            void handleEvents();
            void update();
            void draw();

            SDL::Window _window;

            Level _level;
            std::unique_ptr<EntityPlayer> _player;

            // Texts
            SDL::Text _fpsText;


            inline static std::string VERSION = "0.1";
            inline static int FPS = 20;

    };
}