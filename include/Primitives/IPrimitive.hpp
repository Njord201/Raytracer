/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "Ray.hpp"
#include "Math/Vector3D.hpp"
    
#define IS_HIT(D) ((D >= 0) ? true : false)

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
            virtual Math::Point3D hitPoint(const Raytracer::Ray& ray) const = 0;
    };
};
