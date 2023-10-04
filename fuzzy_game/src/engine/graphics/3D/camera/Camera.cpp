/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Fuzzy {
    namespace Engine {
        Camera::Camera(Vector3d position, Vector3d target, Vector3d rotation, float fov, int projection)
        {
            _camera = {position.getSource(), target.getSource(), rotation.getSource(), fov, projection};
        }

        void Camera::setPosition(Vector3d position, Vector3d target, Vector3d rotation)
        {
            _camera.position = position.getSource();
            _camera.target = target.getSource();
            _camera.up = rotation.getSource();
        }

        void Camera::updateMode(CameraMode mode)
        {
            UpdateCamera(&_camera, mode);
        }

        void Camera::drawGrid(int size, float meshSize)
        {
            DrawGrid(size, meshSize);
        }

        ::Camera3D Camera::getSource()
        {
            return (_camera);
        }
    }
}