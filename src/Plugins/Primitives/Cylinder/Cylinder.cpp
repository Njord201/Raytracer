/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Primitives/Cylinder.hpp"
#include <iostream>
#include <cmath>
#include "RaytracerRules.hpp"

using std::sqrt;

Primitive::Cylinder::Cylinder() : _rotation(0,0,0), _origin(0,0,0), _radius(1), _axis(X){}

Primitive::Cylinder::Cylinder(const Math::Point3D& origin, double radius, Primitive::Axis axis) : _origin(origin), _radius(radius), _axis(axis){}

static Math::Point3D getRayOriginByAxis(const Raytracer::Ray& ray, const Primitive::Axis axis, Math::Point3D rotation)
{
    Math::Point3D rayOrigin = ray.origin();
    rayOrigin.rotateX(rotation.x());
    rayOrigin.rotateY(rotation.y());
    rayOrigin.rotateZ(rotation.z());

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

static Math::Vector3D getRayDirectionByAxis(const Raytracer::Ray& ray, const Primitive::Axis axis, Math::Point3D rotation)
{
    Math::Vector3D rayDirection = ray.direction();

    rayDirection.rotateX(rotation.x());
    rayDirection.rotateY(rotation.y());
    rayDirection.rotateZ(rotation.z());

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
    Math::Point3D rayOrigin = getRayOriginByAxis(ray, _axis, this->_rotation);
    Math::Vector3D rayDirection = getRayDirectionByAxis(ray, _axis, this->_rotation);

    Math::Vector3D vectorCylinderToRay(rayOrigin.x() - _origin.x(),
                                       rayOrigin.y() - _origin.y(),
                                       rayOrigin.z() - _origin.z());
    vectorCylinderToRay.rotateX(this->_rotation.x());
    vectorCylinderToRay.rotateY(this->_rotation.y());
    vectorCylinderToRay.rotateZ(this->_rotation.z());

    double a = rayDirection.dot(rayDirection);
    double b = 2 * vectorCylinderToRay.dot(rayDirection);
    double c = vectorCylinderToRay.dot(vectorCylinderToRay) - _radius * _radius;

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

void Primitive::Cylinder::setRotation(Math::Vector3D rotation)
{
    this->_rotation = rotation;
}

void Primitive::Cylinder::setOrigin(const Math::Point3D& origin)
{
    this->_origin = origin;
}

void Primitive::Cylinder::setRadius(double radius)
{
    this->_radius = radius;
}

void Primitive::Cylinder::setAxis(const Primitive::Axis &axis)
{
    this->_axis = axis;
}

std::shared_ptr<Material::IMaterial> Primitive::Cylinder::getMaterial() const
{
    return this->_material;
}

void Primitive::Cylinder::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

Math::Vector3D Primitive::Cylinder::getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const
{
    (void) ray;
    //TODO : fix the computation of the cylinder normal
    return Math::Vector3D (hitPoint.x() - _origin.x(), hitPoint.y() - _origin.y(), hitPoint.z() - _origin.z());
}

Optimisation::cubeCollider Primitive::Cylinder::getColliderBox() const
{
    Optimisation::cubeCollider collider;

    collider.maxX.second = _origin.x() + _radius;
    collider.minX.second = _origin.x() - _radius;
    collider.maxY.second = _origin.y() + _radius;
    collider.minY.second = _origin.y() - _radius;
    collider.maxZ.second = _origin.z() + _radius;
    collider.minZ.second = _origin.z() - _radius;

    collider.maxX.first = false;
    collider.minX.first = false;
    collider.maxY.first = false;
    collider.minY.first = false;
    collider.maxZ.first = false;
    collider.minZ.first = false;

    if (_axis == Axis::X) {
        collider.minX.first = true;
        collider.maxX.first = true;
    } else if (_axis == Axis::Y) {
        collider.minY.first = true;
        collider.maxY.first = true;
    } else {
        collider.minZ.first = true;
        collider.maxZ.first = true;
    }
    return collider;
}
