/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Triangle
*/

#include "Primitives/Triangle.hpp"

#include <cmath>
#include <iostream>

using std::sqrt;

Primitive::Triangle::Triangle() : _rotation(0,0,0), _vertex1(0,0,0), _vertex2(0,0,0), _vertex3(0, 0, 0), _material(nullptr)
{
    createNormals();
}

Primitive::Triangle::Triangle(const Math::Point3D& vertex1, const Math::Point3D& vertex2, const Math::Point3D& vertex3, std::shared_ptr<Material::IMaterial> material) :
_vertex1(vertex1), _vertex2(vertex2), _vertex3(vertex3), _material(material)
{
    createNormals();
}

Primitive::Triangle::Triangle(const Math::Point3D& vertex1, const Math::Point3D& vertex2, const Math::Point3D& vertex3) :
_vertex1(vertex1), _vertex2(vertex2), _vertex3(vertex3)
{
    createNormals();
}

Math::Point3D Primitive::Triangle::hitPoint(const Raytracer::Ray& ray)
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Point3D rayDirection = ray.direction();
    rayOrigin.rotateX(this->_rotation.x());
    rayOrigin.rotateY(this->_rotation.y());
    rayOrigin.rotateZ(this->_rotation.z());
    rayDirection.rotateX(this->_rotation.x());
    rayDirection.rotateY(this->_rotation.y());
    rayDirection.rotateZ(this->_rotation.z());

    Math::Vector3D normal = getNormal(Math::Vector3D(0,0,0), ray);

    if (normal.dot(rayDirection) == 0)
        return Math::Vector3D(-1,-1,-1);

    Math::Point3D A = _vertex1;
    Math::Point3D B = _vertex2;
    Math::Point3D C = _vertex3;

    double d = normal.dot(A);

    double t = (d - normal.dot(rayOrigin)) / normal.dot(rayDirection);

    Math::Point3D hitPoint = rayOrigin + (rayDirection * t);

    if (((B-A).cross(hitPoint - A)).dot((hitPoint - A).cross(C - A)) < 0)
        return Math::Vector3D(-1,-1,-1);
    if (((C-B).cross(hitPoint - B)).dot((hitPoint - B).cross(A - B)) < 0)
        return Math::Vector3D(-1,-1,-1);
    if (((A-C).cross(hitPoint - C)).dot((hitPoint - C).cross(B - C)) < 0)
        return Math::Vector3D(-1,-1,-1);

    return hitPoint;
}

void Primitive::Triangle::setVertex1(const Math::Point3D& vertex1)
{
    _vertex1 = vertex1;
    createNormals();
}

void Primitive::Triangle::setVertex2(const Math::Point3D& vertex2)
{
    _vertex2 = vertex2;
    createNormals();
}

void Primitive::Triangle::setVertex3(const Math::Point3D& vertex3)
{
    _vertex3 = vertex3;
    createNormals();
}

void Primitive::Triangle::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

std::shared_ptr<Material::IMaterial> Primitive::Triangle::getMaterial() const
{
    return this->_material;
}

Math::Vector3D Primitive::Triangle::getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const
{
    (void) hitPoint;

    Math::Vector3D normal = _normal;
    Math::Vector3D rayDirection = ray.direction();

    double n = normal.dot(rayDirection);
    double d  = normal.length() * rayDirection.length();

    double angle = acos(n / d) * 180 / M_PI;

    if (angle >= 90)
        return _normal;
    return _inverseNormal;
}

void Primitive::Triangle::createNormals()
{
    Math::Vector3D A = _vertex1;
    Math::Vector3D B = _vertex2;
    Math::Vector3D C = _vertex3;

    Math::Vector3D u = B - A;
    Math::Vector3D v = C - A;

    setTriangleNormal(u.cross(v));
    setTriangleInverseNormal(v.cross(u));
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

Math::Vector3D Primitive::Triangle::getTriangleNormal() const
{
    return _normal;
}

Math::Vector3D Primitive::Triangle::getTriangleInverseNormal() const
{
    return _inverseNormal;
}

void Primitive::Triangle::setTriangleNormal(const Math::Vector3D& normal)
{
    _normal = normal;
}

void Primitive::Triangle::setTriangleInverseNormal(const Math::Vector3D& inverseNormal)
{
    _inverseNormal = inverseNormal;
}

Optimisation::cubeCollider Primitive::Triangle::getColliderBox() const
{
    Optimisation::cubeCollider collider;

    collider.maxX.second = std::max(_vertex1.x(), std::max(_vertex2.x(), _vertex3.x()));
    collider.minX.second = std::min(_vertex1.x(), std::min(_vertex2.x(), _vertex3.x()));
    collider.maxY.second = std::max(_vertex1.y(), std::max(_vertex2.y(), _vertex3.y()));
    collider.minY.second = std::min(_vertex1.y(), std::min(_vertex2.y(), _vertex3.y()));
    collider.maxZ.second = std::max(_vertex1.z(), std::max(_vertex2.z(), _vertex3.z()));
    collider.minZ.second = std::min(_vertex1.z(), std::min(_vertex2.z(), _vertex3.z()));

    collider.maxX.first = false;
    collider.minX.first = false;
    collider.maxY.first = false;
    collider.minY.first = false;
    collider.maxZ.first = false;
    collider.minZ.first = false;

    return collider;
}
