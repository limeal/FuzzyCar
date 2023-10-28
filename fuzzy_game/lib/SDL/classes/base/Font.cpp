/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Font
*/

#include "Font.hpp"

#include "../../SDL.hpp"
#include "../../errors/BaseException.hpp"

#include <iostream>

SDL::Font::Font() :
    _font(nullptr),
    _initialized(false)
{
}

SDL::Font::Font(const std::string &path, int size) :
    _font(nullptr),
    _initialized(false)
{
    load(path, size);
}

SDL::Font::~Font()
{
    if (_initialized && _font)
        TTF_CloseFont(_font);
}

void SDL::Font::load(const std::string &path, int size)
{
    if (!Core::HasModule("SDLTtf"))
        throw SDL::BaseException("SDLTtf module is not initialized");

    if (_initialized) throw SDL::BaseException("Font is already initialized");

    _fontPath = path;
    _fontSize = size;

    _font = TTF_OpenFont(path.c_str(), size);
    if (!_font)
        throw SDL::BaseException("Unable to load font: " + std::string(TTF_GetError()));
    _initialized = true;
}

void SDL::Font::unload()
{
    if (!_initialized) return;
    if (_font)
        TTF_CloseFont(_font);
    _font = nullptr;
    _initialized = false;
}

void SDL::Font::setSize(int size)
{
    if (_fontSize == size) return;
    if (_font)
        TTF_CloseFont(_font);
    _font = TTF_OpenFont(_fontPath.c_str(), size);
    if (!_font)
        throw SDL::BaseException("Unable to load font: " + std::string(TTF_GetError()));
    _fontSize = size;
}

