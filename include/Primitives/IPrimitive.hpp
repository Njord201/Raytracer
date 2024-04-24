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
             * @brief compute the hit value of a primitive
             *
             * @param ray vector3D
             * @return double hit value
             */
            virtual double hit(const Raytracer::Ray& ray) const = 0;
    };
};
