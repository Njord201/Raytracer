/*
** EPITECH PROJECT, 2024
** Mesh Primitive
** File description:
** Raytracer
*/

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Optimisation/OctreeRules.hpp"

#include <vector>

namespace Primitive {
    class Mesh;
};

class Primitive::Mesh : public Primitive::IPrimitive {

    public:

        /**
         * @brief Construct a new mesh object.
         *
         */
        Mesh();

        /**
         * @brief Destroy the mesh object.
         *
         */
        ~Mesh() = default;

        /**
         * @brief Compute the hit point of a Mesh with a ray
         *
         * @param ray Vector3D
         * @return Math::Point3D
         */
        Math::Point3D hitPoint(const Raytracer::Ray& ray) override;

        /**
         * @brief Get the normal of the object.
         *
         * @param hitPoint to compute the normal
         * @param ray of the camera
         * @return Math::Vector3D
         */
        Math::Vector3D getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const;

        /**
         * @brief Set the material.
         *
         * @param material New material to set
         */
        void setMaterial(std::shared_ptr<Material::IMaterial> material);

        /**
         * @brief Get the material object.
         *
         * @return std::shared_ptr<Material::IMaterial>
         */
        std::shared_ptr<Material::IMaterial> getMaterial() const;

        /**
         * @brief Get the collider box object.
         *
         * @return Octree::cubeCollider
         */
        Octree::cubeCollider getColliderBox() const override;

        /**
         * @brief Add a primitive to the mesh.
         *
         * @param primitive to add
         */
        void add(std::shared_ptr<Primitive::IPrimitive> primitive);

    private:

        std::shared_ptr<Material::IMaterial>                _material;
        Octree::cubeCollider                                _collider;
        std::shared_ptr<Primitive::IPrimitive>              _lastHit;
        std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
};
