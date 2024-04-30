/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include <cmath>

using std::sqrt;

Primitive::Sphere::Sphere() : _origin(0,0,0), _radius(1){}

Primitive::Sphere::Sphere(const Math::Point3D& origin, double radius) : _origin(origin), _radius(radius){}

Math::Point3D Primitive::Sphere::hitPoint(const Raytracer::Ray& r) const
{
    Math::Point3D rayOrigin = r.origin();
    Math::Vector3D rayDirection = r.direction();

    Math::Vector3D vectorSphereToRay(rayOrigin.x() - _origin.x(), rayOrigin.y() - _origin.y(), rayOrigin.z() - _origin.z());
    double a = rayDirection.dot(rayDirection);
    double b = 2 * vectorSphereToRay.dot(rayDirection);
    double c = vectorSphereToRay.dot(vectorSphereToRay) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;

    if (!IS_HIT(discriminant))
        return Math::Point3D(0,0,0);

    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);

    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    return hitPoint;
}
