/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RectangularCuboid
*/

#include "Primitives/RectangularCuboid.hpp"

Primitive::RectangularCuboid::RectangularCuboid() {
    _maxX = 0;
    _maxY = 0;
    _maxZ = 0;
    _minX = 0;
    _minY = 0;
    _minZ = 0;
}

Primitive::RectangularCuboid::RectangularCuboid(double maxX, double maxY, double maxZ, double minX, double minY, double minZ) {
    _maxX = maxX;
    _maxY = maxY;
    _maxZ = maxZ;
    _minX = minX;
    _minY = minY;
    _minZ = minZ;
}

Math::Point3D Primitive::RectangularCuboid::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();

    double tX = 0;
    double tY = 0;
    double tZ = 0;

    if (rayDirection.x() != 0) {
        double t1 = (_minX - rayOrigin.x()) / rayDirection.x();
        double t2 = (_maxX - rayOrigin.x()) / rayDirection.x();
        tX = t1 < t2 ? t1 : t2;
    } else {
        return Math::Point3D(-1, -1, -1);
    }
    if (rayDirection.y() != 0) {
        double t1 = (_minY - rayOrigin.y()) / rayDirection.y();
        double t2 = (_maxY - rayOrigin.y()) / rayDirection.y();
        tY = t1 < t2 ? t1 : t2;
    } else {
        return Math::Point3D(-1, -1, -1);
    }
    if (rayDirection.z() != 0) {
        double t1 = (_minZ - rayOrigin.z()) / rayDirection.z();
        double t2 = (_maxZ - rayOrigin.z()) / rayDirection.z();
        tZ = t1 < t2 ? t1 : t2;
    } else {
        return Math::Point3D(-1, -1, -1);
    }

    return Math::Point3D(tX, tY, tZ);
}

double Primitive::RectangularCuboid::getMinX() const
{
    return _minX;
}

double Primitive::RectangularCuboid::getMinY() const
{
    return _minY;
}

double Primitive::RectangularCuboid::getMinZ() const
{
    return _minZ;
}

double Primitive::RectangularCuboid::getMaxX() const
{
    return _maxX;
}

double Primitive::RectangularCuboid::getMaxY() const
{
    return _maxY;
}

double Primitive::RectangularCuboid::getMaxZ() const
{
    return _maxZ;
}

void Primitive::RectangularCuboid::setMaxX(double maxX)
{
    _maxX = maxX;
}

void Primitive::RectangularCuboid::setMaxY(double maxY)
{
    _maxY = maxY;
}

void Primitive::RectangularCuboid::setMaxZ(double maxZ)
{
    _maxZ = maxZ;
}

void Primitive::RectangularCuboid::setMinX(double minX)
{
    _minX = minX;
}

void Primitive::RectangularCuboid::setMinY(double minY)
{
    _minY = minY;
}

void Primitive::RectangularCuboid::setMinZ(double minZ)
{
    _minZ = minZ;
}

std::shared_ptr<Material::IMaterial> Primitive::RectangularCuboid::getMaterial() const
{
    return this->_material;
}

void Primitive::RectangularCuboid::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}

Math::Vector3D Primitive::RectangularCuboid::getNormal(const Math::Vector3D& hitPoint) const
{
    if (hitPoint.x() == _maxX)
        return Math::Vector3D(1, 0, 0);
    if (hitPoint.x() == _minX)
        return Math::Vector3D(-1, 0, 0);
    if (hitPoint.y() == _maxY)
        return Math::Vector3D(0, 1, 0);
    if (hitPoint.y() == _minY)
        return Math::Vector3D(0, -1, 0);
    if (hitPoint.z() == _maxZ)
        return Math::Vector3D(0, 0, 1);
    if (hitPoint.z() == _minZ)
        return Math::Vector3D(0, 0, -1);
    return Math::Vector3D(-1, -1, -1);
}
