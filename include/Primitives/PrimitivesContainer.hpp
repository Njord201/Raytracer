/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PrimitivesContainer
*/

#pragma once

#include <vector>
#include <memory>

#include "IPrimitive.hpp"
#include "Lights/LightsContainer.hpp"

namespace Primitive {

    class PrimitivesContainer {

        public:

            /**
             * @brief Construct a new Primitives Container object.
             *
             */
            PrimitivesContainer() = default;

            /**
             * @brief Destroy the Primitives Container object.
             *
             */
            ~PrimitivesContainer() = default;

            /**
             * @brief Add a Primitive to the container.
             *
             * @param primitive to add
             */
            void add(std::shared_ptr<Primitive::IPrimitive> primitive);

            /**
             * @brief Clear the container.
             *
             */
            void clear();

            /**
             * @brief Return the color of hit point of a ray in all the primitives.
             *
             * @param ray Math::Vector3D
             * @param lights list of lights
             * @return Color
             */
            Color getColorPoint(const Raytracer::Ray& ray, const Light::LightsContainer& lights) const;

            /**
             * @brief Get the Primitives List object.
             *
             * @return std::vector<std::shared_ptr<Primitive::IPrimitive>>
             */
            std::vector<std::shared_ptr<Primitive::IPrimitive>> getPrimitivesList(void) const;

            /**
             * @brief Compute the color pixel of a primitive's hitpoint.
             *
             * @param primitive primitive to compute
             * @param hitPoint to check
             * @param lights list of lights
             * @return Math::Point3D
             */
            Color computeColor(const std::shared_ptr<Primitive::IPrimitive>& primitive, const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const;

        private:

            std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
    };
};
