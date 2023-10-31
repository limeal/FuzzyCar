/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** NCurses
*/

#pragma once

#include <ncurses.h>
#include <ctime>

#include "classes/Window.hpp"

namespace NCurses {
    class Core {
        public:
            static void Init();
            static void Quit();

            inline static clock_t GetClock() { ::clock(); }
            inline static double GetElapsedTime(clock_t start, clock_t end) { return (double)(end - start) / CLOCKS_PER_SEC; }
    };
}