/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLTtf
*/

#include "SDLTtf.hpp"

#include "../errors/BaseException.hpp"

#include <iostream>

SDL::SDLTtf::SDLTtf(std::list<Uint32> modes) :
    SDLModule(modes)
{

}

SDL::SDLTtf::~SDLTtf()
{
    if (_initialized)
        TTF_Quit();
}

void SDL::SDLTtf::Init()
{
    if (TTF_Init() == -1)
        throw SDL::BaseException("Unable to initialize SDLTtf: " + std::string(TTF_GetError()));
    _initialized = true;
}