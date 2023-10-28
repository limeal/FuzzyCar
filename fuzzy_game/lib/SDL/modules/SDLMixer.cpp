/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLMixer
*/

#include "SDLMixer.hpp"

#include "../errors/BaseException.hpp"

SDL::SDLMixer::SDLMixer(std::list<Uint32> modes) :
    SDLModule(modes)
{
}

SDL::SDLMixer::~SDLMixer()
{
    if (_initialized)
        Mix_CloseAudio();
}

void SDL::SDLMixer::Init()
{
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
        throw SDL::BaseException("Unable to initialize SDLMixer: " + std::string(Mix_GetError()));
    _initialized = true;
}