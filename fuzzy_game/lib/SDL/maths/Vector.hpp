/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Vector
*/

#pragma once

#include <array>

namespace SDL
{

    template <typename U>
    class Vector2D
    {
    public:
        Vector2D(U x, U y) : x(x), y(y){};
        ~Vector2D() = default;

        U x, y;

        Vector2D<U> operator+(const Vector2D<U> &other)
        {
            return Vector2D<U>(x + other.x, y + other.y);
        }

        Vector2D<U> operator-(const Vector2D<U> &other)
        {
            return Vector2D<U>(x - other.x, y - other.y);
        }

        Vector2D<U> operator*(const Vector2D<U> &other)
        {
            return Vector2D<U>(x * other.x, y * other.y);
        }

        Vector2D<U> operator*(const U &other)
        {
            return Vector2D<U>(x * other, y * other);
        }
    };

    using Vector2i = Vector2D<int>;
    using Vector2d = Vector2D<double>;

    template <typename V>
    class Vector3D 
    {
    public:
        Vector3D(V x, V y, V z) : x(x), y(y), z(z){};
        ~Vector3D() = default;

        V x, y, z;
    };

    using Vector3i = Vector3D<int>;
    using Vector3f = Vector3D<float>;
    using Vector3d = Vector3D<double>;

}
