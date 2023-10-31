/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLMixer
*/

#pragma once

#include <list>

#include <SDL2/SDL_mixer.h>

#include "../SDLModule.hpp"

namespace SDL {
    class SDLMixer : public SDLModule {
        public:
            SDLMixer(std::list<Uint32> modes = {});
            ~SDLMixer();

            void Init() override;
            const std::string getID() override { return "SDLMixer"; }
    };
}