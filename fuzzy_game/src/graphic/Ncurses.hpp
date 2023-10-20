/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

// Terminal Graphic Library (Ncurses)
#include <curses.h>

class Ncurses {
    public:
        Ncurses();
        ~Ncurses();

    protected:
    private:
        WINDOW *_win;
};

#endif /* !NCURSES_HPP_ */
