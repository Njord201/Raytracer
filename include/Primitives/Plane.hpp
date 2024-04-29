/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#pragma once

#include "IPrimitive.hpp"

namespace Primitive {

    enum Axis {
        X,
        Y,
        Z
    };

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
             */
            Plane(Primitive::Axis axis, double position);

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

        private:
            Axis _axis;
            Math::Point3D _position;
    };
};