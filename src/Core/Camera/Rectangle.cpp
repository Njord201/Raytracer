/*
** EPITECH PROJECT, 2024
** Rectangle.cpp
** File description:
** Raytracer
*/

#include "Camera/Rectangle.hpp"

Raytracer::Rectangle3D::Rectangle3D() : _origin{0,0,0}, _bottom_side(0,0,0), _left_side(0,0,0)
{
    
}

Raytracer::Rectangle3D::Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side,
    Math::Vector3D left_side)
{
    this->_origin = origin;
    this->_bottom_side = bottom_side;
    this->_left_side = left_side;
}

Raytracer::Rectangle3D::~Rectangle3D()
{
}

Math::Point3D Raytracer::Rectangle3D::pointAt(double u, double v)
{
    Math::Vector3D offset = (this->_bottom_side * u) + (this->_left_side * v);
    return _origin + offset;
}

Math::Point3D Raytracer::Rectangle3D::getOrigin(void)
{
    return this->_origin;
}

Math::Vector3D Raytracer::Rectangle3D::getBottomSide(void)
{
    return this->_bottom_side;
}

Math::Vector3D Raytracer::Rectangle3D::getLeftSide(void)
{
    return this->_left_side;
}

