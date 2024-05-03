/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Primitives/Cylinder.hpp"

#include <cmath>

using std::sqrt;

Primitive::Cylinder::Cylinder() : _origin(0,0,0), _radius(1), _axis(0){}

Primitive::Cylinder::Cylinder(const Math::Point3D& origin, double radius, double axis) : _origin(origin), _radius(radius), _axis(axis){}


Math::Point3D Primitive::Cylinder::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    rayOrigin = Math::Point3D(0, rayOrigin.y(), rayOrigin.z());
    Math::Vector3D rayDirection = ray.direction();
    rayDirection = Math::Vector3D(0, rayDirection.y(), rayDirection.z());

    Math::Vector3D vectorCylinderToRay(rayOrigin.x() - _origin.x(), rayOrigin.y() - _origin.y(), rayOrigin.z() - _origin.z());
    double a = rayDirection.dot(rayDirection);
    double b = 2 * vectorCylinderToRay.dot(rayDirection);
    double c = vectorCylinderToRay.dot(vectorCylinderToRay) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;

    if (!IS_HIT(discriminant))
        return Math::Point3D(-1,-1,-1);

    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);

    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    return hitPoint;
}

void Primitive::Cylinder::setOrigin(const Math::Point3D& origin)
{
    this->_origin = origin;
}

void Primitive::Cylinder::setAxis(double axis)
{
    this->_axis = axis;
}

void Primitive::Cylinder::setRadius(double radius)
{
    this->_radius = radius;
}
