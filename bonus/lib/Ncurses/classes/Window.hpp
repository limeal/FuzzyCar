/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** WINDOW (Ncurses Rebased)
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

// Terminal Graphic Library (Ncurses)
#include <curses.h>

namespace NCurses
{

    class Window
    {
    public:
        Window();
        ~Window() { endwin(); }

        bool isOpen() const { return _isOpen; }
        void close() { _isOpen = false;  }

        void refresh() const { ::refresh(); }
        void render() const { refresh(); }

        int getChar() const { return getch(); }

        int getWidth() const { return COLS; }
        int getHeight() const { return LINES; }

        void render() const;
    private:
        bool _isOpen = true;
    };
}

#endif /* !WINDOW_HPP_ */
