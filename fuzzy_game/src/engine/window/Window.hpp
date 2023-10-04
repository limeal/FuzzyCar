/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Window
*/

#pragma once

extern "C" {
    #include <raylib.h>
}

#include <string>

#include "../maths/Vector.hpp"
#include "../graphics/2D/image/Image.hpp"
#include "../graphics/3D/camera/Camera.hpp"
#include "../graphics/color/Color.hpp"

namespace Fuzzy {
    namespace Engine {
        class Window {
            public:
                enum WindowState : unsigned int {
                    VSYNC = FLAG_VSYNC_HINT,
                    FULLS = FLAG_FULLSCREEN_MODE,
                    RESIZE = FLAG_WINDOW_RESIZABLE,
                    WUND = FLAG_WINDOW_UNDECORATED,
                    WT = FLAG_WINDOW_TRANSPARENT,
                    WH = FLAG_WINDOW_HIDDEN,
                    MIN = FLAG_WINDOW_MINIMIZED,
                    MAX = FLAG_WINDOW_MAXIMIZED,
                    WUF = FLAG_WINDOW_UNFOCUSED,
                    WTOP = FLAG_WINDOW_TOPMOST,
                    WDPI = FLAG_WINDOW_HIGHDPI,
                    WAR = FLAG_WINDOW_ALWAYS_RUN,
                    WMSA = FLAG_MSAA_4X_HINT
                };


                Window(Vector2i size, const char *title, Fuzzy::Engine::Image icon);
                Window(Vector2i size, const char *title);
                ~Window();

                bool shouldClose();
                void close();
                bool isHidden(void);                    // Check if window is currently hidden (only PLATFORM_DESKTOP)
                bool isMinimized(void);                 // Check if window is currently minimized (only PLATFORM_DESKTOP)
                bool isMaximized(void);                 // Check if window is currently maximized (only PLATFORM_DESKTOP)
                bool isFocused(void);                   // Check if window is currently focused (only PLATFORM_DESKTOP)
                bool isResized(void);                   // Check if window has been resized last frame

                bool isState(WindowState state);          // Check if one specific window flag is enabled
                void setState(WindowState state);      // Set window configuration state using flags
                void clearState(WindowState state);    // Clear window configuration state flags
                
                void setTitle(const std::string title);       // Set title for window (only PLATFORM_DESKTOP)
                void setIcon(Fuzzy::Engine::Image image);              // Set icon for window (only PLATFORM_DESKTOP)
                void setPosition(Vector2i position);         // Set window position on screen (only PLATFORM_DESKTOP)
                void setMinSize(Vector2i size); // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
                void setSize(Vector2i size);    // Set window dimensions
                
                Vector2i getPosition(void);              // Get window position XY on monitor
                void *getHandle(void);                  // Get native window handle
                
                void clearBackground(Color color);            // Set background color (framebuffer clear color)
                void toggleFullscreen(void);                  // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
                
                void maximize(void);                    // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
                void minimize(void);                    // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
                void restore(void);                     // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)

                void beginDrawing(void);                      // Setup canvas (framebuffer) to start drawing
                void endDrawing(void);
                void drawCamera(Fuzzy::Engine::Camera camera);
                void endDrawCamera();

            protected:
            private:
                bool _isClosed;
        };
    }
}
