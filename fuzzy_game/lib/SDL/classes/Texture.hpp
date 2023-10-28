/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Texture
*/

#pragma once

#include <SDL2/SDL.h>

#include "Window.hpp"
#include "base/ISContainer.hpp"

namespace SDL
{
    class Texture
    {
    public:
        Texture();
        Texture(SDL::Window &window, const ISContainer &element, SDL_Rect rect = {});
        ~Texture();

        void load(SDL::Window &window, const ISContainer &image, SDL_Rect rect = {});

        virtual void draw(Window &window);
        
        SDL_Rect &getLocalBounds() { return _localBounds; }
        const ISContainer *getContainer() { return _container; }

        // Operators
        SDL_Texture *operator*() { return _texture; }

    protected:
        SDL_Texture *_texture;
        const ISContainer *_container;

        SDL_Rect _localBounds;
        bool _initialized = false;
    };
}