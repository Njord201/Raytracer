/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "Ray.hpp"
#include "Math/Vector3D.hpp"
#include "Lights/LightsContainer.hpp"

#define IS_HIT(D) ((D >= 0) ? true : false)

namespace Primitive {

    enum Axis {
        X,
        Y,
        Z
    };

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

            /**
             * @brief compute the hit point color of a primitive
             *
             * @param hitPoint to compute the color
             * @param lights container of lights
             * @return Math::Point3D color
             */
            virtual Math::Point3D computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const = 0;
    };
};
