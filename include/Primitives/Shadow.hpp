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

namespace Primitives {
    class Shadow;
};

class Primitives::Shadow {

    public:

        /**
         * @brief Construct a new Shadow object.
         *
         * @param primitives list of primitives
         */
        Shadow(const std::vector<std::shared_ptr<Primitive::IPrimitive>>& primitives);

        /**
         * @brief Destroy the Shadow object.
         *
         */
        ~Shadow() = default;

        /**
         * @brief Return if there is a shadow.
         *
         * @return true
         * @return false
         */
        bool isShadow(const Math::Vector3D& vectorLightToPoint, const Math::Point3D& hitPoint) const;

    private:
        std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
};
