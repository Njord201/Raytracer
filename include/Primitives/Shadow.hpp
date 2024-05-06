/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Shadow
*/

#pragma once

#include "Primitives/IPrimitive.hpp"

#include <vector>
#include <memory>

class Shadow {

    public:

        /**
         * @brief Construct a new Shadow object
         *
         * @param primitives list of primitives
         */
        Shadow(const std::vector<std::shared_ptr<Primitive::IPrimitive>>& primitives) : _primitives(primitives) {};

        /**
         * @brief Destroy the Shadow object
         *
         */
        ~Shadow() = default;

        /**
         * @brief return if there is a shadow
         *
         * @return true
         * @return false
         */
        bool isShadow();

    private:
        std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
};
