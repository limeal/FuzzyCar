/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Camera
*/

#pragma once

#include <string>
extern "C" {
    #include <raylib.h>
}

#include "../../../maths/Vector.hpp"

namespace Fuzzy {
    namespace Engine {

        // Camera projection
        typedef enum
        {
            PERSPECTIVE = 0, // Perspective projection
            ORTHOGRAPHIC     // Orthographic projection
        } CameraProjection;

        enum CameraMode {
            FREE = CAMERA_FREE,
            FIRST_PERSON = CAMERA_FIRST_PERSON,
            THIRD_PERSON = CAMERA_THIRD_PERSON,
            ORBITAL = CAMERA_ORBITAL
        };

        class Camera {
            public:
                Camera(Vector3d position = Vector3d(0.0f, 0.0f, 0.0f), Vector3d target = Vector3d(1.0f, 0.0f, 0.0f), Vector3d up = Vector3d(0.0f, 1.0f, 0.0f), float fovy = 45.f, int projection = CameraProjection::PERSPECTIVE);
                ~Camera() = default;

                void setPosition(Vector3d position, Vector3d target, Vector3d rotation);
                
                Vector3d getPosition();
                Vector3d getTarget();
                Vector3d getRotation();
                ::Camera3D getSource();

                void updateMode(CameraMode mode);
                void drawGrid(int size, float meshSize);

            protected:
            private:
                ::Camera3D _camera;
        };

    }
}