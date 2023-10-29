/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Assets
*/

#ifndef ASSETS_HPP_
#define ASSETS_HPP_

#include <string>

#include "../lib/SDL/SDL.hpp"

namespace Fuzzy {
    class Assets {
        public:

            static void Load() {
                // Images
                BACKGROUND.load("assets/background.png");
                BLUE_CAR.load("assets/cars/blue.png");
                RED_CAR.load("assets/cars/red.png");

                // Fonts
                ROBOTO_FONT.load("assets/fonts/roboto.ttf", 32);

                // Music
                SOUNDTRACK.load("assets/audio/soundtrack.mp3", true);
            }

            static void Unload() {
                // Images
                BACKGROUND.unload();
                BLUE_CAR.unload();
                RED_CAR.unload();

                // Fonts
                ROBOTO_FONT.unload();

                // Music
                SOUNDTRACK.unload();
            }

            // Images
            inline static SDL::Image BACKGROUND;
            inline static SDL::Image BLUE_CAR;
            inline static SDL::Image RED_CAR;

            // Fonts
            inline static SDL::Font ROBOTO_FONT;

            // Music
            inline static SDL::Music SOUNDTRACK;
    };
}

#endif /* !ASSETS_HPP_ */
