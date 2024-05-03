/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#include "Primitives/Cone.hpp"

#include <cmath>

using std::sqrt;

Primitive::Cone::Cone() : _position(0,0,0), _radius(1), _axis(Axis::X), _material(nullptr){}

Primitive::Cone::Cone(const Math::Point3D& origin, double radius, Axis axis, std::shared_ptr<Material::IMaterial> material) :
_position(origin), _radius(radius), _axis(axis), _material(material){}

Math::Point3D Primitive::Cone::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    Math::Vector3D vectorConeToRay(rayOrigin.x() - _position.x(), rayOrigin.y() - _position.y(), rayOrigin.z() - _position.z());
    double a = rayDirection.dot(rayDirection);
    double b = 2 * vectorConeToRay.dot(rayDirection);
    double c = vectorConeToRay.dot(vectorConeToRay) - _radius * _radius;

    double discriminant = b * b - 4 * a * c;

    if (!IS_HIT(discriminant))
        return Math::Point3D(-1,-1,-1);

    double hitValue = (-b - sqrt(discriminant)) / (2.0 * a);

    Math::Point3D hitPoint = rayOrigin + rayDirection * hitValue;

    return hitPoint;
}

Math::Point3D Primitive::Cone::computeColor(const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    Math::Vector3D ConeNormal(hitPoint.x() - _position.x(), hitPoint.y() - _position.y(), hitPoint.z() - _position.z());


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

void Primitive::Cone::setRadius(double radius)
{
    this->_radius = radius;
}

void Primitive::Cone::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

Math::Point3D Primitive::Cone::getOrigin() const
{
    return this->_position;
}

double Primitive::Cone::getRadius() const
{
    return this->_radius;
}

std::shared_ptr<Material::IMaterial> Primitive::Cone::getMaterial() const
{
    return this->_material;
}
