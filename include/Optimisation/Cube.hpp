/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#pragma once

#include <vector>

#include "OctreeRules.hpp"
#include "Primitives/IPrimitive.hpp"

using IPrimitive = Primitive::IPrimitive;

namespace Octree {

    /**
     * @brief Cube class for the Octree subdivision.
     *
     */
    class Cube;

};

class Cube {
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
         */
        Cube(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);

        /**
         * @brief Construct a new Cube object
         *
         */
        Cube() = default;

        /**
         * @brief Destroy the Cube object
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
        void setCollider(const Octree::cubeCollider& collider);

        /**
         * @brief Get the collider of the cube.
         *
         * @return Octree::cubeCollider - collider of the cube.
         */
        Octree::cubeCollider getCollider() const;

        /**
         * @brief Indentify all primitives in the cube or on a side of the cube.
         *
         * @param primitives primitives to check.
         */
        void identifyPrimitives(const std::vector<IPrimitive>& primitives);

    private:
        Octree::cubeCollider    _collider;
        std::vector<IPrimitive> _primitives;
        std::vector<Cube>       _cubes;
};
