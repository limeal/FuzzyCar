/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Sprite
*/

#include "Sprite.hpp"

SDL::Sprite::Sprite(SDL::Window &window, ISContainer &element, SDL_Rect local, SDL_Rect global) :
    Texture(window, element, local),
    _globalBounds(global),
    _origin({0, 0})
{

}

void SDL::Sprite::draw(Vector2i *position)
{
    SDL_Rect rect = {_globalBounds.x - _origin.x, _globalBounds.y - _origin.y, _globalBounds.w, _globalBounds.h};
    if (position) {
        rect.x = position->x - _origin.x;
        rect.y = position->y - _origin.y;
    }
    SDL_RenderCopy(_window->getRenderer(), _texture, &_localBounds, &rect);
}