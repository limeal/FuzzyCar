/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <memory>
// Terminal Graphic Library (Ncurses)
#include <curses.h>

#include "Map.hpp"
#include "entities/Car.hpp"
#include "entities/PlayerCar.hpp"
#include "../helpers/Vector.hpp"

namespace Fuzzy {
    class Game {
        public:
            Game(Map &map);
            ~Game();

            void start();
            void render();

            Map &m_map; // The map

        protected:
        private:
            WINDOW *_win;
            std::vector<Car> _cars; // A vector is an array
            std::unique_ptr<PlayerCar> _player; // The player
    };
}

#endif /* !GAME_HPP_ */
