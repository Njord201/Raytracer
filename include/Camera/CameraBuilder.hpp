/*
** EPITECH PROJECT, 2024
** Camera
** File description:
** Raytracer
*/

#pragma once

#include "Camera/Camera.hpp"

namespace Raytracer {
    class CameraBuilder;
}

class Raytracer::CameraBuilder {
    public:

        /**
         * @brief Construct a new CameraBuilder object.
         *
         */
        CameraBuilder() = default;

        /**
         * @brief Destructor a CameraBuilder object.
         *
         */
        ~CameraBuilder() = default;

        /**
         * @brief Set the Origin object.
         *
         * @param origin Origin to set
         */
        CameraBuilder& setOrigin(Math::Point3D origin);

        /**
         * @brief Set the Screen object.
         *
         * @param screen Screen to set
         */
        CameraBuilder& setScreen(Raytracer::Rectangle3D screen);

        /**
         * @brief Set the Fov object.
         *
         * @param fov Fov to set
         */
        CameraBuilder& setFov(double fov);

        /**
         * @brief Set the Rotation object.
         *
         * @param rotation Rotation Vector to set
         */
        CameraBuilder& setRotation(Math::Vector3D rotation);

        /**
         * @brief Set the Resolution object.
         *
         * @param width of image
         * @param height of image
         */
        CameraBuilder& setResolution(double width, double height);

        /**
         * @brief Build the Camera object.
         * 
         * @return Camera to build
         */
        Camera build(void);

    private:
        Camera camera;
};
