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
         * @brief Construct a new Camera object by another one.
         * 
         * @param other Camera object to duplicate
         * @return Camera& The new Camera object
         */
        Camera& operator=(const Camera& other);

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
        Math::Point3D getOrigin(void) const;

        /**
         * @brief Get Screen of Camera
         *
         */
        Raytracer::Rectangle3D getScreen(void) const;

        /**
         * @brief Get Fov of Camera
         *
         */
        double getFov(void) const;

        /**
         * @brief Get Rotation of Camera
         *
         */
        Math::Vector3D getRotation(void) const;

        /**
         * @brief Get Resolution of Camera
         *
         */
        std::pair<double, double> getResolution(void) const;

        /**
         * @brief Get the antialiasing object.
         *
         * @return int Value of antialiasing
         */
        int getAntialiasing(void) const;

        /**
         * @brief Set the Origin object
         *
         * @param origin Origin to set
         */
        void setOrigin(Math::Point3D origin);

        /**
         * @brief Set the Screen object
         *
         * @param screen Screen to set
         */
        void setScreen(Raytracer::Rectangle3D screen);

        /**
         * @brief Set the Fov object
         *
         * @param fov Fov to set
         */
        void setFov(double fov);

        /**
         * @brief Set the Rotation object
         *
         * @param rotation Rotation Vector to set
         */
        void setRotation(Math::Vector3D rotation);

        /**
         * @brief Set the Resolution object
         *
         * @param width of image
         * @param height of image
         */
        void setResolution(double width, double height);

        /**
         * @brief Set the antialiasing object.
         *
         * @param antialiasing Value of antialiasing
         */
        void setAntialiasing(int antialiasing);

    private:
        int                         _antialiasing;
        Math::Point3D               _origin;
        Math::Vector3D              _rotation;
        Raytracer::Rectangle3D      _screen;
        double                      _fov;
        std::pair<double, double>   _resolution;
};
