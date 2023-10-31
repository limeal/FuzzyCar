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
            const std::string &background,
            std::vector<int> laneKeyPoints,
            const std::string filename,
            bool reverse = false);
        ~Level() = default;


        SDL::Vector2i getRealPosition(SDL::Vector2i position);

        int getLanePosition(int lane) const { return _lanes[lane]; }
        SDL::Vector2i getPlayerPosition() const { return _playerPosition; }
        std::vector<SDL::Vector2i> getEnemiesPositions() const { return _enemiesPositions; }

        int getMaxSteps() const { return _steps.size(); }
        int getNbRoads() const { return _nbRoads; }
        SDL::Sprite &getRoad() { return _road; }

        void render(SDL::Window &window);
        void update();
    private:
        void load(std::vector<int> laneKeyPoints, int nbSteps, int maxStepsPerRoad);

        SDL::Window &_window;
        const std::string _background;
        const std::string _filename;
        bool _reverse;

        SDL::Sprite _road;
        std::deque<int> _lanes;
        std::deque<int> _steps;
        int _nbRoads, _maxStepsPerRoad;

        SDL::Vector2i _playerPosition;
        std::vector<SDL::Vector2i> _enemiesPositions;
    };
}
