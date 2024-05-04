/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#include <iostream>
#include <string>

#include "Primitives/Plane.hpp"

Primitive::Plane::Plane()
{
    _position = Math::Point3D(0, 0, 0);
    _axis = X;
    _material = nullptr;
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

    if (_axis == X && rayDirection.x() == 0)
        return Math::Point3D(0, 0, 0);
    if (_axis == Y && rayDirection.y() == 0)
        return Math::Point3D(0, 0, 0);
    if (_axis == Z && rayDirection.z() == 0)
        return Math::Point3D(0, 0, 0);

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
    return rayDirection * t;
}

Primitive::Axis Primitive::Plane::getAxis(void) const
{
    return this->_axis;
}

void Primitive::Plane::setAxis(const Primitive::Axis &axis)
{
    this->_axis = axis;
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

Math::Point3D Primitive::Plane::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
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
