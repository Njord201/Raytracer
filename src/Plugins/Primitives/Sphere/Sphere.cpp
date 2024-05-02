/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "Primitives/Sphere.hpp"

#include <cmath>

using std::sqrt;

Primitive::Sphere::Sphere() : _origin(0,0,0), _radius(1), _material(nullptr){}

Primitive::Sphere::Sphere(const Math::Point3D& origin, double radius, std::shared_ptr<Material::IMaterial> material) :
_origin(origin), _radius(radius), _material(material){}

Math::Point3D Primitive::Sphere::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    Math::Vector3D vectorSphereToRay(rayOrigin.x() - _origin.x(), rayOrigin.y() - _origin.y(), rayOrigin.z() - _origin.z());
    double a = rayDirection.dot(rayDirection);
    double b = 2 * vectorSphereToRay.dot(rayDirection);
    double c = vectorSphereToRay.dot(vectorSphereToRay) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;

    if (!IS_HIT(discriminant))
        return Math::Point3D(-1,-1,-1);

    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);

    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    return hitPoint;
}

Math::Point3D Primitive::Sphere::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    Math::Vector3D sphereNormal(hitPoint.x() - _origin.x(), hitPoint.y() - _origin.y(), hitPoint.z() - _origin.z());

    return lights.computeColor(sphereNormal);

    // Math::Vector3D light(-8, -16, 8);
    // Math::Vector3D pl = light - hitPoint;

    // double n = sphereNormal.dot(pl);
    // double d  = sphereNormal.length() * pl.length();

    // double angle = acos(n / d) * 180 / M_PI;

    // double ambient = 0.4;
    // double diffuse = 0.6;

    // Math::Vector3D color(64, 255, 64);
    // double coeffLight = (1 - (angle * diffuse / 90));

    // if (angle <= 90 && ambient <= coeffLight)
    //         color *= coeffLight;
    // else
    //     color *= ambient;

    // return color;
}

void Primitive::Sphere::setOrigin(Math::Point3D origin)
{
    this->_origin = origin;
}

void Primitive::Sphere::setRadius(double radius)
{
    this->_radius = radius;
}

void Primitive::Sphere::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

Math::Point3D Primitive::Sphere::getOrigin() const
{
    return this->_origin;
}

double Primitive::Sphere::getRadius() const
{
    return this->_radius;
}

std::shared_ptr<Material::IMaterial> Primitive::Sphere::getMaterial() const
{
    return this->_material;
}
