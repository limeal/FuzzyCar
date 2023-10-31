/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Window
*/

#include "Window.hpp"

NCurses::Window::Window() : _isOpen(true)
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    timeout(1000);
    curs_set(0);
    start_color();
}

void NCurses::Window::render() const
{
    refresh();
}