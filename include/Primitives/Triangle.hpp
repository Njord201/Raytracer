/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Triangle
*/

#pragma once

#include <memory>

#include "IPrimitive.hpp"
#include "Materials/FlatColor.hpp"

namespace Primitive {

    class Triangle : public IPrimitive {

        public:

            /**
             * @brief Construct a new Triangle object.
             *
             */
            Triangle();

            Triangle(const Math::Point3D& vertex1, const Math::Point3D& vertex2, const Math::Point3D& vertex3, std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Destroy the Triangle object.
             *
             */
            ~Triangle() = default;

            /**
             * @brief Return the hit point of the triangle.
             *
             * @param ray vector3D
             * @return Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const override;

            void setVertex1(const Math::Point3D& vertex1);
            void setVertex2(const Math::Point3D& vertex2);
            void setVertex3(const Math::Point3D& vertex3);

            /**
             * @brief Set the Material.
             *
             * @param material New material to set
             */
            void setMaterial(std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Set the Rotation object.
             *
             * @param rotation - Rotation value
             */
            void setRotation(Math::Vector3D rotation);

            Math::Point3D getVertex1() const;
            Math::Point3D getVertex2() const;
            Math::Point3D getVertex3() const;

            /**
             * @brief Get the Material object.
             *
             * @return Material of triangle
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const override;

            /**
             * @brief Get the Normal of the object.
             *
             * @param hitPoint to compute the normal
             * @return Math::Vector3D
             */
            Math::Vector3D getNormal(const Math::Vector3D& hitPoint) const override;

        private:
            Math::Vector3D                       _rotation;
            Math::Point3D                        _vertex1;
            Math::Point3D                        _vertex2;
            Math::Point3D                        _vertex3;
            std::shared_ptr<Material::IMaterial> _material;
    };
};
