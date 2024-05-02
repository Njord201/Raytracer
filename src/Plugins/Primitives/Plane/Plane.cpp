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

    if (_axis == X && rayDirection.x() == 0)
        return Math::Point3D(0, 0, 0);
    if (_axis == Y && rayDirection.y() == 0)
        return Math::Point3D(0, 0, 0);
    if (_axis == Z && rayDirection.z() == 0)
        return Math::Point3D(0, 0, 0);

    double t = 0;
    if (_axis == X) {
        double pos = _position.x();
        t = (pos - rayOrigin.x()) / rayDirection.x();
    }
    if (_axis == Y) {
        double pos = _position.y();
        t = (pos - rayOrigin.y()) / rayDirection.y();
    }
    if (_axis == Z) {
        double pos = _position.z();
        t = (pos - rayOrigin.z()) / rayDirection.z();
    }
    return rayDirection * t;
}

Math::Point3D Primitive::Plane::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    (void) hitPoint;
    (void) lights;
    return Math::Point3D(255, 0, 255);
}
