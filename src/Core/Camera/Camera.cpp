/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** Raytracer
*/

#include "Camera/Camera.hpp"

Raytracer::Camera::Camera(): _origin(0,0,0), _screen()
{
}

Raytracer::Camera::Camera(const Camera& other)
{
    this->_origin = other._origin;
    this->_screen = other._screen;
}

Raytracer::Camera::~Camera()
{
}

Raytracer::Camera::Camera(Math::Point3D _origin, Rectangle3D _screen)
{
    this->_origin = _origin;
    this->_screen = _screen;
}

Raytracer::Ray Raytracer::Camera::ray(double u, double v)
{
    Math::Point3D screen_point = _screen.pointAt(u, v);
    Math::Vector3D direction(screen_point.x() - _origin.x(), screen_point.y() - _origin.y(), screen_point.z() - _origin.z());
    return Raytracer::Ray(_origin, direction);
}

Math::Point3D Raytracer::Camera::getOrigin(void)
{
    return this->_origin;
}

Raytracer::Rectangle3D Raytracer::Camera::getScreen(void)
{
    return this->_screen;
}
