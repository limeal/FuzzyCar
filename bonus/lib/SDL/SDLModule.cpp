/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLModule
*/

#include "SDLModule.hpp"

#include <SDL2/SDL.h>

SDL::SDLModule::SDLModule(std::list<Uint32> modes) : _flags(0)
{
    for (Uint32 mode : modes)
        _flags |= mode;
}
