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
             * @param material Material of Cone
             */
            Cone(const Math::Point3D& origin, double radius, std::shared_ptr<Material::IMaterial> material);

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
             * @return Origin of Cone
             */
            Math::Point3D getOrigin() const;

            /**
             * @brief Get the Origin object
             * @return Radius of Cone
             */
            double getRadius() const;

            /**
             * @brief Get the Material object
             * @return Material of Cone
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const;

        private:
            Math::Point3D                        _origin;
            double                               _radius;
            std::shared_ptr<Material::IMaterial> _material;
    };
};
