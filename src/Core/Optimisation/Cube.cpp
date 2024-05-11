/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#include "Cube.hpp"

Cube::Cube(double minX, double minY, double minZ, double maxX, double maxY, double maxZ)
{
    this->_collider.minX.second = minX;
    this->_collider.minY.second = minY;
    this->_collider.minZ.second = minZ;
    this->_collider.maxX.second = maxX;
    this->_collider.maxY.second = maxY;
    this->_collider.maxZ.second = maxZ;
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

void Cube::setCollider(const Octree::cubeCollider& collider)
{
    this->_collider = collider;
}

Octree::cubeCollider Cube::getCollider() const
{
    return this->_collider;
}

void Cube::identifyPrimitives(const std::vector<IPrimitive> &primitives)
{
    for (auto &primitive : primitives) {
        auto collider = primitive.getColliderBox();
        if ((collider.minX.first || (collider.minX.second >= _collider.minX.second && collider.minX.second <= _collider.maxX.second)) ||
            (collider.minY.first || (collider.minY.second >= _collider.minY.second && collider.minY.second <= _collider.maxY.second)) ||
            (collider.minZ.first || (collider.minZ.second >= _collider.minZ.second && collider.minZ.second <= _collider.maxZ.second)) ||
            (collider.maxX.first || (collider.maxX.second >= _collider.minX.second && collider.maxX.second <= _collider.maxX.second)) ||
            (collider.maxY.first || (collider.maxY.second >= _collider.minY.second && collider.maxY.second <= _collider.maxY.second)) ||
            (collider.maxZ.first || (collider.maxZ.second >= _collider.minZ.second && collider.maxZ.second <= _collider.maxZ.second))) {
                _primitives.push_back(primitive);
        }
    }
}
