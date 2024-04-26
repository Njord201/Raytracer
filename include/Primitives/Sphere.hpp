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
            ~Sphere();

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
             * @brief Get the Origin object
             * @return Origin of sphere
             */
            Math::Point3D getOrigin();
            
            /**
             * @brief Get the Origin object
             * @return Radius of sphere
             */
            double getRadius();

        private:
            Math::Point3D _origin;
            double _radius;
    };
};
