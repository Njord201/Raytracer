/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#include <iostream>
#include <string>

#include "Primitives/Plane.hpp"
#include "RaytracerRules.hpp"

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

    return rayOrigin + rayDirection * t;
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

static Math::Point3D getPlaneNormal(const Primitive::Axis axis)
{
    switch (axis) {
        case Primitive::X:
            return Math::Point3D(1, 0, 0);
        case Primitive::Y:
            return Math::Point3D(0, 1, 0);
        case Primitive::Z:
            return Math::Point3D(0, 0, 1);
        default:
            return Math::Point3D(0, 0, 0);
    }
}

Math::Point3D Primitive::Plane::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    Math::Vector3D planeNormal = getPlaneNormal(_axis);

    if (_material->getType() == Material::MaterialType::FlatColor) {
        std::shared_ptr<FlatColor> planeFlatColor = std::dynamic_pointer_cast<FlatColor>(getMaterial());
        return lights.computeColor(planeNormal, hitPoint, Math::Point3D(planeFlatColor->getR(), planeFlatColor->getG(), planeFlatColor->getB()));
    } else {
        // TODO: handle other material types see #55 (https://github.com/Njord201/Raytracer/issues/55)
        std::cout << "material not handle in plane" << std::endl;
        return VOID_COLOR;
    }

    return Math::Point3D(255, 0, 255);
}
