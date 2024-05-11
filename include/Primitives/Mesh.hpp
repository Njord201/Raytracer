/*
** EPITECH PROJECT, 2024
** Mesh Primitive
** File description:
** Raytracer
*/

#pragma once

#include "Primitives/IPrimitive.hpp"

namespace Primitive {
    class Mesh;
};

class Primitive::Mesh : public Primitive::IPrimitive {

    public:

        /**
         * @brief Construct a new Mesh object.
         *
         */
        Mesh();

        /**
         * @brief Destroy the Mesh object.
         *
         */
        ~Mesh() = default;

        /**
         * @brief compute the hit point of a Mesh with a ray
         *
         * @param ray Vector3D
         * @return Math::Point3D
         */
        Math::Point3D hitPoint(const Raytracer::Ray& ray) const;

        /**
         * @brief Get the Normal of the object.
         *
         * @param hitPoint to compute the normal
         * @param ray of the camera
         * @return Math::Vector3D
         */
        Math::Vector3D getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const;

        /**
         * @brief Set the Material.
         *
         * @param material New material to set
         */
        void setMaterial(std::shared_ptr<Material::IMaterial> material);

        /**
         * @brief Get the Material object.
         *
         * @return std::shared_ptr<Material::IMaterial>
         */
        std::shared_ptr<Material::IMaterial> getMaterial() const;

        /**
         * @brief Get the collider box object.
         *
         * @return Octree::cubeCollider
         */
        Octree::cubeCollider getColliderBox() const;

    private:

        std::shared_ptr<Material::IMaterial>    _material;
        Octree::cubeCollider                    _collider;
};