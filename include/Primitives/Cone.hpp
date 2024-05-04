/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#pragma once

#include <memory>

#include "IPrimitive.hpp"
#include "Materials/FlatColor.hpp"

namespace Primitive {

    class Cone : public IPrimitive {

        public:

            /**
             * @brief Construct a new Cone object
             *
             */
            Cone();

            /**
             * @brief Construct a new Cone object
             *
             * @param origin center of the Cone
             * @param radius of the Cone
             * @param axis of the Cone
             * @param material Material of Cone
             */
            Cone(const Math::Point3D& origin, double radius, Axis axis, std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Destroy the Cone object
             *
             */
            ~Cone() = default;

            /**
             * @brief return the hit point of the Cone
             *
             * @param ray vector3D
             * @return Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const override;

            /**
             * @brief compute the hit point color of a Cone
             *
             * @param hitPoint to compute the color
             * @param lights container of lights
             * @return Math::Point3D color
             */
            Math::Point3D computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const override;

            /**
             * @brief Set the Origin object
             * @param origin New origin to set
             */
            void setOrigin(Math::Point3D origin);

            /**
             * @brief Set the Angle
             * @param angle New angle to set
             */
            void setAngle(double angle);

            /**
             * @brief Set the Axis
             * @param axis New axis to set
             */
            void setAxis(Axis axis);

            /**
             * @brief Set the Material
             * @param material New material to set
             */
            void setMaterial(std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Get the Origin object
             * @return Origin of Cone
             */
            Math::Point3D getOrigin() const;

            /**
             * @brief Get the Angle object
             * @return Angle of Cone
             */
            double getAngle() const;

            /**
             * @brief Get the Axis object
             * @return Axis of Cone
             */
            Axis getAxis() const;

            /**
             * @brief Get the Material object
             * @return Material of Cone
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const;

        private:
            Math::Point3D                        _position;
            double                               _angle;
            Axis                                 _axis;
            std::shared_ptr<Material::IMaterial> _material;
    };
};