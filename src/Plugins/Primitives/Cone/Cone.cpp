/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#include "Primitives/Cone.hpp"

#include <cmath>

using std::sqrt;

Primitive::Cone::Cone() : _position(0,0,0), _angle(25), _axis(Axis::X), _material(nullptr){}

Primitive::Cone::Cone(const Math::Point3D& origin, double angle, Axis axis, std::shared_ptr<Material::IMaterial> material) :
_position(origin), _angle(angle), _axis(axis), _material(material){}

Math::Point3D Primitive::Cone::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    rayOrigin = Math::Point3D(rayOrigin.x(), rayOrigin.y(), rayOrigin.z());
    rayDirection = Math::Point3D(rayDirection.x(), rayDirection.y(), rayDirection.z());

    Math::Vector3D vectorConeToRay(rayOrigin.x() - _position.x(), rayOrigin.y() - _position.y(), rayOrigin.z() - _position.z());

    double a, b, c;
    double angle = _angle * M_PI / 180 / 2;
    double tanAngle = tan(angle) * tan(angle);

    if (_axis == Axis::X) {
        a = -1 * pow(rayDirection.x(), 2) * tanAngle + pow(rayDirection.y(), 2) + pow(rayDirection.z(), 2);
        b = 2 * (-1 * (vectorConeToRay.x() * rayDirection.x() * tanAngle) + (vectorConeToRay.y() * rayDirection.y()) + (vectorConeToRay.z() * rayDirection.z()));
        c = -1 * pow(vectorConeToRay.x(), 2) * tanAngle + pow(vectorConeToRay.y(), 2) + pow(vectorConeToRay.z(), 2);
    }
    else if (_axis == Axis::Y) {
        a = pow(rayDirection.x(), 2) - pow(rayDirection.y(), 2) * tanAngle + pow(rayDirection.z(), 2);
        b = 2 * ((vectorConeToRay.x() * rayDirection.x()) - (vectorConeToRay.y() * rayDirection.y() * tanAngle) + (vectorConeToRay.z() * rayDirection.z()));
        c = pow(vectorConeToRay.x(), 2) - pow(vectorConeToRay.y(), 2) * tanAngle + pow(vectorConeToRay.z(), 2);
    }
    else {
        a = pow(rayDirection.x(), 2) + pow(rayDirection.y(), 2) - pow(rayDirection.z(), 2) * tanAngle;
        b = 2 * ((vectorConeToRay.x() * rayDirection.x()) + (vectorConeToRay.y() * rayDirection.y()) - (vectorConeToRay.z() * rayDirection.z() * tanAngle));
        c = pow(vectorConeToRay.x(), 2) + pow(vectorConeToRay.y(), 2) - pow(vectorConeToRay.z(), 2) * tanAngle;
    }

    double discriminant = b * b - 4 * a * c;

    if (!IS_HIT(discriminant))
        return Math::Point3D(-1,-1,-1);

    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);

    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    // Not compute reverse cone
    if (_axis == Axis::X && hitPoint.x() > _position.x())
        return Math::Point3D(-1,-1,-1);
    if (_axis == Axis::Y && hitPoint.y() > _position.y())
        return Math::Point3D(-1,-1,-1);
    if (_axis == Axis::Z && hitPoint.z() > _position.z())
        return Math::Point3D(-1,-1,-1);

    return hitPoint;
}

Math::Point3D Primitive::Cone::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    Math::Vector3D ConeNormal(hitPoint.x() - _position.x(), hitPoint.y() - _position.y(), hitPoint.z() - _position.z());

    return Math::Point3D(255,255,255);
    if (_material->getType() == Material::MaterialType::FlatColor) {
        std::shared_ptr<FlatColor> ConeFlatColor = std::dynamic_pointer_cast<FlatColor>(getMaterial());
        return lights.computeColor(ConeNormal, hitPoint, Math::Point3D(ConeFlatColor->getR(), ConeFlatColor->getG(), ConeFlatColor->getB()));
    }
    std::cout << "material not handle in Cone" << std::endl;
    return Math::Point3D(0,0,0);
}

void Primitive::Cone::setOrigin(Math::Point3D origin)
{
    this->_position = origin;
}

void Primitive::Cone::setAngle(double angle)
{
    this->_angle = angle;
}

void Primitive::Cone::setAxis(Axis axis)
{
    this->_axis = axis;
}

void Primitive::Cone::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

Math::Point3D Primitive::Cone::getOrigin() const
{
    return this->_position;
}

double Primitive::Cone::getAngle() const
{
    return this->_angle;
}

Primitive::Axis Primitive::Cone::getAxis() const
{
    return this->_axis;
}

std::shared_ptr<Material::IMaterial> Primitive::Cone::getMaterial() const
{
    return this->_material;
}
