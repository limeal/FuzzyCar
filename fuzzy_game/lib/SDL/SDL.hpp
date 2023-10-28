/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDL
*/

#pragma once

#include <list>
#include <memory>

#include <SDL2/SDL.h>

#include "maths/Vector.hpp"
#include "errors/BaseException.hpp"

// Import modules
#include "SDLModule.hpp"
#include "modules/SDLImage.hpp"
#include "modules/SDLTtf.hpp"
#include "modules/SDLMixer.hpp"

// Import classes
#include "classes/Window.hpp"

#include "classes/base/Image.hpp"
#include "classes/base/Font.hpp"
#include "classes/base/Music.hpp"

#include "classes/Text.hpp"
#include "classes/Texture.hpp"
#include "classes/Event.hpp"
#include "classes/Sprite.hpp"


namespace SDL
{

    enum class SDLMODE : Uint32
    {
        VIDEO = SDL_INIT_VIDEO,
        AUDIO = SDL_INIT_AUDIO,
        TIMER = SDL_INIT_TIMER,
        JOYSTICK = SDL_INIT_JOYSTICK,
        HAPTIC = SDL_INIT_HAPTIC,
        GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
        EVENTS = SDL_INIT_EVENTS,
        EVERYTHING = SDL_INIT_EVERYTHING,
        NOPARACHUTE = SDL_INIT_NOPARACHUTE
    };

    class Core
    {
    public:
        static void Init(std::list<Uint32> modes = {
            static_cast<Uint32>(SDLMODE::VIDEO),
            static_cast<Uint32>(SDLMODE::AUDIO)
        });
    
        static void Quit();

        // Modules
        static void InitModules(std::list<std::shared_ptr<SDL::SDLModule>> modules);
        static bool HasModule(const std::string name);

        inline static const void Delay(Uint32 ms) { SDL_Delay(ms); }
        inline static const Uint32 GetTicks() { return SDL_GetTicks(); }
        inline static const Uint32 GetPerformanceCounter() { return SDL_GetPerformanceCounter(); }
        inline static const Uint32 GetPerformanceFrequency() { return SDL_GetPerformanceFrequency(); }


        inline static std::list<std::shared_ptr<SDL::SDLModule>> MODULES = {};
        inline static bool INIT = false;
    };
}