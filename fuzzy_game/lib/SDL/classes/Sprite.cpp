/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Sprite
*/

#include "Sprite.hpp"

SDL::Sprite::Sprite(SDL::Window &window, const ISContainer &element, SDL_Rect local, SDL_Rect global) :
    Texture(window, element, local),
    _globalBounds(global)
{

}

void SDL::Sprite::draw(Window &window)
{
    SDL_RenderCopy(*window, _texture, &_localBounds, &_globalBounds);
}