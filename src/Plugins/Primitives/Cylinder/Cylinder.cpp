/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Primitives/Cylinder.hpp"

#include <cmath>

using std::sqrt;

Primitive::Cylinder::Cylinder() : _origin(0,0,0), _radius(1), _axis(X){}

Primitive::Cylinder::Cylinder(const Math::Point3D& origin, double radius, Primitive::Axis axis) : _origin(origin), _radius(radius), _axis(axis){}

static Math::Point3D getRayOriginByAxis(const Raytracer::Ray& ray, const Primitive::Axis axis)
{
    Math::Point3D rayOrigin = ray.origin();

    switch (axis) {
        case Primitive::X:
            rayOrigin = Math::Point3D(0, rayOrigin.y(), rayOrigin.z());
            break;
        case Primitive::Y:
            rayOrigin = Math::Point3D(rayOrigin.x(), 0, rayOrigin.z());
            break;
        case Primitive::Z:
            rayOrigin = Math::Point3D(rayOrigin.x(), rayOrigin.y(), 0);
            break;
    }
    return rayOrigin;
}

static Math::Vector3D getRayDirectionByAxis(const Raytracer::Ray& ray, const Primitive::Axis axis)
{
    Math::Vector3D rayDirection = ray.direction();

    switch (axis) {
        case Primitive::X:
            rayDirection = Math::Vector3D(0, rayDirection.y(), rayDirection.z());
            break;
        case Primitive::Y:
            rayDirection = Math::Vector3D(rayDirection.x(), 0, rayDirection.z());
            break;
        case Primitive::Z:
            rayDirection = Math::Vector3D(rayDirection.x(), rayDirection.y(), 0);
            break;
    }
    return rayDirection;
}

Math::Point3D Primitive::Cylinder::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = getRayOriginByAxis(ray, _axis);
    Math::Vector3D rayDirection = getRayDirectionByAxis(ray, _axis);

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

void Primitive::Cylinder::setRadius(double radius)
{
    this->_radius = radius;
}

Math::Point3D Primitive::Cylinder::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    (void) hitPoint;
    (void) lights;

    // TODO : compute the color based on the normal of the normal of the hitpoint
    // on the plane, the material and lights

    //example :
    // if (_material->getType() == Material::MaterialType::FlatColor) {
    //     std::shared_ptr<FlatColor> planeFlatColor = std::dynamic_pointer_cast<FlatColor>(getMaterial());
    //     return lights.computeColor(planeNormal, hitPoint, Math::Point3D(planeFlatColor->getR(), planeFlatColor->getG(), planeFlatColor->getB()));
    // }

    return Math::Point3D(255, 0, 255);
}

void Primitive::Cylinder::setAxis(const Primitive::Axis &axis)
{
    this->_axis = axis;
}
