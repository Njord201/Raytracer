/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

Raytracer::Ray::Ray(const Math::Point3D& origin, const Math::Vector3D& direction) : _origin(origin), _direction(direction) {}

const Math::Point3D& Raytracer::Ray::origin() const
{
    return _origin;
}

const Math::Vector3D& Raytracer::Ray::direction() const
{
    return _direction;
}

Math::Point3D Raytracer::Ray::at(double t) const
{
    Math::Point3D p = _direction;

    p *= t;
    p += _origin;

    return p;
}
