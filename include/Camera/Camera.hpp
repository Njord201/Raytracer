/*
** EPITECH PROJECT, 2024
** Camera
** File description:
** Raytracer
*/

#pragma once

#include <iostream>
#include "Ray.hpp"
#include "Rectangle.hpp"

namespace Raytracer {
    class Camera;
}

class Raytracer::Camera {
    public:

        /**
         * @brief Construct a new Camera object
         *
         */
        Camera();

        /**
         * @brief Construct a new Camera object
         * 
         * @param other other Camera object to copy
         */
        Camera(const Camera& other);

        /**
         * @brief Construct a new Rectangle 3D object
         * 
         * @param origin camera’s origin point
         * @param screen of camera
         */
        Camera(Math::Point3D origin, Rectangle3D screen);

        /**
         * @brief Destructor a Camera object
         *
         */
        ~Camera();

        /**
         * @brief return a ray, going from the camera to the coordinates u and v of the image
         * 
         * @param u location u in rectangle
         * @param v location v in rectangle
         */
        Raytracer::Ray ray(double u, double v);

        /**
         * @brief Get origin of Camera
         *
         */
        Math::Point3D getOrigin(void);

        /**
         * @brief Get Screen of Camera
         *
         */
        Raytracer::Rectangle3D getScreen(void);
        
        /**
         * @brief Get Fov of Camera
         *
         */
        double getFov(void);

        /**
         * @brief Get Rotation of Camera
         *
         */
        Math::Vector3D getRotation(void);

        /**
         * @brief Set origin of Camera
         *
         */
        void setOrigin(Math::Point3D origin);

        /**
         * @brief Set Screen of Camera
         *
         */
        void setScreen(Raytracer::Rectangle3D screen);

        /**
         * @brief Set Fov of Camera
         *
         */
        void setFov(double fov);

        /**
         * @brief Set Rotation of Camera
         *
         */
        void setRotation(Math::Vector3D rotation);

    private:

        Math::Point3D               _origin;
        Math::Vector3D              _rotation;
        Raytracer::Rectangle3D      _screen;
        double                      _fov;
};
