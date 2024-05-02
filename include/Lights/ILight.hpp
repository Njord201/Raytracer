/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ILight
*/

#pragma once

#include "Math/Vector3D.hpp"

namespace Light {
    class ILight;

    typedef enum {
        ambient,
        point,
        directionnal
    } LightType;
};

class Light::ILight {

        public:

            /**
             * @brief Destroy the ILight object
             *
             */
            virtual ~ILight() = default;

            /**
             * @brief Get type of Light
             * @return The type of the light
             */
            virtual Light::LightType getType(void) const = 0;

            virtual Math::Point3D computeColor(const Math::Vector3D& primitiveNormal) const = 0;
    };
