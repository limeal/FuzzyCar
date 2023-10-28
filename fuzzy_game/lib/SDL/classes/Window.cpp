/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Window
*/

#include "Window.hpp"

#include "../SDL.hpp"

SDL::Window::Window(
    const std::string title,
    Vector2i size
    ) :
    _open(true),
    _title(title),
    _size(size)
{
    if (!SDL::Core::INIT)
        throw SDL::BaseException("SDL is not initialized");

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _size.x,
        _size.y,
        SDL_WINDOW_OPENGL);

    if (_window == NULL) 
        throw SDL::BaseException("Could not create window: " + std::string(SDL_GetError()));
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
        throw SDL::BaseException("Failed to create renderer: " + std::string(SDL_GetError()));
/* 
    _surface = SDL_GetWindowSurface(_window);

    if (!_surface)
        throw SDL::BaseException("Failed to get the surface from the window"); */
    
}

SDL::Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
