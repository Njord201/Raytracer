/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "Ray.hpp"
#include "Math/Vector3D.hpp"
#include "Materials/IMaterial.hpp"
#include "Optimisation/OctreeRules.hpp"

#include <memory>

#define IS_HIT(D) ((D >= 0) ? true : false)

namespace Primitive {

    enum Axis {
        X,
        Y,
        Z
    };

    class IPrimitive {

        public:

            /**
             * @brief Destroy the IPrimitive object
             *
             */
            virtual ~IPrimitive() = default;

            /**
             * @brief compute the hit point of a primitive with a ray
             *
             * @param ray Vector3D
             * @return Math::Point3D
             */
            virtual Math::Point3D hitPoint(const Raytracer::Ray& ray) const = 0;

            /**
             * @brief Get the Normal of the object.
             *
             * @param hitPoint to compute the normal
             * @return Math::Vector3D
             */
            virtual Math::Vector3D getNormal(const Math::Vector3D& hitPoint) const = 0;

            /**
             * @brief Get the Material object.
             *
             * @return std::shared_ptr<Material::IMaterial>
             */
            virtual std::shared_ptr<Material::IMaterial> getMaterial() const = 0;

            /**
             * @brief Get the collider box object.
             *
             * @return Octree::cubeCollider
             */
            virtual Octree::cubeCollider getColliderBox() const = 0;
    };
};
