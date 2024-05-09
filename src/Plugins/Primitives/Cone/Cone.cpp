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
    rayOrigin.rotateX(this->_rotation.x());
    rayOrigin.rotateY(this->_rotation.y());
    rayOrigin.rotateZ(this->_rotation.z());
    rayDirection.rotateX(this->_rotation.x());
    rayDirection.rotateY(this->_rotation.y());
    rayDirection.rotateZ(this->_rotation.z());

    Math::Vector3D vectorConeToRay(rayOrigin.x() - _position.x(),
                                   rayOrigin.y() - _position.y(),
                                   rayOrigin.z() - _position.z());
    vectorConeToRay.rotateX(this->_rotation.x());
    vectorConeToRay.rotateY(this->_rotation.y());
    vectorConeToRay.rotateZ(this->_rotation.z());

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

    Math::Vector3D rayOriginToHit = hitPoint - rayOrigin;
    if (IS_INVERSE(rayOriginToHit.x(), rayDirection.x()) || IS_INVERSE(rayOriginToHit.y(), rayDirection.y()) || IS_INVERSE(rayOriginToHit.z(), rayDirection.z()))
        return Math::Point3D(-1,-1,-1);

    hitPoint.rotateX(this->_rotation.x());
    hitPoint.rotateY(this->_rotation.y());
    hitPoint.rotateZ(this->_rotation.z());
    return hitPoint;
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

void Primitive::Cone::setRotation(Math::Vector3D rotation)
{
    this->_rotation = rotation;
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

Math::Vector3D Primitive::Cone::getNormal(const Math::Vector3D& hitPoint) const
{
    Math::Vector3D coneNormal;
    Math::Vector3D hit = hitPoint;

    if (_axis == Axis::X)
        coneNormal = Math::Vector3D(_position.x() + hit.x(), _position.y() - hit.y(), _position.z() - hit.z());
    if (_axis == Axis::Y)
        coneNormal = Math::Vector3D(_position.x() - hit.x(), _position.y() + hit.y(), _position.z() - hit.z());
    if (_axis == Axis::Z)
        coneNormal = Math::Vector3D(_position.x() - hit.x(), _position.y() - hit.y(), _position.z() + hit.z());
    coneNormal = coneNormal / coneNormal.length();
    coneNormal *= -1;

    return coneNormal;
}
