/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "Primitives/Sphere.hpp"

#include <cmath>

using std::sqrt;

Primitive::Sphere::Sphere() : _rotation(0,0,0), _origin(0,0,0), _radius(1), _material(nullptr){}

Primitive::Sphere::Sphere(const Math::Point3D& origin, double radius, std::shared_ptr<Material::IMaterial> material) :
_origin(origin), _radius(radius), _material(material){}

Math::Point3D Primitive::Sphere::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();
    rayOrigin.rotateX(this->_rotation.x());
    rayOrigin.rotateY(this->_rotation.y());
    rayOrigin.rotateZ(this->_rotation.z());
    rayDirection.rotateX(this->_rotation.x());
    rayDirection.rotateY(this->_rotation.y());
    rayDirection.rotateZ(this->_rotation.z());

    Math::Vector3D vectorSphereToRay(rayOrigin.x() - _origin.x(), rayOrigin.y() - _origin.y(), rayOrigin.z() - _origin.z());
    vectorSphereToRay.rotateX(this->_rotation.x());
    vectorSphereToRay.rotateY(this->_rotation.y());
    vectorSphereToRay.rotateZ(this->_rotation.z());
    double a = rayDirection.dot(rayDirection);
    double b = 2 * vectorSphereToRay.dot(rayDirection);
    double c = vectorSphereToRay.dot(vectorSphereToRay) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;

    if (!IS_HIT(discriminant))
        return Math::Point3D(-1,-1,-1);

    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);

    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    Math::Vector3D rayOriginToHit = hitPoint - rayOrigin;
    if (IS_INVERSE(rayOriginToHit.x(), rayDirection.x()) || IS_INVERSE(rayOriginToHit.y(), rayDirection.y()) || IS_INVERSE(rayOriginToHit.z(), rayDirection.z()))
        return Math::Point3D(-1,-1,-1);
    hitPoint.rotateX(this->_rotation.x());
    hitPoint.rotateY(this->_rotation.y());
    hitPoint.rotateZ(this->_rotation.z());
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

Math::Vector3D Primitive::Sphere::getNormal(const Math::Vector3D& hitPoint) const
{
    return Math::Vector3D (hitPoint.x() - _origin.x(), hitPoint.y() - _origin.y(), hitPoint.z() - _origin.z());
}

void Primitive::Sphere::setRotation(Math::Vector3D rotation)
{
    this->_rotation = rotation;
}

