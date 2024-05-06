/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#pragma once

#include <memory>

#include "IPrimitive.hpp"
#include "Materials/FlatColor.hpp"

namespace Primitive {

    class Sphere : public IPrimitive {

        public:

            /**
             * @brief Construct a new Sphere object
             *
             */
            Sphere();

            /**
             * @brief Construct a new Sphere object
             *
             * @param origin center of the sphere
             * @param radius of the sphere
             * @param material Material of Sphere
             */
            Sphere(const Math::Point3D& origin, double radius, std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Destroy the Sphere object
             *
             */
            ~Sphere() = default;

            /**
             * @brief return the hit point of the sphere
             *
             * @param ray vector3D
             * @return Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const override;

            /**
             * @brief Set the Origin object
             * @param origin New origin to set
             */
            void setOrigin(Math::Point3D origin);

            /**
             * @brief Set the Radius
             * @param radius New radius to set
             */
            void setRadius(double radius);

            /**
             * @brief Set the Material
             * @param material New material to set
             */
            void setMaterial(std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Get the Origin object
             * @return Origin of sphere
             */
            Math::Point3D getOrigin() const;

            /**
             * @brief Get the Origin object
             * @return Radius of sphere
             */
            double getRadius() const;

            /**
             * @brief Get the Material object
             * @return Material of sphere
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const override;

            /**
             * @brief Get the Normal of the object
             *
             * @param hitPoint to compute
             * @return Math::Vector3D
             */
            Math::Vector3D getNormal(const Math::Vector3D& hitPoint) const;

        private:
            Math::Point3D                        _origin;
            double                               _radius;
            std::shared_ptr<Material::IMaterial> _material;
    };
};
