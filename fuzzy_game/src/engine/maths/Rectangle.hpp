/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Rectangle
*/

#pragma once

extern "C" {
    #include <raylib.h>
}

#include "../IRElement.hpp"
#include "Vector.hpp"

namespace Fuzzy {
    namespace Engine {
        class Rectangle : public IRElement<::Rectangle> {
            public:
                Rectangle() : x(0), y(0), width(1), height(1){};
                Rectangle(float posx, float posy, float recwidth, float recheight) : x(posx), y(posy), width(recwidth), height(recheight) {};
                Rectangle(const Rectangle &rec) {x = rec.x; y = rec.y; width = rec.width; height = rec.height; };
                ~Rectangle() = default;

                ::Rectangle getSource() {return {x, y, width, height}; };

                bool isColliding(Vector2d point) { return CheckCollisionPointRec(point.getSource(), {x, y, width, height}); };
                bool isColliding(Rectangle rec){ return CheckCollisionRecs(rec.getSource(), {x, y, width, height}); };


                float x;                // Rectangle top-left corner position x
                float y;                // Rectangle top-left corner position y
                float width;            // Rectangle width
                float height;           // Rectangle height

            protected:
            private:
        };
    }
}