/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Game
*/

#include "Game.hpp"

#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

#include <time.h>

namespace Fuzzy
{
    Game::Game(Map &map) : m_map(map)
    {
        auto enemies = m_map.getEnemies();
        for (auto &enemy : enemies)
        {
            _cars.push_back(Car(enemy, 1));
        }

        _player = std::make_unique<PlayerCar>(m_map.getPlayer());
    }

    Game::~Game()
    {
        endwin();
    }

    void Game::start()
    {

        initscr();
        keypad(stdscr, TRUE);
        noecho();
        nodelay(stdscr, TRUE);
        curs_set(0);
        start_color();
        
        int ch;
        clock_t start = clock();
        clock_t stop;
        double elapsed = 0.0;
        while((ch = getch()) != 'q')
        {
            refresh();
            if (ch == KEY_RIGHT)
                _player->turnRight(m_map.getSize());
            else if (ch == KEY_LEFT)
                _player->turnLeft();

            
            stop = clock();
            elapsed = (double)( stop - start) / CLOCKS_PER_SEC;

            if (elapsed > 0.5)
            {

                for (int i = 0; i < _cars.size(); i++)
                {
                    _cars[i].move(m_map.getSize());
                }
                
                if (!_player->move(m_map.getSize()))
                    break;
                start = clock();
            }
            
            render();
            refresh();
        }
        
        refresh();
        mvprintw((LINES / 2), (COLS / 2) - 4, "You win!");
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    void Game::render()
    {
        Vector2d size = m_map.getSize();

        for (size_t y = 0; y < size.y; y++)
        {
            std::string line = "";
            for (size_t x = 0; x < size.x; x++)
            {
                if (_player->getPosition().x == x && _player->getPosition().y == y)
                {
                    line += "P";
                    continue;
                }

                auto car = std::find_if(_cars.begin(), _cars.end(), [x, y](Car &car)
                                        { return car.getPosition().x == x && car.getPosition().y == y; })[0];

                if (car.getPosition().x == x && car.getPosition().y == y)
                    line += "O";
                else
                    line += ".";
            }
            //std::cerr << line << std::endl;
            mvprintw((LINES / 4) + y, (COLS / 2) - (size.x / 2), line.data());
        }
    }
}