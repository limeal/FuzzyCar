/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Window
*/

#include "Window.hpp"

namespace Fuzzy {
    namespace Engine {

        Window::Window(Vector2i size, const char *title)
        {
            InitWindow(size.x, size.y, title);
        }

        Window::Window(Vector2i size, const char *title, Image icon)
        {
            InitWindow(size.x, size.y, title);
            setIcon(icon);
        }

        Window::~Window()
        {
            if (!_isClosed) CloseWindow();
        }

        bool Window::shouldClose()
        {
            return WindowShouldClose();
        }

        void Window::close()
        {
            _isClosed = true;
            return CloseWindow();
        }

        bool Window::isHidden()
        {
            return IsWindowHidden();
        }

        bool Window::isMinimized()
        {
            return IsWindowMinimized();
        }

        bool Window::isMaximized()
        {
            return IsWindowMaximized();
        }

        bool Window::isFocused()
        {
            return IsWindowFocused();
        }

        bool Window::isResized()
        {
            return IsWindowResized();
        }

        bool Window::isState(WindowState state)
        {
            return IsWindowState(state);
        }

        void Window::setState(WindowState state)
        {
            SetWindowState(state);
        }

        void Window::clearState(WindowState state)
        {
            ClearWindowState(state);
        }

        void Window::setTitle(const std::string title)
        {
            SetWindowTitle(title.c_str());
        }

        void Window::setIcon(Image icon)
        {
            SetWindowIcon(icon.getSource());
        }

        void Window::setPosition(Vector2i position)
        {
            SetWindowPosition(position.x, position.y);
        }

        void Window::setMinSize(Vector2i size)
        {
            SetWindowMinSize(size.x, size.y);
        }

        void Window::setSize(Vector2i size)
        {
            SetWindowSize(size.x, size.y);
        }

        Vector2i Window::getPosition(void)
        {
            ::Vector2 pos = GetWindowPosition();
            return Vector2i(pos.x, pos.y);
        }

        void *Window::getHandle(void)
        {
            return GetWindowHandle();
        }

        void Window::clearBackground(Color color)
        {
            ClearBackground(color.getSource());
        }

        void Window::toggleFullscreen(void)
        {
            ToggleFullscreen();
        }

        void Window::maximize(void)
        {
            MaximizeWindow();
        }

        void Window::minimize(void)
        {
            MinimizeWindow();
        }

        void Window::restore(void)
        {
            RestoreWindow();
        }

        void Window::beginDrawing(void)
        {
            BeginDrawing();
        }

        void Window::endDrawing(void)
        {
            EndDrawing();
        }

        void Window::drawCamera(Camera camera)
        {
            BeginMode3D(camera.getSource());
        }

        void Window::endDrawCamera()
        {
            EndMode3D();
        }
    }
}