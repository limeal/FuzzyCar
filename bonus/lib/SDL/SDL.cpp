/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDL
*/

#include "SDL.hpp"

void SDL::Core::Init(std::list<std::shared_ptr<SDL::SDLModule>> modules, std::list<Uint32> modes)
{
    if (INIT)
        throw SDL::BaseException("SDL is already initialized");
    Uint32 flags = 0;
    for (Uint32 mode : modes)
        flags |= mode;

    if (SDL_Init(flags) != 0)
        throw SDL::BaseException("Unable to initialize SDL: " + std::string(SDL_GetError()));
    for (auto &mod : modules) {
        mod->Init();
        MODULES.push_back(mod);
    }
    INIT = true;
}

void SDL::Core::Quit()
{
    if (INIT) {
        // Quit modules, by calling their destructors
        MODULES.clear();
        SDL_Quit();
    }
}

bool SDL::Core::HasModule(const std::string name)
{
    for (auto &mod : MODULES) {
        if (mod->getID() == name && mod->IsInitialized())
            return true;
    }
    return false;
}