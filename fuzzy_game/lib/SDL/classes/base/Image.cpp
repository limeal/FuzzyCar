/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Image
*/

#include "Image.hpp"

#include "../../SDL.hpp"
#include "../../errors/BaseException.hpp"

SDL::Image::Image(const std::string path) :
    _path(""),
    _initialized(false)
{
    load(path);
}

SDL::Image::Image() :
    _path(""),
    _initialized(false)
{
}

SDL::Image::~Image()
{
    if (_initialized)
        SDL_FreeSurface(_surface);
}

void SDL::Image::load(const std::string path)
{
    if (!Core::HasModule("SDLImage"))
        throw SDL::BaseException("SDLImage module is not initialized");

    if (_initialized) throw SDL::BaseException("Image is already initialized");

    _path = path;
    _surface = IMG_Load(path.c_str());
    if (!_surface)
        throw SDL::BaseException("Unable to load image: " + std::string(IMG_GetError()));

    _size = (SDL_Rect) {
        0,
        0,
        _surface->w,
        _surface->h
    };
    _initialized = true;
}

void SDL::Image::unload()
{
    if (!_initialized) return;
    if (_surface)
        SDL_FreeSurface(_surface);
    _surface = nullptr;
    _initialized = false;
}