/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Levels
*/

#include "Level.hpp"

#include <iostream>

Fuzzy::Level::Level(
    SDL::Window &window,
    SDL::Image &background,
    std::vector<int> laneKeypoints,
    int nbRoads,
    int nbSteps) : _window(window), _nbSteps(nbSteps), _nbRoads(nbRoads)
{
    SDL::Vector2i size = _window.getSize();

    _roads = std::vector<SDL::Sprite>(nbRoads);
    for (int i = 0; i < nbRoads; i++)
    {
        _roads[i].load(_window, background, {0, 0, 1059, 1080});
        _roads[i].setPosition(SDL::Vector2i(0, i * size.y));
        _roads[i].setSize(size);
    }

    int cellSize = size.y / nbSteps;

    for (auto &keypoint : laneKeypoints)
    {
        _lanes.push_back((float) keypoint * ((float) _window.getSize().x / 1059.f));
    }

    for (int i = 0; i < (nbSteps * nbRoads); i++)
    {
        _steps.push_back((cellSize / 2) + (cellSize * i));
    }
}

void Fuzzy::Level::render(SDL::Window &window)
{
    for (auto &road : _roads)
    {
        road.draw(window);
    }
}