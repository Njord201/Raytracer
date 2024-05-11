/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#include "Optimisation/Cube.hpp"

#include <iostream>

using Cube = Optimisation::Cube;
using cubeCollider = Optimisation::cubeCollider;

Cube::Cube(double minX, double minY, double minZ, double maxX, double maxY, double maxZ, PrimitivesContainer primitives, int nbRecursions)
{
    this->_collider.minX.second = minX;
    this->_collider.minY.second = minY;
    this->_collider.minZ.second = minZ;
    this->_collider.maxX.second = maxX;
    this->_collider.maxY.second = maxY;
    this->_collider.maxZ.second = maxZ;

    _nbRecursions = nbRecursions;
    identifyPrimitives(primitives);
}

Cube::Cube(cubeCollider collider, PrimitivesContainer primitives, int nbRecursions)
{
    this->_collider = collider;
    _nbRecursions = nbRecursions;
    identifyPrimitives(primitives);
}

void Cube::setMinX(double minX)
{
    this->_collider.minX.second = minX;
}

void Cube::setMinY(double minY)
{
    this->_collider.minY.second = minY;
}

void Cube::setMinZ(double minZ)
{
    this->_collider.minZ.second = minZ;
}

void Cube::setMaxX(double maxX)
{
    this->_collider.maxX.second = maxX;
}

void Cube::setMaxY(double maxY)
{
    this->_collider.maxY.second = maxY;
}

void Cube::setMaxZ(double maxZ)
{
    this->_collider.maxZ.second = maxZ;
}

double Cube::getMinX() const
{
    return this->_collider.minX.second;
}

double Cube::getMinY() const
{
    return this->_collider.minY.second;
}

double Cube::getMinZ() const
{
    return this->_collider.minZ.second;
}

double Cube::getMaxX() const
{
    return this->_collider.maxX.second;
}

double Cube::getMaxY() const
{
    return this->_collider.maxY.second;
}

double Cube::getMaxZ() const
{
    return this->_collider.maxZ.second;
}

void Cube::setCollider(const cubeCollider& collider)
{
    this->_collider = collider;
}

cubeCollider Cube::getCollider() const
{
    return this->_collider;
}

PrimitivesContainer Cube::getPrimitivesContainer(void) const
{
    return _primitives;
}

