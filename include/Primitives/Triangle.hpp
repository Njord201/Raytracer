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

            /**
             * @brief Construct a new Triangle object.
             *
             * @param vertex1 first edge of the triangle
             * @param vertex2 second edge of the triangle
             * @param vertex3 third edge of the triangle
             * @param material of the triangle
             */
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

            /**
             * @brief Set the Vertex1 object.
             *
             * @param vertex1 first edge of the triangle to set
             */
            void setVertex1(const Math::Point3D& vertex1);

            /**
             * @brief Set the Vertex2 object.
             *
             * @param vertex2 second edge of the triangle to set
             */
            void setVertex2(const Math::Point3D& vertex2);

            /**
             * @brief Set the Vertex3 object.
             *
             * @param vertex3 third edge of the triangle to set
             */
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

            /**
             * @brief Get the Vertex1 object.
             *
             * @return Math::Point3D
             */
            Math::Point3D getVertex1() const;

            /**
             * @brief Get the Vertex2 object.
             *
             * @return Math::Point3D
             */
            Math::Point3D getVertex2() const;

            /**
             * @brief Get the Vertex3 object.
             *
             * @return Math::Point3D
             */
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
             * @param ray of the camera
             * @return Math::Vector3D
             */
            Math::Vector3D getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const override;

            /**
             * @brief Create the two different normals of the triangle.
             *
             */
            void createNormals();

            /**
             * @brief Get the Triangle Normal object.
             *
             * @return Math::Vector3D
             */
            Math::Vector3D getTriangleNormal();

            /**
             * @brief Get the Triangle Inverse Normal object.
             *
             * @return Math::Vector3D
             */
            Math::Vector3D getTriangleInverseNormal();

            /**
             * @brief Set the Triangle Normal object.
             *
             * @param normal to set
             */
            void setTriangleNormal(const Math::Vector3D& normal);

            /**
             * @brief Set the Triangle Inverse Normal object
             *
             * @param inverseNormal to set
             */
            void setTriangleInverseNormal(const Math::Vector3D& inverseNormal);

            /**
             * @brief Get the collider box object.
             *
             * @return Octree::cubeCollider
             */
            Octree::cubeCollider getColliderBox() const override;

        private:
            Math::Vector3D                       _rotation;
            Math::Vector3D                       _normal;
            Math::Vector3D                       _inverseNormal;
            Math::Point3D                        _vertex1;
            Math::Point3D                        _vertex2;
            Math::Point3D                        _vertex3;
            std::shared_ptr<Material::IMaterial> _material;
    };
};
