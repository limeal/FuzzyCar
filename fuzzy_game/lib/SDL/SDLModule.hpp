/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLModule
*/

#pragma once

#include <list>
#include <string>

#include <SDL2/SDL.h>

namespace SDL
{
    class SDLModule {
        public:
            SDLModule(std::list<Uint32> modes);
            virtual ~SDLModule() {};
            
            virtual const std::string getID() = 0;
            virtual void Init() = 0;

            bool IsInitialized() const { return _initialized; }
            Uint32 GetFlags() const { return _flags; }
        protected:
            Uint32 _flags;

            bool _initialized = false;
    };
}