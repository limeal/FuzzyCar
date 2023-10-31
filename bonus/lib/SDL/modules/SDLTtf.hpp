/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLTtf
*/

#pragma once


#include <SDL2/SDL_ttf.h>

#include "../SDLModule.hpp"

namespace SDL {

    class SDLTtf : public SDLModule {
        public:
            SDLTtf(std::list<Uint32> modes = {});
            ~SDLTtf();

            void Init() override;
            const std::string getID() override { return "SDLTtf"; }
    };
}