/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#include <cmath>
#include <string>
#include <iostream>

#include "RaytracerRules.hpp"
#include "Primitives/Plane.hpp"

Primitive::Plane::Plane()
{
    _position = Math::Point3D(0, 0, 0);
    _axis = X;
    _material = nullptr;
    _rotation = Math::Point3D(0,0,0);
}

Primitive::Plane::Plane(Primitive::Axis axis, double position, std::shared_ptr<Material::IMaterial> material)
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
    _material = material;
}

Math::Point3D Primitive::Plane::hitPoint(const Raytracer::Ray &ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    rayOrigin.rotateX(this->_rotation.x());
    rayOrigin.rotateY(this->_rotation.y());
    rayOrigin.rotateZ(this->_rotation.z());
    rayDirection.rotateX(this->_rotation.x());
    rayDirection.rotateY(this->_rotation.y());
    rayDirection.rotateZ(this->_rotation.z());

    if (_axis == X && rayDirection.x() == 0) {
        if (_position.x() == rayOrigin.x())
            return rayOrigin;
        return Math::Point3D(-1, -1, -1);
    }
    if (_axis == Y && rayDirection.y() == 0) {
        if (_position.y() == rayOrigin.y())
            return rayOrigin;
        return Math::Point3D(-1, -1, -1);
    }
    if (_axis == Z && rayDirection.z() == 0) {
        if (_position.z() == rayOrigin.z())
            return rayOrigin;
        return Math::Point3D(-1, -1, -1);
    }

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

    if (t < 0)
        return Math::Point3D(-1, -1, -1);

    Math::Point3D hitpoint = rayOrigin + rayDirection * t;
    hitpoint.rotateX(this->_rotation.x());
    hitpoint.rotateY(this->_rotation.y());
    hitpoint.rotateZ(this->_rotation.z());
    return hitpoint;
}

Primitive::Axis Primitive::Plane::getAxis(void) const
{
    return this->_axis;
}

void Primitive::Plane::setAxis(const Primitive::Axis &axis)
{
    this->_axis = axis;
}

void Primitive::Plane::setRotation(Math::Vector3D rotation)
{
    this->_rotation = rotation;
}

Math::Point3D Primitive::Plane::getPosition(void) const
{
    return this->_position;
}

void Primitive::Plane::setPosition(Math::Point3D position)
{
    this->_position = position;
}

std::shared_ptr<Material::IMaterial> Primitive::Plane::getMaterial() const
{
    return this->_material;
}

void Primitive::Plane::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

Math::Vector3D Primitive::Plane::getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const
{
    (void) hitPoint;

    Math::Vector3D normal;
    Math::Vector3D rayDirection = ray.direction();

    switch (_axis) {
        case Primitive::X:
            normal = Math::Point3D(1, 0, 0);
            break;
        case Primitive::Y:
            normal = Math::Point3D(0, 1, 0);
            break;
        case Primitive::Z:
            normal = Math::Point3D(0, 0, 1);
            break;
        default:
            normal = Math::Vector3D(0, 0, 0);
    }

    double n = normal.dot(rayDirection);
    double d  = normal.length() * rayDirection.length();

    double angle = acos(n / d) * 180 / M_PI;

    if (angle >= 90)
        return normal;
    return normal * -1;
}

Octree::cubeCollider Primitive::Plane::getColliderBox() const
{
    Octree::cubeCollider collider;

    collider.minX.second = _position.x();
    collider.minY.second = _position.y();
    collider.minZ.second = _position.z();
    collider.maxX.second = _position.x();
    collider.maxY.second = _position.y();
    collider.maxZ.second = _position.z();

    collider.maxX.first = false;
    collider.minX.first = false;
    collider.maxY.first = false;
    collider.minY.first = false;
    collider.maxZ.first = false;
    collider.minZ.first = false;

    if (_axis == Axis::X) {
        collider.minY.first = true;
        collider.minZ.first = true;
        collider.maxY.first = true;
        collider.maxZ.first = true;
    } else if (_axis == Axis::Y) {
        collider.minX.first = true;
        collider.minZ.first = true;
        collider.maxX.first = true;
        collider.maxZ.first = true;
    } else if (_axis == Axis::Z) {
        collider.minX.first = true;
        collider.minY.first = true;
        collider.maxX.first = true;
        collider.maxY.first = true;
    }
    return collider;
}
