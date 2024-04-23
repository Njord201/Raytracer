/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray
*/

#pragma once

#include "Vector3D.hpp"

namespace Raytracer
{
    class Ray {

        public:

            Ray() = default;
            Ray(const Math::Point3D& origin, const Math::Vector3D& direction);
            ~Ray() = default;

            const Math::Point3D& origin() const;
            const Math::Vector3D& direction() const;

            Math::Point3D at(double t) const;

        private:

            Math::Point3D _origin;
            Math::Vector3D _direction;
    };
};
