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
            ~LightsContainer();

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
            std::vector<std::shared_ptr<Light::ILight>> getLightsList(void);

        private:

            std::vector<std::shared_ptr<Light::ILight>> _Lights;
    };
};
