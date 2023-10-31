/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Image
*/

#pragma once

#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ISContainer.hpp"

namespace SDL
{
    class Image : public ISContainer
    {
        public:
            Image();
            Image(const std::string path);
            ~Image();
            
            void load(const std::string path);
            void unload();

            // Getters
            const std::string &getFilePath() const { return _path; }
            
            // Copy constructor
            Image(const Image &other) = delete;

            // Operators
            SDL_Surface *operator*() { return _surface; }
        protected:
        private:
            SDL_Rect _size;
            bool _initialized;

            // Constructors parameters
            std::string _path;
    };
}
