/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Vector
*/

#pragma once

#include <array>

extern "C" {
    #include <raylib.h>
}

#include "../IRElement.hpp"

namespace Fuzzy {
    namespace Engine {

        template <typename U, int S = 2> class Vector2D : public IRElement<::Vector2> {
            public:
                Vector2D(::Vector2 vector) : x(vector.x), y(vector.y) {};
                Vector2D(U x, U y) : x(x), y(y) {};
                ~Vector2D() = default;

                ::Vector2 getSource()
                {
                    return ::Vector2{.x = static_cast<float>(x), .y = static_cast<float>(y)};
                }

                U x, y;
        };

        using Vector2i = Vector2D<int>;
        using Vector2d = Vector2D<double>;

        template <typename V> class Vector3D : public IRElement<::Vector3> {
            public:
                Vector3D(::Vector3 vector) : x(vector.x), y(vector.y), z(vector.z) {};
                Vector3D(V x, V y, V z) : x(x), y(y), z(z) {};
                ~Vector3D() = default;

                ::Vector3 getSource()
                {
                    return ::Vector3{.x = static_cast<float>(x), .y = static_cast<float>(y), .z = static_cast<float>(z)};
                }

                V x, y, z;
        };


        using Vector3i = Vector3D<int>;
        using Vector3f = Vector3D<float>;
        using Vector3d = Vector3D<double>;
    }
}
