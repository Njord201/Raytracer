/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#pragma once

#include <vector>

#include "OctreeRules.hpp"
#include "Primitives/PrimitivesContainer.hpp"

using PrimitivesContainer = Primitive::PrimitivesContainer;

namespace Optimisation {

    /**
     * @brief Cube class for the Octree subdivision.
     *
     */
    class Cube;

};

class Optimisation::Cube {
    public:

        /**
         * @brief Construct a new Cube object.
         *
         * @param minX minX position
         * @param minY minY position
         * @param minZ minZ position
         * @param maxX maxX position
         * @param maxY maxY position
         * @param maxZ maxZ position
         * @param primitives primitives to check.
         */
        Cube(double minX, double minY, double minZ, double maxX, double maxY, double maxZ, PrimitivesContainer primitives, int nbRecursions);

        /**normal
         * @brief Construct a new Cube object.
         *
         * @param collider collider of the cube.
         * @param primitives primitives to check.
         * @param nbRecursions number of recursions.
         */
        Cube(cubeCollider collider, PrimitivesContainer primitives, int nbRecursions);

        /**
         * @brief Construct a new Cube object.
         *
         */
        Cube() = default;

        /**
         * @brief Destroy the Cube object.
         *
         */
        ~Cube() = default;

        /**
         * @brief Set the min X value.
         *
         * @param minX
         */
        void setMinX(double minX);

        /**
         * @brief Set the min Y value.
         *
         * @param minY
         */
        void setMinY(double minY);

        /**
         * @brief Set the min Z value.
         *
         * @param minZ
         */
        void setMinZ(double minZ);

        /**
         * @brief Set the max X value.
         *
         * @param maxX
         */
        void setMaxX(double maxX);

        /**
         * @brief Set the max Y value.
         *
         * @param maxY
         */
        void setMaxY(double maxY);

        /**
         * @brief Set the max Z value.
         *
         * @param maxZ
         */
        void setMaxZ(double maxZ);

        /**
         * @brief Get the min X value.
         *
         * @return double
         */
        double getMinX() const;

        /**
         * @brief Get the min Y value.
         *
         * @return double
         */
        double getMinY() const;

        /**
         * @brief Get the min Z value.
         *
         * @return double
         */
        double getMinZ() const;

        /**
         * @brief Get the max X value.
         *
         * @return double
         */
        double getMaxX() const;

        /**
         * @brief Get the max Y value.
         *
         * @return double
         */
        double getMaxY() const;

        /**
         * @brief Get the max Z value.
         *
         * @return double
         */
        double getMaxZ() const;

        /**
         * @brief Set the collider of the cube.
         *
         * @param collider collider to set.
         */
        void setCollider(const cubeCollider& collider);

        /**
         * @brief Get the collider of the cube.
         *
         * @return Octree::cubeCollider - collider of the cube.
         */
        cubeCollider getCollider() const;

        /**
         * @brief Get the primitives container object.
         *
         * @return PrimitivesContainer
         */
        PrimitivesContainer getPrimitivesContainer(void) const;

        /**
         * @brief Indentify all primitives in the cube or on a side of the cube.
         *
         * @param primitives primitives to check.
         */
        void identifyPrimitives(PrimitivesContainer primitives);

        /**
         * @brief Get the primitives to be calculated with a ray hits object.
         *
         * @param ray ray to check.
         * @return PrimitivesContainer
         */
        PrimitivesContainer getPrimitivesHits(const Raytracer::Ray ray) const;

    private:

        cubeCollider                    _collider;
        PrimitivesContainer             _primitives;
        std::vector<Cube>               _cubes;
        int                             _nbRecursions;
};
