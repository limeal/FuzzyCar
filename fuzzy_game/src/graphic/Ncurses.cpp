/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    _win = newwin(LINES, COLS, 0, 0);
}

Ncurses::~Ncurses()
{
    endwin();
}

