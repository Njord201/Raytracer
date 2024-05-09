/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Triangle
*/

#include "Primitives/Triangle.hpp"

#include <cmath>

using std::sqrt;

Primitive::Triangle::Triangle() : _rotation(0,0,0), _vertex1(0,0,0), _vertex2(0,0,0), _vertex3(0, 0, 0), _material(nullptr){}

Primitive::Triangle::Triangle(const Math::Point3D& vertex1, const Math::Point3D& vertex2, const Math::Point3D& vertex3, std::shared_ptr<Material::IMaterial> material) :
_vertex1(vertex1), _vertex2(vertex2), _vertex3(vertex3), _material(material){}

Math::Point3D Primitive::Triangle::hitPoint(const Raytracer::Ray& ray) const
{
    (void) ray;
    return Math::Point3D(0,0,0);
}

void Primitive::Triangle::setVertex1(const Math::Point3D& vertex1)
{
    _vertex1 = vertex1;
}

void Primitive::Triangle::setVertex2(const Math::Point3D& vertex2)
{
    _vertex2 = vertex2;
}

void Primitive::Triangle::setVertex3(const Math::Point3D& vertex3)
{
    _vertex3 = vertex3;
}

void Primitive::Triangle::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

std::shared_ptr<Material::IMaterial> Primitive::Triangle::getMaterial() const
{
    return this->_material;
}

Math::Vector3D Primitive::Triangle::getNormal(const Math::Vector3D& hitPoint) const
{
    (void) hitPoint;
    return Math::Vector3D(0, 0, 0);
}

void Primitive::Triangle::setRotation(Math::Vector3D rotation)
{
    this->_rotation = rotation;
}

Math::Point3D Primitive::Triangle::getVertex1() const
{
    return _vertex1;
}

Math::Point3D Primitive::Triangle::getVertex2() const
{
    return _vertex2;
}

Math::Point3D Primitive::Triangle::getVertex3() const
{
    return _vertex3;
}
