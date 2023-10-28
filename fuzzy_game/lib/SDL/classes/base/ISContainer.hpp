/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** ISContainer
*/

#pragma once

#include <SDL2/SDL.h>

#include "../../maths/Vector.hpp"

namespace SDL {
    class ISContainer {
        public:
            ISContainer(SDL_Surface *surface = nullptr) : _surface(surface) {}
            virtual ~ISContainer() = default;
    
            SDL_Surface *getSurface() const { return _surface; }
            SDL::Vector2i getDefaultSize() const { return SDL::Vector2i(_surface->w, _surface->h); }
        protected:
            SDL_Surface *_surface;
    };
}