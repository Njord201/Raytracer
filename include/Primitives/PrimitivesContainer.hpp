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

namespace Primitive {

    class PrimitivesContainer {

        public:

            /**
             * @brief Construct a new Primitives Container object
             *
             */
            PrimitivesContainer() = default;

            /**
             * @brief Destroy the Primitives Container object
             *
             */
            ~PrimitivesContainer() = default;

            /**
             * @brief add a Primitive to the container
             *
             * @param primitive to add
             */
            void add(std::shared_ptr<Primitive::IPrimitive> primitive);

            /**
             * @brief clear the container
             *
             */
            void clear();

            /**
             * @brief return the hit point of a ray in all the primitives
             *
             * @param ray Math::Vector3D
             * @return Math::Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const;

            /**
             * @brief Get the Primitives List object
             * 
             * @return std::vector<std::shared_ptr<Primitive::IPrimitive>> 
             */
            std::vector<std::shared_ptr<Primitive::IPrimitive>> getPrimitivesList(void) const;

        private:

            std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
    };
};
