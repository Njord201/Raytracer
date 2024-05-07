/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#pragma once

#include <memory>

#include "IPrimitive.hpp"
#include "Materials/FlatColor.hpp"

namespace Primitive {

    class Plane : public IPrimitive {

        public:

            /**
             * @brief Construct a new Plane object
             *
             */
            Plane();

            /**
             * @brief Construct a new Plane object
             *
             * @param axis Axis of the plane
             * @param position offset on axis
             */
            Plane(Primitive::Axis axis, double position, std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Destroy the Plane object
             *
             */
            ~Plane() = default;

            /**
             * @brief return the hit point of the plane
             *
             * @param ray ray to check vector3D
             * @return Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const override;

            /**
             * @brief Get the Axis object
             *
             * @return Axis The axis of Plane Object
             */
            Primitive::Axis getAxis(void) const;

            /**
             * @brief Set the Axis object
             *
             * @param axis The axis of Plane Object to set
             */
            void setAxis(const Primitive::Axis &axis);

            /**
             * @brief Get the Position object plane
             *
             * @return Math::Point3D Position of Plane Object
             */
            Math::Point3D getPosition(void) const;

            /**
             * @brief Set the Position object
             *
             * @param position Position to set
             */
            void setPosition(Math::Point3D position);

            /**
             * @brief Get the Material object
             * @return Material of plane
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const override;

            /**
             * @brief Set the Material
             * @param material New material to set
             */
            void setMaterial(std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Get the Normal of the object
             *
             * @param hitPoint to have the normal
             * @return Math::Vector3D
             */
            Math::Vector3D getNormal(const Math::Vector3D& hitPoint) const;

        private:
            Primitive::Axis                         _axis;
            Math::Point3D                           _position;
            std::shared_ptr<Material::IMaterial>    _material;
    };
};
