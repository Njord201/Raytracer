/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "Ray.hpp"
#include "Vector3D.hpp"

namespace Primitive {

    class IPrimitive {

        public:

            /**
             * @brief Destroy the IPrimitive object
             *
             */
            virtual ~IPrimitive() = default;

            /**
             * @brief compute the hit point of a primitive with a ray
             *
             * @param ray Vector3D
             * @return Math::Point3D 
             */
            virtual Math::Point3D hit(const Raytracer::Ray& ray) const = 0;
    };
};
