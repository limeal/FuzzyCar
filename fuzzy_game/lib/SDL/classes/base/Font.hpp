/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Font
*/

#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

namespace SDL {
    class Font {
        public:
            Font();
            Font(const std::string &path, int size);
            ~Font();

            void load(const std::string &path, int size);
            void unload();

            void setSize(int size);

            const std::string &getPath() const { return _fontPath; }
            int getSize() const { return _fontSize; }

            TTF_Font *getFont() const { return _font; }

            // Operators
            TTF_Font *operator*() { return _font; }
        private:
            TTF_Font *_font;
            bool _initialized;

            std::string _fontPath;
            int _fontSize;
    };
}