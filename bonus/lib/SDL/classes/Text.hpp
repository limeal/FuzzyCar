/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Text
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "base/ISContainer.hpp"
#include "base/Font.hpp"

namespace SDL {
    class Text : public ISContainer {
        public:
            Text();
            Text(const std::string& text,  const Font &font, const SDL_Color& color);
            ~Text();
    
            void load(const std::string& text, const Font &font, const SDL_Color& color);
    
            // Setter
            void setText(const std::string &text);
            void setFont(const Font &font) { _font = &font; }

            // Getters
            const std::string &getText() const { return _text; }
            const SDL_Color &getColor() const { return _color; }
    
            // Copy constructor
            Text(const Text &other) = delete;
            // Operators
            SDL_Surface *operator*() { return _surface; }
        protected:
        private:
            std::string _text;
            SDL_Color _color;
    
            const SDL::Font *_font;
            bool _initialized;
    };
}