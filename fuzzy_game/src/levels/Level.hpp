/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Level
*/

#pragma once

#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>

#include "../../lib/SDL/SDL.hpp"
#include "../errors/FuzzyException.hpp"

namespace Fuzzy
{
    class Level
    {
    public:
        Level(
            SDL::Window &window,
            SDL::Image &background,
            std::vector<int> laneKeyPoints,
            int nbRoads,
            int nbSteps);
        ~Level() = default;


        SDL::Vector2i getRealPosition(int lane, int step = 0) {
            if (step < 0) throw FuzzyException("Step cannot be negative");
            return SDL::Vector2i(_lanes[lane], _steps[step]);
        }

        int getLanePosition(int lane) const { return _lanes[lane]; }

        int getMaxSteps() const { return _steps.size(); }

        void render(SDL::Window &window);
    private:
        SDL::Window &_window;
        std::vector<SDL::Sprite> _roads;

        std::deque<int> _lanes;
        std::deque<int> _steps;
        int _nbSteps, _nbRoads;
    };
}
