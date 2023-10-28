/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLWindow
*/

#pragma once

#include <list>
#include <string>

#include <SDL2/SDL.h>

#include "../maths/Vector.hpp"
#include "../errors/BaseException.hpp"

namespace SDL
{
    class Window
    {
        public:

            Window(const std::string title, Vector2i size);
            ~Window();

            void clear() { SDL_RenderClear(_renderer); }
            void display() { SDL_RenderPresent(_renderer); }
            void close() { _open = false; }

            // Getters
            bool isOpen() const { return _open; }
            bool isFullscreen() const { return SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN; }

            SDL_Window *getWindow() const { return _window; }
            const std::string &getTitle() const { return _title; }
            const Vector2i &getSize() const { return _size; }

            // Operators
            SDL_Renderer *operator*() { return _renderer; }
        protected:
        private:
            bool _open;
            
            SDL_Window *_window = NULL;
            SDL_Renderer *_renderer = NULL;
            
            // Constructor parameters
            const std::string _title;
            Vector2i _size;
    };
}