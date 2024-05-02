/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "IPrimitive.hpp"

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
             * @param height of the cylinder
             */
            Cylinder(const Math::Point3D& origin, double radius, double height);

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
             * @brief return the normal of the cylinder
             *
             * @param hitPoint Point3D
             * @return Vector3D
             */
            void setOrigin(const Math::Point3D& origin);

            /**
             * @brief return the origin of the cylinder
             *
             * @return Point3D
             */
            void setHeight(double height);

            /**
             * @brief return the height of the cylinder
             *
             * @return double
             */
            void setRadius(double radius);
        private:

            Math::Point3D _origin;
            double _radius;
            double _height;
    };
};
