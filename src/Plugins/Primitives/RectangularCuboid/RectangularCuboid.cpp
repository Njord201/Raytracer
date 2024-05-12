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
    _rotation = Math::Vector3D(0, 0, 0);
}

Primitive::RectangularCuboid::RectangularCuboid(double maxX, double maxY, double maxZ, double minX, double minY, double minZ, std::shared_ptr<Material::IMaterial> material) {
    _maxX = maxX;
    _maxY = maxY;
    _maxZ = maxZ;
    _minX = minX;
    _minY = minY;
    _minZ = minZ;
    _material = material;
}

Math::Point3D Primitive::RectangularCuboid::checkRayReachPrimitive(double t, Math::Vector3D vDir, Math::Point3D origin) const
{
    Math::Point3D hitPoint = origin + vDir * t;

    if (hitPoint.x() >= _minX && hitPoint.x() <= _maxX &&
        hitPoint.y() >= _minY && hitPoint.y() <= _maxY &&
        hitPoint.z() >= _minZ && hitPoint.z() <= _maxZ)
        return hitPoint;
    return Math::Point3D(-1, -1, -1);
}

Math::Point3D Primitive::RectangularCuboid::hitPoint(const Raytracer::Ray& ray)
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();
    rayOrigin.rotateX(this->_rotation.x());
    rayOrigin.rotateY(this->_rotation.y());
    rayOrigin.rotateZ(this->_rotation.z());
    rayDirection.rotateX(this->_rotation.x());
    rayDirection.rotateY(this->_rotation.y());
    rayDirection.rotateZ(this->_rotation.z());

    if (rayDirection.x() != 0) {
        double tXmin = (_minX - rayOrigin.x()) / rayDirection.x();
        double tXmax = (_maxX - rayOrigin.x()) / rayDirection.x();
        if (tXmin > tXmax)
            std::swap(tXmin, tXmax);

        auto hitPoint = checkRayReachPrimitive(tXmin, rayDirection, rayOrigin);
        if (hitPoint != Math::Point3D(-1, -1, -1))
            return hitPoint;
    }
    if (rayDirection.y() != 0) {
        double tYmin = (_minY - rayOrigin.y()) / rayDirection.y();
        double tYmax = (_maxY - rayOrigin.y()) / rayDirection.y();
        if (tYmin > tYmax)
            std::swap(tYmin, tYmax);

        auto hitPoint = checkRayReachPrimitive(tYmin, rayDirection, rayOrigin);
        if (hitPoint != Math::Point3D(-1, -1, -1))
            return hitPoint;
    }
    if (rayDirection.z() != 0) {
        double tZmin = (_minZ - rayOrigin.z()) / rayDirection.z();
        double tZmax = (_maxZ - rayOrigin.z()) / rayDirection.z();
        if (tZmin > tZmax)
            std::swap(tZmin, tZmax);

        auto hitPoint = checkRayReachPrimitive(tZmin, rayDirection, rayOrigin);
        if (hitPoint != Math::Point3D(-1, -1, -1))
            return hitPoint;
    }

    return Math::Point3D(-1, -1, -1);
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

Math::Vector3D Primitive::RectangularCuboid::getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const
{
    (void) ray;

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

void Primitive::RectangularCuboid::setRotation(Math::Vector3D rotation)
{
    _rotation = rotation;
}

Optimisation::cubeCollider Primitive::RectangularCuboid::getColliderBox() const
{
    Optimisation::cubeCollider collider;

    collider.maxX.second = _maxX;
    collider.minX.second = _minX;
    collider.maxY.second = _maxY;
    collider.minY.second = _minY;
    collider.maxZ.second = _maxZ;
    collider.minZ.second = _minZ;

    collider.maxX.first = false;
    collider.minX.first = false;
    collider.maxY.first = false;
    collider.minY.first = false;
    collider.maxZ.first = false;
    collider.minZ.first = false;

    return collider;
}
