/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** SDLImage
*/

#pragma once

#include <SDL2/SDL_image.h>

#include "../SDLModule.hpp"

namespace SDL {

    enum class SDLIMAGEMODE : Uint32
    {
        JPG = IMG_INIT_JPG,
        PNG = IMG_INIT_PNG,
        TIF = IMG_INIT_TIF
    };

    class SDLImage : public SDLModule {
        public:
            SDLImage(std::list<Uint32> modes = {
                static_cast<Uint32>(SDLIMAGEMODE::JPG),
                static_cast<Uint32>(SDLIMAGEMODE::PNG),
                static_cast<Uint32>(SDLIMAGEMODE::TIF)
            });
            ~SDLImage();

            void Init() override;
            const std::string getID() override { return "SDLImage"; }
    };
}
