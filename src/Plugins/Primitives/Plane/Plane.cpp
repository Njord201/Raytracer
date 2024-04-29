/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

Primitive::Plane::Plane()
{
    _position = Math::Point3D(0, 0, 0);
    _axis = X;
}

Primitive::Plane::Plane(Primitive::Axis axis, double position)
{
    switch (axis) {
        case X:
            _position = Math::Point3D(position, 0, 0);
            break;
        case Y:
            _position = Math::Point3D(0, position, 0);
            break;
        case Z:
            _position = Math::Point3D(0, 0, position);
            break;
        default:
            break;
    }
    _axis = axis;
}

Math::Point3D Primitive::Plane::hitPoint(const Raytracer::Ray &ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    double t = 0;
    if (rayDirection.x() != 0)
        t = (_position.x() - rayOrigin.x()) / rayDirection.x();
    else if (rayDirection.y() != 0)
        t = (_position.y() - rayOrigin.y()) / rayDirection.y();
    else if (rayDirection.z() != 0)
        t = (_position.z() - rayOrigin.z()) / rayDirection.z();

    if (t < 0)
        return Math::Point3D(0, 0, 0);

    Math::Point3D hitPoint = rayOrigin + rayDirection * t;

    return hitPoint;
}
