/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray
*/

#pragma once

#include "Vector3D.hpp"

namespace Raytracer
{
    /**
     * @brief Ray class, (point and direction vectors)
     * 
     */
    class Ray {

        public:

            /**
             * @brief Construct a new Ray object
             * 
             */
            Ray() = default;

            /**
             * @brief Construct a new Ray object
             * 
             * @param origin point vector
             * @param direction vector direction
             */
            Ray(const Math::Point3D& origin, const Math::Vector3D& direction);

            /**
             * @brief Destroy the Ray object
             * 
             */
            ~Ray() = default;

            /**
             * @brief return the origin of the ray
             * 
             * @return const Math::Point3D& 
             */
            Math::Point3D& origin();

            /**
             * @brief return the direction of the ray
             * 
             * @return const Math::Vector3D& 
             */
            Math::Vector3D& direction();

            /**
             * @brief return the point vector of where point the ray at multiply by t
             * 
             * @param t multiplication factor
             * @return Math::Point3D 
             */
            Math::Point3D at(double t) const;

        private:

            Math::Point3D _origin;
            Math::Vector3D _direction;
    };
};
