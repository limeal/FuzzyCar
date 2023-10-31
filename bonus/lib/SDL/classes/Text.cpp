/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Text
*/

#include "Text.hpp"

#include "../errors/BaseException.hpp"

SDL::Text::Text() :
    _font(nullptr),
    _initialized(false)
{
}

SDL::Text::Text(const std::string& text, const Font &font, const SDL_Color& color) :
    _font(nullptr),
    _initialized(false)
{
    load(text, font, color);
}

SDL::Text::~Text()
{
    if (_initialized)
        SDL_FreeSurface(_surface);
}

void SDL::Text::load(const std::string& text, const Font &font, const SDL_Color& color)
{
    if (_initialized) throw SDL::BaseException("Text already initialized");

    _font = &font;
    _color = color;
    setText(text);
    _initialized = true;
}

void SDL::Text::setText(const std::string &text)
{
    if (_text == text) return;
    if (_surface)
        SDL_FreeSurface(_surface);
    _surface = TTF_RenderText_Solid(_font->getFont(), text.c_str(), _color);
    if (!_surface)
        throw SDL::BaseException("Failed to render text: " + text + " (" + std::string(TTF_GetError()) + ")");
    _text = text;
}