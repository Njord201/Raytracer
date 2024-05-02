/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Primitives/Cylinder.hpp"

#include <cmath>

using std::sqrt;

Primitive::Cylinder::Cylinder() : _origin(0,0,0), _radius(1), _height(1){}

Primitive::Cylinder::Cylinder(const Math::Point3D& origin, double radius, double height) : _origin(origin), _radius(radius), _height(height){}

Math::Point3D Primitive::Cylinder::hitPoint(const Raytracer::Ray& r) const
{
    Math::Point3D rayOrigin = r.origin();
    Math::Vector3D rayDirection = r.direction();

    double a = rayDirection.x() * rayDirection.x() + rayDirection.z() * rayDirection.z();
    double b = 2 * (rayDirection.x() * (rayOrigin.x() - _origin.x()) + rayDirection.z() * (rayOrigin.z() - _origin.z()));
    double c = (rayOrigin.x() - _origin.x()) * (rayOrigin.x() - _origin.x()) + (rayOrigin.z() - _origin.z()) * (rayOrigin.z() - _origin.z()) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return Math::Point3D(0, 0, 0);
    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);
    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;
    if (hitPoint.y() >= _origin.y() && hitPoint.y() <= _origin.y() + _height)
        return hitPoint;
    else
        return Math::Point3D(0, 0, 0);
}

void Primitive::Cylinder::setOrigin(const Math::Point3D& origin)
{
    this->_origin = origin;
}

void Primitive::Cylinder::setHeight(double height)
{
    this->_height = height;
}

void Primitive::Cylinder::setRadius(double radius)
{
    this->_radius = radius;
}
