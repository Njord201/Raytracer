/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Octree
*/

#pragma once

#include <vector>

#include "Optimisation/Cube.hpp"
#include "Optimisation/OctreeRules.hpp"
#include "Primitives/PrimitivesContainer.hpp"

using PrimitivesContainer = Primitive::PrimitivesContainer;

namespace Optimisation {

    /**
     * @brief Octree class for the Octree subdivision.
     *
     */
    class Octree;
};

class Optimisation::Octree {
    public:

        /**
         * @brief Construct a new Octree object with a list of primitives.
         *
         * @param primitives primitives to study.
         * @param cubeCollider collider of the cube.
         */
        Octree(PrimitivesContainer primitives, cubeCollider cubeCollider);

        /**
         * @brief Construct a new Octree object.
         *
         */
        Octree() = default;

        /**
         * @brief Destroy the Octree object.
         *
         */
        ~Octree() = default;

        /**
         * @brief Get the primitives to be calculated with a ray hits object.
         *
         * @param ray ray to check.
         * @return PrimitivesContainer
         */
        PrimitivesContainer getPrimitivesHits(const Raytracer::Ray &ray) const;

    private:
        Cube   _cube;
};
