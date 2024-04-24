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

Math::Point3D Primitive::Sphere::hitPoint(const Raytracer::Ray& ray) const
{
    double a = ray.direction().length_squared();
    double b = 2 * ray.origin().dot(ray.direction());
    double c = ray.origin().dot(ray.origin()) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return Math::Point3D(0,0,0);
    
    //else
    double hitValue = -b - sqrt(discriminant) / 2 * a;
    Math::Point3D hitPoint = ray.origin() + ray.direction() * hitValue;
}
