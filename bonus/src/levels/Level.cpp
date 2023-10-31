/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Levels
*/

#include "Level.hpp"

#include <iostream>
#include <fstream>
#include <boost/algorithm/string/trim.hpp>

#include "../Assets.hpp"
#include "../errors/FuzzyException.hpp"

Fuzzy::Level::Level(
    SDL::Window &window,
    const std::string &background,
    std::vector<int> laneKeyPoints,
    const std::string filename,
    bool reverse) : _window(window),
                    _background(background),
                    _filename(filename),
                    _reverse(reverse),
                    _nbRoads(0),
                    _maxStepsPerRoad(0),
                    _playerPosition(SDL::Vector2i(-1, -1)),
                    _enemiesPositions({})
{

    std::ifstream file(filename);

    if (!file.is_open())
        throw FuzzyException("Cannot open file " + filename);
    std::string line = "";
    int rows = 0, cols = 0;
    while (std::getline(file, line))
    {
        // Remove comments starting with #
        if (line.find('#') != std::string::npos)
            line = line.substr(0, line.find('#'));
        // Remove end and start spaces
        boost::trim(line);
        if (!cols)
            cols = line.size();
        else if (cols != line.size())
            throw FuzzyException("Invalid map file (Number of cols differ): " + filename);

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == 'P')
            {
                if (_playerPosition.x != -1)
                    throw FuzzyException("Invalid map file (Multiple player): " + filename);
                _playerPosition = SDL::Vector2i(i, rows);
            }
            else if (line[i] == 'E')
            {
                _enemiesPositions.push_back(SDL::Vector2i(i, rows));
            }
        }

        rows++;
    }

    if (_playerPosition.x == -1)
        throw FuzzyException("Invalid map file (No player): " + filename);
    load(laneKeyPoints, rows, 10);
}

void Fuzzy::Level::update()
{
    int cellSize = _window.getSize().y / _maxStepsPerRoad;
    SDL::Vector2i newPosition = SDL::Vector2i(_road.getPosition().x, _road.getPosition().y + 1);
    if (newPosition.y > 0) newPosition.y = 0;
    _road.setPosition(newPosition);
}

void Fuzzy::Level::render(SDL::Window &window)
{
    _road.draw();
}

SDL::Vector2i Fuzzy::Level::getRealPosition(SDL::Vector2i position)
{
    if (position.y < 0 || position.x < 0)
        throw FuzzyException("Step cannot be negative");

    if (position.y >= _steps.size()) return SDL::Vector2i(_lanes[position.x], _steps[_steps.size() - 1]);

    if (_reverse)
        position.y = _steps.size() - 1 - position.y;

    return SDL::Vector2i(_lanes[position.x], _steps[position.y]);
}

void Fuzzy::Level::load(std::vector<int> laneKeyPoints, int nbSteps, int maxStepsPerRoad)
{
    SDL::Vector2i size = _window.getSize();
    _nbRoads = nbSteps < maxStepsPerRoad ? 1 : nbSteps / maxStepsPerRoad;
    _maxStepsPerRoad = maxStepsPerRoad;

    int cellSize = size.y / _maxStepsPerRoad;

    _road.load(_window, Assets::BACKGROUND , {0, 0, 1059, 10800});
    _road.setSize(SDL::Vector2i(size.x, size.y * 10));
    _road.setPosition(SDL::Vector2i(0, -size.y * 9));

    for (auto &keypoint : laneKeyPoints)
        _lanes.push_back((float)keypoint * ((float)_window.getSize().x / 1059.f));

    for (int i = 0; i < (_maxStepsPerRoad * _nbRoads); i++)
        _steps.push_back((cellSize / 2) + (cellSize * i));
}