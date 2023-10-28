/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Sprite
*/

#pragma once


#include <SDL2/SDL.h>

#include "Window.hpp"
#include "Texture.hpp"

namespace SDL {
    class Sprite : public Texture {
        public:
            Sprite() = default;
            Sprite(SDL::Window &window, const ISContainer &element, SDL_Rect local = {}, SDL_Rect global = {});
            ~Sprite() = default;

            void draw(Window &window) override;
            void updateTexture(Vector2i pos) { _localBounds.x = pos.x; _localBounds.y = pos.y; }

            void setPosition(Vector2i pos) { _globalBounds.x = pos.x; _globalBounds.y = pos.y; }
            void setScale(Vector2d scale) { _globalBounds.w *= scale.x; _globalBounds.h *= scale.y; }
            void setSize(Vector2i size) { _globalBounds.w = size.x; _globalBounds.h = size.y; }

            // Getters
            SDL_Rect &getGlobalBounds() { return _globalBounds; }

            Vector2i getPosition() { return Vector2i(_globalBounds.x, _globalBounds.y); }
        private:
            SDL_Rect _globalBounds;
    };
}
