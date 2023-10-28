/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Texture
*/

#include "Texture.hpp"

SDL::Texture::Texture() :
    _texture(nullptr)
{
}

SDL::Texture::Texture(SDL::Window &window, const ISContainer &container, SDL_Rect rect)
{
    load(window, container, rect);
}

SDL::Texture::~Texture()
{
    if (_initialized)
        SDL_DestroyTexture(_texture);
}

void SDL::Texture::load(SDL::Window &window, const ISContainer &container, SDL_Rect rect)
{
    if (_initialized) throw SDL::BaseException("Texture is already initialized");

    _container = &container;
    _texture = SDL_CreateTextureFromSurface(*window, _container->getSurface());

    if (!_texture) throw SDL::BaseException("Unable to create texture: " + std::string(SDL_GetError()));

    _localBounds = (SDL_Rect) {
        rect.x,
        rect.y,
        rect.w > 0 ? rect.w : _container->getDefaultSize().x,
        rect.h > 0 ? rect.h : _container->getDefaultSize().y
    };

    _initialized = true;
}

void SDL::Texture::draw(Window &window)
{
    SDL_RenderCopy(*window, _texture, &_localBounds, &_localBounds);
}