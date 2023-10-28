/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLImage
*/

#include "SDLImage.hpp"

#include <string>

#include "../errors/BaseException.hpp"

SDL::SDLImage::SDLImage(std::list<Uint32> modes) :
    SDLModule(modes)
{
}

SDL::SDLImage::~SDLImage()
{
    if (_initialized)
        IMG_Quit();
}

void SDL::SDLImage::Init()
{
    if (IMG_Init(_flags) != _flags)
        throw SDL::BaseException("Unable to initialize SDLImage: " + std::string(IMG_GetError()));
    _initialized = true;
}