void Cube::identifyPrimitives(PrimitivesContainer primitives)
{
    if (primitives.getPrimitivesList().size() < 8) {
        _primitives = primitives;
        return;
    }
    for (auto primitive : primitives.getPrimitivesList()) {
        auto colliderP = primitive.get()->getColliderBox();

        if ((_collider.maxX.second < colliderP.minX.second) || (_collider.minX.second > colliderP.maxX.second) ||
            (_collider.maxY.second < colliderP.minY.second) || (_collider.minY.second > colliderP.maxY.second) ||
            (_collider.maxZ.second < colliderP.minZ.second) || (_collider.minZ.second > colliderP.maxZ.second)) {
            continue;
        } else {
            _primitives.add(primitive);
        }
    }
    if (_primitives.getPrimitivesList().size() > 2 && _nbRecursions > 0) {
        Cube cube0 = Cube(_collider.minX.second, _collider.minY.second, _collider.minZ.second, (_collider.minX.second + _collider.maxX.second) / 2, (_collider.minY.second + _collider.maxY.second) / 2, (_collider.minZ.second + _collider.maxZ.second) / 2, _primitives, _nbRecursions - 1);
        Cube cube1 = Cube(_collider.minX.second, _collider.minY.second, (_collider.minZ.second + _collider.maxZ.second) / 2, (_collider.minX.second + _collider.maxX.second) / 2, (_collider.minY.second + _collider.maxY.second) / 2, _collider.maxZ.second, _primitives, _nbRecursions - 1);
        Cube cube2 = Cube(_collider.minX.second, (_collider.minY.second + _collider.maxY.second) / 2, _collider.minZ.second, (_collider.minX.second + _collider.maxX.second) / 2, _collider.maxY.second, (_collider.minZ.second + _collider.maxZ.second) / 2, _primitives, _nbRecursions - 1);
        Cube cube3 = Cube(_collider.minX.second, (_collider.minY.second + _collider.maxY.second) / 2, (_collider.minZ.second + _collider.maxZ.second) / 2, (_collider.minX.second + _collider.maxX.second) / 2, _collider.maxY.second, _collider.maxZ.second, _primitives, _nbRecursions - 1);
        Cube cube4 = Cube((_collider.minX.second + _collider.maxX.second) / 2, _collider.minY.second, _collider.minZ.second, _collider.maxX.second, (_collider.minY.second + _collider.maxY.second) / 2, (_collider.minZ.second + _collider.maxZ.second) / 2, _primitives, _nbRecursions - 1);
        Cube cube5 = Cube((_collider.minX.second + _collider.maxX.second) / 2, _collider.minY.second, (_collider.minZ.second + _collider.maxZ.second) / 2, _collider.maxX.second, (_collider.minY.second + _collider.maxY.second) / 2, _collider.maxZ.second, _primitives, _nbRecursions - 1);
        Cube cube6 = Cube((_collider.minX.second + _collider.maxX.second) / 2, (_collider.minY.second + _collider.maxY.second) / 2, _collider.minZ.second, _collider.maxX.second, _collider.maxY.second, (_collider.minZ.second + _collider.maxZ.second) / 2, _primitives, _nbRecursions - 1);
        Cube cube7 = Cube((_collider.minX.second + _collider.maxX.second) / 2, (_collider.minY.second + _collider.maxY.second) / 2, (_collider.minZ.second + _collider.maxZ.second) / 2, _collider.maxX.second, _collider.maxY.second, _collider.maxZ.second, _primitives, _nbRecursions - 1);

        std::size_t nb = 0;
        if (cube0.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube1.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube2.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube3.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube4.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube5.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube6.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;
        if (cube7.getPrimitivesContainer().getPrimitivesList().size() != 0)
            nb++;

        if (nb < _primitives.getPrimitivesList().size()) {
            if (cube0.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube0);
            if (cube1.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube1);
            if (cube2.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube2);
            if (cube3.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube3);
            if (cube4.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube4);
            if (cube5.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube5);
            if (cube6.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube6);
            if (cube7.getPrimitivesContainer().getPrimitivesList().size() != 0)
                _cubes.push_back(cube7);
        }
    }
}

static bool checkRayReachPrimitive(double t, Math::Vector3D vDir, Math::Point3D origin, cubeCollider collider)
{
    Math::Point3D hitPoint = origin + vDir * t;

    if (hitPoint.x() >= collider.minX.second && hitPoint.x() <= collider.maxX.second &&
        hitPoint.y() >= collider.minY.second && hitPoint.y() <= collider.maxY.second &&
        hitPoint.z() >= collider.minZ.second && hitPoint.z() <= collider.maxZ.second)
        return true;
    return false;
}

static bool isCubeHit(const Raytracer::Ray &ray, const Cube cube)
{
    Math::Point3D rayOrigin = ray.origin();
    Math::Vector3D rayDirection = ray.direction();
    cubeCollider collider = cube.getCollider();

    if (rayDirection.x() != 0) {
        double tXmin = (collider.minX.second - rayOrigin.x()) / rayDirection.x();
        double tXmax = (collider.maxX.second - rayOrigin.x()) / rayDirection.x();
        if (tXmin > tXmax)
            std::swap(tXmin, tXmax);

        if (checkRayReachPrimitive(tXmin, rayDirection, rayOrigin, collider))
            return true;
    }
    if (rayDirection.y() != 0) {
        double tYmin = (collider.minY.second - rayOrigin.y()) / rayDirection.y();
        double tYmax = (collider.maxY.second - rayOrigin.y()) / rayDirection.y();
        if (tYmin > tYmax)
            std::swap(tYmin, tYmax);

        if (checkRayReachPrimitive(tYmin, rayDirection, rayOrigin, collider))
            return true;
    }
    if (rayDirection.z() != 0) {
        double tZmin = (collider.minZ.second - rayOrigin.z()) / rayDirection.z();
        double tZmax = (collider.maxZ.second - rayOrigin.z()) / rayDirection.z();
        if (tZmin > tZmax)
            std::swap(tZmin, tZmax);

        if (checkRayReachPrimitive(tZmin, rayDirection, rayOrigin, collider))
            return true;
    }

    return false;
}

PrimitivesContainer Cube::getPrimitivesHits(const Raytracer::Ray ray) const
{
    for (std::size_t i = 0; i < _cubes.size(); i++) {
        if (isCubeHit(ray, _cubes[i])) {
            return _cubes[i].getPrimitivesHits(ray);
        }
    }
    return _primitives;
}
