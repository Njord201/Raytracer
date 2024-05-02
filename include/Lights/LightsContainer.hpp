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
             * @brief Construct a new Lights Container object
             *
             */
            LightsContainer() = default;

            /**
             * @brief Destroy the Lights Container object
             *
             */
            ~LightsContainer() = default;

            /**
             * @brief add a Light to the container
             *
             * @param Light to add
             */
            void add(std::shared_ptr<Light::ILight> Light);

            /**
             * @brief clear the container
             *
             */
            void clear();

            /**
             * @brief Get the Lights List object
             *
             * @return std::vector<std::shared_ptr<Light::ILight>>
             */
            std::vector<std::shared_ptr<Light::ILight>> getLightsList(void) const;

            /**
             * @brief compute the color point with lights
             *
             * @param primitiveNormal normal to the hitpoint
             * @return Math::Point3D color
             */
            Math::Point3D computeColor(const Math::Vector3D& primitiveNormal) const;

        private:

            std::vector<std::shared_ptr<Light::ILight>> _Lights;
    };
};
