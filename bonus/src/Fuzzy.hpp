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

// #include "../lib/Ncurses/Ncurses.hpp"

#include "levels/Level.hpp"

// Entities
#include "entities/EntityPlayer.hpp"

namespace Fuzzy {
    class Fuzzy {
        public:
            Fuzzy(const std::string map, SDL::Vector2i size);

            void launch();
        private:
            void handleEvents();
            void update();
            void draw();


            //NCurses::Window _window;
            SDL::Window _window;
            //SDL::Sprite _background;


            Level _level;
            EntityPlayer _player;
            std::list<EntityCar> _enemies;

            // Texts
            SDL::Text _fpsText;


            inline static std::string VERSION = "0.1";
            inline static int FPS = 20;

    };
}