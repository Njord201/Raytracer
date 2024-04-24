/*
** EPITECH PROJECT, 2024
** Rectangle3D
** File description:
** Raytracer
*/

#pragma once

#include "Ray.hpp"
#include <iostream>

namespace Raytracer {
    class Rectangle3D;
}

class Raytracer::Rectangle3D {
    public:

        /**
         * @brief Construct a new Rectangle 3D object
         *
         */
        Rectangle3D() = default;

        /**
         * @brief Construct a new Rectangle 3D object
         * 
         * @param origin bottom-left corner of the rectangle
         * @param bottom_side vector from the bottom-left corner of the rectangle
         * @param left_side vector from the bottom-left corner of the rectangle
         */
        Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side,
        Math::Vector3D left_side);

        /**
         * @brief Destructor a Rectangle 3D object
         *
         */
        ~Rectangle3D();
        
        /**
         * @brief returns the 3D coordinates of the point at the given location in our rectangle
         * 
         * @param u location u in rectangle
         * @param v location v in rectangle
         */
        Math::Point3D pointAt(double u, double v);

        /**
         * @brief Get origin of Rectangle 3D
         *
         */
        Math::Point3D getOrigin(void);

        /**
         * @brief Get bottom side of Rectangle 3D
         *
         */
        Math::Vector3D getBottomSide(void);

        /**
         * @brief Get left side of Rectangle 3D
         *
         */
        Math::Vector3D getLeftSide(void);

    private:
        Math::Point3D  _origin;
        Math::Vector3D _bottom_side;
        Math::Vector3D _left_side;
};
