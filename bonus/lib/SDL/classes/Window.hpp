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
#include "base/Image.hpp"

namespace SDL
{
    class Window
    {
        public:

            Window(const std::string title, Vector2i size, SDL::Image &icon);
            ~Window();

            void clear() { SDL_RenderClear(_renderer); }
            void display() { SDL_RenderPresent(_renderer); }
            void close() { _open = false; }

            // Getters
            bool isOpen() const { return _open; }
            bool isFullscreen() const { return SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN; }

            void setViewport(SDL_Rect *rect) { SDL_RenderSetViewport(_renderer, rect); }
            void setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { SDL_SetRenderDrawColor(_renderer, r, g, b, a); }
            void setRenderClipRect(SDL_Rect *rect) { SDL_RenderSetClipRect(_renderer, rect); }

            SDL_Rect getViewport() const { SDL_Rect rect; SDL_RenderGetViewport(_renderer, &rect); return rect; }
            SDL_Rect getRenderClipRect() const { SDL_Rect rect; SDL_RenderGetClipRect(_renderer, &rect); return rect; }


            SDL_Window *getWindow() const { return _window; }
            SDL_Renderer *getRenderer() const { return _renderer; }
            const std::string &getTitle() const { return _title; }
            const Vector2i &getSize() const { return _size; }

            // Operators
            SDL_Renderer *operator*() { return _renderer; }
        protected:
        private:
            bool _open;
            
            SDL_Window *_window = NULL;
            SDL_Renderer *_renderer = NULL;
            SDL::Image &_icon;
            
            // Constructor parameters
            const std::string _title;
            Vector2i _size;
    };
}