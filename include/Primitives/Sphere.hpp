/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "IPrimitive.hpp"

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
             */
            Sphere(const Math::Point3D& origin, double radius);

            /**
             * @brief Destroy the Sphere object
             *
             */
            ~Sphere() = default;

            /**
             * @brief return the hit value of the sphere
             *
             * @param ray vector3D
             * @return double hit, -1 instead
             */
            double hit(const Raytracer::Ray& ray) const override;

        private:

            Math::Point3D _origin;
            double _radius;
    };
};