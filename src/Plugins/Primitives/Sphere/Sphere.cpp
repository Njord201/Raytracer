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

Primitive::Sphere::~Sphere()
{
}

Math::Point3D Primitive::Sphere::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    double a = rayDirection.dot(rayDirection);
    double b = 2 * rayOrigin.dot(rayDirection);
    double c = rayOrigin.dot(rayOrigin) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    
    if (!IS_HIT(discriminant))
        return Math::Point3D(0,0,0);
    
    double hitValue = -b - sqrt(discriminant) / 2 * a;
    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    return hitPoint;
}

void Primitive::Sphere::setOrigin(Math::Point3D origin)
{
    this->_origin = origin;
}

void Primitive::Sphere::setRadius(double radius)
{
    this->_radius = radius;
}

Math::Point3D Primitive::Sphere::getOrigin()
{
    return this->_origin;
}

double Primitive::Sphere::getRadius()
{
    return this->_radius;
}

