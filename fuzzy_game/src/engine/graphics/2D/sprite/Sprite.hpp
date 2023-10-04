/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Sprite
*/

#pragma once

extern "C" {
    #include <raylib.h>
}

#include <string>

#include "../../../IRElement.hpp"

#include "../texture/Texture.hpp"
#include "../../../maths/Vector.hpp"
#include "../../../maths/Rectangle.hpp"

namespace Fuzzy {
    namespace Engine {
        class Sprite {
            public:
                Sprite(){};
                Sprite(Texture text, int cols, int rows);
                Sprite(std::string text, int cols, int rows);
                ~Sprite() = default;

                void load(Texture text, int cols, int rows);
                void load(std::string text, int cols, int rows);
                void draw(Vector2d pos, Color color);
                void draw(Vector2d pos, int rows, int cols, Color color);
                void drawLeft(Vector2d pos, Color color);
                void drawDown(Vector2d pos, Color color);
                void unload();
                Rectangle *getRect() {return &_rect;};

            protected:
            private:
                bool _isLoaded = false;
                Texture _texture;
                Rectangle _rect;
        };

    }
}