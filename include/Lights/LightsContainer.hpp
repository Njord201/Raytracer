/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightsContainer
*/

#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "ILight.hpp"

namespace Light {

    class LightsContainer {

        public:

            /**
             * @brief Construct a new Lights Container object.
             *
             */
            LightsContainer() = default;

            /**
             * @brief Destroy the Lights Container object.
             *
             */
            ~LightsContainer() = default;

            /**
             * @brief Add a Light to the container.
             *
             * @param Light to add
             */
            void add(std::shared_ptr<Light::ILight> Light);

            /**
             * @brief Clear the container.
             *
             */
            void clear();

            /**
             * @brief Get the Lights List object.
             *
             * @return std::vector<std::shared_ptr<Light::ILight>>
             */
            std::vector<std::shared_ptr<Light::ILight>> getLightsList(void) const;

            /**
             * @brief Compute the color point with lights.
             *
             * @param primitiveNormal normal to the hitpoint
             * @param hitPoint hitpoint
             * @param color color
             * @param shadow Primitive::Shadow class to handle shadows
             * @return Math::Point3D color
             */
            Math::Point3D computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const;

        private:

            std::vector<std::shared_ptr<Light::ILight>> _Lights;
    };
};
