/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ILight
*/

#pragma once

#include "Color.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/Shadow.hpp"

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
             * @brief Destroy the ILight object.
             *
             */
            virtual ~ILight() = default;

            /**
             * @brief Get type of Light.
             * @return The type of the light
             */
            virtual Light::LightType getType(void) const = 0;

            /**
             * @brief Get the Color object.
             *
             * @return Color
             */
            virtual Color getColor(void) const = 0;

            /**
             * @brief Compute the color point with lights.
             *
             * @param primitiveNormal normal to the hitpoint
             * @param hitPoint hitpoint
             * @param color color
             * @param shadow Primitive::Shadow class to handle shadows
             *
             * @return Color color
             */
            virtual Color computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const = 0;
    };
