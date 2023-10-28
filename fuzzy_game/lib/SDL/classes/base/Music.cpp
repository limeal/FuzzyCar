/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Music
*/

#include "Music.hpp"

#include "../../errors/BaseException.hpp"

SDL::Music::Music() :
    m_mixMusic(nullptr),
    _loop(false),
    _volume(0),
    _initialized(false),
    _playing(false)
{
}

SDL::Music::Music(const std::string path, bool loop)
{
    load(path, loop);
}

SDL::Music::~Music()
{
    if (_initialized)
        Mix_FreeMusic(m_mixMusic);
}

void SDL::Music::load(const std::string path, bool loop)
{
    if (_initialized)
        Mix_FreeMusic(m_mixMusic);
    m_mixMusic = Mix_LoadMUS(path.c_str());
    if (!m_mixMusic)
        throw SDL::BaseException("Unable to load music: " + std::string(Mix_GetError()));
    setVolume(100);
    _playing = false;
    _loop = loop;
    _initialized = true;
}

void SDL::Music::unload()
{
    if (!_initialized) return;
    if (m_mixMusic)
        Mix_FreeMusic(m_mixMusic);
    m_mixMusic = nullptr;
    _initialized = false;
}

void SDL::Music::setVolume(float volume)
{
    if (volume < 0 || volume > 100)
        throw SDL::BaseException("Unable to set volume: volume must be between 0 and 100");
    _volume = volume;
    Mix_VolumeMusic(_volume);
}

void SDL::Music::setSpeed(float speed)
{
    if (speed < 0 || speed > 100)
        throw SDL::BaseException("Unable to set speed: speed must be between 0 and 100");
    // TODO: Set speed
}

bool SDL::Music::play()
{
    if (!m_mixMusic)
        throw SDL::BaseException("Unable to play music: music not loaded");
    if (_playing) return false;
    Mix_PlayMusic(m_mixMusic, _loop ? -1 : 1);
    _playing = true;
    return true;
}

bool SDL::Music::pause()
{
    if (!m_mixMusic)
        throw SDL::BaseException("Unable to pause music: music not loaded");
    if (!_playing) return false;
    Mix_PauseMusic();
    _playing = false;
    return true;
}

bool SDL::Music::stop()
{
    if (!m_mixMusic)
        throw SDL::BaseException("Unable to stop music: music not loaded");
    if (!_playing) return false;
    // Pause + reset music position
    Mix_RewindMusic();
    Mix_PauseMusic();
    _playing = false;
    return true;
}