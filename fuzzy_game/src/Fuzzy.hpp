/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Fuzzy
*/

#pragma once

#include "../lib/SDL/SDL.hpp"
#include "Assets.hpp"

// Entities
#include "entities/EntityPlayer.hpp"

namespace Fuzzy {
    class Fuzzy {
        public:
            Fuzzy(SDL::Vector2i size = SDL::Vector2i(512, 512));

            void launch();
        private:
            void handleEvents();
            void update();
            void draw();

            SDL::Window _window;

            // Sprites
            SDL::Sprite _background;

            SDL::Sprite _player;
            //EntityPlayer _player;

            // Texts
            SDL::Text _fpsText;


            inline static std::string VERSION = "0.1";
            inline static int FPS = 60;
    };
}