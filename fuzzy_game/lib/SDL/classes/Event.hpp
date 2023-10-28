/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Event
*/

#pragma once

#include <SDL2/SDL.h>

namespace SDL
{
    class Event
    {
        public:
            int poll() { return SDL_PollEvent(&_event); }

            // Operators
            SDL_Event &operator*() { return _event; }
            SDL_Event *operator->() { return &_event; }

        protected:
        private:
            SDL_Event _event;
    };
}
