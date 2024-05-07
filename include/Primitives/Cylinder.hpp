/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "IPrimitive.hpp"
#include "Plane.hpp"

namespace Primitive {

    class Cylinder : public IPrimitive {

        public:

            /**
             * @brief Construct a new Cylinder object
             *
             */
            Cylinder();

            /**
             * @brief Construct a new Cylinder object
             *
             * @param origin center of the cylinder
             * @param radius of the cylinder
             * @param axis of the cylinder
             */
            Cylinder(const Math::Point3D& origin, double radius, Primitive::Axis axis);

            /**
             * @brief Destroy the Cylinder object
             *
             */
            ~Cylinder() = default;

            /**
             * @brief return the hit point of the cylinder
             *
             * @param ray vector3D
             * @return Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const override;

            /**
             * @brief set origin of cylinder
             *
             * @param hitPoint Point3D
             */
            void setOrigin(const Math::Point3D& origin);

            /**
             * @brief set axis of cylinder
             *
             * @param axis double
             */
            void setAxis(double axis);

            /**
             * @brief set radius of cylinder
             *
             * @param radius double
             */
            void setRadius(double radius);

            /**
             * @brief compute the hit point color of a cylinder
             *
             * @param hitPoint to compute the color
             * @param lights container of lights
             * @return Math::Point3D color
             */
            Color computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const override;

            /**
             * @brief Set the Axis object
             *
             * @param axis The axis of cylinder Object to set
             */
            void setAxis(const Primitive::Axis &axis);

            /**
             * @brief Get the Material object
             *
             * @return Material of cylinder
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const;

            /**
             * @brief Set the Material object
             *
             * @param material Material of cylinder
             */
            void setMaterial(std::shared_ptr<Material::IMaterial> material);
        private:

            Math::Point3D _origin;
            double _radius;
            Primitive::Axis _axis;
            std::shared_ptr<Material::IMaterial> _material;
    };
};
